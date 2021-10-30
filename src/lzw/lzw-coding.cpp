/**
 * @file lzw-coding.cpp
 * @author Juho Röyskö
 * @brief LZW Coding
 * @version 0.4.0
 * @date 2021-10-30
 */
#include <string>
#include <unordered_map>
#include <vector>
#include "../constants.hpp"
#include "../file-manager.hpp"

/**
 * @brief Encode data with LZW coding
 *
 * @param data Data to encode
 * @return std::vector<int> Encoded data
 */
std::vector<int> LZWEncode(std::string const &data)
{
    std::unordered_map<std::string, int> codes; // The codebook
    for (int i = 0; i < 256; ++i)
    {
        std::string chr = "";
        chr += (char)i;
        codes[chr] = i;
    }

    int current_code = 256;
    std::vector<int> encoded_data;
    std::string old_string = "";
    std::string new_string = "";
    for (char c : data)
    {
        new_string += c;
        if (codes.find(new_string) == codes.end())
        {
            encoded_data.push_back(codes[old_string]);
            codes[new_string] = current_code;
            ++current_code;
            new_string = c;
        }
        old_string = new_string;
    }
    if (new_string != "")
        encoded_data.push_back(codes[new_string]);

    return encoded_data;
}

/**
 * @brief Decode data that has been encoded with LZW coding
 *
 * @param encoded_data Data to decode
 * @return std::string Decoded data
 */
std::string LZWDecode(std::vector<int> const &encoded_data)
{
    std::vector<std::string> codes; // The codebook. Vector is used instead of a unordered_map<int, string>
    for (int i = 0; i < 256; ++i)
    {
        std::string chr = "";
        chr += (char)i;
        codes.push_back(chr);
    }

    std::string decoded_data = "";

    int current_code = 256;
    for (int i = 0; i < (int)encoded_data.size(); ++i)
    {
        int code = encoded_data[i];
        if (i == (int)encoded_data.size() - 1)
        {
            decoded_data += codes[code];
            break;
        }

        int next_code = encoded_data[i + 1];
        if (next_code >= (int)codes.size())
            // Code is not in codebook
            codes.push_back(codes[code] + codes[code][0]);
        else
            // Code is in codebook
            codes.push_back(codes[code] + codes[next_code][0]);

        ++current_code;
        decoded_data += codes[code];
    }

    return decoded_data;
}