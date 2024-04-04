#include "ImageClass.h"
#include <fstream>
#include <sstream>

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

Image Image::zeros(unsigned int width, unsigned int height) {
	Image img(width, height);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			img.m_data[i][j] = 0;
		}
	}
	return img;
}

Image Image::ones(unsigned int width, unsigned int height) {
	Image img(width, height);
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			img.m_data[i][j] = 255;
		}
	}
	return img;
}



bool Image::getROI(Image& roiImg, Rectangle roiRect) {
	if (roiRect.getX() + roiRect.getWidth() > this->m_width || roiRect.getY() + roiRect.getHeight() > this->m_height) {
		return false;
	}
	roiImg.m_height = roiRect.getHeight();
	roiImg.m_width = roiRect.getWidth();
	for (int i = 0; i < 10; i++) {
		roiImg.m_data[i] = new unsigned char[roiRect.getHeight() * roiRect.getWidth()];
	}
	for (int i = 0; i < roiRect.getHeight(); i++) {
		for (int j = 0; j < roiRect.getWidth(); j++) {
			roiImg.m_data[i][j] = this->m_data[i + roiRect.getY()][j + roiRect.getX()];
		}
	}
	return true;
}

bool Image::getROI(Image& roiImg, unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
	if (x + width > this->m_width || y + height > this->m_height) {
		return false;
	}
	roiImg.m_height = height;
	roiImg.m_width = width;
	for (int i = 0; i < 10; i++) {
		roiImg.m_data[i] = new unsigned char[height * width];
	}
	for (int i = 0; i < height; i++) {
		for (int j = 0; j < width; j++) {
			roiImg.m_data[i][j] = this->m_data[i + y][j + x];
		}
	}
	return true;
}

bool Image::isEmpty() const {
	return this->m_height == 0 && this->m_width == 0 && this->m_data[0] == nullptr;
}

Size Image::size() const {
	Size size;
	size.setHeight(this->m_height);
	size.setWidth(this->m_width);
	return size;
}

unsigned int Image::getWidth() const {
	return this->m_width;
}
unsigned int Image::getHeight() const {
	return this->m_height;
}

unsigned char& Image::at(unsigned int x, unsigned int y) {
	return this->m_data[y][x];
}
unsigned char& Image::at(Point pt) {
	return this->m_data[pt.getY()][pt.getX()];
}

unsigned char* Image::row(int y) {
	return this->m_data[y];
}

bool Image::load(std::string imagePath) {
	std::ifstream file(imagePath);
	if (!file.is_open()) {
		return false;
	}
	std::string line;
	std::getline(file, line);
	if (line != "P2") {
		return false;
	}
	std::getline(file, line);
	while (line[0] == '#') {
		std::getline(file, line);
	}
	std::string width, height;
	std::stringstream ss(line);
	ss >> width >> height;
	this->m_width = std::stoi(width);
	this->m_height = std::stoi(height);
	for (int i = 0; i < 10; i++) {
		this->m_data[i] = new unsigned char[this->m_height * this->m_width];
	}
	std::getline(file, line);
	for (int i = 0; i < this->m_height; i++) {
		for (int j = 0; j < this->m_width; j++) {
			file >> this->m_data[i][j];
		}
	}
	file.close();
	return true;
}

bool Image::save(std::string imagePath) const {
	std::ofstream file(imagePath);
	if (!file.is_open()) {
		return false;
	}
	file << "P2\n";
	file << "# Image\n";
	file << this->m_width << " " << this->m_height << "\n";
	file << "255\n";
	for (int i = 0; i < this->m_height; i++) {
		for (int j = 0; j < this->m_width; j++) {
			file << static_cast<int>(this->m_data[i][j]) << " ";
		}
		file << "\n";
	}
	file.close();
	return true;
}

Image Image::operator+(const Image& img) {
	if (this->m_height != img.m_height || this->m_width != img.m_width) {
		throw std::invalid_argument("Images have different sizes");
	}
	Image result(this->m_width, this->m_height);
	for (int i = 0; i < this->m_height; i++) {
		for (int j = 0; j < this->m_width; j++) {
			result.m_data[i][j] = this->m_data[i][j] + img.m_data[i][j];
		}
	}
	return result;
}

Image Image::operator-(const Image& img) {
	if (this->m_height != img.m_height || this->m_width != img.m_width) {
		throw std::invalid_argument("Images have different sizes");
	}
	Image result(this->m_width, this->m_height);
	for (int i = 0; i < this->m_height; i++) {
		for (int j = 0; j < this->m_width; j++) {
			result.m_data[i][j] = this->m_data[i][j] - img.m_data[i][j];
		}
	}
	return result;
}

Image Image::operator*(double s) {
	Image result(this->m_width, this->m_height);
	for (int i = 0; i < this->m_height; i++) {
		for (int j = 0; j < this->m_width; j++) {
			result.m_data[i][j] = static_cast<unsigned char>(this->m_data[i][j] * s);
		}
	}
	return result;
}

std::ostream& operator<<(std::ostream& os, const Image& dt)
{
	os << "Image: " << dt.m_width << "x" << dt.m_height << std::endl;
	for (int i = 0; i < dt.m_height; i++) {
		for (int j = 0; j < dt.m_width; j++) {
			os << static_cast<int>(dt.m_data[i][j]) << " ";
		}
		os << std::endl;
	}
	return os;
}

std::istream& operator>>(std::istream& is, Image& dt)
{
	std::string line;
	std::getline(is, line);
	if (line != "P2") {
		return is;
	}
	std::getline(is, line);
	while (line[0] == '#') {
		std::getline(is, line);
	}
	std::string width, height;
	std::stringstream ss(line);
	ss >> width >> height;
	dt.m_width = std::stoi(width);
	dt.m_height = std::stoi(height);
	for (int i = 0; i < 10; i++) {
		dt.m_data[i] = new unsigned char[dt.m_height * dt.m_width];
	}
	std::getline(is, line);
	for (int i = 0; i < dt.m_height; i++) {
		for (int j = 0; j < dt.m_width; j++) {
			is >> dt.m_data[i][j];
		}
	}
	return is;
}

void Image::setPixel(unsigned int x, unsigned int y, unsigned char value) {
	this->m_data[y][x] = value;
}

unsigned char Image::getPixel(unsigned int x, unsigned int y) const {
	return this->m_data[y][x];
}