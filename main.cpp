#include <iostream>
#include "handle_article.h"
#include "huffman.h"
using namespace std;
int main() {
    cout<<"Welcome to Huffman Compress System!"<<endl;
    int choice;
    vector<int> get_frequency;
    vector<char> get_char;
    get_frequency_and_char(get_frequency,get_char);
    HuffmanTree huffman_tree(get_frequency,get_char);

    do {
        cout << "1. Compress file\n";
        cout << "2. Decompress file\n";
        cout << "3. Compare file size\n";
        cout << "4. Print Huffman Tree by character\n";
        cout << "5. Print Huffman Tree by frequency\n";
        cout << "6. Print each character Huffman Codes\n";
        cout << "0. Quit\n";
        cout << "Please input your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                generate_compressed_file(huffman_tree);
                cout<<"Compress file successfully!"<<endl;
                break;
            case 2:
                decompress_file(huffman_tree);
                cout<<"Decompress file successfully!"<<endl;
                break;
            case 3:
                compare_file_size();
                break;
            case 4:
                huffman_tree.graph_char(cout);
                break;
            case 5:
                huffman_tree.graph_frequency(cout);
                break;
            case 6:
                huffman_tree.printHuffmanCodes();
            default:
                cout<<"Please input correct choice \n";
        }
    } while (choice!=0);



}
