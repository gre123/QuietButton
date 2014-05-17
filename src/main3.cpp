////#include <iostream>
//#include "functions.h"
//
//using namespace std;
//int a=115;
//int b=255;
//int c=100;
//int d=120;
//int e=146;
//int f=220;
//char key;
//
//int main(){
//    char nazwaokna[] = "Podglad kamery - ustawianie tla";
//    cvNamedWindow(nazwaokna, CV_WINDOW_AUTOSIZE); //Create window
//    VideoCapture capture(0); // open the video file for reading
//    if (!capture.isOpened()){
//         cout << "Nie znalazlem kamery!" << endl;
//         return -1;
//    }
//    capture.set(CV_CAP_PROP_FRAME_WIDTH, 800);
//    capture.set(CV_CAP_PROP_FRAME_HEIGHT, 600);
//
/////czesc do wykrywania pozycji klawiatury
//    int u1=150;
//    int u2=100;
//    Mat frame, channel[3], tlo;
//    createTrackbar( "Próg1", nazwaokna, &u1, 255, 0 );
//    createTrackbar( "Próg2", nazwaokna, &u2, 255, 0 );
//    vector<Vec3f> circles;
//    cvSetMouseCallback( nazwaokna, myszkaCallback, (void*) &circles); //do ewentualnego wyklikiwania naroznikow
//    while(capture.read(frame)){ //Bedzie petla do wykrywania tla i kolek
//
//        split(frame, channel);
//        //cvtColor(frame, channel[0], CV_BGR2GRAY);
//        //inRange(channel[0], Scalar(200), Scalar(255), channel[0]);
//		if (circles.size()>0 && circles[0][2]!=10){HoughCircles( channel[0], circles, CV_HOUGH_GRADIENT, 1, channel[0].rows/3, u1, u2, 0, 0 );}
//		//metoda Mieszka I, ale zrobienie tego normalnie wymaga zrobienia struktury na kolka+boolean a nie chce mi sie tego robic
//
//        for( size_t i = 0; i < circles.size(); i++ )
//        {
//            Point center(cvRound(circles[i][0]), cvRound(circles[i][1]));
//            int radius = cvRound(circles[i][2]);
//            circle( channel[0], center, 3, Scalar(0,255,0), -1, 8, 0 );      // circle center
//            circle( channel[0], center, radius, Scalar(0,0,255), 3, 8, 0 );      // circle outline
//        }
////        putText(channel[0], "Twojastara", cvPoint(30,30),
////            FONT_HERSHEY_COMPLEX, 1, cvScalar(200,200,250), 1, CV_AA);
//        imshow(nazwaokna, channel[0]);
//        key = cvWaitKey(10);
//        if (key == 27){
//                cout << "Nacisnieto ESC" << endl;
//                destroyAllWindows();
//                return 0;
//        }
//        if (key == 13) {
//                if (circles.size()==4){  //zmien na ==4
//                    cout << "Nacisnieto ENTER, sa 4 kolka" << endl;
//                    frame.copyTo(tlo);
//                    destroyAllWindows();
//                    break;
//                } else {cout << "Nacisnieto ENTER, ale kolek jest: " << circles.size() << endl;}
//
//        }
//    }
//    sortCircles(&circles);
//    vector<Point> brzegi = vec3fToPoint(circles);
//        brzegi[0].x=brzegi[0].x; //-0.8*circles[0][2]; //lg
//        brzegi[1].x=brzegi[1].x; //+0.8*circles[1][2]; //pg
//        brzegi[2].x=brzegi[2].x; //-0.8*circles[2][2]; //ld
//        brzegi[3].x=brzegi[3].x; //+0.8*circles[3][2]; //pd
//    Rect boundingrect = boundingRect(brzegi);
//    Mat maska;
//        maska = cv::Mat::zeros(tlo.size(),CV_8UC1);
//        maska(boundingrect) = 255;
//
/////teraz czesc do ustawiania parametrow modelu koloru skory
//    //destroyAllWindows();
//    char nazwaokna2[] = "Ustawianie parametrow wykrywania reki";
//    cvNamedWindow(nazwaokna2, CV_WINDOW_AUTOSIZE); //Create window
//    int ta=90;
//    int tb=230;
//    int tc=110;
//    int td=240;
//    int ymin=0;
//    int ymax=140;
//    createTrackbar( "Ta (Ta<Cb)", nazwaokna2, &ta, 255, 0 );
//    createTrackbar( "Tb (Cb<Tb)", nazwaokna2, &tb, 255, 0 );
//    createTrackbar( "Tc (Tc<Cb)", nazwaokna2, &tc, 255, 0 );
//    createTrackbar( "Td (Cb<Td)", nazwaokna2, &td, 255, 0 );
//    createTrackbar( "Ymin (Ymin<Y)", nazwaokna2, &ymin, 255, 0 );
//    createTrackbar( "Ymax (Y<Ymax)", nazwaokna2, &ymax, 255, 0 );
//    Mat ycrcb, reka;
//
//    while(capture.read(frame)){
//        cvtColor(frame, ycrcb, CV_BGR2YCrCb);
//        inRange(ycrcb, Scalar(ymin, tc, ta), Scalar(ymax, td, tb), reka);
//        reka &= maska;
//
//        imshow(nazwaokna2, reka);
//        key = cvWaitKey(10);
//        if (key == 27){
//            cout << "Nacisnieto ESC" << endl;
//            destroyAllWindows();
//            return 0;
//        }
//        if (key == 13) {
//            cout << "Nacisnieto ENTER, parametry wykrywania reki zapisane" << endl;
//            destroyAllWindows();
//            break;
//        }
//    }
//
/////Teraz czesc do ustawiania parametrow wykrywania cienia
//    int levelBin=10;
//    Mat cien;
//    char nazwaokna3[] = "Ustawianie parametrow wykrywania cienia";
//    cvNamedWindow(nazwaokna3, CV_WINDOW_AUTOSIZE); //Create window
//    createTrackbar( "Prog binaryzacji", nazwaokna3, &levelBin, 255, 0 );
//    while(capture.read(frame)){
//        split(frame, channel);
//        cvtColor(frame, ycrcb, CV_BGR2YCrCb);
//        inRange(ycrcb, Scalar(ymin, tc, ta), Scalar(ymax, td, tb), reka);
//        cien = channel[2] + reka;
//        threshold(cien,cien,levelBin,255,1);
//        cien &= maska;
//
//        imshow(nazwaokna3, cien);
//        key = cvWaitKey(10);
//        if (key == 27){
//            cout << "Nacisnieto ESC" << endl;
//            destroyAllWindows();
//            return 0;
//        }
//        if (key == 13) {
//            cout << "Nacisnieto ENTER, parametry wykrywania cienia zapisane" << endl;
//            destroyAllWindows();
//            break;
//        }
//    }
//
/////Chyba wszystko ustawione, teraz koncowe wyswietlanie
//    char nazwaokna4[] = "Podglad wynikow";
//    cvNamedWindow(nazwaokna4, CV_WINDOW_AUTOSIZE); //Create window
//    Point2i *r,*p;
//    Mat polaczone;
//    Mat tym[3];
//        tym[2]=cv::Mat::zeros(tlo.size(),CV_8UC1);
////cout << "echodze do while'a 4" << endl;
//    while(capture.read(frame)){
//        split(frame, channel);
//        cvtColor(frame, ycrcb, CV_BGR2YCrCb);
//        inRange(ycrcb, Scalar(ymin, tc, ta), Scalar(ymax, td, tb), reka);
//        reka &= maska;
////cout << "mam reke" << endl;
//        cien = channel[2] + reka;
//        threshold(cien,cien,levelBin,255,1);
//        cien &= maska;
////cout << "mam cien i maske" << endl;
//        r=najwyzej(reka);
//        p=najwyzej(cien);
//
//        line(tym[2], *r, *p, cv::Scalar(255), 3,8,0);
//        tym[0]=reka;
//        tym[1]=cien;
//        merge(tym,3,polaczone);
//            std::ostringstream str;
//            str << "Pozycja palca: (" << (*r).x << "," << (*r).y << ")";
//            putText(polaczone, str.str(), cvPoint(30,30),
//            FONT_HERSHEY_COMPLEX, 1, cvScalar(200,200,250), 1, CV_AA);
//        imshow(nazwaokna4, polaczone);
//
//        tym[2]=cv::Mat::zeros(frame.size(),CV_8UC1);
//
//        key = cvWaitKey(10);
//        if (key == 27){
//            cout << "Nacisnieto ESC" << endl;
//            destroyAllWindows();
//            return 0;
//        }
//        if (key == 13) {
//            cout << "Nacisnieto ENTER, konczymy impreze" << endl;//trzeba bedzie to w dzialajacej wersji usunac
//            destroyAllWindows();
//            break;
//        }
//    }
//
/////Koniec
//    destroyAllWindows();
//    cout << "Wychodze" << endl;
//    return 0;
//}
//
