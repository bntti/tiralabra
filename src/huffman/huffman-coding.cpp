/**
 * @file huffman-coding.cpp
 * @author Juho Röyskö
 * @brief Huffman coding
 * @version 0.1.2
 * @date 2021-10-02
 */
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include "../constants.hpp"

/**
 * @brief Node in binary tree used to create Huffman coding
 */
struct Node
{
    long long weight; // Amount of occurences of character / sum of weights in subtree
    bool has_val;
    uint8_t val;
    int left, right;
    Node()
    {
        weight = 0;
        has_val = 0;
        val = 0;
        left = -1;
        right = -1;
    }
    Node(long long _weight, uint8_t _val)
    {
        weight = _weight;
        val = _val;
        has_val = 1;
        left = -1;
        right = -1;
    }
    Node(int _left, int _right, int _weight)
    {
        weight = _weight;
        val = 0;
        has_val = 0;
        left = _left;
        right = _right;
    }
};

Node nodes[ALPHABET_SIZE * 2]; // Nodes are stored in a global array to prevent dealing with pointers
std::string codes[ALPHABET_SIZE];
long long amt[ALPHABET_SIZE];

/**
 * @brief Clear global variables
 */
void Init()
{
    std::fill_n(nodes, ALPHABET_SIZE * 2, Node());
    std::fill_n(codes, ALPHABET_SIZE, "");
    std::fill_n(amt, ALPHABET_SIZE, 0);
}

/**
 * @brief Compare Nodes. Return is flipped because priority_queue sorts in reverse
 */
struct CompareWeight
{
    /**
     * @brief Compare Nodes. Return is flipped because priority_queue sorts in reverse
     *
     * @param node_index_1 Node 1
     * @param node_index_2 Node 2
     * @return true If first Node has bigger weight
     * @return false Otherwise
     */
    bool operator()(int node_index_1, int node_index_2)
    {
        return nodes[node_index_1].weight > nodes[node_index_2].weight;
    }
};

/**
 * @brief Get codes for characters using depth first search
 *
 * @param nodeindex Current node
 * @param code Current code
 */
void GetCodes(int nodeindex, std::string &code)
{
    Node node = nodes[nodeindex];
    if (node.has_val)
    {
        codes[node.val] = code;
    }
    else
    {
        if (node.left != -1)
        {
            code += '0';
            GetCodes(node.left, code);
            code.pop_back();
        }
        if (node.right != -1)
        {
            code += '1';
            GetCodes(node.right, code);
            code.pop_back();
        }
    }
}

/**
 * @brief Increment binary string by one
 *
 * @param binary_string Binary string to increment
 */
void IncrementBinaryString(std::string &binary_string)
{
    int len = binary_string.length();
    for (int i = len - 1; i >= 0; --i)
    {
        if (binary_string[i] == '0')
        {
            binary_string[i] = '1';
            return;
        }
        binary_string[i] = '0';
    }
}

/**
 * @brief Set the codes for characters using the Canonical Huffman code
 *
 * @param v Vector containing pairs of {lengths of code, character}
 */
void SetCodes(std::vector<std::pair<uint8_t, uint8_t>> &v)
{
    std::sort(v.begin(), v.end());

    // Get and set first code
    std::string code = "";
    for (int i = 0; i < v[0].first; ++i)
        code += '0';
    codes[v[0].second] = code;

    // Get and set other codes
    for (int i = 1; i < (int)v.size(); ++i)
    {
        IncrementBinaryString(code);
        while ((int)code.length() < v[i].first)
            code += '0';
        codes[v[i].second] = code;
    }
}

/**
 * @brief Convert codes to Canonical Huffman codes
 */
void ConvertCodes()
{
    std::vector<std::pair<uint8_t, uint8_t>> v;
    for (int i = 0; i < ALPHABET_SIZE; ++i)
        v.push_back({codes[i].length(), i});
    SetCodes(v);
}

/**
 * @brief Create Huffman encoding codebook
 *
 * @param input String to create codebook from
 * @return std::string* Codebook of length 256
 */
std::string *HCEncode(std::string const &input)
{
    Init();

    for (char c : input)
        ++amt[(uint8_t)c];

    // Add characters as Nodes to the priority queue
    // We add the characters that don't appear in the input with weight 0,
    // because we need a code that is at least 8 bits long,
    // so that we can pad the end of the compressed file
    int node_array_size = 0;
    std::priority_queue<int, std::vector<int>, CompareWeight> q; // Priority queue containing indexes of nodes
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        nodes[node_array_size] = Node(amt[i], i);
        q.push(node_array_size);
        ++node_array_size;
    }

    // Create tree from nodes. Combine two lightest nodes and create a Node as their parent and replace them with their parent
    while (q.size() > 1)
    {
        int node_index_1 = q.top();
        q.pop();
        int node_index_2 = q.top();
        q.pop();

        nodes[node_array_size] = Node(node_index_1, node_index_2, nodes[node_index_1].weight + nodes[node_index_2].weight);
        q.push(node_array_size);
        ++node_array_size;
    }

    std::string current = "";
    GetCodes(q.top(), current);

    ConvertCodes();
    return codes;
}

/**
 * @brief Decode data that has been compressed with Huffman coding
 *
 * @param compressed_data Data to decompress
 * @return std::string Decompressed data
 */
std::string HCDecode(std::string const &compressed_data)
{
    Init();

    // Get the codes from the input
    std::vector<std::pair<uint8_t, uint8_t>> v;
    for (int i = 0; i < ALPHABET_SIZE; ++i)
        v.push_back({compressed_data[i], i});
    SetCodes(v);

    // Recreate the tree
    int node_index = 0;
    nodes[node_index] = Node();
    ++node_index;
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        int current_node = 0;
        for (char c : codes[i])
        {
            if (c == '0')
            {
                if (nodes[current_node].left == -1)
                {
                    nodes[node_index] = Node();
                    nodes[current_node].left = node_index;
                    ++node_index;
                }
                current_node = nodes[current_node].left;
            }
            else
            {
                if (nodes[current_node].right == -1)
                {
                    nodes[node_index] = Node();
                    nodes[current_node].right = node_index;
                    ++node_index;
                }
                current_node = nodes[current_node].right;
            }
        }
        nodes[current_node].has_val = 1;
        nodes[current_node].val = i;
    }

    // Decode input using the codes and the tree
    std::string output = "";
    int current_node = 0;
    for (int i = ALPHABET_SIZE; i < (int)compressed_data.length(); ++i)
    {
        uint8_t x = compressed_data[i];
        for (int k = 7; k >= 0; --k)
        {
            int bit = x & (1 << k);
            if (bit == 0)
                current_node = nodes[current_node].left;
            else
                current_node = nodes[current_node].right;

            if (nodes[current_node].has_val)
            {
                output += nodes[current_node].val;
                current_node = 0;
            }
        }
    }
    return output;
}