#include "functions.h"
/**
 * Rotate an image
 */
void rotate(Mat& src, double angle, Mat& dst){
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

  /// Create the resultImage matrix
  int resultImage_cols =  sourceImage.cols;- templateImage.cols + 1;
  int resultImage_rows = sourceImage.rows - templateImage.rows + 1;

  resultImage.create(resultImage_cols,resultImage_rows,CV_8UC1 );

  /// Do the Matching and Normalize
  matchTemplate(sourceImage,templateImage,resultImage,match_method);
 // cv::threshold(resultImage, resultImage, 0.1, 1., 2);
  normalize(resultImage,resultImage,0,1,NORM_MINMAX,-1,Mat() );
//for(int q=0;q<4;q++){
int q=0;
 while(q<4){
  /// Localizing the best match with minMaxLoc
  double minVal; double maxVal; double extremum;Point minLoc; Point maxLoc;
  Point matchLoc;

  minMaxLoc(resultImage,&minVal,&maxVal,&minLoc,&maxLoc);
float pixValue;
  /// For SQDIFF and SQDIFF_NORMED, the best matches are lower values. For all the other methods, the higher the better
  if(match_method  == CV_TM_SQDIFF || match_method == CV_TM_SQDIFF_NORMED ){
      matchLoc = minLoc;
      pixValue=1;
      if(minVal>0.3){break;}
  }else{matchLoc = maxLoc;pixValue=0;if(maxVal<0.7){break;}}
//cout<<minVal<<" "<<maxVal<<endl;
    for (int i = 0; i < resultImage.cols; i++){
      for (int j = 0; j < resultImage.rows; j++){
            if((matchLoc.x-templateImage.cols/2<i) && (matchLoc.x+templateImage.cols/2>i) && (matchLoc.y-templateImage.rows/2<j) && (matchLoc.y+templateImage.rows/2>j)){
            resultImage.at<float>(j,i)=pixValue;}
      }
    }
  q++;
  rectangle( imageToDisplay, matchLoc, Point( matchLoc.x + templateImage.cols , matchLoc.y + templateImage.rows ), Scalar::all(0), 2, 8, 0 );
    markers->push_back(Point( matchLoc.x + templateImage.cols , matchLoc.y + templateImage.rows ));
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

void levelOutImage(vector<Point>* markers,Mat &sourceImage){
static float angle;
static int shiftHorizontal;
static int shiftVertical;
if (markers->size()==4){

int rightMarker=findMarker( markers, 2);
int leftMarker=findMarker( markers, 4);
int a=markers->at(rightMarker).y-markers->at(leftMarker).y;
int b=markers->at(rightMarker).x-markers->at(leftMarker).x;
shiftHorizontal=sourceImage.cols/2-(markers->at(rightMarker).x+markers->at(leftMarker).x)/2+26;
shiftVertical=sourceImage.rows/2-(markers->at(rightMarker).y+markers->at(leftMarker).y)/2+26;

sourceImage=shiftFrame(sourceImage, shiftHorizontal,shiftVertical );
angle=(atan2 (a,b)* 180 / 3.14);
rotate(sourceImage,angle , sourceImage);

}else{
rotate(sourceImage,angle , sourceImage);
sourceImage=shiftFrame(sourceImage, shiftHorizontal,shiftVertical );
}

}
int findMarker(vector<Point>* markers,int whichMarker){
int findedMarker=0;
if (whichMarker==2){
    int cord=0;
    for(int i=0;i<markers->size();i++){
        if (markers->at(i).x>cord){cord=markers->at(i).x;findedMarker=i;}
    }
}else if (whichMarker==4){
    int cord=9999;
    for(int i=0;i<markers->size();i++){
        if (markers->at(i).x<cord){cord=markers->at(i).x;findedMarker=i;}
    }
}
return findedMarker;
}

void odejm(Mat &obr,Mat tlo){
    Mat wodj,wtlo;
    absdiff(obr,tlo,wodj);
    threshold(wodj,wodj,60,255,THRESH_BINARY);
    obr=wodj;
}


void ruch(Mat &obr,Mat poprz){
    Mat wobr,wodj;
    cvtColor(obr,wobr,CV_RGB2GRAY);
    absdiff(wobr,poprz,wodj);
    //threshold(wodj,wodj,60,255,THRESH_BINARY);
    obr=wodj;

}

cv::Mat shiftFrame(Mat frame, int horizontalShift, int verticalShift){
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
