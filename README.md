# Tiralabra: Data compression
[![Build Status](https://app.travis-ci.com/bntti/tiralabra.svg?branch=main)](https://app.travis-ci.com/bntti/tiralabra)
[![codecov](https://codecov.io/gh/bntti/tiralabra/branch/main/graph/badge.svg?token=UUM7HC26G1)](https://codecov.io/gh/bntti/tiralabra)

## Dependencies
 - catch2
#### Optional dependencies
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

## Documents
#### Week reports
- [Week report 1](./documentation/week-report-1.md)
- [Week report 2](./documentation/week-report-2.md)
- [Week report 3](./documentation/week-report-3.md)

#### Other documents
- [Definition document](./documentation/definition-document.md)
- [Testing document](./documentation/testing-document.md)
