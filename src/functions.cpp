#include "functions.h"
#define PI 3.14
extern int a;
extern int b;
extern int c;
extern int d;
extern int e;
extern int f;
/**
 * Rotate an image
 */
void rotate(Mat& src, double angle, Mat& dst){//obr
    int len = std::max(src.cols, src.rows);
    cv::Point2f pt(len/2., len/2.);
    cv::Mat r = cv::getRotationMatrix2D(pt, angle, 1.0);
    cv::warpAffine(src, dst, r, cv::Size(len, len));
}
/**
 * @function MatchingMethod
 * @brief Trackbar callback
 */
vector<Point>* matchingMethod(int match_method,int optionOfDisplay,Mat &sourceImage,Mat &templateImage ,Mat &outImage){//zmienic zeby nie przekazywac przez wartosc
  vector<Point> *markers=new vector<Point>();
  /// Source image to display
  Mat resultImage;
  Mat imageToDisplay;
  sourceImage.copyTo( imageToDisplay );

  /// Do the Matching and Normalize
  matchTemplate(sourceImage,templateImage,resultImage,match_method);
int q=0;
 while(q<4){
  /// Localizing the best match with minMaxLoc
  double minVal; double maxVal; Point minLoc; Point maxLoc;
  Point matchLoc;

  minMaxLoc(resultImage,&minVal,&maxVal,&minLoc,&maxLoc);
float pixValue;
  /// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
  if(match_method  == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED ){
      matchLoc = minLoc;
      pixValue=1;
      if(minVal>0.25){break;}
  }else{matchLoc = maxLoc;pixValue=0;if(maxVal<0.75){break;}}
//cout<<minVal<<" "<<maxVal<<endl;
    for (int i = 0; i < resultImage.cols; i++){
      for (int j = 0; j < resultImage.rows; j++){
            if((matchLoc.x-templateImage.cols/2<i) && (matchLoc.x+templateImage.cols/2>i) && (matchLoc.y-templateImage.rows/2<j) && (matchLoc.y+templateImage.rows/2>j)){
            resultImage.at<float>(j,i)=pixValue;}
      }
    }
  q++;
  rectangle( imageToDisplay, matchLoc, Point( matchLoc.x + templateImage.cols , matchLoc.y + templateImage.rows ), Scalar::all(0), 2, 8, 0 );
  markers->push_back(Point( matchLoc.x + templateImage.cols/2 , matchLoc.y + templateImage.rows/2 ));
}

  if (optionOfDisplay==0){
//    imshow( image_window, imageToDisplay );
   // return imageToDisplay;
   outImage=imageToDisplay;
  }else{
   // imshow( result_window, result );
   // return resultImage;
   outImage=resultImage;
  }
  return markers;
}
void sortMarkers(vector<Point>* markers){
vector<Point>* leftMarkers= new vector<Point>();
vector<Point>* rightMarkers= new vector<Point>();
//vector<Point>* resultMarkers= new vector<Point>();
    int findedMarker=0;

    int cordx=9999;
    ///
    for(int i=0;i<markers->size();i++){
        if (markers->at(i).x<cordx){cordx=markers->at(i).x;findedMarker=i;}
    }

    leftMarkers->push_back(markers->at(findedMarker));
    markers->erase(markers->begin()+findedMarker);

    cordx=9999;findedMarker=0;
    for(int i=0;i<markers->size();i++){
        if (markers->at(i).x<cordx){cordx=markers->at(i).x;findedMarker=i;}
    }
    leftMarkers->push_back(markers->at(findedMarker));
    markers->erase(markers->begin()+findedMarker);
    ///
    rightMarkers->push_back(markers->at(0));
    rightMarkers->push_back(markers->at(1));
    markers->clear();
    ///

    int cordy=9999;
    findedMarker=0;
    for(int i=0;i<leftMarkers->size();i++){
        if (leftMarkers->at(i).y<cordy){cordy=leftMarkers->at(i).y;findedMarker=i;}
    }markers->push_back(leftMarkers->at(findedMarker));
    leftMarkers->erase(leftMarkers->begin()+findedMarker);
    ///
    cordy=9999;
    findedMarker=0;
    for(int i=0;i<rightMarkers->size();i++){
        if (rightMarkers->at(i).y<cordy){cordy=rightMarkers->at(i).y;findedMarker=i;}
    }markers->push_back(rightMarkers->at(findedMarker));
    rightMarkers->erase(rightMarkers->begin()+findedMarker);
    ///
    markers->push_back(leftMarkers->at(0));
    markers->push_back(rightMarkers->at(0));

    ///
    for(int i=0;i<markers->size();i++){
       cout<< markers->at(i).x<<" - "<<markers->at(i).y<<endl;
    }
    ///
}
void sortCircles(vector<Vec3f>* markers){
vector<Vec3f>* leftMarkers= new vector<Vec3f>();
vector<Vec3f>* rightMarkers= new vector<Vec3f>();
    int findedMarker=0; int cordx=9999;
    ///
    for(int i=0;i<markers->size();i++){
        if (markers->at(i)[0]<cordx){cordx=markers->at(i)[0];findedMarker=i;}
    }

    leftMarkers->push_back(markers->at(findedMarker));
    markers->erase(markers->begin()+findedMarker);

    cordx=9999;findedMarker=0;
    for(int i=0;i<markers->size();i++){
        if (markers->at(i)[0]<cordx){cordx=markers->at(i)[0];findedMarker=i;}
    }
    leftMarkers->push_back(markers->at(findedMarker));
    markers->erase(markers->begin()+findedMarker);
    ///
    rightMarkers->push_back(markers->at(0));
    rightMarkers->push_back(markers->at(1));
    markers->clear();
    ///
    int cordy=9999;
    findedMarker=0;
    for(int i=0;i<leftMarkers->size();i++){
        if (leftMarkers->at(i)[1]<cordy){cordy=leftMarkers->at(i)[1];findedMarker=i;}
    }markers->push_back(leftMarkers->at(findedMarker));
    leftMarkers->erase(leftMarkers->begin()+findedMarker);
    ///
    cordy=9999;
    findedMarker=0;
    for(int i=0;i<rightMarkers->size();i++){
        if (rightMarkers->at(i)[1]<cordy){cordy=rightMarkers->at(i)[1];findedMarker=i;}
    }markers->push_back(rightMarkers->at(findedMarker));
    rightMarkers->erase(rightMarkers->begin()+findedMarker);
    ///
    markers->push_back(leftMarkers->at(0));
    markers->push_back(rightMarkers->at(0));
    ///
    cout << "powinny by poukladane : lg, pg, ld, pd"<<endl;
    for(int i=0;i<markers->size();i++){
       cout<< markers->at(i)[0]<<" - "<<markers->at(i)[1]<<endl;
    }
}
Point2i *peakDetection(Mat &obr){
    Mat pom;
    RNG rng(12345);
    for(int j=0;j<obr.rows;j++){
        for(int i=0;i<obr.cols;i++){
            if((int)obr.at<uchar>(j,i)==255){
                circle(obr,Point2i(i,j),4,Scalar( rng.uniform(120, 255), rng.uniform(0,255), rng.uniform(0,255) ),-1,8,0);
                return  new Point2i(i,j);
            }
        }
    }
    return new Point2i(0,0);
}
void cien_palec(Mat obr,Mat &tlo,Mat &wynik,Mat &wynik2,int Cb1,int Cb2,int Cr1,int Cr2,int thresLevel){
    Mat difference,CbInRange,CrInRange,CbAndCR,binaryDifference,w_ycbcr,w_gray;
    Mat kanaly[3];
    Mat dlon,cien;
    int morphSize=2;
    Mat element = getStructuringElement(  MORPH_ELLIPSE, Size( 2*morphSize + 1, 2*morphSize+1 ),Point( morphSize,morphSize ) );

    absdiff(tlo,obr,difference);
    cvtColor(difference,w_gray,CV_RGB2GRAY);
    threshold(w_gray,binaryDifference,thresLevel,255,THRESH_BINARY);

    erode(binaryDifference,binaryDifference,element);

    cvtColor(obr,w_ycbcr,CV_RGB2YCrCb);
    split(w_ycbcr,kanaly);
    inRange(kanaly[1],Cb1,Cb2,CbInRange);
    inRange(kanaly[2],Cr1,Cb2,CrInRange);

    bitwise_and(CbInRange,CrInRange,CbAndCR);

    CbAndCR.copyTo(dlon);
    erode(dlon,dlon,element);
    dlon.copyTo(wynik);

    absdiff(binaryDifference,CbAndCR,cien);
    dilate(cien,cien,element);
    cien.copyTo(wynik2);
}
cv::Mat shiftFrame(Mat &frame, int horizontalShift, int verticalShift){//obecnie nieuzywana
    //create a same sized temporary Mat with all the pixels flagged as invalid (-1)
    cv::Mat temp = cv::Mat::zeros(frame.size(), frame.type());
    int startHorizontal=0;
    int startVertical=0;
    int startCopyToHorizontal=0;
    int startCopyToVertical=0;
    int endHorizontal;//=frame.cols;
    int endVertical;//=frame.rows;
    int endCopyToHorizontal;//=frame.cols;
    int endCopyToVertical;//=frame.rows;

    if(horizontalShift<0){
        startHorizontal=-horizontalShift;
        endHorizontal=frame.cols;
        endCopyToHorizontal=endHorizontal+horizontalShift;
        startCopyToHorizontal=0;
    }else{
        startHorizontal=0;
        endHorizontal=frame.cols-horizontalShift;
        endCopyToHorizontal=frame.cols;
        startCopyToHorizontal=horizontalShift;
    }

    if(verticalShift<0){
        startVertical=-verticalShift;
        endVertical=frame.rows;
        endCopyToVertical=endVertical+verticalShift;
        startCopyToVertical=0;
    }else{
        startVertical=0;
        endVertical=frame.rows-verticalShift;
        endCopyToVertical=frame.rows;
        startCopyToVertical=verticalShift;
    }
    frame(Rect(Point(startHorizontal, startVertical), Point(endHorizontal, endVertical))).copyTo(temp(Rect(Point(startCopyToHorizontal, startCopyToVertical), Point(endCopyToHorizontal, endCopyToVertical))));

    return temp;
}
vector<Point> * findKeyboard(Mat &frame,Mat &backgroundFrame,Mat &templateImage){
  Mat frameGray;
  Mat result;
  cvtColor( frame, frameGray, CV_RGB2GRAY );
  adaptiveThreshold(frameGray, frameGray,240,CV_ADAPTIVE_THRESH_MEAN_C, THRESH_BINARY,75,10);
  vector<Point> *markers;
  markers=matchingMethod(4,1,frameGray,templateImage,result);
  if (markers->size()==4){frame.copyTo(backgroundFrame);return markers;}
  return 0;
}
Mat findBackGround(VideoCapture &capture,keyboard *klawiatura,Mat &templateImage){
Mat backgroundFrame;
Mat frame;

while(capture.read(frame)){
    Mat result;
    vector<Point> *markers;

    markers=findKeyboard(frame,backgroundFrame,templateImage);
    if (markers!=0 && markers->size()==4){
        sortMarkers(markers);
        klawiatura->setKeyboard(markers);
        return backgroundFrame;
    }
}
return backgroundFrame;
}
///ma znale�c tlo i 4 kolka
vector<Vec3f> tloznaczniki(VideoCapture &capture,Mat *tlo){
	Mat channel[3];
	Mat frame;
	vector<Vec3f> circles;

	while(capture.read(frame)){
		split(frame, channel);
		HoughCircles( channel[0], circles, CV_HOUGH_GRADIENT, 1, channel[0].rows/5, 200, 30, 0, 0 );
		if (circles.size()==4){
			sortCircles(&circles);
			break;
		}
	}
	*tlo=frame;
	return circles;
}
///(x,y,promien) -> (x,y)
vector<Point> vec3fToPoint(vector<Vec3f> vec){
    int vector_size = vec.size();
    vector<Point> wynik;
    for( int i=0; i<vector_size; i++ ){
        wynik.push_back(Point(vec[i][0], vec[i][1]));
    }
    return wynik;
}

