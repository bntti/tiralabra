/**
 * @file huffman-runner.hpp
 * @author Juho Röyskö
 * @brief Header file for huffman-runner.cpp
 * @version 0.1
 * @date 2021-09-22
 */
#include <string>

void HuffmanCompress(std::string const &input_file, bool verbose = 0);
void HuffmanDecompress(std::string const &input_file, bool verbose = 0);