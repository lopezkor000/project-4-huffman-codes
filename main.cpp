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

void gatherFrequencies(){
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

	data.close();

	// for (auto key : freqCounts) {
	//     cout << "Node: " << key.second->c << " | Count: " << key.second->element << endl;
	// }
}

void sortFrequencies(){
	for (auto key : freqCounts) {
		L.push(key.second);
	}

	// while (!L.empty()) {
	//     cout << "Node: " << L.top()->c << " | Count: " << L.top()->element << endl;
	//     L.pop();
	// }
}

void makeHuffmanTree(){
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

void getHuffmanCodes(binaryTreeNode<int>* node = huffmanTree.root, const string code = ""){
	if (node == NULL){
		return;
	}
	if (node == huffmanTree.root){
		getHuffmanCodes(node->left, code+"0");
		getHuffmanCodes(node->right, code+"1");
		return;
	}

	node->code += code;

	if (node->c != '~'){
		codes.insert({code, node->c});
	}

	getHuffmanCodes(node->left, code+"0");
	getHuffmanCodes(node->right, code+"1");
}

void showCodes(){
	ofstream codesFile("codes.txt");
	for (auto key : codes) {
		codesFile << "Character: " << key.second << " | Code: " << key.first << endl;
	}
}

void encode(){
	ofstream encoded("encoded.txt");
	ifstream message("message.txt");

	char c;
	while (message.get(c)){
		encoded << freqCounts[c]->code;
	}

	encoded.close();
	message.close();
}

void decode(){
	ofstream decoded("decoded.txt");
	ifstream encoded("encoded.txt");

	char c;
	string code;
	while (encoded.get(c)){
		code += c;
		if (codes[code] == '~'){
			continue;
		}
		decoded << codes[code];
		code = "";
	}

	encoded.close();
	decoded.close();
}

int main() {
	gatherFrequencies();
	sortFrequencies();
	makeHuffmanTree();
	getHuffmanCodes();

	showCodes();

	encode();
	decode();

	return 1;
}