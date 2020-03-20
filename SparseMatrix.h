#include<iostream>
using namespace std;

#pragma once


class SparseMatrix
{
	int nrLines, nrColumns;
	int nrElements;//number of elements != 0
	double* elements; //array of the elements !=0 
	int* lines, * cols; //arrays for coordinates
	//am ales sa varianta cu un array double pentru elemente si doua array-uri int pentru indici in locul unei matrici de tip double cu 3 linii
	//deoarece daca vrem sa avem elemente de tip double, un element+indicii sai va ocupa 4*2+8=16 bytes (cu 3 vectori) vs 8*3=24 bytes (varianta cu matrice)
	//in cazul in care vrem long double, diferenta e si mai mare. Chiar daca este mai user friendly, cred ca pentru un numar mare de elemente nu e tocmai bine.

	public:
		SparseMatrix();
		SparseMatrix(int, int, double*, int*, int*);//constructor for M(n*n)
		SparseMatrix(int, int, int, double*,int*,int*);//constructor for M(n*m)
		SparseMatrix(const SparseMatrix&); //copy constructor
		~SparseMatrix();//destructor

		//Operator Overloading Methods
		friend SparseMatrix operator+(const SparseMatrix&, const SparseMatrix&);
		friend SparseMatrix operator-(const SparseMatrix&, const SparseMatrix&);
		friend istream& operator>>(istream&, SparseMatrix&);
		friend ostream& operator<<(ostream&, const SparseMatrix&);
		SparseMatrix operator=(const SparseMatrix&);
	
	protected:
		//Helper Methods
		static int comparePositions(int, int, int, int);
		static int nrOverlapsPlus(const SparseMatrix&, const SparseMatrix&);
		static int nrOverlapsMinus(const SparseMatrix&, const SparseMatrix&);

		
};

