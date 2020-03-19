#include <iostream>
#include <cmath>

using namespace std;

void EmptyBoard(char Board[], int size);
void PrintBoard(char Borad[], int size);

int main() {
	const int size = 9;
	char Board[size]; 
	EmptyBoard(Board, size);
	Print(Borad, size);
	system("pause");
}

void EmptyBoard(char Board[], int size) {
	for (int i = 0; i < size; i++) Board[i] = " ";
}

void PrintBoard(char Board[], int size) {
	for (int i = 0; i < size; i++) {
		if (i % 3 == 0) cout << "| ";
		cout << Board[i];
		if (i % 3 == 2) cout << " |" << endl;
}