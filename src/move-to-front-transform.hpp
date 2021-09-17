/**
 * @file move-to-front-transform.hpp
 * @author Juho Röyskö
 * @brief Header file for move-to-front-transform.cpp
 * @version 0.1
 * @date 2021-09-17
 */
#pragma once
#include <string>
#include <vector>

std::vector<int> MTFTEncode(std::string input);
std::string MTFTDecode(std::vector<int> input);
