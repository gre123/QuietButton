//#include <iostream>
#include "modelT.h"
#include "modelE.h"
#define WINVER 0x0500   //
#include <windows.h>    //do klawiatury
#include <fstream>
#include <stdio.h>
using namespace std;

int a=115;
int b=255;
int c=100;
int d=120;
int e=146;
int f=220;



char nazwaokna4[] = "Podglad wynikow";
char key,option;
char model='E';
Mat frame;
VideoCapture capture(0);
INPUT ip;
bool bylaKalibracja=false;
bool bylaKalibracjaT=false;
char sciezk[50];
modelT modT;
modelE modE;


int klawiatura_podglad()
{
    Mat wynik;
    int licznik=0;
    cvNamedWindow(nazwaokna4, CV_WINDOW_AUTOSIZE); //Create window
    char znak;

    cout<<"Aby zakończyc : enter na okienku"<<endl;
    while(capture.read(frame)){
        std::ostringstream str ;
        str << "Nacisnieto: " ;

        if(model=='E'){
                if(bylaKalibracja) wynik=modE.detekcjaE(frame,znak);
                else return -1;
        }
        else{
                if(bylaKalibracjaT) wynik=modT.detekcjaT(frame,znak);
                else return -1;
        }

        if (znak!=0 && znak!='+' && znak!='-' && znak!='<' && znak!='>'){
        if(licznik==0 || licznik>=50)
        {
            str<<znak;
        }
        licznik++;
        }
        else licznik=0;
        putText(wynik, str.str(), cvPoint(30,30),
        FONT_HERSHEY_COMPLEX, 1, cvScalar(200,200,250), 1, CV_AA);
        imshow(nazwaokna4, wynik);
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
    Mat wynik;
    char znak;

    cout<<"Klawiatura na standard. aby wyjsc wcisnij enter"<<endl;
    while(capture.read(frame) && !kbhit()){

        if(model=='E'){
            if(bylaKalibracja) wynik=modE.detekcjaE(frame,znak);
            else return -1;
        }
        else{
            if(bylaKalibracjaT) wynik=modT.detekcjaT(frame,znak);
            else return -1;
        }

        if (znak!=0 && znak!='+' && znak!='-' && znak!='<' && znak!='>'){
            if(licznik==0 || licznik>=50)
                {
                    ip.ki.wVk = VkKeyScan(znak);        //wysyla przerwanie klawiatury
                    SendInput(1, &ip, sizeof(INPUT));   //nie dziala przytrzymanie klawisza
                }
                licznik++;
            }
            else licznik=0;
    }

    return 0;
}

int klawiatura_dopliku(char* sciezka)
{
    int licznik =0;
    fstream pl(sciezka,ios::out);
    if(!pl.good()){ return -1;}
    cvNamedWindow("DoPliku", CV_WINDOW_AUTOSIZE); //Create window
    Mat wynik;
    char znak;
    while(capture.read(frame)){
        std::ostringstream str ;
        str << "Nacisnieto: " ;
        if(model=='E'){
            if(bylaKalibracja) wynik=modE.detekcjaE(frame,znak);
            else return -1;
        }
        else{
            if(bylaKalibracjaT) wynik=modT.detekcjaT(frame,znak);
            else return -1;
        }
        if (znak!=0 && znak!='+' && znak!='-' && znak!='<' && znak!='>'){
                if(licznik==0 || licznik>=50)
                {
                    str<< znak;
                    pl<<znak;
                }
                licznik++;
            }
            else licznik=0;

          putText(wynik, str.str(), cvPoint(30,30),
            FONT_HERSHEY_COMPLEX, 1, cvScalar(200,200,250), 1, CV_AA);
        imshow("DoPliku", wynik);
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
    VideoCapture cap2(sciezka);
    if(!cap2.isOpened())
    {
        cout<<"Wystapil problem"<<endl;
        return -1;
    }
    cvNamedWindow("ZFilmu", CV_WINDOW_AUTOSIZE); //Create window
    Mat wynik;
    char znak;
    int licznik;

    while(cap2.read(frame)){
        std::ostringstream str ;
        str << "Nacisnieto: " ;

        if(model=='E'){
            if(bylaKalibracja) wynik=modE.detekcjaE(frame,znak);
            else{
                    destroyAllWindows();
                    return -1;
            }
        }
        else{
                if(bylaKalibracjaT) wynik=modT.detekcjaT(frame,znak);
                else{
                    destroyAllWindows();
                    return -1;
                }
        }

        if (znak!=0 && znak!='+' && znak!='-' && znak!='<' && znak!='>'){
                if(licznik==0 || licznik>=50)
                {
                    str<< znak;
                }
                licznik++;
            }
            else licznik=0;

          putText(wynik, str.str(), cvPoint(30,30),
            FONT_HERSHEY_COMPLEX, 1, cvScalar(200,200,250), 1, CV_AA);
        imshow("ZFilmu", wynik);
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

    destroyAllWindows();
    return 0;
}

int main(){

   ip.type = INPUT_KEYBOARD;   //
   ip.ki.wScan = 0;            //do symulowania klawiatury
   ip.ki.time = 0;             //
   ip.ki.dwExtraInfo = 0;      //
   ip.ki.dwFlags = 0; // 0 for key press
   if (!capture.isOpened()){
         cout << "Nie znalazlem kamery!" << endl;
         return -1;
    }
    capture.set(CV_CAP_PROP_FRAME_WIDTH, 800);
    capture.set(CV_CAP_PROP_FRAME_HEIGHT, 600);

///Menu
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
        cout<<"Kalibracja (k)"<<endl;
        cout<<"Odpal klawiature jako standard. (s)"<<endl;
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
                if(model=='E'){
                    ///czesc do wykrywania pozycji klawiatury
                    if(modE.ustawTloE()==-1) return 0;
                    ///teraz czesc do ustawiania parametrow modelu koloru skory
                    //destroyAllWindows();
                    if(modE.ustawRekeE()==-1) return 0;
                    ///Teraz czesc do ustawiania parametrow wykrywania cienia
                    if(modE.ustawCienE()==-1) return 0;

                    if(modE.ustawKlikE()==-1) return 0;
                    bylaKalibracja=true;
                }
                if(model=='T'){
                    if(modT.ustawRekeT()==-1) return 0;
                    if(modT.ustawKlikT()==-1) return 0;
                    bylaKalibracjaT=true;
                }
                break;
            }
            case 's':
            {
                if(klawiatura_system()==-1) {
                    cout<<"Wystąpil problem z ta opcja"<<endl;
                    return 0;
                }
                break;
            }
            case 'w':
            {
                if(klawiatura_podglad()==-1) {
                    cout<<"Wystąpil problem z ta opcja"<<endl;
                    return 0;
                }
                break;
            }
            case 'p':
            {
                cout<<"Podaj bezwzgledna sciezke do zapisu"<<endl;
                scanf("%s",sciezk);
                if(klawiatura_dopliku(sciezk)==-1){
                 cout<<"Nastapil problem z ta opcja"<<endl;
                 return 0;
                }
                break;
            }
            case 'f':
            {
                cout<<"Podaj bezwzgledna sciezke do filmu"<<endl;
                scanf("%s",sciezk);
                if(klawiatura_zfilmu(sciezk)==-1) {
                    cout<<"Nastapil blad w tej opcji"<<endl;
                   // return 0;
                }
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

