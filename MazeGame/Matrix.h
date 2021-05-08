#pragma once
#include <tuple>
#include <string>

class Matrix{

public:
	//Constructors/destructors
	Matrix() : n(0), m(0), M(nullptr), Mc(nullptr) {};//constr sets all null
	Matrix(int n, int m);				//constructor sets all to 0
	Matrix(int n, int m, char let);		//constructor sets all to a given char
	Matrix(int n, int m, int val);		//constructor sets all to a given int
	Matrix(Matrix& MtoCopy);			//copies a map object
	~Matrix() { destroyMatrix(); }

	//setters
	void SetVal(int i, int j, double x);
	void SetChar(int i, int j, char l);
	void SetValMatrixToIndexes();

	//getters
	int GetRows() const { return n; }
	int GetCols() const { return m; }
	double GetVal(int i, int j);
	char GetChar(int i, int j);
	void GetMin();
	double** GetIntMatrix() { return M; }
	char** GetCharMatrix() { return Mc; }
	double GetMinValue() { return minValue; }
	int GetArgi() { return argi; };
	int GetArgj() { return argj; };
	double GetVIndex(int i, int j) { return M[i][j]; }
	
	//printers
	void DisplayMin();
	void DisplayCharMatrixGaps();
	void DisplayIntMatrix();
	void DisplayIntMatrixGaps();
	void DisplayCharMatrix();
	void DisplayCharMatrixWithLabels();
	void DisplayIntMatrixWithLabels();
	
private:
	int n;							//size of rows
	int m;							//size of cols
	double** M = nullptr;			//a 2D array of ints
	char** Mc = nullptr;			//a 2D array of chars
	void destroyMatrix();//deletes the mem alocated to the Map
	
	//for use with get min function Note: Had weird problems with using a tuples
	int argi;
	int argj;
	double minValue;
};

