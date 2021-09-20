/**
 * @file move-to-front-transform.hpp
 * @author Juho Röyskö
 * @brief Header file for move-to-front-transform.cpp
 * @version 0.2
 * @date 2021-09-20
 */
#pragma once
#include <string>
#include <vector>

std::vector<uint8_t> MTFTEncode(std::string input);
std::string MTFTDecode(std::vector<uint8_t> input);
