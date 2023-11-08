#include "hw.hpp"

#include <chrono>
#include <algorithm>
using namespace std;

#include "bmp.hpp"
#include "Image.hpp"

Pair::Pair()
{
}

Pair::Pair(int data1, int data2)
{
	this->data[0] = data1;
	this->data[1] = data2;
}

bool Pair::operator<(const Pair& right) const
{
	return this->data[1] < right.data[1];
}

bool Pair::operator>(const Pair& right) const
{
	return this->data[1] > right.data[1];
}

bool PairGreater(const Pair& a, const Pair& b)
{
	return a > b;
}

void binarize()
{
#pragma region C++ program
	Image img;
	img.openBMP("1.bmp");

	auto start = chrono::high_resolution_clock::now();

	img.rgb2gray();
	img.threshold(200);

	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double, ratio<1, 1000>> duration = end - start;

	img.saveBMP("binarized.bmp", true);

	cout << "C++ program: " << duration.count() << "ms" << endl;
#pragma endregion C++ program
#pragma region OpenCV
	Mat im = imread("1.bmp");

	start = chrono::high_resolution_clock::now();

	cvtColor(im, im, COLOR_BGR2GRAY);
	threshold(im, im, 200 - 1, 255, THRESH_BINARY);

	end = chrono::high_resolution_clock::now();
	duration = end - start;

	imwrite("binarized_opencv.bmp", im);
	cout << "Output file: binarized_opencv.bmp" << endl;

	cout << "OpenCV: " << duration.count() << "ms" << endl;
#pragma endregion OpenCV
}

void largest_regions()
{
#pragma region C++ program
	ConnectedComponents cc;
	cc.openBMP("1.bmp");
	cc.rgb2gray();
	cc.threshold(200);

	auto start = chrono::high_resolution_clock::now();

	cc.label();
	cc.largest_regions(5);

	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double, ratio<1, 1000>> duration = end - start;

	cc.saveBMP("largest_regions.bmp", true);

	cout << "C++ program: " << duration.count() << "ms" << endl << endl;
#pragma endregion C++ program
#pragma region OpenCV
	Mat im = imread("1.bmp");
	cvtColor(im, im, COLOR_BGR2GRAY);
	threshold(im, im, 200 - 1, 255, THRESH_BINARY);
	Mat labels, stats, centroids;

	start = chrono::high_resolution_clock::now();

	connectedComponentsWithStats(im, labels, stats, centroids, 4);
	largest_regions_opencv(im, labels, stats, centroids);

	end = chrono::high_resolution_clock::now();
	duration = end - start;

	imwrite("largest_regions_opencv.bmp", im);
	cout << "Output file: largest_regions_opencv.bmp" << endl;

	cout << "OpenCV: " << duration.count() << "ms" << endl;
#pragma endregion OpenCV
}

void morphology()
{
#pragma region C++ program
	Morphology mm;
	mm.openBMP("1.bmp");
	mm.rgb2gray();
	mm.threshold(200);

	auto start = chrono::high_resolution_clock::now();
	mm.setBoxKernel(3);
	mm.erosion();

	mm.setBoxKernel(5, 15);
	mm.dilation();

	mm.setBoxKernel(10, 4);
	mm.erosion();
	mm.dilation();

	mm.kernel.setKernelSize(ImageSize(2, 23), Coordinate(2 / 2, 23 / 2), 0, false);
	mm.kernel.setKernel(Coordinate(0, 0), 255, true);
	mm.kernel.setKernel(Coordinate(1, 0), 255, true);
	mm.kernel.setKernel(Coordinate(0, 22), 255, true);
	mm.kernel.setKernel(Coordinate(1, 22), 255, true);
	mm.erosion();
	mm.dilation();

	//mm.setBoxKernel(3, 19);
	//mm.dilation();
	auto end = chrono::high_resolution_clock::now();
	chrono::duration<double, ratio<1, 1000>> duration = end - start;

	mm.saveBMP("morphology.bmp", true);
	cout << "C++ program: " << duration.count() << "ms" << endl;
#pragma endregion C++ program
#pragma region OpenCV
	Mat im = imread("1.bmp");
	cvtColor(im, im, COLOR_BGR2GRAY);
	threshold(im, im, 200 - 1, 255, THRESH_BINARY);

	start = chrono::high_resolution_clock::now();

	Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));
	erode(im, im, kernel);

	kernel = getStructuringElement(MORPH_RECT, Size(15, 5));
	dilate(im, im, kernel);

	kernel = getStructuringElement(MORPH_RECT, Size(4, 10));
	erode(im, im, kernel);
	dilate(im, im, kernel);

	kernel = getStructuringElement(MORPH_RECT, Size(23, 2));
	for (int i = 1; i <= 21; i++)
	{
		kernel.at<Vec<uchar, 1>>(0, i)[0] = 0;
		kernel.at<Vec<uchar, 1>>(1, i)[0] = 0;
	}
	erode(im, im, kernel);
	dilate(im, im, kernel);

	end = chrono::high_resolution_clock::now();
	duration = end - start;

	imwrite("morphology_opencv.bmp", im);
	cout << "Output file: morphology_opencv.bmp" << endl;

	cout << "OpenCV: " << duration.count() << "ms" << endl;
#pragma endregion OpenCV
}

