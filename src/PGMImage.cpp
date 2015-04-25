#include "PGMImage.hpp"

#include <fstream>
#include <sstream>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <cstring>

using namespace std;

PGMImage::PGMImage(std::string path) : mNumRows(0), mNumCols(0) {
	ifstream in;

	in.open(path.c_str());

	if (!in)
		cerr << "Error - cannot open file" << endl;

	// Read the header
	readHeader(in);

	//int numPixels = mNumRows * mNumCols;
	mData = new int*[mNumRows];
	for (int i = 0; i < mNumRows; i++)
		mData[i] = new int[mNumCols];

	for (int i = 0; i < mNumRows; i++) {
		for (int j = 0; j < mNumCols; j++) {
			in >> mData[i][j];
			if (in.eof())
				return;
		}
	}

	in.close();
}

void PGMImage::extractFirstWord(string s, string & s1, string & s2) {
	int i;
	int mode;
	int sLen;

	sLen = s.length();
	s1 = "";
	s2 = "";
	mode = 1;

	for (i = 0; i < sLen; i++) {
		if (mode == 1) {
			if (s[i] != ' ') {
				mode = 2;
			}
		} else if (mode == 2) {
			if (s[i] == ' ') {
				mode = 3;
			}
		} else if (mode == 3) {
			if (s[i] != ' ') {
				mode = 4;
			}
		}
		if (mode == 2) {
			s1 = s1 + s[i];
		} else if (mode == 4) {
			s2 = s2 + s[i];
		}
	}
}

int PGMImage::trimLength(string s) {
	int n = s.length();

	while (n > 0) {
		if (s[n - 1] != ' ')
			return n;
		n = n - 1;
	}
	return n;
}

void PGMImage::readHeader(ifstream & fileIn) {
	string line;
	string rest;
	int step;
	string word;

	step = 0;

	while (true) {
		getline(fileIn, line);

		if (fileIn.eof()) {
			cerr << "Error: encountered End of file" << endl;
		}

		if (line[0] == '#')
			continue;

		if (step == 0) {
			extractFirstWord(line, word, rest);
			if (trimLength(word) == 0)
				continue;
			line = rest;

			if ((word[0] != 'P' && word[0] != 'p') || (word[1] != '1' && word[1] != '2' && word[1] != '3' && word[1] != '4' && word[1] != '5')) {
				cerr << "Error - Invalid magic number: \"" << word << "\"";
			}
			step = 1;
		}
		if (step == 1) {
			extractFirstWord(line, word, rest);
			if (trimLength(word) == 0)
				continue;
			mNumCols = atoi(word.c_str());
			line = rest;
			step = 2;
		}
		if (step == 2) {
			extractFirstWord(line, word, rest);
			if (trimLength(word) == 0)
				continue;
			mNumRows = atoi(word.c_str());
			line = rest;
			step = 3;
		}
		if (step == 3) {
			extractFirstWord(line, word, rest);
			if (trimLength(word) == 0)
				continue;
			mMaxGrayVal= atoi(word.c_str());
			line = rest;
			break;
		}
	}
}

int ** PGMImage::getData() {
	return mData;
}

PGMImage::~PGMImage() {
	for (int i = 0; i < mNumRows; i++)
		delete [] mData[i];
	delete [] mData;
}

int PGMImage::getNumRows() {
	return mNumRows;
}

int PGMImage::getNumCols() {
	return mNumCols;
}

int PGMImage::getMaxGrayVal() {
	return mMaxGrayVal;
}

void PGMImage::writePGM(std::string filename, PGMHeader header, int ** data, int numRows, int numCols) {
	ofstream outFile;

	outFile.open(filename.c_str());
	if (!outFile) {
		cerr << "Cannot open the output file \"" << filename << "\"" << endl;
	}

	// Write our header
	writeHeader(outFile, filename, header);

	// Now write the data
	writeData(outFile, header, data, numRows, numCols);

	outFile.close();
}

void PGMImage::writeHeader(ofstream & outFile, string & filename, PGMHeader & header) {
	outFile << header.magic << "\n";
	outFile << "# " << filename << ": Created by Eric's PGMImage lib\n";
	outFile << header.numRows << " " << header.numCols << "\n";
	outFile << header.maxGrayVal << "\n";
}

void PGMImage::writeData(ofstream & outFile, PGMHeader & header, int ** data, int numRows, int numCols) {
	for (int i = 0; i < numRows; i++) {
		for (int j = 0; j < numCols; j++) {
			 if (i == numRows - 1 && j == numCols - 1) {
				outFile << data[i][j];
			} else {
				outFile << data[i][j] << " ";
			}
		}
		outFile << '\n';
	}
}
