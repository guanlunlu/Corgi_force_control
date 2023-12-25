#include "pb_linkleg_trajectory_contact_acc.h"
#include "rtwtypes.h"
#include "mwmathutil.h"
#include "pb_linkleg_trajectory_contact_acc_private.h"
#include "multiword_types.h"
#include <stdio.h>
#include "slexec_vm_simstruct_bridge.h"
#include "slexec_vm_zc_functions.h"
#include "slexec_vm_lookup_functions.h"
#include "slsv_diagnostic_codegen_c_api.h"
#include "simtarget/slSimTgtMdlrefSfcnBridge.h"
#include "simstruc.h"
#include "fixedpoint.h"
#define CodeFormat S-Function
#define AccDefine1 Accelerator_S-Function
#include "simtarget/slAccSfcnBridge.h"
#ifndef __RTW_UTFREE__  
extern void * utMalloc ( size_t ) ; extern void utFree ( void * ) ;
#endif
boolean_T pb_linkleg_trajectory_contact_acc_rt_TDelayUpdateTailOrGrowBuf (
int_T * bufSzPtr , int_T * tailPtr , int_T * headPtr , int_T * lastPtr ,
real_T tMinusDelay , real_T * * uBufPtr , boolean_T isfixedbuf , boolean_T
istransportdelay , int_T * maxNewBufSzPtr ) { int_T testIdx ; int_T tail = *
tailPtr ; int_T bufSz = * bufSzPtr ; real_T * tBuf = * uBufPtr + bufSz ;
real_T * xBuf = ( NULL ) ; int_T numBuffer = 2 ; if ( istransportdelay ) {
numBuffer = 3 ; xBuf = * uBufPtr + 2 * bufSz ; } testIdx = ( tail < ( bufSz -
1 ) ) ? ( tail + 1 ) : 0 ; if ( ( tMinusDelay <= tBuf [ testIdx ] ) && !
isfixedbuf ) { int_T j ; real_T * tempT ; real_T * tempU ; real_T * tempX = (
NULL ) ; real_T * uBuf = * uBufPtr ; int_T newBufSz = bufSz + 1024 ; if (
newBufSz > * maxNewBufSzPtr ) { * maxNewBufSzPtr = newBufSz ; } tempU = (
real_T * ) utMalloc ( numBuffer * newBufSz * sizeof ( real_T ) ) ; if ( tempU
== ( NULL ) ) { return ( false ) ; } tempT = tempU + newBufSz ; if (
istransportdelay ) tempX = tempT + newBufSz ; for ( j = tail ; j < bufSz ; j
++ ) { tempT [ j - tail ] = tBuf [ j ] ; tempU [ j - tail ] = uBuf [ j ] ; if
( istransportdelay ) tempX [ j - tail ] = xBuf [ j ] ; } for ( j = 0 ; j <
tail ; j ++ ) { tempT [ j + bufSz - tail ] = tBuf [ j ] ; tempU [ j + bufSz -
tail ] = uBuf [ j ] ; if ( istransportdelay ) tempX [ j + bufSz - tail ] =
xBuf [ j ] ; } if ( * lastPtr > tail ) { * lastPtr -= tail ; } else { *
lastPtr += ( bufSz - tail ) ; } * tailPtr = 0 ; * headPtr = bufSz ; utFree (
uBuf ) ; * bufSzPtr = newBufSz ; * uBufPtr = tempU ; } else { * tailPtr =
testIdx ; } return ( true ) ; } real_T
pb_linkleg_trajectory_contact_acc_rt_TDelayInterpolate ( real_T tMinusDelay ,
real_T tStart , real_T * uBuf , int_T bufSz , int_T * lastIdx , int_T
oldestIdx , int_T newIdx , real_T initOutput , boolean_T discrete , boolean_T
minorStepAndTAtLastMajorOutput ) { int_T i ; real_T yout , t1 , t2 , u1 , u2
; real_T * tBuf = uBuf + bufSz ; if ( ( newIdx == 0 ) && ( oldestIdx == 0 )
&& ( tMinusDelay > tStart ) ) return initOutput ; if ( tMinusDelay <= tStart
) return initOutput ; if ( ( tMinusDelay <= tBuf [ oldestIdx ] ) ) { if (
discrete ) { return ( uBuf [ oldestIdx ] ) ; } else { int_T tempIdx =
oldestIdx + 1 ; if ( oldestIdx == bufSz - 1 ) tempIdx = 0 ; t1 = tBuf [
oldestIdx ] ; t2 = tBuf [ tempIdx ] ; u1 = uBuf [ oldestIdx ] ; u2 = uBuf [
tempIdx ] ; if ( t2 == t1 ) { if ( tMinusDelay >= t2 ) { yout = u2 ; } else {
yout = u1 ; } } else { real_T f1 = ( t2 - tMinusDelay ) / ( t2 - t1 ) ;
real_T f2 = 1.0 - f1 ; yout = f1 * u1 + f2 * u2 ; } return yout ; } } if (
minorStepAndTAtLastMajorOutput ) { if ( newIdx != 0 ) { if ( * lastIdx ==
newIdx ) { ( * lastIdx ) -- ; } newIdx -- ; } else { if ( * lastIdx == newIdx
) { * lastIdx = bufSz - 1 ; } newIdx = bufSz - 1 ; } } i = * lastIdx ; if (
tBuf [ i ] < tMinusDelay ) { while ( tBuf [ i ] < tMinusDelay ) { if ( i ==
newIdx ) break ; i = ( i < ( bufSz - 1 ) ) ? ( i + 1 ) : 0 ; } } else { while
( tBuf [ i ] >= tMinusDelay ) { i = ( i > 0 ) ? i - 1 : ( bufSz - 1 ) ; } i =
( i < ( bufSz - 1 ) ) ? ( i + 1 ) : 0 ; } * lastIdx = i ; if ( discrete ) {
double tempEps = ( DBL_EPSILON ) * 128.0 ; double localEps = tempEps *
muDoubleScalarAbs ( tBuf [ i ] ) ; if ( tempEps > localEps ) { localEps =
tempEps ; } localEps = localEps / 2.0 ; if ( tMinusDelay >= ( tBuf [ i ] -
localEps ) ) { yout = uBuf [ i ] ; } else { if ( i == 0 ) { yout = uBuf [
bufSz - 1 ] ; } else { yout = uBuf [ i - 1 ] ; } } } else { if ( i == 0 ) {
t1 = tBuf [ bufSz - 1 ] ; u1 = uBuf [ bufSz - 1 ] ; } else { t1 = tBuf [ i -
1 ] ; u1 = uBuf [ i - 1 ] ; } t2 = tBuf [ i ] ; u2 = uBuf [ i ] ; if ( t2 ==
t1 ) { if ( tMinusDelay >= t2 ) { yout = u2 ; } else { yout = u1 ; } } else {
real_T f1 = ( t2 - tMinusDelay ) / ( t2 - t1 ) ; real_T f2 = 1.0 - f1 ; yout
= f1 * u1 + f2 * u2 ; } } return ( yout ) ; } void rt_ssGetBlockPath (
SimStruct * S , int_T sysIdx , int_T blkIdx , char_T * * path ) {
_ssGetBlockPath ( S , sysIdx , blkIdx , path ) ; } void rt_ssSet_slErrMsg (
void * S , void * diag ) { SimStruct * castedS = ( SimStruct * ) S ; if ( !
_ssIsErrorStatusAslErrMsg ( castedS ) ) { _ssSet_slErrMsg ( castedS , diag )
; } else { _ssDiscardDiagnostic ( castedS , diag ) ; } } void
rt_ssReportDiagnosticAsWarning ( void * S , void * diag ) {
_ssReportDiagnosticAsWarning ( ( SimStruct * ) S , diag ) ; } void
rt_ssReportDiagnosticAsInfo ( void * S , void * diag ) {
_ssReportDiagnosticAsInfo ( ( SimStruct * ) S , diag ) ; } static void
mdlOutputs ( SimStruct * S , int_T tid ) { B_pb_linkleg_trajectory_contact_T
* _rtB ; DW_pb_linkleg_trajectory_contact_T * _rtDW ;
P_pb_linkleg_trajectory_contact_T * _rtP ; X_pb_linkleg_trajectory_contact_T
* _rtX ; int32_T isHit ; _rtDW = ( ( DW_pb_linkleg_trajectory_contact_T * )
ssGetRootDWork ( S ) ) ; _rtX = ( ( X_pb_linkleg_trajectory_contact_T * )
ssGetContStates ( S ) ) ; _rtP = ( ( P_pb_linkleg_trajectory_contact_T * )
ssGetModelRtp ( S ) ) ; _rtB = ( ( B_pb_linkleg_trajectory_contact_T * )
_ssGetModelBlockIO ( S ) ) ; vm_ReadLocalDSMNoIdx ( S , _rtDW -> dsmIdx , (
char_T * )
 "pb_linkleg_trajectory_contact/Controller/initialize_switch/Initialize_/Data Store Read1"
, 0 ) ; _rtB -> B_7_0_0 = _rtDW -> Initialize ; vm_ReadLocalDSMNoIdx ( S ,
_rtDW -> dsmIdx , ( char_T * )
"pb_linkleg_trajectory_contact/Controller/initialize_switch/Initialize_Flag"
, 0 ) ; _rtB -> B_7_1_0 = _rtDW -> Initialize ; isHit = ssIsSampleHit ( S , 1
, 0 ) ; if ( isHit != 0 ) { if ( ssIsModeUpdateTimeStep ( S ) ) { _rtDW ->
Compare_Mode = ( _rtB -> B_7_1_0 == _rtB -> B_7_3_0_c ) ; } _rtB -> B_7_2_0_g
= _rtDW -> Compare_Mode ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit
!= 0 ) { _rtB -> B_7_3_0 = _rtDW -> DiscreteTimeIntegrator1_DSTATE ; }
vm_ReadLocalDSMNoIdx ( S , _rtDW -> dsmIdx , ( char_T * )
"pb_linkleg_trajectory_contact/Controller/initialize_switch/Initialize_Flag1"
, 0 ) ; _rtB -> B_7_4_0 = _rtDW -> Initialize ; isHit = ssIsSampleHit ( S , 1
, 0 ) ; if ( isHit != 0 ) { if ( ssIsModeUpdateTimeStep ( S ) ) { _rtDW ->
Compare_Mode_l = ( _rtB -> B_7_4_0 == _rtB -> B_7_2_0 ) ; } _rtB -> B_7_5_0 =
_rtDW -> Compare_Mode_l ; _rtDW -> Step_MODE = ( ssGetTaskTime ( S , 1 ) >=
_rtP -> P_1 ) ; if ( _rtDW -> Step_MODE == 1 ) { _rtB -> B_7_6_0 = _rtP ->
P_3 ; } else { _rtB -> B_7_6_0 = _rtP -> P_2 ; } } if ( _rtB -> B_7_2_0_g !=
0 ) { _rtB -> B_7_9_0 = 0.0 ; } else { if ( _rtB -> B_7_5_0 ) { _rtB ->
B_6_1_0 = _rtB -> B_7_3_0 ; } else { _rtB -> B_5_0_0 = ssGetT ( S ) - _rtB ->
B_7_16_0_c ; _rtB -> B_5_1_0 = _rtB -> B_7_6_0 * _rtB -> B_5_0_0 ; _rtB ->
B_5_2_0 = _rtB -> B_5_1_0 + _rtB -> B_7_17_0_f ; _rtB -> B_6_1_0 = _rtB ->
B_5_2_0 ; } _rtB -> B_7_9_0 = _rtB -> B_6_1_0 ; } if ( _rtDW ->
INPUT_1_1_1_FirstOutput == 0.0 ) { _rtDW -> INPUT_1_1_1_FirstOutput = 1.0 ;
_rtX ->
 pb_linkleg_trajectory_contactL_jointSimulink_PS_ConverteroutputFiltered_2337621977_0
[ 0 ] = _rtB -> B_7_9_0 ; _rtX ->
 pb_linkleg_trajectory_contactL_jointSimulink_PS_ConverteroutputFiltered_2337621977_0
[ 1 ] = 0.0 ; } _rtB -> B_7_10_0 [ 0 ] = _rtX ->
 pb_linkleg_trajectory_contactL_jointSimulink_PS_ConverteroutputFiltered_2337621977_0
[ 0 ] ; _rtB -> B_7_10_0 [ 1 ] = _rtX ->
 pb_linkleg_trajectory_contactL_jointSimulink_PS_ConverteroutputFiltered_2337621977_0
[ 1 ] ; _rtB -> B_7_10_0 [ 2 ] = ( ( _rtB -> B_7_9_0 - _rtX ->
 pb_linkleg_trajectory_contactL_jointSimulink_PS_ConverteroutputFiltered_2337621977_0
[ 0 ] ) * 1000.0 - 2.0 * _rtX ->
 pb_linkleg_trajectory_contactL_jointSimulink_PS_ConverteroutputFiltered_2337621977_0
[ 1 ] ) * 1000.0 ; _rtB -> B_7_10_0 [ 3 ] = 0.0 ; isHit = ssIsSampleHit ( S ,
2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_7_11_0 = _rtDW ->
DiscreteTimeIntegrator_DSTATE ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if (
isHit != 0 ) { _rtDW -> Step_MODE_h = ( ssGetTaskTime ( S , 1 ) >= _rtP ->
P_5 ) ; if ( _rtDW -> Step_MODE_h == 1 ) { _rtB -> B_7_12_0 = _rtP -> P_7 ; }
else { _rtB -> B_7_12_0 = _rtP -> P_6 ; } } if ( _rtB -> B_7_2_0_g != 0 ) {
_rtB -> B_7_15_0 = 0.0 ; } else { if ( _rtB -> B_7_5_0 ) { _rtB -> B_4_1_0 =
_rtB -> B_7_11_0 ; } else { _rtB -> B_3_0_0 = ssGetT ( S ) - _rtB -> B_7_14_0
; _rtB -> B_3_1_0 = _rtB -> B_7_12_0 * _rtB -> B_3_0_0 ; _rtB -> B_3_2_0 =
_rtB -> B_3_1_0 + _rtB -> B_7_15_0_p ; _rtB -> B_4_1_0 = _rtB -> B_3_2_0 ; }
_rtB -> B_7_15_0 = _rtB -> B_4_1_0 ; } if ( _rtDW -> INPUT_2_1_1_FirstOutput
== 0.0 ) { _rtDW -> INPUT_2_1_1_FirstOutput = 1.0 ; _rtX ->
 pb_linkleg_trajectory_contactR_jointSimulink_PS_ConverteroutputFiltered_3438624009_0
[ 0 ] = _rtB -> B_7_15_0 ; _rtX ->
 pb_linkleg_trajectory_contactR_jointSimulink_PS_ConverteroutputFiltered_3438624009_0
[ 1 ] = 0.0 ; } _rtB -> B_7_16_0 [ 0 ] = _rtX ->
 pb_linkleg_trajectory_contactR_jointSimulink_PS_ConverteroutputFiltered_3438624009_0
[ 0 ] ; _rtB -> B_7_16_0 [ 1 ] = _rtX ->
 pb_linkleg_trajectory_contactR_jointSimulink_PS_ConverteroutputFiltered_3438624009_0
[ 1 ] ; _rtB -> B_7_16_0 [ 2 ] = ( ( _rtB -> B_7_15_0 - _rtX ->
 pb_linkleg_trajectory_contactR_jointSimulink_PS_ConverteroutputFiltered_3438624009_0
[ 0 ] ) * 1000.0 - 2.0 * _rtX ->
 pb_linkleg_trajectory_contactR_jointSimulink_PS_ConverteroutputFiltered_3438624009_0
[ 1 ] ) * 1000.0 ; _rtB -> B_7_16_0 [ 3 ] = 0.0 ; ssCallAccelRunBlock ( S , 7
, 17 , SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 7 , 18 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 2 , 0 , SS_CALL_MDL_OUTPUTS
) ; isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) {
ssCallAccelRunBlock ( S , 1 , 0 , SS_CALL_MDL_OUTPUTS ) ; }
ssCallAccelRunBlock ( S , 0 , 0 , SS_CALL_MDL_OUTPUTS ) ; _rtDW -> Initialize
= _rtB -> B_0_0_1 ; vm_WriteLocalDSMNoIdx ( S , _rtDW -> dsmIdx , ( char_T *
)
 "pb_linkleg_trajectory_contact/Controller/initialize_switch/Initialize_/Data Store Write"
, 0 ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { { if (
_rtDW -> TAQSigLogging_InsertedFor_MotorPose_to_ThetaBeta_at_outport_0_PWORK
. AQHandles && ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_MotorPose_to_ThetaBeta_at_outport_0_PWORK .
AQHandles , ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_2_0_1 [ 0 ] + 0
) ; } } { if ( _rtDW ->
TAQSigLogging_InsertedFor_MotorPose_to_ThetaBeta_at_outport_1_PWORK .
AQHandles && ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_MotorPose_to_ThetaBeta_at_outport_1_PWORK .
AQHandles , ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_2_0_1 [ 1 ] + 0
) ; } } { if ( _rtDW ->
TAQSigLogging_InsertedFor_CompareToConstant1_at_outport_0_PWORK . AQHandles
&& ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_CompareToConstant1_at_outport_0_PWORK . AQHandles ,
ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_7_2_0_g + 0 ) ; } } } isHit
= ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { { if ( _rtDW ->
TAQSigLogging_InsertedFor_DiscreteTimeIntegrator_at_outport_0_PWORK .
AQHandles && ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_DiscreteTimeIntegrator_at_outport_0_PWORK .
AQHandles , ssGetTaskTime ( S , 2 ) , ( char * ) & _rtB -> B_7_11_0 + 0 ) ; }
} } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { { if ( _rtDW ->
TAQSigLogging_InsertedFor_Initialize_Flag_at_outport_0_PWORK . AQHandles &&
ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_Initialize_Flag_at_outport_0_PWORK . AQHandles ,
ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_7_1_0 + 0 ) ; } } } { real_T
* * uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [
0 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP ->
P_8 ; _rtB -> B_7_34_0 =
pb_linkleg_trajectory_contact_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 ,
* uBuffer , _rtDW -> TransportDelay_IWORK . CircularBufSize , & _rtDW ->
TransportDelay_IWORK . Last , _rtDW -> TransportDelay_IWORK . Tail , _rtDW ->
TransportDelay_IWORK . Head , _rtP -> P_9 , 1 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ( * uBuffer + _rtDW -> TransportDelay_IWORK .
CircularBufSize ) [ _rtDW -> TransportDelay_IWORK . Head ] == ssGetT ( S ) )
) ) ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay1_PWORK . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S ) ;
real_T tMinusDelay = simTime - _rtP -> P_10 ; _rtB -> B_7_35_0 =
pb_linkleg_trajectory_contact_acc_rt_TDelayInterpolate ( tMinusDelay , 0.0 ,
* uBuffer , _rtDW -> TransportDelay1_IWORK . CircularBufSize , & _rtDW ->
TransportDelay1_IWORK . Last , _rtDW -> TransportDelay1_IWORK . Tail , _rtDW
-> TransportDelay1_IWORK . Head , _rtP -> P_11 , 1 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ( * uBuffer + _rtDW -> TransportDelay1_IWORK .
CircularBufSize ) [ _rtDW -> TransportDelay1_IWORK . Head ] == ssGetT ( S ) )
) ) ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { { if (
_rtDW -> TAQSigLogging_InsertedFor_initialize_switch_at_outport_0_PWORK .
AQHandles && ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_initialize_switch_at_outport_0_PWORK . AQHandles ,
ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_7_15_0 + 0 ) ; } } { if (
_rtDW -> TAQSigLogging_InsertedFor_initialize_switch_at_outport_1_PWORK .
AQHandles && ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_initialize_switch_at_outport_1_PWORK . AQHandles ,
ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_7_9_0 + 0 ) ; } } }
ssCallAccelRunBlock ( S , 7 , 51 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 7 , 58 , SS_CALL_MDL_OUTPUTS ) ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { { if ( _rtDW ->
TAQSigLogging_InsertedFor_PSSimulinkConverter2_at_outport_0_PWORK . AQHandles
&& ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_PSSimulinkConverter2_at_outport_0_PWORK . AQHandles
, ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_7_18_0 [ 20 ] + 0 ) ; } }
{ if ( _rtDW ->
TAQSigLogging_InsertedFor_PSSimulinkConverter_at_outport_0_PWORK . AQHandles
&& ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_PSSimulinkConverter_at_outport_0_PWORK . AQHandles
, ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_7_18_0 [ 21 ] + 0 ) ; } }
} ssCallAccelRunBlock ( S , 7 , 64 , SS_CALL_MDL_OUTPUTS ) ; UNUSED_PARAMETER
( tid ) ; } static void mdlOutputsTID3 ( SimStruct * S , int_T tid ) {
B_pb_linkleg_trajectory_contact_T * _rtB ; P_pb_linkleg_trajectory_contact_T
* _rtP ; _rtP = ( ( P_pb_linkleg_trajectory_contact_T * ) ssGetModelRtp ( S )
) ; _rtB = ( ( B_pb_linkleg_trajectory_contact_T * ) _ssGetModelBlockIO ( S )
) ; _rtB -> B_7_0_0_m = _rtP -> P_13 ; _rtB -> B_7_2_0 = _rtP -> P_14 ; _rtB
-> B_7_3_0_c = _rtP -> P_15 ; _rtB -> B_7_4_0_k = _rtP -> P_16 ; _rtB ->
B_7_6_0_c = _rtP -> P_18 ; _rtB -> B_7_10_0_b = muDoubleScalarSign ( 0.0 -
_rtB -> B_7_4_0_k ) * _rtP -> P_17 ; _rtB -> B_7_13_0 = muDoubleScalarSign (
0.0 - _rtB -> B_7_6_0_c ) * _rtP -> P_19 ; _rtB -> B_7_14_0 = _rtP -> P_20 ;
_rtB -> B_7_15_0_p = _rtP -> P_21 ; _rtB -> B_7_16_0_c = _rtP -> P_22 ; _rtB
-> B_7_17_0_f = _rtP -> P_23 ; UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) {
B_pb_linkleg_trajectory_contact_T * _rtB ; DW_pb_linkleg_trajectory_contact_T
* _rtDW ; P_pb_linkleg_trajectory_contact_T * _rtP ; int32_T isHit ; _rtDW =
( ( DW_pb_linkleg_trajectory_contact_T * ) ssGetRootDWork ( S ) ) ; _rtP = (
( P_pb_linkleg_trajectory_contact_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_pb_linkleg_trajectory_contact_T * ) _ssGetModelBlockIO ( S ) ) ; isHit =
ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtDW ->
DiscreteTimeIntegrator1_DSTATE += _rtP -> P_0 * _rtB -> B_7_35_0 ; _rtDW ->
DiscreteTimeIntegrator_DSTATE += _rtP -> P_4 * _rtB -> B_7_34_0 ; }
ssCallAccelRunBlock ( S , 7 , 17 , SS_CALL_MDL_UPDATE ) ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 0 ]
; real_T simTime = ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK . Head = ( (
_rtDW -> TransportDelay_IWORK . Head < ( _rtDW -> TransportDelay_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK . Head + 1 ) : 0 )
; if ( _rtDW -> TransportDelay_IWORK . Head == _rtDW -> TransportDelay_IWORK
. Tail ) { if ( !
pb_linkleg_trajectory_contact_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay_IWORK . CircularBufSize , & _rtDW -> TransportDelay_IWORK .
Tail , & _rtDW -> TransportDelay_IWORK . Head , & _rtDW ->
TransportDelay_IWORK . Last , simTime - _rtP -> P_8 , uBuffer , ( boolean_T )
0 , false , & _rtDW -> TransportDelay_IWORK . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
uBuffer + _rtDW -> TransportDelay_IWORK . CircularBufSize ) [ _rtDW ->
TransportDelay_IWORK . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay_IWORK . Head ] = _rtB -> B_7_10_0_b ; } { real_T * * uBuffer =
( real_T * * ) & _rtDW -> TransportDelay1_PWORK . TUbufferPtrs [ 0 ] ; real_T
simTime = ssGetT ( S ) ; _rtDW -> TransportDelay1_IWORK . Head = ( ( _rtDW ->
TransportDelay1_IWORK . Head < ( _rtDW -> TransportDelay1_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay1_IWORK . Head + 1 ) : 0 )
; if ( _rtDW -> TransportDelay1_IWORK . Head == _rtDW ->
TransportDelay1_IWORK . Tail ) { if ( !
pb_linkleg_trajectory_contact_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW ->
TransportDelay1_IWORK . CircularBufSize , & _rtDW -> TransportDelay1_IWORK .
Tail , & _rtDW -> TransportDelay1_IWORK . Head , & _rtDW ->
TransportDelay1_IWORK . Last , simTime - _rtP -> P_10 , uBuffer , ( boolean_T
) 0 , false , & _rtDW -> TransportDelay1_IWORK . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
uBuffer + _rtDW -> TransportDelay1_IWORK . CircularBufSize ) [ _rtDW ->
TransportDelay1_IWORK . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay1_IWORK . Head ] = _rtB -> B_7_13_0 ; } UNUSED_PARAMETER ( tid
) ; }
#define MDL_UPDATE
static void mdlUpdateTID3 ( SimStruct * S , int_T tid ) { UNUSED_PARAMETER (
tid ) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) {
B_pb_linkleg_trajectory_contact_T * _rtB ;
XDot_pb_linkleg_trajectory_contact_T * _rtXdot ;
X_pb_linkleg_trajectory_contact_T * _rtX ; _rtXdot = ( (
XDot_pb_linkleg_trajectory_contact_T * ) ssGetdX ( S ) ) ; _rtX = ( (
X_pb_linkleg_trajectory_contact_T * ) ssGetContStates ( S ) ) ; _rtB = ( (
B_pb_linkleg_trajectory_contact_T * ) _ssGetModelBlockIO ( S ) ) ; _rtXdot ->
 pb_linkleg_trajectory_contactL_jointSimulink_PS_ConverteroutputFiltered_2337621977_0
[ 0 ] = _rtX ->
 pb_linkleg_trajectory_contactL_jointSimulink_PS_ConverteroutputFiltered_2337621977_0
[ 1 ] ; _rtXdot ->
 pb_linkleg_trajectory_contactL_jointSimulink_PS_ConverteroutputFiltered_2337621977_0
[ 1 ] = ( ( _rtB -> B_7_9_0 - _rtX ->
 pb_linkleg_trajectory_contactL_jointSimulink_PS_ConverteroutputFiltered_2337621977_0
[ 0 ] ) * 1000.0 - 2.0 * _rtX ->
 pb_linkleg_trajectory_contactL_jointSimulink_PS_ConverteroutputFiltered_2337621977_0
[ 1 ] ) * 1000.0 ; _rtXdot ->
 pb_linkleg_trajectory_contactR_jointSimulink_PS_ConverteroutputFiltered_3438624009_0
[ 0 ] = _rtX ->
 pb_linkleg_trajectory_contactR_jointSimulink_PS_ConverteroutputFiltered_3438624009_0
[ 1 ] ; _rtXdot ->
 pb_linkleg_trajectory_contactR_jointSimulink_PS_ConverteroutputFiltered_3438624009_0
[ 1 ] = ( ( _rtB -> B_7_15_0 - _rtX ->
 pb_linkleg_trajectory_contactR_jointSimulink_PS_ConverteroutputFiltered_3438624009_0
[ 0 ] ) * 1000.0 - 2.0 * _rtX ->
 pb_linkleg_trajectory_contactR_jointSimulink_PS_ConverteroutputFiltered_3438624009_0
[ 1 ] ) * 1000.0 ; ssCallAccelRunBlock ( S , 7 , 17 , SS_CALL_MDL_DERIVATIVES
) ; }
#define MDL_PROJECTION
static void mdlProjection ( SimStruct * S ) { ssCallAccelRunBlock ( S , 7 ,
17 , SS_CALL_MDL_PROJECTION ) ; }
#define MDL_ZERO_CROSSINGS
static void mdlZeroCrossings ( SimStruct * S ) {
B_pb_linkleg_trajectory_contact_T * _rtB ; P_pb_linkleg_trajectory_contact_T
* _rtP ; ZCV_pb_linkleg_trajectory_contact_T * _rtZCSV ; _rtZCSV = ( (
ZCV_pb_linkleg_trajectory_contact_T * ) ssGetSolverZcSignalVector ( S ) ) ;
_rtP = ( ( P_pb_linkleg_trajectory_contact_T * ) ssGetModelRtp ( S ) ) ; _rtB
= ( ( B_pb_linkleg_trajectory_contact_T * ) _ssGetModelBlockIO ( S ) ) ;
_rtZCSV -> Compare_RelopInput_ZC = _rtB -> B_7_1_0 - _rtB -> B_7_3_0_c ;
_rtZCSV -> Compare_RelopInput_ZC_o = _rtB -> B_7_4_0 - _rtB -> B_7_2_0 ;
_rtZCSV -> Step_StepTime_ZC = ssGetT ( S ) - _rtP -> P_1 ; _rtZCSV ->
Step_StepTime_ZC_g = ssGetT ( S ) - _rtP -> P_5 ; } static void
mdlInitializeSizes ( SimStruct * S ) { ssSetChecksumVal ( S , 0 , 1430800139U
) ; ssSetChecksumVal ( S , 1 , 3919888683U ) ; ssSetChecksumVal ( S , 2 ,
4165798083U ) ; ssSetChecksumVal ( S , 3 , 2239706410U ) ; { mxArray *
slVerStructMat = ( NULL ) ; mxArray * slStrMat = mxCreateString ( "simulink"
) ; char slVerChar [ 10 ] ; int status = mexCallMATLAB ( 1 , & slVerStructMat
, 1 , & slStrMat , "ver" ) ; if ( status == 0 ) { mxArray * slVerMat =
mxGetField ( slVerStructMat , 0 , "Version" ) ; if ( slVerMat == ( NULL ) ) {
status = 1 ; } else { status = mxGetString ( slVerMat , slVerChar , 10 ) ; }
} mxDestroyArray ( slStrMat ) ; mxDestroyArray ( slVerStructMat ) ; if ( (
status == 1 ) || ( strcmp ( slVerChar , "10.6" ) != 0 ) ) { return ; } }
ssSetOptions ( S , SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork (
S ) != ( SLSize ) sizeof ( DW_pb_linkleg_trajectory_contact_T ) ) { static
char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file (%ld vs %lu)." , ( signed long )
ssGetSizeofDWork ( S ) , ( unsigned long ) sizeof (
DW_pb_linkleg_trajectory_contact_T ) ) ; ssSetErrorStatus ( S , msg ) ; } if
( ssGetSizeofGlobalBlockIO ( S ) != ( SLSize ) sizeof (
B_pb_linkleg_trajectory_contact_T ) ) { static char msg [ 256 ] ; sprintf (
msg , "Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file (%ld vs %lu)." , ( signed long )
ssGetSizeofGlobalBlockIO ( S ) , ( unsigned long ) sizeof (
B_pb_linkleg_trajectory_contact_T ) ) ; ssSetErrorStatus ( S , msg ) ; } {
int ssSizeofParams ; ssGetSizeofParams ( S , & ssSizeofParams ) ; if (
ssSizeofParams != sizeof ( P_pb_linkleg_trajectory_contact_T ) ) { static
char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file (%d vs %lu)." , ssSizeofParams , (
unsigned long ) sizeof ( P_pb_linkleg_trajectory_contact_T ) ) ;
ssSetErrorStatus ( S , msg ) ; } } _ssSetModelRtp ( S , ( real_T * ) &
pb_linkleg_trajectory_contact_rtDefaultP ) ; rt_InitInfAndNaN ( sizeof (
real_T ) ) ; } static void mdlInitializeSampleTimes ( SimStruct * S ) { {
SimStruct * childS ; SysOutputFcn * callSysFcns ; childS = ssGetSFunction ( S
, 0 ) ; callSysFcns = ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [
3 + 0 ] = ( SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 1 ) ;
callSysFcns = ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ]
= ( SysOutputFcn ) ( NULL ) ; childS = ssGetSFunction ( S , 2 ) ; callSysFcns
= ssGetCallSystemOutputFcnList ( childS ) ; callSysFcns [ 3 + 0 ] = (
SysOutputFcn ) ( NULL ) ; } slAccRegPrmChangeFcn ( S , mdlOutputsTID3 ) ; }
static void mdlTerminate ( SimStruct * S ) { }
#include "simulink.c"
