//#include <iostream>
#include "functions.h"

//using namespace std;
int a=115;
int b=255;
int c=100;
int d=120;
int e=146;
int f=220;

int main()
{

    char* mainWindowName = "Main window";
    char* resultWindowName = "Result window";

    VideoCapture capture("video/vv1.wmv"); // open the video file for reading
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
    createTrackbar( "Próg1", mainWindowName, &u1, 255, 0 );
    createTrackbar( "Próg2", mainWindowName, &u2, 255, 0 );
    //createTrackbar( "Próg binaryzacji", "cien", &levelBin, 255, 0 );
 Mat tlo, frame, maska;
 ///ustawienie prostokata do wyzerowania
 vector<Vec3f> circles = tloznaczniki(capture, &tlo);
 vector<Point> brzegi = vec3fToPoint(circles);
 brzegi[0].x=brzegi[0].x-0.8*circles[0][2]; //lg
 brzegi[1].x=brzegi[1].x+0.8*circles[1][2]; //pg
 brzegi[2].x=brzegi[2].x-0.8*circles[2][2]; //ld
 brzegi[3].x=brzegi[3].x+0.8*circles[3][2]; //pd
 Rect boundingrect = boundingRect(brzegi);
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
Point2i *r,*p;
//vector<Vec3f> circles;

while(capture.read(frame)){
    split(frame, channel);
    cvtColor(frame, ycrcb, CV_BGR2YCrCb);

///Wykrywanie palca
    ///Binaryzacja odwrotna zielonego kanalu
    //threshold(channel[1],result,levelBin,255,1);
    ///Detekcja koloru skóry
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


   r=najwyzej(result);
   p=najwyzej(cien);
    //circle( tym[2], *r, 3, Scalar(255), -1, 8, 0 );
    //circle( tym[2], *p, 3, Scalar(255), -1, 8, 0 );
   line(tym[2], *r, *p, cv::Scalar(255), 3,8,0);


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

