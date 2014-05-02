#include <iostream>
#include "functions.h"

//using namespace std;

int main()
{
//processVideo("video/v4.avi");
//global variables
//Mat frame; //current frame



    int threshold_value = 0;
    int threshold_type = 3;
    int level=200;
    int levelBin=30;
    int levelBin2=30;

    int const max_value = 255;
    int const max_type = 4;
    int const max_BINARY_value = 255;
    char* mainWindowName = "main window";
    char* resultWindowName = "result window";
    int matchMethod=4;
    int optionOfDisplay=0;//0 -zbinaryzowany obraz 1- splot
        int morphSize=1;
    VideoCapture capture("video/v4.avi"); // open the video file for reading

    //VideoCapture capture(0); // open the video camera no. 0
    if (!capture.isOpened()){
         cout << "Cannot open the video file" << endl;
         return -1;
    }
    char* trackbar_type = "level";
    char* trackbar_value = "Value";
    char* templete = "Value";
    Mat templateImage = imread("video/t2.bmp", 0 );

    bool czyOne=true;

  /// Create windows
    namedWindow(mainWindowName, CV_WINDOW_AUTOSIZE);
    namedWindow(resultWindowName, CV_WINDOW_AUTOSIZE);
  /// Create Trackbar

   createTrackbar( trackbar_type, resultWindowName, &level, 255, 0 );
   createTrackbar( "level1", mainWindowName, &levelBin, 255, 0 );
   createTrackbar( "level2", mainWindowName, &levelBin2, 255, 0 );
   createTrackbar( "typ spolotu", resultWindowName, &matchMethod, 4, 0 );
   createTrackbar( "wielksoc elementu", mainWindowName, &morphSize, 20, 0 );
Mat frame;
Mat frameGray;
Mat result;
Mat background;//=imread("video/v5.avi", 0 );
Mat element = getStructuringElement( MORPH_ELLIPSE, Size( 2*morphSize + 1, 2*morphSize+1 ), Point( morphSize, morphSize ) );

//background.create(640,640,CV_8UC1 );
Mat originalBackGround;
//
capture.read(frame);

cvtColor( frame, frameGray, CV_RGB2GRAY );
adaptiveThreshold(frameGray, frameGray,level,CV_ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY,75,10);
levelOutImage(matchingMethod(matchMethod,optionOfDisplay,frameGray,templateImage,result),frame);
frame.copyTo(background);
while(capture.read(frame)){

    cvtColor( frame, frameGray, CV_RGB2GRAY );
    adaptiveThreshold(frameGray, frameGray,level,CV_ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY,75,10);
    vector<Point> *markers;
    markers=matchingMethod(matchMethod,optionOfDisplay,frameGray,templateImage,result);

    levelOutImage(markers,frame);

    odejm(frame,background,levelBin,levelBin2);
    morphSize=4;
    element = getStructuringElement( MORPH_ELLIPSE, Size( 2*morphSize + 1, 2*morphSize+1 ), Point( morphSize, morphSize ) );

  /// Apply the specified morphology operation
    morphologyEx( frame, frame, 0, element );
   // morphSize*=3;
    //element = getStructuringElement( MORPH_ELLIPSE, Size( 2*morphSize + 1, 2*morphSize+1 ), Point( morphSize, morphSize ) );
   // morphologyEx( frame, frame, 1, element );

   imshow(mainWindowName, frame);
   imshow(resultWindowName, result);

    if(waitKey(30) == 27){
        cout << "esc key is pressed by user" << endl;break;
    }
}
    destroyWindow(mainWindowName);
    destroyWindow(resultWindowName);
    return 0;
}