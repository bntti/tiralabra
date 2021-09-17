/**
 * @file burrows-wheeler-transform.hpp
 * @author Juho Röyskö
 * @brief Header file for burrows-wheeler-transform.cpp
 * @version 0.1
 * @date 2021-09-17
 */
#pragma once
#include <string>

std::string BWTEncode(std::string input);
std::string BWTDecode(std::string input);