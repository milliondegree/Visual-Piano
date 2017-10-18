#include "handShape.h"
#include "GravityCenter.h"

void hand_Shape(Mat input,Mat output,CvPoint &g)
{
	vector<vector<Point> > contours;
	vector<Vec4i> hierarchy;
	findContours(input, contours, hierarchy, RETR_TREE, CHAIN_APPROX_SIMPLE, Point(0, 0) );
    double maxarea=0,minarea=1000;
	int max_i=0,sec_i=0;
	for( int i = 0; i< contours.size(); i++ )
        {
		 double tmparea=fabs(contourArea(contours[i]));
		 double arcL=fabs(arcLength(contours[i],0));
		 double arc_area=arcL/sqrt(tmparea);
		 if(arc_area>5&&arc_area<20&&tmparea>20000){
		   if(tmparea>maxarea){
			   maxarea=tmparea;
			   max_i=i;
		   }		 
		 }
        }

	approxPolyDP(contours[max_i], contours[max_i], 5, 1);

	Mat black=Mat::zeros(input.size(),CV_8UC1);
	drawContours( black, contours, max_i, Scalar(255), -1);
	Mat thin(input.size(),CV_8UC1);
	Mat element = getStructuringElement( 0,Size( 50, 50 ) );
	CvPoint center;
	erode(black,thin,element);	
	GravityCenter(thin,center);
	g=center;

	Mat piano=imread("piano.jpg");
	drawContours( piano, contours, max_i, Scalar(0,0,0), 5);
	piano.copyTo(output);

}