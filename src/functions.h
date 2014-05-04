#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include<opencv2/opencv.hpp>//bardzo ogolna biblioteka na koncu zmienic
#include <iostream>
#include <math.h>
#include "enums.h"
#include "keyboard.h"
using namespace std;
using namespace cv;


void rotate(Mat& src, double angle, Mat& dst);
vector<Point>* matchingMethod(int match_method, int optionOfDisplay,Mat &sourceImage,Mat &templateImage,Mat &outImage);
void levelOutImage(vector<Point>* markers,Mat &sourceImage);
int findMarker(vector<Point>* markers,int whichMarker);
<<<<<<< .mine
void sortMarkers(vector<Point>* markers);
=======
>>>>>>> .r8
void cien(Mat &obr,Mat tlo,int p);
<<<<<<< .mine
void odejm(Mat &obr,Mat &tlo,int p,int q);
Mat shiftFrame(Mat &frame, int horizontalShift, int verticalShift);
void processVideo(char* videoFilename);
vector<Point> * findKeyboard(Mat &frame,Mat &backgroundFrame,Mat &templateImage);
Mat findBackGround(VideoCapture &capture,keyboard * klawiatura);
=======
void odejm(Mat &obr,Mat &tlo,int p,int q);
Mat shiftFrame(Mat &frame, int horizontalShift, int verticalShift);
void processVideo(char* videoFilename);
>>>>>>> .r8
#endif
