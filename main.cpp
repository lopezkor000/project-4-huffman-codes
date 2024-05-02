#include <iostream>
#include <fstream>
#include <map>
#include <queue>
#include <string>

using namespace std;

struct character {
    char element;
    int freq;
    character* lptr = NULL;
    character* rptr = NULL;
};

class myComparator { 
public: 
    int operator() (const character p1, const character p2) { 
        return p1.freq > p2.freq; 
    } 
};

map<char, character> freqCounts;
priority_queue<character, vector<character>, myComparator> L;
map<string, char> codes;

void gatherFrequencies() {
    ifstream data("message.txt");

    char c;
    character temp;
    while(data.get(c)) {
        if (freqCounts.find(c) != freqCounts.end()){
            freqCounts[c].freq++;
        }
        else {
            temp = {c, 1, NULL, NULL};
            freqCounts.insert({c, temp});
        }
    }
}

void sortFrequencies() {
    for (auto key : freqCounts) {
        L.push(key.second);
    }
}

void combineNodes() {
    character Nleft;
    character Nright;

    Nleft = L.top();
    L.pop();
    Nright = L.top();
    L.pop();

    int newFreq = Nleft.freq + Nright.freq;
    character N = {'~', newFreq, &Nleft, &Nright};
    L.push(N);
}

void makeHuffmanTree() {
    while(L.size() > 1) {
        combineNodes();
    }
}

void traverseHuffmanTree(const character* node, string binCode = "") {
    cout << "Node: " << node->element << endl;
    if(node->lptr == NULL && node->rptr == NULL) {
        cout << "Code: " << binCode << endl;
        codes.insert({binCode, node->element});
    }
    cout << "---checking left---" << endl;
    if(node->lptr != NULL) {
        traverseHuffmanTree(node->lptr, binCode+"0");
    }
    cout << "---checking right---" << endl;
    if(node->rptr != NULL) {
        traverseHuffmanTree(node->lptr, binCode+"1");
    }
}

int main() {
    gatherFrequencies();
    sortFrequencies();
    makeHuffmanTree();
    const character root = L.top();
    traverseHuffmanTree(&root);
    for (auto key : codes) {
        cout << key.first << "\t" << key.second << endl;
    }

    return 1;
}