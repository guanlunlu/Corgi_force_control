/* Include files */

#include "c_test_sfun.h"
#include "c2_c_test.h"
#define _SF_MEX_LISTEN_FOR_CTRL_C(S)   sf_mex_listen_for_ctrl_c(S);
#ifdef utFree
#undef utFree
#endif

#ifdef utMalloc
#undef utMalloc
#endif

#ifdef __cplusplus

extern "C" void *utMalloc(size_t size);
extern "C" void utFree(void*);

#else

extern void *utMalloc(size_t size);
extern void utFree(void*);

#endif

/* Forward Declarations */

/* Type Definitions */

/* Named Constants */
const int32_T CALL_EVENT = -1;

/* Variable Declarations */

/* Variable Definitions */
static real_T _sfTime_;

/* Function Declarations */
static void initialize_c2_c_test(SFc2_c_testInstanceStruct *chartInstance);
static void initialize_params_c2_c_test(SFc2_c_testInstanceStruct *chartInstance);
static void mdl_start_c2_c_test(SFc2_c_testInstanceStruct *chartInstance);
static void mdl_terminate_c2_c_test(SFc2_c_testInstanceStruct *chartInstance);
static void mdl_setup_runtime_resources_c2_c_test(SFc2_c_testInstanceStruct
  *chartInstance);
static void mdl_cleanup_runtime_resources_c2_c_test(SFc2_c_testInstanceStruct
  *chartInstance);
static void enable_c2_c_test(SFc2_c_testInstanceStruct *chartInstance);
static void disable_c2_c_test(SFc2_c_testInstanceStruct *chartInstance);
static void sf_gateway_c2_c_test(SFc2_c_testInstanceStruct *chartInstance);
static void ext_mode_exec_c2_c_test(SFc2_c_testInstanceStruct *chartInstance);
static void c2_update_jit_animation_c2_c_test(SFc2_c_testInstanceStruct
  *chartInstance);
static void c2_do_animation_call_c2_c_test(SFc2_c_testInstanceStruct
  *chartInstance);
static const mxArray *get_sim_state_c2_c_test(SFc2_c_testInstanceStruct
  *chartInstance);
static void set_sim_state_c2_c_test(SFc2_c_testInstanceStruct *chartInstance,
  const mxArray *c2_st);
static void initSimStructsc2_c_test(SFc2_c_testInstanceStruct *chartInstance);
static real_T c2_emlrt_marshallIn(SFc2_c_testInstanceStruct *chartInstance,
  const mxArray *c2_b_y, const char_T *c2_identifier);
