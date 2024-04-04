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
	}
	default:
	{
		cout << "Invalid option!" << endl;
		break;
	}
	}

}


void ImageConvolution::process(const Image & src, Image & dst)
{
	cout << "Applying image convolution filter..." << endl;
	cout << "Source image size: " << src.size().getWidth() << "x" << src.size().getHeight() << endl;
	Image kernel(3, 3);
	setKernel(1, kernel);
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

void DrawingModule::setColor(int option)
{
	switch (option)
	{
	case 1:
	{
		cout << "Color: Black" << endl;
		break;
	}
	case 2:
	{
		cout << "Color: White" << endl;
		break;
	}
	default:
	{
		cout << "Invalid option!" << endl;
		break;
	}
	}
}

void DrawingModule::drawCircle(Image& img, Point center, int radius, unsigned char color) const
{
	cout << "Drawing circle..." << endl;
	cout << "Center: (" << center.getX() << ", " << center.getY() << ")" << endl;
	cout << "Radius: " << radius << endl;
	cout << "Color: " << static_cast<int>(color) << endl;
	if (radius <= 0)
	{
		cout << "Invalid radius!" << endl;
		return;
	}
	for (int i = 0; i < img.size().getHeight(); i++)
	{
		for (int j = 0; j < img.size().getWidth(); j++)
		{
			if ((i - center.getX()) * (i - center.getX()) + (j - center.getY()) * (j - center.getY()) <= radius * radius) //didn't have cmath included
			{
				img.setPixel(i, j, color);
			}
		}
	}
}

void DrawingModule::drawLine(Image& img, Point start, Point end, unsigned char color) const
{
	cout << "Drawing line..." << endl;
	cout << "Start: (" << start.getX() << ", " << start.getY() << ")" << endl;
	cout << "End: (" << end.getX() << ", " << end.getY() << ")" << endl;
	cout << "Color: " << static_cast<int>(color) << endl;
	if (start.getX() == end.getX() && start.getY() == end.getY())
	{
		cout << "Invalid line!" << endl;
		return;
	}
	int dx = end.getX() - start.getX();
	int dy = end.getY() - start.getY();
	if (abs(dx) > abs(dy))
	{
		if (start.getX() > end.getX())
		{
			swap(start, end);
		}
		for (int i = start.getX(); i <= end.getX(); i++)
		{
			int j = start.getY() + dy * (i - start.getX()) / dx;
			img.setPixel(i, j, color);
		}
	}
	else
	{
		if (start.getY() > end.getY())
		{
			swap(start, end);
		}
		for (int j = start.getY(); j <= end.getY(); j++)
		{
			int i = start.getX() + dx * (j - start.getY()) / dy;
			img.setPixel(i, j, color);
		}
	}
}

void DrawingModule::drawRectangle(Image& img, Rectangle rect, unsigned char color) const
{
	cout << "Drawing rectangle..." << endl;
	cout << "Top-left: (" << rect.getX() << ", " << rect.getY() << ")" << endl;
	cout << "Bottom-right: (" << rect.getX() + rect.getWidth() << ", " << rect.getY() + rect.getHeight() << ")" << endl;
	cout << "Color: " << static_cast<int>(color) << endl;
	if (rect.getWidth() <= 0 || rect.getHeight() <= 0)
	{
		cout << "Invalid rectangle!" << endl;
		return;
	}
	for (int i = rect.getX(); i < rect.getX() + rect.getWidth(); i++)
	{
		img.setPixel(i, rect.getY(), color);
		img.setPixel(i, rect.getY() + rect.getHeight() - 1, color);
	}
	for (int j = rect.getY(); j < rect.getY() + rect.getHeight(); j++)
	{
		img.setPixel(rect.getX(), j, color);
		img.setPixel(rect.getX() + rect.getWidth() - 1, j, color);
	}
}

void DrawingModule::drawRectangle(Image& img, Point topLeft, Point bottomRight, unsigned char color) const
{
	cout << "Drawing rectangle..." << endl;
	cout << "Top-left: (" << topLeft.getX() << ", " << topLeft.getY() << ")" << endl;
	cout << "Bottom-right: (" << bottomRight.getX() << ", " << bottomRight.getY() << ")" << endl;
	cout << "Color: " << static_cast<int>(color) << endl;
	if (topLeft.getX() >= bottomRight.getX() || topLeft.getY() >= bottomRight.getY())
	{
		cout << "Invalid rectangle!" << endl;
		return;
	}
	for (int i = topLeft.getX(); i <= bottomRight.getX(); i++)
	{
		img.setPixel(i, topLeft.getY(), color);
		img.setPixel(i, bottomRight.getY(), color);
	}
	for (int j = topLeft.getY(); j <= bottomRight.getY(); j++)
	{
		img.setPixel(topLeft.getX(), j, color);
		img.setPixel(bottomRight.getX(), j, color);
	}
}