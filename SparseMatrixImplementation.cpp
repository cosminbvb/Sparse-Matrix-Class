// SparseMatrixImplementation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "SparseMatrix.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	//tests for >>, <<, +, -
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


	//test for * and getters
	ifstream g("input2.txt");
	SparseMatrix m4, m5, m6;
	g >> m4 >> m5;
	cout << "--------------------" << endl;
	cout << m4;
	cout << m4.getNumberOfLines() << " lines and " << m4.getNumberOfColumns() << " columns" << endl;
	cout << endl;
	cout << m5;
	cout << m5.getNumberOfLines() << " lines and " << m5.getNumberOfColumns() << " columns" << endl;
	cout << endl;
	m6 = m4 * m5;
	cout << m6;
	cout << m6.getNumberOfLines() << " lines and " << m6.getNumberOfColumns() << " columns" << endl;
	cout << endl;
	m6 = m4 * 3;
	cout << m6;
	cout << endl;

	//test for ^
	cout << (m1 ^ 7); // it needs () because << has higher priority than  ^
	return 0;
	
}



