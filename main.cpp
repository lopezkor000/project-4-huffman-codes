#include <iostream>
#include <fstream>
#include <map>
#include <queue>

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

void gatherFrequencies() {
    ifstream data("message.txt");

    char c;
    character temp;
    while(data >> c) {
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
        cout << key.first << " | " << key.second.freq << endl;
    }
}

// void combineNodes() {
//     character* Nleft;
//     character* Nright;

//     Nleft = L.top();
//     L.pop();
//     Nright = L.top();
//     L.pop();

//     int newFreq = Nleft->freq + Nright->freq;
//     cout << Nleft->freq << " | " << Nright->freq << endl;
//     character N = {'~', newFreq, Nleft, Nright};
//     character* Nptr = &N;
//     L.push(Nptr);

//     cout << N.element << " | " << N.freq << " | " << N.lptr->element << " | " << N.rptr->element << endl;
// }

// void makeHuffmanTree() {

// }

int main() {
    gatherFrequencies();
    sortFrequencies();
    // combineNodes();

    return 1;
}