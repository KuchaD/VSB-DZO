// DIP.cpp : Defines the entry point for the console application.
//

#define _USE_MATH_DEFINES
#include "stdafx.h"
#define _USE_MATH_DEFINES
#include <math.h>

#define SQR(x) ( ( x ) * ( x ) )
#define DEG2RAD(x) ( ( x ) * M_PI / 180.0 )
#define MY_MIN(X, Y) ( ( X ) < ( Y ) ? ( X ) : ( Y ) )
#define MY_MAX(X, Y) ( ( X ) > ( Y ) ? ( X ) : ( Y ) )
#define L 256

void Cv2();
void Cv3();
void Cv4_1();
void Cv4_2();
void Cv5();
void Cv6();
void Cv7();
void Cv8();
void Cv11();
void Cv12();

void flipQuadrants(cv::Mat &source);
void Phase(cv::Mat &furier, cv::Mat &dest);
void Power(cv::Mat &furier, cv::Mat &dest);
void InverseFurier(cv::Mat &furier, cv::Mat &dest);
void Filter(cv::Mat &furier, cv::Mat &mask);
void Furier(cv::Mat &img, cv::Mat &dest);
cv::Mat calcHistogram(cv::Mat &src);
cv::Mat drawHistogram(cv::Mat &hist);
int cdfMin(cv::Mat &cdf);
cv::Mat calcCdf(cv::Mat &hist);

void CentralDerivationEdge(cv::Mat &img, cv::Mat &dest);
void Edge(cv::Mat &img, cv::Mat &dest);
void SobelEdgeFilter(cv::Mat &img, cv::Mat &dest);

cv::Mat UseConvolution(cv::Mat src_Image, double *kernel[], int lenght_kernel, double Normalize = 1.0);
cv::Mat UseConvolutionGray(cv::Mat src_Image, double *kernel[], int lenght_kernel, double Normalize = 1.0);


using namespace std;
int main()
{
	
	//cv::Mat src_8uc3_img = cv::imread("images/lena.png", CV_LOAD_IMAGE_COLOR); // load color image from file system to Mat variable, this will be loaded using 8 bits (uchar)

	//if (src_8uc3_img.empty()) {
	//	printf("Unable to read input file (%s, %d).", __FILE__, __LINE__);
	//}

	////cv::imshow( "LENA", src_8uc3_img );

	//cv::Mat gray_8uc1_img; // declare variable to hold grayscale version of img variable, gray levels wil be represented using 8 bits (uchar)
	//cv::Mat gray_32fc1_img; // declare variable to hold grayscale version of img variable, gray levels wil be represented using 32 bits (float)

	//cv::cvtColor(src_8uc3_img, gray_8uc1_img, CV_BGR2GRAY); // convert input color image to grayscale one, CV_BGR2GRAY specifies direction of conversion
	//gray_8uc1_img.convertTo(gray_32fc1_img, CV_32FC1, 1.0 / 255.0); // convert grayscale image from 8 bits to 32 bits, resulting values will be in the interval 0.0 - 1.0

	//int x = 10, y = 15; // pixel coordinates

	//uchar p1 = gray_8uc1_img.at<uchar>(y, x); // read grayscale value of a pixel, image represented using 8 bits
	//float p2 = gray_32fc1_img.at<float>(y, x); // read grayscale value of a pixel, image represented using 32 bits
	//cv::Vec3b p3 = src_8uc3_img.at<cv::Vec3b>(y, x); // read color value of a pixel, image represented using 8 bits per color channel

	//// print values of pixels
	//printf("p1 = %d\n", p1);
	//printf("p2 = %f\n", p2);
	//printf("p3[ 0 ] = %d, p3[ 1 ] = %d, p3[ 2 ] = %d\n", p3[0], p3[1], p3[2]);

	//gray_8uc1_img.at<uchar>(y, x) = 0; // set pixel value to 0 (black)

	//// draw a rectangle
	//cv::rectangle(gray_8uc1_img, cv::Point(65, 84), cv::Point(75, 94),
	//	cv::Scalar(50), CV_FILLED);

	//// declare variable to hold gradient image with dimensions: width= 256 pixels, height= 50 pixels.
	//// Gray levels wil be represented using 8 bits (uchar)
	//cv::Mat gradient_8uc1_img(50, 256, CV_8UC1);

	//// For every pixel in image, assign a brightness value according to the x coordinate.
	//// This wil create a horizontal gradient.
	//for (int y = 0; y < gradient_8uc1_img.rows; y++) {
	//	for (int x = 0; x < gradient_8uc1_img.cols; x++) {
	//		gradient_8uc1_img.at<uchar>(y, x) = x;
	//	}
	//}

	// diplay images
	//cv::imshow("Gradient", gradient_8uc1_img);
	//cv::imshow("Lena gray", gray_8uc1_img);
	//cv::imshow("Lena gray 32f", gray_32fc1_img);

	Cv12();
	//exercise4();
	cv::waitKey(0); // wait until keypressed

	return 0;
}

