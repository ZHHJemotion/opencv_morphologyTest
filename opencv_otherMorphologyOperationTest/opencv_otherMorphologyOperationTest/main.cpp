//
//  main.cpp
//  opencv_otherMorphologyOperationTest
//
//  Created by ZHHJemotion on 2016/10/17.
//  Copyright ı 2016Äê Lukas_Zhang. All rights reserved.
//

#include <iostream>
#include <opencv2/opencv.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>


using namespace cv;
using namespace std;

#define PATH string("/Users/zhangxingjian/Desktop/Programming/C++/OpenCV/opencv_test8/opencv_otherMorphologyOperationTest/opencv_otherMorphologyOperationTest/")

// ------------------------------- È«¾Ö±äÁ¿ÉêÃ÷²¿·Ö ------------------------------
//    Describe: È«¾Ö±äÁ¿ÉùÃ÷
// ----------------------------------------------------------------------------
Mat srcImage, dstImage1, dstImage2, dstImage3; //Ô­Ê¼Í¼ºÍĞ§¹ûÍ¼
int elementShape = MORPH_RECT; // ÔªËØ½á¹ûµÄĞÎ×´

// ±äÁ¿½ÓÊÕµÄ TrackBar Î»ÖÃ²ÎÊı
int maxIterationNum = 10; // µü´ú´ÎÊı×î´óÖµ
int openCloseNum = 0;
int erodeDilateNum  = 0;
int topBlackHatNum = 0;


// ------------------------------- È«¾Öº¯ÊıÉêÃ÷²¿·Ö ------------------------------
//    Describe: È«¾Öº¯ÊıÉêÃ÷£¨»Øµ÷º¯Êı£©
// ----------------------------------------------------------------------------
static void onOpenClose(int, void *); // ¿ª&±ÕÔËËã»Øµ÷º¯Êı
static void onErodeDilate(int, void *); // ¸¯Ê´&ÅòÕÍ²Ù×÷»Øµ÷º¯Êı
static void onTopBlackHat(int, void *); // ¶¥Ã±&ºÚÃ±²Ù×÷»Øµ÷º¯Êı
static void showHelpText(); // °ïÖúÎÄ×ÖÏÔÊ¾


// ------------------------------- main() º¯Êı ---------------------------------

