#include "sorting.h"
#include <cstdlib>
#include <iostream>
#include <ctime>
using namespace::std;
/**
 * Title: Algorithm Efficiency and Sorting
 * Author: Faaiz Ul Haque
 * ID: 21503527
 * Section: 2
 * Assignment: 1
 * Description: CPP file with implementation of the sorting algorithms taken from slides
 * Algorithms are modified to satisfy arguments given in sorting.h
 * CompCount and MoveCount increments are placed in between in the implementations
 */

//Insertion Sort Implementation From Slides
void insertionSort(int *arr, int size, int &compCount, int &moveCount)
{
  compCount = 0;
  moveCount = 0;
  for (int unsorted = 1; unsorted < size; ++unsorted)
  {

    int nextItem = arr[unsorted];
    moveCount++;

    int loc = unsorted;

    for (  ;(loc > 0) && (arr[loc-1] > nextItem); --loc)
    {
       compCount++;
       arr[loc] = arr[loc-1];
       moveCount++;
    }
    compCount++;

    arr[loc] = nextItem;
    moveCount++;
  }
}




//Merge Sort recursive helper function to merge once two halves are divided
void mergeHalves( int *arr, int first, int mid, int last, int &compCount, int &moveCount)
{

   int tempArray[last + 1]; 	// temporary array

   int first1 = first; 	// beginning of first subarray
   int last1 = mid; 		// end of first subarray
   int first2 = mid + 1;	// beginning of second subarray
   int last2 = last;		// end of second subarray
   int index = first1; // next available location in tempArray

   for ( ; (first1 <= last1) && (first2 <= last2); ++index)
   {
      compCount++;
      if (arr[first1] < arr[first2])
      {
         tempArray[index] = arr[first1];
         moveCount++;
         ++first1;
      }
      else {
          tempArray[index] = arr[first2];
          moveCount++;
          ++first2;
      }
   }
	// finish off the first subarray, if necessary
   for (; first1 <= last1; ++first1, ++index)
   {
      tempArray[index] = arr[first1];
      moveCount++;
   }

   // finish off the second subarray, if necessary
   for (; first2 <= last2; ++first2, ++index)
   {
      tempArray[index] = arr[first2];
      moveCount++;
   }

   // copy the result back into the original array
   for (index = first; index <= last; ++index)
   {
      arr[index] = tempArray[index];
      moveCount++;
   }

}  // end mergeHalves

//Merge sort helper function to divide array into two halves
void divide( int * arr, int first, int last, int &compCount, int &moveCount)
{

	if (first < last)
    {

      int mid = (first + last)/2; 	// index of midpoint

      divide(arr, first, mid, compCount, moveCount);

      divide(arr, mid+1, last, compCount, moveCount);

      // merge the two halves
      mergeHalves(arr, first, mid, last, compCount, moveCount);
   }
}  // end divide


//Merge sort implementation
void mergeSort( int *arr, int size, int &compCount, int &moveCount )
{
    compCount = 0;
    moveCount = 0;
    divide(arr, 0, size - 1, compCount, moveCount);
}




//Swap function for elements for quicksort algorithm
void swapElements( int &x, int &y)
{
   int temp = x;
   x = y;
   y = temp;
}

//Quick sort helper function used to partition array
//Pivot is chosen as the last element, from slides with minor edits
void partitioning( int * arr, int first, int last, int &pivot, int &compCount, int &moveCount )
{
   int pivotPoint = arr[last];
   moveCount++;
   arr[last] = arr[first];
   moveCount++;
   arr[first] = pivotPoint;

   int s1 = first;
   int tempIndex = first + 1;

   for ( ; tempIndex <= last; tempIndex++ )
   {
       compCount++;
       if ( arr[tempIndex] < pivotPoint )
       {
          s1++;
          swapElements( arr[tempIndex], arr[s1] );
          moveCount = moveCount + 3;
       }
   }
   moveCount += 3;
   swapElements( arr[first], arr[s1]);
   pivot = s1;
}

//Quick sort helper function
void quick( int * arr, int first , int last,   int &compCount,   int &moveCount )
{
   int pivotIndex;

   if ( first < last )
   {
        //Create the partition
        partitioning( arr, first, last, pivotIndex, compCount, moveCount );
        //Sort regions s1 and s2
        quick( arr, first, pivotIndex - 1, compCount, moveCount );
        quick( arr, pivotIndex + 1, last, compCount, moveCount );
   }
}

void quickSort(int *arr, int size, int &compCount, int &moveCount)
{
    moveCount = 0;
    compCount = 0;
    quick( arr, 0, size - 1, compCount, moveCount );
}





