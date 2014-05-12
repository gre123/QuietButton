#include "keyboard.h"

key::key(char _key,int _x,int _y,int _width,int _height){
character =_key;
x=_x;
y=_y;
width=_width;
height=_height;
//
vertex[0].x=x;
vertex[0].y=y;
vertex[1].x=x+width;
vertex[1].y=y;
vertex[2].x=x;
vertex[2].y=y+height;
vertex[3].x=x+width;
vertex[3].y=y+height;

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
cv::line(image, markers->at(0), markers->at(1), cv::Scalar(255,0,0), 2, CV_AA);
cv::line(image, markers->at(1), markers->at(3), cv::Scalar(255,0,0), 2, CV_AA);
cv::line(image, markers->at(3), markers->at(2), cv::Scalar(255,0,0), 2, CV_AA);
cv::line(image, markers->at(2), markers->at(0), cv::Scalar(255,0,0), 2, CV_AA);
///
Point shiftPoint=Point (markers->at(0).x+templateImage.rows/2,markers->at(0).y+templateImage.cols/2);

for (int i=0;i<klawisze->size();i++){
 rectangle( image, Point(klawisze->at(i).x,klawisze->at(i).y)+shiftPoint, Point( klawisze->at(i).x+klawisze->at(i).width, klawisze->at(i).y+klawisze->at(i).height)+shiftPoint, cv::Scalar(50,255,0), 2, 8, 0 );
 //cv::line(image, klawisze->at(i).vertex[0], klawisze->at(i).vertex[1], cv::Scalar(255,255,0), 2, CV_AA);
// cv::line(image, klawisze->at(i).vertex[0], klawisze->at(i).vertex[1], cv::Scalar(255,0,0), 2, CV_AA);

}
//
}
void keyboard::translateKeyboardCords(){

float xCof=(markers->at(1).x-markers->at(0).x)/(float)widthReal;
float yCof=(markers->at(2).y-markers->at(0).y)/(float)heightReal;
float xCof1=(markers->at(3).x-markers->at(2).x)/(float)widthReal;
float yCof1=(markers->at(3).y-markers->at(1).y)/(float)heightReal;

float heightShift=markers->at(1).y-markers->at(0).y;
float widthShift=markers->at(2).x-markers->at(0).x;

cout<<xCof<<" - "<<yCof<<endl;
cout<<widthShift<<" - "<<heightShift<<endl;

for (int i=0;i<klawisze->size();i++){
    klawisze->at(i).x*=   xCof;
    klawisze->at(i).width*=   xCof;
    klawisze->at(i).y*=   yCof;
    klawisze->at(i).height*=   yCof;
    ///

    for(int j=0;j<4;j++){
    setCameraCord(klawisze->at(i).vertex[j].x,klawisze->at(i).vertex[j].y);
    }
    ///

}
}

void keyboard::setCameraCord(int &x,int &y){
float xCof=(markers->at(1).x-markers->at(0).x)/(float)widthReal;
float yCof=(markers->at(2).y-markers->at(0).y)/(float)heightReal;
float xCof1=(markers->at(3).x-markers->at(2).x)/(float)widthReal;
float yCof1=(markers->at(3).y-markers->at(1).y)/(float)heightReal;

float heightShift=markers->at(1).y-markers->at(0).y;
float widthShift=markers->at(2).x-markers->at(0).x;
int tx=x;
int ty=y;
x=(x*(xCof*(ty/heightReal)+xCof1*(heightReal-ty)/heightReal))+(ty/heightReal)*markers->at(0).x+(heightReal-ty)/heightReal*markers->at(2).x;
y=(y*(yCof*(tx/widthReal)+yCof1*(widthReal-tx)/widthReal))+(tx/widthReal)*markers->at(0).y+(widthReal-tx)/widthReal*markers->at(1).y;
cout<<x<<"###"<<y<<endl;
}
char keyboard::getKlawisz(Point2i palecPoint, Point2i cienPoint){
int distance=(palecPoint.x-cienPoint.x)*(palecPoint.x-cienPoint.x)+(palecPoint.y-cienPoint.y)*(palecPoint.y-cienPoint.y);
if (distance<1300){
    for(int i=0;i<klawisze->size();i++){
        if (klawisze->at(i).x<palecPoint.x && klawisze->at(i).y<palecPoint.y
            &&klawisze->at(i).width+klawisze->at(i).x>palecPoint.x && klawisze->at(i).height+klawisze->at(i).y<palecPoint.y){
            return klawisze->at(i).character;
            }
    }
    return 0;

}else{return 0;}

}
