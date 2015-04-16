#ifndef SRC_PGMIMAGE_HPP
#define SRC_PGMIMAGE_HPP

#include <iostream>
#include <string>

using namespace std;

class PGMImage {
	public:
		PGMImage(std::string path);
		int ** getData();
		int getNumRows();
		int getNumCols();
		int getMaxGrayVal();
		~PGMImage();

		struct PGMHeader {
			std::string magic;
			int numRows;
			int numCols;
			int maxGrayVal;
		};
		static void writePGM(std::string filename, PGMHeader header, int ** data, int numRows, int numCols);

	private:
		void readHeader(ifstream & fileIn);
		void extractFirstWord(string s, string & s1, string & s2);
		int trimLength(string s);

		static void writeHeader(ofstream & outFile, string & filename, PGMHeader & header);
		static void writeData(ofstream & out, PGMHeader & header, int ** data, int numRows, int numCols);

		int mNumRows;
		int mNumCols;
		int mMaxGrayVal;
		int ** mData = NULL;
};

#endif /* SRC_PGMIMAGE_HPP */
