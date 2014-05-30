#ifndef MODELT_H
#define MODELT_H

#include "functions.h"

#define WINVER 0x0500   //
#include <windows.h>    //do klawiatury
#include <conio.h>

class modelT
{
    public:
        int a=115;
        int b=255;
        int e=100;
        int f=120;
        int c=146;
        int d=220;
        VideoCapture capt1;
        int dist_reqT=35;
        keyboard *klawiatura;
        INPUT ip;

        Mat frame,frame2,frameGray,result,background,tempImg,dlon,cien;
        modelT();
        virtual ~modelT();
        int ustawRekeT();
        int ustawKlikT();
        Mat detekcjaT(Mat frame,char &znak);
};

#endif // MODELT_H
