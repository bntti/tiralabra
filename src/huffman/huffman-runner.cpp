/**
 * @file huffman-runner.cpp
 * @author Juho Röyskö
 * @brief Runs Huffman coding
 * @version 0.5.0
 * @date 2021-10-30
 */
#include <iostream>
#include "huffman-coding.hpp"
#include "../file-manager.hpp"
#include "../constants.hpp"

/**
 * @brief Compress a file using Huffman coding
 *
 * @param input_file Path to the file to compress
 * @param verbose If true then print what function is doing
 */
void HuffmanCompress(std::string const &input_file, bool verbose = 0)
{
    if (verbose)
    {
        std::cout << "Compressing file with Huffman coding" << std::endl;
        std::cout << "Reading file '" << input_file << "'" << std::endl;
    }
    std::string data = ReadFile(input_file);

    if (verbose)
        std::cout << "Compressing data" << std::endl;
    std::string *codes = HCCreateCodebook(data);

    // Get name and path for the output file
    std::string output_file = input_file;
    RemovePath(output_file);
    output_file += ".bnzip";

    if (verbose)
        std::cout << "Writing compressed data to file '" << output_file << "'" << std::endl;

    // Open file
    FileWriter file_writer(output_file);
    file_writer.Write(0); // Tell decompressor that this file is compressed with Huffman coding

    // Write codebook to file and find longest code
    std::string longest_code = "";
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        if (codes[i].length() > longest_code.length())
            longest_code = codes[i];
        uint8_t len = codes[i].length();
        file_writer.Write(len);
    }

    // Write compressed data to file
    for (uint8_t x : data)
        file_writer.BinaryWrite(codes[x]);

    // If there are some bits left pad the end of file with a code that has a length >= 8
    file_writer.Pad(longest_code);

    // Close file
    file_writer.Close();
}

/**
 * @brief Decompress a file that was compressed with Huffman coding
 *
 * @param input_file Path to the file to decompress
 * @param verbose If true then print what function is doing
 */
void HuffmanDecompress(std::string const &input_file, bool verbose = 0)
{
    if (verbose)
    {
        std::cout << "Decompressing file with Huffman coding" << std::endl;
        std::cout << "Reading file '" << input_file << "'" << std::endl;
    }
    std::string data = ReadFile(input_file);
    data = data.substr(1); // Remove first byte

    if (verbose)
        std::cout << "Decompressing data" << std::endl;
    std::string decoded_data = HCDecode(data);

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