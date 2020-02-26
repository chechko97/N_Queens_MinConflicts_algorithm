#include <iostream>
#include <ctime>
#include <vector>
#include <chrono>
#include<bits/stdc++.h>

using namespace std;

int n;
int *queens;
int *rows;
int *d1;
int *d2;

void erase(int *arr, int n) {
	for (int i = 0; i < n; i++) {
		arr[i] = 0;
	}
}

int getQueensMaxConflictIndex() {
	int maxConflicts = INT_MIN;
	int *queensConflicts = new int[n];
	vector<int> queensMaxConflictsIndexes;
	for (int i = 0; i < n; i++) {
		int row = queens[i];
		int conflictCount = 0;
		conflictCount += rows[row] - 1;
		conflictCount += d1[n - (row - i + 1)] - 1;
		conflictCount += d2[i + row] - 1;
		if (maxConflicts < conflictCount) {
			maxConflicts = conflictCount;
		}
		queensConflicts[i] = conflictCount;
	}
	if (maxConflicts == 0) {
		delete[] queensConflicts;
		return -1;
	}
	for (int i = 0; i < n; i++) {
		if (maxConflicts == queensConflicts[i]) {
			queensMaxConflictsIndexes.push_back(i);
		}
	}
	int col = queensMaxConflictsIndexes[rand() % queensMaxConflictsIndexes.size()];
	delete[] queensConflicts;
	queensMaxConflictsIndexes.clear();
	return col;
}

int getQueensMinConflictRowIndex(int col) {
	int minConflicts = INT_MAX;
	int *queensConflictsRow = new int[n];
	vector<int> queensMinConflictsIndexes;
	for (int i = 0; i < n; i++) {
		int rowConflicts = 0;
		rowConflicts += rows[i];
		rowConflicts += d1[n - (i - col + 1)];
		rowConflicts += d2[i + col];
		if (minConflicts > rowConflicts) {
			minConflicts = rowConflicts;
		}
		queensConflictsRow[i] = rowConflicts;
	}
	for (int i = 0; i < n; i++) {
		if (minConflicts == queensConflictsRow[i]) {
			queensMinConflictsIndexes.push_back(i);
		}
	}
	int row = queensMinConflictsIndexes[rand() % queensMinConflictsIndexes.size()];
	delete[] queensConflictsRow;
	queensMinConflictsIndexes.clear();
	return row;
}

void print() {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < n; j++) {
			if (i == queens[j]) {
				cout << "* ";
			}
			else {
				cout << "_ ";
			}
		}
		cout << endl;
	}
}
void restart() {
	for (int i = 0; i < n; i++) {
		int row = rand() % n;
		queens[i] = row;
		rows[row]++;
		d1[n - (row - i + 1)]++;
		d2[i + row]++;
	}
}
int main()
{
	srand(time(NULL));
	cout << "Insert n: ";
	cin >> n;
	if (n < 4) {
		cout << "N must be larger than 3" << endl;
		system("pause");
		return 0;
	}
	queens = new int[n];
	rows = new int[n]();
	d1 = new int[2 * n - 1]();
	d2 = new int[2 * n - 1]();
	restart();

	auto startTime = chrono::steady_clock::now();
	int br = 0;
	while(true)	{
		br++;
		int col = getQueensMaxConflictIndex();
		if (col == -1) {
			break;
		}
		int rowFrom = queens[col];
		int rowTo = getQueensMinConflictRowIndex(col);
		queens[col] = rowTo;
		rows[rowFrom]--;
		rows[rowTo]++;

		d1[n - (rowFrom - col + 1)]--;
		d1[n - (rowTo - col + 1)]++;
		d2[rowFrom + col]--;
		d2[rowTo + col]++;

		if (br > 2 * n)
		{
			erase(rows, n);
			erase(d1, 2*n-1);
			erase(d2, 2*n-1);
			br = 0;
			restart();
		}
	}
	auto endTime = chrono::steady_clock::now();
	auto diff = endTime - startTime;
	cout << "Execution Time: " << chrono::duration<double, milli>(diff).count() << "ms" << endl;
	cout << endl;

	if (n < 101) {
		print();
	}

	delete[] rows;
	delete[] queens;
	delete[] d1;
	delete[] d2;
	return 0;
}
