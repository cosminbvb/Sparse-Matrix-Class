#include "SparseMatrix.h"
#include<iostream>
#include<cassert>
using namespace std;

#pragma region Constructors and Destructor

SparseMatrix::SparseMatrix(): nrLines(1), nrColumns(1), nrElements(1), elements(new double[1]), lines(new int[1]), cols(new int[1]){}

SparseMatrix::SparseMatrix(int nrLines,int nrElements, double* elements, int* lines, int* cols) {
	this->nrLines = nrLines;
	this->nrColumns = nrLines;
	this->nrElements = nrElements;
	this->elements = new double[nrElements];
	this->lines = new int[nrElements];
	this->cols = new int[nrElements];
	for (int i = 0; i < nrElements; i++) {
		this->elements[i] = elements[i];
		this->lines[i] = lines[i];
		this->cols[i] = cols[i];
	}
}

SparseMatrix::SparseMatrix(int nrLines, int nrColumns, int nrElements, double* elements, int* lines, int* cols) {
	this->nrLines = nrLines;
	this->nrColumns = nrColumns;
	this->nrElements = nrElements;
	this->elements = new double[nrElements];
	this->lines = new int[nrElements];
	this->cols = new int[nrElements];
	for (int i = 0; i < nrElements; i++) {
		this->elements[i] = elements[i];
		this->lines[i] = lines[i];
		this->cols[i] = cols[i];
	}
}

SparseMatrix::SparseMatrix(const SparseMatrix& m) {
	this->nrLines = m.nrLines;
	this->nrColumns = m.nrColumns;
	this->nrElements = m.nrElements;
	this->elements = new double[m.nrElements];
	this->lines = new int[m.nrElements];
	this->cols = new int[m.nrElements];
	for (int i = 0; i < m.nrElements; i++) {
		this->elements[i] = m.elements[i];
		this->lines[i] = m.lines[i];
		this->cols[i] = m.cols[i];
	}
}

SparseMatrix::~SparseMatrix() {
	delete[]elements;
	delete[]lines;
	delete[]cols;
}

#pragma endregion

#pragma region Operator Overloading

SparseMatrix operator+(const SparseMatrix& m1, const SparseMatrix& m2) {
	if (m1.nrLines != m2.nrLines || m1.nrColumns != m2.nrColumns) {
		cout<<"Matrixes of different sizes";
		exit(1);
	}
	else {
		int i = 0, j = 0, k = 0, cmp;
		int new_nrElements = m1.nrElements + m2.nrElements - SparseMatrix::nrOverlaps(m1, m2);
		int* new_lines = new int[new_nrElements];
		int* new_cols = new int[new_nrElements];
		double* new_elements = new double[new_nrElements];
		while (i < m1.nrElements && j < m2.nrElements) {
			cmp = SparseMatrix::comparePositions(m1.lines[i], m1.cols[i], m2.lines[j], m2.cols[j]);
			if (cmp == 1) { 
				new_elements[k] = m1.elements[i];
				new_lines[k] = m1.lines[i];
				new_cols[k] = m1.cols[i];
				i++;
			}
			else {
				if (cmp == -1) {
					new_elements[k] = m2.elements[j];
					new_lines[k] = m2.lines[j];
					new_cols[k] = m2.cols[j];
					j++;
				}
				else {
					int localsum = m1.elements[i] + m2.elements[j];
					if (localsum != 0) {
						new_elements[k] = localsum;
						new_lines[k] = m2.lines[j];
						new_cols[k] = m2.cols[j];
						i++;
						j++;
					}
					else { //if sum is 0 ignore both elements
						i++;
						j++;
					}
				}
			}
			k++;
		}
		while (i < m1.nrElements) {
			new_elements[k] = m1.elements[i];
			new_lines[k] = m1.lines[i];
			new_cols[k] = m1.cols[i];
			i++;
			k++;
		}
		while (j < m2.nrElements) {
			new_elements[k] = m2.elements[j];
			new_lines[k] = m2.lines[j];
			new_cols[k] = m2.cols[j];
			j++;
			k++;
		}
		SparseMatrix result(m1.nrLines, m1.nrColumns, new_nrElements, new_elements, new_lines, new_cols);
		delete[]new_elements;
		delete[]new_lines;
		delete[]new_cols;
		return result;
	}

}

SparseMatrix SparseMatrix::operator=(const SparseMatrix& m) {
	nrLines = m.nrLines;
	nrColumns = m.nrColumns;
	nrElements = m.nrElements;
	delete[]elements;
	delete[]lines;
	delete[]cols;
	elements = new double[nrElements];
	lines = new int[nrElements]; 
	cols = new int[nrElements];
	for (int i = 0; i < nrElements; i++) {
		elements[i] = m.elements[i];
		lines[i] = m.lines[i];
		cols[i] = m.cols[i];
	}
	return *this;
}

ostream& operator<<(ostream& out, const SparseMatrix& m) {
	for (int i = 0; i < m.nrElements; i++)
		out << m.elements[i] << " ";
	out << endl;
	for (int i = 0; i < m.nrElements; i++)
		out << m.lines[i] << " ";
	out << endl;
	for (int i = 0; i < m.nrElements; i++)
		out << m.cols[i] << " ";
	out << endl;
	return out;
}

istream& operator>>(istream& in, SparseMatrix& m) {
	delete[]m.elements;
	delete[]m.lines;
	delete[]m.cols;
	in >> m.nrLines >> m.nrColumns >> m.nrElements;
	m.elements = new double[m.nrElements];
	m.lines = new int[m.nrElements];
	m.cols = new int[m.nrElements];
	for (int i = 0; i < m.nrElements; i++) {
		in >> m.elements[i];
	}
	for (int i = 0; i < m.nrElements; i++) {
		in >> m.lines[i];
	}
	for (int i = 0; i < m.nrElements; i++) {
		in >> m.cols[i];
	}
	return in;

}

#pragma endregion

#pragma region Helper Methods

int SparseMatrix::comparePositions(int i1, int j1, int i2, int j2) {
	//returns 1 if [i1][j1] is before [i2][j2] in the matrix
	//0 if they are overlaping
	//-1 if [i1][j1] is after [i2][j2] in the matrix
	if (i1 < i2) return 1;
	else {
		if (i1 == i2) {
			if (j1 < j2) return 1;
			else {
				if (j1 == j2) return 0;
				else return -1;
			}
		}
		else return -1;
	}
}

int SparseMatrix::nrOverlaps(const SparseMatrix& m1, const SparseMatrix& m2) {
	int i = 0, j = 0, cmp, nr = 0, nrOfZeros = 0;
	while (i < m1.nrElements && j < m2.nrElements) {
		cmp = comparePositions(m1.lines[i], m1.cols[i], m2.lines[j], m2.cols[j]);
		if (cmp == 1) i++;
		else {
			if (cmp == -1) j++;
			else {
				if (m1.elements[i] + m2.elements[j] == 0) {//number of overlaps that result in a 0
					nrOfZeros++; 
				}
				else {
					nr++; //number of overlaps that do not result in a 0
				}
				i++;
				j++;
			}
		}
	}
	return nr+2*nrOfZeros; //2*nrOfZeros because the element from each matrix will be ignored
}

#pragma endregion