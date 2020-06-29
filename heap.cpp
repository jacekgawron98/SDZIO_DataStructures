#include "heap.h"
#include "helperFunctions.h"
#include <iostream>
#include <fstream>
using namespace std;

//konstruktor ustawia maksymalny rozmiar kopca w zale¿noœci od podanej danej
Heap::Heap(int heapMaxSize) {
	tableMaxSize = heapMaxSize;
	tableMax = new int[heapMaxSize];
}

//funkcja wypisuje dane w postaci drzewa (drzewo bêdzie odczytywane od prawej do lewej)
void Heap::print2D(int root, int space) {
	if (root >= size) {
		return;
	}
	space += 10;
	print2D(2*root+2, space);
	cout << endl;
	for (int i = 10; i < space; i++) {
		cout << " ";
	}
	cout << tableMax[root] << endl;
	print2D(2*root+1, space);
}

bool Heap::addElement(int data) {
	if (size < tableMaxSize) {
		tableMax[size] = data;
		heapifyUp(size);
		size++;
		return true;
	}
	else {
		return false;
	}
}

bool Heap::deleteElement(int data) {
	int index = find(data);
	if (index != -1) {
		swapElements(index, size - 1);
		size--;
		heapifyDown(index);
		return true;
	}
	else {
		return false;
	}
}

int Heap::find(int data) {
	for (int i = 0; i < size; i++) {
		if (tableMax[i] == data) {
			return i;
		}
	}
	return -1;
}

void Heap::getAll() {
	cout << "W wersji tablicowej: " << endl << endl;
	int index = 0;
	while (index < size) {
		cout << tableMax[index] << " ";
		index++;
	}
	cout << endl << endl << "W wersji drzewa: " << endl << endl;
	print2D(0, 0);
}

//funckje testujace dzia³anie poszczególnych operacji
double Heap::testAdd(int size) {
	int* data = new int[size];
	for (int i = 0; i < size; i++) {
		data[i] = generateInt(0, 1000);
	}
	counterStart();
	for (int i = 0; i < size; i++) {
		addElement(data[i]);
	}
	delete[]data;
	return getCounter();
}

double Heap::testRemove(int size) {
	counterStart();
	for (int i = 0; i < size; i++) {
		deleteElement(tableMax[0]);
	}
	return getCounter();
}

double Heap::testFind(int data) {
	counterStart();
	find(data);
	return getCounter();
}

void Heap::test() {
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
//naparawa kopca w dó³
void Heap::heapifyDown(int index) {
	int largest;
	int l = 2 * index + 1;
	int r = 2 * index + 2;

	if (l < size && tableMax[l] > tableMax[index]) {
		largest = l;
	}
	else {
		largest = index;
	}
	if (r < size && tableMax[r] > tableMax[index]) {
		largest = r;
	}
	if (largest != index) {
		swapElements(index, largest);
		heapifyDown(largest);
	}
}
//naprawa kopca w górê
void Heap::heapifyUp(int index) {
	int parent = (index - 1) / 2;
	if (parent >= 0) {
		if (tableMax[parent] < tableMax[index]) {
			swapElements(index, parent);
			heapifyUp(parent);
		}
	}
}

//podmiana dwóch elementów
void Heap::swapElements(int firstIndex, int secondIndex) {
	int buff = tableMax[firstIndex];
	tableMax[firstIndex] = tableMax[secondIndex];
	tableMax[secondIndex] = buff;
}

Heap Heap::generateRandom(int heapMaxSize, int size) {
	Heap newHeap = Heap(heapMaxSize);
	for (int i = 0; i < size; i++) {
		newHeap.addElement(generateInt(0, 1000));
	}
	return newHeap;
}

Heap Heap::buildFromFile(Heap heapBuff, string name){
	ifstream file;
	file.open(name);
	if (!file) {
		cout << "Nie mozna wczytac z pliku";
		return heapBuff; //w przypadku b³edu odczytu ustawiamy star¹ strukturê
	}
	int size;
	file >> size;
	Heap newHeap = Heap(size*1000); //ustawiam maksymln¹ pojemnoœæ tablicy kopca 1000x wiêksz¹
	int data;
	while (file >> data) {
		newHeap.addElement(data);
	}
	file.close();
	return newHeap;
}
