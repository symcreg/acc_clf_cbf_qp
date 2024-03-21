//
// Created by symct on 2024/3/14.
//
//TODO:update qp problem instead of re-constructing it
#include "dynamic.h"
#include "osqp.h"
#include "cmath"
float p = 0;
float v = 11.0f;
float z = 10;

float param_delta = 5.0f;

float control_u = 0;
float aCLF = 0;
float aCBF = 0;
float constraintValueCLF = 0;
float constraintValueCBF = 0;
void updateState(){
    p = p + v * physic_dt;
    v = v + control_u / physic_m * physic_dt; // -f_r / m * dt;
    z = z + (physic_v_0 - v) * physic_dt;
}
void updateConstraint(){
    // 2 * (v - v_d) / m * u <= -lambda * (v - v_d)^2 + delta
    aCLF = 2 * (v - physic_v_d) / physic_m;
    constraintValueCLF = -param_lambda * powf((v - physic_v_d),2) + param_delta;
    // Th / m * u <= v_0 - v + gamma * (z - Th * v - 0.5f * pow(v - v_0,2) / (c * physic_g))
    aCBF = (param_Th + (v - physic_v_0)/(param_c * physic_g)) / physic_m;
    constraintValueCBF = physic_v_0 - v + param_gamma * (z - param_Th * v - 0.5f * powf(v - physic_v_0,2) / (param_c * physic_g));
}
int qpSlackSolve(){
    //qp problem
    //1/2 * x^T * P * x + q^T * x
    //subject to:
    //2 * (v - v_d) / m * u - delta = -lambda * (v - v_d)^2
    //delta >= 0
    //(param_Th + (v - physic_v_0)/(param_c * physic_g)) / physic_m * u <= physic_v_0 - v + param_gamma * (z - param_Th * v - 0.5f * pow(v - physic_v_0,2) / (param_c * physic_g))
    //introduce slack variable to relax the clf constraint
    //convert to a equality constraint and a inequality constraint(the first one and the second one)

    //matrix 2x2
    /*Matrix P:
     *   [1, 0]
     *   [0, param_p]
     */
    OSQPFloat P_x[2] = {1, param_p}; //non-zero value
    OSQPInt P_nnz = 2; //number of non-zero value
    OSQPInt P_i[3] = {0, 1}; //row indices, corresponding to P_x
    OSQPInt P_p[3] = {0, 1, 2}; //column pointer
    OSQPFloat q[2] = {0, 0};
    /*Matrix A:
     *   [aCLF, -1]
     *   [aCBF, 0]
     *   [0, 1]
     */
    OSQPFloat A_x[4] = {aCLF, aCBF, -1, 1}; //non-zero value
    OSQPInt A_nnz = 4; //number of non-zero value
    OSQPInt A_i[4] = {0, 1, 0, 2}; //row indices, corresponding to A_x
    OSQPInt A_p[3] = {0, 2, 4}; //column pointer
    OSQPFloat l[3] = {constraintValueCLF - param_delta, -OSQP_INFTY,0}; //lower bound
    OSQPFloat u[3] = {constraintValueCLF - param_delta ,constraintValueCBF,OSQP_INFTY}; //upper bound

    OSQPInt n = 2; //number of variables
    OSQPInt m = 3; //number of constraints

    OSQPInt exitFlag = 0; //exitFlag

    OSQPSolver *solver = nullptr;
    OSQPSettings *settings = nullptr;

    auto *P = (OSQPCscMatrix*)malloc(sizeof(OSQPCscMatrix));
    auto *A = (OSQPCscMatrix*)malloc(sizeof(OSQPCscMatrix));

    csc_set_data(P, n, n, P_nnz, P_x, P_i, P_p);
    csc_set_data(A, m, n, A_nnz, A_x, A_i, A_p);

    settings = (OSQPSettings *)malloc(sizeof(OSQPSettings));
    if(settings){
        osqp_set_default_settings(settings);
        settings->verbose = false;
        settings->alpha = 1.0;
    }
    exitFlag = osqp_setup(&solver, P, q, A, l, u, m, n, settings);
    if(!exitFlag){
        // Solve Problem
        exitFlag= osqp_solve(solver);
    }
    control_u = solver->solution->x[0];
    param_delta = solver->solution->x[1];

    osqp_cleanup(solver);
    if(P) free(P);
    if(A) free(A);
    if(settings) free(settings);

    return (int)exitFlag;
}
int qpSolve(){
    //matrix 1x1
    OSQPFloat P_x[1] = {1}; //non-zero value
    OSQPInt P_nnz = 1; //number of non-zero value
    OSQPInt P_i[1] = {0}; //row indices, corresponding to P_x
    OSQPInt P_p[2] = {0, 1}; //column pointer
    OSQPFloat q[1] = {param_p * powf(param_delta,2)}; //non-zero value
//    OSQPFloat q[1] = {0}; //non-zero value

    OSQPFloat A_x[2] = {aCLF, aCBF}; //non-zero value
    OSQPInt A_nnz = 2; //number of non-zero value
    OSQPInt A_i[2] = {0, 1}; //row indices, corresponding to A_x
    OSQPInt A_p[3] = {0, 1, 2}; //column pointer
    OSQPFloat l[2] = {-OSQP_INFTY,-OSQP_INFTY}; //lower bound
    OSQPFloat u[2] = {constraintValueCLF,constraintValueCBF}; //upper bound

    OSQPInt n = 1; //number of variables
    OSQPInt m = 2; //number of constraints
    OSQPInt exitFlag = 0; //exitFlag

    OSQPSolver *solver = nullptr;
    OSQPSettings *settings = nullptr;
    auto *P = (OSQPCscMatrix*)malloc(sizeof(OSQPCscMatrix));
    auto *A = (OSQPCscMatrix*)malloc(sizeof(OSQPCscMatrix));

    // Populate matrices

    csc_set_data(P, n, n, P_nnz, P_x, P_i, P_p);
    csc_set_data(A, m, n, A_nnz, A_x, A_i, A_p);

    // Set default settings
    settings = (OSQPSettings *)malloc(sizeof(OSQPSettings));
    if(settings){
        osqp_set_default_settings(settings);
        settings->verbose = false;
        settings->alpha = 1.0;
    }
    exitFlag = osqp_setup(&solver, P, q, A, l, u, m, n, settings);
    if(!exitFlag){
        // Solve Problem
        exitFlag= osqp_solve(solver);
    }


    control_u = solver->solution->x[0];

    osqp_cleanup(solver);
    if(P) free(P);
    if(A) free(A);
    if(settings) free(settings);


    return (int)exitFlag;
}

