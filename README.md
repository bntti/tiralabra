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
$ ./bnzip <flags> <file>
```
| Flag           | Description |
| -------------- | ----------- |
| `-t`, `--todo` | Todo        |

## Documents
#### Week reports
- [Week report 1](./documentation/week-report-1.md)
- [Week report 2](./documentation/week-report-2.md)

#### Other documents
- [Definition document](./documentation/definition-document.md)
