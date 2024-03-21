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
    if(textVisible == VISIBLE){
        for(int i = 0; i < vData.size(); i++){
            cout<<vData[i]<<endl;
        }
    }
    if(imageVisible == VISIBLE){
        Mat img(1000, 1000, CV_8UC3, Scalar(0, 0, 0));
        for(int i = 0; i < vData.size(); i++){
            line(img, Point(0, 500 - physic_v_d * 10), Point(1000, 500 - physic_v_d * 10), Scalar(255, 255, 255), 2);
            line(img, Point(i * 10, 500 - physic_v_d * 10), Point(i * 10, 500 - vData[i] * 10), Scalar(0, 0, 255), 2);
            line(img, Point(i * 10, 500), Point(i * 10, 500 - vData[i] * 10), Scalar(255, 255, 255), 2);
        }
        namedWindow("vData", WINDOW_NORMAL);
        imshow("vData", img);
        waitKey(0);
    }
}
void displayUData(int textVisible, int imageVisible, vector<float>& uData){
    if(textVisible == VISIBLE){
        for(int i = 0; i < uData.size(); i++){
            cout<<uData[i]<<endl;
        }
    }
    if(imageVisible == VISIBLE){
        Mat img(1000, 1000, CV_8UC3, Scalar(0, 0, 0));
        for(int i = 0; i < uData.size(); i++){
            line(img, Point(i * 10, 500), Point(i * 10, 500 - uData[i] / 10), Scalar(255, 255, 255), 2);
        }
        namedWindow("uData", WINDOW_NORMAL);
        imshow("uData", img);
        waitKey(0);
    }
}

void displayDelta(int textVisible, int imageVisible, std::vector<float>& delta){
    if(textVisible == VISIBLE){
        for(int i = 0; i < delta.size(); i++){
            cout<<delta[i]<<endl;
        }
    }
    if(imageVisible == VISIBLE){
        Mat img(1000, 1000, CV_8UC3, Scalar(0, 0, 0));
        for(int i = 0; i < delta.size(); i++){
            line(img, Point(i * 10, 500), Point(i * 10, 500 - delta[i]), Scalar(255, 255, 255), 2);
        }
        namedWindow("delta", WINDOW_NORMAL);
        imshow("delta", img);
        waitKey(0);
    }
}