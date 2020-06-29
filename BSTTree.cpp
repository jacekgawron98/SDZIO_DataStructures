#include "BSTTree.h"
#include "helperFunctions.h"
#include <iostream>
#include <fstream>
#include <cmath>
using namespace std;

BSTTree::BSTTree() {
	root = NULL;
	numberOfNodes = 0;
}

//metoda wyœwietlaj¹ca dane w postaci drzewa (czytamy od lewej do prawej)
void BSTTree::print2D(Node* root, int space) {
	if (root == NULL) {
		return;
	}
	space += 10;
	print2D(root->right, space);
	cout << endl;
	for (int i = 10; i < space; i++) {
		cout << " ";
	}
	cout << root->key << endl;
	print2D(root->left, space);
}

bool BSTTree::addElement(int key) {
	if (find(key) != NULL) {
		return false;
	}
	Node* newNode = new Node(key);
	if (root == NULL) {
		root = newNode;
	}
	Node* curRoot = root;
	while (curRoot != newNode) {
		if (curRoot->key <= newNode->key) {
			if (curRoot->right == NULL) {
				curRoot->right = newNode;
				newNode->parent = curRoot;
				curRoot = newNode;
			}
			else {
				curRoot = curRoot->right;
			}
		}
		else if (curRoot->key >= newNode->key) {
			if (curRoot->left == NULL) {
				curRoot->left = newNode;
				newNode->parent = curRoot;
				curRoot = newNode;
			}
			else {
				curRoot = curRoot->left;
			}
		}
	}
	numberOfNodes++;
	return true;
}

bool BSTTree::deleteElement(int key) {
	Node* nodeToDelete = find(key);
	if (nodeToDelete == NULL) {
		return false;
	}
	Node* y;
	Node* x;
	if (nodeToDelete->left == NULL || nodeToDelete->right == NULL) {
		y = nodeToDelete;
	}
	else {
		y = findSuccessor(nodeToDelete);
	}
	if (y->left != NULL) {
		x = y->left;
	}
	else {
		x = y->right;
	}
	if (x != NULL) {
		x->parent = y->parent;
	}
	if (y->parent == NULL) {
		root = x;
	}
	else {
		if (y == y->parent->left) {
			y->parent->left = x;
		}
		else {
			y->parent->right = x;
		}
	}
	if (y != nodeToDelete) {
		nodeToDelete->key = y->key;
	}
	numberOfNodes--;
	return true;
}

//metoda zwraca NULL jesli nie odnaleziono podanego klucza
Node* BSTTree::find(int key) {
	Node* curRoot = root;
	while (curRoot != NULL) {
		if (curRoot->key == key) {
			return curRoot;
		}
		else {
			if (curRoot->key <= key) {
				curRoot = curRoot->right;
			}
			else if (curRoot->key >= key) {
				curRoot = curRoot->left;
			}
		}
	}
	return NULL;
}

void BSTTree::getAll() {
	print2D(root, 0);
}

//funkcje testuj¹ce dzia³anie poszczególnych operacji
double BSTTree::testAdd(int size) {
	int* data = new int[size];
	for (int i = 0; i < size; i++) {
		data[i] = generateInt(0, 1000);
	}
	counterStart();
	for (int i = 0; i < size; i++) {
		addElement(data[i]);
		balance();
	}
	delete[]data;
	return getCounter();
}

double BSTTree::testRemove(int size) {
	counterStart();
	for (int i = 0; i < size; i++) {
		if (root != nullptr) {
			deleteElement(root->key);
		}
	}
	return getCounter();
}

double BSTTree::testFind(int data) {
	counterStart();
	find(data);
	return getCounter();
}

//metoda zbieraj¹ca wyniki w pomicznuczych funkcji testujacych
void BSTTree::test() {
	double timeAdd = 0.0;
	double timeFind = 0.0;
	double timeRemove = 0.0;

	int size = 1000;
	for (int i = 1; i < 8; i++) {
		size = 1000 + (i-1) * 4000;
		for (int j = 0; j < 100; j++) {
			timeAdd += testAdd(size);
			timeFind += testFind(generateInt(0, 1000));
			timeRemove += testRemove(size);
		}
		cout << "Czas dodawania " << size << " elementow: " << timeAdd / 100 << endl;
		cout << "Czas wyszukiwania wsrod " << size << " elementow: " << timeFind / 100 << endl;
		cout << "Czas usuwania " << size << " elementow: " << timeRemove / 100 << endl << endl;
		timeAdd = 0.0;
		timeFind = 0.0;
		timeRemove = 0.0;
	}
}

//rotacja w lewo
void BSTTree::rotateLeft(Node* node) {
	Node* tmp;
	if (node->right != NULL) {
		tmp = node->right;
		node->right = tmp->left;
		tmp->left = node;

		if (node->parent != NULL) {
			if (node->parent->right = node) {
				node->parent->right = tmp;
			}
			else {
				node->parent->left = tmp;
			}
		}
		tmp->parent = node->parent;
		node->parent = tmp;
		if (root == node) {
			root = tmp;
		}
	}
	else {
		return;
	}
}

//rotacja w prawo
void BSTTree::rotateRight(Node* node) {
	Node* tmp;
	if (node->left != NULL) {
		tmp = node->left;
		node->left = tmp->right;
		tmp->right = node;

		if (node->parent != NULL) {
			if (node->parent->right = node) {
				node->parent->right = tmp;
			}
			else {
				node->parent->left = tmp;
			}
		}
		tmp->parent = node->parent;
		node->parent = tmp;
		if (root == node) {
			root = tmp;
		}
	}
	else {
		return;
	}
}

//prostowanie drzewa
void BSTTree::createLinear(Node* root) {
	Node* tmp = root;
	while (tmp != NULL) {
		if (tmp->left != NULL) {
			rotateRight(tmp);
			tmp = tmp->parent;
		}
		else {
			tmp = tmp->right;
		}
	}
}

//równowa¿enie drzewa
void BSTTree::balance() {
	createLinear(root);
	int m = pow(2, log2(numberOfNodes + 1)) - 1;
	while (m > 1) {
		m = m / 2;
		Node* tmp = root;
		for (int i = 0; i < m; i++) {
			rotateLeft(tmp);
			tmp = tmp->parent->right;
		}
	}
}

//szukanie nastêpnika
Node* BSTTree::findSuccessor(Node* node) {
	if (node->right != NULL) {
		return findMinKey(node->right);
	}
	Node* tmp = node->parent;
	while (tmp != NULL && tmp->left != node) {
		node = tmp;
		tmp = tmp->parent;
	}
	return tmp;
}

//szukanie maksymalnego klucza
Node* BSTTree::findMaxKey(Node* node) {
	while (node->right != NULL) {
		node = node->right;
	}
	return node;
}
//szukanie minimalnego klucza
Node* BSTTree::findMinKey(Node* node) {
	while (node->left != NULL) {
		node = node->left;
	}
	return node;
}

//tworzenie losowego drzewa
BSTTree BSTTree::generateRandom(int size) {
	BSTTree newTree = BSTTree();
	for (int i = 0; i < size; i++) {
		newTree.addElement(generateInt(0, 1000));
	}
	return newTree;
}

BSTTree BSTTree::buildFromFile(BSTTree treeBuff, string name) {
	ifstream file;
	file.open(name);
	if (!file) {
		cout << "Nie mozna wczytac z pliku";
		return treeBuff;
	}
	BSTTree newTree = BSTTree();
	int data;
	file >> data;
	while (file >> data) {
		newTree.addElement(data);
	}
	file.close();
	return newTree;
}
