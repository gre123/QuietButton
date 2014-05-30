#include "modelE.h"

modelE::modelE()
{

   captE1.open(0);
   ip.type = INPUT_KEYBOARD;   //
   ip.ki.wScan = 0;            //do symulowania klawiatury
   ip.ki.time = 0;             //
   ip.ki.dwExtraInfo = 0;      //
   ip.ki.dwFlags = 0; // 0 for key press

   captE1.set(CV_CAP_PROP_FRAME_WIDTH, 800);
   captE1.set(CV_CAP_PROP_FRAME_HEIGHT, 600);



   nazwaokna = "Podglad kamery - ustawianie tla";
   nazwaokna2 = "Ustawianie parametrow wykrywania reki";
   nazwaokna3 = "Ustawianie parametrow wykrywania cienia";
   nazwaokna4 = "Podglad wynikow";
   nazwaokna5 = "Model Klawiatury";


}

modelE::~modelE()
{
    //dtor
}




int modelE::ustawTloE(){

    cvNamedWindow(nazwaokna, CV_WINDOW_AUTOSIZE); //Create window
    createTrackbar( "Próg1", nazwaokna, &u1, 255, 0 );
    createTrackbar( "Próg2", nazwaokna, &u2, 255, 0 );
    cvSetMouseCallback( nazwaokna, myszkaCallback, (void*) &circles); //do ewentualnego wyklikiwania naroznikow

    while(captE1.read(frame)){ //Bedzie petla do wykrywania tla i kolek

        split(frame, channel);
		if (circles.size()>0 && circles[0][2]!=10){HoughCircles( channel[0], circles, CV_HOUGH_GRADIENT, 1, channel[0].rows/3, u1, u2, 0, 0 );}
		//metoda Mieszka I, ale zrobienie tego normalnie wymaga zrobienia struktury na kolka+boolean a nie chce mi sie tego robic

        for( size_t i = 0; i < circles.size(); i++ )
        {
            Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
            int radius = cvRound(circles[i][2]);
            circle( channel[0], center, 3, Scalar(0,255,0), -1, 8, 0 );      // circle center
            circle( channel[0], center, radius, Scalar(0,0,255), 3, 8, 0 );      // circle outline
        }
        putText(channel[0], "Ustaw znaczniki", cvPoint(30,30),
            FONT_HERSHEY_COMPLEX, 1, cvScalar(200,200,250), 1, CV_AA);
        imshow(nazwaokna, channel[0]);
        key = cvWaitKey(10);
        if (key == 27){
                cout << "Nacisnieto ESC" << endl;
                destroyAllWindows();
                return -1;
        }
        if (key == 13) {
                if (circles.size()==4){  //zmien na ==4
                    cout << "Nacisnieto ENTER, sa 4 kolka" << endl;
                    frame.copyTo(tlo);
                    destroyAllWindows();
                    break;
                } else {cout << "Nacisnieto ENTER, ale kolek jest: " << circles.size() << endl;}

        }
    }
    sortCircles(&circles);
    brzegi = vec3fToPoint(circles);
        brzegi[0].x=brzegi[0].x; //-0.8*circles[0][2]; //lg
        brzegi[1].x=brzegi[1].x; //+0.8*circles[1][2]; //pg
        brzegi[2].x=brzegi[2].x; //-0.8*circles[2][2]; //ld
        brzegi[3].x=brzegi[3].x; //+0.8*circles[3][2]; //pd
    Rect boundingrect = boundingRect(brzegi);

    maska = cv::Mat::zeros(tlo.size(),CV_8UC1);
    maska(boundingrect) = 255;

    klawiaturaE=new keyboard(264,120);
    klawiaturaE->setKeyboard(&brzegi);
    klawiaturaE->translateKeyboardCordsElp(25);


    return 0;
}

