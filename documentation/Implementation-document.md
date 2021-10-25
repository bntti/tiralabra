# Implementation document

### Project structure
<details>
<summary>Show project structure</summary>

```
├── documentation
│   ├── definition-document.md
│   ├── Implementation-document.md
│   ├── testing-document.md
│   ├── usage-instructions.md
│   ├── week-report-1.md
│   ├── week-report-2.md
│   ├── week-report-3.md
│   ├── week-report-4.md
│   ├── week-report-5.md
│   └── week-report-6.md
├── Doxyfile
├── get-code-cov.sh
├── Makefile
├── README.md
├── src
│   ├── constants.hpp
│   ├── file-manager.cpp
│   ├── file-manager.hpp
│   ├── huffman
│   │   ├── huffman-coding.cpp
│   │   ├── huffman-coding.hpp
│   │   ├── huffman-runner.cpp
│   │   └── huffman-runner.hpp
│   ├── lzw
│   │   ├── lzw-coding.cpp
│   │   ├── lzw-coding.hpp
│   │   ├── lzw-runner.cpp
│   │   └── lzw-runner.hpp
│   ├── main.cpp
│   └── Makefile
└── tests
    ├── file-manager-test.cpp
    ├── helper.cpp
    ├── helper.hpp
    ├── huffman-test.cpp
    ├── lzw-test.cpp
    ├── Makefile
    └── test-files
        ├── all-characters.txt
        ├── plaintext.txt
        ├── random-binary-data.bin
        ├── random-plaintext.txt
        └── special-characters.txt
```
</details>

### Huffman coding
Creates the Huffman coding codebook and converts it to Canonical Huffman code.

### Lempel–Ziv–Welch (LZW)
Todo

### Time and memory complexity

A = Alphabet size used in the Huffman coding
|                       | Time complexity | Memory complexity |
| --------------------- | --------------- | ----------------- |
| Huffman compression   | O(n+A²)         | O(n+A²)           |
| Huffman decompression | O(n+A²)         | O(n+A²)           |
| LZW compression       | O(n)            | O(n)              |
| LZW decompression     | O(n)            | O(n)              |


### Comparison

| file                                                             | original size | `./bnzip`     | `./bnzip -l` | `bzip2`      | `xz`         | `gzip`       |
| ---------------------------------------------------------------- | ------------- | ------------- | ------------ | ------------ | ------------ | ------------ |
| [Plain text](../tests/test-files/plaintext.txt)                  | 8000          | 2889 (36.1%)  | 556 (6.95%)  | 66 (0.83%)   | 120 (1.5%)   | 99 (1.24%)   |
| [Random plaintext](../tests/test-files/random-plaintext.txt)     | 12507         | 7008 (56.0%)  | 7847 (62.7%) | 5667 (45.3%) | 6240 (49.9%) | 6311 (50.5%) |
| [Special characters](../tests/test-files/special-characters.txt) | 13853         | 11754 (84.8%) | 3935 (28.4%) | 710 (5.13%)  | 412 (2.97%)  | 468 (3.38%)  |
| [All characters](../tests/test-files/all-characters.txt)         | 11520         | 9381 (81.4%)  | 6049 (52.5%) | 868 (7.53%)  | 396 (3.44%)  | 465 (4.04%)  |
| [Random binary data](../tests/test-files/random-binary-data.bin) | 10552         | 8532 (80.9%)  | 10365(98.2%) | 7555 (71.6%) | 7396 (70.1%) | 8607 (81.6%) |


### Possible improvements
todo