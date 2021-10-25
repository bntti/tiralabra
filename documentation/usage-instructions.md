# Usage instructions

## Dependencies
 - g++
 - make
#### Optional dependencies
 - catch2 (for running tests)
 - doxygen (for generating documentation)
 - cppcheck (for code analysis)

## Usage
| Command        | Description                                                                       |
| -------------- | --------------------------------------------------------------------------------- |
| `make`         | Compiles program                                                                  |
| `make test`    | Compile and run tests                                                             |
| `make analyze` | Runs code analysis                                                                |
| `make check`   | Same as `make analyze && make test`                                               |
| `doxygen`      | Generate documentation (also available [here](https://bntti.github.io/tiralabra)) |

#### Running program
```
$ ./bnzip <args> <file>
```
| Argument             | Description                           |
| -------------------- | ------------------------------------- |
| `-c`, `--compress`   | Compress given file                   |
| `-d`, `--decompress` | Decompress given file                 |
| `-h`, `--help`       | Show usage instructions and arguments |
| `-l`, `--lzw`        | Use LZW to compress                   |
| `-v`, `--verbose`    | Print what program is doing           |

If no compression or decompression arguments are given, then the program decompresses the file if the filename name ends with `.bnzip` and otherwise compresses it.  
When compressing and `-l` or `--lzw` argument is not provided, Huffman coding is used to compress the file.  
When decompressing, it is not necessary to provide `-l` or `--lzw` argument, because the file contains information about what it was compressed with.
