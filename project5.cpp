//// Fall 2021 Computing Structures
//// Project 5
//
#include<iostream>

using namespace std;

class Tree {
	friend ostream& operator<<(ostream& o, Tree& tree);	// ostream operator which prints the parent array
protected:
	int* parentArray;									// The parentArray that stores the parents of not i
	int _size;											// The size of the parentArray
public:
	Tree();												// Default Constructor
	Tree(int size);										// Non - Default constructor
	Tree(Tree& anotherTree);							// Copy Constructor
	~Tree();											// Destructor
	int getSize();										// Get the size of the parentArray
	int* getParentArray();								// Get the parentArray
	int LCA(int firstNode, int secondNode);				// Returns the least common ancestor given two nodes
	int parent(int i);									// Get the parent of node i
	void children(int i);								// Prints the children of node i	
	void siblings(int i);								// Prints the siblings of node i
	int root();											// Get the rood of the tree
	void setRoot(int rootNode);							// Set the root of the tree
	void setParent(int node, int parent);				// Set the parent of the node 
	void nodesAtLevel(int i);							// Give the nodes at level i
	int level(int i);									// Get the level of node i
	int height();										// Get the hight of the tree
	void preorder();									// Give the Preorder traversal of the tree

	void traversal(int root);
};

//default constructor
Tree::Tree() {
	//setting the size of the array to zero
	_size = 0;
}

//non default constructor
Tree::Tree(int n) {

	//setting the size of the array to given integer
	_size = n;

	//declaring a matrix of size int
	parentArray = new int[n];

	//initialising all the elements of the matrix(parent of all the elements) to -1
	for (int i = 0; i < n; i++)
		parentArray[i] = -1;
}

//copy constructor
Tree::Tree(Tree& anotherTree) {

	//initiatializing the size of new array with size of given array 
	_size = anotherTree.getSize();

	//copying the address of the first element of the input matrix to the given matrix
	parentArray = anotherTree.getParentArray();
}

//destructor
Tree::~Tree() {
	delete[]parentArray;
}

//getting the size of array
int Tree::getSize() {
	return _size;
}

//getting the parent array
int* Tree::getParentArray() {
	return parentArray;
}

//getting the least common ancestor
int Tree::LCA(int firstNode, int secondNode) {

	int value = -1, second = secondNode, first = firstNode;

	//to traverse from the first node to the root of the tree
	while (value == -1) {

		//to exit the loop when we reach the root of the tree
		if (first == -1)
			break;

		second = secondNode;

		//to traverse from the second node to the root of the tree 
		while (value == -1) {
			//cout << "first : " << first << " second: " << second << endl;

			//to exit the loop when we reach the root of the tree
			if (second == -1)
				break;

			//to get the common ancestor of the given two nodes
			if (first == second) {
				//cout << "Entered";
				value = first;
			}

			//initialising the second value to the parent of second
			second = this->parent(second);
		}

		//initialising the first value to the parent of first
		first = this->parent(first);
		//cout << "first " << first << " value " << value << endl;
	}
	return value;

}

//to get the parent of a node
int Tree::parent(int i) {
	if (i < getSize() && i >= 0)
		return parentArray[i];
	else
		return -1;
}

//to print the children of node i
void Tree::children(int parent) {
	if (parent < getSize() && parent >= 0) {
		for (int i = 0; i < _size; i++) {

			//to check if the parent of the elements of the matrix is the given node
			if (parentArray[i] == parent)
				cout << i << " ";
		}
		cout << endl;
	}
	else
		cout << "parent not found" << endl;
}

//to print sibblings
void Tree::siblings(int node) {
	if (node < getSize() && node >= 0) {
		// to get the parent of given node
		int parent = parentArray[node];

		for (int i = 0; i < _size; i++) {

			//to check if the parrent of any of the nodes in the tree 
			//is equal to the parent of the given node
			if (parentArray[i] == parent && i != node)
				cout << i << " ";
		}
		cout << endl;
	}

	else
		cout << "node not found " << endl;
}

//to get the the root of the tree
int Tree::root() {

	for (int i = 0; i < _size; i++) {

		//to check if the parent of any node in the tree is -1
		//since parent of the root node is -1
		if (parentArray[i] == -1) {
			return i;
			break;
		}
	}
}

//to set the root node
void Tree::setRoot(int rootNode) {
	parentArray[rootNode] = -1;
}

