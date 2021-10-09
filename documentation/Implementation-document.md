# Implementation document

### Project structure
<details>
<summary>Show project structure</summary>

```
├── documentation
│   ├── definition-document.md
│   ├── Implementation-document.md
│   ├── testing-document.md
│   ├── week-report-1.md
│   ├── week-report-2.md
│   ├── week-report-3.md
│   ├── week-report-4.md
│   └── week-report-5.md
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
#### [Plain text](../tests/test-files/plaintext.txt) (Repetitive data)
| Command      | Original size | Compressed size | Ratio |
| ------------ | ------------- | --------------- | ----- |
| `./bnzip`    | 8000          | 2889            | 36.1% |
| `./bnzip -l` | 8000          | 556             | 6.95% |
| `bzip2`      | 8000          | 66              | 0.83% |
| `xz`         | 8000          | 120             | 1.5%  |
| `gzip`       | 8000          | 99              | 1.24% |

#### [Random plaintext](../tests/test-files/random-plaintext.txt) (Non-repetitive data)
| Command      | Original size | Compressed size | Ratio |
| ------------ | ------------- | --------------- | ----- |
| `./bnzip`    | 12507         | 7008            | 56.0% |
| `./bnzip -l` | 12507         | 7847            | 62.7% |
| `bzip2`      | 12507         | 5667            | 45.3% |
| `xz`         | 12507         | 6240            | 49.9% |
| `gzip`       | 12507         | 6311            | 50.5% |

#### [Special characters](../tests/test-files/special-characters.txt) (Repetitive data)
| Command      | Original size | Compressed size | Ratio |
| ------------ | ------------- | --------------- | ----- |
| `./bnzip`    | 13853         | 11754           | 84.8% |
| `./bnzip -l` | 13853         | 3935            | 28.4% |
| `bzip2`      | 13853         | 710             | 5.13% |
| `xz`         | 13853         | 412             | 2.97% |
| `gzip`       | 13853         | 468             | 3.38% |


#### [All characters](../tests/test-files/all-characters.txt) (Repetitive data)
| Command      | Original size | Compressed size | Ratio |
| ------------ | ------------- | --------------- | ----- |
| `./bnzip`    | 11520         | 9381            | 81.4% |
| `./bnzip -l` | 11520         | 6049            | 52.5% |
| `bzip2`      | 11520         | 868             | 7.53% |
| `xz`         | 11520         | 396             | 3.44% |
| `gzip`       | 11520         | 465             | 4.04% |


#### [Random binary data](../tests/test-files/random-binary-data.bin) (Non-repetitive data)
| Command      | Original size | Compressed size | Ratio |
| ------------ | ------------- | --------------- | ----- |
| `./bnzip`    | 10552         | 8532            | 80.9% |
| `./bnzip -l` | 10552         | 10365           | 98.2% |
| `bzip2`      | 10552         | 7555            | 71.6% |
| `xz`         | 10552         | 7396            | 70.1% |
| `gzip`       | 10552         | 8607            | 81.6% |

### Possible improvements
todo