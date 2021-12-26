#include <iostream>
#include <list>
#include <iterator>

using namespace std;

template <class DT>
class setArrayClass
{
protected:
	list<DT>* arrOfSets; // array of sets/lists
	int lengthOfArray; // length of the array / number of sets

public:
	setArrayClass(); // default constructor
	setArrayClass(int n); // non default constructor
	int getLength(); // get the number of sets / array length
	void setLength(int l); // set the length field with the l value
	list<DT> getSet(int i); // return A[i]
	void setValue(int setIndex, DT val); // set the value val in the setIndex position's set
	void display(); // display in the given format the array of sets

	list<DT> setUnion(list<DT> l1, int l); // find the union between set l1 and A[l] and return result
	list<DT> setIntersection(list<DT> l1, int l); // find the intersection between set l1 and A[l] and return result
	list<DT> setCompliment(int l); // find the compliment of A[l] and return that list

	// other methods necessary
	list<DT> DecideCompliment(int n);

};

//default constructor
template <class DT>
setArrayClass<DT>::setArrayClass() {
	setLength(0);
}

//constructor when an integer is passed
template<class DT>
setArrayClass<DT>::setArrayClass(int n) {
	setLength(n);
	arrOfSets = new list<DT>[n];
}

//to return the length of the array of lists
template<class DT>
int setArrayClass<DT>::getLength() {
	return lengthOfArray;
}

//to set the length of the array of lists
template<class DT>
void setArrayClass<DT>::setLength(int L) {
	lengthOfArray = L;
}

//to return the set that is at the ith position of array
template<class DT>
list<DT> setArrayClass<DT>::getSet(int i) {
	return arrOfSets[i];
}

//to insert  a value into the list that is at the ith position of the array
template<class DT>
void setArrayClass<DT>::setValue(int setIndex, DT val) {
	arrOfSets[setIndex].push_back(val);
}

//to display the array of lists
template<class DT>
void setArrayClass<DT>::display() {
	for (int i = 0; i < getLength(); i++) {
		cout << "A[" << i << "]: ";
		for (auto val : arrOfSets[i])
			cout << val << " ";
		cout << endl;
	}
}

//to decide whether to take original set or compliment set
template<class DT>
list<DT> setArrayClass<DT>::DecideCompliment(int l) {
	list<DT> set;

	//to get the set that is at the lth position of array
	if (l >= 0)
		set = this->getSet(l);

	//to get the complement of the set that is at the lth position of array when l is negative
	else
		set = this->setCompliment(0 - l);

	return set;

}

//to get the union of two arrays
template<class DT>
list<DT> setArrayClass<DT>::setUnion(list<DT> l1, int l) {
	list<DT> Union, set2;

	//to check whether to get the original set or compliment set
	set2 = this->DecideCompliment(l);

	//caluculationg Union
	//inserting the values of set1 iinto the Union set
	for (auto val : l1) {
		Union.push_back(val);
	}

	//to check if the values of set2 that are in set1
	for (auto val : set2) {
		int found = 0;
		for (auto val2 : Union) {
			if (val == val2) {
				found = 1;
				break;
			}
		}
		//inserting the values of set2 that are not in set1
		if (found == 0)
			Union.push_back(val);
	}
	return Union;
}

//to get the intersection of two sets
template <class DT>
list<DT> setArrayClass<DT>::setIntersection(list<DT> l1, int l) {
	list<DT> intersect, set2;

	//to check whether to get the original set or compliment set
	set2 = this->DecideCompliment(l);

	//to insert the common elements into intersection set
	for (auto val : l1) {
		for (auto val2 : set2) {
			if (val == val2)
				intersect.push_back(val);
		}
	}
	return intersect;
}

//to caluculate the complement of a set
template <class DT>
list<DT> setArrayClass<DT>::setCompliment(int n) {
	//list<DT> compl;
	list<DT> set, c;
	set = this->getSet(n);

	//checking if an element is present in the given set
	for (int i = 0; i <= 20; i++) {
		int found = 0;
		for (auto val : set) {
			if (i == val) {
				found = 1;
				break;
			}
		}
		
		//inserting into the complement set if given element is not in the given set
		if (found == 0)
			c.push_back(i);
	}
	return c;
}

int main()
{
	int numLists, numElements, expNum=0;
	char oper, oper2;
	int val1, val2;

	// read in the number of lists/array length and the number of total elements
	cin >> numLists >> numElements;

	// arr1 is the array of lists
	setArrayClass<int>* arr1 = new setArrayClass<int>(numLists);

	// read in the number pairs and insert the element to the specific set index
	for (int i = 0; i < numElements; i++)
	{
		// fill code here
		cin >> val1 >> val2;
		arr1->setValue(val1, val2);
	}

	// display the array of sets
	cout << "Input array of sets: " << endl;
	arr1->display();


	// read all the expressions to evaluate them and display the answer
	while (!cin.eof())
	{
		////// fill code here

		int val1 = 0, val2 = 0;

		//reading the first value into val1
		cin >> val1;

		//declaring lists
		list<int> out, temp;

		//getting the list at value val1 of the array of lists
		//to check if val1 is negative
		//if negative, getting the compliment of the set
		temp = arr1->DecideCompliment(val1);
		

		while (cin >> oper)
		{

			if (oper == ';')
			{
				//cout << "display answer" << endl;
				cout << endl;
				cout << "Expression " << ++expNum << ":" << endl;
				break;
			}

			// fill code here

			//getting the val2 after the operands
			cin >> val2;

			//to determine which operation should be made
			switch (oper) {

			//for union operation
			case '+': out = arr1->setUnion(temp, val2);
				temp = out;
				break;

			//for intersection
			case '*': out = arr1->setIntersection(temp, val2);
				temp = out;
				break;
			}
		}

		//printing the values in the final list
		for (auto val : out)
			cout << val << " ";
		cout << endl;

	}

	return 0;
}
