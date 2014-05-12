//#include <iostream>
#include "functions.h"

//using namespace std;
/*
int main()
{

    char* mainWindowName = "Main window";
    char* resultWindowName = "Result window";

    VideoCapture capture("video/vv11.wmv"); // open the video file for reading
    if (!capture.isOpened()){
         cout << "Cannot open the video file" << endl;
         return -1;
    }

  /// Create windows
    namedWindow(mainWindowName, CV_WINDOW_AUTOSIZE);
    namedWindow(resultWindowName, CV_WINDOW_AUTOSIZE);
//    namedWindow("Red", CV_WINDOW_AUTOSIZE);
//    namedWindow("Green", CV_WINDOW_AUTOSIZE);
//    namedWindow("Blue", CV_WINDOW_AUTOSIZE);
    //namedWindow("cien", CV_WINDOW_AUTOSIZE);
  /// Create Trackbars
    int ta=90;
    int tb=230;
    int tc=110;
    int td=240;
    int ymin=0;
    int ymax=140;
    int u1=200;
    int u2=30;
    int levelBin=10;
    createTrackbar( "Ta (Ta<Cb)", resultWindowName, &ta, 255, 0 );
    createTrackbar( "Tb (Cb<Tb)", resultWindowName, &tb, 255, 0 );
    createTrackbar( "Tc (Tc<Cb)", resultWindowName, &tc, 255, 0 );
    createTrackbar( "Td (Cb<Td)", resultWindowName, &td, 255, 0 );
    createTrackbar( "Ymin (Ymin<Y)", resultWindowName, &ymin, 255, 0 );
    createTrackbar( "Ymax (Y<Ymax)", resultWindowName, &ymax, 255, 0 );
    createTrackbar( "Pr�g1", mainWindowName, &u1, 255, 0 );
    createTrackbar( "Pr�g2", mainWindowName, &u2, 255, 0 );
    //createTrackbar( "Pr�g binaryzacji", "cien", &levelBin, 255, 0 );
 Mat tlo, frame, maska;
 vector<Vec3f> circles = tloznaczniki(capture, &tlo);
 vector<Point> srodki = vec3fToPoint(circles);
 Rect boundingrect = boundingRect(srodki);
 capture.read(frame);   //tej liniki nie powinno tu byc, ale odczytanie rozmiaru obrazu z samego capture rzucalo bledem
     maska = cv::Mat::zeros(frame.size(),CV_8UC1);
     maska(boundingrect) = 255;

Mat ycrcb;
Mat channel[3];
Mat result; //result to bedzie sam palec
Mat cien;
Mat polaczone;
Mat tym[3];
tym[2]=cv::Mat::zeros(frame.size(),CV_8UC1);
Point2i r,p;
//vector<Vec3f> circles;

while(capture.read(frame)){
    split(frame, channel);
    cvtColor(frame, ycrcb, CV_BGR2YCrCb);

///Wykrywanie palca
    ///Binaryzacja odwrotna zielonego kanalu
    //threshold(channel[1],result,levelBin,255,1);
    ///Detekcja koloru sk�ry
    inRange(ycrcb, Scalar(ymin, tc, ta), Scalar(ymax, td, tb), result);
        //maska to prostokatna maska wokol klawiatury, zeby usunac szumy spoza kartki.
    result &= maska;

///Wykrywanie cienia
    cien = channel[2] + result;
    threshold(cien,cien,levelBin,255,1);
    cien &= maska;
    ///inaczej:
    //cvtColor(frame, cien, CV_BGR2GRAY);
    //cien = cien-tlo2;

  /// Draw the circles detected
  for( size_t i = 0; i < circles.size(); i++ )
  {
      Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
      int radius = cvRound(circles[i][2]);
      circle( frame, center, 3, Scalar(0,255,0), -1, 8, 0 );      // circle center
      circle( frame, center, radius, Scalar(0,0,255), 3, 8, 0 );      // circle outline
  }
  ///Rysowanie prostokata miedzy srodkami kolek
  //void rectangle(Mat& img, Rect rec, const Scalar& color, int thickness=1, int lineType=8, int shift=0 )
  rectangle(frame, boundingrect, Scalar(255,0,0),1,8,0);


     Point2i *r=najwyzej(result);
   Point2i *p=najwyzej(cien);
    circle( tym[2], *r, 3, Scalar(255), -1, 8, 0 );
    circle( tym[2], *p, 3, Scalar(255), -1, 8, 0 );

    tym[0]=result;
    tym[1]=cien;
    //tym[2]=cv::Mat::zeros(frame.size(),CV_8UC1);
    merge(tym,3,polaczone);
    // Display
    imshow(mainWindowName, frame);
//    imshow("Blue", channel[0]);
//    imshow("Green", channel[1]);
//    imshow("Red", channel[2]);
    imshow(resultWindowName, polaczone);
    //imshow("cien", cien);

    tym[2]=cv::Mat::zeros(frame.size(),CV_8UC1);
    if(waitKey(30) == 27){
        cout << "esc key is pressed by user" << endl;break;
    }
}
    destroyAllWindows();
    return 0;
}
*/