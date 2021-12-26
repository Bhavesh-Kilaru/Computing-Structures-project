////Computing Structures
////Fall 2021
////Project BONUS
////Author: Aditya Narasimhan

#include<iostream>
#include<cstdlib> // used for random number generation
#include<math.h> // used for math functions 
#include<unordered_set> // used for generating unique elements

using namespace std;

// bubble sort algorithm with D number of comparisons allowed
int* bubbleSort(int* arr, int numElements, int D)
{
    int numComp = 0; // used to count the number of comparisons and to check with D

    int* arrCopy = new int[numElements]; // making a copy of arr as this is an inplace sorting algorithm
                                        // we want to retain the ordering of arr for shell sort 
    for (int i = 0; i < numElements; i++)
        arrCopy[i] = arr[i];

    // bubble sort starts
    for (int i = 0; i < numElements; i++)
    {
        for (int j = 0; j < numElements - 1; j++)
        {
            numComp++; // incrementing the number of comparisons done right before 
                        // the if condition where the comparison happens each time
            if (numComp >= D) // checking for number of comparisons
                return arrCopy; // return the not necessarily sorted array = approximately sorted array

            if (arrCopy[j] > arrCopy[j + 1])
            {
                // swap
                int temp = arrCopy[j];
                arrCopy[j] = arrCopy[j + 1];
                arrCopy[j + 1] = temp;
            }
        }
    }
    // return the completely sorted array
    return arrCopy;
}

// shell sort algorithm with D number of comparisons allowed
int* shellSort(int* arr, int numElements, int D)
{
    int j;
    int numComp = 0;

    // need not make a copy of the arr array since shell sort is performed later/last

    // Start with a largest increment, then reduce by factors of 3 
    for (int inc = numElements / 3; inc > 1; inc /= 3)
    {
        // Insertion sort for the increment length
        for (int i = inc; i < numElements; ++i)
        {
            int temp = arr[i];
            j = i - inc;

            while ((j >= 0) && (arr[j] > temp))
            {
                numComp++; // incrementing the number of comparisons done right before 
                            // the if condition where the comparison happens each time
                if (numComp >= D) // checking for number of comparisons
                    return arr; // return the not necessarily sorted array = approximately sorted array
                arr[j + inc] = arr[j];
                j = j - inc;
            }
            arr[j + inc] = temp;
        }
    }
    // Insertion sort for the increment length = 1; force length 1 in case of inc/3 == 0
    for (int i = 1; i < numElements; ++i)
    {
        int temp = arr[i];
        j = i - 1;

        numComp++; // incrementing the number of comparisons done right before 
                    // the if condition where the comparison happens each time
        if (numComp >= D) // checking for number of comparisons
            return arr; // return the not necessarily sorted array = approximately sorted array

        while ((j >= 0) && (arr[j] > temp))
        {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = temp;
    }
    return arr;
}

//main function
int main()
{
    int n;
    cin >> n; // read the number of elements
    cout << "Number of elements: " << n << endl;

    int s, l, u, D;

    cin >> s >> l >> u >> D; // read the seed, lower range, upper range and the number of comparisons
    cout << "Number of comparisons allowed: " << D << endl;
    cout << endl;

    // generate n random elements with the seed s, within the lower and upper range 
    // store the randomly generated UNIQUE set of elements in an array 'A'
    srand(s);
    unordered_set<int> Unique_set;
    while(Unique_set.size() != n)
    {
        int random = l + (rand() % (u - l + 1));
        Unique_set.insert(random);

    }
    // you may use the unordered set to help generate unique elements

    cout << "Randomly generated elements: ~~~~~~~~~~" << endl;
    // display the array A
    int size = Unique_set.size(), i = 0;
    int* array = new int[size];
    for (const int& x : Unique_set) {
        array[i] = x;
        cout << array[i] << " ";
        i++;
    }
    cout << endl << endl;

    // use one of the sorting algorithms with the third argument for D as n*n (for bubble sort) and store the fully sorted result 

    int* sorted_array = new int[size];
    sorted_array = bubbleSort(array, size, size * size);

    cout << "Completely sorted elements: ~~~~~~~~~~" << endl;
    // display the completely sorted array 
    for (int j = 0; j < size; j++)
        cout << sorted_array[j] << " ";
    cout << endl << endl;

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // sort the array A with only given D comparions using the Bubble Sort algorithm and store the output array as bubResult in an array
    // calculate and display the two quality measures for bubResult
    cout << "Bubble Sort Result: ~~~~~~~~~~" << endl;
    int* buble_sort = new int[size];
    buble_sort = bubbleSort(array, size, D);

    // display bubResult
    for (int j = 0; j < size; j++)
        cout << buble_sort[j] << " ";
    cout << endl << endl;

    // find both the quality metrics for bubResult
    //Number of inversions for Bubble sort result
    cout << "Number of inversions in bubResult: ";
    int bub_inversions = 0;
    for (int j = 0; j < size; j++)
    {
        for (int k = j + 1; k < size; k++)
        {
            if (buble_sort[j] > buble_sort[k])
                bub_inversions++;
        }
    }
    cout << bub_inversions << endl;

    //Chebyshev distance for Bubble sort
    cout << "Chebyshev distance in bubResult: ";
    unordered_set<int> cheb_buble;
    int max_bub = 0;
    for (int j = 0; j < size; j++)
    {
        if (buble_sort[j] != sorted_array[j])
        {
            for (int k = 0; k < size; k++)
            {
                if (buble_sort[j] == sorted_array[k])
                {
                    int dif = abs(j - k);
                    if (max_bub < dif)
                        max_bub = dif;
                    cheb_buble.insert(dif);
                }
            }
        }
    }
    cout << max_bub << endl << endl;

    // ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

    // sort the array A with only given D comparions using the Shell Sort algorithm and store the output array as shellResult in an array
    // calculate and display the two quality measures for shellResult
    cout << "Shell Sort Result: ~~~~~~~~~~" << endl;
    int* shell_sort = new int[size];
    shell_sort = shellSort(array, size, D);

    // display shellResult
    for (int j = 0; j < size; j++)
        cout << shell_sort[j] << " ";
    cout << endl << endl;

    // find both the quality metrics for shellResult
    //number of inversions for Shell sort
    cout << "Number of inversions in shellResult: ";
    int shell_inversions = 0;
    for (int j = 0; j < size; j++)
    {
        for (int k = j + 1; k < size; k++)
        {
            if (shell_sort[j] > shell_sort[k])
                shell_inversions++;
        }
    }
    cout << shell_inversions << endl;
    
    //Chebyshev distance for Shell sort
    cout << "Chebyshev distance in shellResult: ";
    int max_shell = 0;
    for (int j = 0; j < size; j++)
    {
        if (shell_sort[j] != sorted_array[j])
        {
            for (int k = 0; k < size; k++)
            {
                if (shell_sort[j] == sorted_array[k])
                {
                    int dif = fabs(j - k);
                    if (max_shell < dif)
                        max_shell = dif;
                }
            }
        }
    }
    cout << max_shell << endl << endl;

    return 0;
}
