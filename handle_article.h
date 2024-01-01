#ifndef HUFFMAN_COMPRESS_HANDLE_ARTICLE_H
#define HUFFMAN_COMPRESS_HANDLE_ARTICLE_H
#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <bitset>
#include "huffman.h"

using namespace std;
void get_frequency_and_char(vector<int> &get_frequency,vector<char> &get_char);
void generate_compressed_file(HuffmanTree &huffman_tree);
void decompress_file(HuffmanTree &huffman_tree);
void compare_file_size();
#endif //HUFFMAN_COMPRESS_HANDLE_ARTICLE_H
