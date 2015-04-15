#include <iostream>
#include <limits.h>
#include <cstdlib>
#include <ctime>
#include "PGMImage.hpp"
#include "Sorting.hpp"

int main() {
	PGMImage image = PGMImage("Buchtel.pgm");
	std::cout << "The image has " << image.getNumRows() << " rows" << std::endl;
	std::cout << "The image has " << image.getNumCols() << " columns" << std::endl;

	PGMImage::PGMHeader header;
	header.magic = "P2";
	header.maxGrayVal = 255;
	header.numCols = image.getNumCols();
	header.numRows = image.getNumRows();

	// Test - kind of a cool effect
	for (int i = 0; i < header.numCols * header.numRows; i++) {
		if (i % 2 == 0) {
			if ((image.getData()[i] * 2) > header.maxGrayVal)
				image.getData()[i] = 255;
			else
				image.getData()[i] *= 2;
		} else {
			if ((image.getData()[i] / 2) < 0)
				image.getData()[i] = 0;
			else
				image.getData()[i] /= 2;
		}
	}

	PGMImage::writePGM("test.pgm", header, image.getData());

	// Test of radix sort
	int arr[50];
	srand(time(NULL));
	for (int i = 0; i < 50; i++)
		arr[i] = (rand() % 1000) + 1;

	std::clock_t start = std::clock();
	Sorting::radixSort(arr, 50);
	std::clock_t end = std::clock();
	cout << "Radix sort of 50 random numbers took: " << (end - start) / (double)(CLOCKS_PER_SEC / 1000) << "ms" << endl;

	for (int i = 0; i < 50; i++)
		cout << arr[i] << " ";
}
