#include <iostream>
#include <algorithm>
#include <string>
using namespace std;

int digit(string number, int position) {
    return (int)(number[position] - '0');
}

void sortByPosition(string tab[], int n, int pos) {
    int k = 10;
    int *counters = new int[k];
    string *result = new string[n];
	for (int i = 0; i<k; i++) counters[i] = 0;
	for (int i = 0; i < n; i++) counters[digit(tab[i], pos)]++;
	for (int i = 1; i<k; i++) counters[i] += counters[i - 1];
	for (int i = n - 1; i >= 0; i--) {
		result[counters[digit(tab[i], pos)] - 1] = tab[i];
		counters[digit(tab[i], pos)]--;
	}
	for (int i = 0; i < n; i++) tab[i] = result[i];
	delete[] counters;
	delete[] result;
    // inteligentnie przeklej kod countingSorta
    // pamietaj o uzyciu funkcji digit() !!!
}

void radixSort(string tab[], int n, int length) {
	for (int i = length - 1; i >= 0; i--) {
		sortByPosition(tab, n, i);
	}
}

int main() {
    int Z;
    cin >> Z;

	while (Z--) {

		int n, length;
		cin >> n;
        cin >> length;
		string *tab = new string[n];
		for(int i=0; i<n; i++) {
			cin >> tab[i];
            if (tab[i].length() != length) {
                cout << "Wrong number! Expected a number with " << length << " digits, got " << tab[i].length() << endl;
                return -1;
            }
		}

        radixSort(tab, n, length);
        for(int i=0; i<n; i++) {
            cout << tab[i] << endl;
        }
        delete [] tab;
    }
}
