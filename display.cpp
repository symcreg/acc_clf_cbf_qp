//
// Created by symct on 2024/3/20.
//

#include "display.h"
#include "dynamic.h"
#include "opencv2/opencv.hpp"
using namespace std;
using namespace cv;


void displayState(int textVisible, int imageVisible){
    if(textVisible == VISIBLE){
        cout<<"===========param=========="<<endl;
        cout<<"aCLF: "<<aCLF<<" aCBF: "<<aCBF<<" constraintValueCLF: "<<constraintValueCLF<<" constraintValueCBF: "<<constraintValueCBF<<endl;

        cout<<"===========state=========="<<endl;
        cout << "p: " << p << " v: " << v << " z: " << z << " u: " << control_u << endl;
    }
    if(imageVisible == VISIBLE){
        Mat img(1000, 1000, CV_8UC3, Scalar(0, 0, 0));

        rectangle(img, Point(10-5 + p*10, 500-5), Point(10+5 + p * 10, 500+5), Scalar(255, 255, 255), 2);
        rectangle(img, Point(10-5 + (p + z)*10, 500-5), Point(10+5 + (p +z)*10, 500+5), Scalar(255, 255, 255), 2);


        imshow("state", img);
        waitKey(50);
    }
}
void displayVData(int textVisible, int imageVisible, vector<float>& vData){
    Mat img(1000, 1000, CV_8UC3, Scalar(0, 0, 0));
    for(int i = 0; i < vData.size(); i++){
        if(textVisible == VISIBLE){
            cout<<"["<<i<<"]:"<<"v:"<<vData[i]<<endl;
            cout<<"["<<i<<"]:"<<"diff:"<<physic_v_d - vData[i]<<endl;
        }
        if(imageVisible == VISIBLE){
            line(img, Point(0, 500 - physic_v_d * 10), Point(1000, 500 - physic_v_d * 10), Scalar(255, 255, 255), 2);
            line(img, Point(i * 10, 500 - physic_v_d * 10), Point(i * 10, 500 - vData[i] * 10), Scalar(0, 0, 255), 2);
            line(img, Point(i * 10, 500), Point(i * 10, 500 - vData[i] * 10), Scalar(255, 255, 255), 2);
        }
    }
    if(imageVisible == VISIBLE){
        namedWindow("vData", WINDOW_NORMAL);
        imshow("vData", img);
        waitKey(0);
    }
}
void displayUData(int textVisible, int imageVisible, vector<float>& uData){
    Mat img(1000, 1000, CV_8UC3, Scalar(0, 0, 0));
    for(int i = 0; i < uData.size(); i++){
        if(textVisible == VISIBLE){
            cout<<uData[i]<<endl;
        }
        if(imageVisible == VISIBLE){
            line(img, Point(i * 10, 500), Point(i * 10, 500 - uData[i] / 10), Scalar(255, 255, 255), 2);
        }
    }
    if(imageVisible == VISIBLE){
        namedWindow("uData", WINDOW_NORMAL);
        imshow("uData", img);
        waitKey(0);
    }
}

void displayDelta(int textVisible, int imageVisible, std::vector<float>& delta){
    Mat img(1000, 1000, CV_8UC3, Scalar(0, 0, 0));
    for(int i = 0; i < delta.size(); i++){
        if(textVisible == VISIBLE){
            cout<<delta[i]<<endl;
        }
        if(imageVisible == VISIBLE){
            line(img, Point(i * 10, 500), Point(i * 10, 500 - delta[i] * 3), Scalar(255, 255, 255), 2);
        }
    }
    if(imageVisible == VISIBLE){
        namedWindow("delta", WINDOW_NORMAL);
        imshow("delta", img);
        waitKey(0);
    }
}