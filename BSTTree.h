#include <string>
using namespace std;

//struktura reprezentuj¹ca wêze³ drzewa
struct Node{
	int key;
	Node* left;
	Node* right;
	Node* parent;

	Node(int key) {
		parent = NULL;
		left = NULL;
		right = NULL;
		this->key = key;
	}
};

class BSTTree {
private:
	int numberOfNodes;
	Node* findSuccessor(Node* node);
	Node* findMinKey(Node* node);
	Node* findMaxKey(Node* node);

	void print2D(Node* root, int space);

	void rotateLeft(Node* node);
	void rotateRight(Node* node);
	void createLinear(Node* root);
public:
	Node* root;
	BSTTree();

	bool addElement(int key);

	bool deleteElement(int key);

	Node* find(int key);

	void getAll();

	double testAdd(int size);
	double testRemove(int size);
	double testFind(int data);

	void test();

	void balance();

	static BSTTree generateRandom(int size);

	static BSTTree buildFromFile(BSTTree treeBuff, string name);
};
