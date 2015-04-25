#include <iostream>
#include <limits.h>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <algorithm>
#include <string>
#include <vector>
#include <fstream>
#include <sstream>
#include "PGMImage.hpp"
#include "Sorting.hpp"

enum Algorithm {
	INSERTION,
	QUICK,
	RADIX
};

const std::string ALG_INSERTION = "insertion";
const std::string ALG_QUICK = "quick";
const std::string ALG_RADIX = "radix";

bool isNumeric(const char * str);
void toLowercase(std::string & str);
int * getPixels(int ** data, int rowStart, int rowEnd, int colStart, int colEnd);

int main(int argc, char * argv[]) {
	int windowSize = 5;
	std::string filename = "Buchtel.pgm";
	Algorithm alg = INSERTION;

	if (argc != 4) {
		// There should be exactly 3 parameters
		// argv[0] - Application path
		// argv[1] - Window size
		// argv[2] - Input image file
		// argv[3] - Sorting algorithm to use - Either "insertion", "quick" or "radix"
		std::cout << "Error: Invalid arguments!" << std::endl;
		std::cout << "Usage: Sorting 5 \"/path/to/image/image.pgm\" algorithm" << std::endl;
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

	std::string str = argv[3];
	toLowercase(str);
	if (str.length() < 5) {
		// If the string is less than 5 characters there's no way it is valid
		std::cout << "Error: Algorithm not supported" << std::endl;
		std::cout << "Valid algorithms include \"insertion\", \"quick\" and \"radix\"" << std::endl;
		return 0;
	} else {
		if (str.length() == 5) {
			// The algorithm should be either "quick" or "radix"
			if (str.compare(ALG_QUICK) == 0) {
				alg = QUICK;
			} else if (str.compare(ALG_RADIX) == 0) {
				alg = RADIX;
			} else {
				std::cout << "Error: Algorithm not supported" << std::endl;
				std::cout << "Valid algorithms include \"insertion\", \"quick\" and \"radix\"" << std::endl;
				return 0;
			}
		} else {
			if (str.compare(ALG_INSERTION) == 0) {
				alg = INSERTION;
			} else {
				std::cout << "Error: Algorithm not supported" << std::endl;
				std::cout << "Valid algorithms include \"insertion\", \"quick\" and \"radix\"" << std::endl;
				return 0;
			}
		}
	}

	std::cout << "You chose the algorithm: ";
	switch (alg) {
		case INSERTION:
			std::cout << "Insertion" << std::endl;
			break;
		case QUICK:
			std::cout << "Quick" << std::endl;
			break;
		case RADIX:
			std::cout << "Radix" << std::endl;
			break;
	}

	PGMImage image = PGMImage(filename);
	std::cout << "The image has " << image.getNumRows() << " rows" << std::endl;
	std::cout << "The image has " << image.getNumCols() << " columns" << std::endl;

	PGMImage::PGMHeader header;
	header.magic = "P2";
	header.maxGrayVal = 255;
	header.numCols = image.getNumRows();
	header.numRows = image.getNumCols();

	// Divide the window size in half using integer division to get the number of
	// pixels on each edge from the center of the window
	// If the window size is 5 and we are at pixel 0, 0, the window will look like
	// 0 0 0 | 0 0 0 0 0 0 0
	// 0 0 0 | 0 0 0 0 0 0 0
	// 0 0 0 | 0 0 0 0 0 0 0
	// - - -
	// 0 0 0 0 0 0 0 0 0 0 0

	int halfWindow = windowSize / 2;
	int ** newImage = new int*[image.getNumRows()];
	for (int i = 0; i < image.getNumRows(); i++)
		newImage[i] = new int[image.getNumCols()];

	std::clock_t start = std::clock();
	for (int i = 0; i < image.getNumCols(); i++) {
		for (int j = 0; j < image.getNumRows(); j++) {
			int rowStart = i - halfWindow;
			int rowEnd = i + halfWindow;
			int colStart = j - halfWindow;
			int colEnd = j + halfWindow;
			if (rowStart < 0)
				rowStart = 0;
			if (rowEnd > image.getNumCols() - 1)
				rowEnd = image.getNumCols() - 1;
			if (colStart < 0)
				colStart = 0;
			if (colEnd > image.getNumRows() - 1)
				colEnd = image.getNumRows() - 1;

			int numRowsL = (rowEnd - rowStart) + 1;
			int numColsL = (colEnd - colStart) + 1;
			int size = numRowsL * numColsL;

			int * pixels = getPixels(image.getData(), rowStart, rowEnd, colStart, colEnd);

			switch (alg) {
				case INSERTION:
					break;
				case QUICK:
					break;
				case RADIX:
					Sorting::radixSort(pixels, size);
					break;
			}

			int median = 0;
			if (size % 2 == 0) {
				int sum = pixels[(size / 2) - 1] + pixels[(size / 2)];
				median = sum / 2;
			} else {
				median = pixels[(size / 2)];
			}

			newImage[j][i] = median;

			delete [] pixels;
		}
	}
	std::clock_t end = std::clock();
	std::cout << "Image processing took: " << (end - start) / (double)(CLOCKS_PER_SEC / 1000) << "ms" << std::endl;

	size_t index = filename.find_last_of('.');
	if (index != string::npos)
		filename = filename.substr(0, index);

	std::stringstream ss;;
	ss << filename << "_processed_" << windowSize << ".pgm";

	PGMImage::writePGM(ss.str(), header, newImage, image.getNumRows(), image.getNumCols());

	for (int i = 0; i < image.getNumRows(); i++)
		delete [] newImage[i];
	delete [] newImage;
}

int * getPixels(int ** data, int rowStart, int rowEnd, int colStart, int colEnd) {
	int numRowsL = (rowEnd - rowStart) + 1;
	int numColsL = (colEnd - colStart) + 1;
	int size = numRowsL * numColsL;

	int * returnArr = new int[size];

	int count = 0;
	for (int i = colStart; i <= colEnd; i++) {
		for (int j = rowStart; j <= rowEnd; j++) {
			returnArr[count] = data[i][j];
			count++;
		}
	}
	return returnArr;
}

bool isNumeric(const char * str) {
	int len = strlen(str);
	for (int i = 0; i < len; i++) {
		if (!isdigit(str[i]))
			return false;
	}
	return true;
}

void toLowercase(std::string & str) {
	std::transform(str.begin(), str.end(), str.begin(), ::tolower);
}
