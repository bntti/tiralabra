# Testing document
[![codecov](https://codecov.io/gh/bntti/tiralabra/branch/main/graph/badge.svg?token=UUM7HC26G1)](https://codecov.io/gh/bntti/tiralabra)

The tests check that:
- The file-manager.cpp works
- The compressed file is smaller than the original file.
- The decompressed file is identical to the original file.
- Compression and decompression work with the verbose argument set to true.

The tests are run with test input files containing miscellenious data.  
Tests can be replicated by running `make test`.