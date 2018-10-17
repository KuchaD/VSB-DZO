// prvniUkol.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"

#define CV_MAT_ELEM_RE( mat,elemtype,row,col)\
	(((double*)(mat->data.ptr+mat->step*(row)))[(col)*2])
#define PI 3.14159265358979323846

#define CV_MAT_ELEM_IM( mat,elemtype,row,col)\
	(((double*)(mat->data.ptr+mat->step*(row)))[(col)*2+1])

#define SQR( x ) ( ( x ) * ( x ) )


int main(int argc, char* argv[])
{
	IplImage *img=NULL;
	img=cvLoadImage("lena64.png",0);

	cvShowImage("Img",img);
	cvWaitKey();

	IplImage *img2 = cvCreateImage( cvGetSize(img), IPL_DEPTH_64F , 1);
	cvConvertScale(img, img2, (1.0 / 255.0) );
	cvShowImage( "Img", img2 );
	cvWaitKey();
	cvConvertScale( img2, img2, 1.0/sqrtf(img2->width*img2->height) );


	CvMat* F=cvCreateMat(img2->width, img2->height, CV_64FC2);

	cvZero(F);

	for(int y=0;y<img2->height;y++)
	{
		for(int x=0;x<img2->width;x++)
		{
			for(int m=0;m<img2->height;m++)
			{
				for(int n=0;n<img2->width;n++)
				{
					double cislo=2*PI*((m*y)/(float)img2->height + (n*x)/(float)img2->width);
					CV_MAT_ELEM_RE(F,double,m,n) += CV_IMAGE_ELEM(img2,double,m,n)*cos(cislo);
					CV_MAT_ELEM_IM(F,double,m,n) += CV_IMAGE_ELEM(img2,double,m,n)*-sin(cislo);
				}
			}
		}
	}

	
	IplImage *img4 = cvCreateImage( cvGetSize(img), IPL_DEPTH_64F , 1);


	for(int y=0;y<img4->height;y++)
	{
		for(int x=0;x<img4->width;x++)
		{
			CV_IMAGE_ELEM(img4,double,y,x) = sqrt( SQR( CV_MAT_ELEM_RE(F,double,y,x) ) + SQR( CV_MAT_ELEM_IM(F,double,y,x)));
		}
	}



	cvShowImage("amplituda spektra",img4);
	cvWaitKey();

	for(int y=0;y<img4->height;y++)
	{
		for(int x=0;x<img4->width;x++)
		{
			CV_IMAGE_ELEM(img4,double,y,x)=atan(CV_MAT_ELEM_IM(F,double,y,x)/CV_MAT_ELEM_RE(F,double,y,x));
		}
	}


		cvShowImage("Fázový posun",img4);
	cvWaitKey();


for(int y=0;y<img4->height;y++)
	{
	for(int x=0;x<img4->width;x++)
		{
			CV_IMAGE_ELEM(img4,double,y,x)= log10( SQR( CV_MAT_ELEM_RE(F,double,y,x) + SQR( CV_MAT_ELEM_IM(F,double,y,x) ) ) + 1.0 );
		}
	}

	cvShowImage("Power",img4);
	cvWaitKey();
		return 0;
}
