# Implementation document

### Huffman coding
Creates the Huffman coding codebook and converts it to Canonical Huffman code.

### Lempel–Ziv–Welch (LZW)
Todo

### Time and memory complexity

A = Alphabet size used in the Huffman coding
|                       | time complexity | memory complexity |
| --------------------- | --------------- | ----------------- |
| Huffman compression   | O(n+A²)         | O(n+A²)           |
| Huffman decompression | O(n+A²)         | O(n+A²)           |
| LZW compression       | O(n)            | O(n)              |
| LZW decompression     | O(n)            | O(n)              |

### Comparison
Todo