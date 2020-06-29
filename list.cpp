#include "list.h"
#include "helperFunctions.h"
#include <fstream>
using namespace std;

List::List()
{
	size = 0;
	head = NULL;
	tail = NULL;
}

void List::pushFront(int data)
{
	ListElement *element = new ListElement();
	element->data = data;
	element->prev = NULL;

	if (head != NULL) {
		head->prev = element;
		element->next = head;
	}
	else
	{
		element->next = NULL;
		tail = element;
	}
	size++;
	head = element;
}

void List::pushBack(int data)
{
	ListElement *element = new ListElement();
	element->data = data;
	element->next = NULL;


	if (tail != NULL) {
		tail->next = element;
		element->prev = tail;
	}
	else
	{
		element->prev = NULL;
		head = element;
	}
	size++;
	tail = element;
}

bool List::push(int data, int index)
{
	if (index == size) {
		pushBack(data);
	}
	else if (index == 0) {
		pushFront(data);
	}
	else if (index < 0 || index > size) {
		return false;
	}
	else {
		ListElement *elementOnIndex = head;
		ListElement *newElement = new ListElement();
		newElement->data = data;
		for (int i = 0; i <= index; i++) {
			if (i == index)
				break;
			elementOnIndex = elementOnIndex->next;
		}
		size++;
		elementOnIndex->prev->next = newElement;
		newElement->prev = elementOnIndex->prev;
		elementOnIndex->prev = newElement;
		newElement->next = elementOnIndex;
	}
	return true;
}

void List::popFront()
{
	head = head->next;
	delete(head->prev);
	head->prev = NULL;
	size--;
}

void List::popBack()
{
	tail = tail->prev;
	delete(tail->next);
	tail->next = NULL;
	size--;
}

bool List::pop(int data)
{
	int index = find(data);
	if (index == 0) {
		popFront();
	}
	else if (index == size-1) {
		popBack();
	}
	else if (index > 0 && index < size-1) {
		ListElement *elementOnIndex = head;
		for (int i = 0; i <= index; i++) {
			if (i == index)
				break;
			elementOnIndex = elementOnIndex->next;
		}
		elementOnIndex->next->prev = elementOnIndex->prev;
		elementOnIndex->prev->next = elementOnIndex->next;
		delete(elementOnIndex);
		size--;
	}
	else {
		return false;
	}
	return true;
}

int List::find(int data)
{
	int index = 0;
	ListElement *current = head;
	do {
		if (current->data == data) {
			return index;
		}
		index++;
		current = current->next;
	} while (current != NULL);
	return -1;
}

void List::getAll()
{
	if (size == 0) {
		cout << "Lista jest pusta" << endl;
	}
	else {
		ListElement *current = head;
		do
		{
			cout << current->data << " ";
			current = current->next;
		} while (current->next != NULL);
		cout << current->data << " " << endl;

		current = tail;
		do
		{
			cout << current->data << " ";
			current = current->prev;
		} while (current->prev != NULL);
		cout << current->data << " " << endl;
	}
}
//funckje testujace dzia³anie poszczególnych operacji
double List::testPush(int size) {
	int* data = new int[size];
	for (int i = 0; i < size; i++) {
		data[i] = generateInt(0, 1000);
	}
	counterStart();
	for (int i = 0; i < size; i++) {
		push(data[i],generateInt(0,this->size));
	}
	delete[] data;
	return getCounter();
}

double List::testPushBack(int size) {
	int* data = new int[size];
	for (int i = 0; i < size; i++) {
		data[i] = generateInt(0, 1000);
	}
	counterStart();
	for (int i = 0; i < size; i++) {
		pushBack(data[i]);
	}
	delete[] data;
	return getCounter();
}

double List::testPushFront(int size) {
	int* data = new int[size];
	for (int i = 0; i < size; i++) {
		data[i] = generateInt(0, 1000);
	}
	counterStart();
	for (int i = 0; i < size; i++) {
		pushFront(data[i]);
	}
	delete[] data;
	return getCounter();
}

double List::testPop(int size) {
	counterStart();
	for (int i = 0; i < size; i++) {
		pop(generateInt(0,1000));
	}
	return getCounter();
}

double List::testPopBack(int size) {
	counterStart();
	for (int i = 0; i < size; i++) {
		popBack();
	}
	return getCounter();
}

double List::testPopFront(int size) {
	counterStart();
	for (int i = 0; i < size; i++) {
		popFront();
	}
	return getCounter();
}

double List::testFind(int data) {
	counterStart();
	find(data);
	return getCounter();
}

void List::test()
{
	int testSize;
	double timePush = 0.0;
	double timePushFront = 0.0;
	double timePushBack = 0.0;
	double timePop = 0.0;
	double timePopFront = 0.0;
	double timePopBack = 0.0;
	double timeFind = 0.0;

	testSize = 1000;
	for (int i = 1; i < 8; i++) {
		testSize = 1000 + (i-1) * 4000;
		for (int j = 0; j < 100; j++) {
			timePush += testPush(testSize);
			timePop += testPop(testSize);
			timePushFront += testPushFront(testSize);
			timePopFront += testPopFront(testSize);
			timePushBack += testPushBack(testSize);
			timeFind += testFind(generateInt(0,1000));
			timePopBack += testPopBack(testSize);
		}
		cout << "Czas dodawania " << testSize << " elementow z przodu: " << timePushFront/100 << endl;
		cout << "Czas dodawania " << testSize << " elementow z tylu: " << timePushFront/100 << endl;
		cout << "Czas dodawania " << testSize << " elementow na losowej pozycji: " << timePushFront/100 << endl;
		cout << "Czas usuwania " << testSize << " elementow z przodu: " << timePushFront/100 << endl;
		cout << "Czas usuwania " << testSize << " elementow z tylu: " << timePushFront/100 << endl;
		cout << "Czas usuwania " << testSize << " elementow na losowej pozycji: " << timePushFront/100 << endl;
		cout << "Czas szukania wsrod " << testSize << " elementow: " << timeFind/100 << endl;
		timePush =0 ;
		timePop = 0;
		timePushFront = 0;
		timePopFront = 0;
		timePushBack = 0;
		timeFind = 0;
		timePopBack = 0;
	}
}

List List::generateRandom(int size)
{
	List list = List();
	for (int i = 0; i < size; i++) {
		list.pushBack(generateInt(0, 10000));

	}
	return list;
}

List List::buildFromFile(List listBuff, string name){
	ifstream file;
	file.open(name);
	if (!file) {
		cout << "Nie mozna wczytac z pliku";
		return listBuff;
	}
	List newList = List();
	int data;
	file >> data;
	while (file >> data) {
		newList.pushBack(data);
	}
	file.close();
	return newList;
}

//nadpisanie operatora [] umo¿liwia dostêp do elementów listy korzystaj¹c z tablicowych indeksów
int& List::operator[](int index)
{
	if (index >= size) {
		cout << "Nie ma takiego indeksu" << endl;
		cin.get();
		exit(0);
	}
	ListElement *current = head;
	for (int i = 0; i <= index; i++) {
		if (i == index) {
			return current->data;
		}
		current = current->next;
	}
}
