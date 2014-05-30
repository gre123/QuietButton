#include "modelT.h"

modelT::modelT()
{
    capt1.open("video/v12.avi");
    Mat templateImage = imread("video/t4.bmp", 0 );
    klawiatura=new keyboard(196,126);
    background= findBackGround(capt1,klawiatura,templateImage);
    background.copyTo(tempImg);
    klawiatura->translateKeyboardCords(templateImage.cols);
 //   klawiatura->drawKeyBoard(tempImg);

}

modelT::~modelT()
{
    //dtor
}

int modelT::ustawRekeT()
{

    char* mainWindowName = "Ustaw reke";
    if(!capt1.isOpened()) return -1;
    cvNamedWindow(mainWindowName, CV_WINDOW_AUTOSIZE); //Create window

    Mat dlon,cien;



    createTrackbar( "Ta (Ta<Cb)", mainWindowName, &a, 255, 0 );
    createTrackbar( "Tb (Cb<Tb)", mainWindowName, &b, 255, 0 );
    createTrackbar( "Tc (Tc<Cb)", mainWindowName, &c, 255, 0 );
    createTrackbar( "Td (Cb<Td)", mainWindowName, &d, 255, 0 );

    while(capt1.read(frame)){
        cien_palec(frame,background,dlon,cien,a,b,c,d);
        imshow(mainWindowName, dlon);

        if(waitKey(30) == 27){
            cout << "esc key is pressed by user" << endl;break;
        }
        if(waitKey(30) == 13){
            destroyWindow(mainWindowName);
            cout << "wcisnieto ENTER" << endl;break;
        }

    }
    destroyWindow(mainWindowName);
    return 0;
}


int modelT::klawiatura_zfilmu(string sciezka)
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
                Mat dlon,cien;
                VideoCapture capt2(sciezka); // open the video file for readin
                if (!capt2.isOpened()){
                    cout << "Cannot open the video file" << endl;
                return -1;
                }


  /// Create windows
    namedWindow(mainWindowName, CV_WINDOW_AUTOSIZE);
    namedWindow("back", CV_WINDOW_AUTOSIZE);

    while(capt2.read(frame)){
    std::ostringstream str;
    str << "nacisnieto : " ;

    cien_palec(frame,background,dlon,cien,a,b,c,d);

    Point2i *r=najwyzej(dlon);
    Point2i *p=najwyzej(cien);

    if (r!=0 && p!=0){
        cv::line(frame, *r, *p, cv::Scalar(255,0,0), 2, CV_AA);
        char znak=klawiatura->getKlawisz(*r,*p,dist_reqT);
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

int modelT::ustawKlikT()
{
    char* mainWindowName = "Ustaw klik";
    char key;
    cvNamedWindow(mainWindowName, CV_WINDOW_AUTOSIZE); //Create window
    if(!capt1.isOpened()) return -1;
    Mat dlon,cien;

    while(capt1.read(frame)){
    cien_palec(frame,background,dlon,cien,a,b,c,d);
    imshow(mainWindowName, dlon);

    Point2i *r=najwyzej(dlon);
    Point2i *p=najwyzej(cien);

    if (r!=0 && p!=0){
        cv::line(frame, *r, *p, cv::Scalar(255,0,0), 2, CV_AA);
    }

        key = cvWaitKey(10);
        if (key == 27){
            cout << "Nacisnieto ESC" << endl;
            destroyAllWindows();
            return -1;
        }
        if (key == 13) {
            dist_reqT=(r->x-p->x)*(r->x-p->x)+(r->y-p->y)*(r->y-p->y) -50;
            cout << "Nacisnieto ENTER, odleglosc zapisana " << endl;

            break;
        }


}
    destroyAllWindows();
    return 0;
}
int modelT::klawiatura_podgladT()
{
      int threshold_value = 0;
      int threshold_type = 3;
      int level=200;
      int levelBin=30;
      int levelBin2=30;

      Mat dlon,cien;
      int const max_value = 255;
      int const max_type = 4;
      int const max_BINARY_value = 255;
      char* mainWindowName = "main window";
      int matchMethod=4;
      int optionOfDisplay=0;//0 -zbinaryzowany obraz 1- splot
      int morphSize=1;

      if (!capt1.isOpened()){
        cout << "Cannot open the camera" << endl;
        return -1;
      }

  /// Create windows
    namedWindow(mainWindowName, CV_WINDOW_AUTOSIZE);


    while(capt1.read(frame)){
    std::ostringstream str;
    str << "nacisnieto : " ;

    cien_palec(frame,background,dlon,cien,a,b,c,d);
    Point2i *r=najwyzej(dlon);
    Point2i *p=najwyzej(cien);

    if (r!=0 && p!=0){
        cv::line(frame, *r, *p, cv::Scalar(255,0,0), 2, CV_AA);
        char znak=klawiatura->getKlawisz(*r,*p,dist_reqT);
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

int modelT::klawiatura_standardT()
{
      Mat dlon,cien;
      char* mainWindowName = "main window";
      int matchMethod=4;
      int optionOfDisplay=0;//0 -zbinaryzowany obraz 1- splot
      int morphSize=1;

      if (!capt1.isOpened()){
        cout << "Cannot open the camera" << endl;
        return -1;
      }

    ip.type = INPUT_KEYBOARD;   //
    ip.ki.wScan = 0;            //do symulowania klawiatury
    ip.ki.time = 0;             //
    ip.ki.dwExtraInfo = 0;      //
    ip.ki.dwFlags = 0; // 0 for key press

    cout<<"Klawiatura na standard. aby wyjsc wcisnij enter"<<endl;
    while(capt1.read(frame) && !kbhit()){


    cien_palec(frame,background,dlon,cien,a,b,c,d);
    Point2i *r=najwyzej(dlon);
    Point2i *p=najwyzej(cien);

    if (r!=0 && p!=0){
        char znak=klawiatura->getKlawisz(*r,*p,dist_reqT);
        if (znak!=0){

            ip.ki.wVk = VkKeyScan(znak);        //wysyla przerwanie klawiatury
            SendInput(1, &ip, sizeof(INPUT));   //nie dziala przytrzymanie klawisza
        }
    }


    }

    return 0;
}
