#include "modelT.h"

modelT::modelT()
{
    capt1.open(0);
    Mat templateImage = imread("video/t4.bmp", 0 );
    klawiatura=new keyboard(196,126);
    background= findBackGround(capt1,klawiatura,templateImage);
    background.copyTo(tempImg);
    klawiatura->translateKeyboardCords(templateImage.cols);

}

modelT::~modelT()
{
    //dtor
}

Mat modelT::detekcjaT(Mat frame,char &znak)
{
    cien_palec(frame,background,dlon,cien,a,b,c,d);
    Point2i *r=najwyzej(dlon);
    Point2i *p=najwyzej(cien);

    if (r!=0 && p!=0){
        cv::line(frame, *r, *p, cv::Scalar(255,0,0), 2, CV_AA);
        znak=klawiatura->getKlawisz(*r,*p,dist_reqT);
    }
    return frame;
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