int main(int argc, const char * argv[]) {
    // insert code here...
    std::cout << "Hello, World!\n";
    
    // system("color 2F");
    
    showHelpText();
    
    // ÔØÈëÔ­Í¼
    srcImage = imread(PATH+string("1.jpg"),1);
    // Òì³£´¦Àí
    if (!srcImage.data) {
        printf("error! we can not read the original image 1.jpg!!!\n");
        return false;
    }
    
    // ÏÔÊ¾Ô­Í¼
    namedWindow("Ô­Ê¼Í¼");
    imshow("Ô­Ê¼Í¼", srcImage);

    // ´´½¨ÆäÓà²Ù×÷µÄ´°¿Ú
    namedWindow("¿ªÔËËã&±ÕÔËËã");
    namedWindow("¸¯Ê´&ÅòÕÍ");
    namedWindow("¶¥Ã±&ºÚÃ±");
    
    // ²ÎÊı¸³Öµ
    openCloseNum = 9;
    erodeDilateNum  = 9;
    topBlackHatNum = 2;
    
    // ÎªÉÏÊöÈı¸ö´°¿Ú´´½¨¹ì¼£Ìõ
    createTrackbar("µü´úÖµ", "¿ªÔËËã&±ÕÔËËã", &openCloseNum, maxIterationNum*2+1, onOpenClose);
    createTrackbar("µü´úÖµ", "¸¯Ê´&ÅòÕÍ", &erodeDilateNum, maxIterationNum*2+1, onErodeDilate);
    createTrackbar("µü´úÖµ", "¶¥Ã±&ºÚÃ±", &topBlackHatNum, maxIterationNum*2+1, onTopBlackHat);
    
    // ÂÖÑ¯»ñÈ¡°´¼üĞÅÏ¢
    while (1)
    {
        int c;
        
        // Ö´ĞĞ»Øµ÷º¯Êı
        onOpenClose(openCloseNum, 0);
        onErodeDilate(erodeDilateNum, 0);
        onTopBlackHat(topBlackHatNum, 0);
        
        // »ñÈ¡°´¼ü
        c = waitKey(0);
        
        // °´ÏÂ¼üÅÌ q »òÕß esc£¬³ÌĞòÍË³ö, escµÄ ASCII ÂëÎª27
        if ((char)c == 'q' || (char)c == 27)
            break;
        // °´ÏÂ¼üÅÌ1£¬Ê¹ÓÃÍÖÔ²£¨Elliptic£©½á¹¹ÔªËØ MORPH_ELLIPSE
        if ((char)c == 49) // °´¼ü1µÄ ASCII ÂëÊÇ49
        {
            elementShape = MORPH_ELLIPSE;
        }
        // °´ÏÂ¼üÅÌ2£¬Ê¹ÓÃ¾ØĞÎ£¨Rectangle£©½á¹¹ÔªËØ MORPH_RECHT
        else if ((char)c == 50) // °´¼ü2µÄ ASCII ÂëÊÇ50
            elementShape = MORPH_RECT;
        // °´ÏÂ¼üÅÌ3£¬Ê¹ÓÃÊ®×ÖĞÎ£¨Cross-shaped£©½á¹¹ÔªËØ MORPH_CROSS
        else if ((char)c == 51) // °´¼ü3µÄ ASCII ÂëÊÇ51
            elementShape = MORPH_CROSS;
        // °´ÏÂ¼üÅÌ¿Õ¸ñ¼ü pass£¬ÔÚ¾ØĞÎ¡¢ÍÖÔ²¡¢Ê®×ÖĞÎ½á¹¹ÔªËØÖĞÑ­»·
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
//    Describe: ¿ª&±ÕÔËËã»Øµ÷º¯Êı
// -------------------------------------------------------------------------------------------
static void onOpenClose(int, void *)
{
    // Æ«ÒÆÁ¿µÄ¶¨Òå
    int offset = openCloseNum - maxIterationNum; //Æ«ÒÆÁ¿
    int absoluteOffset = offset > 0 ? offset : -offset; //Æ«ÒÆÁ¿¾ø¶ÔÖµ
    // ×Ô¶¨ÒåºË
    Mat element = getStructuringElement(elementShape, Size(absoluteOffset*2+1, absoluteOffset*2+1), Point(absoluteOffset,absoluteOffset));
    // ½øĞĞ²Ù×÷
    if (offset < 0)
    {
        morphologyEx(srcImage, dstImage1, MORPH_OPEN, element);
        // ÏÔÊ¾Í¼Ïñ
        //imshow("¿ªÔËËã", dstImage1);

    }
    else
    {
        morphologyEx(srcImage, dstImage1, MORPH_CLOSE, element);
        // ÏÔÊ¾Í¼Ïñ
        //imshow("±ÕÔËËã", dstImage1);
    }
    imshow("¿ªÔËËã&±ÕÔËËã", dstImage1);
}


// -------------------------------- onErodeDilate() Funciton ----------------------------------
//    Describe: ¸¯Ê´&ÅòÕÍ»Øµ÷º¯Êı
// -------------------------------------------------------------------------------------------
static void onErodeDilate(int, void *)
{
    // Æ«ÒÆÁ¿µÄ¶¨Òå
    int offset = erodeDilateNum - maxIterationNum; //Æ«ÒÆÁ¿
    int absoluteOffset = offset > 0 ? offset : -offset; //Æ«ÒÆÁ¿¾ø¶ÔÖµ
    // ×Ô¶¨ÒåºË
    Mat element = getStructuringElement(elementShape, Size(absoluteOffset*2+1, absoluteOffset*2+1), Point(absoluteOffset,absoluteOffset));
    // ½øĞĞ²Ù×÷
    if (offset < 0)
    {
        morphologyEx(srcImage, dstImage2, MORPH_ERODE, element);
        //imshow("¸¯Ê´", dstImage2);
    }
    else
    {
        morphologyEx(srcImage, dstImage2, MORPH_DILATE, element);
        //imshow("ÅòÕÍ", dstImage2);
    }
    imshow("¸¯Ê´&ÅòÕÍ", dstImage2);
}


// -------------------------------- onTopBlackHat() Funciton ----------------------------------
//    Describe: ¶¥Ã±&ºÚÃ±»Øµ÷º¯Êı
// -------------------------------------------------------------------------------------------
static void onTopBlackHat(int, void *)
{
    // Æ«ÒÆÁ¿µÄ¶¨Òå
    int offset = topBlackHatNum - maxIterationNum; //Æ«ÒÆÁ¿
    int absoluteOffset = offset > 0 ? offset : -offset; //Æ«ÒÆÁ¿¾ø¶ÔÖµ
    // ×Ô¶¨ÒåºË
    Mat element = getStructuringElement(elementShape, Size(absoluteOffset*2+1, absoluteOffset*2+1), Point(absoluteOffset,absoluteOffset));
    // ½øĞĞ²Ù×÷
    if (offset < 0)
    {
        morphologyEx(srcImage, dstImage3, MORPH_TOPHAT, element);
        //imshow("¶¥Ã±", dstImage3);
    }
    else
    {
        morphologyEx(srcImage, dstImage3, MORPH_BLACKHAT, element);
        //imshow("ºÚÃ±", dstImage3);
    }
    imshow("¶¥Ã±&ºÚÃ±", dstImage3);
}


// ---------------------------- showHelpText() Function -----------------------------------
//    Describe: output some helpful information
// ----------------------------------------------------------------------------------------
static void showHelpText()
{
    //Êä³ö°ïÖúĞÅÏ¢
    printf("\n\n\n\tÇëµ÷Õû¹ö¶¯Ìõ¹Û²ìÍ¼ÏñĞ§¹û~\n\n");
    printf( "\n\n\t°´¼ü²Ù×÷ËµÃ÷: \n\n"
           "\t\t¼üÅÌ°´¼ü¡¾ESC¡¿»òÕß¡¾Q¡¿- ÍË³ö³ÌĞò\n"
           "\t\t¼üÅÌ°´¼ü¡¾1¡¿- Ê¹ÓÃÍÖÔ²(Elliptic)½á¹¹ÔªËØ\n"
           "\t\t¼üÅÌ°´¼ü¡¾2¡¿- Ê¹ÓÃ¾ØĞÎ(Rectangle )½á¹¹ÔªËØ\n"
           "\t\t¼üÅÌ°´¼ü¡¾3¡¿- Ê¹ÓÃÊ®×ÖĞÍ(Cross-shaped)½á¹¹ÔªËØ\n"
           "\t\t¼üÅÌ°´¼ü¡¾¿Õ¸ñSPACE¡¿- ÔÚ¾ØĞÎ¡¢ÍÖÔ²¡¢Ê®×ÖĞÎ½á¹¹ÔªËØÖĞÑ­»·\n"
           "\n\n\t\t\t\t\t\t\t\t by ZHHJemotion"
           );
}
