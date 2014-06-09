#include "keyboard.h"

key::key(char _key,float _x,float _y,float _width,float _height){
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
keyboard::keyboard(float _widthReal,float _heightReal,int opcja){
widthReal=_widthReal;
heightReal=_heightReal;
klawisze=new std::vector<key>();
if (opcja==KB_COLOR){
klawisze->push_back(key('q',0,0,24,24));
klawisze->push_back(key('w',24,0,24,24));
klawisze->push_back(key('e',48,0,24,24));
klawisze->push_back(key('r',72,0,24,24));
klawisze->push_back(key('t',96,0,24,24));
klawisze->push_back(key('y',120,0,24,24));
klawisze->push_back(key('u',144,0,24,24));
klawisze->push_back(key('i',168,0,24,24));
klawisze->push_back(key('o',192,0,24,24));
klawisze->push_back(key('p',216,0,24,24));

klawisze->push_back(key('a',0,24,24,24));
klawisze->push_back(key('s',24,24,24,24));
klawisze->push_back(key('d',48,24,24,24));
klawisze->push_back(key('f',72,24,24,24));
klawisze->push_back(key('g',96,24,24,24));
klawisze->push_back(key('h',120,24,24,24));
klawisze->push_back(key('j',144,24,24,24));
klawisze->push_back(key('k',168,24,24,24));
klawisze->push_back(key('l',192,24,24,24));
klawisze->push_back(key(';',216,24,24,24));

klawisze->push_back(key('z',0,48,24,24));
klawisze->push_back(key('x',24,48,24,24));
klawisze->push_back(key('c',48,48,24,24));
klawisze->push_back(key('v',72,48,24,24));
klawisze->push_back(key('b',96,48,24,24));
klawisze->push_back(key('n',120,48,24,24));
klawisze->push_back(key('m',144,48,24,24));
klawisze->push_back(key('/',168,48,24,24));

klawisze->push_back(key((char)15,0,72,24,24));
klawisze->push_back(key((char)32,24,72,168,24));

klawisze->push_back(key((char)13,192,48,48,48));
}
else if(opcja==KB_WHITE){
        float defaultSize=23.5;
        float defaultSizeY=17;

int i=0;
klawisze->push_back(key('1',defaultSize*i++,0,defaultSize,defaultSizeY));
klawisze->push_back(key('2',defaultSize*i++,0,defaultSize,defaultSizeY));
klawisze->push_back(key('3',defaultSize*i++,0,defaultSize,defaultSizeY));
klawisze->push_back(key('4',defaultSize*i++,0,defaultSize,defaultSizeY));
klawisze->push_back(key('5',defaultSize*i++,0,defaultSize,defaultSizeY));
klawisze->push_back(key('6',defaultSize*i++,0,defaultSize,defaultSizeY));
klawisze->push_back(key('7',defaultSize*i++,0,defaultSize,defaultSizeY));
klawisze->push_back(key('8',defaultSize*i++,0,defaultSize,defaultSizeY));
klawisze->push_back(key('9',defaultSize*i++,0,defaultSize,defaultSizeY));
klawisze->push_back(key('0',defaultSize*i++,0,defaultSize,defaultSizeY));

i=0;
float prevSizeY=defaultSizeY;
defaultSizeY=defaultSize;

klawisze->push_back(key('q',defaultSize*i++,prevSizeY,defaultSize,defaultSizeY));
klawisze->push_back(key('w',defaultSize*i++,prevSizeY,defaultSize,defaultSizeY));
klawisze->push_back(key('e',defaultSize*i++,prevSizeY,defaultSize,defaultSizeY));
klawisze->push_back(key('r',defaultSize*i++,prevSizeY,defaultSize,defaultSizeY));
klawisze->push_back(key(KB_WHITE,defaultSize*i++,prevSizeY,defaultSize,defaultSizeY));
klawisze->push_back(key('y',defaultSize*i++,prevSizeY,defaultSize,defaultSizeY));
klawisze->push_back(key('u',defaultSize*i++,prevSizeY,defaultSize,defaultSizeY));
klawisze->push_back(key('i',defaultSize*i++,prevSizeY,defaultSize,defaultSizeY));
klawisze->push_back(key('o',defaultSize*i++,prevSizeY,defaultSize,defaultSizeY));
klawisze->push_back(key('p',defaultSize*i++,prevSizeY,defaultSize,defaultSizeY));

i=0;
float shiftSize=12;
prevSizeY=prevSizeY+defaultSizeY;
klawisze->push_back(key('a',shiftSize+defaultSize*i++,prevSizeY,defaultSize,defaultSizeY));
klawisze->push_back(key('s',shiftSize+defaultSize*i++,prevSizeY,defaultSize,defaultSizeY));
klawisze->push_back(key('d',shiftSize+defaultSize*i++,prevSizeY,defaultSize,defaultSizeY));
klawisze->push_back(key('f',shiftSize+defaultSize*i++,prevSizeY,defaultSize,defaultSizeY));
klawisze->push_back(key('g',shiftSize+defaultSize*i++,prevSizeY,defaultSize,defaultSizeY));
klawisze->push_back(key('h',shiftSize+defaultSize*i++,prevSizeY,defaultSize,defaultSizeY));
klawisze->push_back(key('j',shiftSize+defaultSize*i++,prevSizeY,defaultSize,defaultSizeY));
klawisze->push_back(key('k',shiftSize+defaultSize*i++,prevSizeY,defaultSize,defaultSizeY));
klawisze->push_back(key('l',shiftSize+defaultSize*i++,prevSizeY,defaultSize,defaultSizeY));
klawisze->push_back(key((char)13,shiftSize+defaultSize*i++,prevSizeY,shiftSize,defaultSizeY));

i=1;
prevSizeY=prevSizeY+defaultSizeY;
klawisze->push_back(key('z',shiftSize+defaultSize*i++,prevSizeY,defaultSize,defaultSizeY));
klawisze->push_back(key('x',shiftSize+defaultSize*i++,prevSizeY,defaultSize,defaultSizeY));
klawisze->push_back(key('c',shiftSize+defaultSize*i++,prevSizeY,defaultSize,defaultSizeY));
klawisze->push_back(key('v',shiftSize+defaultSize*i++,prevSizeY,defaultSize,defaultSizeY));
klawisze->push_back(key('b',shiftSize+defaultSize*i++,prevSizeY,defaultSize,defaultSizeY));
klawisze->push_back(key('n',shiftSize+defaultSize*i++,prevSizeY,defaultSize,defaultSizeY));
klawisze->push_back(key('m',shiftSize+defaultSize*i++,prevSizeY,defaultSize,defaultSizeY));
klawisze->push_back(key((char)13,shiftSize+defaultSize*i++,prevSizeY,defaultSize+shiftSize,defaultSizeY));

prevSizeY=prevSizeY+defaultSizeY;

klawisze->push_back(key((char)32,shiftSize+defaultSize*2,prevSizeY,defaultSize*5,defaultSizeY));
klawisze->push_back(key((char)8,shiftSize+defaultSize*7,prevSizeY,shiftSize+defaultSize*2,defaultSizeY));

}else{
klawisze->push_back(key('?',0,0,_widthReal,_heightReal));
}
}

void keyboard::drawKeyBoard(cv::Mat &image){
cv::line(image, markers->at(0), markers->at(1), cv::Scalar(255,0,0), 2, CV_AA);
cv::line(image, markers->at(1), markers->at(3), cv::Scalar(255,0,0), 2, CV_AA);
cv::line(image, markers->at(3), markers->at(2), cv::Scalar(255,0,0), 2, CV_AA);
cv::line(image, markers->at(2), markers->at(0), cv::Scalar(255,0,0), 2, CV_AA);
///
//Point shiftPoint=Point (markers->at(0).x+templateImage.rows/2,markers->at(0).y+templateImage.cols/2);
Point shiftPoint=Point (0,0);

for (int i=0;i<klawisze->size();i++){
 rectangle( image, Point(klawisze->at(i).x,klawisze->at(i).y)+shiftPoint, Point( klawisze->at(i).x+klawisze->at(i).width, klawisze->at(i).y+klawisze->at(i).height)+shiftPoint, cv::Scalar(50,255,0), 2, 8, 0 );
 //cv::line(image, klawisze->at(i).vertex[0], klawisze->at(i).vertex[1], cv::Scalar(255,255,0), 2, CV_AA);
// cv::line(image, klawisze->at(i).vertex[0], klawisze->at(i).vertex[1], cv::Scalar(255,0,0), 2, CV_AA);

}
//
}
void keyboard::translateKeyboardCords(float markerSize){
float xCof=(markers->at(1).x-markers->at(0).x)/(float)widthReal;
float yCof=(markers->at(2).y-markers->at(0).y)/(float)heightReal;
float xCof1=(markers->at(3).x-markers->at(2).x)/(float)widthReal;
float yCof1=(markers->at(3).y-markers->at(1).y)/(float)heightReal;

markerSize*=xCof;

Point shiftPoint=Point (markers->at(0).x+markerSize/2,markers->at(0).y+markerSize/2);

for (int i=0;i<klawisze->size();i++){
    klawisze->at(i).x= klawisze->at(i).x*  xCof+shiftPoint.x;
    klawisze->at(i).width=klawisze->at(i).width*   xCof;
    klawisze->at(i).y=klawisze->at(i).y*   yCof+shiftPoint.y;
    klawisze->at(i).height=klawisze->at(i).height*   yCof;
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
//cout<<x<<"###"<<y<<endl;
}
char keyboard::getKlawisz(Point2i palecPoint, Point2i cienPoint,float minimalDist=1200){
int distance=(palecPoint.x-cienPoint.x)*(palecPoint.x-cienPoint.x)+(palecPoint.y-cienPoint.y)*(palecPoint.y-cienPoint.y);

if (distance<minimalDist){

   // cout<<palecPoint.x<<"---"<<palecPoint.y<<endl;
    for(int i=0;i<klawisze->size();i++){

        if (klawisze->at(i).x<palecPoint.x && klawisze->at(i).y<palecPoint.y
            &&klawisze->at(i).width+klawisze->at(i).x>palecPoint.x && klawisze->at(i).height+klawisze->at(i).y>palecPoint.y){

            return klawisze->at(i).character;
            }
    }
    return 0;

}else{return 0;}

}
