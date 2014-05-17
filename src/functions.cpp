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
int findMarker(vector<Point>* markers,int whichMarker){
return 0;
}
void levelOutImage(vector<Point>* markers,Mat &sourceImage){
static float angle=0;

static int shiftHorizontal;
static int shiftVertical;

if (markers->size()>=3){

int rightMarker=findMarker( markers, 2);
int leftMarker=findMarker( markers, 4);
int a=markers->at(rightMarker).y-markers->at(leftMarker).y;
int b=markers->at(rightMarker).x-markers->at(leftMarker).x;
shiftHorizontal=sourceImage.cols/2-(markers->at(rightMarker).x+markers->at(leftMarker).x)/2+26;
shiftVertical=sourceImage.rows/2-(markers->at(rightMarker).y+markers->at(leftMarker).y)/2+26;

sourceImage=shiftFrame(sourceImage, shiftHorizontal,shiftVertical);

angle=(atan2 (a,b)* 180 / 3.14);
rotate(sourceImage,angle , sourceImage);
}else{
rotate(sourceImage,angle , sourceImage);
sourceImage=shiftFrame(sourceImage, shiftHorizontal,shiftVertical );
}

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
///kopia sortMarkers, bo chcialem zrozumiec ta funkcje
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
Point2i *najwyzej(Mat &obr){
    Mat pom;
    RNG rng(12345);
    for(int j=0;j<obr.rows;j++)
    {
        for(int i=0;i<obr.cols;i++)
        {
            if((int)obr.at<uchar>(j,i)==255)
            {
             //   cout<<j<<" "<<i<<" "<<" "<<(int)obr.at<uchar>(j,i)<<endl;
                circle(obr,Point2i(i,j),4,Scalar( rng.uniform(120, 255), rng.uniform(0,255), rng.uniform(0,255) ),-1,8,0);
                return  new Point2i(i,j);
            }
        }
    }
    return new Point2i(0,0);
}
void cien_palec(Mat obr,Mat &tlo,Mat &wynik,Mat &wynik2){
    Mat wodj,ob1,ob2,ob3,w_cien,wbin,w_reka,w_ycbcr,w_gray;
    Mat kanaly[3];
    Mat dlon,cien;
    int morphSize=1;
    Mat element = getStructuringElement(  MORPH_ELLIPSE, Size( 2*morphSize + 1, 2*morphSize+1 ),Point( morphSize,morphSize ) );

    absdiff(tlo,obr,wodj);
    cvtColor(wodj,w_gray,CV_RGB2GRAY);
    threshold(w_gray,wbin,30,255,THRESH_BINARY);

    erode(wbin,wbin,element);
    //morphSize=5;
    //element = getStructuringElement(  MORPH_ELLIPSE, Size( 2*morphSize + 1, 2*morphSize+1 ),Point( morphSize,morphSize ) );
    //dilate(wbin,wbin,element);

    cvtColor(obr,w_ycbcr,CV_RGB2YCrCb);
    split(w_ycbcr,kanaly);
    inRange(kanaly[0],a,b,ob1);
   // inRange(kanaly[1],c,d,ob2);
    inRange(kanaly[2],e,f,ob3);


//imshow("test1", ob2);
//imshow("test2", ob3);
//bitwise_or(ob3,ob2,dlon);
    //bitwise_and(dlon,wbin,dlon);
    //dilate(dlon,dlon,element);
    ob3.copyTo(dlon);
    dlon.copyTo(wynik);
//imshow("test", dlon);
    //cvtColor(wodj,w_gray,CV_RGB2GRAY);
    //threshold(w_gray,wbin,30,255,THRESH_BINARY);
   // bitwise_not(ob1,ob1);
    //imshow("test", ob1);
   // imshow("test2", wbin);
    absdiff(ob1,wbin,cien);
    bitwise_not(ob3,ob3);
    bitwise_and(ob3,wbin,dlon);
    morphSize=3;
    element = getStructuringElement(  MORPH_ELLIPSE, Size( 2*morphSize + 1, 2*morphSize+1 ),Point( morphSize,morphSize ) );

    erode(dlon,dlon,element);
   // bitwise_and(wbin,wbin,dlon);
    dlon.copyTo(wynik2);
}

void odejm(Mat &obr,Mat &tlo,int p, int q){
    Mat wodj;
    absdiff(tlo,obr,wodj);
    cvtColor(wodj,wodj,CV_RGB2GRAY);
    threshold(wodj,wodj,p,255,THRESH_BINARY);
    wodj.copyTo(obr);
}

cv::Mat shiftFrame(Mat &frame, int horizontalShift, int verticalShift){
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

void processVideo(char* videoFilename) {
    //create the capture object
    Mat frame; //current frame
Mat fgMaskMOG; //fg mask generated by MOG method
Mat fgMaskMOG2; //fg mask fg mask generated by MOG2 method
int keyboard;
int a=1;
int b=1;
namedWindow("FG Mask MOG", CV_WINDOW_AUTOSIZE);
 namedWindow("FG Mask MOG 2", CV_WINDOW_AUTOSIZE);
createTrackbar( "a", "FG Mask MOG", &a, 255, 0 );
   createTrackbar( "b", "FG Mask MOG 2", &b, 255, 0 );

    BackgroundSubtractorMOG pMOG;
    BackgroundSubtractorMOG pMOG2;
    pMOG.set("nmixtures", 10);
   // pMOG2.set("detectShadows",1);
    VideoCapture capture(videoFilename);
    if(!capture.isOpened()){
        //error in opening the video input
        cerr << "Unable to open video file: " << videoFilename << endl;
        exit(EXIT_FAILURE);
    }
    //read input data. ESC or 'q' for quitting
    while( (char)keyboard != 'q' && (char)keyboard != 27 ){
        //read the current frame
        if(!capture.read(frame)) {
            cerr << "Unable to read next frame." << endl;
            cerr << "Exiting..." << endl;
            exit(EXIT_FAILURE);
        }
        //update the background model
           //AND HERE!!!
        pMOG(frame, fgMaskMOG,a/10.f);
        pMOG2(frame, fgMaskMOG2,b/10.f);
        //get the frame number and write it on the current frame
        stringstream ss;
        rectangle(frame, cv::Point(10, 2), cv::Point(100,20),
            cv::Scalar(255,255,255), -1);
        ss << capture.get(CV_CAP_PROP_POS_FRAMES);
        string frameNumberString = ss.str();
        putText(frame, frameNumberString.c_str(), cv::Point(15, 15),FONT_HERSHEY_SIMPLEX, 0.5 , cv::Scalar(0,0,0));
        //show the current frame and the fg masks
        imshow("Frame", frame);
        imshow("FG Mask MOG", fgMaskMOG);
        imshow("FG Mask MOG 2", fgMaskMOG2);
        //get the input from the keyboard
        keyboard = waitKey( 30 );
    }
    //delete capture object
    capture.release();
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
      //  break;
    }
}
return backgroundFrame;
}


///ma znaleüc tlo i 4 kolka
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