void performanceAnalysis()
{
    int sizes[5] = {1000, 5000, 10000, 15000, 20000};
    int compCount = 0;
    int moveCount = 0;
    int temp = 0;


    cout << "-------------------------------------------------------" << endl;
    cout << "Part b1 - Performance analysis of random integers array" << endl;
    cout << "-------------------------------------------------------" << endl;
    for ( int j = 0; j <= 4; j++)
    {
        int insertArr[sizes[j]];
        int mergeArr[sizes[j]];
        int quickArr[sizes[j]];

        //Random Array
        for ( int i = 0; i < sizes[j]; i++ )
        {
            temp = rand()%sizes[j];
            insertArr[i] = temp;
            mergeArr[i] = temp;
            quickArr[i] = temp;
        }
        cout << "ARRAY SIZE: " << sizes[j] << endl;

        double duration;
        clock_t startTime = clock();
        insertionSort( insertArr, sizes[j], compCount, moveCount);
        duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
        cout << "Insertion Sort: Comparisons: " << compCount << " Moves: " << moveCount << " Time: " << duration << endl;

        double duration2;
        clock_t startTime2 = clock();
        mergeSort( mergeArr, sizes[j], compCount, moveCount );
        duration2 = 1000 * double( clock() - startTime2 ) / CLOCKS_PER_SEC;
        cout << "Merge Sort: Comparisons: " << compCount << " Moves: " << moveCount << " Time: " << duration2 << endl;

        double duration3;
        clock_t startTime3 = clock();
        quickSort( quickArr, sizes[j], compCount, moveCount );
        cout << "Quick Sort: Comparisons: " << compCount << " Moves: " << moveCount << " Time: " << duration3 << endl;
        duration3 = 1000 * double( clock() - startTime3 ) / CLOCKS_PER_SEC;
        cout << endl;
    }

    cout << "----------------------------------------------------------" << endl;
    cout << "Part b2 - Performance analysis of ascending integers array" << endl;
    cout << "----------------------------------------------------------" << endl;

    for ( int j = 0; j <= 4; j++)
    {

        int insertArr[sizes[j]];
        int mergeArr[sizes[j]];
        int quickArr[sizes[j]];

        //Ascending Array
        cout << "ARRAY SIZE: " << sizes[j] << endl;
        for ( int i = 0; i < sizes[j]; i++ )
        {
            insertArr[i] = i;
            mergeArr[i] = i;
            quickArr[i] = i;
        }

        double duration;
        clock_t startTime = clock();
        insertionSort( insertArr, sizes[j], compCount, moveCount);
        duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
        cout << "Insertion Sort: Comparisons: " << compCount << " Moves: " << moveCount << " Time: " << duration << endl;

        double duration2;
        clock_t startTime2 = clock();
        mergeSort( mergeArr, sizes[j], compCount, moveCount );
        duration2 = 1000 * double( clock() - startTime2 ) / CLOCKS_PER_SEC;
        cout << "Merge Sort: Comparisons: " << compCount << " Moves: " << moveCount << " Time: " << duration2 << endl;

        double duration3;
        clock_t startTime3 = clock();
        quickSort( quickArr, sizes[j], compCount, moveCount );
        cout << "Quick Sort: Comparisons: " << compCount << " Moves: " << moveCount << " Time: " << duration3 << endl;
        duration3 = 1000 * double( clock() - startTime3 ) / CLOCKS_PER_SEC;
        cout << endl;
    }

    cout << "-----------------------------------------------------------" << endl;
    cout << "Part b3 - Performance analysis of descending integers array" << endl;
    cout << "-----------------------------------------------------------" << endl;

    for ( int j = 0; j <= 4; j++)
    {

        int insertArr[sizes[j]];
        int mergeArr[sizes[j]];
        int quickArr[sizes[j]];

        cout << "ARRAY SIZE: " << sizes[j] << endl;
        for ( int i = 0; i < sizes[j]; i++ )
        {
            insertArr[i] = sizes[j] - i;
            mergeArr[i] = sizes[j] - i;
            quickArr[i] = sizes[j] - i;
        }


        double duration;
        clock_t startTime = clock();
        insertionSort( insertArr, sizes[j], compCount, moveCount);
        duration = 1000 * double( clock() - startTime ) / CLOCKS_PER_SEC;
        cout << "Insertion Sort: Comparisons: " << compCount << " Moves: " << moveCount << " Time: " << duration << endl;

        double duration2;
        clock_t startTime2 = clock();
        mergeSort( mergeArr, sizes[j], compCount, moveCount );
        duration2 = 1000 * double( clock() - startTime2 ) / CLOCKS_PER_SEC;
        cout << "Merge Sort: Comparisons: " << compCount << " Moves: " << moveCount << " Time: " << duration2 << endl;

        double duration3;
        clock_t startTime3 = clock();
        quickSort( quickArr, sizes[j], compCount, moveCount );
        cout << "Quick Sort: Comparisons: " << compCount << " Moves: " << moveCount << " Time: " << duration3 << endl;
        duration3 = 1000 * double( clock() - startTime3 ) / CLOCKS_PER_SEC;
        cout << endl;
    }
}
