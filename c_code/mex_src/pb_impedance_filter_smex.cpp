#define S_FUNCTION_NAME pb_impedance_filter_smex /* Defines and Includes */
#define S_FUNCTION_LEVEL 2
#include "stdio.h"
#include "simstruc.h"

#include "force_tracking.hpp"

static void mdlInitializeSizes(SimStruct *S)
{
    ssSetNumSFcnParams(S, 0);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S))
    {
        return; /* Parameter mismatch reported by the Simulink engine*/
    }

    if (!ssSetNumInputPorts(S, 1))
        return;
    ssSetInputPortWidth(S, 0, 36);
    ssSetInputPortDirectFeedThrough(S, 0, 1);

    if (!ssSetNumOutputPorts(S, 1))
        return;
    ssSetOutputPortWidth(S, 0, 2);

    ssSetNumSampleTimes(S, 1);

    /* Take care when specifying exception free code - see sfuntmpl.doc */
    ssSetOptions(S, SS_OPTION_EXCEPTION_FREE_CODE);
}

static void mdlInitializeSampleTimes(SimStruct *S)
{
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0.0);
}

static void mdlOutputs(SimStruct *S, int_T tid)
{
    int_T i;
    InputRealPtrsType uPtrs = ssGetInputPortRealSignalPtrs(S, 0);
    real_T *output = ssGetOutputPortRealSignal(S, 0);
    int_T width = ssGetOutputPortWidth(S, 0);

    kinematics_setup();

    /* Xref = [x_k, y_k;
              x_k_1, y_k_1;
              x_k_2, y_k_2;] */
    /* Xc = [xc_k_1, yc_k_1;
            yc_k_2, yc_k_2] */
    /* Fref = [Fx(k), Fy(k);
               Fx(k-1), Fyk-1);
               Fx(k-2), Fy(k-2)] */
    /* TB_fb = [theta(k), beta(k);
                theta(k-1), beta(k-1);
                theta(k-2), beta(k-2);
                theta(k-3), beta(k-3)] */
    /* T_fb = [T_R(k), T_L(k);
               T_R(k-1), T_L(k-1);
               T_R(k-2), T_L(k-2)] */
    /* Fext: Force exert to ground (Obtain by Virtual work method)*/

    Eigen::Matrix<double, 3, 2> X_des;
    Eigen::Matrix<double, 2, 2> X_c;
    Eigen::Matrix<double, 3, 2> F_ref;
    Eigen::Matrix<double, 4, 2> TB_fb;
    Eigen::Matrix<double, 3, 2> T_fb; // torque feedback
    X_des << *uPtrs[0], *uPtrs[1], *uPtrs[2], *uPtrs[3], *uPtrs[4], *uPtrs[5];
    X_c << *uPtrs[6], *uPtrs[7], *uPtrs[8], *uPtrs[9];
    F_ref << *uPtrs[10], *uPtrs[11], *uPtrs[12], *uPtrs[13], *uPtrs[14], *uPtrs[15];
    TB_fb << *uPtrs[16], *uPtrs[17], *uPtrs[18], *uPtrs[19], *uPtrs[20], *uPtrs[21], *uPtrs[22], *uPtrs[23];
    T_fb << *uPtrs[24], *uPtrs[25], *uPtrs[26], *uPtrs[27], *uPtrs[28], *uPtrs[29];
    
    Eigen::Matrix2d M{{*uPtrs[30], 0},
                      {0, *uPtrs[31]}};

    Eigen::Matrix2d K{{*uPtrs[32], 0},
                      {0, *uPtrs[33]}};

    Eigen::Matrix2d D{{*uPtrs[34], 0},
                      {0, *uPtrs[35]}};

    Eigen::Vector2d Xc_k = PositionBasedImpedanceFilter(M, K, D, X_des, F_ref, X_c, TB_fb, T_fb);

    // std::cout << "Xref: "<< X_des << "\n";

    // std::cout<< "Xc_k: "<< Xc_k[0] << Xc_k[1] << std::endl;
    // std::cout<< "uXc_k: "<< *uPtrs[0] << *uPtrs[1] << std::endl;
    // std::cout << "--" << std::endl;

    output[0] = Xc_k[0];
    output[1] = Xc_k[1];
    // *output = 0.2;   // Xc_x(k)
    // *output++ = 0.3; // Xc_y(k)
}

static void mdlTerminate(SimStruct *S) {}

#ifdef MATLAB_MEX_FILE /* Is this file being compiled as a MEX-file? */
#include "simulink.c"  /* MEX-file interface mechanism */
#else
#include "cg_sfun.h" /* Code generation registration function */
#endif