int clfQPSolve(){
    //matrix 1x1
    OSQPFloat P_x[1] = {1}; //non-zero value
    OSQPInt P_nnz = 1; //number of non-zero value
    OSQPInt P_i[1] = {0}; //row indices, corresponding to P_x
    OSQPInt P_p[2] = {0, 1}; //column pointer
    OSQPFloat q[1] = {param_p * powf(param_delta,2)};

    OSQPFloat A_x[1] = {aCLF}; //non-zero value
    OSQPInt A_nnz = 1; //number of non-zero value
    OSQPInt A_i[1] = {0}; //row indices, corresponding to A_x
    OSQPInt A_p[2] = {0, 1}; //column pointer
    OSQPFloat l[1] = {-OSQP_INFTY}; //lower bound
    OSQPFloat u[1] = {constraintValueCLF}; //upper bound

    OSQPInt n = 1; //number of variables
    OSQPInt m = 1; //number of constraints
    OSQPInt exitFlag = 0; //exitFlag

    OSQPSolver *solver = nullptr;
    OSQPSettings *settings = nullptr;

    auto *P = (OSQPCscMatrix*)malloc(sizeof(OSQPCscMatrix));
    auto *A = (OSQPCscMatrix*)malloc(sizeof(OSQPCscMatrix));

    csc_set_data(P, n, n, P_nnz, P_x, P_i, P_p);
    csc_set_data(A, m, n, A_nnz, A_x, A_i, A_p);

    settings = (OSQPSettings *)malloc(sizeof(OSQPSettings));
    if(settings){
        osqp_set_default_settings(settings);
        settings->verbose = false;
        settings->alpha = 1.0;
    }
    exitFlag = osqp_setup(&solver, P, q, A, l, u, m, n, settings);
    if(!exitFlag){
        // Solve Problem
        exitFlag= osqp_solve(solver);
    }
    control_u = solver->solution->x[0];

    osqp_cleanup(solver);
    if(P) free(P);
    if(A) free(A);
    if(settings) free(settings);


    return (int)exitFlag;
}
int cbfQPSolve(){
    //matrix 1x1
    OSQPFloat P_x[1] = {1}; //non-zero value
    OSQPInt P_nnz = 1; //number of non-zero value
    OSQPInt P_i[1] = {0}; //row indices, corresponding to P_x
    OSQPInt P_p[2] = {0, 1}; //column pointer
    OSQPFloat q[1] = {0};

    OSQPFloat A_x[1] = {aCBF}; //non-zero value
    OSQPInt A_nnz = 1; //number of non-zero value
    OSQPInt A_i[1] = {0}; //row indices, corresponding to A_x
    OSQPInt A_p[2] = {0, 1}; //column pointer
    OSQPFloat l[1] = {-OSQP_INFTY}; //lower bound
    OSQPFloat u[1] = {constraintValueCBF}; //upper bound

    OSQPInt n = 1; //number of variables
    OSQPInt m = 1; //number of constraints
    OSQPInt exitFlag = 0; //exitFlag

    OSQPSolver *solver = nullptr;
    OSQPSettings *settings = nullptr;

    auto *P = (OSQPCscMatrix*)malloc(sizeof(OSQPCscMatrix));
    auto *A = (OSQPCscMatrix*)malloc(sizeof(OSQPCscMatrix));

    csc_set_data(P, n, n, P_nnz, P_x, P_i, P_p);
    csc_set_data(A, m, n, A_nnz, A_x, A_i, A_p);

    settings = (OSQPSettings *)malloc(sizeof(OSQPSettings));
    if(settings){
        osqp_set_default_settings(settings);
        settings->verbose = false;
        settings->alpha = 1.0;
    }
    exitFlag = osqp_setup(&solver, P, q, A, l, u, m, n, settings);
    if(!exitFlag){
        // Solve Problem
        exitFlag= osqp_solve(solver);
    }
    control_u = solver->solution->x[0];

    osqp_cleanup(solver);
    if(P) free(P);
    if(A) free(A);
    if(settings) free(settings);


    return (int)exitFlag;

}
void constraintControl(){

    if(control_u > param_c* physic_m * physic_g){
        control_u = param_c * physic_m * physic_g;
//        control_u = 0;
    }else if(control_u < -param_c * physic_m * physic_g){
        control_u = -param_c * physic_m * physic_g;
//        control_u = 0;
    }
}