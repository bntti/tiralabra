# Tiralabra
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
| `-v`, `--verbose`    | Print what program is doing           |
| `-h`, `--help`       | Show usage instructions and arguments |

## Documents
#### Week reports
- [Week report 1](./documentation/week-report-1.md)
- [Week report 2](./documentation/week-report-2.md)
- [Week report 3](./documentation/week-report-3.md)

#### Other documents
- [Definition document](./documentation/definition-document.md)
- [Testing document](./documentation/testing-document.md)
