/**
 * @file huffman-coding.cpp
 * @author Juho Röyskö
 * @brief Huffman coding
 * @version 0.3.0
 * @date 2021-10-30
 */
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
#include <cassert>
#include "../constants.hpp"

std::string codes[ALPHABET_SIZE]; // The codebook
long long char_count[ALPHABET_SIZE];

/**
 * @brief Clear global variables
 */
void Init()
{
    std::fill_n(codes, ALPHABET_SIZE, "");
    std::fill_n(char_count, ALPHABET_SIZE, 0);
}

/**
 * @brief Node used in the binary tree used to create Huffman coding
 */
struct Node
{
    long long weight; // Amount of occurences of character / sum of weights in subtree
    bool has_val;
    uint8_t val;
    Node *left, *right;
    Node()
    {
        weight = 0;
        has_val = 0;
        val = 0;
        left = nullptr;
        right = nullptr;
    }
    Node(long long _weight, uint8_t _val)
    {
        weight = _weight;
        val = _val;
        has_val = 1;
        left = nullptr;
        right = nullptr;
    }
    Node(Node *_left, Node *_right)
    {
        weight = _left->weight + _right->weight;
        val = 0;
        has_val = 0;
        left = _left;
        right = _right;
    }
};

/**
 * @brief Delete nodes from memory by using depth-first search
 *
 * @param node Current node
 */
void DeleteNodes(Node *node)
{
    if (node->left != nullptr)
        DeleteNodes(node->left);
    if (node->right != nullptr)
        DeleteNodes(node->right);
    delete node;
}

/**
 * @brief Compare Nodes. Return is flipped because priority_queue sorts in reverse
 */
struct CompareWeight
{
    /**
     * @brief Compare Nodes. Return is flipped because priority_queue sorts in reverse
     *
     * @param node_1 Node 1
     * @param node_2 Node 2
     * @return true If first Node has bigger weight
     * @return false Otherwise
     */
    bool operator()(Node *node_1, Node *node_2)
    {
        return node_1->weight > node_2->weight;
    }
};

/**
 * @brief Get codes for characters using depth-first search
 *
 * @param node Current node
 * @param code Current code
 */
void GetCodes(Node *node, std::string &code)
{
    if (node->has_val)
    {
        codes[node->val] = code;
    }
    else
    {
        if (node->left != nullptr)
        {
            code += '0';
            GetCodes(node->left, code);
            code.pop_back();
        }
        if (node->right != nullptr)
        {
            code += '1';
            GetCodes(node->right, code);
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
 * @param v Vector containing pairs of {bit-length of code, character}
 */
void SetCodes(std::vector<std::pair<int, uint8_t>> &v)
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
    std::vector<std::pair<int, uint8_t>> v;
    for (int i = 0; i < ALPHABET_SIZE; ++i)
        v.push_back({codes[i].length(), i});
    SetCodes(v);
}

/**
 * @brief Create Huffman encoding codebook
 *
 * @param data Data to create codebook from
 * @return std::string* Codebook of length ALPHABET_SIZE
 */
std::string *HCCreateCodebook(std::string const &data)
{
    Init();

    for (uint8_t c : data)
        ++char_count[c];

    // Add characters as Nodes to the priority queue
    // We add the characters that don't appear in the input with weight 0,
    // because we need a code that is at least 8 bits long,
    // so that we can pad the end of the compressed file
    std::priority_queue<Node *, std::vector<Node *>, CompareWeight> nodes; // Priority queue containing nodes
    for (int i = 0; i < ALPHABET_SIZE; ++i)
        nodes.push(new Node(char_count[i], i));

    // Create a tree from the nodes. Combine two lightest nodes and create a Node as their parent and replace them with their parent
    while (nodes.size() > 1)
    {
        // Get two lightest nodes.
        Node *node_1 = nodes.top();
        nodes.pop();
        Node *node_2 = nodes.top();
        nodes.pop();

        // Create new node as their parent.
        Node *new_node = new Node(node_1, node_2);
        nodes.push(new_node);
    }

    // Get codes and convert them to Canonical Huffman codes
    std::string code = "";
    GetCodes(nodes.top(), code);
    ConvertCodes();

    DeleteNodes(nodes.top()); // Clear nodes from memory
    return codes;
}

/**
 * @brief Decode data that has been encoded with Huffman coding
 *
 * @param encoded_data Data to decode
 * @return std::string Decoded data
 */
std::string HCDecode(std::string const &encoded_data)
{
    Init();

    // Get the codes from the input
    std::vector<std::pair<int, uint8_t>> v;
    for (int i = 0; i < ALPHABET_SIZE; ++i)
        v.push_back({encoded_data[i], i});
    SetCodes(v);

    // Recreate the tree
    Node *start_node = new Node();
    for (int i = 0; i < ALPHABET_SIZE; ++i)
    {
        Node *current_node = start_node;
        for (uint8_t c : codes[i])
        {
            if (c == '0')
            {
                if (current_node->left == nullptr)
                    current_node->left = new Node();
                current_node = current_node->left;
            }
            else
            {
                if (current_node->right == nullptr)
                    current_node->right = new Node();
                current_node = current_node->right;
            }
        }
        current_node->has_val = 1;
        current_node->val = i;
    }

    // Decode input using the codes and the tree
    std::string decoded_data = "";
    Node *current_node = start_node;
    for (int i = ALPHABET_SIZE; i < (int)encoded_data.length(); ++i)
    {
        uint8_t x = encoded_data[i];
        for (int k = 7; k >= 0; --k)
        {
            int bit = x & (1 << k);
            if (bit == 0)
                current_node = current_node->left;
            else
                current_node = current_node->right;

            if (current_node->has_val)
            {
                decoded_data += current_node->val;
                current_node = start_node;
            }
        }
    }

    DeleteNodes(start_node); // Clear nodes from memory
    return decoded_data;
}