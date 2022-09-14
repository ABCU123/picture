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
	//����ͼ��
	Mat image = imread(input_img);

	if (image.empty())
	{
		cout << "����ͼƬʧ��!" << endl;
		return;
	}

	//��ʾͼ��
	imshow("ԭͼ", image);

	Mat dstImage;
	//��˹ģ��
	GaussianBlur(image, dstImage, Size(9, 9), 11, 11);

	bool result = imwrite(output_img, dstImage);

	//��ʾЧ��ͼ
	imshow("��˹ģ��(Ч��ͼ)", dstImage);
	imwrite(output_img, dstImage);
	waitKey(0);
	return;
}

void image_to_gray() {

	//����ͼ��
	Mat image = imread(input_img);
	//��ʾͼ��
	imshow("ԭͼ", image);
	//����ƽ��ֵ����ʽD = ��R + G + B�� / 3���ҶȻ�ͼ��
	Mat hui(image.size(), CV_8UC1);

	for (int i = 0; i < image.rows; i++)
	{
		for (int j = 0; j < image.cols; j++)
		{
			hui.at<uchar>(i, j) = saturate_cast<uchar>((image.at<Vec3b>(i, j)[0] + image.at<Vec3b>(i, j)[1] + image.at<Vec3b>(i, j)[2]) / 3);
		}
	}
	imshow("�Ҷȱ任(Ч��ͼ)", hui);

	imwrite(output_img, hui);
	waitKey(0);
	return;
}

void init() {
	printf("Please input cmd:\n");
	printf("����һ������1��: ͼ��ģ��\n");
	printf("���ܶ�������2��: �任�Ҷ�ͼ\n");
	printf("������������3��: ͼ��ָ���ߴ�����\n");
	printf("�����ģ�����4��: ��Ե���\n");
}

void image_resize() {
	cout << "����ָ��������size: " << endl;
	double size;
	cin >> size;
	//����ͼ��
	Mat image = imread(input_img);
	Mat dstImage;

	if (image.empty())
	{
		cout << "����ͼƬʧ��!" << endl;
		return;
	}

	//��ʾͼ��
	imshow("ԭͼ", image);

	resize(image, dstImage, Size(image.cols * size, image.rows * size), (0, 0), (0, 0), 3);

	imshow("ͼ������(Ч��ͼ)", dstImage);

	imwrite(output_img, dstImage);

	waitKey(0);
	return;

}

void image_edge() {
	//����ͼ��
	//����ͼ��
	Mat image = imread(input_img);

	if (image.empty())
	{
		cout << "����ͼƬʧ��!" << endl;
	}

	imshow("ԭͼ", image);
	Mat greyImage, edge; //��������

	cvtColor(image, greyImage, COLOR_BGR2GRAY);

	blur(greyImage, edge, Size(3, 3));

	Canny(edge, edge, 3, 9, 3);

	imshow("��Ե��ȡ��Ч��ͼ)", edge);

	bool result = imwrite(output_img, edge);

	//�����������
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
			//ͼ��ģ��
			image_mohu();
			break;
		case 2:
			//�任�Ҷ�ͼ
			image_to_gray();
			break;
		case 3:
			//ͼ��ָ���ߴ�����
			image_resize();
			break;
		case 4:
			//��Ե��ȡ
			image_edge();
			break;
		default:
			break;
		}
		init();
	}
	return 0;
}

