#ifndef _skinSegment_H_
#define _skinSegment_H_
#include "hand.h"
void cvThresholdOtsu(IplImage* src,IplImage* dst);
void skin_Segment(Mat input,Mat output);
void skin_Segment2(Mat input,Mat output);
void skin_Segment3(Mat input,Mat output);
#endif