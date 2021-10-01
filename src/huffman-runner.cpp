/**
 * @file huffman-runner.cpp
 * @author Juho Röyskö
 * @brief Runs Huffman coding
 * @version 0.3
 * @date 2021-10-01
 */
#include <iostream>
#include "huffman-coding.hpp"
#include "file-manager.hpp"

const int ALPHABET_SIZE = 256;

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

    FileWriter file_writer(output_file);

    // Write codebook to file and find longest code.
    std::string longest = "";
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        if (codes[i].length() > longest.length())
            longest = codes[i];
        uint8_t len = codes[i].length();
        file_writer.Write(len);
    }

    // Write compressed data to file.
    for (uint8_t x : str)
        file_writer.BinaryWrite(codes[x]);

    // If there are some bits left pad the end of file with a code that has a length >= 8
    file_writer.Pad(longest);

    // Close file
    file_writer.Close();
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
    RemoveExtension(output_file);
    RemovePath(output_file);

    if (verbose)
        std::cout << "Writing decompressed data to file '" << output_file << "'" << std::endl;
    FileWriter file_writer(output_file);
    file_writer.Write(decoded_data);
    file_writer.Close();
}