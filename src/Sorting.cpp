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

void Sorting::insertionSort(int * arr, int numElem) {
	int i, j;

	for (i = 1; i < numElem; i++) {
		int selectItem = arr[i];
		bool inserted = false;

		for (j = i - 1; j >= 0 && inserted != true;) {
			if (selectItem < arr[j]) {
				arr[j + 1] = arr[j];
				j--;

				arr[j + 1] = selectItem;
			}
			else inserted = true;
		}
	}
}

int Sorting::partition (int * arr, int start, int end)
{
    int x = arr[end];    
    int i = (start - 1);  
 
    for (int j = start; j <= end- 1; j++)
    {
        
        if (arr[j] <= x)
        {
            i++;
            int t = arr[i];
            arr[i] = arr[j];
            arr[j] = t;
        }
    }
    int temp = arr[i+1];
    arr[i+1] = arr[end];
    arr[end] = temp;
    return (i + 1);
}
 
void Sorting::quicksort(int * arr, int start, int end)
{
    if (start < end)
    {
        int pindex = partition(arr, start, end);
        quicksort(arr, start, pindex - 1);
        quicksort(arr, pindex + 1, end);
    }
}

void Sorting::quicksort(int * arr, int numElem){
    quicksort(arr, 0, numElem-1);
}
