/**
 * @file lzw-runner.cpp
 * @author Juho Röyskö
 * @brief Runs LZW coding
 * @version 0.1
 * @date 2021-10-01
 */
#include <string>
#include <vector>
#include <iostream>
#include "file-manager.hpp"
#include "lzw-coding.hpp"

const int B = 11;

/**
 * @brief Compress file with LZW coding
 * 
 * @param input_file File to compress
 * @param verbose If true then print what function is doing
 */
void LZWCompress(std::string const &input_file, bool verbose = 1)
{
    if (verbose)
    {
        std::cout << "Compressing file with LZW coding" << std::endl;
        std::cout << "Reading file '" << input_file << "'" << std::endl;
    }
    std::string data = ReadFile(input_file);

    if (verbose)
        std::cout << "Compressing data" << std::endl;
    std::vector<int> encoded_data = LZWEncode(data);

    std::string output_file = input_file + ".bnzip";
    RemovePath(output_file);
    FileWriter file_writer(output_file);

    if (verbose)
        std::cout << "Writing compressed data to file '" << output_file << "'" << std::endl;
    file_writer.Write(1); // Tell decompressor that this file is compressed with LZW.
    for (int x : encoded_data)
    {
        file_writer.Write(x, B);
    }

    file_writer.Pad("00000000");
    file_writer.Close();
}

/**
 * @brief Decompress file that has been compressed with LZW coding
 * 
 * @param input_file File to decompress
 * @param verbose If true then print what function is doing
 */
void LZWDecompress(std::string const &input_file, bool verbose = 0)
{
    if (verbose)
    {
        std::cout << "Decompressing file with LZW coding" << std::endl;
        std::cout << "Reading file '" << input_file << "'" << std::endl;
    }
    std::string data = ReadFile(input_file);
    data = data.substr(1); // Remove first byte

    if (verbose)
        std::cout << "Parsing compressed data" << std::endl;

    std::vector<int> codes;
    int currbyte = 0;
    int bitcount = 0;
    for (char c : data)
    {
        for (int i = 7; i >= 0; --i)
        {
            int bit = (c & (1 << i)) > 0;
            currbyte = currbyte << 1 | bit;
            ++bitcount;
            if (bitcount == B)
            {
                codes.push_back(currbyte);
                currbyte = 0;
                bitcount = 0;
            }
        }
    }

    if (verbose)
        std::cout << "Decompressing data" << std::endl;
    std::string decoded_data = LZWDecode(codes);

    std::string output_file = input_file;
    RemoveExtension(output_file);
    RemovePath(output_file);

    if (verbose)
        std::cout << "Writing decompressed data to file '" << output_file << "'" << std::endl;
    FileWriter file_writer(output_file);
    file_writer.Write(decoded_data);
    file_writer.Close();
}