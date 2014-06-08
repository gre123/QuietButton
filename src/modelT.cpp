#include "modelT.h"

modelT::modelT()
{
    capt1.open(0);
    Mat templateImage = imread("video/temp8x6.png", 0 );
    klawiatura=new keyboard(254,148,KB_WHITE);
    background= findBackGround(capt1,klawiatura,templateImage);
    background.copyTo(tempImg);
    klawiatura->translateKeyboardCords(17);
    klawiatura->drawKeyBoard(tempImg);
}

modelT::~modelT()
{
    //dtor
}

Mat modelT::detekcja(Mat frame,char &znak)
{
    cien_palec(frame,background,dlon,cien,a,b,c,d,levelThresh);
    Point2i *r=bigestPeakDetection(&dlon);
    Point2i *p=bigestPeakDetection(&cien);

    if (r!=0 && p!=0){
        cv::line(frame, *r, *p, cv::Scalar(255,0,0), 2, CV_AA);
        znak=klawiatura->getKlawisz(*r,*p,dist_reqT);
    }
    return frame;
}

int modelT::ustawReke()
{
    if(!capt1.isOpened()){ return -1;}
    char* mainWindowName = "Ustaw reke";
    char* cienWindowName = "Ustaw cien";
    char* klawWindowName = "Wykryta klawiatura";

    cvNamedWindow(mainWindowName, CV_WINDOW_AUTOSIZE); //Create window
    cvNamedWindow(cienWindowName, CV_WINDOW_AUTOSIZE);
    cvNamedWindow(klawWindowName, CV_WINDOW_AUTOSIZE);
    imshow(klawWindowName,tempImg);
    Mat dlon,cien;

    createTrackbar( "Ta (Ta<Cb)", mainWindowName, &a, 255, 0 );
    createTrackbar( "Tb (Cb<Tb)", mainWindowName, &b, 255, 0 );
    createTrackbar( "Tc (Tc<Cr)", mainWindowName, &c, 255, 0 );
    createTrackbar( "Td (Cr<Td)", mainWindowName, &d, 255, 0 );
    createTrackbar( "level", cienWindowName, &levelThresh, 255, 0 );
    while(capt1.read(frame)){

        cien_palec(frame,background,dlon,cien,a,b,c,d,levelThresh);
        imshow(mainWindowName, dlon);
        imshow(cienWindowName, cien);

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

int modelT::ustawKlik()
{
    char* mainWindowName = "Ustaw klik";
    char key;
    cvNamedWindow(mainWindowName, CV_WINDOW_AUTOSIZE); //Create window
    if(!capt1.isOpened()) return -1;
    Mat dlon,cien;

    while(capt1.read(frame)){
    cien_palec(frame,background,dlon,cien,a,b,c,d,levelThresh);
    imshow(mainWindowName, dlon);

    Point2i *r=bigestPeakDetection(&dlon);
    Point2i *p=bigestPeakDetection(&cien);

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

