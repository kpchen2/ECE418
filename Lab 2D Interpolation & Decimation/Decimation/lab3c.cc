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
	if (argc < 6) 
	{
		cerr << "Usage: " << argv[0] << " in.png out.png [top] [left]" << endl;
		return 1;
	}

	// load the input image
	ComplexFFTImage inputImage;
	inputImage.LoadPng (argv[1]);

	// determine the scale factor
	int factor = atoi(argv[6]); // M=2, M=8
	int alias = atoi(argv[5]); // 0: no anti-aliasing; 1: LPF
	
	// initialize the output interpolated image, small-decimated, restored image (after interpolation), differential image
	ComplexFFTImage outputImage;
	outputImage.Resize(inputImage.Width(), inputImage.Height());
	ComplexFFTImage smallImage;
	smallImage.Resize (inputImage.Width() / factor, inputImage.Height() / factor);
	ComplexFFTImage diffImage;
	diffImage.Resize(inputImage.Width(), inputImage.Height());
	
	/*===

	Insert Lab 3 code here
	
	Note that in this lab if you want to take the FFT of a ComplexFFTImage called image, 
	you only have to call image.FourierTransform () or image.InverseFourierTransform ()
	
	===*/

	// decimation
	if (!alias) {
		// direct sampling
		for (int i = 0; i < smallImage.Width(); i++) {
			for (int j = 0; j < smallImage.Height(); j++) {
				smallImage.Pixel(i, j) = inputImage.Pixel(factor * i, factor * j);
			}
		}
	}
	else {
		// LPF
		inputImage.FourierTransform();
		
		for (int i = 0; i < smallImage.Width() / 2; i++) {
			for (int j = 0; j < smallImage.Height() / 2; j++) {
				smallImage.Pixel(i, j) = inputImage.Pixel(i, j); // corner 1
				smallImage.Pixel(smallImage.Width() - i - 1, j) = inputImage.Pixel(inputImage.Width() - i - 1, j); // corner 2
				smallImage.Pixel(i, smallImage.Height() - j - 1) = inputImage.Pixel(i, inputImage.Height() - j - 1); // corner 3
				smallImage.Pixel(smallImage.Width() - i - 1, smallImage.Height() - j - 1) = inputImage.Pixel(inputImage.Width() - i - 1, inputImage.Height() - j - 1); // corner 4
			}
		}
		smallImage.InverseFourierTransform();
		inputImage.InverseFourierTransform();

		// Parseval's relation
		for (int i = 0; i < smallImage.Width(); i++) {
			for (int j = 0; j < smallImage.Height(); j++) {
				smallImage.Pixel(i, j) = smallImage.Pixel(i, j) * (1 / float(factor * factor));
				if (smallImage.Pixel(i, j).real() > 255) {
					smallImage.Pixel(i, j) = 255;
				}
				if (smallImage.Pixel(i, j).real() < 0) {
					smallImage.Pixel(i, j) = 0;
				}	
			}
		}
	}

	// interpolation
	for (int i = 0; i < outputImage.Width() / factor; i++) {
		for (int j = 0; j < outputImage.Height() / factor; j++) {
			outputImage.Pixel(factor * i, factor * j) = smallImage.Pixel(i, j);
		}
	}

	// interpolate horizontally
	for (int j = 0; j < outputImage.Height() / factor; j++) {
		for (int i = 0; i < outputImage.Width() / factor; i++) {
			if (i != outputImage.Width() / factor - 1) {
				for (int k = 1; k < factor; k++) {
					outputImage.Pixel(factor * i + k, factor * j) = outputImage.Pixel(factor * i, factor * j) * float(float(factor - k) / factor) + outputImage.Pixel(factor * i + factor, factor * j) * float(float(k) / factor);
				}
			}
			else {
				for (int k = 1; k < factor; k++) {
					outputImage.Pixel(factor * i + k, factor * j) = outputImage.Pixel(factor * i, factor * j);
				}
			}
		}
	}

	// interpolate vertically
	for (int i = 0; i < outputImage.Width(); i++) {
		for (int j = 0; j < outputImage.Height() / factor; j++) {
			if (j != outputImage.Height() / factor - 1) {
				for (int k = 1; k < factor; k++) {
					outputImage.Pixel(i, factor * j + k) = outputImage.Pixel(i, factor * j) * float(float(factor - k) / factor) + outputImage.Pixel(i, factor * j + factor) * float(float(k) / factor);
				}
			}
			else {
				for (int k = 1; k < factor; k++) {
					outputImage.Pixel(i, factor * j + k) = outputImage.Pixel(i, factor * j);
				}
			}
		}
	}

	// difference image
	for (int i = 0; i < inputImage.Width(); i++) {
		for (int j = 0; j < inputImage.Height(); j++) {
			diffImage.Pixel(i, j) = inputImage.Pixel(i, j) - outputImage.Pixel(i, j);
		}
	}

	// compute MSE
	double mse = 0;
	for (int i = 0; i < diffImage.Width(); i++) {
		for (int j = 0; j < diffImage.Height(); j++) {
			mse += diffImage.Pixel(i, j).real() * diffImage.Pixel(i, j).real();
		}
	}
	// print MSE
	cout << mse / (diffImage.Width() * diffImage.Height()) << endl;

	// find minimum/maximum of difference image
	double low, high;
	int f = 1;
	for (int i = 0; i < inputImage.Width(); i++) {
		for (int j = 0; j < inputImage.Height(); j++) {
			if (f == 1) {
				low = diffImage.Pixel(i, j).real();
				high = diffImage.Pixel(i, j).real();
				f = 0;
			}
			else {
				if (low > diffImage.Pixel(i, j).real()) {
					low = diffImage.Pixel(i, j).real();
				}
				if (high < diffImage.Pixel(i, j).real()) {
					high = diffImage.Pixel(i, j).real();
				}
			}
		}
	}

	// scale difference image
	for (int i = 0; i < inputImage.Width(); i++) {
		for (int j = 0; j < inputImage.Height(); j++) {
			if (diffImage.Pixel(i, j).real() <= 0) {
				diffImage.Pixel(i, j) = 128.0 * (diffImage.Pixel(i, j).real() - low) / (-1 * low);
			}
			else {
				diffImage.Pixel(i, j) = 127.0 * (diffImage.Pixel(i, j).real() / high) + 128;
			}
		}
	}
	
	// save the image
	smallImage.SavePng(argv[2]);
	outputImage.SavePng(argv[3]);
	diffImage.SavePng(argv[4]);

	return 0;
}
