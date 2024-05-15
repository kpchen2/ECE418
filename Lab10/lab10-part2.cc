/*===
lab10-part2-solution.cc

Abstract: Skeleton for part two of lab ten (run length coding)
===*/

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "image.h"
using namespace std;

// calculate the log base 2 of a number
double log2 (double x);

// snake raster scan function -- updates x and y for a raster-snake scan
// of image, returning false only when the whole image has been traversed
bool SnakePixel (const Image& image, int& x, int& y);

int main (int argc, char* argv[]) 
{
	// verify arguments' correctness
	if (argc != 3) 
	{
		cerr << "Useage: " << argv[0] 
		     << " input.png histogram.txt" << endl;
		return 1;
	}

	// load the input image
	Image image;
	image.LoadPng (argv[1]);
	int totalPixels = image.Width () * image.Height ();
	
	// create the normalized (sum of elements is one) histogram for the run lengths
	vector<double> runLengthHistogram (totalPixels + 1, 0);

	int curVal = 0;
	int curLength = 1;
	double numRuns = 0.0;
	
	// traverse the image in raster-snake order
	for (int x = 0, y = 0; SnakePixel (image, x, y); )
	{
		/*===

		Insert Lab 10 Part 2 Code Here
			-you will probably need to insert some code before this 
			 to calculate run length histogram (initialize current
			 run length, current run's pixel value, etc).
			-don't forget to include last run in the calculation 
			 and normalize your histogram (so its elements sum to
			 one).

		===*/

		if (x == 0 && y == 0) {
			curVal = image.Pixel(x, y);
		}
		else {
			if (curVal != image.Pixel(x, y)) {
				runLengthHistogram[curLength] += 1.0;
				curVal = image.Pixel(x, y);
				curLength = 1;
				numRuns += 1.0;
			}
			else {
				curLength += 1;
			}
		}
	} 
	runLengthHistogram[curLength] += 1.0;
	numRuns += 1.0;
	
	
	// calculate and print the entropy of the histogram
	double entropy = 0;
	vector<double> prob(runLengthHistogram.size(), 0.0);
	for (int i = 0; i < runLengthHistogram.size (); i++) 
	{
		/*===

		Insert Lab 10 Part 2 Code Here
		
		===*/
		prob[i] = runLengthHistogram[i] / numRuns;
		entropy -= prob[i] * log2(prob[i]);
	}
	cout << "Run-Length Entropy is " << entropy << "." << endl;
	// print other requested data
	cout << "The total number of runs is " << numRuns << endl;
	cout << "The total number of bits required is " << entropy * numRuns << endl;
	cout << "The number of bits per pixel is " << entropy * numRuns / totalPixels << endl;
	
	// print the histogram the specified file (only as many entries as are nonzero)
	ofstream out (argv[2]);
	if (out.fail () ) 
	{
		cerr << "Failed to open file for histogram output" << endl;
		return 1;
	}
	int maxNonZeroIndex = 0;
	for (int i = 0; i < runLengthHistogram.size (); i++) 
	{
		if (runLengthHistogram[i] != 0) {
			maxNonZeroIndex = i;
		}
	}
	for (int i = 0, pixels = 0; i <= maxNonZeroIndex; i++) 
	{
		out << runLengthHistogram[i] << endl;
	}
	out.close ();

	return 0;
}

// calculate the log base 2 of a number
double log2 (double x) 
{
	if (x == 0) return 0;
	return log (x) / (log (2.0) );
}

// snake raster scan function -- updates x and y for a raster-snake scan
// of image, returning false only when the whole image has been traversed
bool SnakePixel (const Image& image, int& x, int& y) 
{
	if (y % 2 == 0) 
	{
		x++;
		if (x == image.Width () ) 
		{
			x--;
			y++;
		}
	}
	else 
	{
		x--;
		if (x == -1) 
		{
			x++;
			y++;
		}		
	}
	return (y < image.Height () );
}

