
#include "handle_article.h"

void get_frequency_and_char(vector<int> &get_frequency, vector<char> &get_char) {
 ifstream inputFile(R"(D:\CLionProjects\huffman_compress\article)");
    if (!inputFile.is_open()) {
        cout << "Error opening file" << endl;
        exit(1);
    }


    char c;
    while (inputFile.get(c)) {
        if (c == '\n' || c == '\r' || c == '\t' ) {
            continue;
        }
        auto it = find(get_char.begin(), get_char.end(), c);
        if (it == get_char.end()) {// not found
            get_char.push_back(c);
            get_frequency.push_back(1);
        } else {
            int index = distance(get_char.begin(), it);
            get_frequency[index]++;
        }
    }
    inputFile.close();
}

void generate_compressed_file(HuffmanTree &huffman_tree) {
    ifstream inputFile(R"(D:\CLionProjects\huffman_compress\article)", ios::binary);
    ofstream outputFile(R"(D:\CLionProjects\huffman_compress\compressed_article)", ios::binary);

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cout << "Error opening file" << endl;
        exit(1);
    }
    huffman_tree.buildHuffmanCodes();

    char c;
    string buffer; // Buffer to hold bits

    while (inputFile.get(c)) {
        if (c == '\n' || c == '\r' || c == '\t' ) {
            continue;
        }
        string code = huffman_tree.get_huffman_code(c);

        for (char bit : code) {
            buffer += bit;

            if (buffer.size() == 8) {
                char byte = static_cast<char>(bitset<8>(buffer).to_ulong());
                outputFile.put(byte);
                buffer.clear();
            }
        }
    }

    // Write the remaining bits in the buffer, if any
    if (!buffer.empty()) {
        buffer.append(8 - buffer.size(), '0');
        char byte = static_cast<char>(bitset<8>(buffer).to_ulong());
        outputFile.put(byte);
    }

    inputFile.close();
    outputFile.close();
}

void compare_file_size() {
    ifstream inputFile(R"(D:\CLionProjects\huffman_compress\article)");
    ifstream compressedFile(R"(D:\CLionProjects\huffman_compress\compressed_article)");

    inputFile.seekg(0, std::ios::end);
    streampos fileSize = inputFile.tellg();
    cout << "File size: " << fileSize << " bytes before compressed" << std::endl;

    compressedFile.seekg(0, std::ios::end);
    streampos compressedFileSize = compressedFile.tellg();
    cout << "File size: " << compressedFileSize << " bytes after compressed" << std::endl;
    cout << "Compressed rate: " << (double) compressedFileSize / fileSize * 100 << "%" << std::endl;
}

void decompress_file(HuffmanTree &huffman_tree) {
    ifstream inputFile(R"(D:\CLionProjects\huffman_compress\compressed_article)", ios::binary);
    ofstream outputFile(R"(D:\CLionProjects\huffman_compress\decompressed_article)");

    if (!inputFile.is_open() || !outputFile.is_open()) {
        cout << "Error opening file" << endl;
        exit(1);
    }

    char c;
    string buffer; // Buffer to hold bits
    HBinNode* current = huffman_tree.getRoot();

    while (inputFile.get(c)) {
        buffer = bitset<8>(static_cast<unsigned char>(c)).to_string();

        for (char bit : buffer) {
            if (bit == '0') {
                current = current->left;
            } else {
                current = current->right;
            }

            if (current->left == nullptr && current->right == nullptr) {
                outputFile<<current->data;
                current = huffman_tree.getRoot();
            }
        }
    }

    inputFile.close();
    outputFile.close();
}