void myszkaCallback(int event, int x, int y, int flags, void* kolka){
    if  ( event == EVENT_LBUTTONDOWN ){
        vector<Vec3f> *circles;
        circles = (vector<Vec3f>*) kolka;
        cout<< "Bede dodawal kolko o wspolrzednych: " << x << " ; " << y <<endl;
        //Vec3f *tym = new Vec3f((float) x, (float) y, 10);
        (*circles).push_back( Vec3f((float) x, (float) y, 10));
    }

}

char kolKlikniecie(Point2i *r, Point2i *c, Point *lg, Point *pg, Point *ld,int distance_req){
    int distance=(r->x-c->x)*(r->x-c->x)+(r->y-c->y)*(r->y-c->y);
    if (distance<distance_req){ //czyli, ze jest klikniecie
        float klpoz, klpion;
        klpion = (ld->y - lg->y)/5;
        klpoz = (pg->x - lg->x)/11;
        Point kwz = Point(r->x - lg->x + klpoz/2, r->y - lg->y + klpion/2); //kwz - pozycja klawisza wzgledem srodka lewego gornego kolka
        switch( (int) (kwz.y/klpion) ){ //najpierw po wierszach
        case 0:
            //poza klawiatura (za wysoko)
            return '+';
        case 1:
            switch( (int) (kwz.x/klpoz) ){
            case 0:
                return '<';//za bardzo na lewo
            case 1:
                return 'q';
            case 2:
                return 'w';
            case 3:
                return 't';
            case 4:
                return 'r';
            case 5:
                return 't';
            case 6:
                return 'y';
            case 7:
                return 'u';
            case 8:
                return 'i';
            case 9:
                return 'o';
            case 10:
                return 'p';
            default:
                return '>'; //za bardzo na prawo
            }
        break;
        case 2:
            switch( (int) (kwz.x/klpoz) ){
            case 0:
                return '<';//za bardzo na lewo
            case 1:
                return 'a';
            case 2:
                return 's';
            case 3:
                return 'd';
            case 4:
                return 'f';
            case 5:
                return 'g';
            case 6:
                return 'h';
            case 7:
                return 'j';
            case 8:
                return 'k';
            case 9:
                return 'l';
            case 10:
                return ':';
            default:
                return '>'; //za bardzo na prawo
            }
        break;
        case 3:
            switch( (int) (kwz.x/klpoz) ){
            case 0:
                return '<';//za bardzo na lewo
            case 1:
                return 'z';
            case 2:
                return 'x';
            case 3:
                return 'c';
            case 4:
                return 'v';
            case 5:
                return 'b';
            case 6:
                return 'n';
            case 7:
                return 'm';
            case 8:
                return '?';
            case 9:
                return 13;  //13 = ENTER
            case 10:
                return 13;
            default:
                return '>'; //za bardzo na prawo
            }
        break;
        case 4:
            switch( (int) (kwz.x/klpoz) ){
            case 0:
                return '<';//za bardzo na lewo
            case 1:
                return '^';
            case 2:
                return 32;
            case 3:
                return 32;
            case 4:
                return 32;
            case 5:
                return 32;
            case 6:
                return 32;
            case 7:
                return 32;
            case 8:
                return 32;
            case 9:
                return 13;
            case 10:
                return 13;
            default:
                return '>'; //za bardzo na prawo
            }
        break;
        default:
            //poza klawiatura (za nisko)
            return '-';
        }
    }
return 0;
}
Point* bigestPeakDetection(Mat *obr){
    Mat pom;
    (*obr).copyTo(pom);
    int largest_area=0;
    //Rect bounding_rect;
    int largest_contour_index=0;
    vector<vector<Point> > contours;
    findContours( pom, contours,CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);
    for( int i = 0; i< contours.size(); i++ ){        // iterate through each contour.
        double a=contourArea( contours[i],false);       //  Find the area of contour
        if(a>largest_area){
            largest_area=a;
            largest_contour_index=i;                //Store the index of largest contour
            //bounding_rect=boundingRect(contours[i]); // Find the bounding rectangle for biggest contour
        }
    }
    if (largest_area<100){return new Point2i(0,0);}
    //czyli mam contours[largest_contour_index] - kontur palca, teraz najwyzszy punkt
    //mozna by to przeniesc do odddzielnej funkcji
    int hpx=pom.size().width, hpy=pom.size().height;
    if (contours.size()>0){
        int highest_point_index=0;
        for( int i = 0; i< (contours[largest_contour_index]).size(); i++ ){
            if((contours[largest_contour_index][i]).y<hpy){
                hpx=(contours[largest_contour_index][i]).x;
                hpy=(contours[largest_contour_index][i]).y;
            }
        }
        drawContours(*obr, contours,largest_contour_index, Scalar(255), 3, 0 );
    }
    return new Point2i(hpx,hpy);
}

