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
int model=KB_COLOR;
Mat frame;
VideoCapture capture(0);
INPUT ip;
bool bylaKalibracja=false;
bool bylaKalibracjaT=false;
char sciezk[50];
modelE md_kolorowy;
modelT md_bialy;

int klawiatura_dopliku(char* sciezka){
    int licznik =0;
    fstream pl(sciezka,ios::out);
    if(!pl.good()){ return -1;}
    cvNamedWindow("DoPliku", CV_WINDOW_AUTOSIZE); //Create window
    Mat wynik;
    char znak;
    while(capture.read(frame)){
        std::ostringstream str ;
        str << "Nacisnieto: " ;
        if(model==KB_COLOR){
            if(bylaKalibracja) wynik=md_kolorowy.detekcja(frame,znak);
            else return -1;
        }
        else{
            if(bylaKalibracjaT) wynik=md_bialy.detekcja(frame,znak);
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

int readFromCamera(int option,char* sciezka="video/out.txt"){
bool correctChar=false;
    Mat wynik;
    if (option==OP_PREVIEW){
        cvNamedWindow(nazwaokna4, CV_WINDOW_AUTOSIZE); //Create window
        cout<<"Aby zakończyc : enter na okienku"<<endl;
    }else if (option==OP_SYSTEM){
        cout<<"Klawiatura na standard. aby wyjsc wcisnij enter"<<endl;
    }else if (option==OP_FILE){
        fstream pl(sciezka,ios::out);
        if(!pl.good()){ return -1;}
        cvNamedWindow(nazwaokna4, CV_WINDOW_AUTOSIZE); //Create window
        cout<<"Zapis do pliku"<<endl;
    }

    int licznik=0;
    char znak;


    while(capture.read(frame)){
            correctChar=false;
        std::ostringstream str ;
        str << "Nacisnieto: " ;

        if(model==KB_COLOR){
                if(bylaKalibracja) wynik=md_kolorowy.detekcja(frame,znak);
                else return -1;
        }
        else{
                if(bylaKalibracjaT) wynik=md_bialy.detekcja(frame,znak);
                else return -1;
        }

        if (znak!=0 && znak!='+' && znak!='-' && znak!='<' && znak!='>'){
        if(licznik==0 || licznik>=50)
        {
            str<<znak;
            correctChar=true;
        }
        licznik++;
        }
        else licznik=0;

        if (option==OP_PREVIEW){
            putText(wynik, str.str(), cvPoint(30,30),
            FONT_HERSHEY_COMPLEX, 1, cvScalar(255,0,0), 1, CV_AA);
            imshow(nazwaokna4, wynik);
        }else if (option==OP_SYSTEM && correctChar){
            ip.ki.wVk = VkKeyScan(znak);        //wysyla przerwanie klawiatury
            SendInput(1, &ip, sizeof(INPUT));   //nie dziala przytrzymanie klawisza
        }else if (option==OP_FILE){
            putText(wynik, str.str(), cvPoint(30,30),
            FONT_HERSHEY_COMPLEX, 1, cvScalar(255,10,10), 1, CV_AA);
            imshow(nazwaokna4, wynik);
        }

        key = cvWaitKey(15);
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


int klawiatura_zfilmu(string sciezka){
    VideoCapture cap2(sciezka);
    if(!cap2.isOpened())
    {
        cout<<"Wystapil problemz otwieraniem pliku."<<endl;
        Sleep(1000);
        return -1;
    }
    if((model==KB_COLOR)&&(md_kolorowy.ustawDomyslne(cap2)==-1))
    {
                cout<<"Nastapil blad z ustawieniem domyslnych wartosci."<<endl;
                Sleep(1000);
                return -1;
    }
    if(model==KB_WHITE)
    {
                cout<<"Wejscie z pliku przeznaczone jest dla modelu kolorowego, ustaw go."<<endl;
                Sleep(1000);
                return -1;
    }
    cvNamedWindow("ZFilmu", CV_WINDOW_AUTOSIZE); //Create window
    Mat wynik;
    char znak;
    int licznik;



    while(cap2.read(frame)){
     std::ostringstream str ;
        str << "Nacisnieto: " ;

        if(model==KB_COLOR){

            wynik=md_kolorowy.detekcja(frame,znak);

        }
        else{
                 wynik=md_bialy.detekcja(frame,znak);

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
   if (!capture.isOpened()){cout << "Nie znalazlem kamery!" << endl;//return -1;
   }else{
        capture.set(CV_CAP_PROP_FRAME_WIDTH, 800);
        capture.set(CV_CAP_PROP_FRAME_HEIGHT, 600);
   }

///Menu
    do{
        //cout<<string(22, '\n');
        system("cls");
        cout<<"KLAWIATURA <<<<<<<<<<<<<"<<endl;

        cout<<"Model : "<<model<<endl<<endl;

        if(model==KB_COLOR){
        cout<<"Kalibracja (k)"<<endl;
        cout<<"Odpal klawiature jako standard. (s)"<<endl;
        cout<<"Odpal klawiature - podglad wyniku (w)"<<endl;
        cout<<"Odpal klawiature i zapisuj do pliku (p)"<<endl;
        cout<<"Zmiana modelu klawiatury (m)"<<endl;
        cout<<"Wczytaj znaki z filmu (f)"<<endl;
        cout<<"Wyjscie (q)"<<endl;
        }
        else if(model==KB_WHITE){
        cout<<"Kalibracja (k)"<<endl;
        cout<<"Odpal klawiature jako standard. (s)"<<endl;
        cout<<"Odpal klawiature - podglad wyniku (w)"<<endl;
        cout<<"Zmiana modelu klawiatury (m)"<<endl;
        cout<<"Wyjscie (q)"<<endl;
        }

        cin>>option;
        switch(option)
        {
            case 'k':
            {
                if(model==KB_COLOR){


                    ///czesc do wykrywania pozycji klawiatury
                    if(md_kolorowy.ustawTlo()==-1){
                        cout<<"Nastapil problem z ta opcja"<<endl;
                        break;
                    };
                    ///teraz czesc do ustawiania parametrow modelu koloru skory
                    //destroyAllWindows();
                    if(md_kolorowy.ustawReke()==-1){
                        cout<<"Nastapil problem z ta opcja"<<endl;
                        break;
                    };
                    ///Teraz czesc do ustawiania parametrow wykrywania cienia
                    if(md_kolorowy.ustawCien()==-1){
                        cout<<"Nastapil problem z ta opcja"<<endl;
                        break;
                    };

                    if(md_kolorowy.ustawKlik()==-1){
                        cout<<"Nastapil problem z ta opcja"<<endl;
                        break;
                    };
                    bylaKalibracja=true;
                }
                else if(model==KB_WHITE){

                    if(md_bialy.ustawReke()==-1){
                        cout<<"Nastapil problem z ta opcja"<<endl;
                        break;
                    };
                    if(md_bialy.ustawCien()==-1){
                        cout<<"Nastapil problem z ta opcja"<<endl;
                        break;
                    };
                    if(md_bialy.ustawKlik()==-1){
                        cout<<"Nastapil problem z ta opcja"<<endl;
                        break;
                    };
                    bylaKalibracjaT=true;
                }
                break;
            }
            case 's':
            {
                if(readFromCamera(OP_SYSTEM)==-1) {
                    cout<<"Wystąpil problem SYSTEM"<<endl;
                    return 0;
                }
                break;
            }
            case 'w':
            {
                if(readFromCamera(OP_PREVIEW)==-1) {
                    cout<<"Wystąpil problem PODGLAD"<<endl;
                    return 0;
                }
                break;
            }
            case 'p':
            {
                cout<<"Podaj sciezke do zapisu"<<endl;
                scanf("%s",sciezk);
                if(klawiatura_dopliku(sciezk)==-1){
                 cout<<"Nastapil problem z ta opcja"<<endl<<"Sprobuj wpisac poprawna sciezke"<<endl;
                 cin>>option;
                }
                break;
            }
            case 'f':
            {
                cout<<"Podaj bezwzgledna sciezke do filmu"<<endl;
                scanf("%s",sciezk);
                if(klawiatura_zfilmu(sciezk)==-1) {
                    cout<<"Nastapil blad w przetwarzaniu filmu."<<endl<<"Sprobuj wpisac poprawna sciezke"<<endl;
                    cin>>option;
                }
                break;
            }
            case 'm':
            {
                if(model==KB_COLOR) {
                    model=KB_WHITE;
                //    md_bialy.dopelnieniekonstruktora();
                    }

                else model=KB_COLOR;
                break;
            }
        }
    }while(option!='q');

    destroyAllWindows();
    cout << "Wychodze" << endl;
    return 0;
}