void largest_regions_opencv(Mat& im, Mat& labels, Mat& stats, Mat& centroids)
{
	int nccomps = stats.rows;
	vector<Pair> pair;
	for (int i = 1; i < nccomps; i++)
	{
		int area = stats.at<Vec<int, 1>>(i, 4)[0];
		pair.push_back(Pair(i, area));
	}
	sort(pair.begin(), pair.end(), PairGreater);

	int rows = im.rows;
	int columns = im.cols;
	Mat im_out(rows, columns, CV_8UC3);
	for (int r = 0; r < rows; r++)
		for (int c = 0; c < columns; c++)
		{
			im_out.at<Vec3b>(r, c)[0] = im.at<Vec<uchar, 1>>(r, c)[0];
			im_out.at<Vec3b>(r, c)[1] = im_out.at<Vec3b>(r, c)[0];
			im_out.at<Vec3b>(r, c)[2] = im_out.at<Vec3b>(r, c)[0];
		}

	for (int i = 0; i < 5; i++)
	{
		int index = pair[i].data[0];
		int area = pair[i].data[1];
		double centroid[2];
		centroid[0] = centroids.at<Vec<double, 1>>(index, 0)[0];
		centroid[1] = centroids.at<Vec<double, 1>>(index, 1)[0];
		Coordinate p[8];
		int up = stats.at<Vec<int, 1>>(index, 1)[0];
		int down = up + stats.at<Vec<int, 1>>(index, 3)[0] - 1;
		int left = stats.at<Vec<int, 1>>(index, 0)[0];
		int right = left + stats.at<Vec<int, 1>>(index, 2)[0] - 1;
		for (int c = left; c <= right; c++)
		{
			int flagUp = 0, flagDown = 0;
			if (labels.at<Vec<int, 1>>(up, c)[0] > 0 && flagUp++ == 0)
				p[0] = Coordinate(up, c);
			if (labels.at<Vec<int, 1>>(down, c)[0] > 0 && flagDown++ == 0)
				p[5] = Coordinate(down, c);
			if (flagUp == 1 && flagDown == 1)
				break;
		}
		for (int c = right; c >= left; c--)
		{
			int flagUp = 0, flagDown = 0;
			if (labels.at<Vec<int, 1>>(up, c)[0] > 0 && flagUp++ == 0)
				p[1] = Coordinate(up, c);
			if (labels.at<Vec<int, 1>>(down, c)[0] > 0 && flagDown++ == 0)
				p[4] = Coordinate(down, c);
			if (flagUp == 1 && flagDown == 1)
				break;
		}
		for (int r = up; r <= down; r++)
		{
			int flagLeft = 0, flagRight = 0;
			if (labels.at<Vec<int, 1>>(r, left)[0] > 0 && flagLeft++ == 0)
				p[7] = Coordinate(r, left);
			if (labels.at<Vec<int, 1>>(r, right)[0] > 0 && flagRight++ == 0)
				p[2] = Coordinate(r, right);
			if (flagLeft == 1 && flagRight == 1)
				break;
		}
		for (int r = down; r >= up; r--)
		{
			int flagLeft = 0, flagRight = 0;
			if (labels.at<Vec<int, 1>>(r, left)[0] > 0 && flagLeft++ == 0)
				p[6] = Coordinate(r, left);
			if (labels.at<Vec<int, 1>>(r, right)[0] > 0 && flagRight++ == 0)
				p[3] = Coordinate(r, right);
			if (flagLeft == 1 && flagRight == 1)
				break;
		}
		double m[4] = { 0 };
		m[0] = p[0].length(p[4]);
		m[1] = p[1].length(p[5]);
		m[2] = p[2].length(p[6]);
		m[3] = p[3].length(p[7]);
		int max_L = (int)distance(m, max_element(m, m + 3));
		double max_O = p[max_L].orientation(p[max_L + 4]);
		max_O = max_O / 3.14159265358979323846 * 180.0;

		cout << i + 1 << " rigion:" << endl;
		cout << "area-> " << area << endl;
		cout << "centroid-> (" << centroid[1] << ", " << centroid[0] << ")" << endl;
		cout << "longest length-> " << m[max_L] << endl;
		cout << "orientation-> " << max_O << endl << endl;

		up = (up - 1 < 0) ? 0 : up - 1;
		down = (down + 1 > rows) ? rows : down + 1;
		left = (left - 1 < 0) ? 0 : left - 1;
		right = (right + 1 > columns) ? columns : right + 1;
		for (int r = up; r <= down; r++)
		{
			im_out.at<Vec3b>(r, left)[0] = 0;
			im_out.at<Vec3b>(r, left)[1] = 0;
			im_out.at<Vec3b>(r, left)[2] = 255;
			im_out.at<Vec3b>(r, right)[0] = 0;
			im_out.at<Vec3b>(r, right)[1] = 0;
			im_out.at<Vec3b>(r, right)[2] = 255;
		}
		for (int c = left; c <= right; c++)
		{
			im_out.at<Vec3b>(up, c)[0] = 0;
			im_out.at<Vec3b>(up, c)[1] = 0;
			im_out.at<Vec3b>(up, c)[2] = 255;
			im_out.at<Vec3b>(down, c)[0] = 0;
			im_out.at<Vec3b>(down, c)[1] = 0;
			im_out.at<Vec3b>(down, c)[2] = 255;
		}
	}

	im = im_out.clone();
}