static real_T c2_b_emlrt_marshallIn(SFc2_c_testInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static uint8_T c2_c_emlrt_marshallIn(SFc2_c_testInstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_c_test, const char_T *c2_identifier);
static uint8_T c2_d_emlrt_marshallIn(SFc2_c_testInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId);
static void c2_slStringInitializeDynamicBuffers(SFc2_c_testInstanceStruct
  *chartInstance);
static void c2_chart_data_browse_helper(SFc2_c_testInstanceStruct *chartInstance,
  int32_T c2_ssIdNumber, const mxArray **c2_mxData, uint8_T *c2_isValueTooBig);
static void init_dsm_address_info(SFc2_c_testInstanceStruct *chartInstance);
static void init_simulink_io_address(SFc2_c_testInstanceStruct *chartInstance);

/* Function Definitions */
static void initialize_c2_c_test(SFc2_c_testInstanceStruct *chartInstance)
{
  sim_mode_is_external(chartInstance->S);
  chartInstance->c2_sfEvent = CALL_EVENT;
  _sfTime_ = sf_get_time(chartInstance->S);
  chartInstance->c2_is_active_c2_c_test = 0U;
}

static void initialize_params_c2_c_test(SFc2_c_testInstanceStruct *chartInstance)
{
}

static void mdl_start_c2_c_test(SFc2_c_testInstanceStruct *chartInstance)
{
}

static void mdl_terminate_c2_c_test(SFc2_c_testInstanceStruct *chartInstance)
{
}

static void mdl_setup_runtime_resources_c2_c_test(SFc2_c_testInstanceStruct
  *chartInstance)
{
  static const uint32_T c2_decisionTxtEndIdx = 0U;
  static const uint32_T c2_decisionTxtStartIdx = 0U;
  setDebuggerFlag(chartInstance->S, true);
  setDataBrowseFcn(chartInstance->S, (void *)&c2_chart_data_browse_helper);
  chartInstance->c2_RuntimeVar = sfListenerCacheSimStruct(chartInstance->S);
  sfListenerInitializeRuntimeVars(chartInstance->c2_RuntimeVar,
    &chartInstance->c2_IsDebuggerActive,
    &chartInstance->c2_IsSequenceViewerPresent, 0, 0,
    &chartInstance->c2_mlFcnLineNumber, &chartInstance->c2_IsHeatMapPresent, 0);
  sim_mode_is_external(chartInstance->S);
  covrtCreateStateflowInstanceData(chartInstance->c2_covrtInstance, 1U, 0U, 1U,
    6U);
  covrtChartInitFcn(chartInstance->c2_covrtInstance, 0U, false, false, false);
  covrtStateInitFcn(chartInstance->c2_covrtInstance, 0U, 0U, false, false, false,
                    0U, &c2_decisionTxtStartIdx, &c2_decisionTxtEndIdx);
  covrtTransInitFcn(chartInstance->c2_covrtInstance, 0U, 0, NULL, NULL, 0U, NULL);
  covrtEmlInitFcn(chartInstance->c2_covrtInstance, "", 4U, 0U, 1U, 0U, 0U, 0U,
                  0U, 0U, 0U, 0U, 0U, 0U);
  covrtEmlFcnInitFcn(chartInstance->c2_covrtInstance, 4U, 0U, 0U,
                     "eML_blk_kernel", 0, -1, 81);
}

static void mdl_cleanup_runtime_resources_c2_c_test(SFc2_c_testInstanceStruct
  *chartInstance)
{
  sfListenerLightTerminate(chartInstance->c2_RuntimeVar);
  covrtDeleteStateflowInstanceData(chartInstance->c2_covrtInstance);
}

static void enable_c2_c_test(SFc2_c_testInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void disable_c2_c_test(SFc2_c_testInstanceStruct *chartInstance)
{
  _sfTime_ = sf_get_time(chartInstance->S);
}

static void sf_gateway_c2_c_test(SFc2_c_testInstanceStruct *chartInstance)
{
  real_T c2_b_u1;
  real_T c2_b_u2;
  real_T c2_b_y;
  real_T c2_x;
  chartInstance->c2_JITTransitionAnimation[0] = 0U;
  _sfTime_ = sf_get_time(chartInstance->S);
  covrtSigUpdateFcn(chartInstance->c2_covrtInstance, 1U, *chartInstance->c2_u2);
  covrtSigUpdateFcn(chartInstance->c2_covrtInstance, 0U, *chartInstance->c2_u1);
  chartInstance->c2_sfEvent = CALL_EVENT;
  c2_b_u1 = *chartInstance->c2_u1;
  c2_b_u2 = *chartInstance->c2_u2;
  covrtEmlFcnEval(chartInstance->c2_covrtInstance, 4U, 0, 0);
  c2_x = add_2(c2_b_u1, c2_b_u2);
  c2_b_y = c2_x;
  *chartInstance->c2_y = c2_b_y;
  c2_do_animation_call_c2_c_test(chartInstance);
  covrtSigUpdateFcn(chartInstance->c2_covrtInstance, 2U, *chartInstance->c2_y);
}

static void ext_mode_exec_c2_c_test(SFc2_c_testInstanceStruct *chartInstance)
{
}

static void c2_update_jit_animation_c2_c_test(SFc2_c_testInstanceStruct
  *chartInstance)
{
}

static void c2_do_animation_call_c2_c_test(SFc2_c_testInstanceStruct
  *chartInstance)
{
  sfDoAnimationWrapper(chartInstance->S, false, true);
  sfDoAnimationWrapper(chartInstance->S, false, false);
}

static const mxArray *get_sim_state_c2_c_test(SFc2_c_testInstanceStruct
  *chartInstance)
{
  const mxArray *c2_b_y = NULL;
  const mxArray *c2_c_y = NULL;
  const mxArray *c2_d_y = NULL;
  const mxArray *c2_st;
  c2_st = NULL;
  c2_st = NULL;
  c2_b_y = NULL;
  sf_mex_assign(&c2_b_y, sf_mex_createcellmatrix(2, 1), false);
  c2_c_y = NULL;
  sf_mex_assign(&c2_c_y, sf_mex_create("y", chartInstance->c2_y, 0, 0U, 0U, 0U,
    0), false);
  sf_mex_setcell(c2_b_y, 0, c2_c_y);
  c2_d_y = NULL;
  sf_mex_assign(&c2_d_y, sf_mex_create("y",
    &chartInstance->c2_is_active_c2_c_test, 3, 0U, 0U, 0U, 0), false);
  sf_mex_setcell(c2_b_y, 1, c2_d_y);
  sf_mex_assign(&c2_st, c2_b_y, false);
  return c2_st;
}

static void set_sim_state_c2_c_test(SFc2_c_testInstanceStruct *chartInstance,
  const mxArray *c2_st)
{
  const mxArray *c2_u;
  chartInstance->c2_doneDoubleBufferReInit = true;
  c2_u = sf_mex_dup(c2_st);
  *chartInstance->c2_y = c2_emlrt_marshallIn(chartInstance, sf_mex_dup
    (sf_mex_getcell(c2_u, 0)), "y");
  chartInstance->c2_is_active_c2_c_test = c2_c_emlrt_marshallIn(chartInstance,
    sf_mex_dup(sf_mex_getcell(c2_u, 1)), "is_active_c2_c_test");
  sf_mex_destroy(&c2_u);
  sf_mex_destroy(&c2_st);
}

static void initSimStructsc2_c_test(SFc2_c_testInstanceStruct *chartInstance)
{
}

const mxArray *sf_c2_c_test_get_eml_resolved_functions_info()
{
  const mxArray *c2_nameCaptureInfo = NULL;
  c2_nameCaptureInfo = NULL;
  sf_mex_assign(&c2_nameCaptureInfo, sf_mex_create("nameCaptureInfo", NULL, 0,
    0U, 1U, 0U, 2, 0, 1), false);
  return c2_nameCaptureInfo;
}

static real_T c2_emlrt_marshallIn(SFc2_c_testInstanceStruct *chartInstance,
  const mxArray *c2_b_y, const char_T *c2_identifier)
{
  emlrtMsgIdentifier c2_thisId;
  real_T c2_c_y;
  c2_thisId.fIdentifier = const_cast<const char_T *>(c2_identifier);
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_c_y = c2_b_emlrt_marshallIn(chartInstance, sf_mex_dup(c2_b_y), &c2_thisId);
  sf_mex_destroy(&c2_b_y);
  return c2_c_y;
}

static real_T c2_b_emlrt_marshallIn(SFc2_c_testInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  real_T c2_b_y;
  real_T c2_d;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_d, 1, 0, 0U, 0, 0U, 0);
  c2_b_y = c2_d;
  sf_mex_destroy(&c2_u);
  return c2_b_y;
}

static uint8_T c2_c_emlrt_marshallIn(SFc2_c_testInstanceStruct *chartInstance,
  const mxArray *c2_b_is_active_c2_c_test, const char_T *c2_identifier)
{
  emlrtMsgIdentifier c2_thisId;
  uint8_T c2_b_y;
  c2_thisId.fIdentifier = const_cast<const char_T *>(c2_identifier);
  c2_thisId.fParent = NULL;
  c2_thisId.bParentIsCell = false;
  c2_b_y = c2_d_emlrt_marshallIn(chartInstance, sf_mex_dup
    (c2_b_is_active_c2_c_test), &c2_thisId);
  sf_mex_destroy(&c2_b_is_active_c2_c_test);
  return c2_b_y;
}

static uint8_T c2_d_emlrt_marshallIn(SFc2_c_testInstanceStruct *chartInstance,
  const mxArray *c2_u, const emlrtMsgIdentifier *c2_parentId)
{
  uint8_T c2_b_u;
  uint8_T c2_b_y;
  sf_mex_import(c2_parentId, sf_mex_dup(c2_u), &c2_b_u, 1, 3, 0U, 0, 0U, 0);
  c2_b_y = c2_b_u;
  sf_mex_destroy(&c2_u);
  return c2_b_y;
}

static void c2_slStringInitializeDynamicBuffers(SFc2_c_testInstanceStruct
  *chartInstance)
{
}

static void c2_chart_data_browse_helper(SFc2_c_testInstanceStruct *chartInstance,
  int32_T c2_ssIdNumber, const mxArray **c2_mxData, uint8_T *c2_isValueTooBig)
{
  real_T c2_d;
  real_T c2_d1;
  real_T c2_d2;
  *c2_mxData = NULL;
  *c2_mxData = NULL;
  *c2_isValueTooBig = 0U;
  switch (c2_ssIdNumber) {
   case 4U:
    c2_d = *chartInstance->c2_u1;
    sf_mex_assign(c2_mxData, sf_mex_create("mxData", &c2_d, 0, 0U, 0U, 0U, 0),
                  false);
    break;

   case 5U:
    c2_d1 = *chartInstance->c2_y;
    sf_mex_assign(c2_mxData, sf_mex_create("mxData", &c2_d1, 0, 0U, 0U, 0U, 0),
                  false);
    break;

   case 6U:
    c2_d2 = *chartInstance->c2_u2;
    sf_mex_assign(c2_mxData, sf_mex_create("mxData", &c2_d2, 0, 0U, 0U, 0U, 0),
                  false);
    break;
  }
}

static void init_dsm_address_info(SFc2_c_testInstanceStruct *chartInstance)
{
}

static void init_simulink_io_address(SFc2_c_testInstanceStruct *chartInstance)
{
  chartInstance->c2_covrtInstance = (CovrtStateflowInstance *)
    sfrtGetCovrtInstance(chartInstance->S);
  chartInstance->c2_fEmlrtCtx = (void *)sfrtGetEmlrtCtx(chartInstance->S);
  chartInstance->c2_u1 = (real_T *)ssGetInputPortSignal_wrapper(chartInstance->S,
    0);
  chartInstance->c2_y = (real_T *)ssGetOutputPortSignal_wrapper(chartInstance->S,
    1);
  chartInstance->c2_u2 = (real_T *)ssGetInputPortSignal_wrapper(chartInstance->S,
    1);
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* SFunction Glue Code */
void sf_c2_c_test_get_check_sum(mxArray *plhs[])
{
  ((real_T *)mxGetPr((plhs[0])))[0] = (real_T)(485966425U);
  ((real_T *)mxGetPr((plhs[0])))[1] = (real_T)(1770464895U);
  ((real_T *)mxGetPr((plhs[0])))[2] = (real_T)(2091689071U);
  ((real_T *)mxGetPr((plhs[0])))[3] = (real_T)(2088938844U);
}

mxArray *sf_c2_c_test_third_party_uses_info(void)
{
  mxArray * mxcell3p = mxCreateCellMatrix(1,0);
  return(mxcell3p);
}

mxArray *sf_c2_c_test_jit_fallback_info(void)
{
  const char *infoFields[] = { "fallbackType", "fallbackReason",
    "hiddenFallbackType", "hiddenFallbackReason", "incompatibleSymbol" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 5, infoFields);
  mxArray *fallbackType = mxCreateString("late");
  mxArray *fallbackReason = mxCreateString("ir_function_calls");
  mxArray *hiddenFallbackType = mxCreateString("");
  mxArray *hiddenFallbackReason = mxCreateString("");
  mxArray *incompatibleSymbol = mxCreateString("add_2");
  mxSetField(mxInfo, 0, infoFields[0], fallbackType);
  mxSetField(mxInfo, 0, infoFields[1], fallbackReason);
  mxSetField(mxInfo, 0, infoFields[2], hiddenFallbackType);
  mxSetField(mxInfo, 0, infoFields[3], hiddenFallbackReason);
  mxSetField(mxInfo, 0, infoFields[4], incompatibleSymbol);
  return mxInfo;
}

mxArray *sf_c2_c_test_updateBuildInfo_args_info(void)
{
  mxArray *mxBIArgs = mxCreateCellMatrix(1,0);
  return mxBIArgs;
}

static const mxArray *sf_get_sim_state_info_c2_c_test(void)
{
  const char *infoFields[] = { "chartChecksum", "varInfo" };

  mxArray *mxInfo = mxCreateStructMatrix(1, 1, 2, infoFields);
  mxArray *mxVarInfo = sf_mex_decode(
    "eNpjYPT0ZQACPiD+wMjAwAakOYCYiQECWKF8RqgYI1ycBS6uAMQllQWpIPHiomTPFCCdl5gL5ie"
    "WVnjmpeWDzbdgQJjPhsV8RiTzOaHiEPDBnjL9Ig4g/QZI+lkI6BcAsiqh4QILH/LtV3CgTD/Efg"
    "8C7hdGcT+En1kcn5hcklmWGp9sFJ8cX5JaXAI3DwQARZ8XKg=="
    );
  mxArray *mxChecksum = mxCreateDoubleMatrix(1, 4, mxREAL);
  sf_c2_c_test_get_check_sum(&mxChecksum);
  mxSetField(mxInfo, 0, infoFields[0], mxChecksum);
  mxSetField(mxInfo, 0, infoFields[1], mxVarInfo);
  return mxInfo;
}

static const char* sf_get_instance_specialization(void)
{
  return "s9jzng0WD4R1U6jP4bUGkEE";
}

static void sf_opaque_initialize_c2_c_test(void *chartInstanceVar)
{
  initialize_params_c2_c_test((SFc2_c_testInstanceStruct*) chartInstanceVar);
  initialize_c2_c_test((SFc2_c_testInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_enable_c2_c_test(void *chartInstanceVar)
{
  enable_c2_c_test((SFc2_c_testInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_disable_c2_c_test(void *chartInstanceVar)
{
  disable_c2_c_test((SFc2_c_testInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_gateway_c2_c_test(void *chartInstanceVar)
{
  sf_gateway_c2_c_test((SFc2_c_testInstanceStruct*) chartInstanceVar);
}

static const mxArray* sf_opaque_get_sim_state_c2_c_test(SimStruct* S)
{
  return get_sim_state_c2_c_test((SFc2_c_testInstanceStruct *)
    sf_get_chart_instance_ptr(S));     /* raw sim ctx */
}

static void sf_opaque_set_sim_state_c2_c_test(SimStruct* S, const mxArray *st)
{
  set_sim_state_c2_c_test((SFc2_c_testInstanceStruct*)sf_get_chart_instance_ptr
    (S), st);
}

static void sf_opaque_cleanup_runtime_resources_c2_c_test(void *chartInstanceVar)
{
  if (chartInstanceVar!=NULL) {
    SimStruct *S = ((SFc2_c_testInstanceStruct*) chartInstanceVar)->S;
    if (sim_mode_is_rtw_gen(S) || sim_mode_is_external(S)) {
      sf_clear_rtw_identifier(S);
      unload_c_test_optimization_info();
    }

    mdl_cleanup_runtime_resources_c2_c_test((SFc2_c_testInstanceStruct*)
      chartInstanceVar);
    ((SFc2_c_testInstanceStruct*) chartInstanceVar)->~SFc2_c_testInstanceStruct();
    utFree(chartInstanceVar);
    if (ssGetUserData(S)!= NULL) {
      sf_free_ChartRunTimeInfo(S);
    }

    ssSetUserData(S,NULL);
  }
}

static void sf_opaque_mdl_start_c2_c_test(void *chartInstanceVar)
{
  mdl_start_c2_c_test((SFc2_c_testInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_mdl_terminate_c2_c_test(void *chartInstanceVar)
{
  mdl_terminate_c2_c_test((SFc2_c_testInstanceStruct*) chartInstanceVar);
}

static void sf_opaque_init_subchart_simstructs(void *chartInstanceVar)
{
  initSimStructsc2_c_test((SFc2_c_testInstanceStruct*) chartInstanceVar);
}

extern unsigned int sf_machine_global_initializer_called(void);
static void mdlProcessParameters_c2_c_test(SimStruct *S)
{
  int i;
  for (i=0;i<ssGetNumRunTimeParams(S);i++) {
    if (ssGetSFcnParamTunable(S,i)) {
      ssUpdateDlgParamAsRunTimeParam(S,i);
    }
  }

  sf_warn_if_symbolic_dimension_param_changed(S);
  if (sf_machine_global_initializer_called()) {
    initialize_params_c2_c_test((SFc2_c_testInstanceStruct*)
      sf_get_chart_instance_ptr(S));
    initSimStructsc2_c_test((SFc2_c_testInstanceStruct*)
      sf_get_chart_instance_ptr(S));
  }
}

const char* sf_c2_c_test_get_post_codegen_info(void)
{
  int i;
  const char* encStrCodegen [22] = {
    "eNrtWN2O20QUdqLtihWwWmmRUCUEveCCm0oFChQJld1NnBJpl43qZCshodXEPomnGY/d+ckmFY/",
    "BNeJBEIK34IZ34JJLzjhONnVCMpNQaFG98jpj+5vvnDPnb+xVmmceHvt4jm563i5eX8Oz6k2OG8",
    "W4MndO7u94XxTj7173vDCNoA880L0eHXluB9dJiwiSSM/94CSBhyBTphVNeZP3Unss5T0QwEOcI",
    "EuFcuKVNNGM8kFD89Awy0cxDeMgTjWLTnBCEp1zNv473kyrFjLWqYBQNQAiFYtU9+MGI/3VVhDq",
    "qhZDOJA6cbaVBBXozKgqzzRTNGPgjyBscqkIWkGu0TdQREFNjdyMbPSVwRSdJhmjhNvbOiYygAy",
    "9Q0Eni/D/uVZoPStsGBOhTiAmQ5CndJCzpxys2KnEt7uUE5UKSpifsJqZzVLfFkMdzzAkmOsaob",
    "4nAsggSylXjgERNNDOPiddBnXo6r4jbwBPtImGCwpXINzWt1dLhyBIH865m8z5Gvmj3ClnsWSJV",
    "TSBCyKOQ/RdCZFb3sCgkwFBd4Q2TuOEhdzETdkWdIi+4Zrrmib8N8p1Opl4v9wIm/P6Q3D2qxlv",
    "I+Q1wph0w7bT7BSGwHL+OlFkA+yE3wEsJY3aKXqHyTaOGUtzipFQYGspj6i9Vw5LqLywfY1FygJ",
    "OExMGEKGZZ6LPJloXR1qqNKlhyqmfnlryLWKbXIHokRCsa4wgVAIKnPuVI29EpQkkRKOVVK6l9Q",
    "yTGNwI6sme5vWrVAzQxq7F7NpWJhLc0BD1MTEryJOcj959QZi2lDmRfYwfdI+OxCzrxotYEz8bg",
    "UMSxhCZykkZnGGexQlsl1iakn+M2g6pGtdBhoJmtpGkMaFj0TVWao8z6PABT694Q6RJUHReK/wK",
    "ALMGEZzy/gmWcDFuoPB2Ugt40s6zu2uTY+xMFCNd4xsPgGM1NLqaroGEGFU+xxYZBdoGG9Cn2MR",
    "wSaXCQj2elPpJ3TP9+5F33b/vLOnf9+b694NiHH50GV4qkNPOxsxzZ26eNyz2ATY4bwF3zTe9fj",
    "CHryzh9eauZb696rPvV0t8VfyrVBbt9GaJZ6eE2y1sxX/69dv3v//lh8PmZz+/+/vtT9bxVxb4K",
    "/lvg/ux6rbP2i/G70z7pVl2Hi4kMPPuV2v84O2SH5ix/PzxU96/86h+9+GHnU8ft+52Ow8Gvp/P",
    "90dltbzVkrzT+7dMj4bBm+cCETajYr9mxkRP9hFm/ntz8u6uscfenD+hZF9uh3/rqLyOO2vwB/h",
    "rXPLbzflvHW2Ht1vvw9J6H+Y9+yUxmRkun80A+5bxtcq/XXHev4x7WeR8ZZfnr59NfatuiKs8x3",
    "r6T+K21c+1br/s76+qF17p/YMXWI9V+d6lf3vR9PrNc+uv3ivG92ffDWoxZdGSnUvxGDcXvWVP/",
    "yf+/aej/ab9pG/sV3xg/ubjY07YGLcqk61gcbslzHfC2SMBRC7fD/4X9WRZP7esn7pRim8z7rQb",
    "t+9tUZf+AqdXD5Q=",
    ""
  };

  static char newstr [1517] = "";
  newstr[0] = '\0';
  for (i = 0; i < 22; i++) {
    strcat(newstr, encStrCodegen[i]);
  }

  return newstr;
}

static void mdlSetWorkWidths_c2_c_test(SimStruct *S)
{
  const char* newstr = sf_c2_c_test_get_post_codegen_info();
  sf_set_work_widths(S, newstr);
  ssSetChecksum0(S,(1572977774U));
  ssSetChecksum1(S,(2663420964U));
  ssSetChecksum2(S,(3191294227U));
  ssSetChecksum3(S,(892198174U));
}

static void mdlRTW_c2_c_test(SimStruct *S)
{
  if (sim_mode_is_rtw_gen(S)) {
    ssWriteRTWStrParam(S, "StateflowChartType", "Embedded MATLAB");
  }
}

static void mdlSetupRuntimeResources_c2_c_test(SimStruct *S)
{
  SFc2_c_testInstanceStruct *chartInstance;
  chartInstance = (SFc2_c_testInstanceStruct *)utMalloc(sizeof
    (SFc2_c_testInstanceStruct));
  if (chartInstance==NULL) {
    sf_mex_error_message("Could not allocate memory for chart instance.");
  }

  memset(chartInstance, 0, sizeof(SFc2_c_testInstanceStruct));
  chartInstance = new (chartInstance) SFc2_c_testInstanceStruct;
  chartInstance->chartInfo.chartInstance = chartInstance;
  chartInstance->chartInfo.isEMLChart = 1;
  chartInstance->chartInfo.chartInitialized = 0;
  chartInstance->chartInfo.sFunctionGateway = sf_opaque_gateway_c2_c_test;
  chartInstance->chartInfo.initializeChart = sf_opaque_initialize_c2_c_test;
  chartInstance->chartInfo.mdlStart = sf_opaque_mdl_start_c2_c_test;
  chartInstance->chartInfo.mdlTerminate = sf_opaque_mdl_terminate_c2_c_test;
  chartInstance->chartInfo.mdlCleanupRuntimeResources =
    sf_opaque_cleanup_runtime_resources_c2_c_test;
  chartInstance->chartInfo.enableChart = sf_opaque_enable_c2_c_test;
  chartInstance->chartInfo.disableChart = sf_opaque_disable_c2_c_test;
  chartInstance->chartInfo.getSimState = sf_opaque_get_sim_state_c2_c_test;
  chartInstance->chartInfo.setSimState = sf_opaque_set_sim_state_c2_c_test;
  chartInstance->chartInfo.getSimStateInfo = sf_get_sim_state_info_c2_c_test;
  chartInstance->chartInfo.zeroCrossings = NULL;
  chartInstance->chartInfo.outputs = NULL;
  chartInstance->chartInfo.derivatives = NULL;
  chartInstance->chartInfo.mdlRTW = mdlRTW_c2_c_test;
  chartInstance->chartInfo.mdlSetWorkWidths = mdlSetWorkWidths_c2_c_test;
  chartInstance->chartInfo.extModeExec = NULL;
  chartInstance->chartInfo.restoreLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.restoreBeforeLastMajorStepConfiguration = NULL;
  chartInstance->chartInfo.storeCurrentConfiguration = NULL;
  chartInstance->chartInfo.callAtomicSubchartUserFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartAutoFcn = NULL;
  chartInstance->chartInfo.callAtomicSubchartEventFcn = NULL;
  chartInstance->chartInfo.chartStateSetterFcn = NULL;
  chartInstance->chartInfo.chartStateGetterFcn = NULL;
  chartInstance->S = S;
  chartInstance->chartInfo.dispatchToExportedFcn = NULL;
  sf_init_ChartRunTimeInfo(S, &(chartInstance->chartInfo), false, 0,
    chartInstance->c2_JITStateAnimation,
    chartInstance->c2_JITTransitionAnimation);
  init_dsm_address_info(chartInstance);
  init_simulink_io_address(chartInstance);
  if (!sim_mode_is_rtw_gen(S)) {
  }

  mdl_setup_runtime_resources_c2_c_test(chartInstance);
}

void c2_c_test_method_dispatcher(SimStruct *S, int_T method, void *data)
{
  switch (method) {
   case SS_CALL_MDL_SETUP_RUNTIME_RESOURCES:
    mdlSetupRuntimeResources_c2_c_test(S);
    break;

   case SS_CALL_MDL_SET_WORK_WIDTHS:
    mdlSetWorkWidths_c2_c_test(S);
    break;

   case SS_CALL_MDL_PROCESS_PARAMETERS:
    mdlProcessParameters_c2_c_test(S);
    break;

   default:
    /* Unhandled method */
    sf_mex_error_message("Stateflow Internal Error:\n"
                         "Error calling c2_c_test_method_dispatcher.\n"
                         "Can't handle method %d.\n", method);
    break;
  }
}
