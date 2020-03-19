#include <ctime>
#include <iostream>
#include <cmath>

using namespace std;

void print(int T[], int N) {
	for (int i = 0; i < N; i++) cout << T[i] << " ";
}

int partition(int tab[], int left, int right) {
	int x = tab[right];
	int j = left - 1;
	int i;
	for (i = left; i<right; i++) {
		if (tab[i] <= x) {
			j++;
			swap(T[i], T[j]);
		}
	}
	j++;
	swap(tab[i], tab[j]);
	return j;
}

void quickSort(int tab[], int left, int right) {
	if (left < right) {
		int pivot = partition(tab, left, right);
		quickSort(tab, left, pivot - 1);
		quickSort(tab, pivot + 1);
	}
}

int main() {
	const int N = 10;
	int K = 100000;
	int T[N];
	srand(time(NULL));
	for (int i = 0; i < N; i++) T[i] = rand() % K;
	print(T, N);
	quicksort(T, 0, N);
	print(T, N);
	system("pause");
	return 0;
}
