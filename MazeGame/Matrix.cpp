#include "Matrix.h"
#include <iostream>
using namespace std;

//Constructor if we only know size of map, initializes both maps to default val
Matrix::Matrix(int n1, int m1){
	n = n1;
	m = m1;

	//initialize a 2d array with zeros
	M = new double* [n];  //allocate mem for n number of rows
	Mc = new char* [n];  //allocate mem for n number of rows
	for (int row = 0; row < n; row++) {
		M[row] = new double [m];  //allocate mem for m number of columns	
		Mc[row] = new char[m];  //allocate mem for m number of columns	
		for (int col = 0; col < m; col++) {//INT == spot reward, CHAR ==terrain
			M[row][col] = 0;		//initialize each spot in INT map to 0
			Mc[row][col] = 'M';		//initialize each spot in CHAR map to M
		}
	}
}

//Constructor if we only know size of matrix and initializes to val
Matrix::Matrix(int n1, int m1, int val) {
	Mc = nullptr;
	n = n1;
	m = m1;

	//initialize a 2d array with given val
	M = new double* [n];  //allocate mem for n number of rows
	for (int row = 0; row < n; row++) {
		M[row] = new double[m];  //allocate mem for m number of columns	
		for (int col = 0; col < m; col++)
			M[row][col] = val;	//initialize each spot in map to given int
	}
}

//Constructor if we only know size of matrix and initializes to letter
Matrix::Matrix(int n1, int m1, char letter) {
	M = nullptr;
	n = n1;
	m = m1;

	//initialize a 2d array with given letter
	Mc = new char* [n];  //allocate mem for n number of rows
	for (int row = 0; row < n; row++) {
		Mc[row] = new char[m];  //allocate mem for m number of columns	
		for (int col = 0; col < m; col++)
			Mc[row][col] = letter;//initialize each spot in matrix to given let
	}
}

//Copy constructor
Matrix::Matrix(Matrix& MtoCopy){
	n = MtoCopy.n;
	m = MtoCopy.m;
	
	//initialize a 2d array with given val
	M = new double* [n];  //allocate mem for n number of rows
	for (int row = 0; row < n; row++) {
		M[row] = new double[m];  //allocate mem for m number of columns	
		for (int col = 0; col < m; col++)
			M[row][col] = MtoCopy.M[row][col];	//copy values from input map
	}
}

//Display the contents of the CHAR map with labels 
void Matrix::DisplayCharMatrixWithLabels() {
	cout << "\n\n\n";
	cout << "  J->| ";
	for (int j = 0; j < m; j++)
		//uses ternary operator to fix line when n>9
		j <= 9 ? cout << j << "   " : cout << j << "  ";
	cout << "\n    I|\n";
	for (int i = 0; i < n; i++) {
		//uses ternary operator to fix line when n>9 
		i <= 9 ? cout << "    " << i << "| " : cout << "   " << i << "| ";
		for (int j = 0; j < m; j++)
			cout << Mc[i][j] << "   ";
		cout << endl;
	}
}

//Display the contents of the INT map with labels 
void Matrix::DisplayIntMatrixWithLabels(){
	cout << "\n\n\n";
	cout << "  J->| ";
	for (int j = 0; j < m; j++) { 
		//uses ternary operator to fix line when n>9
		j <= 9 ? cout << j << "   " : cout << j << "  ";
	}
	cout << "\n    I|\n";
	for (int i = 0; i < n; i++) {
		//uses ternary operator to fix line when n>9 
		i <= 9 ? cout << "    " << i << "| " : cout << "   " << i << "| ";
		for (int j = 0; j < m; j++)
			cout << M[i][j] << "   ";
		cout << endl;
	}
}

//returns the double value at the spot i,j in the matrix
double Matrix::GetVal(int i, int j){
	try { 
		return M[i][j]; 
	}
	catch(exception& e){
		cout << "Error at " << e.what() << endl;
	}
}

//returns the char value at the spot i,j in the matrix
char Matrix::GetChar(int i, int j){
	try {
		return Mc[i][j];
	}
	catch (exception& e) {
		cout << "Error at " << e.what() << endl;
	}
}

//Sets the double value at the spot i,j in the matrix
void Matrix::SetVal(int i, int j, double val){
	try {
		M[i][j] = val;
	}
	catch (exception& e) {
		cout << "Error at " << e.what() << endl;
	}
}

//Sets the char value at the spot i,j in the matrix
void Matrix::SetChar(int i, int j, char let){
	try {
		Mc[i][j] = let;
	}
	catch (exception& e) {
		cout << "Error at " << e.what() << endl;
	}
}

//sets the matrix to each index val
void Matrix::SetValMatrixToIndexes(){
	int count = 0;
	for (int i = 0; i < n; i++)
		for (int j = 0; j < m; j++)
			M[i][j] = count++;
}

void Matrix::GetMin(){
	minValue = DBL_MAX;
	argi = 0;
	argj = 0;
	for(int i = 0; i < n; i++)
		for (int j = 0; j < m; j++) 
			if ((M[i][j] < minValue) && (M[i][j] > 0)) {
				minValue = M[i][j];
				argi = i;
				argj = j;
			}
	 
	M[argi][argj] = 0; 
}

//display the minValue found when GetMin is called
void Matrix::DisplayMin(){
	cout << "Min[" << GetArgi() << "][" << GetArgj() << "]: " << GetMinValue();
}

//Display the char matrix with gaps
void Matrix::DisplayCharMatrixGaps(){
	cout << "\n\n\n";
	for (int i = 0; i < n; i++) {
		cout << "     ";
		for (int j = 0; j < m; j++)
			cout << Mc[i][j] << "  ";
		cout << endl;
	}
}

//Display the matrix with gaps
void Matrix::DisplayIntMatrixGaps(){
	cout << "\n\n\n";
	for (int i = 0; i < n; i++) {
		cout << "     ";
		for (int j = 0; j < m; j++)
			cout << M[i][j] << "  ";
		cout << endl;
	}
}

//Display the char matrix with gaps
void Matrix::DisplayCharMatrix() {
	cout << "\n";
	for (int i = 0; i < n; i++) {
		cout << "     ";
		for (int j = 0; j < m; j++)
			cout << Mc[i][j];
		cout << endl;
	}
}

//Display the int matrix without gaps
void Matrix::DisplayIntMatrix() {
	cout << "\n";
	for (int i = 0; i < n; i++) {
		cout << "     ";
		for (int j = 0; j < m; j++)
			cout << M[i][j];
		cout << endl;
	}
}

//deletes the mem alocated to the Map
void Matrix::destroyMatrix(){
	for (int i = 0; i < n; i++) {
		delete[] M[i];
		delete[] Mc[i];
	}
	delete[] Mc;
	delete[] M;
}