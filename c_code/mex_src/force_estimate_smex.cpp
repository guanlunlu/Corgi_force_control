#define S_FUNCTION_NAME force_estimate_smex /* Defines and Includes */
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
    ssSetInputPortWidth(S, 0, 8);
    ssSetInputPortDirectFeedThrough(S, 0, 1);

    if (!ssSetNumOutputPorts(S, 1))
        return;
    ssSetOutputPortWidth(S, 0, 8);

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

    Eigen::Vector2d T_fb(*uPtrs[0], *uPtrs[1]);
    Eigen::Vector2d TB_fb(*uPtrs[2], *uPtrs[3]);
    Eigen::Vector2d TB_fb_1(*uPtrs[4], *uPtrs[5]);
    Eigen::Vector2d TB_fb_2(*uPtrs[6], *uPtrs[7]);

    Eigen::Matrix<double, 3, 2> tb_fb_state;
    tb_fb_state << TB_fb[0], TB_fb[1], TB_fb_1[0], TB_fb_1[1], TB_fb_2[0], TB_fb_2[1];
    Eigen::Vector2d tau_inertia = ID2(tb_fb_state);

    Eigen::Vector2d d_phi = dtb2dphi((TB_fb - TB_fb_1) / T_);
    Eigen::Vector2d tau_ft = jointFriction(d_phi);
    Eigen::Vector2d F_est = jointTrq2footendForce(T_fb -tau_inertia - tau_ft, TB_fb);
    

    output[0] = F_est[0];
    output[1] = F_est[1];
    output[2] = T_fb[0];
    output[3] = T_fb[1];
    output[4] = tau_inertia[0];
    output[5] = tau_inertia[1];
    output[6] = tau_ft[0];
    output[7] = tau_ft[1];
}

static void mdlTerminate(SimStruct *S) {}

#ifdef MATLAB_MEX_FILE /* Is this file being compiled as a MEX-file? */
#include "simulink.c"  /* MEX-file interface mechanism */
#else
#include "cg_sfun.h" /* Code generation registration function */
#endif