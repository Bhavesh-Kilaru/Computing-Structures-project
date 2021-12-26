////Computing Structures
////Fall 2021
////Project 6
////Author: Aditya Narasimhan
//
#include <iostream>
#include <queue> // for BFS

using namespace std;

class CSR {
protected:
	int n; //The number rows of the original matrix
	int nonZeros; //The number of non-zeros in the original matrix
	int* rowPtr; //Array that contains number of non-zero elements in each row of the original matrix
	int* colPos; //Array that contains the column number from the original matrix for the non-zero values.

	int rowIndex; //maybe used for building the CSR data structure
	int colIndex; //maybe used for building the CSR data structure

public:
	CSR(); //default constructor
	CSR(const CSR& csrToCopy); //Copy Constructor
	CSR(int rows, int numNonZeros); //Non-default Constructor
	~CSR(); //destructor
	int getNumRows(); //get n
	int getNonZero(); //get nonZeros
	int getRowPtr(int i); //get rowPtr at index i
	int getColPos(int i); //get colPos at index i
	void addColumn(int col); //add a column in the colPos array
	void addRow(int row); //add a row in the rowPtr array
	void display(); //print the contents of the 2 arrays and the matrix
	int getEdge(int row, int col); //return an edge existent (1 or 0)
	int triangleCount(); //count the number of triangles and return it
	void DFS(int startNode, int* visited); //print the nodes in DFS ordering; visited is an array for recursive implementation
	void BFS(int startNode); //print the nodes in BFS ordering

	//You may have other methods
	int numOfNeighbours(int node);
};

//default constructor
CSR::CSR() {
	n = 0;							//initializing the number of elements in the graph to 0
	nonZeros = 0;					//intialising the number of non zero elements in adjacency matrix to 0 
}

//copy constructor
CSR::CSR(const CSR& csrToCopy) {
	
	//initializing the number of rows of the new object to the number of rows in the csrToCopy 
	this->n = csrToCopy.n;

	//initializing the number of non zero elements of the new  object to the number of non zero elements in the csrToCopy 
	this->nonZeros = csrToCopy.nonZeros;

	//copying the address of rowPtr of csrToCopy object into rowPtr of the new object
	this->rowPtr = csrToCopy.rowPtr;

	//copying the address of colPos of csrToCopy object into colPos of the new object
	this->colPos = csrToCopy.colPos;
}

//non default constructor
CSR::CSR(int rows, int numNonZeros) {
	//intializing the number of rows in the adjacency matrix or nodes in the graph
	n = rows;

	//intializing the number of non zero elements in the adjacency matrix
	nonZeros = numNonZeros;				

	//declaring a matrix of length "rows" to store the  the number of 1s in a specific row
	rowPtr = new int[rows];				

	//intializing the rowIndex to zero so it can be used while inserting elements in rowPtr matrix
	rowIndex = 0;

	//declaring a matrix of length numNonZeros to store  column number of the value 1 present in adjacency matrix
	colPos = new int[numNonZeros];		

	////intializing the colIndex to zero so it can be used while inserting elements in colPos matrix
	colIndex = 0;						
}


//destructor
CSR::~CSR() {

}

//getter for the number of nodes in the graph
int CSR::getNumRows() {
	return n;
}

//getter for number of non zeros in the adjacency matrix
int CSR::getNonZero() {
	return nonZeros;
}

//getters for the value at ith index in rowPtr matrix
int CSR::getRowPtr(int i) {
	return  rowPtr[i];
}

//getters for the value at ith index in colPos matrix
int CSR::getColPos(int i) {
	return colPos[i];
}

//setters for adding the col value to the colPos matrix
void CSR::addColumn(int col) {

	//checking whether the input node is in the given list
	if (col <= this->getNumRows())
	{
		colPos[colIndex] = col;
		colIndex++;
	}
	else
		cout << "Input col out of bounds for colPos matrix" << endl;
}

//setters for adding Row to rowPtr matrix
void CSR::addRow(int Row) {
	
	//checking if the given input is in the limits of non zero elements in the matrix
	if (Row <= this->getNonZero())
	{
		rowPtr[rowIndex] = Row;
		rowIndex++;
	}
	else
		cout << "input value out of bounds for rowPtr matix " << endl;
}

//to display the adjacency matrix
void CSR::display() {

	//to traverse over the number of rows
	for (int row = 0; row < getNumRows(); row++)
	{

		//to traverse over the columns
		for (int col = 0; col < getNumRows(); col++)
		{
			//to print the edge between the row node and column node
			//getEdge returns 1 if a node exists between the two nodes else it returns 0
			cout << this->getEdge(row, col) << " ";
		}
		cout << endl;
	}

	//printing the rowptr matrix
	cout << "rowPtr: ";
	for (int i = 0; i < this->getNumRows(); i++)
		cout << this->getRowPtr(i) << " ";
	cout << endl;

	//printing the colPos matric
	cout << "colPos: ";
	for (int i = 0; i < this->getNonZero(); i++)
		cout << this->getColPos(i) << " ";
	cout << endl;
}

