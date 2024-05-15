/*===
lab5-dither4x4-skeleton.cc

Abstract: Skeleton code for a 4x4 dithering scheme
===*/

#include <stdlib.h>
#include <iostream>
#include <vector>
#include "image.h"
using namespace std;

int main (int argc, char* argv[])
{
	// load the input image
	Image image;
	image.LoadPng("ca_coast.png");

	Image origin;
	origin.LoadPng("ca_coast.png");

	for (int i = 0; i < image.Width(); i++) {
		for (int j = 0; j < image.Height(); j++) {
			image.Pixel(i, j) = 57;
			origin.Pixel(i, j) = 57;
		}
	}

	// the dithering matrix (to access the pixel at column x, row y, the
	// index in this structure is [x][y]
	static short ditherMatrix[4][4] = {
		{8,   136, 40,  168},
		{200, 72,  232, 104},
		{56,  184, 24,  152},
		{248, 120, 216, 88} };

	// dither the image
	for (int x = 0; x < image.Width (); x+=4)
	{
		for (int y = 0; y < image.Height (); y+=4)
		{
			/*===
	
			Insert Lab 5 4x4 dithering code here
	
			===*/	
			for (int a = 0; a < 4; a++) {
				for (int b = 0; b < 4; b++) {
					int& value = image.Pixel(x + a, b + y);
					value = (value < ditherMatrix[a][b]) ? 0 : 255;
				}
			}
		}
	}

	double MSE = 0.0;
	for (int i = 0; i < image.Width(); i++) {
		for (int j = 0; j < image.Height(); j++) {
			MSE += pow(image.Pixel(i, j) - origin.Pixel(i, j), 2);
		}
	}
	MSE /= (image.Width() * image.Height());
	cout << MSE << endl;
	
	// save the image
	image.SavePng ("ca_coast_dither4x4.png");

	return 0;
}