static void Cv2() 
{
	cv::Mat gray_8uc1_img = cv::imread("images/moon.jpg", CV_LOAD_IMAGE_GRAYSCALE); // load color image from file system to Mat variable, this will be loaded using 8 bits (uchar)
	cv::imshow("Moon", gray_8uc1_img);

	double min, max;
	cv::minMaxLoc(gray_8uc1_img, &min, &max);

	uchar max_8UC = max * 255;
	uchar min_8UC = min * 255;

	for (int y = 0; y < gray_8uc1_img.rows; y++) {
		for (int x = 0; x < gray_8uc1_img.cols; x++) {
			gray_8uc1_img.at<uchar>(y, x) = (gray_8uc1_img.at<uchar>(y, x) - min) / (max - min) * 255;
		}
	}


	cv::imshow("Moon", gray_8uc1_img);
}

static void Cv3()
{
	cv::Mat src_8uc3_img = cv::imread("images/lena.png", CV_LOAD_IMAGE_COLOR); // load color image from file system to Mat variable, this will be loaded using 8 bits (uchar)
	cv::imshow("Moon org", src_8uc3_img);

	for (int y = 0; y < src_8uc3_img.rows; y++) {
		for (int x = 0; x < src_8uc3_img.cols; x++) {
			for (int c = 0; c < 3; c++) {
				
				double l = (double)src_8uc3_img.at<cv::Vec3b>(y, x)[c] / 255.0;
				double gamma = 2.2;
				double cor = pow(l,gamma) * 255.0;
				src_8uc3_img.at<cv::Vec3b>(y, x)[c] = (uchar)cor;
			}
			
		}
	}

	cv::imshow("Moon gamma", src_8uc3_img);
	
}
static cv::Mat UseConvolution(cv::Mat src_Image,  double *kernel[],int lenght_kernel,double Normalize)
{

	cv::Mat color_8uc3_img = src_Image.clone();
	int lval;
	int mask;
	int cutPixel = lenght_kernel / 2;
	

	
		for (int y = cutPixel; y < src_Image.rows - cutPixel; y++) {
			for (int x = cutPixel; x < src_Image.cols - cutPixel; x++) {
				double r = 0, g = 0, b = 0;
				for (int i = 0; i < lenght_kernel; i++)
				{

					for (int j = 0; j < lenght_kernel; j++) {
						mask = kernel[i][j];
						cv::Vec3b lValue = src_Image.at<cv::Vec3b>(y - cutPixel + i, x - cutPixel + j);
						r = r + (lValue[2] * mask);
						g = g + (lValue[1] * mask);
						b = b + (lValue[0] * mask);

					}

				}
				color_8uc3_img.at<cv::Vec3b>(y, x)[0] = b / Normalize;
				color_8uc3_img.at<cv::Vec3b>(y, x)[1] = g / Normalize;
				color_8uc3_img.at<cv::Vec3b>(y, x)[2] = r / Normalize;
			}
		}

		
	return color_8uc3_img;
}

