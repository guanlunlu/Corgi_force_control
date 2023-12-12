#define S_FUNCTION_NAME impedance_filter_smex /* Defines and Includes */
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
    ssSetInputPortWidth(S, 0, DYNAMICALLY_SIZED);
    ssSetInputPortDirectFeedThrough(S, 0, 1);

    if (!ssSetNumOutputPorts(S, 1))
        return;
    ssSetOutputPortWidth(S, 0, DYNAMICALLY_SIZED);

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
    real_T *y = ssGetOutputPortRealSignal(S, 0);
    int_T width = ssGetOutputPortWidth(S, 0);

    Eigen::Matrix<double, 3, 2> X_des;
    Eigen::Matrix<double, 3, 2> X_fb;
    X_des << *uPtrs[0], *uPtrs[3], *uPtrs[1], *uPtrs[4], *uPtrs[2], *uPtrs[5];
    X_fb << *uPtrs[6], *uPtrs[9], *uPtrs[7], *uPtrs[10], *uPtrs[8], *uPtrs[11];

    Eigen::Matrix2d M{{*uPtrs[12], 0},
                      {0, *uPtrs[13]}};

    Eigen::Matrix2d K{{*uPtrs[14], 0},
                      {0, *uPtrs[15]}};

    Eigen::Matrix2d D{{*uPtrs[16], 0},
                      {0, *uPtrs[17]}};

    std::cout << X_des << std::endl;

    *y = 2.0 * (*uPtrs[0]);   // trq_phiR
    *y++ = 2.0 * (*uPtrs[0]); // trq_phiL
}

static void mdlTerminate(SimStruct *S) {}

#ifdef MATLAB_MEX_FILE /* Is this file being compiled as a MEX-file? */
#include "simulink.c"  /* MEX-file interface mechanism */
#else
#include "cg_sfun.h" /* Code generation registration function */
#endif