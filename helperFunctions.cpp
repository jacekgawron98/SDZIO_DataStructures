#include "helperFunctions.h"
#include <Windows.h>
#include <iostream>
using namespace std;

double PCFreq = 0.0;
__int64 CounterStart = 0;

//funckja resetuj¹ca licznik
void counterStart() {
	LARGE_INTEGER li;
	if (!QueryPerformanceFrequency(&li))
		cout << "QueryPerformanceFrequency failed\n";
	PCFreq = double(li.QuadPart) / 1000.0; //dzielenie przez 1000 pozwoli na wyœwietlenie wyniku w milisekundach

	QueryPerformanceCounter(&li);
	CounterStart = li.QuadPart;
}

//funkcja pobieraj¹ca licznik
double getCounter() {
	LARGE_INTEGER li;
	QueryPerformanceCounter(&li);
	return double(li.QuadPart - CounterStart) / PCFreq;
}

//pomocnicza funckja do generowania losowych liczb ca³kowitych
int generateInt(int min, int max) {
	if (max - min != 0) {
		int number = rand() % (max - min) + min;
		return number;
	}
	return 0;
}

