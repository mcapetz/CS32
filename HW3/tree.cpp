//
//  main.cpp
//  tree
//
//  Created by Margaret Capetz on 2/5/22.
//

#include <iostream>
#include <cassert>

using namespace std;

//(Hint: Using the separate function, the order function can be written in fewer than eight short lines of code.)

//Consider all operations comparing two doubles (e.g. <=, ==, etc.) that a function performs. You will not receive full credit if for nonnegative n2 and n1 >= n2, the countContains function causes operations like these to be called more than factorial(n1+1) / (factorial(n2)*factorial(n1+1-n2)) times. The countContains function can be implemented in a way that meets the spec without calling any of the functions in problem 2. (If you implement it so that it does call one of those functions, then it will probably not meet the limit stated in this paragraph.)


// Return the number of ways that all n2 elements of a2 appear in
      // the n1 element array a1 in the same order (though not necessarily
      // consecutively).  The empty sequence (i.e. one where n2 is 0)
      // appears in a sequence of length n1 in 1 way, even if n1 is 0.
      // For example, if a1 is the 7 element array
      //        10 50 40 20 50 40 30
      // then for this value of a2     the function must return
      //        10 20 40                        1
      //        10 40 30                        2
      //        20 10 40                        0
      //        50 40 30                        3
    int countContains(const double a1[], int n1, const double a2[], int n2)
    {
        if(n1 == 0 && n2 != 0) return 0;
        if(n2 == 0) return 1;
        if(a1[0] == a2[0]) return countContains(a1+1, n1-1, a2, n2) + countContains(a1+1, n1-1, a2+1, n2-1);
        else return countContains(a1+1, n1-1, a2, n2);
    }

      // Exchange two doubles
    void exchange(double& x, double& y)
    {
        double t = x;
        x = y;
        y = t;
    }

      // Rearrange the elements of the array so that all the elements
      // whose value is > separator come before all the other elements,
      // and all the elements whose value is < separator come after all
      // the other elements.  Upon return, firstNotGreater is set to the
      // index of the first element in the rearranged array that is
      // <= separator, or n if there is no such element, and firstLess is
      // set to the index of the first element that is < separator, or n
      // if there is no such element.
      // In other words, upon return from the function, the array is a
      // permutation of its original value such that
      //   * for 0 <= i < firstNotGreater, a[i] > separator
      //   * for firstNotGreater <= i < firstLess, a[i] == separator
      //   * for firstLess <= i < n, a[i] < separator
      // All the elements > separator end up in no particular order.
      // All the elements < separator end up in no particular order.
    void separate(double a[], int n, double separator,
                        int& firstNotGreater, int& firstLess)
    {
        if (n < 0)
        n = 0;
    
          // It will always be the case that just before evaluating the loop
          // condition:
          //  firstNotGreater <= firstUnknown and firstUnknown <= firstLess
          //  Every element earlier than position firstNotGreater is > separator
          //  Every element from position firstNotGreater to firstUnknown-1 is
          //    == separator
          //  Every element from firstUnknown to firstLess-1 is not known yet
          //  Every element at position firstLess or later is < separator
    
        firstNotGreater = 0;
        firstLess = n;
        int firstUnknown = 0;
        while (firstUnknown < firstLess)
        {
        if (a[firstUnknown] < separator)
        {
            firstLess--;
            exchange(a[firstUnknown], a[firstLess]);
        }
        else
        {
            if (a[firstUnknown] > separator)
            {
            exchange(a[firstNotGreater], a[firstUnknown]);
            firstNotGreater++;
            }
            firstUnknown++;
        }
        }
    }

      // Rearrange the elements of the array so that
      // a[0] >= a[1] >= a[2] >= ... >= a[n-2] >= a[n-1]
      // If n <= 1, do nothing.
    void order(double a[], int n)
    {
        //write with fewer than 8 lines with separate()
        return;  // This is not always correct.
    }


int main(int argc, const char * argv[]) {
    double arr[7] = {10, 50, 40, 20, 50, 40, 30};
    double arr0[0] = {};
    double arr1[3] = {10, 20, 40};
    double arr2[3] = {10, 40, 30};
    double arr3[3] = {20, 10, 40};
    double arr5[3] = {50, 40, 30};
    
    assert(countContains(arr, 7, arr0, 0) == 1);
    assert(countContains(arr, 7, arr1, 3) == 1);
    assert(countContains(arr, 7, arr2, 3) == 2);
    assert(countContains(arr, 7, arr3, 3) == 0);
    assert(countContains(arr, 7, arr5, 3) == 3);
    
    
    
    cout << "passed all tests" << endl;
    
}
