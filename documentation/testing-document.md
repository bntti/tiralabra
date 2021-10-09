# Testing document
[![codecov](https://codecov.io/gh/bntti/tiralabra/branch/main/graph/badge.svg?token=UUM7HC26G1)](https://codecov.io/gh/bntti/tiralabra)

The tests check that:
- The file-manager.cpp works
- Compressed files are smaller than the original files.
- Decompressed files are identical to the original files.
- Compression and decompression both work with the verbose argument set to true.

The tests are run with test input files containing miscellenious data.  
Tests can be replicated by running `make test`.  
Empirical testing data available [here](./Implementation-document.md).