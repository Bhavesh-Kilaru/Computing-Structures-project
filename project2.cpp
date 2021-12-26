// Project 2
// Fall 2021
// DSA 5005 Computing Structures
// Boiler Plate Code for Project 2
#include<iostream>

using namespace std;

class SparseRow {
protected:
	int row; // Row#
	int col; // Column#
	int value; // We will assume that all our values will be integers
	// you are restricted to add or modify the fields in the class
public:
	SparseRow(); // default constructor; row=-1;col=-1;value=0 
	SparseRow(int r, int c, int v); // non default constructor
	virtual ~SparseRow(); // Destructor
	void display(); // print Row#, Column#, value
	void setRow(int r); // setters
	void setCol(int c);
	void setValue(int v);
	int getRow(); // getters
	int getCol();
	int getValue();

	// other methods as you deem fit
};

//default constructor for sparseRow Class
SparseRow::SparseRow() {
	setRow(-1);
	setCol(-1);
	setValue(0);
}

//Non-Default Constructor For Sparse Row
SparseRow::SparseRow(int r, int c, int v) {
	setRow(r);
	setCol(c);
	setValue(v);
}

//destructor for Sparse Row
SparseRow::~SparseRow() {
	cout << "sparse destructor called" << endl;
}

//to display a particular sparseRow
void SparseRow::display() {
	cout << ' ' << row << ' ' << col << ' ' << value << endl;
}

//to set the row value in sparseRow
void SparseRow::setRow(int r) {
	row = r;
}

//to set the column value in sparseRow
void SparseRow::setCol(int c) {
	col = c;
}

//to set the value of a element in a sparseRow
void SparseRow::setValue(int v) {
	value = v;
}

//to get a row value in a sparseRow
int SparseRow::getRow() {
	return row;
}

//to get a Column value in a sparseRow
int SparseRow::getCol() {
	return col;
}

//to get a particular element value in a sparseRow
int SparseRow::getValue() {
	return value;
}

class matrixClass {
protected:
	int numRows; // number of rows 
	int numCols; // number of columns
	int numNonZero; // number of non zero elements
	int commonValue; // read from input - assume 0
	SparseRow* mat; // an array of SparseRow objects of length numNonZero

	// you are restricted to add or modify the fields in the class

public:
	matrixClass(); // default constructor
	matrixClass(int r, int c, int numNonZero); // non default constructor
	~matrixClass(); // destructor
	matrixClass(matrixClass& copyThis); // copy constructor
	void display(); // display in sparse row format
	void displayMatrix(); // display in matrix format
	void setValue(int pos, int i, int j, int val); // to set the value at location i, j; pos is to keep track of the position in mat
	int getValue(int i, int j); // return val at i, j
	int getNumRows(); // getter for numRows
	int getNumCols(); // getter for numCols
	int getValWithRowandCol(int row, int col); // given row and col number, return the value at that spot
	matrixClass* multiply(matrixClass* multiplier); // multiply method
	matrixClass* add(matrixClass* addend); // add method
	// BONUS: matrixClass* transpose(); // transopse method
	matrixClass* transpose();
	// TODO: Write the overloaded ostream operator - same as displayMatrix() method
	friend ostream& operator << (ostream& s, matrixClass& m);
	// other methods as you deem fit
	int getNumNonZeros();         //to get the number of nonZero elements in a matrix
	void matrixReorder();   //to reorder elements in a sparse matrix
};

//default constructor for matrixClass
matrixClass::matrixClass() {
	numRows = 0;
	numCols = 0;
	numNonZero = 0;
}

//constructor for matrixClass
matrixClass::matrixClass(int r, int c, int NonZero) {
	numRows = r;
	numCols = c;
	numNonZero = NonZero;
	mat = new SparseRow[NonZero];

}

//destructor for matrixClass
matrixClass::~matrixClass() {
	delete [] mat;
	cout << "destructor called " << endl;
}

//copy this constructor
matrixClass::matrixClass(matrixClass& copyThis) {
	numRows = copyThis.getNumRows();
	numCols = copyThis.getNumCols();
	numNonZero = copyThis.getNumNonZeros();
	mat = new SparseRow[numNonZero];
	for (int i = 0; i < numNonZero; i++) {
		this->setValue(i, copyThis.mat[i].getRow(), copyThis.mat[i].getCol(), copyThis.mat[i].getValue());
	}
}

