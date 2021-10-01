/**
 * @file file-manager.cpp
 * @author Juho Röyskö
 * @brief File management utilities
 * @version 0.1
 * @date 2021-10-01
 */
#include <string>
#include <sstream>
#include <fstream>

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