static cv::Mat UseConvolutionGray(cv::Mat src_Image, double *kernel[], int lenght_kernel, double Normalize)
{

	cv::Mat color_8uc3_img = src_Image.clone();
	int lval;
	int mask;
	int cutPixel = lenght_kernel / 2;



	for (int y = cutPixel; y < src_Image.rows - cutPixel; y++) {
		for (int x = cutPixel; x < src_Image.cols - cutPixel; x++) {
			double r = 0, g = 0, b = 0;
			for (int i = 0; i < lenght_kernel; i++)
			{

				for (int j = 0; j < lenght_kernel; j++) {
					mask = kernel[i][j];
					uchar lValue = src_Image.at<uchar>(y - cutPixel + i, x - cutPixel + j);
					r = r + (lValue * mask);
					

				}

			}
			if (r < 0)
				r = 0;
			color_8uc3_img.at<uchar>(y,x) = r / Normalize;
			
		}
	}


	return color_8uc3_img;
}

static void Cv4_1()
{
	cv::Mat src_8uc3_img = cv::imread("images/lena.png", CV_LOAD_IMAGE_COLOR); // load color image from file system to Mat variable, this will be loaded using 8 bits (uchar)
	cv::imshow("Lena org", src_8uc3_img);

	
	int lval;
	int mask;
	int lenght = 3;
	

	double *kernel[3];
	kernel[0] = new double[3]{ 1,2,1 };
	kernel[1] = new double[3]{ 2,4,2 };
	kernel[2] = new double[3]{ 1,2,1 };
	

	cv::imshow("Lenna conv", UseConvolution(src_8uc3_img,kernel,3,16));
}

