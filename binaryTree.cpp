#include <iostream>
#include <string>
using namespace std;

template <class Type>
class binaryTree;

template <class Type>
class binaryTreeNode {
	public:
		friend class binaryTree<Type>;
		// constructor
		binaryTreeNode(const Type &value, char character, string huffmanCode, binaryTreeNode<Type> *lp, binaryTreeNode<Type> *rp)
			:element(value), c(character), code(huffmanCode), left(lp), right(rp){ };
		Type element;
		char c;
		string code;
		binaryTreeNode<Type> *left;
		binaryTreeNode<Type> *right;
};

template<class Type>
class binaryTree {
	public:
		explicit binaryTree();						// default constructor
		binaryTree(const binaryTree<Type> &rhs);	// copy constructor
		~binaryTree();								// destructor

		binaryTreeNode<Type> *findMin() const;
		binaryTreeNode<Type> *findMax() const;
		bool find(const Type &node) const;
		bool isEmpty();

		void destroyTree();
		void insert(const Type &node);
		void remove(const Type &node);

		// overload operator =
		const binaryTree &operator=(const binaryTree<Type> &rhs);

		void inOrderTraversal();
		void preOrderTraversal();
		void postOrderTraversal();

		int treeHeight();
		int treeNodeCount();
		int treeLeaveCount();

		binaryTreeNode<Type> *root;

	private:
		binaryTreeNode<Type> *copyTree(binaryTreeNode<Type> *&lt, binaryTreeNode<Type> *rhs);
		void destroyTree(binaryTreeNode<Type> *&p);
		// Manipulation
		void insert(binaryTreeNode<Type> *&p, const Type &x);
		void remove(binaryTreeNode<Type> *&p, const Type &x);
		// Traversal
		void inOrderTraversal(binaryTreeNode<Type> *p);
		void preOrderTraversal(binaryTreeNode<Type> *p);
		void postOrderTraversal(binaryTreeNode<Type> *p);
		// Tree info
		int treeHeight(binaryTreeNode<Type> *p);
		int treeNodeCount(binaryTreeNode<Type> *p);
		int treeLeaveCount(binaryTreeNode<Type> *p);
		binaryTreeNode<Type> *findMin(binaryTreeNode<Type> *p) const;
		binaryTreeNode<Type> *findMax(binaryTreeNode<Type> *p) const;
		bool find(const binaryTreeNode<Type> *p, const Type &x) const;
		// Etc methods
		int larger(int x, int y); 
};

// default constructor
template <class Type>
binaryTree<Type>::binaryTree() {
	root = NULL;
};

// copy constructor
template <class Type>
binaryTree<Type>::binaryTree(const binaryTree<Type> &rhs) {
	if (this != &rhs)
		root = copyTree(root, rhs.root);	// actual copy
};

// destructor
template<class Type>
binaryTree<Type>::~binaryTree() {
	destroyTree();
};

/*
=================================================
BASE CLASS DEFINITIONS (before generalized later)
=================================================
*/

template<class Type>
binaryTreeNode<Type> * binaryTree<Type>::findMin() const {
	return findMin(root);
};

template<class Type>
binaryTreeNode<Type> * binaryTree<Type>::findMax() const {
	return findMax(root);
};

template<class Type>
bool binaryTree<Type>::find(const Type &x) const {
	return find(root, x);
};

template<class Type>
bool binaryTree<Type>::isEmpty() {
	return root == NULL;
};

template<class Type>
void binaryTree<Type>::destroyTree() {
	destroyTree(root);
};

template<class Type>
void binaryTree<Type>::insert(const Type &x) {
	insert(root, x);
};

template<class Type>
void binaryTree<Type>::remove(const Type &x) {
	remove(root, x);
};

//overload operator =
template<class Type>
const binaryTree<Type> &binaryTree<Type>::operator=(const binaryTree<Type> &rhs) {
	if (this != &rhs)
		copyTree(root, rhs);	
	return this;
};

template<class Type>
void binaryTree<Type>::inOrderTraversal() {
	inOrderTraversal(root); 
};

template<class Type>
void binaryTree<Type>::preOrderTraversal() {
	preOrderTraversal(root); 
};

template<class Type>
void binaryTree<Type>::postOrderTraversal() {
	postOrderTraversal(root); 
};

template<class Type>
int binaryTree<Type>::treeHeight() {
	return treeHeight(root); 
};

template<class Type>
int binaryTree<Type>::treeNodeCount() {
	return treeNodeCount(root); 
};

