/**
 * @file huffman-runner.cpp
 * @author Juho Röyskö
 * @brief Manages files and runs Huffman coding
 * @version 0.1
 * @date 2021-09-22
 */
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>
#include "huffman-coding.hpp"

const int ALPHABET_SIZE = 256;

/**
 * @brief Read file into a single string
 * 
 * @param input_file File to read
 * @return std::string File content
 */
std::string ReadFile(std::string input_file)
{
    std::ifstream in_file;
    in_file.open(input_file);

    std::stringstream str_stream;
    str_stream << in_file.rdbuf();
    std::string str = str_stream.str();

    return str;
}

/**
 * @brief Remove leading path to file
 * 
 * @param file_path File path to remove leading path from
 */
void RemovePath(std::string &file_path)
{
    for (int i = file_path.length() - 1; i >= 0; --i)
    {
        if (file_path[i] == '/')
        {
            file_path = file_path.substr(i + 1, file_path.length() - i - 1);
            return;
        }
    }
}

/**
 * @brief Compress a file using Huffman coding
 * 
 * @param input_file File to compress
 * @param verbose If true then print what function is doing
 */
void HuffmanCompress(std::string const &input_file, bool verbose = 0)
{
    if (verbose)
        std::cout << "Reading file '" << input_file << "'" << std::endl;
    std::string str = ReadFile(input_file);

    if (verbose)
        std::cout << "Compressing data" << std::endl;
    std::string *codes = HCEncode(str);

    // Get name and path for output file.
    std::string output_file = input_file;
    RemovePath(output_file);
    output_file += ".bnzip";

    // Open file.
    if (verbose)
        std::cout << "Writing compressed data to file '" << output_file << "'" << std::endl;
    std::ofstream fout;
    fout.open(output_file, std::ios::binary | std::ios::out);

    // Write codebook to file.
    std::string longest = "";
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        if (codes[i].length() > longest.length())
            longest = codes[i];
        uint8_t len = codes[i].length();
        fout.write((char *)&len, 1);
    }

    // Write compressed data to file.
    int currbyte = 0;
    int bitcount = 0;
    for (uint8_t x : str)
    {
        for (char c : codes[x])
        {
            int bit = c == '1';
            currbyte = currbyte << 1 | bit;
            ++bitcount;
            if (bitcount == 8)
            {
                fout.write((char *)&currbyte, 1);
                currbyte = 0;
                bitcount = 0;
            }
        }
    }

    // If there are some bits left pad the end of file with a code that has a length >= 8
    if (bitcount > 0)
    {
        for (char c : longest)
        {
            int bit = c == '1';
            currbyte = currbyte << 1 | bit;
            ++bitcount;
            if (bitcount == 8)
            {
                fout.write((char *)&currbyte, 1);
                break;
            }
        }
    }
    fout.close();
}

/**
 * @brief Decompress a file that was compressed with Huffman coding
 * 
 * @param input_file File to decompress
 * @param verbose If true then print what function is doing
 */
void HuffmanDecompress(std::string const &input_file, bool verbose = 0)
{
    if (verbose)
        std::cout << "Reading file '" << input_file << "'" << std::endl;
    std::string data = ReadFile(input_file);

    if (verbose)
        std::cout << "Decompressing data" << std::endl;
    std::string decoded_data = HCDecode(data);

    std::string output_file = input_file;
    while (output_file.length() >= 6 && output_file.substr(output_file.length() - 6, 6) == ".bnzip")
        output_file = output_file.substr(0, output_file.length() - 6);
    RemovePath(output_file);

    if (verbose)
        std::cout << "Writing decompressed data to file '" << output_file << "'" << std::endl;
    std::ofstream out(output_file);
    out << decoded_data;
    out.close();
}