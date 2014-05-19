////#include <iostream>
//#include "functions.h"
//
//#define WINVER 0x0500   //
//#include <windows.h>    //do klawiatury
//
////using namespace std;
//int a=115;
//int b=255;
//int c=100;
//int d=120;
//int e=146;
//int f=220;
//
//
//int main()
//{
//    INPUT ip;                   //
//    ip.type = INPUT_KEYBOARD;   //
//    ip.ki.wScan = 0;            //do symulowania klawiatury
//    ip.ki.time = 0;             //
//    ip.ki.dwExtraInfo = 0;      //
//    ip.ki.dwFlags = 0; // 0 for key press
//
//    int threshold_value = 0;
//    int threshold_type = 3;
//    int level=200;
//    int levelBin=30;
//    int levelBin2=30;
//
//    int const max_value = 255;
//    int const max_type = 4;
//    int const max_BINARY_value = 255;
//    char* mainWindowName = "main window";
//    char* shadow = "cieñ";
//    char* hand = "r¹sia";
//    char* resultWindowName = "result window";
//    char* backgroundWindowName = "background window";
//    int matchMethod=4;
//    int optionOfDisplay=0;//0 -zbinaryzowany obraz 1- splot
//        int morphSize=1;
//    VideoCapture capture("video/v13.avi"); // open the video file for reading
//    Mat templateImage = imread("video/t4.bmp", 0 );
//    //VideoCapture capture(0); // open the video camera no. 0
//    if (!capture.isOpened()){
//         cout << "Cannot open the video file" << endl;
//         return -1;
//    }
//    char* trackbar_type = "level";
//    char* trackbar_value = "Value";
//    char* templete = "Value";
//
//  /// Create windows
//    namedWindow(mainWindowName, CV_WINDOW_AUTOSIZE);
//    namedWindow(resultWindowName, CV_WINDOW_AUTOSIZE);
//    namedWindow(backgroundWindowName, CV_WINDOW_AUTOSIZE);
//    namedWindow(hand, CV_WINDOW_AUTOSIZE);
//    namedWindow(shadow, CV_WINDOW_AUTOSIZE);
//    //namedWindow("test", CV_WINDOW_AUTOSIZE);
//   // namedWindow("test1", CV_WINDOW_AUTOSIZE);
//   // namedWindow("test2", CV_WINDOW_AUTOSIZE);
//  /// Create Trackbar
//
//    createTrackbar( trackbar_type, resultWindowName, &level, 255, 0 );
//    createTrackbar( "level1", mainWindowName, &levelBin, 255, 0 );
//    createTrackbar( "level2", mainWindowName, &levelBin2, 255, 0 );
//    createTrackbar( "typ spolotu", resultWindowName, &matchMethod, 4, 0 );
//    createTrackbar( "wielksoc elementu", mainWindowName, &morphSize, 20, 0 );
//    createTrackbar( "wielksoc elementu", mainWindowName, &morphSize, 20, 0 );
//    /*
//    createTrackbar( "a ", "test", &a, 255, 0 );
//    createTrackbar( "b ", "test", &b, 255, 0 );
//    createTrackbar( "c ", "test1", &c, 255, 0 );
//    createTrackbar( "d ", "test1", &d, 255, 0 );
//    createTrackbar( "e ", "test2", &e, 255, 0 );
//    createTrackbar( "f ", "test2", &f, 255, 0 );*/
//Mat frame,frame2;
//Mat frameGray;
//Mat result;
//Mat background;//=imread("video/v5.avi", 0 );
//Mat tempImg;
//Mat dlon,cien;
////Mat element = getStructuringElement( MORPH_ELLIPSE, Size( 2*morphSize + 1, 2*morphSize+1 ), Point( morphSize, morphSize ) );
//keyboard * klawiatura=new keyboard(196,126);
//
//background= findBackGround(capture,klawiatura,templateImage);
//background.copyTo(tempImg);
//klawiatura->translateKeyboardCords();
//klawiatura->drawKeyBoard(tempImg,templateImage);
//imshow(resultWindowName, tempImg);
//imshow(backgroundWindowName, background);
//
//while(capture.read(frame)){
//
// //   odejm(frame,background,levelBin,levelBin2);
//   cien_palec(frame,background,dlon,cien);
//   Point2i *r=najwyzej(dlon);
//   Point2i *p=najwyzej(cien);
//
//  if (r!=0 && p!=0){
//   //cout<<r->x<<";"<<r->y<<";";
//   //cout<<p->x<<";"<<p->y<<endl;
//   cv::line(frame, *r, *p, cv::Scalar(255,0,0), 2, CV_AA);
//   char znak=klawiatura->getKlawisz(*r,*p);
//   if (znak!=0){
//        ip.ki.wVk = VkKeyScan(znak);        //wysyla przerwanie klawiatury
//        SendInput(1, &ip, sizeof(INPUT));   //nie dziala przytrzymanie klawisza
//    cout<<znak<<endl;
//   }
//
//  }else{
//  //cout<<0<<";"<<0<<";";
//  // cout<<480<<";"<<0<<endl;
//  }
//////#include <iostream>
//#include "functions.h"
//
//#define WINVER 0x0500   //
//#include <windows.h>    //do klawiatury
//
////using namespace std;
//int a=115;
//int b=255;
//int c=100;
//int d=120;
//int e=146;
//int f=220;
//
//
//int main()
//{
//    INPUT ip;                   //
//    ip.type = INPUT_KEYBOARD;   //
//    ip.ki.wScan = 0;            //do symulowania klawiatury
//    ip.ki.time = 0;             //
//    ip.ki.dwExtraInfo = 0;      //
//    ip.ki.dwFlags = 0; // 0 for key press
//
//    int threshold_value = 0;
//    int threshold_type = 3;
//    int level=200;
//    int levelBin=30;
//    int levelBin2=30;
//
//    int const max_value = 255;
//    int const max_type = 4;
//    int const max_BINARY_value = 255;
//    char* mainWindowName = "main window";
//    char* shadow = "cieñ";
//    char* hand = "r¹sia";
//    char* resultWindowName = "result window";
//    char* backgroundWindowName = "background window";
//    int matchMethod=4;
//    int optionOfDisplay=0;//0 -zbinaryzowany obraz 1- splot
//        int morphSize=1;
//    VideoCapture capture("video/v13.avi"); // open the video file for reading
//    Mat templateImage = imread("video/t4.bmp", 0 );
//    //VideoCapture capture(0); // open the video camera no. 0
//    if (!capture.isOpened()){
//         cout << "Cannot open the video file" << endl;
//         return -1;
//    }
//    char* trackbar_type = "level";
//    char* trackbar_value = "Value";
//    char* templete = "Value";
//
//  /// Create windows
//    namedWindow(mainWindowName, CV_WINDOW_AUTOSIZE);
//    namedWindow(resultWindowName, CV_WINDOW_AUTOSIZE);
//    namedWindow(backgroundWindowName, CV_WINDOW_AUTOSIZE);
//    namedWindow(hand, CV_WINDOW_AUTOSIZE);
//    namedWindow(shadow, CV_WINDOW_AUTOSIZE);
//    //namedWindow("test", CV_WINDOW_AUTOSIZE);
//   // namedWindow("test1", CV_WINDOW_AUTOSIZE);
//   // namedWindow("test2", CV_WINDOW_AUTOSIZE);
//  /// Create Trackbar
//
//    createTrackbar( trackbar_type, resultWindowName, &level, 255, 0 );
//    createTrackbar( "level1", mainWindowName, &levelBin, 255, 0 );
//    createTrackbar( "level2", mainWindowName, &levelBin2, 255, 0 );
//    createTrackbar( "typ spolotu", resultWindowName, &matchMethod, 4, 0 );
//    createTrackbar( "wielksoc elementu", mainWindowName, &morphSize, 20, 0 );
//    createTrackbar( "wielksoc elementu", mainWindowName, &morphSize, 20, 0 );
//    /*
//    createTrackbar( "a ", "test", &a, 255, 0 );
//    createTrackbar( "b ", "test", &b, 255, 0 );
//    createTrackbar( "c ", "test1", &c, 255, 0 );
//    createTrackbar( "d ", "test1", &d, 255, 0 );
//    createTrackbar( "e ", "test2", &e, 255, 0 );
//    createTrackbar( "f ", "test2", &f, 255, 0 );*/
//Mat frame,frame2;
//Mat frameGray;
//Mat result;
//Mat background;//=imread("video/v5.avi", 0 );
//Mat tempImg;
//Mat dlon,cien;
////Mat element = getStructuringElement( MORPH_ELLIPSE, Size( 2*morphSize + 1, 2*morphSize+1 ), Point( morphSize, morphSize ) );
//keyboard * klawiatura=new keyboard(196,126);
//
//background= findBackGround(capture,klawiatura,templateImage);
//background.copyTo(tempImg);
//klawiatura->translateKeyboardCords();
//klawiatura->drawKeyBoard(tempImg,templateImage);
//imshow(resultWindowName, tempImg);
//imshow(backgroundWindowName, background);
//
//while(capture.read(frame)){
//
// //   odejm(frame,background,levelBin,levelBin2);
//   cien_palec(frame,background,dlon,cien);
//   Point2i *r=najwyzej(dlon);
//   Point2i *p=najwyzej(cien);
//
//  if (r!=0 && p!=0){
//   //cout<<r->x<<";"<<r->y<<";";
//   //cout<<p->x<<";"<<p->y<<endl;
//   cv::line(frame, *r, *p, cv::Scalar(255,0,0), 2, CV_AA);
//   char znak=klawiatura->getKlawisz(*r,*p);
//   if (znak!=0){
//        ip.ki.wVk = VkKeyScan(znak);        //wysyla przerwanie klawiatury
//        SendInput(1, &ip, sizeof(INPUT));   //nie dziala przytrzymanie klawisza
//    cout<<znak<<endl;
//   }
//
//  }else{
//  //cout<<0<<";"<<0<<";";
//  // cout<<480<<";"<<0<<endl;
//  }
//
//   // kontury(frame2,150);
//   // kontury(frame,150);
//   // morphSize=4;
//    //element = getStructuringElement( MORPH_ELLIPSE, Size( 2*morphSize + 1, 2*morphSize+1 ), Point( morphSize, morphSize ) );
//
//  /// Apply the specified morphology operation
//    //morphologyEx( frame, frame, 0, element );
//    //morphSize*=2;
//   // element = getStructuringElement( MORPH_ELLIPSE, Size( 2*morphSize + 1, 2*morphSize+1 ), Point( morphSize, morphSize ) );
//   // morphologyEx( frame, frame, 1, element );
//
//   imshow(mainWindowName, frame);
//   imshow(hand, dlon);
//   imshow(shadow, cien);
//
//    if(waitKey(30) == 27){
//        cout << "esc key is pressed by user" << endl;break;
//    }
//}
//    destroyWindow(mainWindowName);
//    destroyWindow(resultWindowName);
//    destroyWindow(hand);
//    destroyWindow(shadow);
//    return 0;
//}

//   // kontury(frame2,150);
//   // kontury(frame,150);
//   // morphSize=4;
//    //element = getStructuringElement( MORPH_ELLIPSE, Size( 2*morphSize + 1, 2*morphSize+1 ), Point( morphSize, morphSize ) );
//
//  /// Apply the specified morphology operation
//    //morphologyEx( frame, frame, 0, element );
//    //morphSize*=2;
//   // element = getStructuringElement( MORPH_ELLIPSE, Size( 2*morphSize + 1, 2*morphSize+1 ), Point( morphSize, morphSize ) );
//   // morphologyEx( frame, frame, 1, element );
//
//   imshow(mainWindowName, frame);
//   imshow(hand, dlon);
//   imshow(shadow, cien);
//
//    if(waitKey(30) == 27){
//        cout << "esc key is pressed by user" << endl;break;
//    }
//}
//    destroyWindow(mainWindowName);
//    destroyWindow(resultWindowName);
//    destroyWindow(hand);
//    destroyWindow(shadow);
//    return 0;
//}
