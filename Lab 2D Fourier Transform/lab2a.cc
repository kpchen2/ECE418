/*===
lab2ab-skeleton.cc

Abstract: Skeleton for Lab 2 parts (a) and (b).
===*/

#include <stdlib.h>
#include <iostream>
#include <vector>
#include "image.h"
#include "fft.h"
using namespace std;

int main (int argc, char* argv[])
{
	// check parameters' correctness
	if (argc != 3) 
	{
		cerr << "Usage: " << argv[0] << " in.png out.png" << endl;
		return 1;
	}

	// load the image
	ComplexImage image;
	image.LoadPng (argv[1]);
	
	/*===
	
	Insert Lab 2 code here:
	
	1. Compute the 2D FFT of the image
	2. Perform the frequency domain operation(s)
	3. Compute the inverse 2D FFT of the image
	4. For parts (b) and (c), re-normalize the image
	
	===*/

	int W = int(image.Width());
	int H = int(image.Height());

	std::vector<Complex> container;
	container.resize(W);
	ComplexImage f_image;
	f_image.Resize(H, W);

	// iterate over rows DFT
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			container[j] = image.Pixel(i, j);
		}
		FFT::Transform(container);

		for (int j = 0; j < W; j++) {
			image.Pixel(i, j) = container[j];
		}
	}

	// iterate over columns DFT
	for (int j = 0; j < W; j++) {
		for (int i = 0; i < H; i++) {
			container[i] = image.Pixel(i, j);
		}
		FFT::Transform(container);

		for (int i = 0; i < H; i++) {
			image.Pixel(i, j) = abs(container[i]);
			f_image.Pixel(i, j) = abs(image.Pixel(i, j));
		}
	}

	// iterate over rows IDFT
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			container[j] = image.Pixel(i, j);
		}
		FFT::InverseTransform(container);

		for (int j = 0; j < W; j++) {
			image.Pixel(i, j) = container[j];
		}
	}

	// iterate over columns IDF
	for (int j = 0; j < W; j++) {
		for (int i = 0; i < H; i++) {
			container[i] = image.Pixel(i, j);
		}
		FFT::InverseTransform(container);

		for (int i = 0; i < H; i++) {
			image.Pixel(i, j) = container[i];
		}
	}
	
	// save the image
	image.SavePng (argv[2]);
	
	return 0;
}