//to display the matrix in sparse row format
void matrixClass::display() {
	for (int i = 0; i < this->getNumNonZeros(); i++) {
		mat[i].display();
	}
}

//to display the matrix in matrix format
void matrixClass::displayMatrix() {
	int** mt;
	mt = new int* [this->getNumRows()];
	for (int cols = 0; cols < this->getNumRows(); cols++)
		mt[cols] = new int[this->getNumCols()];
	for (int i = 0; i < this->getNumRows(); i++) {
		for (int j = 0; j < this->getNumCols(); j++) {
			mt[i][j] = 0;
		}
	}

	//to set the non zero elements in matrix
	for (int k = 0; k < this->getNumNonZeros(); k++) {
		mt[mat[k].getRow()][mat[k].getCol()] = mat[k].getValue();
	}

	//displaying in matrix format
	for (int i = 0; i < this->getNumRows(); i++) {
		for (int j = 0; j < this->getNumCols(); j++) {
			cout << mt[i][j] << ' ';
		}
		cout << endl;
	}
}

//to set the row, column and value at particular position in SparseRow matrix
void matrixClass::setValue(int pos, int i, int j, int val) {
	mat[pos] = SparseRow(i, j, val);
}

//to get the value at ith row and jth column
int matrixClass::getValue(int i, int j) {
	int out = 0;
	for (int k = 0; k < this->getNumNonZeros(); k++) {
		if (mat[k].getRow() == i && mat[k].getCol() == j) {
			out = mat[k].getValue();
		}
	}
	return out;
}

//to get the number of rows in the matrix
int matrixClass::getNumRows() {
	return numRows;
}

//to get the number of columns in the matrix
int matrixClass::getNumCols() {
	return numCols;
}

//to get the number of non zero elements in matrix
int matrixClass::getNumNonZeros() {
	return numNonZero;
}

int matrixClass::getValWithRowandCol(int row, int col) {
	int out = 0;
	for (int i = 0; i < this->getNumNonZeros(); i++) {
		if (this->mat[i].getRow() == row && this->mat[i].getCol() == col)
			out = this->mat[i].getValue();
	}
	return out;
}

//to reorder the matrix
void matrixClass::matrixReorder()
{
	//ordering columns in sparse row matrix
	for (int i = 1; i < this->getNumNonZeros(); i++)
	{
		int row = this->mat[i].getRow();
		int col = this->mat[i].getCol();
		int val = this->mat[i].getValue();

		int j = i - 1;
		while (j >= 0 && this->mat[j].getCol() > col)
		{
			int temprow = this->mat[j].getRow();
			int tempcol = this->mat[j].getCol();
			int tempval = this->mat[j].getValue();

			this->setValue(j + 1, temprow, tempcol, tempval);
			j--;
		}

		this->setValue(j + 1, row, col, val);
	}

	//ordering rows in the sparse row matrix
	for (int i = 1; i < this->getNumNonZeros(); i++)
	{
		int row = this->mat[i].getRow();
		int col = this->mat[i].getCol();
		int val = this->mat[i].getValue();

		int j = i - 1;
		while (j >= 0 && this->mat[j].getRow() > row)
		{
			int temprow = this->mat[j].getRow();
			int tempcol = this->mat[j].getCol();
			int tempval = this->mat[j].getValue();

			this->setValue(j + 1, temprow, tempcol, tempval);
			j--;
		}

		this->setValue(j + 1, row, col, val);
	}
}

