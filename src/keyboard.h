#ifndef KEYBOARD_H
#define KEYBOARD_H
#include<opencv2/opencv.hpp>//bardzo ogolna biblioteka na koncu zmienic
#include <iostream>
struct key{
char key;
int x,y;
int width,height;
};
class keyboard{
public:
keyboard();
private:
std::vector<key> *klawisze;
std::vector<cv::Point> * markers;
public:
char getKey(int x, int y);
void setKeyboard(std::vector<cv::Point> * _markers);

};
#endif
