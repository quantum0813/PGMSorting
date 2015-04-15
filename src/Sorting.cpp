#include "Sorting.hpp"

int Sorting::arrayMax(int * arr, int numElem) {
	int max = arr[0];
	for (int i = 0; i < numElem; i++)
		if (arr[i] > max)
			max = arr[i];
	return max;
}

void Sorting::countSort(int * arr, int numElem, int exp) {
	int output[numElem];
	int i, count[10] = {0};

	for (i = 0; i < numElem; i++)
		count[(arr[i] / exp) % 10]++;

	for (i = 1; i < 10; i++)
		count[i] += count[i - 1];

	for (i = numElem - 1; i >= 0; i--) {
		output[count[(arr[i] / exp) % 10] - 1] = arr[i];
		count[(arr[i] / exp) % 10]--;
	}

	for (i = 0; i < numElem; i++)
		arr[i] = output[i];
}

void Sorting::radixSort(int * arr, int numElem) {
	int max = arrayMax(arr, numElem);

	for (int exp = 1; max / exp > 0; exp *= 10)
		countSort(arr, numElem, exp);
}
