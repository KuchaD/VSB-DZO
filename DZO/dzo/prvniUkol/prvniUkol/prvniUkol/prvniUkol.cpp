// prvniUkol.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"


int main(int argc, char* argv[])
{
	IplImage *img=NULL;
	img=cvLoadImage("c://Users//adam//Dokumenty//Visual Studio 2010//c++//dzo/prvniUkol//prvniUkol//lena.png");

	if(!img)
	{
		printf("No Image\n");
		return -1;
	}
	cvShowImage("Lena",img);

	cvWaitKey(0);


	IplImage *imgLarge=cvCreateImage(cvSize(img->width*2,img->height*2),
		img->depth,img->nChannels);
	cvResize(img,imgLarge,CV_INTER_LINEAR);
	cvShowImage("Lena",imgLarge);
	cvWaitKey(0);
	
	IplImage *imgGray=cvCreateImage(cvGetSize(img),IPL_DEPTH_8U,1);
	cvCvtColor(img,imgGray,CV_BGR2GRAY);
	cvShowImage("Lena",imgGray);
	cvWaitKey(0);

	IplImage *imgGray64f=cvCreateImage(cvGetSize(img),IPL_DEPTH_64F,1);
	cvConvertScale(imgGray,imgGray64f,1.0/255.0);
	cvShowImage("Lena",imgGray64f);
	cvWaitKey(0);


	int x=5,y=10;
	uchar *p1=&CV_IMAGE_ELEM(img,uchar,y,x*img->nChannels);
	uchar p2=CV_IMAGE_ELEM(imgGray,uchar,y,x);
	double p3=CV_IMAGE_ELEM(imgGray64f,double,y,x);
	CvScalar p4=cvGet2D(img,y,x);

	printf("p1=(b=%d,g=%d,r=%d),p2=%d,p3=%f,p4=(%0.1f,%0.1f,%0.1f)\n",
		p1[0],p1[1],p1[2],p2,p3,p4.val[0],p4.val[1],p4.val[2]);

	CV_IMAGE_ELEM(imgGray64f,double,y,x)=1.0;
	cvShowImage("Lena",imgGray64f);

	cvWaitKey(0);

	return 0;
}

