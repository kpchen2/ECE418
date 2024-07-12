/*===
lab12-skeleton.cc

Abstract: Skeleton code for lab 12
===*/

#include "image.h"
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

// main
int main (int argc, char* argv[]) {
	
	// check arguments' correctness
	if (argc != 8) {
		cout << "Usage : " << argv[0] 
		     << " current previous blocksize"
		     << " xblock yblock search_size output_ascii_file" 
		     << endl;
	  return 1;
	}

	// load the current frame
	Image current;
	current.LoadPng ( argv[1] );

	// load the previous frame
	Image previous;
	previous.LoadPng ( argv[2] );

	// parse command line arguments
	int blockSize = atoi(argv[3]);  // the size of the block we will be comparing
	int xStart = atoi(argv[4]);     // starting horizontal pixel for the block we will compare
	int yStart = atoi(argv[5]);     // starting vertical pixel for the block we will compare
	int searchSize = atoi(argv[6]); // number of pixels up and down our search will encompass
	
	// initialize the 2D array holding the MSE for each displacement to have size searchSize^2
	vector<vector<double> > displacementMSE (searchSize, vector<double> (searchSize, 0) );

	// fill in the displacementMSE table and print the displacement that minimizes MSE
	/*===
	
	Insert Lab 12 Code Here
	
	===*/

	int normX = xStart - int(searchSize / 2);
	int normY = yStart - int(searchSize / 2);
	for (int i = normX; i <= xStart + int(searchSize / 2); i++) {
		for (int j = normY; j <= yStart + int(searchSize / 2); j++) {

			int curX = xStart;
			int curY = yStart;
			int curNum = 0;
			double mse = 0;
			for (int x = i; x < i + blockSize; x++) {
				for (int y = j; y < j + blockSize; y++) {
					mse += pow((current.Pixel(curX + x - i, curY + y - j) - previous.Pixel(x, y)), 2);
				}
			}
			displacementMSE[i - normX][j - normY] = mse;

		}
	}

	double min = displacementMSE[0][0];
	int mv[2] = { -int(searchSize / 2), -int(searchSize / 2) };
	for (int i = 0; i < searchSize; i++) {
		for (int j = 0; j < searchSize; j++) {
			if (displacementMSE[i][j] < min) {
				min = displacementMSE[i][j];
				mv[0] = i - int(searchSize / 2);
				mv[1] = j - int(searchSize / 2);
			}
		}
	}
	cout << "THIS IS THE MIN: " << min/pow(blockSize,2) << endl;
	cout << "THIS IS THE MV: (" << mv[0] << ", " << mv[1] << ")" << endl;

	// save each displacement's MSE to a file
	ofstream out (argv[7]);
	if (out.fail () ) 
	{
		cout << "Failed to open " << argv[7] << " for writing." << endl;
		return 1;
	}	
	for (int x = 0; x < searchSize; x++)
	{
		int xOffset = x - (searchSize - 1)/2;
		for (int y = 0; y < searchSize; y++)
		{
			int yOffset = y - (searchSize - 1)/2;
			out << xOffset << " " << yOffset << " " << displacementMSE[x][y] << endl;
		}
	}
	out.close ();	
}
