#include "skinSegment.h"

void skin_Segment3(Mat input,Mat output)
{
	IplImage input_img=input; 
	IplImage* output_mask=NULL;  
    IplImage* output_img=NULL;  
	output_img=cvCreateImage(cvGetSize(&input_img),(&input_img)->depth,(&input_img)->nChannels);  
    cvZero(output_img);  
	if(output_mask==NULL)  
        {  
            output_mask=cvCreateImage(cvGetSize(&input_img),(&input_img)->depth,1);  
        }  
	CvAdaptiveSkinDetector skin_detector(1,CvAdaptiveSkinDetector::MORPHING_METHOD_ERODE_DILATE);   
    skin_detector.process(&input_img,output_mask);   

    cvCopy(&input_img,output_img,output_mask);  

	Mat out(output_img,0);
	out.copyTo(output);
}
void skin_Segment2(Mat input,Mat output)
{
	Mat result, tmp;  
    Mat Y, Cr, Cb;  
    vector<Mat> channels;  
	cvtColor(input, tmp, CV_BGR2YCrCb);     
    split(tmp, channels);  
    Y = channels.at(0);  
    Cr = channels.at(1);  
    Cb = channels.at(2);  
      
    result.create(input.rows, input.cols, CV_8UC1);  
  
        /*遍历图像，将符合阈值范围的像素设置为255，其余为0*/  
    for (int j = 1; j < Y.rows - 1; j++)  
    {  
           uchar* currentCr = Cr.ptr< uchar>(j);  
           uchar* currentCb = Cb.ptr< uchar>(j);  
           uchar* current = result.ptr< uchar>(j);  
           for (int i = 1; i < Y.cols - 1; i++)  
           {  
                if ((currentCr[i] > 137) && (currentCr[i] < 175) && (currentCb[i] > 100) && (currentCb[i] < 118))  
                    current[i] = 255;  
                else  
                    current[i] = 0;  
           }  
    } 
	result.copyTo(output);
}
void skin_Segment(Mat input,Mat output)
{	
	Mat ycrcb(input.size(),CV_8UC3);         //BGR to YCrCb
	cvtColor(input,ycrcb,CV_BGR2YCrCb);
	//for(int i=0;i<ycrcb.rows;i++)
	//{
	//	for(int j=0;j<ycrcb.cols;j++)
	//	{
	//		if(ycrcb.at<Vec3b>(i,j)[0]<70||ycrcb.at<Vec3b>(i,j)[1]>200||ycrcb.at<Vec3b>(i,j)[1]<110||ycrcb.at<Vec3b>(i,j)[2]>140||ycrcb.at<Vec3b>(i,j)[2]<75)
	//			ycrcb.at<Vec3b>(i,j)[1]=0;
	//	}
	//}

	vector<Mat> channels;                      //devide Cr  
	split(ycrcb,channels);

	Mat dst=Mat::zeros(input.size(),CV_8UC1); //选取通道一Cr值
	dst=channels.at(1); 
	
	IplImage img_cr=dst;                        //阈值分割	
	cvThresholdOtsu(&img_cr,&img_cr);

	Mat cr(&img_cr,0);
	threshold(cr,cr,127,255,CV_THRESH_BINARY);

	cr.copyTo(output);
	
}
void cvThresholdOtsu(IplImage* src,IplImage* dst)//otsu 最大类间差分法，一种自适应阈值确定方法
{
    int height = src->height;
    int width = src->width;

    float histogram[256] = {0};
    for (int i = 0; i < height; i++)
    {
        unsigned char* p = (unsigned char*)src->imageData + src->widthStep*i;
        for (int j = 0; j < width; j++)
        {
             histogram[*p++]++;
        }
    }
    int size = height * width;
    for (int i = 0; i < 256; i++)
    {
        histogram[i] = histogram[i] / size;
    }
    float avgValue = 0;
    for (int i = 0; i < 256; i++)
    {
        avgValue += i*histogram[i];
    }

    int threshold;
    float maxVariance = 0;
    float w = 0, u = 0;
    for (int i = 0; i < 256; i++)
    {
        w += histogram[i];
        u += i*histogram[i];
        float t = avgValue*w - u;
        float variance = t*t / (w*(1-w));
        if (variance > maxVariance)
        {
            maxVariance = variance;
               threshold = i;
        }
    }
    cvThreshold(src,dst,threshold,255,CV_THRESH_BINARY);
}
