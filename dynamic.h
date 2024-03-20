//
// Created by symct on 2024/3/14.
//

#ifndef CLF_CBF_LEARN_DYNAMIC_H
#define CLF_CBF_LEARN_DYNAMIC_H
#define physic_dt 0.1f //time step
#define physic_g 9.8f //gravity
#define physic_m 1600.0f //mass
#define physic_v_0 10.0f //front car speed
#define physic_v_d 15.0f //desired speed


#define param_Th 0.5f //safe distance z >= Th*v
#define param_c 2.0f //-cmg<=u<=cmg
#define param_lambda 5.0f
#define param_gamma 5.0f
#define param_p 0.02f
//#define param_delta 0.05f
//slack variable
extern float param_delta;

//state
extern float p; //position
extern float v; //velocity
extern float z; //distance to front car

//control
extern float aCLF;
extern float aCBF;
extern float constraintValueCLF;
extern float constraintValueCBF;
extern float control_u;


void updateState();
void updateConstraint();
int qpSlackSolve();
int qpSolve();
int clfQPSolve();
int cbfQPSolve();
void constraintControl();
#endif //CLF_CBF_LEARN_DYNAMIC_H
