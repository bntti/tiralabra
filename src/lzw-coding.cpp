/**
 * @file lzw-coding.cpp
 * @author Juho Röyskö
 * @brief LZW Coding
 * @version 0.1
 * @date 2021-10-01
 */
#include <string>
#include <unordered_map>
#include <vector>
#include "file-manager.hpp"

const int B = 11;
const int CODE_MAX = (1 << B) - 1;

/**
 * @brief Initialize map
 * 
 * @param mp Map to initialize
 */
void ClearMap(std::unordered_map<std::string, int> &mp)
{
    mp.clear();
    for (int i = 0; i < 256; ++i)
    {
        std::string chr = "";
        chr += (char)i;
        mp[chr] = i;
    }
}

/**
 * @brief Initialize map
 * 
 * @param mp Map to initialize
 */
void ClearMap(std::unordered_map<int, std::string> &mp)
{
    mp.clear();
    for (int i = 0; i < 256; ++i)
    {
        std::string chr = "";
        chr += (char)i;
        mp[i] = chr;
    }
}

/**
 * @brief Encode data with LZW coding
 * 
 * @param data Data to encode
 * @return std::vector<int> Encoded data
 */
std::vector<int> LZWEncode(std::string const &data)
{
    std::unordered_map<std::string, int> codebook;
    ClearMap(codebook);

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

            if (current_code == CODE_MAX)
            {
                current_code = 256;
                output.push_back(CODE_MAX);
                ClearMap(codebook);
            }
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
    std::unordered_map<int, std::string> codebook;
    ClearMap(codebook);

    std::string output = "";

    int current_code = 256;
    for (int i = 0; i < (int)codes.size(); ++i)
    {
        int code = codes[i];
        if (code == CODE_MAX)
        {
            current_code = 256;
            ClearMap(codebook);
            continue;
        }

        if (i == (int)codes.size() - 1)
        {
            output += codebook[code];
            break;
        }

        int next_code = codes[i + 1];
        if (codebook.find(next_code) == codebook.end())
            codebook[current_code] = codebook[code] + codebook[code][0];
        else
            codebook[current_code] = codebook[code] + codebook[next_code][0];

        ++current_code;
        output += codebook[code];
    }

    return output;
}