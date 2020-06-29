#include <string>
using namespace std;
class Heap {
	int tableMaxSize;
	int size = 0;

	void swapElements(int, int);

	void print2D(int root, int space);
public:
	int* tableMax;

	Heap(int);

	bool addElement(int);

	bool deleteElement(int);

	int find(int);

	void getAll();

	double testAdd(int size);
	double testRemove(int size);
	double testFind(int data);

	void test();

	void heapifyDown(int);

	void heapifyUp(int);

	static Heap generateRandom(int,int);

	static Heap buildFromFile(Heap heapBuff, string name);
};