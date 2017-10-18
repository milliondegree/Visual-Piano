#include "ColorCenter.h"
#include "GravityCenter.h"
void ColorCenter(Mat input, CvPoint &center,int color)
{
	Mat ycrcb(input.size(),CV_8UC3);         //BGR to YCrCb
	cvtColor(input,ycrcb,CV_BGR2YCrCb);

	int cr,cb;
	switch (color)
	{
	case 1:cr=119;cb=155;break;
	case 2:cr=120;cb=125;break;
	case 3:cr=170;cb=139;break;
	case 4:cr=139;cb=112;break;
	case 5:cr=210;cb=100;break;
	}

	for(int i=0;i<ycrcb.rows;i++)
	{
		for(int j=0;j<ycrcb.cols;j++)
		{
			if(abs(ycrcb.at<Vec3b>(i,j)[1]-cr)<=10&&abs(ycrcb.at<Vec3b>(i,j)[2]-cb)<=10)
				ycrcb.at<Vec3b>(i,j)[0]=255;
			else
				ycrcb.at<Vec3b>(i,j)[0]=0;
		}
	}
	vector<Mat> channels;                      //devide Cr  
	split(ycrcb,channels);
	Mat dst=Mat::zeros(input.size(),CV_8UC1); //选取通道一Cr值
	dst=channels.at(0); 
	GravityCenter(dst,center);
}