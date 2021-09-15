#include <vector>
#include <string>

const int ALPHABET_SIZE = 128;

// Encode string in O(n)
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

// Decode string in O(n)
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