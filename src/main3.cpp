//#include <iostream>
#include "modelT.h"
#define WINVER 0x0500   //
#include <windows.h>    //do klawiatury
#include <fstream>
#include <conio.h>
#include <stdio.h>
using namespace std;

int a=115;
int b=255;
int c=100;
int d=120;
int e=146;
int f=220;

int ta=90;
int tb=230;
int tc=110;
int td=240;
int ymin=0;
int ymax=140;
int levelBin=10;
int dist_req;

char nazwaokna[] = "Podglad kamery - ustawianie tla";
char nazwaokna2[] = "Ustawianie parametrow wykrywania reki";
char nazwaokna3[] = "Ustawianie parametrow wykrywania cienia";
char nazwaokna4[] = "Podglad wynikow";
char nazwaokna5[] = "Model Klawiatury";
char key,option;
char model='E';
Mat frame, channel[3], tlo,maska,ycrcb, reka,cien;
VideoCapture capture(0);
vector<Point> brzegi;
INPUT ip;
std::ostringstream str ;
bool bylaKalibracja=false;
char sciezk[50];
modelT modT;
keyboard * klawiatura;

int ustawTlo(){
    int u1=150;
    int u2=100;

    cvNamedWindow(nazwaokna, CV_WINDOW_AUTOSIZE); //Create window
    createTrackbar( "Próg1", nazwaokna, &u1, 255, 0 );
    createTrackbar( "Próg2", nazwaokna, &u2, 255, 0 );
    vector<Vec3f> circles;
    cvSetMouseCallback( nazwaokna, myszkaCallback, (void*) &circles); //do ewentualnego wyklikiwania naroznikow
    while(capture.read(frame)){ //Bedzie petla do wykrywania tla i kolek

        split(frame, channel);
        //cvtColor(frame, channel[0], CV_BGR2GRAY);
        //inRange(channel[0], Scalar(200), Scalar(255), channel[0]);
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

    return 0;
}

int ustawReke(){

    cvNamedWindow(nazwaokna2, CV_WINDOW_AUTOSIZE); //Create window

    createTrackbar( "Ta (Ta<Cb)", nazwaokna2, &ta, 255, 0 );
    createTrackbar( "Tb (Cb<Tb)", nazwaokna2, &tb, 255, 0 );
    createTrackbar( "Tc (Tc<Cb)", nazwaokna2, &tc, 255, 0 );
    createTrackbar( "Td (Cb<Td)", nazwaokna2, &td, 255, 0 );
    createTrackbar( "Ymin (Ymin<Y)", nazwaokna2, &ymin, 255, 0 );
    createTrackbar( "Ymax (Y<Ymax)", nazwaokna2, &ymax, 255, 0 );


    while(capture.read(frame)){
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

int ustawCien(){


    cvNamedWindow(nazwaokna3, CV_WINDOW_AUTOSIZE); //Create window
    createTrackbar( "Prog binaryzacji", nazwaokna3, &levelBin, 255, 0 );
    while(capture.read(frame)){
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

int ustawKlik()
{
    cvNamedWindow("Klikniecie", CV_WINDOW_AUTOSIZE); //Create window
    Point2i *r,*p;
    Mat polaczone;
    Mat tym[3];
        tym[2]=cv::Mat::zeros(tlo.size(),CV_8UC1);
    char znak;
    while(capture.read(frame)){

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

int klawiatura_podglad()
{
    int licznik=0;
    cvNamedWindow(nazwaokna4, CV_WINDOW_AUTOSIZE); //Create window
     str << "kolKlikniecie zwrocil: " ;
    Point2i *r,*p;
    Mat polaczone;
    Mat tempImg;

    Mat tym[3];
        tym[2]=cv::Mat::zeros(tlo.size(),CV_8UC1);
    char znak;


    //// model z  klawiatura
    cvNamedWindow(nazwaokna5, CV_WINDOW_AUTOSIZE); //Create window
    klawiatura->setKeyboard(&brzegi);
    tlo.copyTo(tempImg);
    klawiatura->translateKeyboardCordsElp(25);
    klawiatura->drawKeyBoard(tempImg);
    imshow(nazwaokna5,tempImg);
    ////
//cout << "echodze do while'a 4" << endl;
    while(capture.read(frame)){
        split(frame, channel);
        cvtColor(frame, ycrcb, CV_BGR2YCrCb);
        inRange(ycrcb, Scalar(ymin, tc, ta), Scalar(ymax, td, tb), reka);
        reka &= maska;
//cout << "mam reke" << endl;
        cien = channel[2] + reka;
        threshold(cien,cien,levelBin,255,1);
        cien &= maska;
//cout << "mam cien i maske" << endl;
        r=najwyzej(reka);
        p=najwyzej(cien);

        line(tym[2], *r, *p, cv::Scalar(255), 3,8,0);
        tym[0]=reka;
        tym[1]=cien;
        merge(tym,3,polaczone);
            //str << "Pozycja palca: (" << (*r).x << "," << (*r).y << ")";
          //  znak = kolKlikniecie(r,p,&(brzegi[0]), &(brzegi[1]), &(brzegi[2]),dist_req);
             znak = klawiatura->getKlawisz(*r,*p,dist_req);

           if (znak!=0 && znak!='+' && znak!='-' && znak!='<' && znak!='>'){
                if(licznik==0 || licznik>=50)
                {
                    ip.ki.wVk = VkKeyScan(znak);        //wysyla przerwanie klawiatury
                    SendInput(1, &ip, sizeof(INPUT));   //nie dziala przytrzymanie klawisza
                }
                licznik++;
            }
            else licznik=0;
            imshow(nazwaokna4, polaczone);
            putText(polaczone, str.str(), cvPoint(30,30),
            FONT_HERSHEY_COMPLEX, 1, cvScalar(200,200,250), 1, CV_AA);


        tym[2]=cv::Mat::zeros(frame.size(),CV_8UC1);

        key = cvWaitKey(10);
        if (key == 27){
            cout << "Nacisnieto ESC" << endl;
            destroyAllWindows();
            return -1;
        }
        if (key == 13) {
            cout << "Nacisnieto ENTER, konczymy impreze" << endl;//trzeba bedzie to w dzialajacej wersji usunac
            destroyAllWindows();
            break;
        }
    }


    return 0;
}


int klawiatura_system()
{
    int licznik=0;
    Point2i *r,*p;
    Mat polaczone;
   // Mat tempImg;
    Mat tym[3];
        tym[2]=cv::Mat::zeros(tlo.size(),CV_8UC1);
    char znak;

    cout<<"Klawiatura na standard. aby wyjsc wcisnij enter"<<endl;
    while(capture.read(frame) && !kbhit()){
        split(frame, channel);
        cvtColor(frame, ycrcb, CV_BGR2YCrCb);
        inRange(ycrcb, Scalar(ymin, tc, ta), Scalar(ymax, td, tb), reka);
        reka &= maska;
        cien = channel[2] + reka;
        threshold(cien,cien,levelBin,255,1);
        cien &= maska;

        r=najwyzej(reka);
        p=najwyzej(cien);

        tym[0]=reka;
        tym[1]=cien;

        merge(tym,3,polaczone);
            znak = kolKlikniecie(r,p,&(brzegi[0]), &(brzegi[1]), &(brzegi[2]),dist_req);
            if (znak!=0 && znak!='+' && znak!='-' && znak!='<' && znak!='>'){
                if(licznik==0 || licznik>=50)
                {
                    ip.ki.wVk = VkKeyScan(znak);        //wysyla przerwanie klawiatury
                    SendInput(1, &ip, sizeof(INPUT));   //nie dziala przytrzymanie klawisza
                }
                licznik++;
            }
            else licznik=0;

        tym[2]=cv::Mat::zeros(frame.size(),CV_8UC1);
    }

    return 0;
}

int klawiatura_dopliku(char* sciezka)
{
    int licznik =0;
    fstream pl(sciezka,ios::out);
    if(!pl.good()){ return -1;}

    str << "kolKlikniecie zwrocil: " ;
    cvNamedWindow("DoPliku", CV_WINDOW_AUTOSIZE); //Create window
    Point2i *r,*p;
    Mat polaczone;
    Mat tym[3];
        tym[2]=cv::Mat::zeros(tlo.size(),CV_8UC1);
    char znak;
    while(capture.read(frame)){
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
        znak = kolKlikniecie(r,p,&(brzegi[0]), &(brzegi[1]), &(brzegi[2]),dist_req);
         if (znak!=0 && znak!='+' && znak!='-' && znak!='<' && znak!='>'){
                if(licznik==0 || licznik>=50)
                {
                    str<< znak;
                    pl<<znak;
                }
                licznik++;
            }
            else licznik=0;

        //pl.flush();
        imshow("DoPliku", polaczone);
        putText(polaczone, str.str(), cvPoint(30,30),
            FONT_HERSHEY_COMPLEX, 1, cvScalar(200,200,250), 1, CV_AA);
        tym[2]=cv::Mat::zeros(frame.size(),CV_8UC1);

        key = cvWaitKey(10);
        if (key == 27){
            cout << "Nacisnieto ESC" << endl;
            destroyAllWindows();
            pl.close();
            return -1;
        }
        if (key == 13) {
            cout << "Nacisnieto ENTER, konczymy impreze" << endl;//trzeba bedzie to w dzialajacej wersji usunac
            destroyAllWindows();
            pl.close();
            break;
        }
    }
    return 0;
}

int klawiatura_zfilmu(string sciezka)
{

    return 0;
}

int main(){
                      //
    ip.type = INPUT_KEYBOARD;   //
    ip.ki.wScan = 0;            //do symulowania klawiatury
    ip.ki.time = 0;             //
    ip.ki.dwExtraInfo = 0;      //
    ip.ki.dwFlags = 0; // 0 for key press

    // open the video file for reading
    if (!capture.isOpened()){
         cout << "Nie znalazlem kamery!" << endl;
         return -1;
    }
    capture.set(CV_CAP_PROP_FRAME_WIDTH, 800);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT, 600);
    klawiatura=new keyboard(264,120);
///Chyba wszystko ustawione, teraz koncowe wyswietlanie

    do
    {
        cout<<string(22, '\n');
        cout<<"KLAWIATURA <<<<<<<<<<<<<"<<endl;
        cout<<"Model : "<<model<<endl<<endl;

        if(model=='E'){
        cout<<"Kalibracja (k)"<<endl;
        cout<<"Odpal klawiature jako standard. (s)"<<endl;
        cout<<"Odpal klawiature - podglad wyniku (w)"<<endl;
        cout<<"Odpal klawiature i zapisuj do pliku (p)"<<endl;
        cout<<"Zmiana modelu klawiatury (m)"<<endl;
        cout<<"Wczytaj znaki z filmu (f)"<<endl;
        cout<<"Wyjscie (q)"<<endl;
        }

        if(model=='T'){
        cout<<"Odpal klawiature - podglad wyniku (w)"<<endl;
        cout<<"Zmiana modelu klawiatury (m)"<<endl;
        cout<<"Wczytaj znaki z filmu (f)"<<endl;
        cout<<"Wyjscie (q)"<<endl;
        }

        cin>>option;
        switch(option)
        {
            case 'k':
            {
                ///czesc do wykrywania pozycji klawiatury
                if(ustawTlo()==-1) return 0;
                ///teraz czesc do ustawiania parametrow modelu koloru skory
                //destroyAllWindows();
                if(ustawReke()==-1) return 0;
                ///Teraz czesc do ustawiania parametrow wykrywania cienia
                if(ustawCien()==-1) return 0;

                if(ustawKlik()==-1) return 0;
                bylaKalibracja=true;
                break;
            }
            case 's':
            {
                if(!bylaKalibracja || klawiatura_system()==-1 ) return 0;
                break;
            }
            case 'w':
            {
                if(model=='E') if(!bylaKalibracja || klawiatura_podglad()==-1) return 0;
                else if(modT.klawiatura_podglad(capture)==-1) return 0;
                    break;
            }
            case 'p':
            {
                cout<<"Podaj bezwzgledna sciezke do zapisu"<<endl;
                scanf("%s",sciezk);
                if(!bylaKalibracja || klawiatura_dopliku(sciezk)==-1) return 0;
                break;
            }
            case 'f':
            {
                cout<<"Podaj bezwzgledna sciezke do filmu"<<endl;
                scanf("%s",sciezk);
                if(model=='T')
                {
                    if(modT.klawiatura_zfilmu(sciezk)==-1) return 0;
                }
                else if(!bylaKalibracja || klawiatura_zfilmu(sciezk)==-1) return 0;
                break;
            }
            case 'm':
            {
                if(model=='E') model='T';
                else model='E';
                break;
            }

        }
    }while(option!='q');

///Koniec
    destroyAllWindows();
    cout << "Wychodze" << endl;
    return 0;
}

