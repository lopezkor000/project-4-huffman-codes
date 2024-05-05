#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <string>
#include "binaryTree.cpp"

using namespace std;

class myComparator { 
public: 
    int operator() (binaryTreeNode<int>* p1, binaryTreeNode<int>* p2) { 
        return p1->element > p2->element; 
    } 
};

map<char, binaryTreeNode<int>*> freqCounts;
priority_queue<binaryTreeNode<int>*, vector<binaryTreeNode<int>*>, myComparator> L;
map<string, char> codes;
binaryTree<int> huffmanTree;

void gatherFrequencies() {
    ifstream data("message.txt");

    char c;
    while(data.get(c)) {
        if (freqCounts.find(c) != freqCounts.end()){
            freqCounts[c]->element++;
        }
        else {
            binaryTreeNode<int>* node = new binaryTreeNode<int>(1, c, "", NULL, NULL);
            freqCounts.insert({c, node});
        }
    }

    // for (auto key : freqCounts) {
    //     cout << "Node: " << key.second->c << " | Count: " << key.second->element << endl;
    // }
}

void sortFrequencies() {
    for (auto key : freqCounts) {
        L.push(key.second);
    }

    // while (!L.empty()) {
    //     cout << "Node: " << L.top()->c << " | Count: " << L.top()->element << endl;
    //     L.pop();
    // }
}

void makeHuffmanTree() {
    while (L.size() > 1) {
        binaryTreeNode<int>* ptr1 = L.top();
        L.pop();
        binaryTreeNode<int>* ptr2 = L.top();
        L.pop();

        int newFreq = ptr1->element + ptr2->element;
        binaryTreeNode<int>* root = new binaryTreeNode<int>(newFreq, '~', "", ptr1, ptr2);

        L.push(root);
    }

    huffmanTree.root = L.top();

    // cout << L.size() << endl;
    // cout << "Node: " << L.top()->c << " | Count: " << L.top()->element << endl;
}

void getHuffmanCodes() {
    
}

int main() {
    gatherFrequencies();
    sortFrequencies();
    makeHuffmanTree();
    getHuffmanCodes();

    return 1;
}