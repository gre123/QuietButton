#include "modelT.h"

modelT::modelT()
{
    //ctor
}

modelT::~modelT()
{
    //dtor
}

int modelT::klawiatura_zfilmu(string sciezka)
{
                 INPUT ip;                   //
                 ip.type = INPUT_KEYBOARD;   //
                 ip.ki.wScan = 0;            //do symulowania klawiatury
                 ip.ki.time = 0;             //
                 ip.ki.dwExtraInfo = 0;      //
                 ip.ki.dwFlags = 0; // 0 for key press

                int threshold_value = 0;
                int threshold_type = 3;
                int level=200;
                int levelBin=30;
                int levelBin2=30;

                int const max_value = 255;
                int const max_type = 4;
                int const max_BINARY_value = 255;
                char* mainWindowName = "main window";
                int matchMethod=4;
                int optionOfDisplay=0;//0 -zbinaryzowany obraz 1- splot
                int morphSize=1;

                VideoCapture capture(sciezka); // open the video file for reading
                Mat templateImage = imread("video/t4.bmp", 0 );
                if (!capture.isOpened()){
                    cout << "Cannot open the video file" << endl;
                return -1;
                }
                char* trackbar_type = "level";
                char* trackbar_value = "Value";
                char* templete = "Value";

  /// Create windows
    namedWindow(mainWindowName, CV_WINDOW_AUTOSIZE);
  /// Create Trackbar
    createTrackbar( "level1", mainWindowName, &levelBin, 255, 0 );
    createTrackbar( "level2", mainWindowName, &levelBin2, 255, 0 );
    createTrackbar( "wielksoc elementu", mainWindowName, &morphSize, 20, 0 );
    createTrackbar( "wielksoc elementu", mainWindowName, &morphSize, 20, 0 );

    keyboard * klawiatura=new keyboard(196,126);

    background= findBackGround(capture,klawiatura,templateImage);
    background.copyTo(tempImg);
    klawiatura->translateKeyboardCords();
    klawiatura->drawKeyBoard(tempImg,templateImage);

    while(capture.read(frame)){
    std::ostringstream str;
    str << "nacisnieto : " ;

    cien_palec(frame,background,dlon,cien);
    Point2i *r=najwyzej(dlon);
    Point2i *p=najwyzej(cien);

    if (r!=0 && p!=0){
        cv::line(frame, *r, *p, cv::Scalar(255,0,0), 2, CV_AA);
        char znak=klawiatura->getKlawisz(*r,*p);
        if (znak!=0){
            str<<znak;
            ip.ki.wVk = VkKeyScan(znak);        //wysyla przerwanie klawiatury
            SendInput(1, &ip, sizeof(INPUT));   //nie dziala przytrzymanie klawisza
            putText(frame, str.str(), cvPoint(30,30),
            FONT_HERSHEY_COMPLEX, 1, cvScalar(0,200,0), 1, CV_AA);
        }
    }
   imshow(mainWindowName, frame);

    if(waitKey(30) == 27){
        cout << "esc key is pressed by user" << endl;break;
    }
    if(waitKey(30) == 13){
        cout << "wcisnieto ENTER" << endl;break;
    }

    }
    destroyWindow(mainWindowName);
    return 0;

    }


int modelT::klawiatura_podglad(VideoCapture capture)
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
      int matchMethod=4;
      int optionOfDisplay=0;//0 -zbinaryzowany obraz 1- splot
      int morphSize=1;

      Mat templateImage = imread("video/t4.bmp", 0 );
      if (!capture.isOpened()){
        cout << "Cannot open the camera" << endl;
        return -1;
      }
      char* trackbar_type = "level";
      char* trackbar_value = "Value";
      char* templete = "Value";


  /// Create windows
    namedWindow(mainWindowName, CV_WINDOW_AUTOSIZE);
  /// Create Trackbar
    createTrackbar( "level1", mainWindowName, &levelBin, 255, 0 );
    createTrackbar( "level2", mainWindowName, &levelBin2, 255, 0 );
    createTrackbar( "wielksoc elementu", mainWindowName, &morphSize, 20, 0 );
    createTrackbar( "wielksoc elementu", mainWindowName, &morphSize, 20, 0 );

    keyboard * klawiatura=new keyboard(196,126);

    background= findBackGround(capture,klawiatura,templateImage);
    background.copyTo(tempImg);
    klawiatura->translateKeyboardCords();
    klawiatura->drawKeyBoard(tempImg,templateImage);

    while(capture.read(frame)){
    std::ostringstream str;
    str << "nacisnieto : " ;

    cien_palec(frame,background,dlon,cien);
    Point2i *r=najwyzej(dlon);
    Point2i *p=najwyzej(cien);

    if (r!=0 && p!=0){
        cv::line(frame, *r, *p, cv::Scalar(255,0,0), 2, CV_AA);
        char znak=klawiatura->getKlawisz(*r,*p);
        if (znak!=0){
            str<<znak;
            putText(frame, str.str(), cvPoint(30,30),
            FONT_HERSHEY_COMPLEX, 1, cvScalar(0,200,0), 1, CV_AA);
        }
    }
   imshow(mainWindowName, frame);

    if(waitKey(30) == 27){
        cout << "esc key is pressed by user" << endl;break;
    }
    if(waitKey(30) == 13){
        cout << "wcisnieto ENTER" << endl;break;
    }

    }

    destroyWindow(mainWindowName);
    return 0;
}