static void Cv4_2()
{
	cv::Mat src_8uc3_img = cv::imread("images/lena.png", CV_LOAD_IMAGE_COLOR); // load color image from file system to Mat variable, this will be loaded using 8 bits (uchar)
	cv::imshow("Lena org", src_8uc3_img);

	cv::Mat color_8uc3_img = src_8uc3_img.clone();
	int lval;
	int mask;
	int lenght = 5;


	double kernel[5][5] = { {1,4,6,4,1},
							{4,16,24,16,4},
							{6,24,36,24,6},
							{4,16,24,16,4},
							{1,4,6,4,1} };

	for (int y = 2; y < src_8uc3_img.rows - 2; y++) {
		for (int x = 2; x < src_8uc3_img.cols - 2; x++) {
			double r = 0, g = 0, b = 0;
			for (int i = 0; i < lenght; i++)
			{

				for (int j = 0; j < lenght; j++) {
					mask = kernel[i][j];
					cv::Vec3b lValue = src_8uc3_img.at<cv::Vec3b>(y - 2 + i, x - 2 + j);
					r = r + (lValue[2] * mask);
					g = g + (lValue[1] * mask);
					b = b + (lValue[0] * mask);

				}

			}
			color_8uc3_img.at<cv::Vec3b>(y, x)[0] = b / 256;
			color_8uc3_img.at<cv::Vec3b>(y, x)[1] = g / 256;
			color_8uc3_img.at<cv::Vec3b>(y, x)[2] = r / 256;
		}
 	}

	cv::imshow("Lenna conv", color_8uc3_img);
}
static void Cv5()
{
	cv::Mat src_8UC3_img = cv::imread("images/lena.png", CV_LOAD_IMAGE_COLOR);

	if (src_8UC3_img.empty()) {
		printf("Unable to read input file (%s, %d).", __FILE__, __LINE__);
	}
	
	cv::Mat src_64FC3_img ;
	src_8UC3_img.convertTo(src_64FC3_img, CV_64FC3,1.0/255.0);
	cv::imshow("Original", src_64FC3_img);
	

	double lambda = 0.1;
	double sigma = 0.5;

	int iterations = 30;


	cv::Mat edit_64FC3_img(src_64FC3_img.rows, src_64FC3_img.cols, CV_64FC3);
	
	
	for (int i = 0; i < iterations; i++)
	{
		for (int y = 1; y < src_64FC3_img.rows - 1; y++)
		{
			for (int x = 1; x < src_64FC3_img.cols - 1; x++)
			{
				
				for (int c = 0; c < 3; c++) {

					double cn = 0, cs = 0, cw = 0, ce = 0;
					double in, is, iw, ie;
							
					in = src_64FC3_img.at<cv::Vec3d>(y - 1, x)[c] - src_64FC3_img.at<cv::Vec3d>(y, x)[c];
					is = src_64FC3_img.at<cv::Vec3d>(y + 1, x)[c] - src_64FC3_img.at<cv::Vec3d>(y, x)[c];
					iw = src_64FC3_img.at<cv::Vec3d>(y, x - 1)[c] - src_64FC3_img.at<cv::Vec3d>(y, x)[c];
					ie = src_64FC3_img.at<cv::Vec3d>(y, x + 1)[c] - src_64FC3_img.at<cv::Vec3d>(y, x)[c];

					cn = exp(-1 * ((in*in) / (sigma*sigma)));
					cs = exp(-1 * ((is*is) / (sigma*sigma)));
					cw = exp(-1 * ((iw*iw) / (sigma*sigma)));
					ce = exp(-1 * ((ie*ie) / (sigma*sigma)));

					edit_64FC3_img.at<cv::Vec3d>(y, x)[c] = src_64FC3_img.at<cv::Vec3d>(y, x)[c] * (1 - lambda * (cn + cs + ce + cw)) +
						lambda * (cn*src_64FC3_img.at<cv::Vec3d>(y - 1, x)[c] + cs * src_64FC3_img.at<cv::Vec3d>(y + 1, x)[c] +
							cw * src_64FC3_img.at<cv::Vec3d>(y, x - 1)[c] + ce * src_64FC3_img.at<cv::Vec3d>(y, x + 1)[c]);
				}
			}
		}
		for (int y = 1; y < src_64FC3_img.rows - 1; y++)
		{
			for (int x = 1; x < src_64FC3_img.cols - 1; x++)
			{
				for (int c = 0; c < 3; c++) {
					src_64FC3_img.at<cv::Vec3d>(y, x)[c] = edit_64FC3_img.at<cv::Vec3d>(y, x)[c];
				}
			}
		}
	}


	cv::imshow("Anisotropic Filtration", edit_64FC3_img);	
}
void Cv6()
{
	cv::Mat src_8UC1_img = cv::imread("images/lena64.png", CV_LOAD_IMAGE_GRAYSCALE);

	if (src_8UC1_img.empty()) {
		printf("Unable to read input file (%s, %d).", __FILE__, __LINE__);
	}

	int M = src_8UC1_img.rows;
    int N = src_8UC1_img.cols;
    double lSqrt_d = 1.0 / sqrt(M * N);
    double PI_2 = 3.1415 * 2;
    double lSumR = 0, lSumI = 0;
	double M_d = 1.0 / M;
	double N_d = 1.0 / N;

	cv::Mat src_64FC1_img;
	src_8UC1_img.convertTo(src_64FC1_img, CV_64FC3, 1.0 / 255.0 * lSqrt_d);
	cv::namedWindow("Original", 0);
	cv::imshow("Original", src_8UC1_img);

	cv::Mat edit_64FC2_img(src_64FC1_img.rows, src_64FC1_img.cols, CV_64FC2);

	for (int k = 0; k < M; k++) {
		for (int l = 0; l < N; l++) {

			lSumR = 0;
			lSumI = 0;

			for (int m = 0; m < M; m++) {
				for (int n = 0; n < N; n++) {

					double lValue = src_64FC1_img.at<double>(m, n);
					double lExpX = -PI_2 * (m * k * M_d + n * l * N_d);

					lSumR += lValue * cos(lExpX);
					lSumI += lValue * sin(lExpX);
				}
			}

			edit_64FC2_img.at<cv::Vec2d>(k, l) = cv::Vec2d(lSumR, lSumI);
		}
	}
	
	cv::Mat Visualize;
	Phase(edit_64FC2_img, Visualize);
	cv::namedWindow("Phasen", 0);
	cv::imshow("Phasen", Visualize);

	cv::Mat VisualizePower;
	Power(edit_64FC2_img, VisualizePower);
	cv::namedWindow("Power", 0);
	cv::imshow("Power", VisualizePower);

	cv::Mat Inverse;
	InverseFurier(edit_64FC2_img, Inverse);
	cv::namedWindow("Inverse", 0);
	cv::imshow("Inverse", Inverse);
}

