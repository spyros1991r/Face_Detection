#include <iostream>
#include <vector>
#include <math.h>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
namespace formulas1{
	void Formulas();

	double E1(int M, int N,cv::Mat dct1);

	double E_DC(int M, int N, cv::Mat dct1,double E);

	double E_H(int M, int N, cv::Mat dct1,double E);

	double E_V(int M, int N, cv::Mat dct1, double E);

}

