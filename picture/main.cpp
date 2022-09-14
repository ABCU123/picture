#include <opencv2/highgui/highgui.hpp>
#include<opencv2/imgproc/imgproc.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/opencv.hpp>
#include<stdlib.h>
#include<stdio.h>
#include<iostream>
#include <vector>
#include <string>
#include <sstream>
#include<opencv2/opencv.hpp>
#include<opencv2/core/core.hpp>
#include<opencv2/imgcodecs.hpp>
#include<opencv2/highgui.hpp>
#include<opencv2\imgproc\types_c.h>
#include<iostream>


using namespace std;
using namespace cv;

int flag;
string input_img;
string output_img;

void image_mohu() {
	//加载图像
	Mat image = imread(input_img);

	if (image.empty())
	{
		cout << "读入图片失败!" << endl;
		return;
	}

	//显示图像
	imshow("原图", image);

	Mat dstImage;
	//高斯模糊
	GaussianBlur(image, dstImage, Size(9, 9), 11, 11);

	bool result = imwrite(output_img, dstImage);

	//显示效果图
	imshow("高斯模糊(效果图)", dstImage);
	imwrite(output_img, dstImage);
	waitKey(0);
	return;
}

void image_to_gray() {

	//加载图像
	Mat image = imread(input_img);
	//显示图像
	imshow("原图", image);
	//利用平均值法公式D = （R + G + B） / 3，灰度化图像；
	Mat hui(image.size(), CV_8UC1);

	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			hui.at<uchar>(i, j) = saturate_cast<uchar>((image.at<Vec3b>(i, j)[0] + image.at<Vec3b>(i, j)[1] + image.at<Vec3b>(i, j)[2]) / 3);
		}
	}
	imshow("灰度变换(效果图)", hui);

	imwrite(output_img, hui);
	waitKey(0);
	return;
}

void init() {
	printf("Please input cmd:\n");
	printf("功能一（输入1）: 图像模糊\n");
	printf("功能二（输入2）: 变换灰度图\n");
	printf("功能三（输入3）: 图像指定尺寸缩放\n");
	printf("功能四（输入4）: 边缘检测\n");
}

void image_resize() {
	cout << "输入指定的缩放size: " << endl;
	double size;
	cin >> size;
	//加载图像
	Mat image = imread(input_img);
	Mat dstImage;

	if (image.empty())
	{
		cout << "读入图片失败!" << endl;
		return;
	}

	//显示图像
	imshow("原图", image);

	resize(image, dstImage, Size(image.cols * size, image.rows * size), (0, 0), (0, 0), 3);

	imshow("图像缩放(效果图)", dstImage);

	imwrite(output_img, dstImage);

	waitKey(0);
	return;

}

void image_edge() {
	//加载图像
	//加载图像
	Mat image = imread(input_img);

	if (image.empty())
	{
		cout << "读入图片失败!" << endl;
	}

	imshow("原图", image);
	Mat greyImage, edge; //参数定义

	cvtColor(image, greyImage, COLOR_BGR2GRAY);

	blur(greyImage, edge, Size(3, 3));

	Canny(edge, edge, 3, 9, 3);

	imshow("边缘提取（效果图)", edge);

	bool result = imwrite(output_img, edge);

	//按任意键结束
	waitKey(0);
	return;
}

int main()
{
	char input[256];
	init();
	while (cin >> input_img) {
		cin >> output_img;
		cin >> flag;
		switch (flag)
		{
		case 1:
			//图像模糊
			image_mohu();
			break;
		case 2:
			//变换灰度图
			image_to_gray();
			break;
		case 3:
			//图像指定尺寸缩放
			image_resize();
			break;
		case 4:
			//边缘提取
			image_edge();
			break;
		default:
			break;
		}
		init();
	}
	return 0;
}