//multiplying the given matrix with other matrix "Multiplier"
matrixClass* matrixClass::multiply(matrixClass* multiplier)
{
	matrixClass* matrixC = new matrixClass(this->getNumRows(), multiplier->getNumCols(),
		this->getNumRows() * multiplier->getNumCols());

	int position = 0;
	for (int i = 0; i < this->getNumRows(); i++)
	{
		for (int j = 0; j < multiplier->getNumCols(); j++)
		{
			int val = 0;
			for (int k = 0; k < this->getNumCols(); k++)
			{
				val += this->getValue(i, k) * multiplier->getValue(k, j);
			}
			if (val != 0)
			{
				matrixC->setValue(position, i, j, val);
				position++;
			}
		}
	}
	//delete matrixC;
	//removing the elements with zero values
	matrixClass* result = new matrixClass(this->getNumRows(), multiplier->getNumCols(), position);
	for (int i = 0, j = 0; i < matrixC->getNumNonZeros(); i++)
	{
		if (matrixC->mat[i].getValue())
		{
			result->setValue(j, matrixC->mat[i].getRow(),
				matrixC->mat[i].getCol(),
				matrixC->mat[i].getValue());
			j++;
		}

	}

	result->matrixReorder();
	//delete matrixC;

	return result;
}

//adding the given matrix with other matrix "addend"
matrixClass* matrixClass::add(matrixClass* addend)
{
	matrixClass* result = new matrixClass(this->getNumRows(), this->getNumCols(), this->numNonZero + addend->numNonZero);
			int pos = 0, found;
			for (int i = 0; i < this->getNumNonZeros(); i++) {
				for (int j = 0; j < addend->getNumNonZeros(); j++) {
					found = 0;
					//to check if value exists for particular row and column in both the matrices
					//if exists, then to insert the particular row, column and added value in result matrix
					if (this->mat[i].getRow() == addend->mat[j].getRow() &&
						this->mat[i].getCol() == addend->mat[j].getCol()) {
						int op = this->mat[i].getValue() + addend->mat[j].getValue();
						result->setValue(pos, this->mat[i].getRow(), this->mat[i].getCol(), op);
						pos++;
						found = 1;
						break;
					}
				}
				//to insert the values into result matrix that are in first matrix and not in addend matrix
				if (found == 0) {
					result->setValue(pos, this->mat[i].getRow(), this->mat[i].getCol(), this->mat[i].getValue());
					pos++;
				}
			}

			//to check for all the values that are in addend matrix but result matrix
			for (int i = 0; i < addend->getNumNonZeros(); i++) {
				for (int j = 0; j < pos; j++) {
					found = 0;
					if (result->mat[j].getRow() == addend->mat[i].getRow() &&
						result->mat[j].getCol() == addend->mat[i].getCol()) {
						found = 1;
						break;
					}
				}
				//to insert the values that are in addend but not in result matrix
				if (found == 0) {
					result->setValue(pos, addend->mat[i].getRow(), addend->mat[i].getCol(), addend->mat[i].getValue());
					pos++;
				}
			}

			matrixClass* result1 = new matrixClass(this->getNumRows(), this->getNumCols(), pos);

			//to delete the non zero elements in the matrix
			for (int nonZero = 0; nonZero < pos; nonZero++)
				result1->setValue(nonZero, result->mat[nonZero].getRow(), result->mat[nonZero].getCol(), result->mat[nonZero].getValue());
			result1->matrixReorder();
			return result1;
			//delete result;
}

//to transpose the matrix
matrixClass* matrixClass::transpose()
{
	matrixClass* matrixT = new matrixClass(this->getNumCols(), this->getNumRows(),
		this->getNumNonZeros());

	for (int i = 0; i < this->getNumNonZeros(); i++)
	{
		int row = this->mat[i].getCol();
		int col = this->mat[i].getRow();
		int val = this->mat[i].getValue();

		matrixT->setValue(i, row, col, val);
	}

	//to reorder the SparseRow
	matrixT->matrixReorder();

	return matrixT;
}

//overloading << operator to display in matrix format
ostream& operator << (ostream& s, matrixClass& m) {
	m.displayMatrix();
	return s;
}

