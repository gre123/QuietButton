#include <iostream>
#include "functions.h"

//using namespace std;

int main()
{
    int threshold_value = 0;
    int threshold_type = 3;
    int level=200;
    int levelBin=85;
    int levelBin2=104;

    int const max_value = 255;
    int const max_type = 4;
    int const max_BINARY_value = 255;
    char* mainWindowName = "main window";
    char* resultWindowName = "result window";
    int matchMethod=1;
    int optionOfDisplay=0;//0 -zbinaryzowany obraz 1- splot
    VideoCapture capture("D:/Grzesiek/C++ pliki/QuietButton/klawiatura/v1.avi"); // open the video file for reading
    //VideoCapture capture(0); // open the video camera no. 0
    if (!capture.isOpened()){
         cout << "Cannot open the video file" << endl;
         return -1;
    }
    char* trackbar_type = "level";
    char* trackbar_value = "Value";
    char* templete = "Value";
    Mat templateImage = imread("D:/Grzesiek/C++ pliki/QuietButton/t1.jpg", 0 );

    bool czyOne=true;

  /// Create windows
    namedWindow(mainWindowName, CV_WINDOW_AUTOSIZE);
    namedWindow(resultWindowName, CV_WINDOW_AUTOSIZE);
  /// Create Trackbar
 // char* trackbar_label = "Method: \n 0: SQDIFF \n 1: SQDIFF NORMED \n 2: TM CCORR \n 3: TM CCORR NORMED \n 4: TM COEFF \n 5: TM COEFF NORMED";
 // createTrackbar( trackbar_label, resultWindowName, &matchMethod, 4, 0 );

   createTrackbar( trackbar_type, resultWindowName, &level, 255, 0 );
   createTrackbar( "level1", mainWindowName, &levelBin, 255, 0 );
   createTrackbar( "level2", mainWindowName, &levelBin2, 255, 0 );

Mat frame;
Mat frameGray;
Mat result;
Mat background;
while(capture.read(frame)){
    cvtColor( frame, frameGray, CV_RGB2GRAY );
   // threshold( frameGray, frameGray, level, max_BINARY_value,4 );
    adaptiveThreshold(frameGray, frameGray,level,CV_ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY,75,10);


    /// Load image and template
    //frameGray.copyTo( img );
    vector<Point> *markers;
    markers=matchingMethod(matchMethod,optionOfDisplay,frameGray,templateImage,result);
    levelOutImage(markers,frame);

    /// Image processing
    if(czyOne)
    {

        background=frame;
        czyOne=false;
    }
    odejm(frame,background,levelBin,levelBin2);

    ///Displaying

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
