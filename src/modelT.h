#ifndef MODELT_H
#define MODELT_H

#include "functions.h"

#define WINVER 0x0500   //
#include <windows.h>    //do klawiatury


class modelT
{
    public:
        int a=115;
        int b=255;
        int c=100;
        int d=120;
        int e=146;
        int f=220;

        Mat frame,frame2,frameGray,result,background,tempImg,dlon,cien;
        modelT();
        virtual ~modelT();
        int klawiatura_zfilmu(string sciezka);
        int klawiatura_podglad(VideoCapture capture);
};

#endif // MODELT_H
