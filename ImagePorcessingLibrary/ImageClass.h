#pragma once
#include <string>
#include <iostream>

/*
Remember to actually do these libraries before running it
*/
//#include "Size.h"
//#include "Point.h"
//#include "Rectangle.h"


//the images we will be working with will be .ascii.pgm. 
/*
Pgm image example:

P2
# Comentariu de exemplu
4 4
255
0 0 0 0
0 255 255 0
0 255 255 0
0 0 0 0
*/
class Image
{
public:
	Image(); //the default constructor, in which m_data is set to nullptr, m_width and m_height are set to 0.
	Image(unsigned int width, unsigned int height); //a parameterized constructor which creates a new Image instance with the specified width and height. All the pixels will be initialised to 0
	Image(const Image& other); //copy constructor
	Image& operator=(const Image& other); //copy assignment operator
	~Image(); //destructor
	bool load(std::string imagePath); //a method to load an image from a file. The method should return true if the image was loaded successfully, and false otherwise.
	bool save(std::string imagePath) const; //a method to save the image to a file. The method should return true if the image was saved successfully, and false otherwise.

	Image operator+(const Image& i);
	Image operator-(const Image& i);
	Image operator*(double s);
	//bool getROI(Image& roiImg, Rectangle roiRect);
	bool setROI(Image &roiImg, unsigned int x, unsigned int y, unsigned int width, unsigned int height);

	bool isEmpty() const; //returns true if the image is empty (i.e. m_data is nullptr and m_height and m_width are 0), and false otherwise.

	//Size size()	const; //a method to return the size of the image as an object of the Size class.

	unsigned int getWidth() const;
	unsigned int getHeight() const;

	unsigned char& at(unsigned int x, unsigned int y);
	//unsigned char& at(Point pt);

	unsigned char* row(int y);

	void release(); //a method to release the memory allocated for the image pixels. The method will be called in the destructor.

	friend std::ostream& operator<<(std::ostream& os, const Image& dt);
	friend std::istream& operator>>(std::istream& is, Image& dt);
	static Image zeros(unsigned int width, unsigned int height);
	static Image ones(unsigned int width, unsigned int height);

private:
	unsigned char** m_data; //a pointer to a pointer of unsigned char which will store the image pixels. This data must be dynamically alocated on the heap.
	//two variables of type unsigned int to store the width and height of the image.
	unsigned int m_width;
	unsigned int m_height;
};