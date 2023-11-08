#ifndef _HW_
#define _HW_

#include <opencv2\opencv.hpp>
using namespace cv;

class Pair
{
public:
	int data[2];
	Pair();
	Pair(int data1, int data2);
	bool operator<(const Pair& right) const;
	bool operator>(const Pair& right) const;
};

bool PairGreater(const Pair& a, const Pair& b);

void binarize();
void largest_regions();
void morphology();
void largest_regions_opencv(Mat& im, Mat& labels, Mat& stats, Mat& centroids);

#endif /* _HW_ */