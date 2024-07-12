/*===
lab3-skeleton.cc

Abstract: Skeleton for Lab 3 parts (a), (b), and (c)
===*/

#include <stdlib.h>
#include <iostream>
#include <vector>
#include "imagefft.h"
using namespace std;

complex<double> operator*(complex<double>& b, const float& a) {
	return complex<double>(b.real() * a, b.imag() * a);
}

int main (int argc, char* argv[])
{
	// check parameters' correctness [for parts (a) and (b) -- this needs to be changed for (c)]
	if (argc < 3) 
	{
		cerr << "Usage: " << argv[0] << " in.png out.png [top] [left]" << endl;
		return 1;
	}

	// read the top row and left column that will be used [remove this for part (c)]
	int topLeftRow = atoi(argv[3]);
	int topLeftColumn = atoi(argv[4]);

	// load the input image
	ComplexFFTImage inputImage;
	inputImage.LoadPng (argv[1]);
	
	// initialize the output interpolated image
	ComplexFFTImage outputImage;
	outputImage.Resize (inputImage.Width (), inputImage.Height ());
	
	/*===

	Insert Lab 3 code here
	
	Note that in this lab if you want to take the FFT of a ComplexFFTImage called image, 
	you only have to call image.FourierTransform () or image.InverseFourierTransform ()
	
	===*/

	// fills in every fourth value
	for (int i = 0; i < outputImage.Width() / 4; i++) {
		for (int j = 0; j < outputImage.Height() / 4; j++) {
			outputImage.Pixel(4 * i, 4 * j) = inputImage.Pixel(i + topLeftRow, j + topLeftColumn);
		}
	}

	// interpolate horizontally
	for (int j = 0; j < outputImage.Height() / 4; j++) {
		for (int i = 0; i < outputImage.Width() / 4; i++) {
			if (i != outputImage.Width() / 4 - 1) {
				outputImage.Pixel(4 * i + 1, 4 * j) = outputImage.Pixel(4 * i, 4 * j) * float(3.0 / 4.0) + outputImage.Pixel(4 * i + 4, 4 * j) * float(1.0 / 4.0);
				outputImage.Pixel(4 * i + 2, 4 * j) = outputImage.Pixel(4 * i, 4 * j) * float(2.0 / 4.0) + outputImage.Pixel(4 * i + 4, 4 * j) * float(2.0 / 4.0);
				outputImage.Pixel(4 * i + 3, 4 * j) = outputImage.Pixel(4 * i, 4 * j) * float(1.0 / 4.0) + outputImage.Pixel(4 * i + 4, 4 * j) * float(3.0 / 4.0);
			}
			else {
				outputImage.Pixel(4 * i + 1, 4 * j) = outputImage.Pixel(4 * i, 4 * j);
				outputImage.Pixel(4 * i + 2, 4 * j) = outputImage.Pixel(4 * i, 4 * j);
				outputImage.Pixel(4 * i + 3, 4 * j) = outputImage.Pixel(4 * i, 4 * j);
			}
		}
	}

	// interpolate vertically
	for (int i = 0; i < outputImage.Width(); i++) {
		for (int j = 0; j < outputImage.Height() / 4; j++) {
			if (j != outputImage.Height() / 4 - 1) {
				outputImage.Pixel(i, 4 * j + 1) = outputImage.Pixel(i, 4 * j) * float(3.0 / 4.0) + outputImage.Pixel(i, 4 * j + 4) * float(1.0 / 4.0);
				outputImage.Pixel(i, 4 * j + 2) = outputImage.Pixel(i, 4 * j) * float(2.0 / 4.0) + outputImage.Pixel(i, 4 * j + 4) * float(2.0 / 4.0);
				outputImage.Pixel(i, 4 * j + 3) = outputImage.Pixel(i, 4 * j) * float(1.0 / 4.0) + outputImage.Pixel(i, 4 * j + 4) * float(3.0 / 4.0);
			}
			else {
				outputImage.Pixel(i, 4 * j + 1) = outputImage.Pixel(i, 4 * j);
				outputImage.Pixel(i, 4 * j + 2) = outputImage.Pixel(i, 4 * j);
				outputImage.Pixel(i, 4 * j + 3) = outputImage.Pixel(i, 4 * j);
			}
		}
	}
	
	// save the image
	outputImage.SavePng (argv[2]);

	return 0;
}
