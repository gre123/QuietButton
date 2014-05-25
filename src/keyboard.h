#ifndef KEYBOARD_H
#define KEYBOARD_H
#include<opencv2/opencv.hpp>//bardzo ogolna biblioteka na koncu zmienic
#include <iostream>
using namespace std;
using namespace cv;
struct key{
    key(char _key,int _x,int _y,int _width,int _height);
char character;
int x,y;
int width,height;
///
Point2i vertex[4];
};
class keyboard{
public:
keyboard(int _widthReal,int _heightReal);
int widthReal,heightReal;//w milimetrach
private:
std::vector<key> *klawisze;
std::vector<cv::Point> * markers;
public:
char getKey(int x, int y);
void setKeyboard(std::vector<cv::Point> * _markers);
void drawKeyBoard(cv::Mat &image);
void translateKeyboardCords(int markerSize);
void translateKeyboardCordsElp(int markerSize);
char getKlawisz(Point2i palecPoint, Point2i cienPoint,int minimalDist);
void setCameraCord(int &x,int &y);
};
#endif
