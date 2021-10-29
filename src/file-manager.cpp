/**
 * @file file-manager.cpp
 * @author Juho Röyskö
 * @brief File management utilities
 * @version 0.4.1
 * @date 2021-10-29
 */
#include <string>
#include <sstream>
#include <fstream>

/**
 * @brief Check if a filename ends with .bnzip
 *
 * @param filename Path to file to check
 * @return true If the filename ends with .bnzip
 * @return false Otherwise
 */
bool IsCompressed(std::string const &filename)
{
    return filename.length() >= 6 && filename.substr(filename.length() - 6, 6) == ".bnzip";
}

/**
 * @brief Removes .bnzip extensions from a filename
 *
 * @param filename Filename to remove .bnzip extensions from
 */
void RemoveExtension(std::string &filename)
{
    while (IsCompressed(filename))
        filename = filename.substr(0, filename.length() - 6);
}

/**
 * @brief Read contents of a file into a single string
 *
 * @param filename Path to the file to read
 * @return std::string File content
 */
std::string ReadFile(std::string const &filename)
{
    std::ifstream in;
    in.open(filename);

    std::stringstream str_stream;
    str_stream << in.rdbuf();
    std::string str = str_stream.str();

    return str;
}

/**
 * @brief Checks if a file exists
 *
 * @param filename Path to the file to check
 * @return true If the file exists
 * @return false otherwise
 */
bool FileExists(std::string const &filename)
{
    std::ifstream f(filename.c_str());
    return f.good();
}

/**
 * @brief Returns the first byte of a file
 *
 * @param filename Path to the file to get the first byte from
 * @return int First byte of the file
 */
int FirstByte(std::string const &filename)
{
    std::ifstream in(filename, std::ios::binary | std::ios::in);

    char c;
    if (in.get(c))
        return c;
    return 0;
}

/**
 * @brief Remove leading path to file
 *
 * @param file_path File path to remove the leading path from
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
