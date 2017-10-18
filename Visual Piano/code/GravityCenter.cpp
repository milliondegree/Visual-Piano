#include "GravityCenter.h"


void GravityCenter(Mat input, CvPoint &center)
{
	 IplImage src=input;
	 double m00, m10, m01;
	 CvMoments moment;
	 cvMoments( &src, &moment, 1);
	 m00 = cvGetSpatialMoment( &moment, 0, 0 );

	 m10 = cvGetSpatialMoment( &moment, 1, 0 );
	 m01 = cvGetSpatialMoment( &moment, 0, 1 );
	 center.x = (int) (m10/m00);
	 center.y = (int) (m01/m00);
}

double Distance(CvPoint &p1,CvPoint &p2)
{
	double d;
	d=sqrt(((p1.x-p2.x)*(p1.x-p2.x)+(p1.y-p2.y)*(p1.y-p2.y))*1.0);
	return d;
}