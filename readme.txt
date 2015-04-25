Sorting Project - Project 4
----------------------------
This program takes in an ascii PGM (Portable Gray Map) file and processes it using one of three sorting algorithms and a window size. The result is a "blurred" version of the original image. 

There are 3 main classes to this program:
	* PGMImage - The PGM image library. It reads and writes PGM image files
	* Sorting - A "static" class containing the three sorting algorithms
	* Main - The main driver class for the program

PGMImage
--------
This class simply reads and writes ascii PGM files.
A PGM file is read by creating an instance of the class, constructed with a string containing the filename of the image.
Ex. PGMImage image = PGMImage("filename.pgm");

There are methods to get the number of rows, columns, max gray value, PGM "magic number and pixel data as a 2D array of integers.

A PGM file is created by calling the static method writePGM.
The method takes the filename of the image to be output, a PGM header struct, a 2D array of pixels, the number of rows and the number of columns.

Ex. PGMImage::writePGM("output.pgm", header, pixels, rows, cols);

Sorting
-------
This class contains static methods that take in a 1D array of integers and a size, and output a 1D array of pixels, sorted.

Ex. Sorting::radixSort(pixels, 10);

Main
----
This class takes in arguments from the command line and processes them. After getting the command line arguments, it processes the pixel data using the specified window size and algorithm. It outputs the processed file, and the runtime taken to process the file.

As expected, the program takes longer to run the larger the window size is. Processing a small file with a small window size (< 11 or so) can be done almost instantly whereas the time complexity greatly increases as the window size increases.
