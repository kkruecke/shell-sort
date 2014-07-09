/* 
 * File:   main.cpp
 * Author: kurt
 *
 * Created on July 9, 2014, 8:13 AM
 */

#include <cstdlib>
#include "shell-sort.h"
#include<iostream>
#include<ctime>
#include<cstdlib>
#include<string>
#include <cmath>

using namespace std;

int main(int argc, char** argv) 
{
    int size = 70000;
    srand(0);

    if (argc > 1) {

	size = atoi(argv[argc-1]);
    }
   
    /* 
     * Allocate memory for int array of dimensions data[8][size] into which
     * we put random ints
     */
    int tests = 8;
    
    int** data = new int *[tests];
    
    for (int i = 0; i < tests; i++) {

	data[i] = new int[size];
    }

    for (int i = 0; i < size; i++) {

	data[0][i] = rand();
	    
	for (int j = 1; j < tests; j++) {

	     data[j][i] = data[0][i];
        }
    }
    
    cout << "Base number of adjacent inversions: " << count_inversions(data[0], size) << endl;
    
    time_t before, after;

    double diff;
    
    /*** INSERTION SORT ***/
    // time and sort it
    if (size < 100) {

	 cout << "Before: ";
	 print(data[5], size);
    }

    before = time(NULL);

    //	shellsort_pass(data[5], size, 1);
    after = time(NULL);

    diff = difftime(after, before);

    if (count_inversions(data[5], size) > 0) {

	    cerr << "Insertion sort failed test" << endl;
    }

    cout << "Insertion sort: " << diff << "s" << endl;

    if (size < 100) {

       cout << "After: ";
      print(data[5], size);
    }

    /*** INSERTION WITH SINGLE-PASS SHELL ***/
    // time and sort it
    if (size < 100) {
 
	cout << "Before: ";
	print(data[6], size);
    }

    before = time(NULL);

    //	shellsort_motivation(data[6], size);
    after = time(NULL);

    diff = difftime(after, before);

    if (count_inversions(data[6], size) > 0) {

	cerr << "Insertion sort with shell first-pass failed test" << endl;
    } 

    cout << "Insertion sort with h=N/3 first-pass: " << diff << "s" << endl;

    if (size < 100) {

	cout << "After: ";
	print(data[6], size);
    }

    /*** SHELL INCREMENTS ***/
    if (size < 100) {

	cout << "Before: ";
	print(data[1], size);
    }

    before = time(NULL);

    shellsort_shell(data[1], size);

    after = time(NULL);

    diff = difftime(after, before);

    if (count_inversions(data[1], size) > 0)
	    cerr << "Shellsort (shell) failed test" << endl;

    cout << "Shellsort (shell): " << diff << "s" << endl;

    if (size < 100) {

	 cout << "After: ";
	 print(data[1], size);
    }

    /*** HIBBARD INCREMENTS (MARSENNE) ***/
    if (size < 100) {

        cout << "Before: ";
	print(data[2], size);
    }

    before = time(NULL);

    shellsort_hibbard(data[2], size);

    after = time(NULL);

    diff = difftime(after, before);

    if (count_inversions(data[2], size) > 0) {
	    cerr << "Shellsort (hibbard) failed test" << endl;
    }

    cout << "Shellsort (hibbard): " << diff << "s" << endl;

    if (size < 100) {

	cout << "After: ";
	print(data[2], size);
    }

    /*** KNUTH INCREMENTS ***/
    if (size < 100) {

	cout << "Before: ";
	print(data[3], size);
    }
    before = time(NULL);

    shellsort_knuth(data[3], size);

    after = time(NULL);

    diff = difftime(after, before);

    if (count_inversions(data[3], size) > 0) {

	    cerr << "Shellsort (knuth) failed test" << endl;
    } 

    cout << "Shellsort (knuth): " << diff << "s" << endl;

    if (size < 100) {

	cout << "After: ";
	print(data[3], size);
    }
    
    /*** SEDGEWICK INCREMENTS ***/
    if (size < 100) {

	 cout << "Before: ";
	 print(data[4], size);
    }
    before = time(NULL);

    shellsort_sedgewick(data[4], size);

    after = time(NULL);

    diff = difftime(after, before);

    if (count_inversions(data[4], size) > 0) {

	    cerr << "Shellsort (sedgewick) failed test" << endl;
    } 

    cout << "Shellsort (sedgewick): " << diff << "s" << endl;

    if (size < 100) {
	    cout << "After: ";
	    print(data[4], size);
     }

    return 0;
}

