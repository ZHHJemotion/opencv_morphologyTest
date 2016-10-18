//
//  main.cpp
//  opencv_otherMorphologyOperationTest
//
//  Created by ZHHJemotion on 2016/10/17.
//  Copyright � 2016�� Lukas_Zhang. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace cv;
using namespace std;

#define PATH string("/Users/zhangxingjian/Desktop/Programming/C++/OpenCV/opencv_test8/opencv_otherMorphologyOperationTest/opencv_otherMorphologyOperationTest/")

// ------------------------------- ȫ�ֱ����������� ------------------------------
//    Describe: ȫ�ֱ�������
// ----------------------------------------------------------------------------
Mat srcImage, dstImage1, dstImage2, dstImage3; //ԭʼͼ��Ч��ͼ
int elementShape = MORPH_RECT; // Ԫ�ؽ������״

// �������յ� TrackBar λ�ò���
int maxIterationNum = 10; // �����������ֵ
int openCloseNum = 0;
int erodeDilateNum  = 0;
int topBlackHatNum = 0;


// ------------------------------- ȫ�ֺ����������� ------------------------------
//    Describe: ȫ�ֺ����������ص�������
// ----------------------------------------------------------------------------
static void onOpenClose(int, void *); // ��&������ص�����
static void onErodeDilate(int, void *); // ��ʴ&���Ͳ����ص�����
static void onTopBlackHat(int, void *); // ��ñ&��ñ�����ص�����
static void showHelpText(); // ����������ʾ


// ------------------------------- main() ���� ---------------------------------

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    // system("color 2F");
    
    showHelpText();
    
    // ����ԭͼ
    srcImage = imread(PATH+string("1.jpg"),1);
    // �쳣����
    if (!srcImage.data) {
        printf("error! we can not read the original image 1.jpg!!!\n");
        return false;
    }
    
    // ��ʾԭͼ
    namedWindow("ԭʼͼ");
    imshow("ԭʼͼ", srcImage);

    // ������������Ĵ���
    namedWindow("������&������");
    namedWindow("��ʴ&����");
    namedWindow("��ñ&��ñ");
    
    // ������ֵ
    openCloseNum = 9;
    erodeDilateNum  = 9;
    topBlackHatNum = 2;
    
    // Ϊ�����������ڴ����켣��
    createTrackbar("����ֵ", "������&������", &openCloseNum, maxIterationNum*2+1, onOpenClose);
    createTrackbar("����ֵ", "��ʴ&����", &erodeDilateNum, maxIterationNum*2+1, onErodeDilate);
    createTrackbar("����ֵ", "��ñ&��ñ", &topBlackHatNum, maxIterationNum*2+1, onTopBlackHat);
    
    // ��ѯ��ȡ������Ϣ
    while (1)
    {
        int c;
        
        // ִ�лص�����
        onOpenClose(openCloseNum, 0);
        onErodeDilate(erodeDilateNum, 0);
        onTopBlackHat(topBlackHatNum, 0);
        
        // ��ȡ����
        c = waitKey(0);
        
        // ���¼��� q ���� esc�������˳�, esc�� ASCII ��Ϊ27
        if ((char)c == 'q' || (char)c == 27)
            break;
        // ���¼���1��ʹ����Բ��Elliptic���ṹԪ�� MORPH_ELLIPSE
        if ((char)c == 49) // ����1�� ASCII ����49
        {
            elementShape = MORPH_ELLIPSE;
        }
        // ���¼���2��ʹ�þ��Σ�Rectangle���ṹԪ�� MORPH_RECHT
        else if ((char)c == 50) // ����2�� ASCII ����50
            elementShape = MORPH_RECT;
        // ���¼���3��ʹ��ʮ���Σ�Cross-shaped���ṹԪ�� MORPH_CROSS
        else if ((char)c == 51) // ����3�� ASCII ����51
            elementShape = MORPH_CROSS;
        // ���¼��̿ո�� pass���ھ��Ρ���Բ��ʮ���νṹԪ����ѭ��
        else if ((char)c == ' ')
            elementShape = (elementShape +1) % 3;
        
    }
    
    // ========================================================================================
    //   Without using Trackbar
    Mat image = imread(PATH+string("1.jpg"),1);
    namedWindow("the original image");
    imshow("the original image", image);
    
    Mat outImage;
    namedWindow("the result after operation");
    
    Mat element1 = getStructuringElement(elementShape, Size(7,7));
    //morphologyEx(image, outImage, MORPH_OPEN, element1);
    //morphologyEx(image, outImage, MORPH_CLOSE, element1);
    //morphologyEx(image, outImage, MORPH_TOPHAT, element1);
    //morphologyEx(image, outImage, MORPH_BLACKHAT, element1);
    morphologyEx(image, outImage, MORPH_GRADIENT, element1);
    
    imshow("the result after operation", outImage);
    
    waitKey(0);
    //========================================================================================
    
    
    return 0;
}


