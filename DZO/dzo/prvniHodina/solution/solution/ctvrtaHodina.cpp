// prvniUkol.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



int f4(int argc, char* argv[])
{
	IplImage *img=NULL;
	img=cvLoadImage("c://Users//adam//Dokumenty//Visual Studio 2010//c++//dzo/prvniHodina//solution//solution//lena.png",0);

	double lambda = 0.05;
	double sigma = 0.1;
	int t = 50;
	float cn, cs, cw, ce;
	cn=cs=cw=ce=0;
	float in, is, iw, ie;
	float gn, gs, gw, ge;
	cvShowImage("Img",img);
	cvWaitKey();
	IplImage *img2 = cvCreateImage( cvGetSize(img), IPL_DEPTH_32F , 0);
	cvConvertScale(img, img2, 1.0 / 255.0);
	IplImage *img3 = cvCreateImage( cvGetSize(img), IPL_DEPTH_32F , 0);
	for(int i = 1 ; i < t; i++)
	{
	 for(int y = 1; y < img->height-1; y++)
		{
			for(int x = 1; x < img->width-1; x++)
			{
				in=CV_IMAGE_ELEM(img2,float,y-1,x)-CV_IMAGE_ELEM(img2,float,y,x);
				is=CV_IMAGE_ELEM(img2,float,y+1,x)-CV_IMAGE_ELEM(img2,float,y,x);
				iw=CV_IMAGE_ELEM(img2,float,y,x-1)-CV_IMAGE_ELEM(img2,float,y,x);
				ie=CV_IMAGE_ELEM(img2,float,y,x+1)-CV_IMAGE_ELEM(img2,float,y,x);
				cn=exp(-1*((in*in)/(sigma*sigma)));
	cs=exp(-1*((is*is)/(sigma*sigma)));
	cw=exp(-1*((iw*iw)/(sigma*sigma)));
	ce=exp(-1*((ie*ie)/(sigma*sigma)));
	CV_IMAGE_ELEM(img3,float,y,x) = CV_IMAGE_ELEM(img2,float,y,x)*(1-lambda*(cn+cs+ce+cw))+
	lambda*(cn*CV_IMAGE_ELEM(img2,float,y-1,x)+cs*CV_IMAGE_ELEM(img2,float,y+1,x)+
	cw*CV_IMAGE_ELEM(img2,float,y,x-1)+ce*CV_IMAGE_ELEM(img2,float,y,x+1));
	}
	}
		for(int y = 1; y < img2->height-1; y++)
	{
		for(int x = 1; x < img2->width-1; x++)
	{
	CV_IMAGE_ELEM(img2,float,y,x) = CV_IMAGE_ELEM(img3,float,y,x);
	}
	}
	}
	cvShowImage("Img2",img2);
	cvWaitKey();
		return 0;
}
