#include "Copy_of_linkleg_trajectory_contact_acc.h"
#include "rtwtypes.h"
#include "Copy_of_linkleg_trajectory_contact_acc_private.h"
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
boolean_T Copy_of_linkleg_trajectory_contact_acc_rt_TDelayUpdateTailOrGrowBuf
( int_T * bufSzPtr , int_T * tailPtr , int_T * headPtr , int_T * lastPtr ,
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
Copy_of_linkleg_trajectory_contact_acc_rt_TDelayInterpolate ( real_T
tMinusDelay , real_T tStart , real_T * uBuf , int_T bufSz , int_T * lastIdx ,
int_T oldestIdx , int_T newIdx , real_T initOutput , boolean_T discrete ,
boolean_T minorStepAndTAtLastMajorOutput ) { int_T i ; real_T yout , t1 , t2
, u1 , u2 ; real_T * tBuf = uBuf + bufSz ; if ( ( newIdx == 0 ) && (
oldestIdx == 0 ) && ( tMinusDelay > tStart ) ) return initOutput ; if (
tMinusDelay <= tStart ) return initOutput ; if ( ( tMinusDelay <= tBuf [
oldestIdx ] ) ) { if ( discrete ) { return ( uBuf [ oldestIdx ] ) ; } else {
int_T tempIdx = oldestIdx + 1 ; if ( oldestIdx == bufSz - 1 ) tempIdx = 0 ;
t1 = tBuf [ oldestIdx ] ; t2 = tBuf [ tempIdx ] ; u1 = uBuf [ oldestIdx ] ;
u2 = uBuf [ tempIdx ] ; if ( t2 == t1 ) { if ( tMinusDelay >= t2 ) { yout =
u2 ; } else { yout = u1 ; } } else { real_T f1 = ( t2 - tMinusDelay ) / ( t2
- t1 ) ; real_T f2 = 1.0 - f1 ; yout = f1 * u1 + f2 * u2 ; } return yout ; }
} if ( minorStepAndTAtLastMajorOutput ) { if ( newIdx != 0 ) { if ( * lastIdx
== newIdx ) { ( * lastIdx ) -- ; } newIdx -- ; } else { if ( * lastIdx ==
newIdx ) { * lastIdx = bufSz - 1 ; } newIdx = bufSz - 1 ; } } i = * lastIdx ;
if ( tBuf [ i ] < tMinusDelay ) { while ( tBuf [ i ] < tMinusDelay ) { if ( i
== newIdx ) break ; i = ( i < ( bufSz - 1 ) ) ? ( i + 1 ) : 0 ; } } else {
while ( tBuf [ i ] >= tMinusDelay ) { i = ( i > 0 ) ? i - 1 : ( bufSz - 1 ) ;
} i = ( i < ( bufSz - 1 ) ) ? ( i + 1 ) : 0 ; } * lastIdx = i ; if ( discrete
) { double tempEps = ( DBL_EPSILON ) * 128.0 ; double localEps = tempEps *
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
mdlOutputs ( SimStruct * S , int_T tid ) { real_T B_10_82_0 ; real_T
B_10_84_0 ; B_Copy_of_linkleg_trajectory_contact_T * _rtB ;
DW_Copy_of_linkleg_trajectory_contact_T * _rtDW ;
P_Copy_of_linkleg_trajectory_contact_T * _rtP ; int32_T isHit ; uint8_T
rtb_B_10_18_0 ; uint8_T rtb_B_10_21_0 ; boolean_T rtb_B_10_31_0 ; _rtDW = ( (
DW_Copy_of_linkleg_trajectory_contact_T * ) ssGetRootDWork ( S ) ) ; _rtP = (
( P_Copy_of_linkleg_trajectory_contact_T * ) ssGetModelRtp ( S ) ) ; _rtB = (
( B_Copy_of_linkleg_trajectory_contact_T * ) _ssGetModelBlockIO ( S ) ) ;
vm_ReadLocalDSMNoIdx ( S , _rtDW -> dsmIdx , ( char_T * )
 "Copy_of_linkleg_trajectory_contact/Controller/initialize_switch/Initialize_/Data Store Read1"
, 0 ) ; _rtB -> B_10_0_0 = _rtDW -> Initialize ; ssCallAccelRunBlock ( S , 10
, 1 , SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 10 , 2 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 7 , 0 , SS_CALL_MDL_OUTPUTS
) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) {
ssCallAccelRunBlock ( S , 0 , 0 , SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock
( S , 2 , 0 , SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 6 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; } ssCallAccelRunBlock ( S , 5 , 0 ,
SS_CALL_MDL_OUTPUTS ) ; _rtDW -> Initialize = _rtB -> B_5_0_1 ;
vm_WriteLocalDSMNoIdx ( S , _rtDW -> dsmIdx , ( char_T * )
 "Copy_of_linkleg_trajectory_contact/Controller/initialize_switch/Initialize_/Data Store Write"
, 0 ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { { if (
_rtDW -> TAQSigLogging_InsertedFor_MotorPose_to_ThetaBeta_at_outport_0_PWORK
. AQHandles && ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_MotorPose_to_ThetaBeta_at_outport_0_PWORK .
AQHandles , ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_7_0_1 [ 0 ] + 0
) ; } } { if ( _rtDW ->
TAQSigLogging_InsertedFor_MotorPose_to_ThetaBeta_at_outport_1_PWORK .
AQHandles && ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_MotorPose_to_ThetaBeta_at_outport_1_PWORK .
AQHandles , ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_7_0_1 [ 1 ] + 0
) ; } } } vm_ReadLocalDSMNoIdx ( S , _rtDW -> dsmIdx , ( char_T * )
 "Copy_of_linkleg_trajectory_contact/Controller/initialize_switch/Initialize_Flag3"
, 0 ) ; _rtB -> B_10_17_0 = _rtDW -> Initialize ; isHit = ssIsSampleHit ( S ,
1 , 0 ) ; if ( isHit != 0 ) { if ( ssIsModeUpdateTimeStep ( S ) ) { _rtDW ->
Compare_Mode = ( _rtB -> B_10_17_0 == _rtB -> B_10_3_0 ) ; } rtb_B_10_18_0 =
_rtDW -> Compare_Mode ; { if ( _rtDW ->
TAQSigLogging_InsertedFor_CompareToConstant1_at_outport_0_PWORK . AQHandles
&& ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_CompareToConstant1_at_outport_0_PWORK . AQHandles ,
ssGetTaskTime ( S , 1 ) , ( char * ) & rtb_B_10_18_0 + 0 ) ; } } }
vm_ReadLocalDSMNoIdx ( S , _rtDW -> dsmIdx , ( char_T * )
 "Copy_of_linkleg_trajectory_contact/Controller/initialize_switch/Initialize_Flag2"
, 0 ) ; _rtB -> B_10_20_0 = _rtDW -> Initialize ; isHit = ssIsSampleHit ( S ,
1 , 0 ) ; if ( isHit != 0 ) { if ( ssIsModeUpdateTimeStep ( S ) ) { _rtDW ->
Compare_Mode_c = ( _rtB -> B_10_20_0 == _rtB -> B_10_4_0 ) ; } rtb_B_10_21_0
= _rtDW -> Compare_Mode_c ; { if ( _rtDW ->
TAQSigLogging_InsertedFor_CompareToConstant2_at_outport_0_PWORK . AQHandles
&& ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_CompareToConstant2_at_outport_0_PWORK . AQHandles ,
ssGetTaskTime ( S , 1 ) , ( char * ) & rtb_B_10_21_0 + 0 ) ; } } { if ( _rtDW
-> TAQSigLogging_InsertedFor_Initialize_Flag2_at_outport_0_PWORK . AQHandles
&& ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_Initialize_Flag2_at_outport_0_PWORK . AQHandles ,
ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_10_20_0 + 0 ) ; } } { if (
_rtDW -> TAQSigLogging_InsertedFor_Initialize_Flag3_at_outport_0_PWORK .
AQHandles && ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_Initialize_Flag3_at_outport_0_PWORK . AQHandles ,
ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_10_17_0 + 0 ) ; } } }
vm_ReadLocalDSMNoIdx ( S , _rtDW -> dsmIdx , ( char_T * )
"Copy_of_linkleg_trajectory_contact/Controller/Initialize_Flag2" , 0 ) ; _rtB
-> B_10_25_0 = _rtDW -> Initialize ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if
( isHit != 0 ) { if ( ssIsModeUpdateTimeStep ( S ) ) { _rtDW ->
Compare_Mode_m = ( _rtB -> B_10_25_0 == _rtB -> B_10_7_0 ) ; } _rtB ->
B_10_27_0 [ 0 ] = _rtB -> B_10_8_0 [ 0 ] ; _rtB -> B_10_27_0 [ 1 ] = _rtB ->
B_10_8_0 [ 1 ] ; ssCallAccelRunBlock ( S , 1 , 0 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 3 , 0 , SS_CALL_MDL_OUTPUTS ) ; }
vm_ReadLocalDSMNoIdx ( S , _rtDW -> dsmIdx , ( char_T * )
 "Copy_of_linkleg_trajectory_contact/Controller/initialize_switch/Initialize_Flag1"
, 0 ) ; _rtB -> B_10_30_0 = _rtDW -> Initialize ; isHit = ssIsSampleHit ( S ,
1 , 0 ) ; if ( isHit != 0 ) { if ( ssIsModeUpdateTimeStep ( S ) ) { _rtDW ->
Compare_Mode_l = ( _rtB -> B_10_30_0 == _rtB -> B_10_2_0_c ) ; }
rtb_B_10_31_0 = _rtDW -> Compare_Mode_l ; if ( rtb_B_10_21_0 != 0 ) { _rtB ->
B_10_33_0 = _rtB -> B_3_0_1 [ 0 ] ; } else if ( _rtDW -> Compare_Mode_l ) {
_rtB -> B_10_33_0 = _rtB -> B_2_0_1 [ 0 ] ; } else { _rtB -> B_10_33_0 = _rtB
-> B_10_6_0 ; } { if ( _rtDW ->
TAQSigLogging_InsertedFor_Switch4_at_outport_0_PWORK . AQHandles &&
ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_Switch4_at_outport_0_PWORK . AQHandles ,
ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_10_33_0 + 0 ) ; } } if (
rtb_B_10_18_0 != 0 ) { _rtB -> B_10_36_0 = _rtB -> B_3_0_1 [ 1 ] ; } else if
( rtb_B_10_31_0 ) { _rtB -> B_10_36_0 = _rtB -> B_2_0_1 [ 1 ] ; } else { _rtB
-> B_10_36_0 = _rtB -> B_10_5_0 ; } { if ( _rtDW ->
TAQSigLogging_InsertedFor_Switch5_at_outport_0_PWORK . AQHandles &&
ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_Switch5_at_outport_0_PWORK . AQHandles ,
ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_10_36_0 + 0 ) ; } } } _rtB
-> B_10_38_0 = _rtB -> B_10_33_0 - _rtB -> B_10_2_0 [ 2 ] ; _rtB -> B_10_39_0
= _rtP -> P_0 * _rtB -> B_10_38_0 ; isHit = ssIsSampleHit ( S , 2 , 0 ) ; if
( isHit != 0 ) { _rtB -> B_10_40_0 = _rtDW -> Filter_DSTATE ; } _rtB ->
B_10_41_0 = _rtB -> B_10_39_0 - _rtB -> B_10_40_0 ; _rtB -> B_10_42_0 = _rtP
-> P_3 * _rtB -> B_10_38_0 ; isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit
!= 0 ) { _rtB -> B_10_43_0 = _rtDW -> Integrator_DSTATE ; } _rtB -> B_10_44_0
= _rtP -> P_6 * _rtB -> B_10_41_0 ; _rtB -> B_10_45_0 = _rtP -> P_7 * _rtB ->
B_10_38_0 ; _rtB -> B_10_46_0 = ( _rtB -> B_10_45_0 + _rtB -> B_10_43_0 ) +
_rtB -> B_10_44_0 ; if ( ssIsModeUpdateTimeStep ( S ) ) { _rtDW ->
Saturation_MODE = _rtB -> B_10_46_0 >= _rtP -> P_8 ? 1 : _rtB -> B_10_46_0 >
_rtP -> P_9 ? 0 : - 1 ; } _rtB -> B_10_47_0 = _rtDW -> Saturation_MODE == 1 ?
_rtP -> P_8 : _rtDW -> Saturation_MODE == - 1 ? _rtP -> P_9 : _rtB ->
B_10_46_0 ; _rtB -> B_10_48_0 = _rtB -> B_10_36_0 - _rtB -> B_10_2_0 [ 0 ] ;
_rtB -> B_10_49_0 = _rtP -> P_10 * _rtB -> B_10_48_0 ; isHit = ssIsSampleHit
( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_10_50_0 = _rtDW ->
Filter_DSTATE_g ; } _rtB -> B_10_51_0 = _rtB -> B_10_49_0 - _rtB -> B_10_50_0
; _rtB -> B_10_52_0 = _rtP -> P_13 * _rtB -> B_10_48_0 ; isHit =
ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_10_53_0 = _rtDW
-> Integrator_DSTATE_b ; } _rtB -> B_10_54_0 = _rtP -> P_16 * _rtB ->
B_10_51_0 ; _rtB -> B_10_55_0 = _rtP -> P_17 * _rtB -> B_10_48_0 ; _rtB ->
B_10_56_0 = ( _rtB -> B_10_55_0 + _rtB -> B_10_53_0 ) + _rtB -> B_10_54_0 ;
if ( ssIsModeUpdateTimeStep ( S ) ) { _rtDW -> Saturation_MODE_k = _rtB ->
B_10_56_0 >= _rtP -> P_18 ? 1 : _rtB -> B_10_56_0 > _rtP -> P_19 ? 0 : - 1 ;
} _rtB -> B_10_57_0 = _rtDW -> Saturation_MODE_k == 1 ? _rtP -> P_18 : _rtDW
-> Saturation_MODE_k == - 1 ? _rtP -> P_19 : _rtB -> B_10_56_0 ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { _rtDW -> Step_MODE = (
ssGetTaskTime ( S , 1 ) >= _rtP -> P_20 ) ; if ( _rtDW -> Step_MODE == 1 ) {
_rtB -> B_10_62_0 = _rtP -> P_22 ; } else { _rtB -> B_10_62_0 = _rtP -> P_21
; } } _rtB -> B_10_66_0 = ( ssGetT ( S ) - _rtB -> B_10_16_0 ) * _rtB ->
B_10_62_0 + _rtB -> B_10_17_0_k ; isHit = ssIsSampleHit ( S , 2 , 0 ) ; if (
isHit != 0 ) { _rtB -> B_10_67_0 = _rtDW -> Delay3_DSTATE ; _rtB -> B_10_68_0
= _rtDW -> Delay2_DSTATE ; _rtB -> B_10_69_0 = _rtDW -> Delay_DSTATE [ 0 ] ;
_rtB -> B_10_70_0 = _rtDW -> Delay1_DSTATE [ 0 ] ; _rtB -> B_10_71_0 [ 0 ] =
_rtDW -> Delay_DSTATE_b [ 0 ] ; _rtB -> B_10_72_0 [ 0 ] = _rtDW ->
Delay1_DSTATE_a [ 0 ] ; _rtB -> B_10_71_0 [ 1 ] = _rtDW -> Delay_DSTATE_b [ 1
] ; _rtB -> B_10_72_0 [ 1 ] = _rtDW -> Delay1_DSTATE_a [ 1 ] ; _rtB ->
B_10_73_0 = _rtDW -> Delay3_DSTATE_k ; _rtB -> B_10_74_0 = _rtDW ->
Delay2_DSTATE_o ; _rtB -> B_10_75_0 = _rtDW -> Delay_DSTATE_f [ 0 ] ; _rtB ->
B_10_76_0 = _rtDW -> Delay1_DSTATE_p [ 0 ] ; } { real_T * * uBuffer = (
real_T * * ) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T
simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_33 ; _rtB
-> B_10_77_0 = Copy_of_linkleg_trajectory_contact_acc_rt_TDelayInterpolate (
tMinusDelay , 0.0 , * uBuffer , _rtDW -> TransportDelay_IWORK .
CircularBufSize , & _rtDW -> TransportDelay_IWORK . Last , _rtDW ->
TransportDelay_IWORK . Tail , _rtDW -> TransportDelay_IWORK . Head , _rtP ->
P_34 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && ( ( * uBuffer + _rtDW
-> TransportDelay_IWORK . CircularBufSize ) [ _rtDW -> TransportDelay_IWORK .
Head ] == ssGetT ( S ) ) ) ) ; } { real_T * * uBuffer = ( real_T * * ) &
_rtDW -> TransportDelay1_PWORK . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT
( S ) ; real_T tMinusDelay = simTime - _rtP -> P_35 ; _rtB -> B_10_78_0 =
Copy_of_linkleg_trajectory_contact_acc_rt_TDelayInterpolate ( tMinusDelay ,
0.0 , * uBuffer , _rtDW -> TransportDelay1_IWORK . CircularBufSize , & _rtDW
-> TransportDelay1_IWORK . Last , _rtDW -> TransportDelay1_IWORK . Tail ,
_rtDW -> TransportDelay1_IWORK . Head , _rtP -> P_36 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ( * uBuffer + _rtDW -> TransportDelay1_IWORK .
CircularBufSize ) [ _rtDW -> TransportDelay1_IWORK . Head ] == ssGetT ( S ) )
) ) ; } ssCallAccelRunBlock ( S , 4 , 0 , SS_CALL_MDL_OUTPUTS ) ; isHit =
ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_10_80_0 [ 0 ] =
_rtDW -> Delay1_DSTATE_a4 [ 0 ] ; _rtB -> B_10_81_0 [ 0 ] = _rtDW ->
Delay_DSTATE_a [ 0 ] ; _rtB -> B_10_80_0 [ 1 ] = _rtDW -> Delay1_DSTATE_a4 [
1 ] ; _rtB -> B_10_81_0 [ 1 ] = _rtDW -> Delay_DSTATE_a [ 1 ] ; } { real_T *
* uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_n . TUbufferPtrs [
0 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP ->
P_39 ; B_10_82_0 =
Copy_of_linkleg_trajectory_contact_acc_rt_TDelayInterpolate ( tMinusDelay ,
0.0 , * uBuffer , _rtDW -> TransportDelay_IWORK_p . CircularBufSize , & _rtDW
-> TransportDelay_IWORK_p . Last , _rtDW -> TransportDelay_IWORK_p . Tail ,
_rtDW -> TransportDelay_IWORK_p . Head , _rtP -> P_40 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ( * uBuffer + _rtDW -> TransportDelay_IWORK_p .
CircularBufSize ) [ _rtDW -> TransportDelay_IWORK_p . Head ] == ssGetT ( S )
) ) ) ; } _rtB -> B_10_83_0 = _rtP -> P_41 * B_10_82_0 ; { real_T * * uBuffer
= ( real_T * * ) & _rtDW -> TransportDelay1_PWORK_k . TUbufferPtrs [ 0 ] ;
real_T simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_42 ;
B_10_84_0 = Copy_of_linkleg_trajectory_contact_acc_rt_TDelayInterpolate (
tMinusDelay , 0.0 , * uBuffer , _rtDW -> TransportDelay1_IWORK_a .
CircularBufSize , & _rtDW -> TransportDelay1_IWORK_a . Last , _rtDW ->
TransportDelay1_IWORK_a . Tail , _rtDW -> TransportDelay1_IWORK_a . Head ,
_rtP -> P_43 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S ) && ( ( * uBuffer +
_rtDW -> TransportDelay1_IWORK_a . CircularBufSize ) [ _rtDW ->
TransportDelay1_IWORK_a . Head ] == ssGetT ( S ) ) ) ) ; } _rtB -> B_10_85_0
= _rtP -> P_44 * B_10_84_0 ; isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit
!= 0 ) { _rtB -> B_10_86_0 [ 0 ] = _rtDW -> Delay1_DSTATE_b [ 0 ] ; _rtB ->
B_10_87_0 [ 0 ] = _rtDW -> Delay_DSTATE_d [ 0 ] ; _rtB -> B_10_86_0 [ 1 ] =
_rtDW -> Delay1_DSTATE_b [ 1 ] ; _rtB -> B_10_87_0 [ 1 ] = _rtDW ->
Delay_DSTATE_d [ 1 ] ; } ssCallAccelRunBlock ( S , 10 , 88 ,
SS_CALL_MDL_OUTPUTS ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0
) { { if ( _rtDW -> TAQSigLogging_InsertedFor_SFunction_at_outport_0_PWORK .
AQHandles && ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_SFunction_at_outport_0_PWORK . AQHandles ,
ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_10_88_0 [ 0 ] + 0 ) ; } } {
if ( _rtDW -> TAQSigLogging_InsertedFor_Motortotheta_beta_at_outport_0_PWORK
. AQHandles && ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_Motortotheta_beta_at_outport_0_PWORK . AQHandles ,
ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_4_0_1 [ 0 ] + 0 ) ; } } { if
( _rtDW -> TAQSigLogging_InsertedFor_TransportDelay1_at_outport_0_PWORK .
AQHandles && ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_TransportDelay1_at_outport_0_PWORK . AQHandles ,
ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_10_78_0 + 0 ) ; } } { if (
_rtDW -> TAQSigLogging_InsertedFor_TransportDelay_at_outport_0_PWORK .
AQHandles && ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_TransportDelay_at_outport_0_PWORK . AQHandles ,
ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_10_77_0 + 0 ) ; } } } {
real_T * * uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_l .
TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay ; {
int_T i1 ; real_T * y0 = & _rtB -> B_10_101_0 [ 0 ] ; int_T * iw_Tail = &
_rtDW -> TransportDelay_IWORK_m . Tail [ 0 ] ; int_T * iw_Head = & _rtDW ->
TransportDelay_IWORK_m . Head [ 0 ] ; int_T * iw_Last = & _rtDW ->
TransportDelay_IWORK_m . Last [ 0 ] ; int_T * iw_CircularBufSize = & _rtDW ->
TransportDelay_IWORK_m . CircularBufSize [ 0 ] ; for ( i1 = 0 ; i1 < 2 ; i1
++ ) { tMinusDelay = ( ( _rtP -> P_47 > 0.0 ) ? _rtP -> P_47 : 0.0 ) ;
tMinusDelay = simTime - tMinusDelay ; y0 [ i1 ] =
Copy_of_linkleg_trajectory_contact_acc_rt_TDelayInterpolate ( tMinusDelay ,
0.0 , * uBuffer , iw_CircularBufSize [ i1 ] , & iw_Last [ i1 ] , iw_Tail [ i1
] , iw_Head [ i1 ] , _rtP -> P_48 , 0 , ( boolean_T ) ( ssIsMinorTimeStep ( S
) && ( ( * uBuffer + iw_CircularBufSize [ i1 ] ) [ iw_Head [ i1 ] ] == ssGetT
( S ) ) ) ) ; uBuffer ++ ; } } } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if (
isHit != 0 ) { _rtB -> B_10_102_0 [ 0 ] = _rtB -> B_10_83_0 ; _rtB ->
B_10_102_0 [ 1 ] = _rtB -> B_10_85_0 ; } _rtB -> B_10_110_0 [ 0 ] = _rtB ->
B_10_2_0 [ 1 ] ; _rtB -> B_10_110_0 [ 1 ] = 0.0 ; _rtB -> B_10_110_0 [ 2 ] =
0.0 ; _rtB -> B_10_110_0 [ 3 ] = 0.0 ; ssCallAccelRunBlock ( S , 10 , 111 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 10 , 112 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_10_113_0 = _rtB -> B_10_57_0 + _rtB ->
B_10_112_0 ; _rtB -> B_10_126_0 [ 0 ] = _rtB -> B_10_2_0 [ 3 ] ; _rtB ->
B_10_126_0 [ 1 ] = 0.0 ; _rtB -> B_10_126_0 [ 2 ] = 0.0 ; _rtB -> B_10_126_0
[ 3 ] = 0.0 ; ssCallAccelRunBlock ( S , 10 , 127 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 10 , 128 , SS_CALL_MDL_OUTPUTS ) ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { { if ( _rtDW ->
TAQSigLogging_InsertedFor_PSSimulinkConverter1_at_outport_0_PWORK . AQHandles
&& ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_PSSimulinkConverter1_at_outport_0_PWORK . AQHandles
, ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_10_128_0 + 0 ) ; } } { if
( _rtDW -> TAQSigLogging_InsertedFor_t_at_outport_0_PWORK . AQHandles &&
ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_t_at_outport_0_PWORK . AQHandles , ssGetTaskTime (
S , 1 ) , ( char * ) & _rtB -> B_10_47_0 + 0 ) ; } } } _rtB -> B_10_131_0 =
_rtB -> B_10_47_0 + _rtB -> B_10_128_0 ; _rtB -> B_10_133_0 [ 0 ] = _rtB ->
B_10_113_0 ; _rtB -> B_10_133_0 [ 1 ] = 0.0 ; _rtB -> B_10_133_0 [ 2 ] = 0.0
; _rtB -> B_10_133_0 [ 3 ] = 0.0 ; _rtB -> B_10_134_0 [ 0 ] = _rtB ->
B_10_131_0 ; _rtB -> B_10_134_0 [ 1 ] = 0.0 ; _rtB -> B_10_134_0 [ 2 ] = 0.0
; _rtB -> B_10_134_0 [ 3 ] = 0.0 ; ssCallAccelRunBlock ( S , 10 , 135 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 10 , 136 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 10 , 148 ,
SS_CALL_MDL_OUTPUTS ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0
) { { if ( _rtDW ->
TAQSigLogging_InsertedFor_PSSimulinkConverter2_at_outport_0_PWORK . AQHandles
&& ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_PSSimulinkConverter2_at_outport_0_PWORK . AQHandles
, ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_10_2_0 [ 4 ] + 0 ) ; } } {
if ( _rtDW ->
TAQSigLogging_InsertedFor_PSSimulinkConverter_at_outport_0_PWORK . AQHandles
&& ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_PSSimulinkConverter_at_outport_0_PWORK . AQHandles
, ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_10_2_0 [ 5 ] + 0 ) ; } } }
ssCallAccelRunBlock ( S , 10 , 154 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 10 , 155 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 10 , 156 , SS_CALL_MDL_OUTPUTS ) ; UNUSED_PARAMETER
( tid ) ; } static void mdlOutputsTID3 ( SimStruct * S , int_T tid ) {
B_Copy_of_linkleg_trajectory_contact_T * _rtB ;
P_Copy_of_linkleg_trajectory_contact_T * _rtP ; _rtP = ( (
P_Copy_of_linkleg_trajectory_contact_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_Copy_of_linkleg_trajectory_contact_T * ) _ssGetModelBlockIO ( S ) ) ; _rtB
-> B_10_0_0_m = _rtP -> P_50 ; _rtB -> B_10_2_0_c = _rtP -> P_51 ; _rtB ->
B_10_3_0 = _rtP -> P_52 ; _rtB -> B_10_4_0 = _rtP -> P_53 ; _rtB -> B_10_5_0
= _rtP -> P_54 ; _rtB -> B_10_6_0 = _rtP -> P_55 ; _rtB -> B_10_7_0 = _rtP ->
P_56 ; _rtB -> B_10_10_0 = _rtP -> P_58 ; _rtB -> B_10_12_0 = _rtP -> P_60 ;
_rtB -> B_10_13_0 = _rtP -> P_61 ; _rtB -> B_10_8_0 [ 0 ] = _rtP -> P_57 [ 0
] ; _rtB -> B_10_11_0 [ 0 ] = _rtP -> P_59 [ 0 ] ; _rtB -> B_10_14_0 [ 0 ] =
_rtP -> P_62 [ 0 ] ; _rtB -> B_10_15_0 [ 0 ] = _rtP -> P_63 [ 0 ] ; _rtB ->
B_10_8_0 [ 1 ] = _rtP -> P_57 [ 1 ] ; _rtB -> B_10_11_0 [ 1 ] = _rtP -> P_59
[ 1 ] ; _rtB -> B_10_14_0 [ 1 ] = _rtP -> P_62 [ 1 ] ; _rtB -> B_10_15_0 [ 1
] = _rtP -> P_63 [ 1 ] ; _rtB -> B_10_16_0 = _rtP -> P_64 ; _rtB ->
B_10_17_0_k = _rtP -> P_65 ; _rtB -> B_10_18_0 = _rtP -> P_66 ; _rtB ->
B_10_19_0 = _rtP -> P_67 ; _rtB -> B_10_20_0_c = _rtP -> P_68 ; _rtB ->
B_10_21_0 = _rtP -> P_69 ; ssCallAccelRunBlock ( S , 10 , 328 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 10 , 329 ,
SS_CALL_MDL_OUTPUTS ) ; UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) {
B_Copy_of_linkleg_trajectory_contact_T * _rtB ;
DW_Copy_of_linkleg_trajectory_contact_T * _rtDW ;
P_Copy_of_linkleg_trajectory_contact_T * _rtP ; int32_T isHit ; _rtDW = ( (
DW_Copy_of_linkleg_trajectory_contact_T * ) ssGetRootDWork ( S ) ) ; _rtP = (
( P_Copy_of_linkleg_trajectory_contact_T * ) ssGetModelRtp ( S ) ) ; _rtB = (
( B_Copy_of_linkleg_trajectory_contact_T * ) _ssGetModelBlockIO ( S ) ) ;
ssCallAccelRunBlock ( S , 10 , 1 , SS_CALL_MDL_UPDATE ) ; isHit =
ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtDW -> Filter_DSTATE +=
_rtP -> P_1 * _rtB -> B_10_44_0 ; _rtDW -> Integrator_DSTATE += _rtP -> P_4 *
_rtB -> B_10_42_0 ; _rtDW -> Filter_DSTATE_g += _rtP -> P_11 * _rtB ->
B_10_54_0 ; _rtDW -> Integrator_DSTATE_b += _rtP -> P_14 * _rtB -> B_10_52_0
; _rtDW -> Delay3_DSTATE = _rtB -> B_10_66_0 ; _rtDW -> Delay2_DSTATE = _rtB
-> B_10_10_0 ; _rtDW -> Delay_DSTATE [ 0U ] = _rtDW -> Delay_DSTATE [ 1U ] ;
_rtDW -> Delay_DSTATE [ 1 ] = _rtB -> B_10_66_0 ; _rtDW -> Delay1_DSTATE [ 0U
] = _rtDW -> Delay1_DSTATE [ 1U ] ; _rtDW -> Delay1_DSTATE [ 1 ] = _rtB ->
B_10_10_0 ; _rtDW -> Delay_DSTATE_b [ 0 ] = _rtB -> B_10_101_0 [ 0 ] ; _rtDW
-> Delay_DSTATE_b [ 1 ] = _rtB -> B_10_101_0 [ 1 ] ; _rtDW -> Delay1_DSTATE_a
[ 0U ] = _rtDW -> Delay1_DSTATE_a [ 2U ] ; _rtDW -> Delay1_DSTATE_a [ 1U ] =
_rtDW -> Delay1_DSTATE_a [ 3U ] ; _rtDW -> Delay1_DSTATE_a [ 2 ] = _rtB ->
B_10_101_0 [ 0 ] ; _rtDW -> Delay1_DSTATE_a [ 3 ] = _rtB -> B_10_101_0 [ 1 ]
; _rtDW -> Delay3_DSTATE_k = _rtB -> B_10_12_0 ; _rtDW -> Delay2_DSTATE_o =
_rtB -> B_10_13_0 ; _rtDW -> Delay_DSTATE_f [ 0U ] = _rtDW -> Delay_DSTATE_f
[ 1U ] ; _rtDW -> Delay_DSTATE_f [ 1 ] = _rtB -> B_10_12_0 ; _rtDW ->
Delay1_DSTATE_p [ 0U ] = _rtDW -> Delay1_DSTATE_p [ 1U ] ; _rtDW ->
Delay1_DSTATE_p [ 1 ] = _rtB -> B_10_13_0 ; } { real_T * * uBuffer = ( real_T
* * ) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T simTime =
ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK . Head = ( ( _rtDW ->
TransportDelay_IWORK . Head < ( _rtDW -> TransportDelay_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK . Head + 1 ) : 0 )
; if ( _rtDW -> TransportDelay_IWORK . Head == _rtDW -> TransportDelay_IWORK
. Tail ) { if ( !
Copy_of_linkleg_trajectory_contact_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW
-> TransportDelay_IWORK . CircularBufSize , & _rtDW -> TransportDelay_IWORK .
Tail , & _rtDW -> TransportDelay_IWORK . Head , & _rtDW ->
TransportDelay_IWORK . Last , simTime - _rtP -> P_33 , uBuffer , ( boolean_T
) 0 , false , & _rtDW -> TransportDelay_IWORK . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
uBuffer + _rtDW -> TransportDelay_IWORK . CircularBufSize ) [ _rtDW ->
TransportDelay_IWORK . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay_IWORK . Head ] = _rtB -> B_10_2_0 [ 2 ] ; } { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay1_PWORK . TUbufferPtrs [ 0
] ; real_T simTime = ssGetT ( S ) ; _rtDW -> TransportDelay1_IWORK . Head = (
( _rtDW -> TransportDelay1_IWORK . Head < ( _rtDW -> TransportDelay1_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay1_IWORK . Head + 1 ) : 0 )
; if ( _rtDW -> TransportDelay1_IWORK . Head == _rtDW ->
TransportDelay1_IWORK . Tail ) { if ( !
Copy_of_linkleg_trajectory_contact_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW
-> TransportDelay1_IWORK . CircularBufSize , & _rtDW -> TransportDelay1_IWORK
. Tail , & _rtDW -> TransportDelay1_IWORK . Head , & _rtDW ->
TransportDelay1_IWORK . Last , simTime - _rtP -> P_35 , uBuffer , ( boolean_T
) 0 , false , & _rtDW -> TransportDelay1_IWORK . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
uBuffer + _rtDW -> TransportDelay1_IWORK . CircularBufSize ) [ _rtDW ->
TransportDelay1_IWORK . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay1_IWORK . Head ] = _rtB -> B_10_2_0 [ 0 ] ; } isHit =
ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtDW -> Delay1_DSTATE_a4 [
0 ] = _rtB -> B_4_0_1 [ 0 ] ; _rtDW -> Delay1_DSTATE_a4 [ 1 ] = _rtB ->
B_4_0_1 [ 1 ] ; _rtDW -> Delay_DSTATE_a [ 0U ] = _rtDW -> Delay_DSTATE_a [ 2U
] ; _rtDW -> Delay_DSTATE_a [ 1U ] = _rtDW -> Delay_DSTATE_a [ 3U ] ; _rtDW
-> Delay_DSTATE_a [ 2 ] = _rtB -> B_4_0_1 [ 0 ] ; _rtDW -> Delay_DSTATE_a [ 3
] = _rtB -> B_4_0_1 [ 1 ] ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW
-> TransportDelay_PWORK_n . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S
) ; _rtDW -> TransportDelay_IWORK_p . Head = ( ( _rtDW ->
TransportDelay_IWORK_p . Head < ( _rtDW -> TransportDelay_IWORK_p .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK_p . Head + 1 ) : 0
) ; if ( _rtDW -> TransportDelay_IWORK_p . Head == _rtDW ->
TransportDelay_IWORK_p . Tail ) { if ( !
Copy_of_linkleg_trajectory_contact_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW
-> TransportDelay_IWORK_p . CircularBufSize , & _rtDW ->
TransportDelay_IWORK_p . Tail , & _rtDW -> TransportDelay_IWORK_p . Head , &
_rtDW -> TransportDelay_IWORK_p . Last , simTime - _rtP -> P_39 , uBuffer , (
boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_p . MaxNewBufSize ) )
{ ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } (
* uBuffer + _rtDW -> TransportDelay_IWORK_p . CircularBufSize ) [ _rtDW ->
TransportDelay_IWORK_p . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay_IWORK_p . Head ] = _rtB -> B_10_135_0 [ 9 ] ; } { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay1_PWORK_k . TUbufferPtrs [
0 ] ; real_T simTime = ssGetT ( S ) ; _rtDW -> TransportDelay1_IWORK_a . Head
= ( ( _rtDW -> TransportDelay1_IWORK_a . Head < ( _rtDW ->
TransportDelay1_IWORK_a . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay1_IWORK_a . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay1_IWORK_a . Head == _rtDW -> TransportDelay1_IWORK_a . Tail ) {
if ( ! Copy_of_linkleg_trajectory_contact_acc_rt_TDelayUpdateTailOrGrowBuf (
& _rtDW -> TransportDelay1_IWORK_a . CircularBufSize , & _rtDW ->
TransportDelay1_IWORK_a . Tail , & _rtDW -> TransportDelay1_IWORK_a . Head ,
& _rtDW -> TransportDelay1_IWORK_a . Last , simTime - _rtP -> P_42 , uBuffer
, ( boolean_T ) 0 , false , & _rtDW -> TransportDelay1_IWORK_a .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * uBuffer + _rtDW -> TransportDelay1_IWORK_a .
CircularBufSize ) [ _rtDW -> TransportDelay1_IWORK_a . Head ] = simTime ; ( *
uBuffer ) [ _rtDW -> TransportDelay1_IWORK_a . Head ] = _rtB -> B_10_135_0 [
1 ] ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtDW ->
Delay1_DSTATE_b [ 0 ] = _rtB -> B_10_102_0 [ 0 ] ; _rtDW -> Delay1_DSTATE_b [
1 ] = _rtB -> B_10_102_0 [ 1 ] ; _rtDW -> Delay_DSTATE_d [ 0U ] = _rtDW ->
Delay_DSTATE_d [ 2U ] ; _rtDW -> Delay_DSTATE_d [ 1U ] = _rtDW ->
Delay_DSTATE_d [ 3U ] ; _rtDW -> Delay_DSTATE_d [ 2 ] = _rtB -> B_10_102_0 [
0 ] ; _rtDW -> Delay_DSTATE_d [ 3 ] = _rtB -> B_10_102_0 [ 1 ] ; } { real_T *
* uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_l . TUbufferPtrs [
0 ] ; real_T simTime = ssGetT ( S ) ; _rtDW -> TransportDelay_IWORK_m . Head
[ 0 ] = ( ( _rtDW -> TransportDelay_IWORK_m . Head [ 0 ] < ( _rtDW ->
TransportDelay_IWORK_m . CircularBufSize [ 0 ] - 1 ) ) ? ( _rtDW ->
TransportDelay_IWORK_m . Head [ 0 ] + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay_IWORK_m . Head [ 0 ] == _rtDW -> TransportDelay_IWORK_m . Tail
[ 0 ] ) { if ( !
Copy_of_linkleg_trajectory_contact_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW
-> TransportDelay_IWORK_m . CircularBufSize [ 0 ] , & _rtDW ->
TransportDelay_IWORK_m . Tail [ 0 ] , & _rtDW -> TransportDelay_IWORK_m .
Head [ 0 ] , & _rtDW -> TransportDelay_IWORK_m . Last [ 0 ] , simTime - _rtP
-> P_47 , uBuffer , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay_IWORK_m . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * uBuffer + _rtDW ->
TransportDelay_IWORK_m . CircularBufSize [ 0 ] ) [ _rtDW ->
TransportDelay_IWORK_m . Head [ 0 ] ] = simTime ; ( * uBuffer ++ ) [ _rtDW ->
TransportDelay_IWORK_m . Head [ 0 ] ] = _rtB -> B_10_88_0 [ 0 ] ; _rtDW ->
TransportDelay_IWORK_m . Head [ 1 ] = ( ( _rtDW -> TransportDelay_IWORK_m .
Head [ 1 ] < ( _rtDW -> TransportDelay_IWORK_m . CircularBufSize [ 1 ] - 1 )
) ? ( _rtDW -> TransportDelay_IWORK_m . Head [ 1 ] + 1 ) : 0 ) ; if ( _rtDW
-> TransportDelay_IWORK_m . Head [ 1 ] == _rtDW -> TransportDelay_IWORK_m .
Tail [ 1 ] ) { if ( !
Copy_of_linkleg_trajectory_contact_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW
-> TransportDelay_IWORK_m . CircularBufSize [ 1 ] , & _rtDW ->
TransportDelay_IWORK_m . Tail [ 1 ] , & _rtDW -> TransportDelay_IWORK_m .
Head [ 1 ] , & _rtDW -> TransportDelay_IWORK_m . Last [ 1 ] , simTime - _rtP
-> P_47 , uBuffer , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay_IWORK_m . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * uBuffer + _rtDW ->
TransportDelay_IWORK_m . CircularBufSize [ 1 ] ) [ _rtDW ->
TransportDelay_IWORK_m . Head [ 1 ] ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay_IWORK_m . Head [ 1 ] ] = _rtB -> B_10_88_0 [ 1 ] ; }
ssCallAccelRunBlock ( S , 10 , 111 , SS_CALL_MDL_UPDATE ) ;
ssCallAccelRunBlock ( S , 10 , 127 , SS_CALL_MDL_UPDATE ) ; UNUSED_PARAMETER
( tid ) ; }
#define MDL_UPDATE
static void mdlUpdateTID3 ( SimStruct * S , int_T tid ) { UNUSED_PARAMETER (
tid ) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) { ssCallAccelRunBlock ( S , 10 ,
1 , SS_CALL_MDL_DERIVATIVES ) ; ssCallAccelRunBlock ( S , 10 , 111 ,
SS_CALL_MDL_DERIVATIVES ) ; ssCallAccelRunBlock ( S , 10 , 127 ,
SS_CALL_MDL_DERIVATIVES ) ; }
#define MDL_PROJECTION
static void mdlProjection ( SimStruct * S ) { ssCallAccelRunBlock ( S , 10 ,
1 , SS_CALL_MDL_PROJECTION ) ; ssCallAccelRunBlock ( S , 10 , 111 ,
SS_CALL_MDL_PROJECTION ) ; ssCallAccelRunBlock ( S , 10 , 127 ,
SS_CALL_MDL_PROJECTION ) ; }
#define MDL_FORCINGFUNCTION
static void mdlForcingFunction ( SimStruct * S ) { ssCallAccelRunBlock ( S ,
10 , 1 , SS_CALL_MDL_FORCINGFUNCTION ) ; ssCallAccelRunBlock ( S , 10 , 111 ,
SS_CALL_MDL_FORCINGFUNCTION ) ; ssCallAccelRunBlock ( S , 10 , 127 ,
SS_CALL_MDL_FORCINGFUNCTION ) ; }
#define MDL_MASSMATRIX
static void mdlMassMatrix ( SimStruct * S ) { ssCallAccelRunBlock ( S , 10 ,
1 , SS_CALL_MDL_MASSMATRIX ) ; ssCallAccelRunBlock ( S , 10 , 111 ,
SS_CALL_MDL_MASSMATRIX ) ; ssCallAccelRunBlock ( S , 10 , 127 ,
SS_CALL_MDL_MASSMATRIX ) ; }
#define MDL_ZERO_CROSSINGS
static void mdlZeroCrossings ( SimStruct * S ) {
B_Copy_of_linkleg_trajectory_contact_T * _rtB ;
P_Copy_of_linkleg_trajectory_contact_T * _rtP ;
ZCV_Copy_of_linkleg_trajectory_contact_T * _rtZCSV ; _rtZCSV = ( (
ZCV_Copy_of_linkleg_trajectory_contact_T * ) ssGetSolverZcSignalVector ( S )
) ; _rtP = ( ( P_Copy_of_linkleg_trajectory_contact_T * ) ssGetModelRtp ( S )
) ; _rtB = ( ( B_Copy_of_linkleg_trajectory_contact_T * ) _ssGetModelBlockIO
( S ) ) ; _rtZCSV -> Compare_RelopInput_ZC = _rtB -> B_10_17_0 - _rtB ->
B_10_3_0 ; _rtZCSV -> Compare_RelopInput_ZC_g = _rtB -> B_10_20_0 - _rtB ->
B_10_4_0 ; _rtZCSV -> Compare_RelopInput_ZC_e = _rtB -> B_10_25_0 - _rtB ->
B_10_7_0 ; _rtZCSV -> Compare_RelopInput_ZC_o = _rtB -> B_10_30_0 - _rtB ->
B_10_2_0_c ; _rtZCSV -> Saturation_UprLim_ZC = _rtB -> B_10_46_0 - _rtP ->
P_8 ; _rtZCSV -> Saturation_LwrLim_ZC = _rtB -> B_10_46_0 - _rtP -> P_9 ;
_rtZCSV -> Saturation_UprLim_ZC_n = _rtB -> B_10_56_0 - _rtP -> P_18 ;
_rtZCSV -> Saturation_LwrLim_ZC_b = _rtB -> B_10_56_0 - _rtP -> P_19 ;
_rtZCSV -> Step_StepTime_ZC = ssGetT ( S ) - _rtP -> P_20 ; } static void
mdlInitializeSizes ( SimStruct * S ) { ssSetChecksumVal ( S , 0 , 3525691627U
) ; ssSetChecksumVal ( S , 1 , 1471494481U ) ; ssSetChecksumVal ( S , 2 ,
3799601008U ) ; ssSetChecksumVal ( S , 3 , 1505197036U ) ; { mxArray *
slVerStructMat = ( NULL ) ; mxArray * slStrMat = mxCreateString ( "simulink"
) ; char slVerChar [ 10 ] ; int status = mexCallMATLAB ( 1 , & slVerStructMat
, 1 , & slStrMat , "ver" ) ; if ( status == 0 ) { mxArray * slVerMat =
mxGetField ( slVerStructMat , 0 , "Version" ) ; if ( slVerMat == ( NULL ) ) {
status = 1 ; } else { status = mxGetString ( slVerMat , slVerChar , 10 ) ; }
} mxDestroyArray ( slStrMat ) ; mxDestroyArray ( slVerStructMat ) ; if ( (
status == 1 ) || ( strcmp ( slVerChar , "10.6" ) != 0 ) ) { return ; } }
ssSetOptions ( S , SS_OPTION_EXCEPTION_FREE_CODE ) ; if ( ssGetSizeofDWork (
S ) != ( SLSize ) sizeof ( DW_Copy_of_linkleg_trajectory_contact_T ) ) {
static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal DWork sizes do "
"not match for accelerator mex file (%ld vs %lu)." , ( signed long )
ssGetSizeofDWork ( S ) , ( unsigned long ) sizeof (
DW_Copy_of_linkleg_trajectory_contact_T ) ) ; ssSetErrorStatus ( S , msg ) ;
} if ( ssGetSizeofGlobalBlockIO ( S ) != ( SLSize ) sizeof (
B_Copy_of_linkleg_trajectory_contact_T ) ) { static char msg [ 256 ] ;
sprintf ( msg , "Unexpected error: Internal BlockIO sizes do "
"not match for accelerator mex file (%ld vs %lu)." , ( signed long )
ssGetSizeofGlobalBlockIO ( S ) , ( unsigned long ) sizeof (
B_Copy_of_linkleg_trajectory_contact_T ) ) ; ssSetErrorStatus ( S , msg ) ; }
{ int ssSizeofParams ; ssGetSizeofParams ( S , & ssSizeofParams ) ; if (
ssSizeofParams != sizeof ( P_Copy_of_linkleg_trajectory_contact_T ) ) {
static char msg [ 256 ] ; sprintf ( msg ,
"Unexpected error: Internal Parameters sizes do "
"not match for accelerator mex file (%d vs %lu)." , ssSizeofParams , (
unsigned long ) sizeof ( P_Copy_of_linkleg_trajectory_contact_T ) ) ;
ssSetErrorStatus ( S , msg ) ; } } _ssSetModelRtp ( S , ( real_T * ) &
Copy_of_linkleg_trajectory_contact_rtDefaultP ) ; if ( ssGetSizeofDWork ( S )
== ( SLSize ) sizeof ( DW_Copy_of_linkleg_trajectory_contact_T ) ) { { ( (
DW_Copy_of_linkleg_trajectory_contact_T * ) ssGetRootDWork ( S ) ) ->
STATE_3_MASS_MATRIX_PR = 44 ; ( ( DW_Copy_of_linkleg_trajectory_contact_T * )
ssGetRootDWork ( S ) ) -> STATE_2_MASS_MATRIX_PR = 45 ; } } rt_InitInfAndNaN
( sizeof ( real_T ) ) ; } static void mdlInitializeSampleTimes ( SimStruct *
S ) { { SimStruct * childS ; SysOutputFcn * callSysFcns ; childS =
ssGetSFunction ( S , 0 ) ; callSysFcns = ssGetCallSystemOutputFcnList (
childS ) ; callSysFcns [ 3 + 0 ] = ( SysOutputFcn ) ( NULL ) ; childS =
ssGetSFunction ( S , 1 ) ; callSysFcns = ssGetCallSystemOutputFcnList (
childS ) ; callSysFcns [ 3 + 0 ] = ( SysOutputFcn ) ( NULL ) ; childS =
ssGetSFunction ( S , 2 ) ; callSysFcns = ssGetCallSystemOutputFcnList (
childS ) ; callSysFcns [ 3 + 0 ] = ( SysOutputFcn ) ( NULL ) ; childS =
ssGetSFunction ( S , 3 ) ; callSysFcns = ssGetCallSystemOutputFcnList (
childS ) ; callSysFcns [ 3 + 0 ] = ( SysOutputFcn ) ( NULL ) ; childS =
ssGetSFunction ( S , 4 ) ; callSysFcns = ssGetCallSystemOutputFcnList (
childS ) ; callSysFcns [ 3 + 0 ] = ( SysOutputFcn ) ( NULL ) ; childS =
ssGetSFunction ( S , 5 ) ; callSysFcns = ssGetCallSystemOutputFcnList (
childS ) ; callSysFcns [ 3 + 0 ] = ( SysOutputFcn ) ( NULL ) ; childS =
ssGetSFunction ( S , 6 ) ; callSysFcns = ssGetCallSystemOutputFcnList (
childS ) ; callSysFcns [ 3 + 0 ] = ( SysOutputFcn ) ( NULL ) ; childS =
ssGetSFunction ( S , 7 ) ; callSysFcns = ssGetCallSystemOutputFcnList (
childS ) ; callSysFcns [ 3 + 0 ] = ( SysOutputFcn ) ( NULL ) ; }
slAccRegPrmChangeFcn ( S , mdlOutputsTID3 ) ; } static void mdlTerminate (
SimStruct * S ) { }
#include "simulink.c"
