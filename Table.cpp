#include "table.h";
#include "helperFunctions.h"
#include <iostream>
#include <fstream>
using namespace std;

Table::Table() {
	curSize = 0;
	table = new int[curSize];
}

void Table::pushBack(int data) {
	curSize++;
	int* buff = table;
	table = new int[curSize];
	for (int i = 0; i < curSize - 1; i++) {
		table[i] = buff[i];
	}
	table[curSize - 1] = data;
	delete[]buff;
}

void Table::pushFront(int data) {
	curSize++;
	int* buff = table;
	table = new int[curSize];
	for (int i = 1; i < curSize; i++) {
		table[i] = buff[i - 1];
	}
	table[0] = data;
	delete[]buff;
}

bool Table::push(int data, int index) {
	if (index > curSize || index < 0) {
		return false;
	}
	if (index == 0) {
		pushFront(data);
		return true;
	}
	else if (index == curSize) {
		pushBack(data);
		return true;
	}
	else {
		curSize++;
		int* buff = table;
		table = new int[curSize];
		for (int i = 0; i < curSize; i++) {
			if (i == index) {
				table[i] = data;
			}
			else if (i < index) {
				table[i] = buff[i];
			}
			else {
				table[i] = buff[i - 1];
			}
		}
		delete[]buff;
		return true;
	}
}

bool Table::pop(int index) {
	if (index >= curSize || index < 0) {
		return false;
	}
	curSize--;
	int* buff = table;
	table = new int[curSize];
	for (int i = 0; i <= curSize; i++) {
		if (i == index) {
			continue;
		}
		if (i < index) {
			table[i] = buff[i];
		}
		else {
			table[i - 1] = buff[i];
		}
	}
	delete[]buff;
	return true;
}

int Table::find(int data) {
	for (int i = 0; i < curSize; i++) {
		if (table[i] == data) {
			return i;
		}
	}
	return -1;
}

void Table::getAll() {
	for (int i = 0; i < curSize; i++) {
		cout << table[i] << " ";
	}
	cout << endl << endl;
}

//funckje testujace dzia³anie poszczególnych operacji
double Table::testPush(int size) {
	int* data = new int[size];
	for (int i = 0; i < size; i++) {
		data[i] = generateInt(0, 1000);
	}
	counterStart();
	for (int i = 0; i < size; i++) {
		push(data[i], generateInt(0, curSize + 1));
	}
	delete[]data;
	return getCounter();
}

double Table::testPushFront(int size) {
	int* data = new int[size];
	for (int i = 0; i < size; i++) {
		data[i] = generateInt(0, 1000);
	}
	counterStart();
	for (int i = 0; i < size; i++) {
		pushFront(data[i]);
	}
	delete[]data;
	return getCounter();
}

double Table::testPushBack(int size) {
	int* data = new int[size];
	for (int i = 0; i < size; i++) {
		data[i] = generateInt(0, 1000);
	}
	counterStart();
	for (int i = 0; i < size; i++) {
		pushBack(data[i]);
	}
	delete[]data;
	return getCounter();
}

double Table::testFind(int data) {
	counterStart();
	find(data);
	return getCounter();
}

double Table::testRemove(int size) {
	counterStart();
	for (int i = 0; i < size; i++) {
		pop(0);
	}
	return getCounter();
}

void Table::test() {
	double timePush = 0.0;
	double timePushBack = 0.0;
	double timePushFront = 0.0;
	double timeFind = 0.0;
	double timeRemove = 0.0;

	int size = 1000;
	for (int i = 1; i < 8; i++) {
		size = 1000 + (i - 1) * 4000;
		for (int j = 0; j < 100; j++) {
			timePush += testPush(size);
			testRemove(size);
			timePushBack += testPushBack(size);
			testRemove(size);
			timePushFront += testPushFront(size);
			timeFind += testFind(generateInt(0, 1000));
			timeRemove += testRemove(size);
		}
		cout << "Czas dodawania z przodu " << size << " elementow: " << timePushFront / 100 << endl;
		cout << "Czas dodawania z tylu " << size << " elementow: " << timePushBack / 100 << endl;
		cout << "Czas dodawania na losowej pozycji " << size << " elementow: " << timePush / 100 << endl;
		cout << "Czas wyszukiwania wsrod " << size << " elementow: " << timeFind / 100 << endl;
		cout << "Czas usuwania " << size << " elementow: " << timeRemove / 100 << endl << endl;
		timePush = 0.0;
		timePushBack = 0.0;
		timePushFront = 0.0;
		timeFind = 0.0;
		timeRemove = 0.0;
	}
}

Table Table::generateRandom(int size) {
	Table newTable = Table();
	for (int i = 0; i < size; i++) {
		newTable.push(generateInt(0, 1000), i);
	}
	return newTable;
}

Table Table::buildFromFile(Table tableBuff, string name) {
	ifstream file;
	file.open(name);
	if (!file) {
		cout << "Nie mozna wczytac z pliku";
		return tableBuff;
	}
	Table newTable = Table();
	int data;
	file >> data;
	while (file >> data) {
		newTable.pushBack(data);
	}
	file.close();
	return newTable;
}
//nadpisanie operatora [] umo¿liwia dostêp do elementów korzystaj¹c z tablicowych indeksów
int& Table::operator[](int index) {
	if (index >= curSize) {
		cout << "Nie ma takiego indeksu" << endl;
		cin.get();
		exit(0);
	}
	return table[index];
}
