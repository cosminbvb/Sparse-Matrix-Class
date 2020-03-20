// SparseMatrixImplementation.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "SparseMatrix.h"
#include <iostream>
#include <fstream>
using namespace std;

int main()
{
	ifstream f("input.txt");
	SparseMatrix m1, m2, m3;
	f >> m1 >> m2;
	m3 = m1 + m2;
	cout << m3;
	m3 = m1 - m2;
	cout << m3;
	return 0;
	
}



