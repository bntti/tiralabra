/**
 * @file lzw-coding.cpp
 * @author Juho Röyskö
 * @brief LZW Coding
 * @version 0.3.0
 * @date 2021-10-02
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
    std::unordered_map<std::string, int> codebook;
    for (int i = 0; i < 256; ++i)
    {
        std::string chr = "";
        chr += (char)i;
        codebook[chr] = i;
    }

    int current_code = 256;
    std::vector<int> output;
    std::string old_string = "";
    std::string new_string = "";
    for (char c : data)
    {
        new_string = old_string + c;
        if (codebook.find(new_string) == codebook.end())
        {
            output.push_back(codebook[old_string]);
            codebook[new_string] = current_code;
            ++current_code;
            new_string = c;
        }
        old_string = new_string;
    }
    if (new_string != "")
        output.push_back(codebook[new_string]);

    return output;
}

/**
 * @brief Decode data that has been encoded with LZW coding
 *
 * @param codes Data to decode
 * @return std::string Decoded data
 */
std::string LZWDecode(std::vector<int> const &codes)
{
    std::vector<std::string> codebook; // Vector is used instead of a unordered_map<int, string>
    for (int i = 0; i < 256; ++i)
    {
        std::string chr = "";
        chr += (char)i;
        codebook.push_back(chr);
    }

    std::string output = "";

    int current_code = 256;
    for (int i = 0; i < (int)codes.size(); ++i)
    {
        int code = codes[i];
        if (i == (int)codes.size() - 1)
        {
            output += codebook[code];
            break;
        }

        int next_code = codes[i + 1];
        if (next_code >= (int)codebook.size())
            codebook.push_back(codebook[code] + codebook[code][0]);
        else
            codebook.push_back(codebook[code] + codebook[next_code][0]);

        ++current_code;
        output += codebook[code];
    }

    return output;
}