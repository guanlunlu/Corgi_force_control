#ifndef RTW_HEADER_pb_linkleg_trajectory_contact_acc_h_
#define RTW_HEADER_pb_linkleg_trajectory_contact_acc_h_
#ifndef pb_linkleg_trajectory_contact_acc_COMMON_INCLUDES_
#define pb_linkleg_trajectory_contact_acc_COMMON_INCLUDES_
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
#include "pb_linkleg_trajectory_contact_acc_types.h"
#include <stddef.h>
#include <float.h>
#include "mwmathutil.h"
#include "rt_defines.h"
#include "rt_nonfinite.h"
typedef struct { real_T B_7_0_0 ; real_T B_7_1_0 ; real_T B_7_3_0 ; real_T
B_7_4_0 ; real_T B_7_6_0 ; real_T B_7_9_0 ; real_T B_7_10_0 [ 4 ] ; real_T
B_7_11_0 ; real_T B_7_12_0 ; real_T B_7_15_0 ; real_T B_7_16_0 [ 4 ] ; real_T
B_7_17_0 [ 40 ] ; real_T B_7_18_0 [ 23 ] ; real_T B_7_34_0 ; real_T B_7_35_0
; real_T B_7_0_0_m ; real_T B_7_2_0 ; real_T B_7_3_0_c ; real_T B_7_4_0_k ;
real_T B_7_6_0_c ; real_T B_7_10_0_b ; real_T B_7_13_0 ; real_T B_7_14_0 ;
real_T B_7_15_0_p ; real_T B_7_16_0_c ; real_T B_7_17_0_f ; real_T B_6_1_0 ;
real_T B_5_0_0 ; real_T B_5_1_0 ; real_T B_5_2_0 ; real_T B_4_1_0 ; real_T
B_3_0_0 ; real_T B_3_1_0 ; real_T B_3_2_0 ; real_T B_2_0_1 [ 2 ] ; real_T
B_1_0_1 [ 2 ] ; real_T B_0_0_1 ; uint8_T B_7_2_0_g ; boolean_T B_7_5_0 ;
char_T pad_B_7_5_0 [ 6 ] ; } B_pb_linkleg_trajectory_contact_T ; typedef
struct { real_T DiscreteTimeIntegrator1_DSTATE ; real_T INPUT_1_1_1_Discrete
; real_T INPUT_1_1_1_FirstOutput ; real_T DiscreteTimeIntegrator_DSTATE ;
real_T INPUT_2_1_1_Discrete ; real_T INPUT_2_1_1_FirstOutput ; real_T
STATE_1_Discrete ; real_T OUTPUT_1_0_Discrete ; real_T Initialize ; struct {
real_T modelTStart ; } TransportDelay_RWORK ; struct { real_T modelTStart ; }
TransportDelay1_RWORK ; void * STATE_1_Simulator ; void * STATE_1_SimData ;
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
TAQSigLogging_InsertedFor_DiscreteTimeIntegrator_at_outport_0_PWORK ; struct
{ void * AQHandles ; }
TAQSigLogging_InsertedFor_Initialize_Flag_at_outport_0_PWORK ; struct { void
* TUbufferPtrs [ 2 ] ; } TransportDelay_PWORK ; struct { void * TUbufferPtrs
[ 2 ] ; } TransportDelay1_PWORK ; struct { void * AQHandles ; }
TAQSigLogging_InsertedFor_initialize_switch_at_outport_0_PWORK ; struct {
void * AQHandles ; }
TAQSigLogging_InsertedFor_initialize_switch_at_outport_1_PWORK ; void *
Scope_PWORK ; void * Scope_PWORK_o ; struct { void * AQHandles ; }
TAQSigLogging_InsertedFor_PSSimulinkConverter2_at_outport_0_PWORK ; struct {
void * AQHandles ; }
TAQSigLogging_InsertedFor_PSSimulinkConverter_at_outport_0_PWORK ; void *
SINK_1_RtwLogger ; void * SINK_1_RtwLogBuffer ; void *
SINK_1_RtwLogFcnManager ; void * DataStoreMemory_PWORK ; int32_T dsmIdx ;
int32_T TmpAtomicSubsysAtSwitch5Inport3_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitch2Inport3_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitch4Inport3_sysIdxToRun ; int32_T
TmpAtomicSubsysAtSwitch3Inport3_sysIdxToRun ; int32_T
Motortotheta_beta_sysIdxToRun ; int32_T Motortotheta_beta_sysIdxToRun_o ;
int32_T MATLABFunction_sysIdxToRun ; int_T STATE_1_Modes ; int_T
OUTPUT_1_0_Modes ; struct { int_T Tail ; int_T Head ; int_T Last ; int_T
CircularBufSize ; int_T MaxNewBufSize ; } TransportDelay_IWORK ; struct {
int_T Tail ; int_T Head ; int_T Last ; int_T CircularBufSize ; int_T
MaxNewBufSize ; } TransportDelay1_IWORK ; int_T Step_MODE ; int_T Step_MODE_h
; boolean_T Compare_Mode ; boolean_T Compare_Mode_l ; boolean_T
STATE_1_FirstOutput ; boolean_T OUTPUT_1_0_FirstOutput ; char_T
pad_OUTPUT_1_0_FirstOutput [ 4 ] ; } DW_pb_linkleg_trajectory_contact_T ;
typedef struct { real_T
 pb_linkleg_trajectory_contactL_jointSimulink_PS_ConverteroutputFiltered_2337621977_0
[ 2 ] ; real_T
 pb_linkleg_trajectory_contactR_jointSimulink_PS_ConverteroutputFiltered_3438624009_0
[ 2 ] ; real_T pb_linkleg_trajectory_contactSubsystem2L_joint_AL_jointARzq [
40 ] ; } X_pb_linkleg_trajectory_contact_T ; typedef struct { real_T
 pb_linkleg_trajectory_contactL_jointSimulink_PS_ConverteroutputFiltered_2337621977_0
[ 2 ] ; real_T
 pb_linkleg_trajectory_contactR_jointSimulink_PS_ConverteroutputFiltered_3438624009_0
[ 2 ] ; real_T pb_linkleg_trajectory_contactSubsystem2L_joint_AL_jointARzq [
40 ] ; } XDot_pb_linkleg_trajectory_contact_T ; typedef struct { boolean_T
 pb_linkleg_trajectory_contactL_jointSimulink_PS_ConverteroutputFiltered_2337621977_0
[ 2 ] ; boolean_T
 pb_linkleg_trajectory_contactR_jointSimulink_PS_ConverteroutputFiltered_3438624009_0
[ 2 ] ; boolean_T pb_linkleg_trajectory_contactSubsystem2L_joint_AL_jointARzq
[ 40 ] ; } XDis_pb_linkleg_trajectory_contact_T ; typedef struct { real_T
 pb_linkleg_trajectory_contactL_jointSimulink_PS_ConverteroutputFiltered_2337621977_0
[ 2 ] ; real_T
 pb_linkleg_trajectory_contactR_jointSimulink_PS_ConverteroutputFiltered_3438624009_0
[ 2 ] ; real_T pb_linkleg_trajectory_contactSubsystem2L_joint_AL_jointARzq [
40 ] ; } CStateAbsTol_pb_linkleg_trajectory_contact_T ; typedef struct {
real_T
 pb_linkleg_trajectory_contactL_jointSimulink_PS_ConverteroutputFiltered_2337621977_0
[ 2 ] ; real_T
 pb_linkleg_trajectory_contactR_jointSimulink_PS_ConverteroutputFiltered_3438624009_0
[ 2 ] ; real_T pb_linkleg_trajectory_contactSubsystem2L_joint_AL_jointARzq [
40 ] ; } CXPtMin_pb_linkleg_trajectory_contact_T ; typedef struct { real_T
 pb_linkleg_trajectory_contactL_jointSimulink_PS_ConverteroutputFiltered_2337621977_0
[ 2 ] ; real_T
 pb_linkleg_trajectory_contactR_jointSimulink_PS_ConverteroutputFiltered_3438624009_0
[ 2 ] ; real_T pb_linkleg_trajectory_contactSubsystem2L_joint_AL_jointARzq [
40 ] ; } CXPtMax_pb_linkleg_trajectory_contact_T ; typedef struct { real_T
Compare_RelopInput_ZC ; real_T Compare_RelopInput_ZC_o ; real_T
Step_StepTime_ZC ; real_T Step_StepTime_ZC_g ; }
ZCV_pb_linkleg_trajectory_contact_T ; typedef struct { ZCSigState
Compare_RelopInput_ZCE ; ZCSigState Compare_RelopInput_ZCE_l ; ZCSigState
Step_StepTime_ZCE ; ZCSigState Step_StepTime_ZCE_h ; }
PrevZCX_pb_linkleg_trajectory_contact_T ; struct
P_pb_linkleg_trajectory_contact_T_ { real_T P_0 ; real_T P_1 ; real_T P_2 ;
real_T P_3 ; real_T P_4 ; real_T P_5 ; real_T P_6 ; real_T P_7 ; real_T P_8 ;
real_T P_9 ; real_T P_10 ; real_T P_11 ; real_T P_12 ; real_T P_13 ; real_T
P_14 ; real_T P_15 ; real_T P_16 ; real_T P_17 ; real_T P_18 ; real_T P_19 ;
real_T P_20 ; real_T P_21 ; real_T P_22 ; real_T P_23 ; } ; extern
P_pb_linkleg_trajectory_contact_T pb_linkleg_trajectory_contact_rtDefaultP ;
#endif
