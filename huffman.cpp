#include "huffman.h"

bool CompareNodes::operator()(HBinNode *a, HBinNode *b) {
    return a->frequency > b->frequency; // Min heap based on frequency
}

HBinNode::HBinNode(int fre, char Data, HBinNode *L, HBinNode *R, HBinNode *p)
        : frequency(fre), data(Data), left(L), right(R), parent(p) {}

void HuffmanTree::generateCodes(HBinNode *root, string code) {
    if (root->left == nullptr && root->right == nullptr) {
        huffmanCodes[root->data] = code;
        return;
    }
    if (root->left)
        generateCodes(root->left, code + "0");
    if (root->right)
        generateCodes(root->right, code + "1");
}

HuffmanTree::HuffmanTree(vector<int> frequencies, vector<char> characters) {
    for (size_t i = 0; i < frequencies.size(); ++i) {
        HBinNode* node = new HBinNode(frequencies[i], characters[i]);
        minHeap.push(node);
    }

    while (minHeap.size() > 1) {
        HBinNode* left = minHeap.top();
        minHeap.pop();
        HBinNode* right = minHeap.top();
        minHeap.pop();

        HBinNode* newNode = new HBinNode(left->frequency + right->frequency, '#', left, right);
        left->parent = newNode;
        right->parent = newNode;

        minHeap.push(newNode);
    }
    root = minHeap.top();
    minHeap.pop();
}

void HuffmanTree::buildHuffmanCodes() {
    generateCodes(root, "");
}

void HuffmanTree::printHuffmanCodes() {
    for (auto & huffmanCode : huffmanCodes) {
        cout << huffmanCode.first << ": " << huffmanCode.second << endl;
    }

}

int HuffmanTree::Height() {
    if (root == nullptr) {
        return 0;
    }
    int leftHeight = 0;
    int rightHeight = 0;
    HBinNode *current = root;
    while (current->left != nullptr) {
        leftHeight++;
        current = current->left;
    }
    current = root;
    while (current->right != nullptr) {
        rightHeight++;
        current = current->right;
    }
    return max(leftHeight, rightHeight);
}
void HuffmanTree::graph_frequency(ostream &out) {
    int height = this->Height();
    if (root == nullptr) {
        return;
    }
    vector<HBinNode *> nodes;
    vector<int> data;
    nodes.push_back(root);
    while (!nodes.empty()) {
        HBinNode *current = nodes.front();
        nodes.erase(nodes.begin());
        data.push_back(current->frequency);
        if (current->left != nullptr) {
            nodes.push_back(current->left);
        }
        if (current->right != nullptr) {
            nodes.push_back(current->right);
        }
    }//层次遍历

    int position = pow(2,height+1)/2;
    string space(pow(2.0,height+1),' ');
    string freq = to_string(data[0]);
    space.replace(position, freq.length(), freq);
    data.erase(data.begin());
    out<<space<<endl;//输出根结点

    for (int i = 1; i < height+1 ; ++i) {
        position/=2;
        string space(pow(2.0,height+1),' ');
        for (int j = 0; j <= pow(2,i)-1; ++j) {//每层的个数
            if (data.size() > 0) {
                freq = to_string(data[0]);
                space.replace(position + j * position * 2, freq.length(), freq);
                data.erase(data.begin());
            }
        }
        out<<space<<endl;
    }
}

void HuffmanTree::graph_char(ostream &out) {
    out<<"Additional node use '#' to represent"<<endl;
    int height = this->Height();
    if (root == nullptr) {
        return;
    }
    vector<HBinNode *> nodes;
    vector<char> data;
    nodes.push_back(root);
    while (!nodes.empty()) {
        HBinNode *current = nodes.front();
        nodes.erase(nodes.begin());
        data.push_back(current->data);
        if (current->left != nullptr) {
            nodes.push_back(current->left);
        }
        if (current->right != nullptr) {
            nodes.push_back(current->right);
        }
    }//层次遍历

    int position = pow(2,height+1)/2;
    string space(pow(2.0,height+1),' ');
    space.at(position) = data[0];
    data.erase(data.begin());
    out<<space<<endl;//输出根结点

    for (int i = 1; i < height+1 ; ++i) {
        position/=2;
        string space(pow(2.0,height+1),' ');
        for (int j = 0; j <= pow(2,i)-1; ++j) {//每层的个数
            if (data.size() > 0) {
                space.at(position+j*position*2) = data[0];
                data.erase(data.begin());
            }
        }
        out<<space<<endl;

    }
}

string HuffmanTree::get_huffman_code(char c) {
    return huffmanCodes[c];
}

HBinNode *HuffmanTree::getRoot() const {
    return root;
}
