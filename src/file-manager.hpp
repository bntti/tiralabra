/**
 * @file file-manager.hpp
 * @author Juho Röyskö
 * @brief Header file for file-manager.cpp
 * @version 0.3
 * @date 2021-10-01
 */
#include <string>
#include <fstream>

void RemoveExtension(std::string &filename);
std::string ReadFile(std::string input_file);
bool FileExists(std::string filename);
bool IsCompressed(std::string filename);
int FirstByte(std::string filename);
void RemovePath(std::string &file_path);

/**
 * @brief Writes (binary) data into a file
 */
struct FileWriter
{
    std::ofstream out;
    int currbyte = 0;
    int bitcount = 0;

    /**
     * @brief Construct a new File Writer object
     * 
     * @param output_file File to write data to
     */
    explicit FileWriter(std::string output_file)
    {
        out.open(output_file, std::ios::binary | std::ios::out);
    }

    /**
     * @brief Write binary string as binary into file
     * 
     * @param data Binary string that will be written to file
     */
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

    /**
     * @brief Write b bits from int to file
     * 
     * @param data Int to write bits from
     * @param b Amount of bits to write
     */
    void Write(int data, int b)
    {
        std::string bindata = "";
        for (int i = b - 1; i >= 0; --i)
        {
            if ((data & (1 << i)))
                bindata += '1';
            else
                bindata += '0';
        }
        BinaryWrite(bindata);
    }

    /**
     * @brief Write bits of character into file
     * 
     * @param data Character from which to write bits from
     */
    void Write(char data)
    {
        Write(data, 8);
    }

    /**
     * @brief Write string into file
     * 
     * @param data String that will be written to the file
     */
    void Write(std::string const &data)
    {
        out << data;
    }

    /**
     * @brief Pad the end of the file so that we can write all necessary bits
     * 
     * @param pad_data Data to pad with
     */
    void Pad(std::string pad_data)
    {
        if (bitcount > 0)
        {
            BinaryWrite(pad_data.substr(0, 8 - bitcount));
        }
    }

    /**
     * @brief Close file
     */
    void Close()
    {
        out.close();
    }
};
