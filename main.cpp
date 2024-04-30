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
    int operator() (const character& p1, const character& p2) { 
        return p1.freq > p2.freq; 
    } 
};

map<char, character> freqCounts;
priority_queue<character, vector<character>, myComparator> L;

void gatherFrequencies() {
    ifstream data("message.txt");

    char c;
    while(data >> c) {
        if (freqCounts.find(c) != freqCounts.end())
            freqCounts[c].freq++;
        else {
            character temp = {c, 1, NULL, NULL};
            freqCounts[c] = temp;
        }
    }
}

void sortFrequencies() {
    for (auto key : freqCounts)
        L.push(key.second);
}

int main() {
    gatherFrequencies();
    sortFrequencies();

    return 1;
}