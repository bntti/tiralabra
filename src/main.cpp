/**
 * @file main.cpp
 * @author Juho Röyskö
 * @brief Reads arguments and runs the program
 * @version 0.2
 * @date 2021-09-22
 */
#include <iostream>
#include "huffman-runner.hpp"

/**
 * @brief Converts string to lowercase
 * 
 * @param input String to convert
 */
void ToLower(std::string &input)
{
    for (char &c : input)
        c = tolower(c);
}

/**
 * @brief Reads arguments and runs the program
 * 
 * @param argc Amount of arguments
 * @param argv Arguments
 * @return int Return code
 */
int main(int argc, char **argv)
{
    // Argument values
    std::string input_file = "";
    bool compress = 1;
    bool verbose = 0;
    bool help = 0;

    // Read arguments
    for (int i = 1; i < argc; ++i)
    {
        std::string argument = argv[i];
        if (argument.length() > 1 && argument[0] == '-' && argument[1] != '-')
        {
            ToLower(argument);
            for (int j = 1; j < (int)argument.length(); ++j)
            {
                if (argument[j] == 'c')
                    compress = 1;
                if (argument[j] == 'd')
                    compress = 0;
                if (argument[j] == 'v')
                    verbose = 1;
                if (argument[j] == 'h')
                    help = 1;
            }
        }
        else if (argument.length() > 1 && argument[0] == '-' && argument[1] == '-')
        {
            argument = argument.substr(2, argument.length() - 2);
            ToLower(argument);
            if (argument == "compress")
                compress = 1;
            if (argument == "decompress")
                compress = 0;
            if (argument == "verbose")
                verbose = 1;
            if (argument == "help")
                help = 1;
        }
        else
            input_file = argument;
    }

    if (input_file == "" || help)
    {
        std::cout << "Usage:\n$ " << argv[0] << " <flags> <file>\n";
        std::cout << '\n';
        std::cout << "Arguments:\n";
        std::cout << "\t-c, --compress | Compress selected file\n";
        std::cout << "\t-d, --decompress | Decompress selected file\n";
        std::cout << "\t-v, --verbose | Print what program is doing\n";
        std::cout << "\t-h, --help | Print this message\n";
        return 0;
    }

    if (compress)
        HuffmanCompress(input_file, verbose);
    else
        HuffmanDecompress(input_file, verbose);
}