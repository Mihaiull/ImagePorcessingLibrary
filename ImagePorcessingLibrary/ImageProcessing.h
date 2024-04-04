#pragma once
#include "ImageClass.h"

//the image processing interface with a pure virtual method signature
class ImageProcessing
{
	public:
	virtual void process(const Image& src, Image& dst);
};

class Brightness : public ImageProcessing
{
public:
	//dst(x,y) = alpha * src(x,y) + beta
	void process(const Image& src, Image& dst) override;
};

class GammaCorrection : public ImageProcessing
{
	//dst(x,y) = src(x,y)^gamma
	void process(const Image& src, Image& dst) override;
};

class ImageConvolution : public ImageProcessing
{
	//dst(x,y) = sum_{i,j} src(x+i,y+j) * kernel(i,j)
	void process(const Image& src, Image& dst) override;

	void setKernel(int option, Image& kernel); //this will set the kernel to identity, mean blur, gaussean blur, horizontal sobel, vertical sobel
	// 1: identity kernel 2: mean blur kernel 3: gaussean blur kernel 4: horizontal sobel kernel 5: vertical sobel kernel
};

class DrawingModule : public ImageProcessing
{
	void setColor(int option);
	void drawCircle(Image& img, Point center, int radius, unsigned char color) const;
	void drawLine(Image& img, Point start, Point end, unsigned char color) const;
	void drawRectangle(Image& img, Rectangle rect, unsigned char color) const;
	void drawRectangle(Image& img, Point topLeft, Point bottomRight, unsigned char color) const;
};