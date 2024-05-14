/*===
lab4-skeleton.cc

Abstract: Skeleton for Lab 4
===*/

#include <stdlib.h>
#include <iostream>
#include <vector>
#include "image.h"
#include <math.h>
using namespace std;

int main(int argc, char* argv[])
{
	Image image;
	image.Resize(512, 512);

	/*===

	Insert Lab 4 code here

	===*/

	// part 1a
	for (int i = 0; i < image.Width(); i++) {
		for (int j = 0; j < image.Height(); j++) {
			image.Pixel(i, j) = float(int(i / (image.Width() / 8)) * (255.0 / 7));
		}
	}
	image.SavePng("Lab4_1a.png");

	// part 1b
	for (int i = 0; i < image.Width(); i++) {
		for (int j = 0; j < image.Height(); j++) {
			image.Pixel(i, j) = float(int(j / (image.Width() / 8)) * (255.0 / 7));
		}
	}
	image.SavePng("Lab4_1b.png");

	// part 2
	image.Resize(1024, 512);
	for (int i = 0; i < image.Width(); i++) {
		float freq = (float(i) / (image.Width() - 1)) * (M_PI / 3);
		for (int j = 0; j < image.Height(); j++) {
			float amp = (1 - (float(j) / (image.Height() - 1))) * 127.5;
			image.Pixel(i, j) = amp * (1 + sin(freq * i));
		}
	}
	image.SavePng("Lab4_2.png");

	// part 3
	float s1 = 75;
	float s2 = 50;
	float B1 = 25;
	float B2 = 25;
	for (int i = 0; i < image.Width(); i++) {
		for (int j = 0; j < image.Height(); j++) {
			if (i >= (image.Width() / 4) - 32 && i < (image.Width() / 4) + 32 && j >= (image.Height() / 2) - 32 && j < (image.Height() / 2) + 32) {
				image.Pixel(i, j) = B1;
			}
			else if (i >= (image.Width() * 3 / 4) - 32 && i < (image.Width() * 3 / 4) + 32 && j >= (image.Height() / 2) - 32 && j < (image.Height() / 2) + 32) {
				image.Pixel(i, j) = B2;
			} else if (i < image.Width() / 2) {
				image.Pixel(i, j) = s1;
			}
			else {
				image.Pixel(i, j) = s2;
			}
		}
	}
	image.SavePng("Lab4_3.png");

	// part 4
	float I = 255;
	float F = 254;
	image.Resize(512, 512);
	for (int i = 0; i < image.Width(); i++) {
		for (int j = 0; j < image.Height(); j++) {
			if (i >= image.Width() / 2 - 4 && i < image.Width() / 2 + 4 && j >= image.Height() / 2 - 4 && j < image.Height() / 2 + 4) {
				image.Pixel(i, j) = F;
			}
			else {
				image.Pixel(i, j) = I;
			}
		}
	}
	image.SavePng("Lab4_4.png");

	return 0;
}
