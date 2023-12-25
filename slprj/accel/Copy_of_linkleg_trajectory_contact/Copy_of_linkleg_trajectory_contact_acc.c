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
mdlOutputs ( SimStruct * S , int_T tid ) {
B_Copy_of_linkleg_trajectory_contact_T * _rtB ;
DW_Copy_of_linkleg_trajectory_contact_T * _rtDW ;
P_Copy_of_linkleg_trajectory_contact_T * _rtP ; int32_T isHit ; boolean_T
rtb_B_8_55_0 ; _rtDW = ( ( DW_Copy_of_linkleg_trajectory_contact_T * )
ssGetRootDWork ( S ) ) ; _rtP = ( ( P_Copy_of_linkleg_trajectory_contact_T *
) ssGetModelRtp ( S ) ) ; _rtB = ( ( B_Copy_of_linkleg_trajectory_contact_T *
) _ssGetModelBlockIO ( S ) ) ; vm_ReadLocalDSMNoIdx ( S , _rtDW -> dsmIdx , (
char_T * )
 "Copy_of_linkleg_trajectory_contact/Controller/initialize_switch/Initialize_/Data Store Read1"
, 0 ) ; _rtB -> B_8_0_0 = _rtDW -> Initialize ; ssCallAccelRunBlock ( S , 8 ,
1 , SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 8 , 2 ,
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
, 0 ) ; _rtB -> B_8_17_0 = _rtDW -> Initialize ; isHit = ssIsSampleHit ( S ,
1 , 0 ) ; if ( isHit != 0 ) { if ( ssIsModeUpdateTimeStep ( S ) ) { _rtDW ->
Compare_Mode = ( _rtB -> B_8_17_0 == _rtB -> B_8_3_0 ) ; } _rtB -> B_8_18_0_b
= _rtDW -> Compare_Mode ; { if ( _rtDW ->
TAQSigLogging_InsertedFor_CompareToConstant1_at_outport_0_PWORK . AQHandles
&& ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_CompareToConstant1_at_outport_0_PWORK . AQHandles ,
ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_8_18_0_b + 0 ) ; } } }
vm_ReadLocalDSMNoIdx ( S , _rtDW -> dsmIdx , ( char_T * )
 "Copy_of_linkleg_trajectory_contact/Controller/initialize_switch/Initialize_Flag2"
, 0 ) ; _rtB -> B_8_20_0 = _rtDW -> Initialize ; isHit = ssIsSampleHit ( S ,
1 , 0 ) ; if ( isHit != 0 ) { if ( ssIsModeUpdateTimeStep ( S ) ) { _rtDW ->
Compare_Mode_c = ( _rtB -> B_8_20_0 == _rtB -> B_8_4_0 ) ; } _rtB ->
B_8_21_0_p = _rtDW -> Compare_Mode_c ; { if ( _rtDW ->
TAQSigLogging_InsertedFor_CompareToConstant2_at_outport_0_PWORK . AQHandles
&& ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_CompareToConstant2_at_outport_0_PWORK . AQHandles ,
ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_8_21_0_p + 0 ) ; } } { if (
_rtDW -> TAQSigLogging_InsertedFor_Initialize_Flag2_at_outport_0_PWORK .
AQHandles && ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_Initialize_Flag2_at_outport_0_PWORK . AQHandles ,
ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_8_20_0 + 0 ) ; } } { if (
_rtDW -> TAQSigLogging_InsertedFor_Initialize_Flag3_at_outport_0_PWORK .
AQHandles && ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_Initialize_Flag3_at_outport_0_PWORK . AQHandles ,
ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_8_17_0 + 0 ) ; } } _rtDW ->
Step_MODE = ( ssGetTaskTime ( S , 1 ) >= _rtP -> P_0 ) ; if ( _rtDW ->
Step_MODE == 1 ) { _rtB -> B_8_25_0 = _rtP -> P_2 ; } else { _rtB -> B_8_25_0
= _rtP -> P_1 ; } } _rtB -> B_8_27_0 = ssGetT ( S ) - _rtB -> B_8_15_0 ; _rtB
-> B_8_28_0 = _rtB -> B_8_25_0 * _rtB -> B_8_27_0 ; _rtB -> B_8_29_0 = _rtB
-> B_8_28_0 + _rtB -> B_8_16_0 ; isHit = ssIsSampleHit ( S , 2 , 0 ) ; if (
isHit != 0 ) { _rtB -> B_8_30_0 = _rtDW -> Delay3_DSTATE ; _rtB -> B_8_31_0 =
_rtDW -> Delay2_DSTATE ; _rtB -> B_8_32_0 = _rtDW -> Delay_DSTATE [ 0 ] ;
_rtB -> B_8_33_0 = _rtDW -> Delay1_DSTATE [ 0 ] ; _rtB -> B_8_34_0 [ 0 ] =
_rtDW -> Delay_DSTATE_b [ 0 ] ; _rtB -> B_8_35_0 [ 0 ] = _rtDW ->
Delay1_DSTATE_a [ 0 ] ; _rtB -> B_8_34_0 [ 1 ] = _rtDW -> Delay_DSTATE_b [ 1
] ; _rtB -> B_8_35_0 [ 1 ] = _rtDW -> Delay1_DSTATE_a [ 1 ] ; _rtB ->
B_8_36_0 = _rtDW -> Delay3_DSTATE_k ; _rtB -> B_8_37_0 = _rtDW ->
Delay2_DSTATE_o ; _rtB -> B_8_38_0 = _rtDW -> Delay_DSTATE_f [ 0 ] ; _rtB ->
B_8_39_0 = _rtDW -> Delay1_DSTATE_p [ 0 ] ; } { real_T * * uBuffer = ( real_T
* * ) & _rtDW -> TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T simTime =
ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP -> P_13 ; _rtB -> B_8_40_0
= Copy_of_linkleg_trajectory_contact_acc_rt_TDelayInterpolate ( tMinusDelay ,
0.0 , * uBuffer , _rtDW -> TransportDelay_IWORK . CircularBufSize , & _rtDW
-> TransportDelay_IWORK . Last , _rtDW -> TransportDelay_IWORK . Tail , _rtDW
-> TransportDelay_IWORK . Head , _rtP -> P_14 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ( * uBuffer + _rtDW -> TransportDelay_IWORK .
CircularBufSize ) [ _rtDW -> TransportDelay_IWORK . Head ] == ssGetT ( S ) )
) ) ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay1_PWORK . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S ) ;
real_T tMinusDelay = simTime - _rtP -> P_15 ; _rtB -> B_8_41_0 =
Copy_of_linkleg_trajectory_contact_acc_rt_TDelayInterpolate ( tMinusDelay ,
0.0 , * uBuffer , _rtDW -> TransportDelay1_IWORK . CircularBufSize , & _rtDW
-> TransportDelay1_IWORK . Last , _rtDW -> TransportDelay1_IWORK . Tail ,
_rtDW -> TransportDelay1_IWORK . Head , _rtP -> P_16 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ( * uBuffer + _rtDW -> TransportDelay1_IWORK .
CircularBufSize ) [ _rtDW -> TransportDelay1_IWORK . Head ] == ssGetT ( S ) )
) ) ; } ssCallAccelRunBlock ( S , 4 , 0 , SS_CALL_MDL_OUTPUTS ) ; isHit =
ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB -> B_8_43_0 [ 0 ] =
_rtDW -> Delay1_DSTATE_a4 [ 0 ] ; _rtB -> B_8_44_0 [ 0 ] = _rtDW ->
Delay_DSTATE_a [ 0 ] ; _rtB -> B_8_43_0 [ 1 ] = _rtDW -> Delay1_DSTATE_a4 [ 1
] ; _rtB -> B_8_44_0 [ 1 ] = _rtDW -> Delay_DSTATE_a [ 1 ] ; } { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_n . TUbufferPtrs [ 0
] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP ->
P_19 ; _rtB -> B_8_45_0 =
Copy_of_linkleg_trajectory_contact_acc_rt_TDelayInterpolate ( tMinusDelay ,
0.0 , * uBuffer , _rtDW -> TransportDelay_IWORK_p . CircularBufSize , & _rtDW
-> TransportDelay_IWORK_p . Last , _rtDW -> TransportDelay_IWORK_p . Tail ,
_rtDW -> TransportDelay_IWORK_p . Head , _rtP -> P_20 , 0 , ( boolean_T ) (
ssIsMinorTimeStep ( S ) && ( ( * uBuffer + _rtDW -> TransportDelay_IWORK_p .
CircularBufSize ) [ _rtDW -> TransportDelay_IWORK_p . Head ] == ssGetT ( S )
) ) ) ; } _rtB -> B_8_46_0 = _rtP -> P_21 * _rtB -> B_8_45_0 ; { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay1_PWORK_k . TUbufferPtrs [
0 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay = simTime - _rtP ->
P_22 ; _rtB -> B_8_47_0 =
Copy_of_linkleg_trajectory_contact_acc_rt_TDelayInterpolate ( tMinusDelay ,
0.0 , * uBuffer , _rtDW -> TransportDelay1_IWORK_a . CircularBufSize , &
_rtDW -> TransportDelay1_IWORK_a . Last , _rtDW -> TransportDelay1_IWORK_a .
Tail , _rtDW -> TransportDelay1_IWORK_a . Head , _rtP -> P_23 , 0 , (
boolean_T ) ( ssIsMinorTimeStep ( S ) && ( ( * uBuffer + _rtDW ->
TransportDelay1_IWORK_a . CircularBufSize ) [ _rtDW ->
TransportDelay1_IWORK_a . Head ] == ssGetT ( S ) ) ) ) ; } _rtB -> B_8_48_0 =
_rtP -> P_24 * _rtB -> B_8_47_0 ; isHit = ssIsSampleHit ( S , 2 , 0 ) ; if (
isHit != 0 ) { _rtB -> B_8_49_0 [ 0 ] = _rtDW -> Delay1_DSTATE_b [ 0 ] ; _rtB
-> B_8_50_0 [ 0 ] = _rtDW -> Delay_DSTATE_d [ 0 ] ; _rtB -> B_8_49_0 [ 1 ] =
_rtDW -> Delay1_DSTATE_b [ 1 ] ; _rtB -> B_8_50_0 [ 1 ] = _rtDW ->
Delay_DSTATE_d [ 1 ] ; } ssCallAccelRunBlock ( S , 8 , 51 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 1 , 0 , SS_CALL_MDL_OUTPUTS
) ; ssCallAccelRunBlock ( S , 3 , 0 , SS_CALL_MDL_OUTPUTS ) ;
vm_ReadLocalDSMNoIdx ( S , _rtDW -> dsmIdx , ( char_T * )
 "Copy_of_linkleg_trajectory_contact/Controller/initialize_switch/Initialize_Flag1"
, 0 ) ; _rtB -> B_8_54_0 = _rtDW -> Initialize ; isHit = ssIsSampleHit ( S ,
1 , 0 ) ; if ( isHit != 0 ) { if ( ssIsModeUpdateTimeStep ( S ) ) { _rtDW ->
Compare_Mode_l = ( _rtB -> B_8_54_0 == _rtB -> B_8_2_0_c ) ; } rtb_B_8_55_0 =
_rtDW -> Compare_Mode_l ; if ( _rtDW -> Compare_Mode_l ) { _rtB -> B_8_56_0 =
_rtB -> B_2_0_1 [ 0 ] ; } else { _rtB -> B_8_56_0 = _rtB -> B_8_6_0 ; } } if
( _rtB -> B_8_21_0_p != 0 ) { _rtB -> B_8_57_0 = _rtB -> B_3_0_1 [ 0 ] ; }
else { _rtB -> B_8_57_0 = _rtB -> B_8_56_0 ; } isHit = ssIsSampleHit ( S , 1
, 0 ) ; if ( isHit != 0 ) { { if ( _rtDW ->
TAQSigLogging_InsertedFor_Switch4_at_outport_0_PWORK . AQHandles &&
ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_Switch4_at_outport_0_PWORK . AQHandles ,
ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_8_57_0 + 0 ) ; } } if (
rtb_B_8_55_0 ) { _rtB -> B_8_59_0 = _rtB -> B_2_0_1 [ 1 ] ; } else { _rtB ->
B_8_59_0 = _rtB -> B_8_5_0 ; } } if ( _rtB -> B_8_18_0_b != 0 ) { _rtB ->
B_8_60_0 = _rtB -> B_3_0_1 [ 1 ] ; } else { _rtB -> B_8_60_0 = _rtB ->
B_8_59_0 ; } isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { { if (
_rtDW -> TAQSigLogging_InsertedFor_Switch5_at_outport_0_PWORK . AQHandles &&
ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_Switch5_at_outport_0_PWORK . AQHandles ,
ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_8_60_0 + 0 ) ; } } } _rtB ->
B_8_62_0 = _rtB -> B_8_57_0 - _rtB -> B_8_2_0 [ 2 ] ; _rtB -> B_8_63_0 = _rtP
-> P_27 * _rtB -> B_8_62_0 ; isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit
!= 0 ) { _rtB -> B_8_64_0 = _rtDW -> Filter_DSTATE ; } _rtB -> B_8_65_0 =
_rtB -> B_8_63_0 - _rtB -> B_8_64_0 ; _rtB -> B_8_66_0 = _rtP -> P_30 * _rtB
-> B_8_62_0 ; isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB
-> B_8_67_0 = _rtDW -> Integrator_DSTATE ; } _rtB -> B_8_68_0 = _rtP -> P_33
* _rtB -> B_8_65_0 ; _rtB -> B_8_69_0 = _rtP -> P_34 * _rtB -> B_8_62_0 ;
_rtB -> B_8_70_0 = ( _rtB -> B_8_69_0 + _rtB -> B_8_67_0 ) + _rtB -> B_8_68_0
; if ( ssIsModeUpdateTimeStep ( S ) ) { _rtDW -> Saturation_MODE = _rtB ->
B_8_70_0 >= _rtP -> P_35 ? 1 : _rtB -> B_8_70_0 > _rtP -> P_36 ? 0 : - 1 ; }
_rtB -> B_8_71_0 = _rtDW -> Saturation_MODE == 1 ? _rtP -> P_35 : _rtDW ->
Saturation_MODE == - 1 ? _rtP -> P_36 : _rtB -> B_8_70_0 ; _rtB -> B_8_72_0 =
_rtB -> B_8_60_0 - _rtB -> B_8_2_0 [ 0 ] ; _rtB -> B_8_73_0 = _rtP -> P_37 *
_rtB -> B_8_72_0 ; isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) {
_rtB -> B_8_74_0 = _rtDW -> Filter_DSTATE_g ; } _rtB -> B_8_75_0 = _rtB ->
B_8_73_0 - _rtB -> B_8_74_0 ; _rtB -> B_8_76_0 = _rtP -> P_40 * _rtB ->
B_8_72_0 ; isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtB ->
B_8_77_0 = _rtDW -> Integrator_DSTATE_b ; } _rtB -> B_8_78_0 = _rtP -> P_43 *
_rtB -> B_8_75_0 ; _rtB -> B_8_79_0 = _rtP -> P_44 * _rtB -> B_8_72_0 ; _rtB
-> B_8_80_0 = ( _rtB -> B_8_79_0 + _rtB -> B_8_77_0 ) + _rtB -> B_8_78_0 ; if
( ssIsModeUpdateTimeStep ( S ) ) { _rtDW -> Saturation_MODE_k = _rtB ->
B_8_80_0 >= _rtP -> P_45 ? 1 : _rtB -> B_8_80_0 > _rtP -> P_46 ? 0 : - 1 ; }
_rtB -> B_8_81_0 = _rtDW -> Saturation_MODE_k == 1 ? _rtP -> P_45 : _rtDW ->
Saturation_MODE_k == - 1 ? _rtP -> P_46 : _rtB -> B_8_80_0 ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { { if ( _rtDW ->
TAQSigLogging_InsertedFor_SFunction_at_outport_0_PWORK . AQHandles &&
ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_SFunction_at_outport_0_PWORK . AQHandles ,
ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_8_51_0 [ 0 ] + 0 ) ; } } {
if ( _rtDW -> TAQSigLogging_InsertedFor_Motortotheta_beta_at_outport_0_PWORK
. AQHandles && ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_Motortotheta_beta_at_outport_0_PWORK . AQHandles ,
ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_4_0_1 [ 0 ] + 0 ) ; } } { if
( _rtDW -> TAQSigLogging_InsertedFor_TransportDelay1_at_outport_0_PWORK .
AQHandles && ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_TransportDelay1_at_outport_0_PWORK . AQHandles ,
ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_8_41_0 + 0 ) ; } } { if (
_rtDW -> TAQSigLogging_InsertedFor_TransportDelay_at_outport_0_PWORK .
AQHandles && ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_TransportDelay_at_outport_0_PWORK . AQHandles ,
ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_8_40_0 + 0 ) ; } } } {
real_T * * uBuffer = ( real_T * * ) & _rtDW -> TransportDelay_PWORK_l .
TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S ) ; real_T tMinusDelay ; {
int_T i1 ; real_T * y0 = & _rtB -> B_8_98_0 [ 0 ] ; int_T * iw_Tail = & _rtDW
-> TransportDelay_IWORK_m . Tail [ 0 ] ; int_T * iw_Head = & _rtDW ->
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
isHit != 0 ) { _rtB -> B_8_99_0 [ 0 ] = _rtB -> B_8_46_0 ; _rtB -> B_8_99_0 [
1 ] = _rtB -> B_8_48_0 ; } _rtB -> B_8_107_0 [ 0 ] = _rtB -> B_8_2_0 [ 1 ] ;
_rtB -> B_8_107_0 [ 1 ] = 0.0 ; _rtB -> B_8_107_0 [ 2 ] = 0.0 ; _rtB ->
B_8_107_0 [ 3 ] = 0.0 ; ssCallAccelRunBlock ( S , 8 , 108 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 8 , 109 ,
SS_CALL_MDL_OUTPUTS ) ; _rtB -> B_8_110_0 = _rtB -> B_8_81_0 + _rtB ->
B_8_109_0 ; _rtB -> B_8_123_0 [ 0 ] = _rtB -> B_8_2_0 [ 3 ] ; _rtB ->
B_8_123_0 [ 1 ] = 0.0 ; _rtB -> B_8_123_0 [ 2 ] = 0.0 ; _rtB -> B_8_123_0 [ 3
] = 0.0 ; ssCallAccelRunBlock ( S , 8 , 124 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 8 , 125 , SS_CALL_MDL_OUTPUTS ) ; isHit =
ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0 ) { { if ( _rtDW ->
TAQSigLogging_InsertedFor_PSSimulinkConverter1_at_outport_0_PWORK . AQHandles
&& ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_PSSimulinkConverter1_at_outport_0_PWORK . AQHandles
, ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_8_125_0 + 0 ) ; } } { if (
_rtDW -> TAQSigLogging_InsertedFor_t_at_outport_0_PWORK . AQHandles &&
ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_t_at_outport_0_PWORK . AQHandles , ssGetTaskTime (
S , 1 ) , ( char * ) & _rtB -> B_8_71_0 + 0 ) ; } } } _rtB -> B_8_128_0 =
_rtB -> B_8_71_0 + _rtB -> B_8_125_0 ; _rtB -> B_8_130_0 [ 0 ] = _rtB ->
B_8_110_0 ; _rtB -> B_8_130_0 [ 1 ] = 0.0 ; _rtB -> B_8_130_0 [ 2 ] = 0.0 ;
_rtB -> B_8_130_0 [ 3 ] = 0.0 ; _rtB -> B_8_131_0 [ 0 ] = _rtB -> B_8_128_0 ;
_rtB -> B_8_131_0 [ 1 ] = 0.0 ; _rtB -> B_8_131_0 [ 2 ] = 0.0 ; _rtB ->
B_8_131_0 [ 3 ] = 0.0 ; ssCallAccelRunBlock ( S , 8 , 132 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 8 , 133 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 8 , 145 ,
SS_CALL_MDL_OUTPUTS ) ; isHit = ssIsSampleHit ( S , 1 , 0 ) ; if ( isHit != 0
) { { if ( _rtDW ->
TAQSigLogging_InsertedFor_PSSimulinkConverter2_at_outport_0_PWORK . AQHandles
&& ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_PSSimulinkConverter2_at_outport_0_PWORK . AQHandles
, ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_8_2_0 [ 4 ] + 0 ) ; } } {
if ( _rtDW ->
TAQSigLogging_InsertedFor_PSSimulinkConverter_at_outport_0_PWORK . AQHandles
&& ssGetLogOutput ( S ) ) { sdiWriteSignal ( _rtDW ->
TAQSigLogging_InsertedFor_PSSimulinkConverter_at_outport_0_PWORK . AQHandles
, ssGetTaskTime ( S , 1 ) , ( char * ) & _rtB -> B_8_2_0 [ 5 ] + 0 ) ; } } }
ssCallAccelRunBlock ( S , 8 , 151 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 8 , 152 , SS_CALL_MDL_OUTPUTS ) ;
ssCallAccelRunBlock ( S , 8 , 153 , SS_CALL_MDL_OUTPUTS ) ; UNUSED_PARAMETER
( tid ) ; } static void mdlOutputsTID3 ( SimStruct * S , int_T tid ) {
B_Copy_of_linkleg_trajectory_contact_T * _rtB ;
P_Copy_of_linkleg_trajectory_contact_T * _rtP ; _rtP = ( (
P_Copy_of_linkleg_trajectory_contact_T * ) ssGetModelRtp ( S ) ) ; _rtB = ( (
B_Copy_of_linkleg_trajectory_contact_T * ) _ssGetModelBlockIO ( S ) ) ; _rtB
-> B_8_0_0_m = _rtP -> P_50 ; _rtB -> B_8_2_0_c = _rtP -> P_51 ; _rtB ->
B_8_3_0 = _rtP -> P_52 ; _rtB -> B_8_4_0 = _rtP -> P_53 ; _rtB -> B_8_5_0 =
_rtP -> P_54 ; _rtB -> B_8_6_0 = _rtP -> P_55 ; _rtB -> B_8_8_0 = _rtP ->
P_57 ; _rtB -> B_8_10_0 = _rtP -> P_59 ; _rtB -> B_8_11_0 = _rtP -> P_60 ;
_rtB -> B_8_7_0 [ 0 ] = _rtP -> P_56 [ 0 ] ; _rtB -> B_8_9_0 [ 0 ] = _rtP ->
P_58 [ 0 ] ; _rtB -> B_8_13_0 [ 0 ] = _rtP -> P_61 [ 0 ] ; _rtB -> B_8_14_0 [
0 ] = _rtP -> P_62 [ 0 ] ; _rtB -> B_8_7_0 [ 1 ] = _rtP -> P_56 [ 1 ] ; _rtB
-> B_8_9_0 [ 1 ] = _rtP -> P_58 [ 1 ] ; _rtB -> B_8_13_0 [ 1 ] = _rtP -> P_61
[ 1 ] ; _rtB -> B_8_14_0 [ 1 ] = _rtP -> P_62 [ 1 ] ; _rtB -> B_8_15_0 = _rtP
-> P_63 ; _rtB -> B_8_16_0 = _rtP -> P_64 ; _rtB -> B_8_17_0_k = _rtP -> P_65
; _rtB -> B_8_18_0 = _rtP -> P_66 ; _rtB -> B_8_19_0 = _rtP -> P_67 ; _rtB ->
B_8_20_0_c = _rtP -> P_68 ; ssCallAccelRunBlock ( S , 8 , 324 ,
SS_CALL_MDL_OUTPUTS ) ; ssCallAccelRunBlock ( S , 8 , 325 ,
SS_CALL_MDL_OUTPUTS ) ; UNUSED_PARAMETER ( tid ) ; }
#define MDL_UPDATE
static void mdlUpdate ( SimStruct * S , int_T tid ) {
B_Copy_of_linkleg_trajectory_contact_T * _rtB ;
DW_Copy_of_linkleg_trajectory_contact_T * _rtDW ;
P_Copy_of_linkleg_trajectory_contact_T * _rtP ; int32_T isHit ; _rtDW = ( (
DW_Copy_of_linkleg_trajectory_contact_T * ) ssGetRootDWork ( S ) ) ; _rtP = (
( P_Copy_of_linkleg_trajectory_contact_T * ) ssGetModelRtp ( S ) ) ; _rtB = (
( B_Copy_of_linkleg_trajectory_contact_T * ) _ssGetModelBlockIO ( S ) ) ;
ssCallAccelRunBlock ( S , 8 , 1 , SS_CALL_MDL_UPDATE ) ; isHit =
ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtDW -> Delay3_DSTATE =
_rtB -> B_8_29_0 ; _rtDW -> Delay2_DSTATE = _rtB -> B_8_8_0 ; _rtDW ->
Delay_DSTATE [ 0U ] = _rtDW -> Delay_DSTATE [ 1U ] ; _rtDW -> Delay_DSTATE [
1 ] = _rtB -> B_8_29_0 ; _rtDW -> Delay1_DSTATE [ 0U ] = _rtDW ->
Delay1_DSTATE [ 1U ] ; _rtDW -> Delay1_DSTATE [ 1 ] = _rtB -> B_8_8_0 ; _rtDW
-> Delay_DSTATE_b [ 0 ] = _rtB -> B_8_98_0 [ 0 ] ; _rtDW -> Delay_DSTATE_b [
1 ] = _rtB -> B_8_98_0 [ 1 ] ; _rtDW -> Delay1_DSTATE_a [ 0U ] = _rtDW ->
Delay1_DSTATE_a [ 2U ] ; _rtDW -> Delay1_DSTATE_a [ 1U ] = _rtDW ->
Delay1_DSTATE_a [ 3U ] ; _rtDW -> Delay1_DSTATE_a [ 2 ] = _rtB -> B_8_98_0 [
0 ] ; _rtDW -> Delay1_DSTATE_a [ 3 ] = _rtB -> B_8_98_0 [ 1 ] ; _rtDW ->
Delay3_DSTATE_k = _rtB -> B_8_10_0 ; _rtDW -> Delay2_DSTATE_o = _rtB ->
B_8_11_0 ; _rtDW -> Delay_DSTATE_f [ 0U ] = _rtDW -> Delay_DSTATE_f [ 1U ] ;
_rtDW -> Delay_DSTATE_f [ 1 ] = _rtB -> B_8_10_0 ; _rtDW -> Delay1_DSTATE_p [
0U ] = _rtDW -> Delay1_DSTATE_p [ 1U ] ; _rtDW -> Delay1_DSTATE_p [ 1 ] =
_rtB -> B_8_11_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S ) ;
_rtDW -> TransportDelay_IWORK . Head = ( ( _rtDW -> TransportDelay_IWORK .
Head < ( _rtDW -> TransportDelay_IWORK . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay_IWORK . Head + 1 ) : 0 ) ; if ( _rtDW -> TransportDelay_IWORK
. Head == _rtDW -> TransportDelay_IWORK . Tail ) { if ( !
Copy_of_linkleg_trajectory_contact_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW
-> TransportDelay_IWORK . CircularBufSize , & _rtDW -> TransportDelay_IWORK .
Tail , & _rtDW -> TransportDelay_IWORK . Head , & _rtDW ->
TransportDelay_IWORK . Last , simTime - _rtP -> P_13 , uBuffer , ( boolean_T
) 0 , false , & _rtDW -> TransportDelay_IWORK . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
uBuffer + _rtDW -> TransportDelay_IWORK . CircularBufSize ) [ _rtDW ->
TransportDelay_IWORK . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay_IWORK . Head ] = _rtB -> B_8_2_0 [ 2 ] ; } { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay1_PWORK . TUbufferPtrs [ 0
] ; real_T simTime = ssGetT ( S ) ; _rtDW -> TransportDelay1_IWORK . Head = (
( _rtDW -> TransportDelay1_IWORK . Head < ( _rtDW -> TransportDelay1_IWORK .
CircularBufSize - 1 ) ) ? ( _rtDW -> TransportDelay1_IWORK . Head + 1 ) : 0 )
; if ( _rtDW -> TransportDelay1_IWORK . Head == _rtDW ->
TransportDelay1_IWORK . Tail ) { if ( !
Copy_of_linkleg_trajectory_contact_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW
-> TransportDelay1_IWORK . CircularBufSize , & _rtDW -> TransportDelay1_IWORK
. Tail , & _rtDW -> TransportDelay1_IWORK . Head , & _rtDW ->
TransportDelay1_IWORK . Last , simTime - _rtP -> P_15 , uBuffer , ( boolean_T
) 0 , false , & _rtDW -> TransportDelay1_IWORK . MaxNewBufSize ) ) {
ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } ( *
uBuffer + _rtDW -> TransportDelay1_IWORK . CircularBufSize ) [ _rtDW ->
TransportDelay1_IWORK . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay1_IWORK . Head ] = _rtB -> B_8_2_0 [ 0 ] ; } isHit =
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
_rtDW -> TransportDelay_IWORK_p . Last , simTime - _rtP -> P_19 , uBuffer , (
boolean_T ) 0 , false , & _rtDW -> TransportDelay_IWORK_p . MaxNewBufSize ) )
{ ssSetErrorStatus ( S , "tdelay memory allocation error" ) ; return ; } } (
* uBuffer + _rtDW -> TransportDelay_IWORK_p . CircularBufSize ) [ _rtDW ->
TransportDelay_IWORK_p . Head ] = simTime ; ( * uBuffer ) [ _rtDW ->
TransportDelay_IWORK_p . Head ] = _rtB -> B_8_132_0 [ 9 ] ; } { real_T * *
uBuffer = ( real_T * * ) & _rtDW -> TransportDelay1_PWORK_k . TUbufferPtrs [
0 ] ; real_T simTime = ssGetT ( S ) ; _rtDW -> TransportDelay1_IWORK_a . Head
= ( ( _rtDW -> TransportDelay1_IWORK_a . Head < ( _rtDW ->
TransportDelay1_IWORK_a . CircularBufSize - 1 ) ) ? ( _rtDW ->
TransportDelay1_IWORK_a . Head + 1 ) : 0 ) ; if ( _rtDW ->
TransportDelay1_IWORK_a . Head == _rtDW -> TransportDelay1_IWORK_a . Tail ) {
if ( ! Copy_of_linkleg_trajectory_contact_acc_rt_TDelayUpdateTailOrGrowBuf (
& _rtDW -> TransportDelay1_IWORK_a . CircularBufSize , & _rtDW ->
TransportDelay1_IWORK_a . Tail , & _rtDW -> TransportDelay1_IWORK_a . Head ,
& _rtDW -> TransportDelay1_IWORK_a . Last , simTime - _rtP -> P_22 , uBuffer
, ( boolean_T ) 0 , false , & _rtDW -> TransportDelay1_IWORK_a .
MaxNewBufSize ) ) { ssSetErrorStatus ( S , "tdelay memory allocation error" )
; return ; } } ( * uBuffer + _rtDW -> TransportDelay1_IWORK_a .
CircularBufSize ) [ _rtDW -> TransportDelay1_IWORK_a . Head ] = simTime ; ( *
uBuffer ) [ _rtDW -> TransportDelay1_IWORK_a . Head ] = _rtB -> B_8_132_0 [ 1
] ; } isHit = ssIsSampleHit ( S , 2 , 0 ) ; if ( isHit != 0 ) { _rtDW ->
Delay1_DSTATE_b [ 0 ] = _rtB -> B_8_99_0 [ 0 ] ; _rtDW -> Delay1_DSTATE_b [ 1
] = _rtB -> B_8_99_0 [ 1 ] ; _rtDW -> Delay_DSTATE_d [ 0U ] = _rtDW ->
Delay_DSTATE_d [ 2U ] ; _rtDW -> Delay_DSTATE_d [ 1U ] = _rtDW ->
Delay_DSTATE_d [ 3U ] ; _rtDW -> Delay_DSTATE_d [ 2 ] = _rtB -> B_8_99_0 [ 0
] ; _rtDW -> Delay_DSTATE_d [ 3 ] = _rtB -> B_8_99_0 [ 1 ] ; _rtDW ->
Filter_DSTATE += _rtP -> P_28 * _rtB -> B_8_68_0 ; _rtDW -> Integrator_DSTATE
+= _rtP -> P_31 * _rtB -> B_8_66_0 ; _rtDW -> Filter_DSTATE_g += _rtP -> P_38
* _rtB -> B_8_78_0 ; _rtDW -> Integrator_DSTATE_b += _rtP -> P_41 * _rtB ->
B_8_76_0 ; } { real_T * * uBuffer = ( real_T * * ) & _rtDW ->
TransportDelay_PWORK_l . TUbufferPtrs [ 0 ] ; real_T simTime = ssGetT ( S ) ;
_rtDW -> TransportDelay_IWORK_m . Head [ 0 ] = ( ( _rtDW ->
TransportDelay_IWORK_m . Head [ 0 ] < ( _rtDW -> TransportDelay_IWORK_m .
CircularBufSize [ 0 ] - 1 ) ) ? ( _rtDW -> TransportDelay_IWORK_m . Head [ 0
] + 1 ) : 0 ) ; if ( _rtDW -> TransportDelay_IWORK_m . Head [ 0 ] == _rtDW ->
TransportDelay_IWORK_m . Tail [ 0 ] ) { if ( !
Copy_of_linkleg_trajectory_contact_acc_rt_TDelayUpdateTailOrGrowBuf ( & _rtDW
-> TransportDelay_IWORK_m . CircularBufSize [ 0 ] , & _rtDW ->
TransportDelay_IWORK_m . Tail [ 0 ] , & _rtDW -> TransportDelay_IWORK_m .
Head [ 0 ] , & _rtDW -> TransportDelay_IWORK_m . Last [ 0 ] , simTime - _rtP
-> P_47 , uBuffer , ( boolean_T ) 0 , false , & _rtDW ->
TransportDelay_IWORK_m . MaxNewBufSize ) ) { ssSetErrorStatus ( S ,
"tdelay memory allocation error" ) ; return ; } } ( * uBuffer + _rtDW ->
TransportDelay_IWORK_m . CircularBufSize [ 0 ] ) [ _rtDW ->
TransportDelay_IWORK_m . Head [ 0 ] ] = simTime ; ( * uBuffer ++ ) [ _rtDW ->
TransportDelay_IWORK_m . Head [ 0 ] ] = _rtB -> B_8_51_0 [ 0 ] ; _rtDW ->
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
TransportDelay_IWORK_m . Head [ 1 ] ] = _rtB -> B_8_51_0 [ 1 ] ; }
ssCallAccelRunBlock ( S , 8 , 108 , SS_CALL_MDL_UPDATE ) ;
ssCallAccelRunBlock ( S , 8 , 124 , SS_CALL_MDL_UPDATE ) ; UNUSED_PARAMETER (
tid ) ; }
#define MDL_UPDATE
static void mdlUpdateTID3 ( SimStruct * S , int_T tid ) { UNUSED_PARAMETER (
tid ) ; }
#define MDL_DERIVATIVES
static void mdlDerivatives ( SimStruct * S ) { ssCallAccelRunBlock ( S , 8 ,
1 , SS_CALL_MDL_DERIVATIVES ) ; ssCallAccelRunBlock ( S , 8 , 108 ,
SS_CALL_MDL_DERIVATIVES ) ; ssCallAccelRunBlock ( S , 8 , 124 ,
SS_CALL_MDL_DERIVATIVES ) ; }
#define MDL_PROJECTION
static void mdlProjection ( SimStruct * S ) { ssCallAccelRunBlock ( S , 8 , 1
, SS_CALL_MDL_PROJECTION ) ; ssCallAccelRunBlock ( S , 8 , 108 ,
SS_CALL_MDL_PROJECTION ) ; ssCallAccelRunBlock ( S , 8 , 124 ,
SS_CALL_MDL_PROJECTION ) ; }
#define MDL_FORCINGFUNCTION
static void mdlForcingFunction ( SimStruct * S ) { ssCallAccelRunBlock ( S ,
8 , 1 , SS_CALL_MDL_FORCINGFUNCTION ) ; ssCallAccelRunBlock ( S , 8 , 108 ,
SS_CALL_MDL_FORCINGFUNCTION ) ; ssCallAccelRunBlock ( S , 8 , 124 ,
SS_CALL_MDL_FORCINGFUNCTION ) ; }
#define MDL_MASSMATRIX
static void mdlMassMatrix ( SimStruct * S ) { ssCallAccelRunBlock ( S , 8 , 1
, SS_CALL_MDL_MASSMATRIX ) ; ssCallAccelRunBlock ( S , 8 , 108 ,
SS_CALL_MDL_MASSMATRIX ) ; ssCallAccelRunBlock ( S , 8 , 124 ,
SS_CALL_MDL_MASSMATRIX ) ; }
#define MDL_ZERO_CROSSINGS
static void mdlZeroCrossings ( SimStruct * S ) {
B_Copy_of_linkleg_trajectory_contact_T * _rtB ;
P_Copy_of_linkleg_trajectory_contact_T * _rtP ;
ZCV_Copy_of_linkleg_trajectory_contact_T * _rtZCSV ; _rtZCSV = ( (
ZCV_Copy_of_linkleg_trajectory_contact_T * ) ssGetSolverZcSignalVector ( S )
) ; _rtP = ( ( P_Copy_of_linkleg_trajectory_contact_T * ) ssGetModelRtp ( S )
) ; _rtB = ( ( B_Copy_of_linkleg_trajectory_contact_T * ) _ssGetModelBlockIO
( S ) ) ; _rtZCSV -> Compare_RelopInput_ZC = _rtB -> B_8_17_0 - _rtB ->
B_8_3_0 ; _rtZCSV -> Compare_RelopInput_ZC_g = _rtB -> B_8_20_0 - _rtB ->
B_8_4_0 ; _rtZCSV -> Step_StepTime_ZC = ssGetT ( S ) - _rtP -> P_0 ; _rtZCSV
-> Compare_RelopInput_ZC_o = _rtB -> B_8_54_0 - _rtB -> B_8_2_0_c ; _rtZCSV
-> Saturation_UprLim_ZC = _rtB -> B_8_70_0 - _rtP -> P_35 ; _rtZCSV ->
Saturation_LwrLim_ZC = _rtB -> B_8_70_0 - _rtP -> P_36 ; _rtZCSV ->
Saturation_UprLim_ZC_n = _rtB -> B_8_80_0 - _rtP -> P_45 ; _rtZCSV ->
Saturation_LwrLim_ZC_b = _rtB -> B_8_80_0 - _rtP -> P_46 ; } static void
mdlInitializeSizes ( SimStruct * S ) { ssSetChecksumVal ( S , 0 , 3703320370U
) ; ssSetChecksumVal ( S , 1 , 1097142830U ) ; ssSetChecksumVal ( S , 2 ,
2872968825U ) ; ssSetChecksumVal ( S , 3 , 1505548349U ) ; { mxArray *
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