//prohozeni oblasti pul pul 
void flipQuadrants(cv::Mat &source) {

	int lRows_half = source.rows / 2;
	int lCols_half = source.cols / 2;

	for (int y = 0; y < lRows_half; y++) {
		for (int x = 0; x < lCols_half; x++) {
			
			double tl = source.at<double>(y, x); // top left 
			double tr = source.at<double>(y, x + lCols_half); // top right 
			double bl = source.at<double>(y + lRows_half, x); // bottom left 
			double br = source.at<double>(y + lRows_half, x + lCols_half); // bottom right 

			
			source.at<double>(y, x) = br;
			source.at<double>(y, x + lCols_half) = bl;
			source.at<double>(y + lRows_half, x) = tr;
			source.at<double>(y + lRows_half, x + lCols_half) = tl;
		}
	}
}

void Phase(cv::Mat &furier, cv::Mat &dest) {
	int M = furier.rows;
	int N = furier.cols;

	
	dest = cv::Mat(M, N, CV_64FC1);

	for (int m = 0; m < M; m++) {
		for (int n = 0; n < N; n++) {

			cv::Vec2d F = furier.at<cv::Vec2d>(m, n);
			dest.at<double>(m, n) = atan(F[1] / F[0]);
		}
	}
}

void Power(cv::Mat &furier, cv::Mat &dest) {
	int M = furier.rows;
	int N = furier.cols;

	
	dest = cv::Mat(M, N, CV_64FC1);

	for (int m = 0; m < M; m++) {
		for (int n = 0; n < N; n++) {

			cv::Vec2d F = furier.at<cv::Vec2d>(m, n);
			double amp = sqrt(powf((F[0]),2) + powf((F[1]),2));
			dest.at<double>(m, n) = log(powf((amp),2));
		}
	}

	cv::normalize(dest, dest, 0.0, 1.0,CV_MINMAX);
	flipQuadrants(dest);
}
void Furier(cv::Mat &img, cv::Mat &dest){
	int M = img.rows;
	int N = img.cols;
	double lSqrt_d = 1.0 / sqrt(M * N);
	double PI_2 = 3.1415 * 2;
	double lSumR = 0, lSumI = 0;
	double M_d = 1.0 / M;
	double N_d = 1.0 / N;

	cv::Mat src_64FC1_img;
	img.convertTo(src_64FC1_img, CV_64FC3, 1.0 / 255.0 * lSqrt_d);
	
	dest = cv::Mat(src_64FC1_img.rows, src_64FC1_img.cols, CV_64FC2);

	for (int k = 0; k < M; k++) {
		for (int l = 0; l < N; l++) {

			lSumR = 0;
			lSumI = 0;

			for (int m = 0; m < M; m++) {
				for (int n = 0; n < N; n++) {

					double lValue = src_64FC1_img.at<double>(m, n);
					double lExpX = -PI_2 * (m * k * M_d + n * l * N_d);

					lSumR += lValue * cos(lExpX);
					lSumI += lValue * sin(lExpX);
				}
			}

			dest.at<cv::Vec2d>(k, l) = cv::Vec2d(lSumR, lSumI);
		}
	}
}
void InverseFurier(cv::Mat &furier, cv::Mat &dest) {

	int M = furier.cols;
	int N = furier.cols;
	double lSqrtMN_d = 1.0 / sqrt(M * N);
	double PI_2 = M_PI * 2;
	double lSum = 0;
	double M_d = 1.0 / M;
	double N_d = 1.0 / N;

	dest = cv::Mat(M, N, CV_64FC1);

	for (int m = 0; m < M; m++) {
		for (int n = 0; n < N; n++) {
			lSum = 0;

			for (int k = 0; k < M; k++) {
				for (int l = 0; l < N; l++) {

					double lExp = PI_2 * ((k * m * M_d) + (l * n * N_d));			
					double lReal = cos(lExp) * lSqrtMN_d;
					double lImag = sin(lExp) * lSqrtMN_d;
				
					cv::Vec2d lValue = furier.at<cv::Vec2d>(k, l);
					lSum += lValue[0] * lReal - lValue[1] * lImag;
				}
			}

			dest.at<double>(m, n) = lSum;
		}
	}

	cv::normalize(dest, dest, 0.0, 1.0, CV_MINMAX);
}
void Filter(cv::Mat &furier, cv::Mat &mask) {
	
	flipQuadrants(furier);
	for (int y = 0; y < furier.rows; y++) {
		for (int x = 0; x < furier.cols; x++) {		
			uchar MaskValue = mask.at<uchar>(y, x);		
			
			if (MaskValue == 0) {
				furier.at<cv::Vec2d>(y, x) = cv::Vec2d(0,0);
			}
		}
	}
	flipQuadrants(furier);
}
void Cv7()
{
	cv::Mat src_8UC1_img = cv::imread("images/lena64_noise.png", CV_LOAD_IMAGE_GRAYSCALE);

	if (src_8UC1_img.empty()) {
		printf("Unable to read input file (%s, %d).", __FILE__, __LINE__);
	}
	cv::Mat lFurier;
	Furier(src_8UC1_img, lFurier);

	cv::Mat LowMask = cv::Mat::zeros(64, 64, CV_8UC1);
	cv::Mat HightMask = cv::Mat::ones(64, 64, CV_8UC1) * 255;
	//cv::Mat LineMask = cv::Mat::zeros(64, 64, CV_8UC1) * 255;

	cv::circle(LowMask, cv::Point(LowMask.rows / 2, LowMask.cols / 2), 1, 255, -1); 
	cv::circle(HightMask, cv::Point(HightMask.rows / 2, HightMask.cols / 2), 20, 0, -1);
	//cv::circle(LineMask, cv::Point(LineMask.rows / 2, LineMask.cols / 2), 30, 255, -1);

	cv::namedWindow("Inverse", 0);
	cv::imshow("Inverse", LowMask);

	Filter(lFurier, LowMask);
	cv::Mat InverseLine;
	InverseFurier(lFurier, InverseLine);
	cv::namedWindow("Line", 0);
	cv::imshow("Line", InverseLine);



}
cv::Mat calcHistogram(cv::Mat &src) {
	cv::Mat hist = cv::Mat::zeros(L, 1, CV_32FC1);

	for (int y = 0; y < src.rows; y++) {
		for (int x = 0; x < src.cols; x++) {
			uchar &srcPx = src.at<uchar>(y, x);
			float &histPx = hist.at<float>(srcPx);
			histPx++;
		}
	}

	return hist;
}