int modelE::ustawRekeE(){

    cvNamedWindow(nazwaokna2, CV_WINDOW_AUTOSIZE); //Create window

    createTrackbar( "Ta (Ta<Cb)", nazwaokna2, &ta, 255, 0 );
    createTrackbar( "Tb (Cb<Tb)", nazwaokna2, &tb, 255, 0 );
    createTrackbar( "Tc (Tc<Cb)", nazwaokna2, &tc, 255, 0 );
    createTrackbar( "Td (Cb<Td)", nazwaokna2, &td, 255, 0 );
    createTrackbar( "Ymin (Ymin<Y)", nazwaokna2, &ymin, 255, 0 );
    createTrackbar( "Ymax (Y<Ymax)", nazwaokna2, &ymax, 255, 0 );


    while(captE1.read(frame)){
        cvtColor(frame, ycrcb, CV_BGR2YCrCb);
        inRange(ycrcb, Scalar(ymin, tc, ta), Scalar(ymax, td, tb), reka);
        reka &= maska;

        imshow(nazwaokna2, reka);
        putText(reka, "Ustaw suwaki aby wyodrebnic palec", cvPoint(30,30),
            FONT_HERSHEY_COMPLEX, 1, cvScalar(200,200,250), 1, CV_AA);

        key = cvWaitKey(10);
        if (key == 27){
            cout << "Nacisnieto ESC" << endl;
            destroyAllWindows();
            return -1;
        }
        if (key == 13) {
            cout << "Nacisnieto ENTER, parametry wykrywania reki zapisane" << endl;
            destroyAllWindows();
            break;
        }
    }
    return 0;
}


int modelE::ustawCienE(){


    cvNamedWindow(nazwaokna3, CV_WINDOW_AUTOSIZE); //Create window
    createTrackbar( "Prog binaryzacji", nazwaokna3, &levelBin, 255, 0 );
    while(captE1.read(frame)){
        split(frame, channel);
        cvtColor(frame, ycrcb, CV_BGR2YCrCb);
        inRange(ycrcb, Scalar(ymin, tc, ta), Scalar(ymax, td, tb), reka);
        cien = channel[2] + reka;
        threshold(cien,cien,levelBin,255,1);
        cien &= maska;

        imshow(nazwaokna3, cien);
        key = cvWaitKey(10);
        if (key == 27){
            cout << "Nacisnieto ESC" << endl;
            destroyAllWindows();
            return -1;
        }else if (key == 13) {
            cout << "Nacisnieto ENTER, parametry wykrywania cienia zapisane" << endl;
            destroyAllWindows();
            break;
        }
    }
    return 0;
}



int modelE::ustawKlikE()
{



    cvNamedWindow("Klikniecie", CV_WINDOW_AUTOSIZE); //Create window
    Point2i *r,*p;
    Mat polaczone;
    Mat tym[3];
        tym[2]=cv::Mat::zeros(tlo.size(),CV_8UC1);
    char znak;
    while(captE1.read(frame)){

        split(frame, channel);
        cvtColor(frame, ycrcb, CV_BGR2YCrCb);
        inRange(ycrcb, Scalar(ymin, tc, ta), Scalar(ymax, td, tb), reka);
        reka &= maska;
        cien = channel[2] + reka;
        threshold(cien,cien,levelBin,255,1);
        cien &= maska;
        r=najwyzej(reka);
        p=najwyzej(cien);

        line(tym[2], *r, *p, cv::Scalar(255), 3,8,0);
        tym[0]=reka;
        tym[1]=cien;
        merge(tym,3,polaczone);
        imshow("Ustaw klikniecie", polaczone);
        putText(polaczone, "Przytrzymaj klawisz i wcisnij ENTER", cvPoint(30,30),
            FONT_HERSHEY_COMPLEX, 1, cvScalar(200,200,250), 1, CV_AA);
        tym[2]=cv::Mat::zeros(frame.size(),CV_8UC1);

        key = cvWaitKey(10);
        if (key == 27){
            cout << "Nacisnieto ESC" << endl;
            destroyAllWindows();
            return -1;
        }
        if (key == 13) {
            dist_req=(r->x-p->x)*(r->x-p->x)+(r->y-p->y)*(r->y-p->y) -20;
            cout << "Nacisnieto ENTER, odleglosc zapisana " << endl;
            destroyAllWindows();
            break;
        }


}
    return 0;
}
