/**
 * @file file-manager.hpp
 * @author Juho Röyskö
 * @brief Header file for file-manager.cpp. Also contains FileWriter struct
 * @version 0.4.1
 * @date 2021-10-29
 */
#include <string>
#include <fstream>

bool IsCompressed(std::string const &filename);
void RemoveExtension(std::string &filename);
std::string ReadFile(std::string const &filename);
bool FileExists(std::string const &filename);
int FirstByte(std::string const &filename);
void RemovePath(std::string &file_path);

/**
 * @brief Writes (binary) data into a file
 */
struct FileWriter
{
    std::ofstream out;
    std::string data_to_write = "";
    int current_byte = 0;
    int bit_count = 0;

    /**
     * @brief Construct a new File Writer object
     *
     * @param output_file Path to the file to write data to
     */
    explicit FileWriter(std::string const &output_file)
    {
        out.open(output_file, std::ios::binary | std::ios::out);
    }

    /**
     * @brief Write binary string as binary into the file
     *
     * @param data Binary string that will be written to the file
     */
    void BinaryWrite(std::string const &data)
    {
        for (char c : data)
        {
            int bit = c == '1';
            current_byte = (current_byte << 1) | bit;
            ++bit_count;
            if (bit_count == 8)
            {
                data_to_write += current_byte;
                current_byte = 0;
                bit_count = 0;
            }
        }
    }

    /**
     * @brief Write b least significant bits from a given integer to the file
     *
     * @param data Integer to write bits from
     * @param b Amount of least significant bits to write
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
     * @brief Write bits of character into the file
     *
     * @param data Character from which to write bits from
     */
    void Write(char data)
    {
        Write(data, 8);
    }

    /**
     * @brief Write string into the file
     *
     * @param data String that will be written to the file
     */
    void Write(std::string const &data)
    {
        data_to_write += data;
    }

    /**
     * @brief Pad the end of the file so that we can write all necessary bits
     *
     * @param pad_data Data to pad with
     */
    void Pad(std::string const &pad_data)
    {
        if (bit_count > 0)
        {
            BinaryWrite(pad_data.substr(0, 8 - bit_count));
        }
    }

    /**
     * @brief Close the file
     */
    void Close()
    {
        out << data_to_write;
        out.close();
    }
};
