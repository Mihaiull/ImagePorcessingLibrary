#include "ImageProcessing.h"
#include "ImageClass.h"
#include "SizeClass.h"
#include "PointClass.h"
#include "RectangleClass.h"
#include <iostream>

using namespace std; //pentru ca dintr-un motiv sau altul la momentul scrierii codului am uitat ca input-u si outputu se face in ui si l-am facut direct in functii sunt un geniu ce pot sa zic


void ImageProcessing::process(const Image& src, Image& dst)
{
		cout << "Processing image..." << endl;
		cout << "Source image size: " << src.size().getWidth() << "x" << src.size().getHeight() << endl;
}

void Brightness::process(const Image& src, Image& dst)
{
	cout << "Applying brightness filter..." << endl;
	cout << "Source image size: " << src.size().getWidth() << "x" << src.size().getHeight() << endl;
	float alpha = 0.0, beta = 0.0;
	cout<< "Enter alpha and beta values: ";
	cin >> alpha;
	cin >> beta;
	for (int i = 0; i < src.size().getHeight(); i++)
	{
		for (int j = 0; j < src.size().getWidth(); j++)
		{
			dst.setPixel(i, j, alpha * src.getPixel(i, j) + beta);
		}
	}
}

void GammaCorrection::process(const Image& src, Image& dst)
{
	cout << "Applying gamma correction filter..." << endl;
	cout << "Source image size: " << src.size().getWidth() << "x" << src.size().getHeight() << endl;
	float gamma = 0.0;
	cout << "Enter gamma value: ";
	cin >> gamma;
	for (int i = 0; i < src.size().getHeight(); i++)
	{
		for (int j = 0; j < src.size().getWidth(); j++)
		{
			dst.setPixel(i, j, pow(src.getPixel(i, j), gamma));
		}
	}
}

void ImageConvolution::setKernel(int option, Image& kernel)
{
	switch (option)
	{
	case 1: //identity
	{
		kernel.setPixel(0, 0, 0);
		kernel.setPixel(0, 1, 0);
		kernel.setPixel(0, 2, 0);
		kernel.setPixel(1, 0, 0);	
		kernel.setPixel(1, 1, 1);
		kernel.setPixel(1, 2, 0);
		kernel.setPixel(2, 0, 0);
		kernel.setPixel(2, 1, 0);
		kernel.setPixel(2, 2, 0);
		break;
	}
	case 2: //mean blur
	{
		kernel.setPixel(0, 0, 1);
		kernel.setPixel(0, 1, 1);
		kernel.setPixel(0, 2, 1);
		kernel.setPixel(1, 0, 1);
		kernel.setPixel(1, 1, 1);
		kernel.setPixel(1, 2, 1);
		kernel.setPixel(2, 0, 1);
		kernel.setPixel(2, 1, 1);
		kernel.setPixel(2, 2, 1);
		break;
	}
	case 3: //3x3 gaussean blur
	{
		kernel.setPixel(0, 0, 1);
		kernel.setPixel(0, 1, 2);
		kernel.setPixel(0, 2, 1);
		kernel.setPixel(1, 0, 2);
		kernel.setPixel(1, 1, 4);
		kernel.setPixel(1, 2, 2);
		kernel.setPixel(2, 0, 1);
		kernel.setPixel(2, 1, 2);
		kernel.setPixel(2, 2, 1);
		break;
	}
	case 4: //horizontal sobel
	{
		kernel.setPixel(0, 0, -1);
		kernel.setPixel(0, 1, 0);
		kernel.setPixel(0, 2, 1);
		kernel.setPixel(1, 0, -2);
		kernel.setPixel(1, 1, 0);
		kernel.setPixel(1, 2, 2);
		kernel.setPixel(2, 0, -1);
		kernel.setPixel(2, 1, 0);
		kernel.setPixel(2, 2, 1);
		break;
	}
	case 5: //vertical sobel
	{
		kernel.setPixel(0, 0, -1);
		kernel.setPixel(0, 1, -2);
		kernel.setPixel(0, 2, -1);
		kernel.setPixel(1, 0, 0);
		kernel.setPixel(1, 1, 0);
		kernel.setPixel(1, 2, 0);
		kernel.setPixel(2, 0, 1);
		kernel.setPixel(2, 1, 2);
		kernel.setPixel(2, 2, 1);
		break;
	
	default:
	{
		cout << "Invalid option!" << endl;
		break;
	}
	}
}

void ImageConvolution::process(Image& src, Image& dst)
{
	cout << "Applying image convolution filter..." << endl;
	cout << "Source image size: " << src.size().getWidth() << "x" << src.size().getHeight() << endl;
	Image kernel(3, 3);
	cout << "Enter kernel option: ";
	cout << "1: identity kernel \n2: mean blur kernel \n3: gaussean blur kernel \n4: horizontal sobel kernel \n5: vertical sobel kernel\n Your choice: " << endl;
	int option=1; //default identity kernel
	cin >> option;
	setKernel(option, kernel);
	for (int i = 0; i < src.size().getHeight(); i++)
	{
		for (int j = 0; j < src.size().getWidth(); j++)
		{
			int sum = 0;
			for (int k = 0; k < 3; k++)
			{
				for (int l = 0; l < 3; l++)
				{
					sum += src.getPixel(i + k, j + l) * kernel.getPixel(k, l);
				}
			}
			dst.setPixel(i, j, sum);
		}
	}
}