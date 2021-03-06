#ifndef FUNCTIONS_H
#define FUNCTIONS_H
//#include<opencv2/opencv.hpp>//bardzo ogolna biblioteka na koncu zmienic
//#include <iostream>
#include <math.h>
#include "keyboard.h"

#include <stdlib.h>
using namespace std;
using namespace cv;

static int dist;

void rotate(Mat& src, double angle, Mat& dst);
vector<Point>* matchingMethod(int match_method, int optionOfDisplay,Mat &sourceImage,Mat &templateImage,Mat &outImage);
void levelOutImage(vector<Point>* markers,Mat &sourceImage);
int findMarker(vector<Point>* markers,int whichMarker);
void sortMarkers(vector<Point>* markers);
void sortCircles(vector<Vec3f>* markers);
Point2i *peakDetection(Mat &obr);
void cien_palec(Mat obr,Mat &tlo,Mat &wynik,Mat &wynik2,int Cb1,int Cb2,int Cr1,int Cr2,int thresLevel);
Mat shiftFrame(Mat &frame, int horizontalShift, int verticalShift);
vector<Point> * findKeyboard(Mat &frame,Mat &backgroundFrame,Mat &templateImage);
Mat findBackGround(VideoCapture &capture,keyboard *klawiatura,Mat &templateImage);
vector<Vec3f> tloznaczniki(VideoCapture &capture,Mat *tlo);
vector<Point> vec3fToPoint(vector<Vec3f> vec);
void myszkaCallback(int event, int x, int y, int flags, void* kolka);
char kolKlikniecie(Point2i *r, Point2i *c, Point *lg, Point *pg, Point *ld,int distance_req);
Point* bigestPeakDetection(Mat *obr);


#endif
