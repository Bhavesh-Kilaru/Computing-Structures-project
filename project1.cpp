#include<iostream>

using namespace std;

class matrixClass {
protected: 
	int numRows; // number of rows 
	int numCols; // number of columns
	int** mat; // 2D dynamic array to store matrix 

public: 
	matrixClass(); // default constructor
	matrixClass(int r, int c); // non default constructor
	void display(); // display
	void setValue(int i, int j, int val); // to set the value at location i, j
	int getValue(int i, int j); // return val at i, j
	int getNumRows(); // getter for numRows
	int getNumCols(); // getter for numCols
	matrixClass* multiply(matrixClass* multiplier); // multiply method
};// main function

default constructor
matrixClass::matrixClass() {
	numRows = 0;
	numCols = 0;
}

non default constructor
matrixClass::matrixClass(int r, int c) {
	numRows = r;
	numCols = c;

	creating a 2d matrix
	mat = new int*[numRows];
	for (int cols = 0; cols < numRows; cols++)
		mat[cols] = new int[numCols];

	initializing all values to zero in a matrix
	for (int Row = 0; Row < numRows; Row++)
		for (int Col = 0; Col < numCols; Col++)
			mat[Row][Col] = 0;
}

display
void matrixClass::display() {
	cout << "the given matrix is " << endl;
	for (int rows = 0; rows < numRows; rows++) {
		for (int cols = 0; cols < numCols; cols++) {
			cout << mat[rows][cols] << " ";
		}
		cout << endl;
	}
}

setting the value in matrix
void matrixClass :: setValue(int i, int j, int value) {
	mat[i][j] = value;
}

returning the value at a particular element
int matrixClass::getValue(int i, int j) {
	return mat[i][j];
}

returning the number of rows in the matrix
int matrixClass::getNumRows(){
	return numRows;
}

returning thr number of columns in a matrix
int matrixClass::getNumCols() {
	return numCols;
}

matrixClass* matrixClass::multiply(matrixClass* multiplier) {
	if (this->numCols != multiplier->numRows) {
		cout << "matrix multipication not possible";
		return NULL;
	}
	matrixClass *out = new matrixClass(this->numRows, multiplier -> numCols);
	for (int rows = 0; rows < this->numRows; rows++) {
		for (int cols = 0; cols < multiplier->numCols; cols++) {
			for (int k = 0; k < this->numCols; k++) {
				(*out).mat[rows][cols] += this->mat[rows][k] * multiplier ->mat[k][cols];
			}
		}
	}
	return out;
}

int main(){

	int numRows, numCols, numNonZero;
	cout << "enter the values" << endl;
	
	 read in all the numRows, numCols and numNonZero values from redirected input for matrix A
	cin >> numRows >> numCols >> numNonZero;
	
	 declare object for matrix A
	matrixClass *matrixA = new matrixClass(numRows, numCols);
	matrixA->display();

	 read in the values and use setValue to set the values read in for A
	 use the setValue method to put the values in the mat of A
	for (int nonZero = 0; nonZero < numNonZero; nonZero++) {
		int rowValue, colValue, value;
		cin >> rowValue >> colValue >> value;
		matrixA->setValue(rowValue, colValue, value);
	}

	
	 display matrix A
	cout << "A: " << endl;
	matrixA->display();
	
	 read in all the numRows, numCols and numNonZero values from redirected input for matrix B
	cin >> numRows >> numCols >> numNonZero;
	
	 declare object for matrix B
	matrixClass* matrixB = new matrixClass(numRows, numCols);
	
	 read in the values and use setValue to set the values read in for B
	 use the setValue method to put the values in the mat of B
	for (int nonZero = 0; nonZero < numNonZero; nonZero++) {
		int rowValue, colValue, value;
		cin >> rowValue >> colValue >> value;
		matrixB->setValue(rowValue, colValue, value);
	}
	
	 display matrix A
	cout << "B: " << endl;
	matrixB->display();
	
	 declare resultant matrix to store A * B
	matrixClass *matrixC = new matrixClass(matrixA->getNumRows(), matrixB->getNumCols());
	matrixC = matrixA -> multiply(matrixB);
	
	 display resultant matrix
	cout << "RESULT: " << endl;
	matrixC->display();


	return 0; 


}