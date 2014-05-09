//#include <iostream>
#include "functions.h"

//using namespace std;

int main()
{
    int threshold_value = 0;
    int threshold_type = 3;
    int level=200;
    int levelBin=30;
    int levelBin2=30;

    int const max_value = 255;
    int const max_type = 4;
    int const max_BINARY_value = 255;
    char* mainWindowName = "main window";
    char* shadow = "cieñ";
    char* hand = "r¹sia";
    char* resultWindowName = "result window";
    char* backgroundWindowName = "background window";
    int matchMethod=4;
    int optionOfDisplay=0;//0 -zbinaryzowany obraz 1- splot
        int morphSize=1;
    VideoCapture capture("video/v6.avi"); // open the video file for reading
    Mat templateImage = imread("video/t4.bmp", 0 );
    //VideoCapture capture(0); // open the video camera no. 0
    if (!capture.isOpened()){
         cout << "Cannot open the video file" << endl;
         return -1;
    }
    char* trackbar_type = "level";
    char* trackbar_value = "Value";
    char* templete = "Value";
   // Mat templateImage = imread("video/t2.bmp", 0 );

  /// Create windows
    namedWindow(mainWindowName, CV_WINDOW_AUTOSIZE);
    namedWindow(resultWindowName, CV_WINDOW_AUTOSIZE);
     namedWindow(backgroundWindowName, CV_WINDOW_AUTOSIZE);
     namedWindow(hand, CV_WINDOW_AUTOSIZE);
     namedWindow(shadow, CV_WINDOW_AUTOSIZE);
  /// Create Trackbar

   createTrackbar( trackbar_type, resultWindowName, &level, 255, 0 );
   createTrackbar( "level1", mainWindowName, &levelBin, 255, 0 );
   createTrackbar( "level2", mainWindowName, &levelBin2, 255, 0 );
   createTrackbar( "typ spolotu", resultWindowName, &matchMethod, 4, 0 );
   createTrackbar( "wielksoc elementu", mainWindowName, &morphSize, 20, 0 );
Mat frame,frame2;
Mat frameGray;
Mat result;
Mat background;//=imread("video/v5.avi", 0 );
Mat tempImg;
Mat element = getStructuringElement( MORPH_ELLIPSE, Size( 2*morphSize + 1, 2*morphSize+1 ), Point( morphSize, morphSize ) );
keyboard * klawiatura=new keyboard(196,126);

background= findBackGround(capture,klawiatura,templateImage);
background.copyTo(tempImg);
klawiatura->translateKeyboardCords();
klawiatura->drawKeyBoard(tempImg,templateImage);
imshow(resultWindowName, tempImg);
imshow(backgroundWindowName, background);
while(capture.read(frame)){

    //odejm(frame,background,levelBin,levelBin2);
    cien_palec(frame,background,frame,frame2);

    kontury(frame2,150);
    kontury(frame,150);

  //  morphSize=4;
    //element = getStructuringElement( MORPH_ELLIPSE, Size( 2*morphSize + 1, 2*morphSize+1 ), Point( morphSize, morphSize ) );

  /// Apply the specified morphology operation
    //morphologyEx( frame, frame, 0, element );
    //morphSize*=2;
   // element = getStructuringElement( MORPH_ELLIPSE, Size( 2*morphSize + 1, 2*morphSize+1 ), Point( morphSize, morphSize ) );
   // morphologyEx( frame, frame, 1, element );

   //imshow(mainWindowName, frame);
   imshow(hand, frame2);
   imshow(shadow, frame);

    if(waitKey(30) == 27){
        cout << "esc key is pressed by user" << endl;break;
    }
}
    destroyWindow(mainWindowName);
    destroyWindow(resultWindowName);
    destroyWindow(hand);
    destroyWindow(shadow);
    return 0;
}
