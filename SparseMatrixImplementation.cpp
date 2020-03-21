// SparseMatrixImplementation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "SparseMatrix.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	//tests
	ifstream f("input.txt");
	SparseMatrix m1, m2, m3;
	f >> m1 >> m2;
	cout << m1 << endl;
	cout << m2 << endl;
	m3 = m1 + m2;
	cout << m3 << endl;
	m3 = m1 - m2;
	cout << m3 << endl;
	//test for matrix[line]
	double* linie;
	for (int k = 0; k < 5; k++) {
		linie = m1[k];
		for (int i = 0; i < 5; i++) cout << linie[i] << " ";
		cout << endl;
	}
	delete[]linie;

	return 0;
	
}



