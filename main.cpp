#include <iostream>
#include <string>
#include <ctime>
#include <cstdlib>
#include <cstdio>
#include "list.h"
#include "heap.h"
#include "table.h"
#include "BSTTree.h"
using namespace std;

void displayMenu(string info, bool isTree) {

	cout << info << endl;
	cout << "1. Zbuduj z pliku" << endl;
	cout << "2. Usun element" << endl;
	cout << "3. Dodaj element" << endl;
	cout << "4. Znajdz element" << endl;
	cout << "5. Utworz losowe" << endl;
	cout << "6. Wyswietl zawartosc" << endl;
	cout << "7. Testuj" << endl;
	if (isTree)
	{
		cout << "8. Rownowaz drzewo" << endl;
	}
	cout << "0. Powrot do menu" << endl;
}

void menuTable(Table &table) {
    char option;
	do {
		displayMenu("=====TABLICA=====", false);
		cin >> option;
		cin.clear();
		switch (option)
		{
		case '1': {
			string name;
			cout << "Podaj nazwe pliku: ";
			cin >> name;
			table = Table::buildFromFile(table,name);
			cout << endl << endl;
			table.getAll();
			break;
		}
		case '2': {
			int index;
			cout << "Podaj indeks do usuniecia: ";
			cin >> index;
			if (!table.pop(index)) {
				cout << "Nieprawidlowy indeks" << endl;
			}
			cout << endl << endl;
			table.getAll();
			break;
		}
		case '3': {
			int data, index;
			cout << "Podaj wartosc: ";
			cin >> data;
			cout << "Podaj indeks: ";
			cin >> index;
			if (!table.push(data, index)) {
				cout << "Nieprawidlowy indeks" << endl;
			}
			cout << endl << endl;
			table.getAll();
			break;
		}
		case '4': {
			int data;
			cout << "Podaj wartosc do wyszukania: ";
			cin >> data;
			if (table.find(data) > 0) {
				cout << "Podana wartosc zostala znaleziona na indeksie: " << table.find(data) << endl;
			}
			else {
				cout << "Nie odnalezionio podanej wartosci" << endl;
			}
			break;
		}
		case '5': {
			int size;
			cout << "Podaj rozmiar tablicy: ";
			cin >> size;
			table = Table::generateRandom(size);
			cout << endl << endl;
			table.getAll();
			break;
		}
		case '6': {
			table.getAll();
			break;
		}
		case '7': {
			table.test();
			break;
		}
		default:
			break;
		}
		system("pause");
		system("cls");
	} while (option != '0');
}

void menuList(List &list) {
	char option;
	do {
		displayMenu("=====LISTA=====", false);
		cin >> option;
		switch (option)
		{
		case '1': {
			string name;
			cout << "Podaj nazwe pliku: ";
			cin >> name;
			list = List::buildFromFile(list,name);
			cout << endl << endl;
			list.getAll();
			break;
		}
		case '2': {
			int data;
			cout << "Podaj wartosc do usuniecia: ";
			cin >> data;
			if (!list.pop(data)) {
				cout << "Nie ma takiej wartosci lub wystapil blad" << endl;
			}
			cout << endl << endl;
			list.getAll();
			break;
		}
		case '3': {
			int data, index;
			cout << "Podaj wartosc: ";
			cin >> data;
			cout << "Podaj indeks: ";
			cin >> index;
			if (!list.push(data, index)) {
				cout << "Nie ma takiego indeksu lub wystapil blad" << endl;
			}
			cout << endl << endl;
			list.getAll();
			break;
		}
		case '4': {
			int data;
			cout << "Podaj wartosc do wyszukania: ";
			cin >> data;
			if (int i = list.find(data) > 0) {
				cout << "Podana wartosc zostala znaleziona na indeksie: " << list.find(data) << endl;
			}
			else {
				cout << "Nie odnalezionio podanej wartoœci" << endl;
			}
			break;
		}
		case '5': {
			int size;
			cout << "Podaj rozmiar listy: ";
			cin >> size;
			list = List::generateRandom(size);
			cout << endl << endl;
			list.getAll();
			break;
		}
		case '6': {
			list.getAll();
			break;
		}
		case '7': {
			list.test();
			break;
		}
		default:
			break;
		}
		system("pause");
		system("cls");
	} while (option != '0');
}

