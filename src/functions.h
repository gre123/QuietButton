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
Mat Shift_Image_to_Right( Mat src_in, int num_pixels);
void ruch(Mat &obr,Mat poprz);
void odejm(Mat &obr,Mat tlo);
Mat shiftFrame(Mat frame, int horizontalShift, int verticalShift);
#endif
