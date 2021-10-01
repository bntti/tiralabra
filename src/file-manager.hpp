/**
 * @file file-manager.hpp
 * @author Juho Röyskö
 * @brief Header file for file-manager.cpp
 * @version 0.2
 * @date 2021-10-01
 */
#include <string>
#include <fstream>

void RemoveExtension(std::string &filename);
std::string ReadFile(std::string input_file);
void RemovePath(std::string &file_path);

/**
 * @brief Writes binary data into a file
 */
struct FileWriter
{
    std::ofstream out;
    int currbyte = 0;
    int bitcount = 0;

    explicit FileWriter(std::string output_file)
    {
        out.open(output_file, std::ios::binary | std::ios::out);
    }

    void BinaryWrite(std::string data)
    {
        for (char c : data)
        {
            int bit = c == '1';
            currbyte = currbyte << 1 | bit;
            ++bitcount;
            if (bitcount == 8)
            {
                out.write((char *)&currbyte, 1);
                currbyte = 0;
                bitcount = 0;
            }
        }
    }

    void Write(char data)
    {
        out.write(&data, 1);
    }

    void Write(std::string const &data)
    {
        out << data;
    }

    void Pad(std::string pad_data)
    {
        if (bitcount > 0)
        {
            for (char c : pad_data)
            {
                int bit = c == '1';
                currbyte = currbyte << 1 | bit;
                ++bitcount;
                if (bitcount == 8)
                {
                    out.write((char *)&currbyte, 1);
                    return;
                }
            }
        }
    }

    void Close()
    {
        out.close();
    }
};