// main function
int main()
{
	int numRows, numCols, numNonZero;

	// read in all the numRows, numCols and numNonZero values from redirected input for matrix A
	cin >> numRows >> numCols >> numNonZero;

	// declare object for matrix A
	matrixClass* A = new matrixClass(numRows, numCols, numNonZero);

	// read in the values and use setValue to set the values read in for A
	int rowValue = 0, colValue = 0, val = 0;
	for (int i = 0; i < numNonZero; i++) {
		cin >> rowValue >> colValue >> val;
		try {
			//throwing the row out of bound if input row >= number of rows
			if (rowValue >= numRows) throw 'a';

			//throwing the column out of bound if input column >= number of columns
			if (colValue >= numCols) throw 2;

			A->setValue(i, rowValue, colValue, val);
		}
		//catching the rows out of bound error
		catch (char a) {
			cout << "Row Out of Bounce exception thrown–stopping execution" << endl;
			return 0;
		}
		//catching the rows out of bound error
		catch (int b) {
			cout << "Column Out of Bounce exception thrown –stopping execution" << endl;
			return 0;
		}
	}

	// display matrix A
	cout << "A in SparseRow format: " << endl;
	A->display();

	cout << "A in Matrix format: " << endl;
	cout << *A; // use ostream operator 

	// read in all the numRows, numCols and numNonZero values from redirected input for matrix B
	cin >> numRows >> numCols >> numNonZero;

	// declare object for matrix B
	matrixClass* B = new matrixClass(numRows, numCols, numNonZero);

	// read in the values and use setValue to set the values read in for B
	int rowValueB = 0, colValueB = 0, valB = 0;
	for (int i = 0; i < numNonZero; i++) {
		cin >> rowValueB >> colValueB >> valB;
		try {

			//throwing the row out of bound if input row >= number of rows
			if (rowValueB >= numRows) throw 'a';

			//throwing the column out of bound if input column >= number of columns
			if (colValueB >= numCols) throw 2;

			B->setValue(i, rowValueB, colValueB, valB);
		}
		//catching the rows out of bound error
		catch (char a) {
			cout << "Row Out of Bounce exception thrown–stopping execution" << endl;
			return 0;
		}
		//catching the columns out of bound error
		catch (int b) {
			cout << "Column Out of Bounce exception thrown –stopping execution" << endl;
			return 0;
		}
	}
	
	// display matrix A
	cout << "B in SparseRow format: " << endl;
	B->display();

	cout << "B in Matrix format: " << endl;
	cout << *B; // use ostream operator 


	// declare resultant matrix to store A * B
	try {
		//checking for matrix multipication
		//to throw the exception if number of columns of A is not equal to number of rows in B
		if (A->getNumCols() != B->getNumRows())
			throw 'e';

		matrixClass* resultMultiply = new matrixClass();
		resultMultiply = A->multiply(B);

		// display resultant matrix
		cout << "RESULT A*B in SparseRow format: " << endl;
		resultMultiply->display();

		cout << "RESULT A*B in Matrix format: " << endl;
		cout << *resultMultiply; // use ostream operator method
	}
	//to catch the exception if number of columns of A is not equal to number of rows in B
	catch (char e) {
		cout << "Matrix Dimension Mismatch for Multiplication exception thrown" << endl;
	}

	// declare resultant matrix to store A + B
	try{
			//to throw an exception if the number of rows of two matrices 
			//or number of columns of two matrices are different
			if (A->getNumRows() != B->getNumRows() ||
				A->getNumCols() != B->getNumCols())
				throw 20;

			//creating an object to store the result of addition
			matrixClass* resultAdd = new matrixClass();
			resultAdd = A->add(B);

			// display resultant matrix
			cout << "RESULT A+B in SparseRow format: " << endl;
			resultAdd->display();

			cout << "RESULT A+B in Matrix format: " << endl;
			cout << *resultAdd;// use ostream operator method
	}
	//to catch the exception if the number of rows of two matrices 
	//or number of columns of two matrices are different
	catch(int e) {
		cout << "Matrix Dimension Mismatch for Addition exception thrown." << endl;
	}

	// BONUS
	// declare resultant matrix to store transpose of A
	//matrixClass * resultTranspose = new matrixClass();
	//resultTranspose = A->transpose();


	// display resultant matrix
	//cout << "RESULT A^T in SparseRow format: " << endl;
	//resultTranspose->display();

	//cout << "RESULT A^T in Matrix format: " << endl;
	//cout << *resultTranspose;	//use ostream operator method
	//<"C:\Users\Bhavesh Kilaru\Desktop\computing structures\project2\input1.txt"

	return 0;
}