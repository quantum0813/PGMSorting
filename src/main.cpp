#include <iostream>
#include "PGMImage.hpp"

int main() {
	PGMImage image = PGMImage("Buchtel.pgm");
	std::cout << "The image has " << image.getNumRows() << " rows" << std::endl;
	std::cout << "The image has " << image.getNumCols() << " columns" << std::endl;

	for (int i = 0; i < image.getNumRows() * image.getNumCols(); i++) {
		if (i % 20 == 0) {
			cout << endl;
			cout << image.getData()[i] << " ";
		} else {
			cout << image.getData()[i] << " ";
		}
	}

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
}
