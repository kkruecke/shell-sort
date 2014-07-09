/* 
 * File:   shell-sort.h
 */

#ifndef SHELL_SORT_H
#define	SHELL_SORT_H

#include <iterator>
#include <iostream>
#include <cmath>

// returns the number of inversions in the array (just for double-checking)
template <class T>
int count_inversions(T* data, int size)
{
    int count = 0;

    for (int i = 0; i < size - 1; i++) {

        if (data[i + 1] < data[i]) {
    	    count++;
        } 
    }
    return count;
}


// displays the array (just for double-checking)
template <class T>
void print(const T* data, int size)
{
    std::ostream_iterator<T> out_it (std::cout,", ");
    std::copy ( data, data + size, out_it );
    std::cout << std::endl; 
}
/*
 * Basic first stab - good on many inputs, very very bad if size is a power of two
 * Funny aside - if size is one less than a power of two, performance is fine!
 */
template <class T>
void shellsort_shell(T* data, int size)
{
  int j;

  for (int h = size / 2; h > 0; h /= 2) {

     std::cout << "h = " << h << std::endl;

     for (int i = h; i < size; i++)  {
     
       // insert element i into the slice data[i-h], data[i-2h], ...
       T temp = data[i];
     
       for (j = i; j-h >= 0 && temp < data[j-h]; j -= h)  {
     
	     data[j] = data[j-h];
       }
     
       data[j] = temp;
     }
   }
}

/*
 * bad idea for increments - h(i) = 2^i
 * The odds and evens will never be merged until the last phase.
 * Can construct input for which this takes O(n^2).
 */
template <class T>
void shellsort_bad(T* data, int size)
{
   int j;
   
   // determine the largest 2^i we can use
   int base;

   for (base = 1; base < size; base *= 2);

   base /= 2;
   
   for (int h = base; h > 0; h /= 2) {

        std::cout << "h = " << h << std::endl;

        for (int i = h; i < size; i++) {

      	// insert element i into the slice data[i-h], data[i-2h], ...
      	T temp = data[i];
      	     
      	for (j = i; j-h >= 0 && temp < data[j-h]; j -= h) {

      		     data[j] = data[j-h];
              }
      	     
      	data[j] = temp;
        }
   }
}

/*
 * increment sequence is Mersenne numbers (2^i - 1).  Also called Hibbard's increments.
 * For some reason, mathy people seem to like Mersenne primes (i.e., Mersenne numbers
 * that are also prime).  There are some interesting things about them on Wikipedia.
 *
 * With this increment sequence, it's O(n^(3/2))
 */
template <class T>
void shellsort_hibbard(T* data, int size)
{
     int j;
     
     // determine the increment sequence - marsenne numbers (2^x - 1)
     // the loop is just finding the value of x we should start at
     int x;
     
     for (x = 1; pow(2.0, x) - 1 < size; x++);
     
     x--;
     
     for (; x > 0; x--) {

	  int h = pow(2.0, x) - 1;
     
	  std::cout << "h(" << x <<  ") = " << h << std::endl;
     
	  for (int i = h; i < size; i++) {

	      // insert element i into the slice data[i-h], data[i-2h], ...
	      T temp = data[i];
		     
	      for (j = i; j-h >= 0 && temp < data[j-h]; j -= h) {

	          data[j] = data[j-h];
              } 
		     
	      data[j] = temp;
	  }
      }
}
         
/*
 * does one pass of shell sort.  Call with i = 1 to do insertion sort.
*/
template <class T>
inline void shellsort_pass(T* data, int size, int h)
{
  int j;

  for (int i = h; i < size; i++) {

      // insert element i into the slice data[i-h], data[i-2h], ...
      T temp = data[i];
        
      for (j = i; j - h >= 0 && temp < data[j-h]; j -= h) {

	    data[j] = data[j-h];
      }
             
      data[j] = temp;
  }
}
 
/*
 * Knuth's increment sequence h = 3*h+1
 * Note: the reason dividing by three in the main loop works
 * is cause it's integer arithmetic so it truncates.
 *
 * This is also O(n^(3/2))
 */
template <class T>
void shellsort_knuth(T* data, int size)
{
    int j;
    
    // find the initial value of h (the biggest one smaller than N)
    // note:  Sedgewick book uses stopping condition h <= (size-1)/9 but it doesn't benefit much
    int h;

    for (h = 1; h < size; h = 3*h + 1);

    h /= 3;

    for (; h > 0; h /= 3) {

	std::cout << "h = " << h << std::endl;

	for (int i = h; i < size; i++)   {

	   // insert element i into the slice data[i-h], data[i-2h], ...
	   T temp = data[i];
		    
	   for (j = i; j-h >= 0 && temp < data[j-h]; j -= h) {

		data[j] = data[j-h];
           }
		    
	   data[j] = temp;
	}
     }
}
    
/*
 * Sedgewick's increment sequence h(j) = 4^(j+1) + 3*2^j + 1 for some j
 * Note that h(0) = 8, so you have to manually do something like h(-1) = 1
 *
 * The runtime is O(n^(4/3))
 */
template <class T>
void shellsort_sedgewick(T* data, int size)
{
  int j, x;
      
  // find the value of x that oversteps N and backtrack one
  for (x = 0; pow(4.0, x+1) + 3*pow(2.0, x) + 1 < size; x++);

  x--;

  int h;

  for (; x >= -1; x--) {

     if (x == -1) {

       	h = 1;

     } else {

        h = pow(4.0, x+1) + 3*pow(2.0, x) + 1;
     }
  	    
     std::cout << "h(" << x << ") = " << h << std::endl;
  	    
     // can just as easily write all these increment sequences with a call to an h-sort
     shellsort_pass(data, size, h);
  }
}
       
/*
 * just doing an h=N/3 pass before insertion sort as an example
 */
template <class T>
void shellsort_motivation(T* data, int size)
{
    if (size >= 6) {

    	 shellsort_pass(data, size, size/3);
    } 

    shellsort_pass(data, size, 1);
}

/*
 * an example of faster growth, but worse performance
 */
template <class T>
void shellsort_fifths(T* data, int size)
{
   for (int h = size / 5; h > 0; h /= 5) {

        shellsort_pass(data, size, h);
   }
}

#endif
