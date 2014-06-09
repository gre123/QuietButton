#ifndef MODELE_H
#define MODELE_H

#include "functions.h"

#define WINVER 0x0500   //
#include <windows.h>    //do klawiatury
#include <conio.h>

class modelE
{
    public:
        VideoCapture captE1;
        INPUT ip;
        keyboard *klawiatura;
        vector<Vec3f> circles;
        vector<Point> brzegi;
        Mat maska,reka,frame,tlo,cien,polaczone,ycrcb;
        Mat channel[3];
        Mat tym[3];
        int a=115;
        int b=255;
        int c=100;
        int d=120;
        int e=146;
        int f=220;
        int u1=150;
        int u2=100;
        int ta=90;
        int tb=230;
        int tc=110;
        int td=240;
        int ymin=0;
        int ymax=255;
        int levelBin=10;
        int dist_req=1200;
        char key;

        modelE();
        virtual ~modelE();
        int ustawDomyslne(VideoCapture cap);
        int ustawTlo();
        int ustawReke();
        int ustawCien();
        int ustawKlik();
        Mat detekcja(Mat frame,char &znak);

    protected:
        char *nazwaokna;
        char *nazwaokna2;
        char *nazwaokna3;
        char *nazwaokna4;
        char *nazwaokna5;
    private:
};

#endif // MODELE_H
