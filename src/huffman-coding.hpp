/**
 * @file huffman-coding.hpp
 * @author Juho Röyskö
 * @brief Header file for huffman-coding.cpp
 * @version 0.1
 * @date 2021-09-22
 */
#include <vector>
#include <string>

std::string *HCEncode(std::string const &input);
std::string HCDecode(std::string const &input);