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
    ssSetInputPortWidth(S, 0, 18);
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

    Eigen::Matrix<double, 3, 2> X_des;
    Eigen::Matrix<double, 2, 2> TB_fb;
    Eigen::Vector2d T_fb; // reply torque
    X_des << *uPtrs[0], *uPtrs[3], *uPtrs[1], *uPtrs[4], *uPtrs[2], *uPtrs[5];
    TB_fb << *uPtrs[6], *uPtrs[7], *uPtrs[8], *uPtrs[9];
    T_fb << *uPtrs[10], *uPtrs[11];

    Eigen::Matrix2d M{{*uPtrs[12], 0},
                      {0, *uPtrs[13]}};

    Eigen::Matrix2d K{{*uPtrs[14], 0},
                      {0, *uPtrs[15]}};

    Eigen::Matrix2d D{{*uPtrs[16], 0},
                      {0, *uPtrs[17]}};

    Eigen::Vector2d Xeef_ddot = ImpedanceFilter(M, K, D, X_des, TB_fb, T_fb);
    // std::cout << "-------- imp filt --------" << std::endl;
    // std::cout << "Xdes = " << std::endl;
    // std::cout << X_des << std::endl;
    // std::cout << "Xeef_ddot = " << std::endl;
    // std::cout << Xeef_ddot << std::endl;

    *output = Xeef_ddot[0];   // dd_x
    *output++ = Xeef_ddot[1]; // dd_y
}

static void mdlTerminate(SimStruct *S) {}

#ifdef MATLAB_MEX_FILE /* Is this file being compiled as a MEX-file? */
#include "simulink.c"  /* MEX-file interface mechanism */
#else
#include "cg_sfun.h" /* Code generation registration function */
#endif