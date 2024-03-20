#include <iostream>
#include "opencv2/opencv.hpp"
#include "dynamic.h"
#include "display.h"
using namespace std;
using namespace cv;
//TODO:fix the problem of qp infeasible, correct dynamic delta to relax clf constraint

//#define CLF_TEST
//#define CBF_TEST
//#define ALL_TEST
#define SLACK_TEST
int main() {
    int i = 0;
    vector<float> vData;
    vector<float> uData;
    vector<float> Delta;
    while (z > 0 && i < 100){
        i++;
        updateState();
        vData.push_back(v);
        uData.push_back(control_u);
        Delta.push_back(param_delta);
        updateConstraint();

#ifdef CLF_TEST
        clfQPSolve();
#endif
#ifdef CBF_TEST
        cbfQPSolve();
#endif
#ifdef ALL_TEST
        qpSolve();
#endif
#ifdef SLACK_TEST
        qpSlackSolve();
#endif
        constraintControl();
        displayState(INVISIBLE, INVISIBLE);
    }
    cout<<i<<endl;
    displayVData(VISIBLE, VISIBLE, vData);
    displayUData(INVISIBLE, VISIBLE, uData);
    displayDelta(INVISIBLE, VISIBLE, Delta);
    return 0;
}