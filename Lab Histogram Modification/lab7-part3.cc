/*===
lab7-part3-skeleton.cc

Abstract: Skeleton for part three of lab seven (histogram equalization)
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
	if (argc != 3)
	{
		cerr << "Useage: " << argv[0] 
		     << " input.png output.png" << endl;
		return 1;
	}

	// load the input image
	Image image;
	image.LoadPng (argv[1]);

	// set up the histogram
	vector<int> histogram (256, 0);
	
	// calculate the image's histogram
	for (int x = 0; x < image.Width (); x++)
	{
		for (int y = 0; y < image.Height (); y++)
		{
			histogram[image.Pixel(x, y)] += 1;
		}
	}
	
	// calculate the cumulative distribution function from the histogram
	vector<int> cDistFunction (256, 0);
	/*===

	Insert Lab 7 Part 3 Code Here - Compute the cumulative distribution 
	function
	
	===*/
	for (int i = 0; i < 256; i++) {
		if (i == 0) {
			cDistFunction[i] = histogram[i];
		}
		else {
			cDistFunction[i] = cDistFunction[i - 1] + histogram[i];
		}
	}

	// apply the cumulative distribution function
	/*===

	Insert Lab 7 Part 3 Code Here - Apply the cumulative distribution 
	function to equalize the image's histogram.  You can then use part two 
	to compute the equalized image's histogram.
	
	===*/
	vector<int> pnt(256, 0);
	for (int i = 0; i < 256; i++) {
		pnt[i] = int((255.0 * (cDistFunction[i] - cDistFunction[0]) / (image.Width() * image.Height() - cDistFunction[0])) + 0.5);
	}

	for (int i = 0; i < image.Width(); i++) {
		for (int j = 0; j < image.Height(); j++) {
			image.Pixel(i, j) = pnt[image.Pixel(i, j)];
		}
	}

	// save the image 
	image.SavePng (argv[2]);

	return 0;
}
