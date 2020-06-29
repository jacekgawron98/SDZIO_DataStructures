#include <string>
using namespace std;
class Table {
private: 
	int curSize = 0;
public:
	int *table;

	Table();

	void pushBack(int data);
	void pushFront(int data);

	bool push(int data,int index);
	bool pop(int index);

	int find(int data);

	void test();

	double testPush(int size);
	double testPushFront(int size);
	double testPushBack(int size);
	double testFind(int size);
	double testRemove(int size);

	void getAll();

	static Table generateRandom(int size);
	static Table buildFromFile(Table tableBuff,string name);

	int& operator[](int index);
};
