#include "keyboard.h"

key::key(char _key,int _x,int _y,int _width,int _height){
character =_key;
x=_x;
y=_y;
width=_width;
height=_height;
}

void keyboard::setKeyboard(std::vector<cv::Point> * _markers){
markers=_markers;
}
keyboard::keyboard(int _widthReal,int _heightReal){
widthReal=_widthReal;
heightReal=_heightReal;
klawisze=new std::vector<key>();

klawisze->push_back(key('q',0,0,90,55));
klawisze->push_back(key('w',90,0,90,55));
klawisze->push_back(key('e',0,55,90,55));
klawisze->push_back(key('r',90,55,90,55));
}

void keyboard::drawKeyBoard(cv::Mat &image,Mat &templateImage){
cv::line(image, markers->at(0), markers->at(1), cv::Scalar(255,0,0), 2, CV_AA); // 1 pixel thick, CV_AA == Anti-aliased flag
cv::line(image, markers->at(1), markers->at(3), cv::Scalar(255,0,0), 2, CV_AA); // 1 pixel thick, CV_AA == Anti-aliased flag
cv::line(image, markers->at(3), markers->at(2), cv::Scalar(255,0,0), 2, CV_AA); // 1 pixel thick, CV_AA == Anti-aliased flag
cv::line(image, markers->at(2), markers->at(0), cv::Scalar(255,0,0), 2, CV_AA); // 1 pixel thick, CV_AA == Anti-aliased flag
///
Point shiftPoint=Point (markers->at(0).x+templateImage.rows/2,markers->at(0).y+templateImage.cols/2);
//Point shiftPointEnd=Point (markers->at(0).x,markers->at(0).y);

for (int i=0;i<klawisze->size();i++){
 rectangle( image, Point(klawisze->at(i).x,klawisze->at(i).y)+shiftPoint, Point( klawisze->at(i).x+klawisze->at(i).width, klawisze->at(i).y+klawisze->at(i).height)+shiftPoint, cv::Scalar(50,255,0), 2, 8, 0 );
}
//
}
void keyboard::translateKeyboardCords(){
float xCof=(markers->at(1).x-markers->at(0).x)/(float)widthReal;
float yCof=(markers->at(2).y-markers->at(0).y)/(float)heightReal;
cout<<xCof<<" - "<<yCof<<endl;
for (int i=0;i<klawisze->size();i++){
    klawisze->at(i).x*=   xCof;
    klawisze->at(i).width*=   xCof;
    klawisze->at(i).y*=   yCof;
    klawisze->at(i).height*=   yCof;

}
}
