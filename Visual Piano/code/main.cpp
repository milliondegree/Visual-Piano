#include "hand.h"
#include "skinSegment.h"
#include "handShape.h"
#include "handThin.h"
#include "ErosionDilation.h"
#include "GravityCenter.h"
#include "ColorCenter.h"
#include <windows.h>
#pragma comment(lib, "Winmm.lib")
#define BLUE    1
#define GREEN   2
#define PINK    3
#define YELLOW  4

void main()
{
    VideoCapture inputVideo(0);    //0为外部摄像头的ID，1为笔记本内置摄像头的ID
    Mat src;
	double rd=0;
	//---------test-----------------
	cout << "start! \n";

	//------------------------------
    for(;;)
    {
        inputVideo >> src;    //input Vedio		
		imshow("原始图像",src);
		waitKey(10);

		Mat skin(src.size(),CV_8UC1);
        skin_Segment(src,skin);
		//imshow("肤色分割后",skin);
		//waitKey(10);

		Mat hand(src.size(),CV_8UC3);
		CvPoint g;
        hand_Shape(skin,hand,g);		     
		//imshow("手形",hand);
		//waitKey(10);
		

		//circle(thin,center,10,0,2,8,0);   
		//imshow("腐蚀",thin);
		//
	    circle(hand,g,10,CV_RGB(0,0,0),2,8,0);
		CvPoint g1,g2,g3,g4,g5;
		//ColorCenter(src,g1,1);
		//ColorCenter(src,g2,2);
		//ColorCenter(src,g3,3);
		//ColorCenter(src,g4,4);
		//circle(src,g1,10,CV_RGB(0,0,0),2,8,0);
		//circle(src,g2,10,CV_RGB(0,0,0),2,8,0);
		//circle(src,g3,10,CV_RGB(0,0,0),2,8,0);
		//circle(src,g4,10,CV_RGB(0,0,0),2,8,0);
		ColorCenter(src,g5,5);
		//Mat piano=imread("piano.jpg");
		circle(hand,g5,10,CV_RGB(0,0,0),2,8,0);
		if(g5.x>10&&g5.y>10){
		line(hand,g,g5,CV_RGB(0,0,0),2);
		double d=Distance(g,g5);
		if(d<0.7*rd)
		{
			int key=1+g5.x/80;
			cout << key <<"\n";
			switch (key)
			{
			case 1:PlaySound(TEXT("Sound\\1 do.wav"), NULL, SND_FILENAME | SND_SYNC );break;
            case 2:PlaySound(TEXT("Sound\\2 re.wav"), NULL, SND_FILENAME | SND_SYNC );break;
			case 3:PlaySound(TEXT("Sound\\3 mi.wav"), NULL, SND_FILENAME | SND_SYNC );break;
			case 4:PlaySound(TEXT("Sound\\4 fa.wav"), NULL, SND_FILENAME | SND_SYNC );break;
			case 5:PlaySound(TEXT("Sound\\5 sol.wav"), NULL, SND_FILENAME | SND_SYNC );break;
			case 6:PlaySound(TEXT("Sound\\6 la.wav"), NULL, SND_FILENAME | SND_SYNC );break;
			case 7:PlaySound(TEXT("Sound\\7 si.wav"), NULL, SND_FILENAME | SND_SYNC );break;
			case 8:PlaySound(TEXT("Sound\\8.wav"), NULL, SND_FILENAME | SND_SYNC );break;
			default:break;
			}
		//	Sleep(1);
		//	PlaySound(NULL,NULL,SND_FILENAME);
		}
		rd=d;
		}
		imshow("piano",hand);
		waitKey(10);
		
		waitKey(200);
    }
}

