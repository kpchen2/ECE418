/*===
lab7-part2-skeleton.cc

Abstract: Skeleton for part two of lab seven (histogram output)
===*/

#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <vector>
#include "image.h"
using namespace std;

int main (int argc, char* argv[])
{
	// verify arguments' correctness
	if (argc != 4)
	{
		cerr << "Useage: " << argv[0] 
		     << " input.png histogram.txt bin_count" << endl;
		return 1;
	}
	int binCount = atoi (argv[3]);
	if (binCount < 1)
	{
		cerr << "Bin count must be greater than zero" << endl;
	}

	// load the input image
	Image image;
	image.LoadPng (argv[1]);

	// set up the histogram
	vector<int> histogram (binCount, 0);
	
	// perform gamma point operation
	for (int x = 0; x < image.Width (); x++)
	{
		for (int y = 0; y < image.Height (); y++)
		{
			int pos = image.Pixel(x, y) / (256.0 / binCount);
			histogram[pos] += 1;
		}
	}
	
	// print the histogram the specified file
	ofstream out (argv[2]);
	if (out.fail () )
	{
		cerr << "Failed to open file for histogram output" << endl;
		return 1;
	}
	for (int i = 0; i < histogram.size (); i++)
	{
		out << histogram[i] << endl;
	}
	out.close ();

	return 0;
}
