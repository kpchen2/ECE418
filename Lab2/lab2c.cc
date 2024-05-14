/*===
lab2c-skeleton.cc

Abstract: Skeleton for Lab 2 part (c)
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
	if (argc != 4) 
	{
		cerr << "Usage: " << argv[0] << " in.png out.png frequency" << endl;
		return 1;
	}
	double frequency = atof (argv[3]);
	if (frequency < 0 || frequency > 0.5)
	{
		cerr << "Cutoff frequency must be in [0,0.5]" << endl;
		return 1;
	}

	// load the image
	ComplexImage image;
	image.LoadPng (argv[1]);
	
	/*===
	
	Insert Lab 2 code here:
	
	1. Compute the 2D FFT of the image
	2. Perform the frequency domain operation
	3. Compute the inverse 2D FFT of the image
	4. Re-normalize the image
	
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
			image.Pixel(i, j) = container[i];
			f_image.Pixel(i, j) = abs(image.Pixel(i, j));
		}
	}

	// filtering
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < W; j++) {
			if (pow(pow(i, 2) + pow(j, 2), 0.5) <= frequency * H) {

			}
			else if (pow(pow(W - i, 2) + pow(j, 2), 0.5) <= frequency * H) {

			}
			else if (pow(pow(W - i, 2) + pow(H - j, 2), 0.5) <= frequency * H) {

			}
			else if (pow(pow(i, 2) + pow(H - j, 2), 0.5) <= frequency * H) {

			}
			else {
				image.Pixel(i, j) = 0;
			}
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

	// find lowest/highest values
	Complex minValue = image.Pixel(0, 0);
	Complex maxValue = image.Pixel(0, 0);
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < H; j++) {
			if (image.Pixel(i, j).real() > maxValue.real()) {
				maxValue = image.Pixel(i, j);
			}
			if (image.Pixel(i, j).real() < minValue.real()) {
				minValue = image.Pixel(i, j);
			}
		}
	}

	// normalize
	for (int i = 0; i < H; i++) {
		for (int j = 0; j < H; j++) {
			image.Pixel(i, j) = (image.Pixel(i, j) - minValue).real() * 255 / (maxValue - minValue).real();
		}
	}
	
	// save the image
	image.SavePng (argv[2]);
	
	return 0;
}
