#include <iostream>
#include <limits.h>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include "PGMImage.hpp"
#include "Sorting.hpp"

bool isNumeric(const char * str);

int main(int argc, char * argv[]) {
	int windowSize = 3;
	std::string filename = "Buchtel.pgm";

	if (argc != 3) {
		// There should be exactly 3 parameters
		// argv[0] - Application path
		// argv[1] - Window size
		// argv[2] - Input image file
		std::cout << "Error: Invalid arguments!" << std::endl;
		std::cout << "Usage: Sorting 5 \"/path/to/image/image.pgm\"" << std::endl;
		return 0;
	}

	if (!isNumeric(argv[1])) {
		std::cout << "Error: Argument 2 must be a number" << std::endl;
		return 0;
	}

	windowSize = atoi(argv[1]);
	filename = string(argv[2]);

	if (windowSize % 2 == 0) {
		std::cout << "Error: Window size must be an odd number" << std::endl;
		return 0;
	}

	PGMImage image = PGMImage(filename);
	std::cout << "The image has " << image.getNumRows() << " rows" << std::endl;
	std::cout << "The image has " << image.getNumCols() << " columns" << std::endl;

	PGMImage::PGMHeader header;
	header.magic = "P2";
	header.maxGrayVal = 255;
	header.numCols = image.getNumCols();
	header.numRows = image.getNumRows();

	// Test - kind of a cool effect
	for (int i = 0; i < header.numRows; i++) {
		for (int j = 0; j < header.numCols; j++) {
			if ((i + j) % 2 == 0) {
				if ((image.getData()[i][j] * 2) > header.maxGrayVal)
					image.getData()[i][j] = 255;
				else
					image.getData()[i][j] *= 2;
			} else {
				if ((image.getData()[i][j] / 2) < 0)
					image.getData()[i][j] = 0;
				else
					image.getData()[i][j] /= 2;
			}
		}
	}

	PGMImage::writePGM("test.pgm", header, image.getData(), image.getNumRows(), image.getNumCols());

	// Test of radix sort
	int arr[50];
	srand(time(NULL));
	for (int i = 0; i < 50; i++)
		arr[i] = (rand() % 1000) + 1;

	std::clock_t start = std::clock();
	Sorting::radixSort(arr, 50);
	std::clock_t end = std::clock();
	std::cout << "Radix sort of 50 random numbers took: " << (end - start) / (double)(CLOCKS_PER_SEC / 1000) << "ms" << std::endl;
}

bool isNumeric(const char * str) {
	int len = strlen(str);
	for (int i = 0; i < len; i++) {
		if (!isdigit(str[i]))
			return false;
	}
	return true;
}
