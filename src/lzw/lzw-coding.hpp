/**
 * @file lzw-coding.hpp
 * @author Juho Röyskö
 * @brief Header file for lzw-coding.cpp
 * @version 0.1.2
 * @date 2021-10-30
 */
#include <vector>

std::vector<int> LZWEncode(std::string const &data);
std::string LZWDecode(std::vector<int> const &encoded_data);