#ifndef HUFFMAN_COMPRESS_HUFFMAN_H
#define HUFFMAN_COMPRESS_HUFFMAN_H
#include <iostream>
#include <queue>
#include <vector>
#include <unordered_map>
#include <string>
#include <cmath>
using namespace std;
class HBinNode{
public:
    int frequency;
    char data;
    HBinNode* left;
    HBinNode* right;
    HBinNode* parent;
   explicit HBinNode(int fre, char Data = '\0', HBinNode* L = nullptr, HBinNode* R = nullptr,
                     HBinNode* p = nullptr);
};
class CompareNodes {
public:
    bool operator()(HBinNode* a, HBinNode* b);
};

class HuffmanTree {
private:
    priority_queue<HBinNode*, vector<HBinNode*>, CompareNodes> minHeap;
    unordered_map<char, string> huffmanCodes;
    HBinNode* root;
   void generateCodes(HBinNode* root, string code);
public:
    HBinNode *getRoot() const;
    HuffmanTree(vector<int> frequencies, vector<char> characters);
    void buildHuffmanCodes();
    void printHuffmanCodes();
    int Height();
    void graph_frequency(ostream& out);
    void graph_char(ostream& out);
    string get_huffman_code(char c);

};

#endif //HUFFMAN_COMPRESS_HUFFMAN_H
