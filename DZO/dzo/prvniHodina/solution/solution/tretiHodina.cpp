// prvniUkol.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



int f3(int argc, char* argv[])
{
	IplImage *img=NULL;
	img=cvLoadImage("c://Users//adam//Dokumenty//Visual Studio 2010//c++//dzo/prvniHodina//solution//solution//lena.png",0);
	
	if(!img)
	{
		printf("No Image\n");
		return -1;
	}
	cvShowImage("Lenka",img);

	cvWaitKey(0);
	/*Konvoluce*/
	
	IplImage *imgKonvoluce=cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,1);
	cvConvertScale(img,imgKonvoluce);

	//float maska[3][3]={{1/9,1/9,1/9},{1/9,1/9,1/9},{1/9,1/9,1/9}};
	const int velikost=3;
	int maska[velikost][velikost]={{1,1,1},{1,1,1},{1,1,1}};

	for(int y=(velikost/2);y<imgKonvoluce->height-(velikost/2);y++)
	{
		for(int x=(velikost/2);x<imgKonvoluce->width-(velikost/2);x++)
		{
			//int hodnota=CV_IMAGE_ELEM(img,float,y,x);
			float value=0;
			for(int i=0;i<3;i++)
			{
				for(int j=0;j<3;j++)
				{
					value=value+maska[i][j]*CV_IMAGE_ELEM(imgKonvoluce,uchar, y+i,x+j);
				}
			}
			value=value*(1.0/9.9);
			CV_IMAGE_ELEM(imgKonvoluce,uchar,y,x)=(uchar)value;
		}
	}
	cvShowImage("Lena",imgKonvoluce);

	cvWaitKey(0);


	/*Gaussova konvoluce*/

    IplImage *imgGauss=cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,1);
	cvConvertScale(img,imgGauss);

	const int velikostGauss=5;
	int maska2[velikostGauss][velikostGauss]={{2,4,5,4,2},{4,9,12,9,4},{5,12,15,12,5},{4,9,12,9,4},{2,4,5,4,2}};

	for(int y=(velikostGauss/2);y<imgGauss->height-(velikostGauss/2);y++)
	{
		for(int x=(velikostGauss/2);x<imgGauss->width-(velikostGauss/2);x++)
		{
			//int hodnota=CV_IMAGE_ELEM(img,float,y,x);
			float value=0;
			for(int i=0;i<velikostGauss;i++)
			{
				for(int j=0;j<velikostGauss;j++)
				{
					value=value+maska2[i][j]*CV_IMAGE_ELEM(imgGauss,uchar, y+i,x+j);
				}
			}
			value=value*(1.0/159.0);
			CV_IMAGE_ELEM(imgGauss,uchar,y,x)=(uchar)value;
		}
	}


	cvShowImage("Lena",imgGauss);

	cvWaitKey(0);
	return 0;
}

