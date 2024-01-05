#define S_FUNCTION_NAME impf2_smex /* Defines and Includes */
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
    ssSetInputPortWidth(S, 0, 22);
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

    /* Fext: Force exert to ground (Obtain by Virtual work method)*/

    Eigen::Matrix<double, 3, 2> X_des;
    X_des << *uPtrs[0], *uPtrs[1], *uPtrs[2], *uPtrs[3], *uPtrs[4], *uPtrs[5];

    Eigen::Matrix<double, 2, 1> F_ref;
    F_ref << *uPtrs[6], *uPtrs[7];

    Eigen::Matrix<double, 3, 2> TB_fb;
    TB_fb << *uPtrs[8], *uPtrs[9], *uPtrs[10], *uPtrs[11], *uPtrs[12], *uPtrs[13];

    Eigen::Matrix<double, 2, 1> T_fb; // torque feedback
    T_fb << *uPtrs[14], *uPtrs[15];
    
    Eigen::Matrix2d M{{*uPtrs[16], 0},
                      {0, *uPtrs[17]}};

    Eigen::Matrix2d K{{*uPtrs[18], 0},
                      {0, *uPtrs[19]}};

    Eigen::Matrix2d D{{*uPtrs[20], 0},
                      {0, *uPtrs[21]}};
    
    Eigen::Vector2d ddXc_k = PB_impf2(M, K, D, X_des, F_ref, TB_fb, T_fb);

    output[0] = ddXc_k[0];
    output[1] = ddXc_k[1];
}

static void mdlTerminate(SimStruct *S) {}

#ifdef MATLAB_MEX_FILE /* Is this file being compiled as a MEX-file? */
#include "simulink.c"  /* MEX-file interface mechanism */
#else
#include "cg_sfun.h" /* Code generation registration function */
#endif