#include <iostream>
#include <string>
using namespace std;
struct ListElement
{
	int data;
	ListElement *prev, *next;
};

class List {
public:
	int size;
	ListElement *head, *tail;
	
	List();

	void pushFront(int data);
	void pushBack(int data);
	bool push(int data, int index);
	
	void popFront();
	void popBack();
	bool pop(int data);

	int find(int data);

	void getAll();
	
	double testPush(int size);
	double testPushFront(int size);
	double testPushBack(int size);

	double testPop(int size);
	double testPopFront(int size);
	double testPopBack(int size);

	double testFind(int data);

	void test();

	static List generateRandom(int size);

	static List buildFromFile(List listBuff,string name);

	int& operator[](int);
};
