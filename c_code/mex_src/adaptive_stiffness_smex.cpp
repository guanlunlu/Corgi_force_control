#define S_FUNCTION_NAME adaptive_stiffness_smex /* Defines and Includes */
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
    ssSetInputPortWidth(S, 0, 18);
    ssSetInputPortDirectFeedThrough(S, 0, 1);

    if (!ssSetNumOutputPorts(S, 1))
        return;
    ssSetOutputPortWidth(S, 0, 4);

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

    Eigen::Vector2d F_d(*uPtrs[0], *uPtrs[1]);
    Eigen::Vector2d T_fb(*uPtrs[2], *uPtrs[3]);
    Eigen::Matrix2d X_des{{*uPtrs[4], *uPtrs[5]},
                          {*uPtrs[6], *uPtrs[7]}};
    Eigen::Matrix2d TB_fb{{*uPtrs[8], *uPtrs[9]},
                          {*uPtrs[10], *uPtrs[11]}};

    Eigen::Matrix2d K{{*uPtrs[12], 0},
                      {0, *uPtrs[13]}};

    Eigen::Matrix2d Alpha{{*uPtrs[14], 0},
                          {0, *uPtrs[15]}};

    Eigen::Matrix2d r_k_1{{*uPtrs[16], 0},
                          {0, *uPtrs[17]}};

    Eigen::Matrix<double, 2, 3> Adapt_out = AdaptiveStiffness(F_d, T_fb, K, Alpha, r_k_1, X_des, TB_fb);

    output[0] = Adapt_out.coeff(0, 0);
    output[1] = Adapt_out.coeff(1, 1);
    output[2] = Adapt_out.coeff(0, 2);
    output[3] = Adapt_out.coeff(1, 2);
}

static void mdlTerminate(SimStruct *S) {}

#ifdef MATLAB_MEX_FILE /* Is this file being compiled as a MEX-file? */
#include "simulink.c"  /* MEX-file interface mechanism */
#else
#include "cg_sfun.h" /* Code generation registration function */
#endif