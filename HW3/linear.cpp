//
//  main.cpp
//  linear
//
//  Created by Margaret Capetz on 2/3/22.
//

#include <iostream>
#include <cassert>
using namespace std;

bool somePredicate(double x)
    {
        return x < 0;
    }


// Return true if the somePredicate function returns false for at
    // least one of the array elements, false otherwise.
  bool anyFalse(const double a[], int n)
  {
      if(n == 0) return false;
      if(!somePredicate(a[0])) return true;
      return anyFalse(a+1, n-1);
  }

    // Return the number of elements in the array for which the
    // somePredicate function returns false.
  int countFalse(const double a[], int n)
  {
      
      if(n == 0) return 0;
      int total;
      total = countFalse(a+1, n-1);
      if(!somePredicate(a[0])) {
          total++;
      }
      return total;
  }

    // Return the subscript of the first element in the array for which
    // the somePredicate function returns true.  If there is no such
    // element, return -1.
  int firstTrue(const double a[], int n)
  {
      if(n == 0) return -1;
      if(somePredicate(a[0])) return 0;
      int pos = firstTrue(a+1, n-1);
      if(pos == -1) return -1;
      return 1 + pos;
  }

    // Return the subscript of the largest element in the array (i.e.,
    // return the smallest subscript m such that a[m] >= a[k] for all
    // k such that k >= 0 and k < n).  If there is no such subscript,
    // return -1.
  int locateMax(const double a[], int n)
  {
      if(n == 0) return -1;
      int pos = locateMax(a+1, n-1);
      //cout << a[0] << " pos: " << pos << endl;
      if(pos != 0 && a[0] >= a[pos])  {
          //cout << "i got here because " << a[0] << " >= " << a[pos] << endl;
          return 0;
      }
      if(pos == -1) return -1;
      return 1 + pos;
  }

    // If all n2 elements of a2 appear in the n1 element array a1, in
    // the same order (though not necessarily consecutively), then
    // return true; otherwise (i.e., if the array a1 does not contain
    // a2 as a not-necessarily-contiguous subsequence), return false.
    // (Of course, if a2 is empty (i.e., n2 is 0), return true.)
    // For example, if a1 is the 7 element array
    //    10 50 40 20 50 40 30
    // then the function should return true if a2 is
    //    50 20 30
    // or
    //    50 40 40
    // and it should return false if a2 is
    //    50 30 20
    // or
    //    10 20 20

  bool contains(const double a1[], int n1, const double a2[], int n2)
  {
      
      return false;  // This is not always correct.
  }


int main(int argc, const char * argv[]) {
    double arr[5] = {1, 2, 3, -5, -8};
    double arr1[0] = {}; //empty
    double arr2[1] = {1}; //single element
    double arr3[6] = {-1, -2, 3, 5, 6, -7};
    
    assert(anyFalse(arr, 5) == true);
    assert(anyFalse(arr1, 0) == false);
    assert(anyFalse(arr2, 1) == true);
    
    assert(countFalse(arr, 5) == 3);
    assert(countFalse(arr1, 0) == 0);
    assert(countFalse(arr2, 1) == 1);
    assert(countFalse(arr3, 6) == 3);
    
    assert(firstTrue(arr, 5) == 3);
    assert(firstTrue(arr1, 0) == -1);
    assert(firstTrue(arr2, 1) == -1);
    assert(firstTrue(arr3, 6) == 0);
    
    assert(locateMax(arr, 5) == 2);
    assert(locateMax(arr1, 0) == -1);
    assert(locateMax(arr2, 1) == 0);
    assert(locateMax(arr3, 6) == 4);
    
    cout << "passed all tests" << endl;
}
