/**
 * @file move-to-front-transform.cpp
 * @author Juho Röyskö
 * @brief Move-to-front transform
 * @version 0.2
 * @date 2021-09-20
 */
#include <vector>
#include <string>

const uint8_t ALPHABET_SIZE = 128;

/**
 * @brief Encode string in O(n)
 * 
 * @param input String to encode
 * @return std::vector<uint8_t> Encoded vector
 */
std::vector<uint8_t> MTFTEncode(std::string input)
{
    // Init
    std::vector<uint8_t> arr, pos;
    for (uint8_t i = 0; i < ALPHABET_SIZE; ++i)
    {
        arr.push_back(i);
        pos.push_back(i);
    }

    // Encode
    std::vector<uint8_t> encoded;
    for (char c : input)
    {
        encoded.push_back(pos[(uint8_t)c]);
        for (uint8_t i = pos[(uint8_t)c]; i > 0; --i)
        {
            std::swap(arr[i], arr[i - 1]);
            pos[arr[i]] = i;
            pos[arr[i - 1]] = i - 1;
        }
    }
    return encoded;
}

/**
 * @brief Decode string in O(n)
 * 
 * @param input Vector to decode
 * @return std::string Decoded string
 */
std::string MTFTDecode(std::vector<uint8_t> input)
{
    // Init
    std::vector<uint8_t> arr;
    for (uint8_t i = 0; i < ALPHABET_SIZE; ++i)
        arr.push_back(i);

    // Decode
    std::string decoded;
    for (uint8_t val : input)
    {
        decoded += arr[val];
        for (uint8_t i = val; i > 0; --i)
            std::swap(arr[i], arr[i - 1]);
    }
    return decoded;
}