cv::Mat drawHistogram(cv::Mat &hist) {
	cv::Mat histNorm;
	cv::normalize(hist, histNorm, 0.0f, 255.0f, CV_MINMAX);
	cv::Mat dst = cv::Mat::zeros(L, L, CV_8UC1);

	for (int x = 0; x < dst.cols; x++) {
		int vertical = cv::saturate_cast<int>(histNorm.at<float>(x));
		for (int y = L - 1; y > (L - vertical - 1); y--) {
			dst.at<uchar>(y, x) = 255;
		}
	}

	return dst;
}
int cdfMin(cv::Mat &cdf) {
	int min = 1;

	for (int i = 0; i < cdf.rows; i++) {
		float newMin = cdf.at<float>(i);
		if (newMin < min) min = (int)newMin;
	}

	return min;
}
cv::Mat calcCdf(cv::Mat &hist) {
	// Calculate image integral
	cv::Mat cdfInt;
	cv::integral(hist, cdfInt, CV_32F);

	// Remove first column and row, since integral adds W + 1 and H + 1
	return cdfInt(cv::Rect(1, 1, 1, hist.rows - 1));
}

void Cv8()
{
	cv::Mat src_8uc1_img, src_32fc1_hist, src_32fc1_cdf;
	src_8uc1_img = cv::imread("images/uneq.jpg", CV_LOAD_IMAGE_GRAYSCALE);
	cv::Mat dst_32fc1_normed = cv::Mat::zeros(src_8uc1_img.rows, src_8uc1_img.cols, CV_32FC1);

	// Get rows and cols
	int rows = src_8uc1_img.rows;
	int cols = src_8uc1_img.cols;
	int WxH = rows * cols;

	// Calc histogram and img integral (cdf)
	src_32fc1_hist = calcHistogram(src_8uc1_img);
	src_32fc1_cdf = calcCdf(src_32fc1_hist);

	// Get cdf min
	float min = cdfMin(src_32fc1_cdf);

	for (int y = 0; y < rows; y++) {
		for (int x = 0; x < cols; x++) {
			int srcPx = cv::saturate_cast<int>(src_8uc1_img.at<uchar>(y, x));
			float cdf = src_32fc1_cdf.at<float>(srcPx);

			dst_32fc1_normed.at<float>(y, x) = roundf(((cdf - min) / (WxH - min)) * (L - 1));
		}
	}

	// Normalize result
	cv::normalize(dst_32fc1_normed, dst_32fc1_normed, 0.0f, 1.0f, CV_MINMAX);

	// Show results
	cv::imshow("Source", src_8uc1_img);
	cv::imshow("Result", dst_32fc1_normed);
	cv::imshow("Source Histogram", drawHistogram(src_32fc1_hist));
	cv::imshow("Result Histogram", drawHistogram(src_32fc1_cdf));

}

