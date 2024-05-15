/*===
lab5-dither1x1.cc

Abstract: Implementation of a 1x1 dithering scheme
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
	
	// do 1x1 dithering
	for (int x = 0; x < image.Width (); x++)
	{
		for (int y = 0; y < image.Height (); y++)
		{
			int& value = image.Pixel (x, y);
			value = (value < 128) ? 0 : 255;
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
	image.SavePng ("ca_coast_dither1x1.png");

	return 0;
}
