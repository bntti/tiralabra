/**
 * @file main.cpp
 * @author Juho Röyskö
 * @brief Reads arguments and runs the program
 * @version 0.4
 * @date 2021-10-02
 */
#include <iostream>
#include "huffman/huffman-runner.hpp"
#include "lzw/lzw-runner.hpp"
#include "file-manager.hpp"

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
int main(int argc, char const **argv)
{
    // Argument values
    std::string input_file = "";
    bool compress = 0;
    bool decompress = 0;
    bool verbose = 0;
    bool lzw = 0;
    bool help = 0;

    // Read arguments
    for (int i = 1; i < argc; ++i)
    {
        std::string argument = argv[i];
        if (argument.length() >= 2 && argument[0] == '-' && argument[1] != '-')
        {
            ToLower(argument);
            for (int j = 1; j < (int)argument.length(); ++j)
            {
                if (argument[j] == 'c')
                    compress = 1;
                else if (argument[j] == 'd')
                    decompress = 1;
                else if (argument[j] == 'h')
                    help = 1;
                else if (argument[j] == 'l')
                    lzw = 1;
                else if (argument[j] == 'v')
                    verbose = 1;
                else
                {
                    std::cout << "No such argument '-" << argument[j] << "'\n";
                    std::cout << "Run '" << argv[0] << " -h' for usage instructions\n";
                    return 1;
                }
            }
        }
        else if (argument.length() >= 2 && argument[0] == '-' && argument[1] == '-')
        {
            argument = argument.substr(2, argument.length() - 2);
            ToLower(argument);
            if (argument == "compress")
                compress = 1;
            else if (argument == "decompress")
                decompress = 1;
            else if (argument == "lzw")
                lzw = 1;
            else if (argument == "help")
                help = 1;
            else if (argument == "verbose")
                verbose = 1;
            else
            {
                std::cout << "No such argument '--" << argument << "'\n";
                std::cout << "Run '" << argv[0] << " -h' for usage instructions\n";
                return 1;
            }
        }
        else
            input_file = argument;
    }

    if (!help && input_file == "")
    {
        std::cout << "No input file provided\n";
        std::cout << "Run '" << argv[0] << " -h' for usage instructions\n";
        return 1;
    }

    if (help)
    {
        std::cout << "Usage:\n$ " << argv[0] << " <args> <file>\n";
        std::cout << R"rstring(
Arguments:
    -c, --compress | Compress selected file
    -d, --decompress | Decompress selected file
    -h, --help | Print this message
    -l, --lzw | Use LZW to compress
    -v, --verbose | Print what program is doing

If no compression or decompression arguments are given, then the program decompresses the file if the filename name ends with `.bnzip` and otherwise compresses it.
When compressing and `-l` or `--lzw` argument is not provided, Huffman coding is used to compress the file.
When decompressing, it is not necessary to provide `-l` or `--lzw` argument, because the file contains information about what it was compressed with.
)rstring";
        return 0;
    }

    if (!FileExists(input_file))
    {
        std::cout << "No such file '" << input_file << "'\n";
        return 1;
    }

    if (compress || (!decompress && !IsCompressed(input_file)))
    {
        if (lzw)
            LZWCompress(input_file, verbose);
        else
            HuffmanCompress(input_file, verbose);
    }
    else
    {
        if (FirstByte(input_file) == 1)
            LZWDecompress(input_file, verbose);
        else
            HuffmanDecompress(input_file, verbose);
    }
}