void menuHeap(Heap &heap) {
	char option;
	do {
		displayMenu("=====KOPIEC=====", false);
		cin >> option;
		switch (option)
		{
		case '1': {
			string name;
			cout << "Podaj nazwe pliku: ";
			cin >> name;
			heap = Heap::buildFromFile(heap,name);
			cout << endl << endl;
			heap.getAll();
			break;
		}
		case '2': {
			int data;
			cout << "Podaj wartosc do usuniecia: ";
			cin >> data;
			if (!heap.deleteElement(data)) {
				cout << "Nie odnaleziono podanego elementu" << endl;
			}
			cout << endl << endl;
			heap.getAll();
			break;
		}
		case '3': {
			int data, index;
			cout << "Podaj wartosc: ";
			cin >> data;
			if (!heap.addElement(data)) {
				cout << "Przekroczono pojemnosc kopca" << endl;
			}
			cout << endl << endl;
			heap.getAll();
			break;
		}
		case '4': {
			int data;
			cout << "Podaj wartosc do wyszukania: ";
			cin >> data;
			if (heap.find(data) > 0) {
				cout << "Podana wartosc zostala znaleziona w tablicy kopca na indeksie: " << heap.find(data) << endl;
			}
			else {
				cout << "Nie odnalezionio podanej wartosci" << endl;
			}
			break;
		}
		case '5': {
			int maxSize;
			int size;
			cout << "Podaj rozmiar kopca (<=10000000): ";
			cin >> size;
			if (size > 10000000) {
				cout << "Za duza wartosc" << endl;
				break;
			}
			heap = Heap::generateRandom(10000000,size);
			cout << endl << endl;
			heap.getAll();
			break;
		}
		case '6': {
			heap.getAll();
			break;
		}
		case '7': {
			heap.test();
			break;
		}
		default:
			break;
		}
		system("pause");
		system("cls");
	} while (option != '0');

}

void menuTree(BSTTree &tree) {
	char option;
	do {
        displayMenu("=====DRZEWO BST=====", true);
		cin >> option;
		switch (option)
		{
		case '1': {
			string name;
			cout << "Podaj nazwe pliku: ";
			cin >> name;
			tree = BSTTree::buildFromFile(tree,name);
			cout << endl << endl;
			tree.getAll();
			break;
		}
		case '2': {
			int data;
			cout << "Podaj wartosc do usuniecia: ";
			cin >> data;
			if (!tree.deleteElement(data)) {
				cout << "Podana wartosc nie istnieje" << endl;
			}
			cout << endl << endl;
			tree.getAll();
			break;
		}
		case '3': {
			int data, index;
			cout << "Podaj wartosc: ";
			cin >> data;
			if (!tree.addElement(data)) {
				cout << "Podana wartosc juz istnieje" << endl;
			}
			cout << endl << endl;
			tree.getAll();
			break;
		}
		case '4': {
			int data;
			cout << "Podaj wartosc do wyszukania: ";
			cin >> data;
			if (tree.find(data) != NULL) {
				cout << "Podana wartosc znajduje sie w drzewie" << endl;
			}
			else {
				cout << "Nie odnalezionio podanej wartosci" << endl;
			}
			break;
		}
		case '5': {
			int maxSize;
			int size;
			cout << "Podaj rozmiar drzewa: ";
			cin >> size;
			tree = BSTTree::generateRandom(size);
			cout << endl << endl;
			tree.getAll();
			break;
		}
		case '6': {
			cout << "Struktura drzewa: " << endl;
			tree.getAll();
			break;
		}
		case '7': {
			tree.test();
			break;
		}
		case '8': {
			cout << "Rownowazenie drzewa"<<endl;
			tree.balance();
			cout << endl << endl;
			tree.getAll();
			break;
		}
		default:
			break;
		}
		system("pause");
		system("cls");
	} while (option != '0');
}

int main() {

	srand(time(NULL));

	//tworzenie pustych strukturs
	Table myTable = Table();
	List myList = List();
	Heap myHeap = Heap(10000000);
	BSTTree myTree = BSTTree();

	char option;
	do {
		cout << "MENU GLOWNE" << endl;
		cout << "1. Tablica" << endl;
		cout << "2. Lista dwukieronkowa" << endl;
		cout << "3. Kopiec" << endl;
		cout << "4. Drzewo BTS" << endl;
		cout << "0. Wyjscie" << endl;
		cin >> option;
		system("cls");
		switch (option)
		{
		case '1': {
			menuTable(myTable);
			break;
		}
		case '2': {
			menuList(myList);
			break;
		}
		case '3': {
			menuHeap(myHeap);
			break;
		}
		case '4': {
			menuTree(myTree);
			break;
		}
		}
	} while (option != '0');
	return 0;
}
