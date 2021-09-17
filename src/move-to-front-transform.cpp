/**
 * @file move-to-front-transform.cpp
 * @author Juho Röyskö
 * @brief Move-to-front transform
 * @version 0.1
 * @date 2021-09-17
 */
#include <vector>
#include <string>

const int ALPHABET_SIZE = 128;

/**
 * @brief Encode string in O(n)
 * 
 * @param input String to encode
 * @return std::vector<int> Encoded vector
 */
std::vector<int> MTFTEncode(std::string input)
{
    // Init
    std::vector<int> arr, pos;
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        arr.push_back(i);
        pos.push_back(i);
    }

    // Encode
    std::vector<int> encoded;
    for (char c : input)
    {
        encoded.push_back(pos[(int)c]);
        for (int i = pos[(int)c]; i > 0; --i)
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
std::string MTFTDecode(std::vector<int> input)
{
    // Init
    std::vector<int> arr;
    for (int i = 0; i < ALPHABET_SIZE; ++i)
        arr.push_back(i);

    // Decode
    std::string decoded;
    for (int val : input)
    {
        decoded += arr[val];
        for (int i = val; i > 0; --i)
            std::swap(arr[i], arr[i - 1]);
    }
    return decoded;
}