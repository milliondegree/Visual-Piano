#include "handThin.h"

void ImgThin(Mat src,int maxIterations)
{
	if (src.empty()||src.channels()!=1) return;//图像为空，直接返回

	cv::threshold(src, src, 128, 1, CV_THRESH_BINARY);//转为0或1的图像
    int ImgHeight = src.rows;
    int ImgWidth = src.cols;

    int count = 0;  //记录迭代次数
    while (true)
    {
        count++;
        if (maxIterations != -1 && count > maxIterations) //限制次数并且迭代次数到达
            break;

        vector<pair<int, int> > mFlag; //用于标记需要删除的点
        //对点标记
        for (int i = 0; i < ImgHeight; ++i)
        {
            for (int j = 0; j < ImgWidth; ++j)
            {
                //如果满足四个条件，进行标记
                //  p9 p2 p3
                //  p8 p1 p4
                //  p7 p6 p5
                int p1 = src.at<uchar>(i, j);
                int p2 = (i == 0) ? 0 : src.at<uchar>(i - 1, j);
                int p3 = (i == 0 || j == ImgWidth - 1) ? 0 : src.at<uchar>(i - 1, j + 1);
                int p4 = (j == ImgWidth - 1) ? 0 : src.at<uchar>(i, j + 1);
                int p5 = (i == ImgHeight - 1 || j == ImgWidth - 1) ? 0 : src.at<uchar>(i + 1, j + 1);
                int p6 = (i == ImgHeight - 1) ? 0 : src.at<uchar>(i + 1, j);
                int p7 = (i == ImgHeight - 1 || j == 0) ? 0 : src.at<uchar>(i + 1, j - 1);
                int p8 = (j == 0) ? 0 : src.at<uchar>(i, j - 1);
                int p9 = (i == 0 || j == 0) ? 0 : src.at<uchar>(i - 1, j - 1);

                if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) >= 2 && (p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) <= 6)
                {
                    int ap = 0;
                    if (p2 == 0 && p3 == 1) ++ap;
                    if (p3 == 0 && p4 == 1) ++ap;
                    if (p4 == 0 && p5 == 1) ++ap;
                    if (p5 == 0 && p6 == 1) ++ap;
                    if (p6 == 0 && p7 == 1) ++ap;
                    if (p7 == 0 && p8 == 1) ++ap;
                    if (p8 == 0 && p9 == 1) ++ap;
                    if (p9 == 0 && p2 == 1) ++ap;

                    if (ap == 1)
                    {
                        if (p2*p4*p6 == 0)
                        {
                            if (p4*p6*p8 == 0)
                            {
                                //标记
                                mFlag.push_back(make_pair(i, j));
                            }
                        }
                    }
                }
            }
        }

        //将标记的点删除
        for (vector<pair<int, int> >::iterator i = mFlag.begin(); i != mFlag.end(); ++i)
        {
            src.at<uchar>(i->first, i->second) = 0;
        }

        //直到没有点满足，算法结束
        if (mFlag.size() == 0) break;
        else mFlag.clear();//将mFlag清空

        //对点标记
        for (int i = 0; i < ImgHeight; ++i)
        {
            for (int j = 0; j < ImgWidth; ++j)
            {
                //如果满足四个条件，进行标记
                //  p9 p2 p3
                //  p8 p1 p4
                //  p7 p6 p5
                int p1 = src.at<uchar>(i, j);
                if (p1 != 1) continue;
                int p2 = (i == 0) ? 0 : src.at<uchar>(i - 1, j);
                int p3 = (i == 0 || j == ImgWidth - 1) ? 0 : src.at<uchar>(i - 1, j + 1);
                int p4 = (j == ImgWidth - 1) ? 0 : src.at<uchar>(i, j + 1);
                int p5 = (i == ImgHeight - 1 || j == ImgWidth - 1) ? 0 : src.at<uchar>(i + 1, j + 1);
                int p6 = (i == ImgHeight - 1) ? 0 : src.at<uchar>(i + 1, j);
                int p7 = (i == ImgHeight - 1 || j == 0) ? 0 : src.at<uchar>(i + 1, j - 1);
                int p8 = (j == 0) ? 0 : src.at<uchar>(i, j - 1);
                int p9 = (i == 0 || j == 0) ? 0 : src.at<uchar>(i - 1, j - 1);

                if ((p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) >= 2 && (p2 + p3 + p4 + p5 + p6 + p7 + p8 + p9) <= 6)
                {
                    int ap = 0;
                    if (p2 == 0 && p3 == 1) ++ap;
                    if (p3 == 0 && p4 == 1) ++ap;
                    if (p4 == 0 && p5 == 1) ++ap;
                    if (p5 == 0 && p6 == 1) ++ap;
                    if (p6 == 0 && p7 == 1) ++ap;
                    if (p7 == 0 && p8 == 1) ++ap;
                    if (p8 == 0 && p9 == 1) ++ap;
                    if (p9 == 0 && p2 == 1) ++ap;

                    if (ap == 1)
                    {
                        if (p2*p4*p8 == 0)
                        {
                            if (p2*p6*p8 == 0)
                            {
                                //标记
                                mFlag.push_back(make_pair(i, j));
                            }
                        }
                    }
                }
            }
        }
        //删除
        for (vector<pair<int, int> >::iterator i = mFlag.begin(); i != mFlag.end(); ++i)
        {
            src.at<uchar>(i->first, i->second) = 0;
        }

        //直到没有点满足，算法结束
        if (mFlag.size() == 0) break;
        else mFlag.clear();//将mFlag清空
    }

    cv::threshold(src, src, 0, 255, CV_THRESH_BINARY);//二值化图像
}