void CentralDerivationEdge(cv::Mat &img, cv::Mat &dest)
{
	int M = img.cols;
	int N = img.cols;
	double PI_2 = M_PI * 2;
	double lSum = 0;

	dest = cv::Mat(M, N, CV_8UC1);

	for (int x = 1; x < M-1; x++) {
		for (int y = 1; y < N-1; y++) {
			double lX = 0;
			double lY = 0;

			uchar lValueX_ = img.at<uchar>(x-1 , y);
			uchar lValueX = img.at<uchar>(x+1, y);

			uchar lValueY_ = img.at<uchar>(x, y-1);
			uchar lValueY = img.at<uchar>(x, y + 1);

			
			dest.at<uchar>(x, y) = sqrt( (SQR((lValueX_ - lValueX)* 0.5)) + (SQR((lValueY_ - lValueY)* 0.5)) );
		}
	}
}
void SobelEdgeFilter(cv::Mat &img, cv::Mat &dest) 
{
	int M = img.cols;
	int N = img.cols;
	double PI_2 = M_PI * 2;
	double lSum = 0;

	cv::Mat imgX = img.clone();
	cv::Mat imgY = img.clone();

	cv::Mat soubleY;
	cv::Mat soubleX;
	dest = cv::Mat(M, N, CV_8UC1);


	double *kernelX[3];
	kernelX[0] = new double[3]{ 1,0,-1 };
	kernelX[1] = new double[3]{ 2,0,-2 };
	kernelX[2] = new double[3]{ 1,0,-1 };

	double *kernelY[3];
	kernelY[0] = new double[3]{ 1,2,1 };
	kernelY[1] = new double[3]{ 0,0,0 };
	kernelY[2] = new double[3]{ -1,-2,-1 };
	
	soubleX = UseConvolutionGray(imgX, kernelX, 3);
	soubleY =  UseConvolutionGray(imgY, kernelY, 3);

	for (int x = 0; x < M ; x++) {
		for (int y = 0; y < N ; y++) {
			
			dest.at<uchar>(x, y) = sqrt( SQR(soubleX.at<uchar>(x,y)) + SQR(soubleY.at<uchar>(x,y)) );
		}
	}
}