// -------------------------------- onOpenClose() Funciton ----------------------------------
//    Describe: ��&������ص�����
// -------------------------------------------------------------------------------------------
static void onOpenClose(int, void *)
{
    // ƫ�����Ķ���
    int offset = openCloseNum - maxIterationNum; //ƫ����
    int absoluteOffset = offset > 0 ? offset : -offset; //ƫ��������ֵ
    // �Զ����
    Mat element = getStructuringElement(elementShape, Size(absoluteOffset*2+1, absoluteOffset*2+1), Point(absoluteOffset,absoluteOffset));
    // ���в���
    if (offset < 0)
    {
        morphologyEx(srcImage, dstImage1, MORPH_OPEN, element);
        // ��ʾͼ��
        //imshow("������", dstImage1);

    }
    else
    {
        morphologyEx(srcImage, dstImage1, MORPH_CLOSE, element);
        // ��ʾͼ��
        //imshow("������", dstImage1);
    }
    imshow("������&������", dstImage1);
}


// -------------------------------- onErodeDilate() Funciton ----------------------------------
//    Describe: ��ʴ&���ͻص�����
// -------------------------------------------------------------------------------------------
static void onErodeDilate(int, void *)
{
    // ƫ�����Ķ���
    int offset = erodeDilateNum - maxIterationNum; //ƫ����
    int absoluteOffset = offset > 0 ? offset : -offset; //ƫ��������ֵ
    // �Զ����
    Mat element = getStructuringElement(elementShape, Size(absoluteOffset*2+1, absoluteOffset*2+1), Point(absoluteOffset,absoluteOffset));
    // ���в���
    if (offset < 0)
    {
        morphologyEx(srcImage, dstImage2, MORPH_ERODE, element);
        //imshow("��ʴ", dstImage2);
    }
    else
    {
        morphologyEx(srcImage, dstImage2, MORPH_DILATE, element);
        //imshow("����", dstImage2);
    }
    imshow("��ʴ&����", dstImage2);
}


// -------------------------------- onTopBlackHat() Funciton ----------------------------------
//    Describe: ��ñ&��ñ�ص�����
// -------------------------------------------------------------------------------------------
static void onTopBlackHat(int, void *)
{
    // ƫ�����Ķ���
    int offset = topBlackHatNum - maxIterationNum; //ƫ����
    int absoluteOffset = offset > 0 ? offset : -offset; //ƫ��������ֵ
    // �Զ����
    Mat element = getStructuringElement(elementShape, Size(absoluteOffset*2+1, absoluteOffset*2+1), Point(absoluteOffset,absoluteOffset));
    // ���в���
    if (offset < 0)
    {
        morphologyEx(srcImage, dstImage3, MORPH_TOPHAT, element);
        //imshow("��ñ", dstImage3);
    }
    else
    {
        morphologyEx(srcImage, dstImage3, MORPH_BLACKHAT, element);
        //imshow("��ñ", dstImage3);
    }
    imshow("��ñ&��ñ", dstImage3);
}


// ---------------------------- showHelpText() Function -----------------------------------
//    Describe: output some helpful information
// ----------------------------------------------------------------------------------------
static void showHelpText()
{
    //���������Ϣ
    printf("\n\n\n\t������������۲�ͼ��Ч��~\n\n");
    printf( "\n\n\t��������˵��: \n\n"
           "\t\t���̰�����ESC�����ߡ�Q��- �˳�����\n"
           "\t\t���̰�����1��- ʹ����Բ(Elliptic)�ṹԪ��\n"
           "\t\t���̰�����2��- ʹ�þ���(Rectangle )�ṹԪ��\n"
           "\t\t���̰�����3��- ʹ��ʮ����(Cross-shaped)�ṹԪ��\n"
           "\t\t���̰������ո�SPACE��- �ھ��Ρ���Բ��ʮ���νṹԪ����ѭ��\n"
           "\n\n\t\t\t\t\t\t\t\t by ZHHJemotion"
           );
}
