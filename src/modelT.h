#ifndef MODELT_H
#define MODELT_H

#include "functions.h"

#define WINVER 0x0500   //
#include <windows.h>    //do klawiatury
#include <conio.h>

class modelT
{
    public:
        int a=75;
        int b=125;
        int e=100;
        int f=120;
        int c=130;
        int d=185;
        int levelThresh=30;
        VideoCapture capt1;
        int dist_reqT=35;
        keyboard *klawiatura;
        INPUT ip;
        char* mainWindowName = "Ustaw reke";
        char* cienWindowName = "Ustaw cien";

        Mat frame,frame2,frameGray,result,background,tempImg,dlon,cien,templateImage;
        modelT();
        virtual ~modelT();
        int ustawReke();
        int ustawKlik();
        int ustawCien();
        Mat detekcja(Mat frame,char &znak);
        void dopelnieniekonstruktora();
};

#endif // MODELT_H