//to check if a node exists between the given two nodes
//returns 1 if a node exists between the two nodes else it returns 0
int CSR::getEdge(int row, int column) {
	int neighbour = 0;

	//to check if the node exists in the graph
	if (row < getNumRows() && column < getNumRows()) {
		
		//to get the number of neighbours for the row node
		int dif = this->numOfNeighbours(row);

		//to get the number of neighbours of the the node "row
		for (int i = getRowPtr(row); i < getRowPtr(row) + dif; i++) {

			//to set the value when "column" is a neighbour of "row"
			if (getColPos(i) == column)
			{
				neighbour = 1;
				break;
			}
		}
	}
	return neighbour;
}

//to get the number of triangles in the given graph
int CSR::triangleCount() {

	int triCount = 0;

	//to traverse through all the nodes in the graph
	//let it be first node
	for (int firstNode = 0; firstNode < getNumRows(); firstNode++)
	{
		int dif1, dif2;

		//to get the number of neighbours for the first node
		dif1 = this->numOfNeighbours(firstNode);

		//to traverse over the neighbours of a node
		//let it be second node
		for (int i = getRowPtr(firstNode); i < getRowPtr(firstNode) + dif1; i++)
		{
			int secondNode = getColPos(i);

			//to get the number of neighbours for the second node
			dif2 = this->numOfNeighbours(secondNode);

			//to get the neighbours of the second node
			//let it be third node
			for (int j = getRowPtr(secondNode); j < getRowPtr(secondNode) + dif2; j++) {
				int thirdNode = getColPos(j);

				//to check if third node is also a neighbour of first node
				if (this->getEdge(firstNode, thirdNode) && (firstNode < secondNode) && (secondNode < thirdNode))
					triCount++;
				
			}
		}
	}
	return triCount;
}

//depth first search algorithm
void CSR::DFS(int startNode, int* visited) {
	
	int dif;

	//to check if the node is already visited
	if (visited[startNode] == 0)
	{

		//marking the node as visited
		visited[startNode] = 1;

		//printing the visited node
		cout << startNode << " ";

		//to get the number of neighbours for the startNode
		dif = this->numOfNeighbours(startNode);

		//to traverse over all the neigbours of first node
		for (int i = getRowPtr(startNode); i < getRowPtr(startNode) + dif; i++) {
			int neighbour = getColPos(i);

			//caluculating the DFS algorithm for the neighbours of first node
			DFS(neighbour, visited);
		}
	}

}

//breadth for search algorithm
void CSR::BFS(int startNode) {

	//declaring queue
	queue<int>* q = new queue<int>[getNumRows()];

	//declaring the matrix
	//this helps in checking whether a node is already visited
	int* found = new int(getNumRows());
	for (int i = 0; i < getNumRows(); i++)
		found[i] = 0;								//initializing all the elements of found matrix to zero
	int dif;

	//pushing the start node into the queue
	q->push(startNode);

	//to empty the queue
	while (!q->empty()) {

		//getting the first element in the queue
		int element = q->front();
		found[element] = 1;
		
		//getting the number of neigbours of the first element in queue
		dif = this->numOfNeighbours(element);

		//getting the neighbours of the first element in queue
		for(int i = getRowPtr(element); i < getRowPtr(element) + dif; i++) {
			int element2 = getColPos(i);

			//checking if the neighbour had already been visited
			if (found[element2] == 0)
			{
				//pushing the neighbour into queue if not visited
				q->push(getColPos(i));

				//marking that neighbour node as visited
				found[element2] = 1;
			}
		}

		//poping and printing the first element from queue
		cout << element << " ";
		q->pop();
	}

}

//to get the number of neighbours of an element
int CSR::numOfNeighbours(int node) {

	int dif = 0;

	//to get the number of neighbours for the node if it has the highest value
	if (node + 1 == getNumRows())
		dif = getNonZero() - getRowPtr(node);

	//to get the number of neighbours for the node if its value is other than the highest value
	else
		dif = getRowPtr(node + 1) - getRowPtr(node);

	return dif;
}

int main() {

	int numRows, numNonZeros, count = 0; //maybe used or not
	int row, col, value, startNode = 0;

	//read in the first matrix
	cin >> numRows >> numNonZeros;

	//object A of CSR
	CSR* A;
	A = new CSR(numRows, numNonZeros);

	//to traverse over all the nodes(rows)
	for (row = 0; row < A->getNumRows(); row++) {
		A->addRow(count);								//insertion into the rowPtr matrix
		for (col = 0; col < A->getNumRows(); col++) {
			cin >> value;
			if (value != 0) {
				A->addColumn(col);							//insertion of a neigbour of "row" node in colPos matrix
				count++;									//for the number of neighbours of the "row" node
			}
		}
	}

	//display mat A
	cout << "Matrix A:" << endl;
	(*A).display();

	//triangle counting
	int numTri = A->triangleCount();
	cout << "Number of Triangles: " << numTri << endl;

	//TODO: start node
	//TODO: initialize visited array to 0
	cin >> startNode;

	//BFS
	cout << "BFS ordering: ";
	//TODO: call BFS()
	A->BFS(startNode);
	cout << endl;

	//DFS
	cout << "DFS ordering: ";
	//TODO: call DFS()
	//declaring a matrix to check if a node have been visited as a part of DFS
	int* visited = new int[A->getNumRows()];
	for (int i = 0; i < A->getNumRows(); i++)
		//marking all the elements as not visyed
		visited[i] = 0;
	A->DFS(startNode, visited);
	cout << endl;

	//TODO: Call the destructors
	delete A;

	return 0;
}