//to set the parents of nodes
void Tree::setParent(int node, int parent) {

	if(node < getSize() && node >= 0 && parent < getSize() && parent >= 0)
		//to set the parent of the given node
		parentArray[node] = parent;

}

//getting the level of particular node
int Tree::level(int i) {
	//to check if node exists in given tree
	if (i < getSize() && i >= 0) {
		int level = 1, node = i;

		//to traverse from node i till the root of the tree.
		while (parent(node) != -1) {
			node = parent(node);
			level++;
		}
		return level;
	}
	else
		return -1;
}

//getting the height of the tree
int Tree::height() {
	int max = 0, nodeHeight = 0;
	for (int i = 0; i < getSize(); i++) {

		//to find the heights of all the nodes
		nodeHeight = level(i);

		if (max < nodeHeight)
			max = nodeHeight;
	}
	return max;
}

//to get the nodes at particular level
void Tree::nodesAtLevel(int height) {
	int nodeHeight = 0;

	for (int i = 0; i < getSize(); i++) {

		//to get the height of the nodes
		nodeHeight = level(i);

		//if height of a node is equal to given height
		if (height == nodeHeight)
			cout << i << " ";
	}
	cout << endl;
}


//ostream operator
ostream& operator <<(ostream& o, Tree& tree) {

	for (int i = 0; i < tree.getSize(); i++) {

		//printing the nodes of the tree and their parents
		cout << i << ": " << tree.parent(i) << " ";
	}

	cout << endl;
	return o;
}

//preorder traversal of tree
void Tree::preorder() {
	int rt = root();

	//to traverse from the root
	traversal(rt);

}

void Tree::traversal(int root) {
	cout << root << " ";

	//to traverse from root the leaves
	for (int i = 0; i < getSize(); i++) {
		if (parentArray[i] == root) {
			traversal(i);
		}
	}

}

// main function
int main()
{
	int numNodes, numChildren, nodeNum, childNum; // you may use these or not

	// read in the number of nodes in the tree
	cin >> numNodes;

	// create object of class Tree
	Tree* myTree = new Tree(numNodes);

	// read in the information about each node and build the parent array 
	for (int i = 0; i < numNodes; i++) {

		//to read the number of children for a given node
		cin >> nodeNum >> numChildren;

		//to set the parent of the nodes
		for (int i = 0; i < numChildren; i++) {
			cin >> childNum;
			myTree->setParent(childNum, nodeNum);
		}
	}

	char option; // to read in the option

	//to read the values when needed
	int node1, node2, height = 0;

	// read in the options and switch based on the option

	while (!cin.eof()) {

		while (cin >> option) {

			//to display the tree
			if (option == 'D')
			{
				cout << "Parent Array of tree:" << endl;
				cout << *myTree;
			}

			//to display the root of the tree
			else if (option == 'O')
				cout << "Root of tree: " << myTree->root() << endl;

			//to display the height of the tree
			else if (option == 'H')
				cout << "Height of tree: " << myTree->height() << endl;

			//to display the parent of a given node
			else if (option == 'P')
			{
				cin >> node1;
				cout << "parent of " << node1 << ": " << myTree->parent(node1) << endl;
			}

			//to display the children of a given node
			else if (option == 'C')
			{
				cin >> node1;
				cout << "Children of " << node1 << ":" << endl;
				myTree->children(node1);
			}

			//to display the siblings of a given node
			else if (option == 'S')
			{
				cin >> node1;
				cout << "Siblings of " << node1 << ":" << endl;
				myTree->siblings(node1);
			}

			//to display the least common ancestor of the given two nodes
			else if (option == 'A')
			{
				cin >> node1 >> node2;
				cout << "LCA of " << node1 << " and " << node2 << ": " << myTree->LCA(node1, node2) << endl;
			}

			//to display the height of a given node
			else if (option == 'L')
			{
				cin >> node1;
				cout << "Level of " << node1 << ": " << myTree->level(node1) << endl;
			}

			//to display the nodes at a particular level
			else if (option == 'N')
			{
				cin >> height;
				cout << "Nodes at level " << height << ":" << endl;
				myTree->nodesAtLevel(height);
			}

			//to display the pre order traversal of the given tree
			else if (option == 'R') {
				cout << "Preorder traversal of tree: " << endl;
				myTree->preorder();
			}
		}

	}
	return 0;
}