template<class Type>
int binaryTree<Type>::treeLeaveCount() {
	return treeLeaveCount(root);
};

/*
=======================================
Generalized and Defined Class Functions
=======================================
*/

template<class Type>
binaryTreeNode<Type> *binaryTree<Type>::copyTree(binaryTreeNode<Type> *&lt, binaryTreeNode<Type> *rhs) {
	if (lt != NULL)
		destroy(lt);
	if (rhs == NULL)
		lt = NULL;
	else
		lt = new binaryTreeNode<Type>(rhs->value, copyTree(lt->left, rhs->left), copyTree(lt->right, rhs->right));	
	return lt;
};

template<class Type>	
void binaryTree<Type>::destroyTree(binaryTreeNode<Type> *&p) {
	if (p != NULL) {
		destroyTree(p->left); 
		destroyTree(p->right); 
		delete p; 
	}
};

template<class Type>	
void binaryTree<Type>::insert(binaryTreeNode<Type> *&p, const Type &x) {
	if (p == NULL) 
		p = new binaryTreeNode<Type>(x, NULL, NULL); 
	else if (p->element <= x)
		insert(p->right, x); 
	else 
		insert(p->left, x); 
};

template<class Type>	
void binaryTree<Type>::remove(binaryTreeNode<Type> *&p, const Type &x) {
	binaryTreeNode<Type> *rm;
	if (p==NULL)
		return;
	if (x < p->element)
		remove(p->left, x);
	else if (x > p->element)
		remove (p->right, x);
	else {
		if (p->left == NULL || p->right == NULL) {
			rm = p; 
			p = (p->left == NULL)? p->right: p->left; 
			delete rm; 
		}
		else {
			p->element = findMin(p->right)->element; 
			remove(p->right, p->element);    
		}
	}
};

template<class Type>	
void binaryTree<Type>::inOrderTraversal(binaryTreeNode<Type> *p) {
	if (p != NULL) {
		inOrderTraversal(p->left); 
		cout << " " << p->element; 
		inOrderTraversal(p->right); 
	}
};

template<class Type>	
void binaryTree<Type>::preOrderTraversal(binaryTreeNode<Type> *p) {
	if (p != NULL) {
		cout << " " << p->element; 
		preOrderTraversal(p->left); 
		preOrderTraversal(p->right); 
	}
};

template<class Type>	
void binaryTree<Type>::postOrderTraversal(binaryTreeNode<Type> *p) {
	if (p != NULL) {
		postOrderTraversal(p->left); 
		postOrderTraversal(p->right); 
		cout << " " << p->element; 
	}
};

template<class Type>	
int binaryTree<Type>::treeHeight(binaryTreeNode<Type> *p) {
	if (p == NULL)
		return -1; 
	else 
		return 1 + larger(treeHeight(p->left), treeHeight(p->right)); 
};

template<class Type>	
int binaryTree<Type>::treeNodeCount(binaryTreeNode<Type> *p) {
	if (p == NULL)
		return 0; 
	else 
		return 1 + treeNodeCount(p->left) + treeNodeCount(p->right);   
};

template<class Type>	
int binaryTree<Type>::treeLeaveCount(binaryTreeNode<Type> *p) {
	if (p == NULL)
		return 0; 
	else if (p->left == NULL && p->right == NULL)
		return 1; 
	else if (p->left == NULL)
		return treeLeaveCount(p->right); 
	else if (p->right == NULL)
		return treeLeaveCount(p->left); 
	else 
		return treeLeaveCount(p->left) + treeLeaveCount(p->right);
};

template<class Type>	
binaryTreeNode<Type> *binaryTree<Type>::findMin(binaryTreeNode<Type> *p) const {
	if (p == NULL)
		return NULL; 
	else if (p->left == NULL)
		return p; 
	else 
		return findMin(p->left); 
};

template<class Type>	
binaryTreeNode<Type> *binaryTree<Type>::findMax(binaryTreeNode<Type> *p) const {
	if (p == NULL)
		return NULL; 
	else if (p->right == NULL)
		return p; 
	else 
		return findMin(p->right); 
};

template<class Type>	
bool binaryTree<Type>::find(const binaryTreeNode<Type> *p, const Type &x) const {
	if (p == NULL)
		return false;
	else if (p->element == x)
		return true; 
	else if (x < p->element)
		return find(p->left, x); 
	else 
		return find (p->right, x); 
};

template<class Type>
int binaryTree<Type>::larger(int x, int y) {
	return (x >= y)? x : y; 
};