#ifndef RTW_HEADER_Copy_of_linkleg_trajectory_contact_acc_h_
#define RTW_HEADER_Copy_of_linkleg_trajectory_contact_acc_h_
#ifndef Copy_of_linkleg_trajectory_contact_acc_COMMON_INCLUDES_
#define Copy_of_linkleg_trajectory_contact_acc_COMMON_INCLUDES_
#include <stdlib.h>
#define S_FUNCTION_NAME simulink_only_sfcn
#define S_FUNCTION_LEVEL 2
#ifndef RTW_GENERATED_S_FUNCTION
#define RTW_GENERATED_S_FUNCTION
#endif
#include "sl_AsyncioQueue/AsyncioQueueCAPI.h"
#include "rtwtypes.h"
#include "simstruc.h"
#include "fixedpoint.h"
#endif
#include "Copy_of_linkleg_trajectory_contact_acc_types.h"
#include <stddef.h>
#include <float.h>
#include "mwmathutil.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
typedef struct { real_T B_8_0_0 ; real_T B_8_1_0 [ 44 ] ; real_T B_8_2_0 [ 7
] ; real_T B_8_17_0 ; real_T B_8_20_0 ; real_T B_8_25_0 ; real_T B_8_27_0 ;
real_T B_8_28_0 ; real_T B_8_29_0 ; real_T B_8_30_0 ; real_T B_8_31_0 ;
real_T B_8_32_0 ; real_T B_8_33_0 ; real_T B_8_34_0 [ 2 ] ; real_T B_8_35_0 [
2 ] ; real_T B_8_36_0 ; real_T B_8_37_0 ; real_T B_8_38_0 ; real_T B_8_39_0 ;
real_T B_8_40_0 ; real_T B_8_41_0 ; real_T B_8_43_0 [ 2 ] ; real_T B_8_44_0 [
2 ] ; real_T B_8_45_0 ; real_T B_8_46_0 ; real_T B_8_47_0 ; real_T B_8_48_0 ;
real_T B_8_49_0 [ 2 ] ; real_T B_8_50_0 [ 2 ] ; real_T B_8_51_0 [ 2 ] ;
real_T B_8_52_0 ; real_T B_8_54_0 ; real_T B_8_56_0 [ 2 ] ; real_T B_8_59_0 ;
real_T B_8_61_0 ; real_T B_8_62_0 ; real_T B_8_64_0 ; real_T B_8_65_0 ;
real_T B_8_67_0 ; real_T B_8_68_0 ; real_T B_8_69_0 ; real_T B_8_70_0 ;
real_T B_8_71_0 ; real_T B_8_72_0 ; real_T B_8_73_0 ; real_T B_8_74_0 ;
real_T B_8_75_0 ; real_T B_8_76_0 ; real_T B_8_77_0 ; real_T B_8_78_0 ;
real_T B_8_79_0 ; real_T B_8_80_0 ; real_T B_8_81_0 ; real_T B_8_82_0 ;
real_T B_8_83_0 ; real_T B_8_84_0 ; real_T B_8_85_0 ; real_T B_8_86_0 ;
real_T B_8_103_0 [ 2 ] ; real_T B_8_104_0 [ 2 ] ; real_T B_8_112_0 [ 4 ] ;
real_T B_8_113_0 ; real_T B_8_114_0 ; real_T B_8_115_0 ; real_T B_8_128_0 [ 4
] ; real_T B_8_129_0 ; real_T B_8_130_0 ; real_T B_8_133_0 ; real_T B_8_135_0
[ 4 ] ; real_T B_8_136_0 [ 4 ] ; real_T B_8_137_0 [ 16 ] ; real_T B_8_0_0_m ;
real_T B_8_2_0_c ; real_T B_8_3_0 ; real_T B_8_4_0 ; real_T B_8_5_0 ; real_T
B_8_6_0 ; real_T B_8_7_0 ; real_T B_8_8_0 [ 2 ] ; real_T B_8_9_0 ; real_T
B_8_10_0 ; real_T B_8_11_0 [ 2 ] ; real_T B_8_12_0 ; real_T B_8_13_0 ; real_T
B_8_15_0 [ 2 ] ; real_T B_8_16_0 [ 2 ] ; real_T B_8_17_0_k ; real_T B_8_18_0
; real_T B_8_19_0 ; real_T B_8_20_0_c ; real_T B_8_21_0 ; real_T B_8_22_0 ;
real_T B_8_23_0 ; real_T B_8_24_0 ; real_T B_7_0_1 [ 2 ] ; real_T B_6_0_1 [ 2
] ; real_T B_5_0_1 ; real_T B_4_0_1 [ 2 ] ; real_T B_3_0_1 [ 2 ] ; real_T
B_2_0_1 [ 2 ] ; real_T B_1_0_1 [ 2 ] ; real_T B_0_0_1 [ 2 ] ; uint8_T
B_8_18_0_b ; uint8_T B_8_21_0_p ; uint8_T B_8_53_0 ; char_T pad_B_8_53_0 [ 5
] ; } B_Copy_of_linkleg_trajectory_contact_T ; typedef struct { real_T
Delay3_DSTATE ; real_T Delay2_DSTATE ; real_T Delay_DSTATE [ 2 ] ; real_T
Delay1_DSTATE [ 2 ] ; real_T Delay_DSTATE_b [ 2 ] ; real_T Delay1_DSTATE_a [
4 ] ; real_T Delay3_DSTATE_k ; real_T Delay2_DSTATE_o ; real_T Delay_DSTATE_f
[ 2 ] ; real_T Delay1_DSTATE_p [ 2 ] ; real_T Delay1_DSTATE_a4 [ 2 ] ; real_T
Delay_DSTATE_a [ 4 ] ; real_T Delay1_DSTATE_b [ 2 ] ; real_T Delay_DSTATE_d [
4 ] ; real_T Filter_DSTATE ; real_T Integrator_DSTATE ; real_T
Filter_DSTATE_g ; real_T Integrator_DSTATE_b ; real_T INTERNAL_1_1_1_Discrete
[ 2 ] ; real_T INTERNAL_2_1_1_Discrete [ 2 ] ; real_T INPUT_1_1_1_Discrete [
2 ] ; real_T INPUT_2_1_1_Discrete [ 2 ] ; real_T STATE_1_Discrete ; real_T
OUTPUT_1_0_Discrete ; real_T STATE_3_Discrete ; real_T OUTPUT_3_0_Discrete ;
real_T STATE_2_Discrete ; real_T OUTPUT_2_0_Discrete ; real_T
OUTPUT_1_1_Discrete ; real_T Initialize ; struct { real_T modelTStart ; }
TransportDelay_RWORK ; struct { real_T modelTStart ; } TransportDelay1_RWORK
; struct { real_T modelTStart ; } TransportDelay_RWORK_f ; struct { real_T
modelTStart ; } TransportDelay1_RWORK_d ; struct { real_T modelTStart ; }
TransportDelay1_RWORK_j ; struct { real_T modelTStart ; }
TransportDelay_RWORK_c ; void * STATE_1_Simulator ; void * STATE_1_SimData ;
void * STATE_1_DiagMgr ; void * STATE_1_ZcLogger ; void * STATE_1_TsInfo ;
void * OUTPUT_1_0_Simulator ; void * OUTPUT_1_0_SimData ; void *
OUTPUT_1_0_DiagMgr ; void * OUTPUT_1_0_ZcLogger ; void * OUTPUT_1_0_TsInfo ;
struct { void * AQHandles ; }
TAQSigLogging_InsertedFor_MotorPose_to_ThetaBeta_at_outport_0_PWORK ; struct
{ void * AQHandles ; }
TAQSigLogging_InsertedFor_MotorPose_to_ThetaBeta_at_outport_1_PWORK ; struct
{ void * AQHandles ; }
TAQSigLogging_InsertedFor_CompareToConstant1_at_outport_0_PWORK ; struct {
void * AQHandles ; }
TAQSigLogging_InsertedFor_CompareToConstant2_at_outport_0_PWORK ; struct {
void * AQHandles ; }
TAQSigLogging_InsertedFor_Initialize_Flag2_at_outport_0_PWORK ; struct { void
* AQHandles ; } TAQSigLogging_InsertedFor_Initialize_Flag3_at_outport_0_PWORK
; struct { void * TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK ; struct { void
* TUbufferPtrs [ 2 ] ; } TransportDelay1_PWORK ; struct { void * TUbufferPtrs
[ 2 ] ; } TransportDelay_PWORK_n ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay1_PWORK_k ; struct { void * TUbufferPtrs [ 2 ] ; }
TransportDelay1_PWORK_j ; struct { void * AQHandles ; }
TAQSigLogging_InsertedFor_Switch4_at_outport_0_PWORK ; struct { void *
AQHandles ; } TAQSigLogging_InsertedFor_Switch5_at_outport_0_PWORK ; struct {
void * AQHandles ; } TAQSigLogging_InsertedFor_SFunction_at_outport_0_PWORK ;
struct { void * AQHandles ; }
TAQSigLogging_InsertedFor_Motortotheta_beta_at_outport_0_PWORK ; struct {
void * AQHandles ; }
TAQSigLogging_InsertedFor_TransportDelay1_at_outport_0_PWORK ; struct { void
* AQHandles ; } TAQSigLogging_InsertedFor_TransportDelay_at_outport_0_PWORK ;
struct { void * TUbufferPtrs [ 4 ] ; } TransportDelay_PWORK_l ; void *
STATE_3_Simulator ; void * STATE_3_SimData ; void * STATE_3_DiagMgr ; void *
STATE_3_ZcLogger ; void * STATE_3_TsInfo ; void * OUTPUT_3_0_Simulator ; void
* OUTPUT_3_0_SimData ; void * OUTPUT_3_0_DiagMgr ; void * OUTPUT_3_0_ZcLogger
; void * OUTPUT_3_0_TsInfo ; void * STATE_2_Simulator ; void *
STATE_2_SimData ; void * STATE_2_DiagMgr ; void * STATE_2_ZcLogger ; void *
STATE_2_TsInfo ; void * OUTPUT_2_0_Simulator ; void * OUTPUT_2_0_SimData ;
void * OUTPUT_2_0_DiagMgr ; void * OUTPUT_2_0_ZcLogger ; void *
OUTPUT_2_0_TsInfo ; struct { void * AQHandles ; }
TAQSigLogging_InsertedFor_PSSimulinkConverter1_at_outport_0_PWORK ; struct {
void * AQHandles ; } TAQSigLogging_InsertedFor_t_at_outport_0_PWORK ; void *
OUTPUT_1_1_Simulator ; void * OUTPUT_1_1_SimData ; void * OUTPUT_1_1_DiagMgr
; void * OUTPUT_1_1_ZcLogger ; void * OUTPUT_1_1_TsInfo ; void * Scope_PWORK
; void * Scope_PWORK_o ; struct { void * AQHandles ; }
TAQSigLogging_InsertedFor_PSSimulinkConverter2_at_outport_0_PWORK ; struct {
void * AQHandles ; }
TAQSigLogging_InsertedFor_PSSimulinkConverter_at_outport_0_PWORK ; void *
SINK_1_RtwLogger ; void * SINK_1_RtwLogBuffer ; void *
SINK_1_RtwLogFcnManager ; void * SINK_2_RtwLogger ; void *
SINK_2_RtwLogBuffer ; void * SINK_2_RtwLogFcnManager ; void *
SINK_3_RtwLogger ; void * SINK_3_RtwLogBuffer ; void *
SINK_3_RtwLogFcnManager ; void * DataStoreMemory_PWORK ; void *
RTP_2_RtpManager ; void * RTP_3_RtpManager ; int32_T dsmIdx ; int32_T
Motortotheta_beta1_sysIdxToRun ; int32_T Motortotheta_beta_sysIdxToRun ;
int32_T MATLABFunction_sysIdxToRun ; int32_T Motortotheta_beta_sysIdxToRun_m
; int32_T MATLABFunction2_sysIdxToRun ; int32_T MATLABFunction_sysIdxToRun_i
; int32_T IK1_sysIdxToRun ; int32_T IK_sysIdxToRun ; int_T STATE_1_Modes ;
int_T OUTPUT_1_0_Modes ; struct { int_T Tail ; int_T Head ; int_T Last ;
int_T CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay_IWORK ; struct
{ int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay1_IWORK ; struct { int_T Tail ; int_T Head ;
int_T Last ; int_T CircularBufSize ; int_T MaxNewBufSize ; }
TransportDelay_IWORK_p ; struct { int_T Tail ; int_T Head ; int_T Last ;
int_T CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay1_IWORK_a ;
struct { int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay1_IWORK_i ; struct { int_T Tail [ 2 ] ; int_T
Head [ 2 ] ; int_T Last [ 2 ] ; int_T CircularBufSize [ 2 ] ; int_T
MaxNewBufSize ; } TransportDelay_IWORK_m ; int_T STATE_3_Modes ; int_T
OUTPUT_3_0_Modes ; int_T STATE_2_Modes ; int_T OUTPUT_2_0_Modes ; int_T
OUTPUT_1_1_Modes ; int_T Step_MODE ; int_T Saturation_MODE ; int_T
Saturation_MODE_k ; int32_T STATE_3_MASS_MATRIX_PR ; int32_T
STATE_2_MASS_MATRIX_PR ; boolean_T STATE_1_FirstOutput ; boolean_T
OUTPUT_1_0_FirstOutput ; boolean_T Compare_Mode ; boolean_T Compare_Mode_c ;
boolean_T Compare_Mode_a ; boolean_T Compare_Mode_l ; boolean_T
STATE_3_FirstOutput ; boolean_T OUTPUT_3_0_FirstOutput ; boolean_T
STATE_2_FirstOutput ; boolean_T OUTPUT_2_0_FirstOutput ; boolean_T
OUTPUT_1_1_FirstOutput ; boolean_T RTP_2_SetParametersNeeded ; boolean_T
RTP_3_SetParametersNeeded ; char_T pad_RTP_3_SetParametersNeeded [ 7 ] ; }
DW_Copy_of_linkleg_trajectory_contact_T ; typedef struct { real_T
Copy_of_linkleg_trajectory_contactL_jointL_MotorRzq [ 44 ] ; real_T
Copy_of_linkleg_trajectory_contactL_jointRotational_Frictiont ; real_T
Copy_of_linkleg_trajectory_contactR_jointRotational_Frictiont ; }
X_Copy_of_linkleg_trajectory_contact_T ; typedef struct { real_T
Copy_of_linkleg_trajectory_contactL_jointL_MotorRzq [ 44 ] ; real_T
Copy_of_linkleg_trajectory_contactL_jointRotational_Frictiont ; real_T
Copy_of_linkleg_trajectory_contactR_jointRotational_Frictiont ; }
XDot_Copy_of_linkleg_trajectory_contact_T ; typedef struct { boolean_T
Copy_of_linkleg_trajectory_contactL_jointL_MotorRzq [ 44 ] ; boolean_T
Copy_of_linkleg_trajectory_contactL_jointRotational_Frictiont ; boolean_T
Copy_of_linkleg_trajectory_contactR_jointRotational_Frictiont ; }
XDis_Copy_of_linkleg_trajectory_contact_T ; typedef struct { real_T
Copy_of_linkleg_trajectory_contactL_jointL_MotorRzq [ 44 ] ; real_T
Copy_of_linkleg_trajectory_contactL_jointRotational_Frictiont ; real_T
Copy_of_linkleg_trajectory_contactR_jointRotational_Frictiont ; }
CStateAbsTol_Copy_of_linkleg_trajectory_contact_T ; typedef struct { real_T
Copy_of_linkleg_trajectory_contactL_jointL_MotorRzq [ 44 ] ; real_T
Copy_of_linkleg_trajectory_contactL_jointRotational_Frictiont ; real_T
Copy_of_linkleg_trajectory_contactR_jointRotational_Frictiont ; }
CXPtMin_Copy_of_linkleg_trajectory_contact_T ; typedef struct { real_T
Copy_of_linkleg_trajectory_contactL_jointL_MotorRzq [ 44 ] ; real_T
Copy_of_linkleg_trajectory_contactL_jointRotational_Frictiont ; real_T
Copy_of_linkleg_trajectory_contactR_jointRotational_Frictiont ; }
CXPtMax_Copy_of_linkleg_trajectory_contact_T ; typedef struct { real_T
Compare_RelopInput_ZC ; real_T Compare_RelopInput_ZC_g ; real_T
Step_StepTime_ZC ; real_T Compare_RelopInput_ZC_h ; real_T
Compare_RelopInput_ZC_o ; real_T Saturation_UprLim_ZC ; real_T
Saturation_LwrLim_ZC ; real_T Saturation_UprLim_ZC_n ; real_T
Saturation_LwrLim_ZC_b ; } ZCV_Copy_of_linkleg_trajectory_contact_T ; typedef
struct { ZCSigState Compare_RelopInput_ZCE ; ZCSigState
Compare_RelopInput_ZCE_o ; ZCSigState Step_StepTime_ZCE ; ZCSigState
Compare_RelopInput_ZCE_h ; ZCSigState Compare_RelopInput_ZCE_l ; ZCSigState
Saturation_UprLim_ZCE ; ZCSigState Saturation_LwrLim_ZCE ; ZCSigState
Saturation_UprLim_ZCE_e ; ZCSigState Saturation_LwrLim_ZCE_p ; }
PrevZCX_Copy_of_linkleg_trajectory_contact_T ; typedef struct { int_T ir [ 46
] ; int_T jc [ 47 ] ; real_T pr [ 46 ] ; }
MassMatrix_Copy_of_linkleg_trajectory_contact_T ; struct
P_Copy_of_linkleg_trajectory_contact_T_ { real_T P_0 ; real_T P_1 ; real_T
P_2 ; real_T P_3 ; real_T P_4 ; real_T P_5 ; real_T P_6 ; real_T P_7 ; real_T
P_8 ; real_T P_9 ; real_T P_10 ; real_T P_11 ; real_T P_12 ; real_T P_13 ;
real_T P_14 ; real_T P_15 ; real_T P_16 ; real_T P_17 ; real_T P_18 ; real_T
P_19 ; real_T P_20 ; real_T P_21 ; real_T P_22 ; real_T P_23 ; real_T P_24 ;
real_T P_25 ; real_T P_26 ; real_T P_27 ; real_T P_28 ; real_T P_29 ; real_T
P_30 ; real_T P_31 ; real_T P_32 ; real_T P_33 ; real_T P_34 ; real_T P_35 ;
real_T P_36 ; real_T P_37 ; real_T P_38 ; real_T P_39 ; real_T P_40 ; real_T
P_41 ; real_T P_42 ; real_T P_43 ; real_T P_44 ; real_T P_45 ; real_T P_46 ;
real_T P_47 ; real_T P_48 ; real_T P_49 ; real_T P_50 ; real_T P_51 ; real_T
P_52 ; real_T P_53 ; real_T P_54 ; real_T P_55 ; real_T P_56 ; real_T P_57 ;
real_T P_58 ; real_T P_59 [ 2 ] ; real_T P_60 ; real_T P_61 ; real_T P_62 [ 2
] ; real_T P_63 ; real_T P_64 ; real_T P_65 [ 2 ] ; real_T P_66 [ 2 ] ;
real_T P_67 ; real_T P_68 ; real_T P_69 ; real_T P_70 ; real_T P_71 ; real_T
P_72 ; } ; extern P_Copy_of_linkleg_trajectory_contact_T
Copy_of_linkleg_trajectory_contact_rtDefaultP ;
#endif
