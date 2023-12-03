#ifndef __c2_c_test_h__
#define __c2_c_test_h__

/* Forward Declarations */
struct SFc2_c_testInstanceStruct;

/* Type Definitions */
#ifndef typedef_c2_c_testStackData
#define typedef_c2_c_testStackData

typedef struct {
} c2_c_testStackData;

#endif                                 /* typedef_c2_c_testStackData */

#ifndef struct_SFc2_c_testInstanceStruct
#define struct_SFc2_c_testInstanceStruct

struct SFc2_c_testInstanceStruct
{
  SimStruct *S;
  ChartInfoStruct chartInfo;
  int32_T c2_sfEvent;
  boolean_T c2_doneDoubleBufferReInit;
  uint8_T c2_is_active_c2_c_test;
  uint8_T c2_JITStateAnimation[1];
  uint8_T c2_JITTransitionAnimation[1];
  int32_T c2_IsDebuggerActive;
  int32_T c2_IsSequenceViewerPresent;
  int32_T c2_SequenceViewerOptimization;
  int32_T c2_IsHeatMapPresent;
  void *c2_RuntimeVar;
  uint32_T c2_mlFcnLineNumber;
  void *c2_fcnDataPtrs[4];
  char_T *c2_dataNames[4];
  uint32_T c2_numFcnVars;
  uint32_T c2_ssIds[4];
  uint32_T c2_statuses[4];
  void *c2_outMexFcns[4];
  void *c2_inMexFcns[4];
  CovrtStateflowInstance *c2_covrtInstance;
  void *c2_fEmlrtCtx;
  real_T *c2_u1;
  real_T *c2_y;
  real_T *c2_u2;
};

#endif                                 /* struct_SFc2_c_testInstanceStruct */

/* Named Constants */

/* Variable Declarations */

/* Variable Definitions */

/* Function Declarations */
extern const mxArray *sf_c2_c_test_get_eml_resolved_functions_info();

/* Function Definitions */
extern void sf_c2_c_test_get_check_sum(mxArray *plhs[]);
extern void c2_c_test_method_dispatcher(SimStruct *S, int_T method, void *data);

#endif
