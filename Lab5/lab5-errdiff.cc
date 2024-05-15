/*===
lab5-errdiff-skeleton.cc

Abstract: Skeleton code for an error diffusion scheme
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
	image.LoadPng ("ca_coast.png");


	/*===

	You may want to set up an image (doubles as pixel values) to store 
	the error at each pixel
	
	ImageTemplate<double> error;
	error.Resize (image.Width (), image.Height () );

	===*/

	Image origin;
	origin.LoadPng("ca_coast.png");

	for (int i = 0; i < image.Width(); i++) {
		for (int j = 0; j < image.Height(); j++) {
			image.Pixel(i, j) = 57;
			origin.Pixel(i, j) = 57;
		}
	}

	Image error;
	error.Resize(image.Width(), image.Height());

	// dither the image (note we must traverse in raster-scan order here)
	for (int y = 0; y < image.Height (); y++)
	{
		for (int x = 0; x < image.Width (); x++)
		{
			double err = 0.0;
			if (x > 0) {
				err += 7.0 / 16 * error.Pixel(x - 1, y);
			}
			if (y > 0) {
				err += 5.0 / 16 * error.Pixel(x, y - 1);
			}
			if (x > 0 && y > 0) {
				err += 1.0 / 16 * error.Pixel(x - 1, y - 1);
			}
			if (x + 1 < image.Width() && y > 0) {
				err += 3.0 / 16 * error.Pixel(x + 1, y - 1);
			}

			double U = image.Pixel(x, y) - err; // unquantized
			double O = (U < 128) ? 0 : 255; // quantized
			image.Pixel(x, y) = O; // output image
			error.Pixel(x, y) = O - U; // updated error
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
	image.SavePng ("ca_coast_errdiff.png");

	return 0;
}
