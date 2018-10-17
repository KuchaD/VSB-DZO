// prvniUkol.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"



int f1(int argc, char* argv[])
{
	IplImage *img=NULL;
	img=cvLoadImage("c://Users//adam//Dokumenty//Visual Studio 2010//c++//dzo/prvniHodina//solution//solution//moon.jpg",0);
	
	if(!img)
	{
		printf("No Image\n");
		return -1;
	}
	cvShowImage("Moon",img);

	cvWaitKey(0);

		IplImage *img64f=cvCreateImage(cvGetSize(img),IPL_DEPTH_32F,1);
	cvConvertScale(img,img64f);


	IplImage *img_kopie=cvCreateImage(cvGetSize(img),IPL_DEPTH_32F,1);
	cvConvertScale(img,img_kopie);


	cvScale(img64f,img64f,1.0/255.0);
 /*Gamma korekce*/

	for(int y=0;y<img64f->height;y++)
		for(int x=0;x<img64f->width;x++)
		{
			float gamma=1.5; 
			float korekce=pow(CV_IMAGE_ELEM(img64f,float,y,x),gamma);
			CV_IMAGE_ELEM(img64f,float,y,x)=korekce;
		}


		cvShowImage("Moon",img64f);

	cvWaitKey(0);
	/*Normalizace*/
	float max=CV_IMAGE_ELEM(img_kopie,float,0,0);
	float min=CV_IMAGE_ELEM(img_kopie,float,0,0);
	for(int y=0;y<img_kopie->height;y++)
	{
		for(int x=0;x<img_kopie->width;x++)
		{
			float value=CV_IMAGE_ELEM(img_kopie,float,y,x);
			if(value>max)
				max=value;

			if(value<min)
				min=value;
		}
	}



		int i=1;
		for(int y=0;y<img_kopie->height;y++)
		for(int x=0;x<img_kopie->width;x++)
		{
			float hodnota=CV_IMAGE_ELEM(img_kopie,float,y,x);
			float koeficient=255/(max-min);

			
			
				CV_IMAGE_ELEM(img_kopie,float,y,x)=(hodnota-min)*koeficient;
	
		}

	cvScale(img_kopie,img_kopie,1.0/255.0);
	cvShowImage("Moon",img_kopie);
	img=NULL;
	img64f=NULL;
	img_kopie=NULL;
	cvWaitKey(0);
	return 0;
}

