#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include<opencv2/opencv.hpp>//bardzo ogolna biblioteka na koncu zmienic
#include <iostream>
#include <math.h>
#include "enums.h"
using namespace std;
using namespace cv;


void rotate(Mat& src, double angle, Mat& dst);
vector<Point>* matchingMethod(int match_method, int optionOfDisplay,Mat &sourceImage,Mat &templateImage,Mat &outImage);
void levelOutImage(vector<Point>* markers,Mat &sourceImage);
int findMarker(vector<Point>* markers,int whichMarker);
void cien(Mat &obr,Mat tlo,int p);
void odejm(Mat &obr,Mat &tlo,int p,int q);
Mat shiftFrame(Mat &frame, int horizontalShift, int verticalShift);
void processVideo(char* videoFilename);
#endif
