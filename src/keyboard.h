#ifndef KEYBOARD_H
#define KEYBOARD_H
#include<opencv2/opencv.hpp>//bardzo ogolna biblioteka na koncu zmienic
#include <iostream>
#include "enums.h"
using namespace std;
using namespace cv;
struct key{
    key(char _key,float _x,float _y,float _width,float _height);
char character;
float x,y;
float width,height;
///
Point2i vertex[4];
};
class keyboard{
public:
keyboard(float _widthReal,float _heightReal,int opcja=KB_COLOR);

float widthReal,heightReal;//w milimetrach
private:
std::vector<key> *klawisze;
std::vector<cv::Point> * markers;
public:
char getKey(int x, int y);
void setKeyboard(std::vector<cv::Point> * _markers);
void drawKeyBoard(cv::Mat &image);
void translateKeyboardCords(float markerSize);
char getKlawisz(Point2i palecPoint, Point2i cienPoint,float minimalDist);
void setCameraCord(int &x,int &y);
};
#endif
