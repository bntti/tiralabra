/**
 * @file huffman-coding.hpp
 * @author Juho Röyskö
 * @brief Header file for huffman-coding.cpp
 * @version 0.1.2
 * @date 2021-10-30
 */
#include <string>

std::string *HCCreateCodebook(std::string const &data);
std::string HCDecode(std::string const &encoded_data);