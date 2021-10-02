/**
 * @file lzw-runner.cpp
 * @author Juho Röyskö
 * @brief Runs LZW coding
 * @version 0.1.2
 * @date 2021-10-02
 */
#include <string>
#include <vector>
#include <iostream>
#include "../constants.hpp"
#include "../file-manager.hpp"
#include "lzw-coding.hpp"

/**
 * @brief Compress file with LZW coding
 * 
 * @param input_file Path to the file to compress
 * @param verbose If true then print what function is doing
 */
void LZWCompress(std::string const &input_file, bool verbose = 0)
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

    // Get name and path for the output file
    std::string output_file = input_file + ".bnzip";
    RemovePath(output_file);

    // Open file
    FileWriter file_writer(output_file);
    file_writer.Write(1); // Tell decompressor that this file is compressed with LZW coding

    if (verbose)
        std::cout << "Writing compressed data to file '" << output_file << "'" << std::endl;
    for (int x : encoded_data)
    {
        file_writer.Write(x, LZW_CODE_SIZE);
    }

    file_writer.Pad("00000000");
    file_writer.Close();
}

/**
 * @brief Decompress file that has been compressed with LZW coding
 * 
 * @param input_file Path to the file to decompress
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

    // Read codes from compressed data
    std::vector<int> codes;
    int current_byte = 0;
    int bit_count = 0;
    for (char c : data)
    {
        for (int i = 7; i >= 0; --i)
        {
            int bit = (c & (1 << i)) > 0;
            current_byte = current_byte << 1 | bit;
            ++bit_count;
            if (bit_count == LZW_CODE_SIZE)
            {
                codes.push_back(current_byte);
                current_byte = 0;
                bit_count = 0;
            }
        }
    }

    if (verbose)
        std::cout << "Decompressing data" << std::endl;
    std::string decoded_data = LZWDecode(codes);

    // Get name and path for the output file
    std::string output_file = input_file;
    RemoveExtension(output_file);
    RemovePath(output_file);

    if (verbose)
        std::cout << "Writing decompressed data to file '" << output_file << "'" << std::endl;
    FileWriter file_writer(output_file);
    file_writer.Write(decoded_data);
    file_writer.Close();
}