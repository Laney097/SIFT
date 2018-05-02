//VS2010+opencv2.2
#include <windows.h>

#include <iostream>
using namespace std;

#include <cv.h>
#include <highgui.h>
#include <cxcore.h>
using namespace cv;

#include "sift.h"

int main(int argc, char **argv)
{
	Mat image1 = imread("1.jpg");
	Mat image2 = imread("2.jpg");
	Mat image01 = image1.clone();
	Mat image02 = image2.clone();

	Vector<Keypoint> features1, features2;
	//
	Sift(image1, features1, SIGMA);
	Sift(image2, features2, SIGMA);

	//��ͼ���ϻ���������
	DrawKeyPoints(image1, features1);
	DrawKeyPoints(image2, features2);

	//����������������
	DrawSiftFeatures(image1, features1);
	DrawSiftFeatures(image2, features2);

	//���������128ά����
	write_features(features1, "descriptor_1.txt");
	write_features(features2, "descriptor_2.txt");

	imshow("image1", image1);
	imshow("image2", image2);

	//��������ͼ��Ӧ������
	CvSize size;  
	size.width = image1.cols + image2.cols;  
	size.height = image1.rows + image2.rows; 
	int width = size.width;
	int height = size.height;
	Mat img_match(size.height, size.width, CV_8UC3);
	for (int i = 0; i< size.height; i++)
		for (int j = 0; j< size.width; j++)
		{
			if (i<image1.rows && j<image1.cols)
			{
				img_match.data[(i*width+j)*3] = image01.data[(i*image01.cols+j)*3];
				img_match.data[(i*width+j)*3+1] = image01.data[(i*image01.cols+j)*3+1];
				img_match.data[(i*width+j)*3+2] = image01.data[(i*image01.cols+j)*3+2];
			}
			if (i>image1.rows && j>image1.cols)
			{
				img_match.data[(i*width+j)*3] = image02.data[((i-image1.rows)*image2.cols+j-image1.cols)*3];
				img_match.data[(i*width+j)*3+1] = image02.data[((i-image1.rows)*image2.cols+j-image1.cols)*3+1];
				img_match.data[(i*width+j)*3+2] = image02.data[((i-image1.rows)*image2.cols+j-image1.cols)*3+2];
			}
		}
	DrawKeyPoints(img_match, features1);
	CvSize size1;
	size1.height = image1.rows;
	size1.width = image1.cols;
    DrawKeyPointsLowRight(img_match, features2, size1);


	//vector<MatchPoint> v_matchpoint;

	////������ƥ��
	//for (int i = 0; i<features1.size(); i++)
	//{
	//	double odest = 0; //ŷ�Ͼ���
 //       int min_index = 0x7fffffff;
	//	double min_value = DBL_MAX;
	//	double penuntimatemin_value = DBL_MAX;
	//	for (int j = 0; j<features2.size(); j++)
	//	{
	//		//����ŷʽ�����
	//		for(int k = 0; k < FEATURE_ELEMENT_LENGTH; k++)
	//			odest += (features1[i].descriptor[k]-features2[j].descriptor[k])*(features1[i].descriptor[k]-features2[j].descriptor[k]);
	//		odest = sqrt(odest);
	//		//�ж��Ƿ�����С
	//	    //�������С������С��ֵ����С�����������С���ж��ǲ��Ǵ�С
	//		if (odest < min_value)
	//		{
	//			penuntimatemin_value = min_value;
	//			min_value = odest;
	//			min_index = j;
	//		}
	//		else
	//		{
	//			if (odest < penuntimatemin_value)
	//				penuntimatemin_value = odest;
	//		}
	//	}
	//	//�ж���С�ʹ�С��ֵ�Ƿ�С����ֵ
	//	//С����ֵ����MatchPoint����

	//	printf(" %lf\n", min_value/penuntimatemin_value);

	//	if (min_value/penuntimatemin_value < 0.5)
	//	{
	//		MatchPoint* matchpoint = new MatchPoint;
	//		matchpoint->index_1 = i;
	//		matchpoint->index_2 = min_index;
	//		v_matchpoint.push_back(*matchpoint);

	//	}
	//}

	//printf("match number  %d\n", v_matchpoint.size());

	////����
	//for (int i=0; i<v_matchpoint.size(); i++)
	//{
	//	Point point1, point2;
	//	point1.x = features1[v_matchpoint[i].index_1].dx;
	//	point1.y = features1[v_matchpoint[i].index_1].dy;
	//	point2.x = features2[v_matchpoint[i].index_2].dx;
	//	point2.y = features2[v_matchpoint[i].index_2].dy;
	//	line(img_match, point1, point2, Scalar(255,0,0));
	//}


	imshow("img_match", img_match);
	waitKey(0);
	return 0;
}