void Cv11()
{
	cv::Mat src_8UC3_img = cv::imread("images/lena.png", CV_LOAD_IMAGE_GRAYSCALE);

	if (src_8UC3_img.empty()) {
		printf("Unable to read input file (%s, %d).", __FILE__, __LINE__);
	}

	cv::Mat img_8UC1_img;
	cv::Mat img_8UC1_img_sobel;
	cv::imshow("Original", src_8UC3_img);

	CentralDerivationEdge(src_8UC3_img, img_8UC1_img);
	cv::imshow("Central derivaiton mEdge", img_8UC1_img);

	SobelEdgeFilter(src_8UC3_img, img_8UC1_img_sobel);
	cv::imshow("Sobel", img_8UC1_img_sobel);

}
void Cv12() 
{
	cv::Mat src_8UC3_img = cv::imread("images/lena.png", CV_LOAD_IMAGE_GRAYSCALE);

	if (src_8UC3_img.empty()) {
		printf("Unable to read input file (%s, %d).", __FILE__, __LINE__);
	}

	cv::Mat img_8UC1_img;
	cv::Mat img_8UC1_img_e;

	CentralDerivationEdge(src_8UC3_img, img_8UC1_img);
	cv::imshow("Central ", img_8UC1_img);

	Edge(img_8UC1_img, img_8UC1_img_e);
	cv::imshow("Central derivaiton mEdge", img_8UC1_img_e);

}
void Edge(cv::Mat &img, cv::Mat &dest)
{
	int M = img.rows;
	int N = img.cols;
	double PI_2 = M_PI * 2;
	double lSum = 0;

	cv::Mat destt = cv::Mat::zeros(M, N, CV_8UC1);

	for (int x = 1; x < M - 1; x++) {
		for (int y = 1; y < N - 1; y++) {
			double lX = 0;
			double lY = 0;

			uchar lValueX_ = img.at<uchar>(x - 1, y);
			uchar lValueX = img.at<uchar>(x + 1, y);

			uchar lValueY_ = img.at<uchar>(x, y - 1);
			uchar lValueY = img.at<uchar>(x, y + 1);

			double lX_ = (lValueX - lValueX_) * 0.5;
			double lY_ = (lValueY - lValueY_) * 0.5;

			double alfa = std::atan2(lY_, lX_);



			double EP, EM;

			double a = tan(alfa);

			if (alfa >= 0 && alfa < M_PI / 2)
			{
				EP = a * img.at<uchar>(x + 1, y + 1) + (1 - a) * img.at<uchar>(x + 1, y);
				EM = a * img.at<uchar>(x - 1, y - 1) + (1 - a) * img.at<uchar>(x - 1, y);
			}
			else if (alfa >= M_PI / 2 && alfa < M_PI)
			{
				EP = a * img.at<uchar>(x - 1, y ) + (1 - a) * img.at<uchar>(x, y + 1);
				EM = a * img.at<uchar>(x + 1, y ) + (1 - a) * img.at<uchar>(x , y - 1);
			}
			else if (alfa >= M_PI && alfa < 3 / 2 * M_PI)
			{
				EP = a * img.at<uchar>(x, y - 1) + (1 - a) * img.at<uchar>(x - 1, y);
				EM = a * img.at<uchar>(x , y + 1) + (1 - a) * img.at<uchar>(x + 1, y);
			}
			else
			{
				EP = a * img.at<uchar>(x + 1, y ) + (1 - a) * img.at<uchar>(x , y - 1);
				EM = a * img.at<uchar>(x - 1, y ) + (1 - a) * img.at<uchar>(x , y + 1);
			}


			if (EM < img.at<uchar>(x, y) && img.at<uchar>(x, y) > EP)
				destt.at<uchar>(x, y) = img.at<uchar>(x, y);

			


		}
	}

	//cv::threshold(destt, dest,10,255,cv::THRESH_BINARY);
}