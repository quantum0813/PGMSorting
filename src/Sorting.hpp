#ifndef SRC_SORTING_HPP
#define SRC_SORTING_HPP

/**
 * This is not really the best "class" per se. It's basically just a collection
 * of public and private static functions declared in a class to separate them
 * from the main module. You shouldn't make an instance of this class. It is a
 * "static" class.
 */
class Sorting {
	private:
		static int arrayMax(int * arr, int numElem);
		static void countSort(int * arr, int numElem, int exp);
		static int partition(int * arr, int start, int end);
		static void quicksort(int * arr, int start, int end);
		

	public:
		static void radixSort(int * arr, int numElem);
		static void insertionSort(int * arr, int numElem);
		static void quicksort(int * arr, int numElem);
};

#endif /* SRC_SORTING_HPP */
