#ifndef _IMAGE_
#define _IMAGE_

#define _USE_MATH_DEFINES

#include <cmath>
#include <cstdio>
#include <cstdint>

#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

#include "bmp.hpp"

enum class ColorSpace
{
	RGB,
	GRAY,
	Binary,
	HSV,
	HSL
};

class ImageSize
{
public:
	int rows;
	int columns;
	int size();

	ImageSize();
	ImageSize(int rows, int columns);
	ImageSize(const ImageSize& source);
	ImageSize operator=(const ImageSize& other);
	ImageSize operator*(const double& other);
	ImageSize operator/(const double& other);
	bool operator==(const ImageSize& other);
	bool operator!=(const ImageSize& other);
};

class Image
{
public:
	ColorSpace color;
	ImageSize size;
	vector<vector<uint8_t>> img_0;	// R, Gray, V, L
	vector<vector<uint8_t>> img_1;	// G		S, S
	vector<vector<uint8_t>> img_2;	// B		H, H
	void openBMP(const char* FileName);
	void saveBMP(const char* FileName, bool printName);
	void saveBMP(const char* FileName, int channel, bool printName);
	void rgb2gray();
	void rgb2hsv();
	void rgb2hsl();
	void threshold(uint8_t th);
	void threshold(uint8_t th, int channel);

	Image();
	Image(const Image& source);
	Image(const vector<vector<uint8_t>>& img_0);
	Image(const vector<vector<uint8_t>>& img_0, const vector<vector<uint8_t>>& img_1, const vector<vector<uint8_t>>& img_2);
	Image(ImageSize size, uint8_t value);
	Image operator=(const Image& other);

protected:
	BMP bmp;
	uint8_t mapping(double value, double min_f, double max_f, uint8_t min_i, uint8_t max_i);
	vector<vector<uint8_t>> padding(vector<vector<uint8_t>>& img, int pad);
};

class Coordinate
{
public:
	int row;
	int column;
	double length(const Coordinate& source);
	double orientation(const Coordinate& source);

	Coordinate();
	Coordinate(int row, int column);
	Coordinate(const Coordinate& source);
	Coordinate operator=(const Coordinate& other);
	bool operator==(const Coordinate& other);
	bool operator!=(const Coordinate& other);
};

class CCpair
{
public:
	int up;
	int left;
	CCpair(const int& up, const int& left);
};

class ConnectedComponents : public Image
{
public:
	int numOfRegion;
	vector<vector<int>> table;
	void label();
	void largest_regions(int num);
	void RegionsToGray();

	ConnectedComponents();
	ConnectedComponents(const vector<vector<uint8_t>>& img);

private:
	void madeEqList(vector<vector<int>>& equivalence, const vector<vector<bool>>& regionTable, int region);
	int checkEquivalence(const vector<vector<int>>& equivalence, int in);
};

class MorphologyKernel
{
public:
	Coordinate origin;
	ImageSize kernelSize;
	vector<vector<bool>> valid;
	vector<vector<uint8_t>> binary;
	void setKernelSize(ImageSize kernelSize, Coordinate origin = Coordinate(0, 0), uint8_t binary = 255, bool valid = true);
	void setKernel(Coordinate coord, uint8_t binary, bool valid);

	MorphologyKernel();
	MorphologyKernel(int rows, int columns);
	MorphologyKernel operator=(const MorphologyKernel& other);
};

class Morphology : public ConnectedComponents
{
public:
	MorphologyKernel kernel;
	void setStarKernel(int n);
	void setStarKernel(int rows, int columns);
	void setBoxKernel(int n);
	void setBoxKernel(int rows, int columns);
	void dilation();
	void erosion();

	Morphology();
};

#endif /* _IMAGE_ */