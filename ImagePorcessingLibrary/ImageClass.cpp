#include "ImageClass.h"
#include <fstream>

Image::Image() {
	this->m_height = 0;
	this->m_width = 0;
	//m_daata dynamicalyy allocated
	for (int i = 0; i < 10; i++){
		this->m_data[i] = nullptr;
	}
}

Image::Image(unsigned int width, unsigned int height) {
	this->m_height = height;
	this->m_width = width;
	for (int i = 0; i < 10; i++) {
		this->m_data[i] = new unsigned char[height * width];
	}
}

Image::Image(const Image& img) {
	this->m_height = img.m_height;
	this->m_width = img.m_width;
	for (int i = 0; i < 10; i++) {
		this->m_data[i] = new unsigned char[img.m_height * img.m_width];
		memcpy(this->m_data[i], img.m_data[i], img.m_height * img.m_width);
	}
}

Image& Image::operator=(const Image& img) {
	if (this != &img) {
		this->m_height = img.m_height;
		this->m_width = img.m_width;
		for (int i = 0; i < 10; i++) {
			delete[] this->m_data[i];
			this->m_data[i] = new unsigned char[img.m_height * img.m_width];
			memcpy(this->m_data[i], img.m_data[i], static_cast<size_t>(img.m_height * img.m_width));
		}
	}
	return *this;
}

Image::~Image()
{
	Image::release();
}

void Image::release() {
	for (int i = 0; i < 10; i++) {
		delete[] this->m_data[i];
		this->m_data[i] = nullptr;
	}
}
