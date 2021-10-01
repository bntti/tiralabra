/**
 * @file file-manager.cpp
 * @author Juho Röyskö
 * @brief File management utilities
 * @version 0.3
 * @date 2021-10-01
 */
#include <string>
#include <sstream>
#include <fstream>

/**
 * @brief Removes .bnzip extensions from files
 * 
 * @param filename Filename to remove .bnzip extensions from
 */
void RemoveExtension(std::string &filename)
{
    while (filename.length() >= 6 && filename.substr(filename.length() - 6, 6) == ".bnzip")
        filename = filename.substr(0, filename.length() - 6);
}

/**
 * @brief Read file into a single string
 * 
 * @param input_file File to read
 * @return std::string File content
 */
std::string ReadFile(std::string input_file)
{
    std::ifstream in_file;
    in_file.open(input_file);

    std::stringstream str_stream;
    str_stream << in_file.rdbuf();
    std::string str = str_stream.str();

    return str;
}

/**
 * @brief Checks if file exists
 * 
 * @param filename Filename of the file to check
 * @return true If file exists
 * @return false otherwise
 */
bool FileExists(std::string filename)
{
    std::ifstream f(filename.c_str());
    return f.good();
}

/**
 * @brief If file is compressed. Determined by checking if filename ends with .bnzip
 * 
 * @param filename File to check
 * @return true If file is compressed
 * @return false Otherwise
 */
bool IsCompressed(std::string filename)
{
    return filename.length() >= 6 && filename.substr(filename.length() - 6, 6) == ".bnzip";
}

/**
 * @brief Returns first byte of file
 * 
 * @param filename File to get first byte from
 * @return int First byte of file
 */
int FirstByte(std::string filename)
{
    std::ifstream f(filename, std::ios::binary | std::ios::in);
    char c;
    if (f.get(c))
    {
        return c;
    }
    return 0;
}

/**
 * @brief Remove leading path to file
 * 
 * @param file_path File path to remove leading path from
 */
void RemovePath(std::string &file_path)
{
    for (int i = file_path.length() - 1; i >= 0; --i)
    {
        if (file_path[i] == '/')
        {
            file_path = file_path.substr(i + 1, file_path.length() - i - 1);
            return;
        }
    }
}
