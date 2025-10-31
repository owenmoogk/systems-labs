/*
 * cart_trial_simple.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "cart_trial_simple".
 *
 * Model version              : 1.99
 * Simulink Coder version : 9.6 (R2021b) 14-May-2021
 * C source code generated on : Fri Oct 31 10:19:00 2025
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "cart_trial_simple.h"
#include "cart_trial_simple_private.h"
#include "cart_trial_simple_dt.h"

/* Block signals (default storage) */
B_cart_trial_simple_T cart_trial_simple_B;

/* Continuous states */
X_cart_trial_simple_T cart_trial_simple_X;

/* Block states (default storage) */
DW_cart_trial_simple_T cart_trial_simple_DW;

/* Real-time model */
static RT_MODEL_cart_trial_simple_T cart_trial_simple_M_;
RT_MODEL_cart_trial_simple_T *const cart_trial_simple_M = &cart_trial_simple_M_;

/*
 * This function updates continuous states using the ODE3 fixed-step
 * solver algorithm
 */
static void rt_ertODEUpdateContinuousStates(RTWSolverInfo *si )
{
  /* Solver Matrices */
  static const real_T rt_ODE3_A[3] = {
    1.0/2.0, 3.0/4.0, 1.0
  };

  static const real_T rt_ODE3_B[3][3] = {
    { 1.0/2.0, 0.0, 0.0 },

    { 0.0, 3.0/4.0, 0.0 },

    { 2.0/9.0, 1.0/3.0, 4.0/9.0 }
  };

  time_T t = rtsiGetT(si);
  time_T tnew = rtsiGetSolverStopTime(si);
  time_T h = rtsiGetStepSize(si);
  real_T *x = rtsiGetContStates(si);
  ODE3_IntgData *id = (ODE3_IntgData *)rtsiGetSolverData(si);
  real_T *y = id->y;
  real_T *f0 = id->f[0];
  real_T *f1 = id->f[1];
  real_T *f2 = id->f[2];
  real_T hB[3];
  int_T i;
  int_T nXc = 1;
  rtsiSetSimTimeStep(si,MINOR_TIME_STEP);

  /* Save the state values at time t in y, we'll use x as ynew. */
  (void) memcpy(y, x,
                (uint_T)nXc*sizeof(real_T));

  /* Assumes that rtsiSetT and ModelOutputs are up-to-date */
  /* f0 = f(t,y) */
  rtsiSetdX(si, f0);
  cart_trial_simple_derivatives();

  /* f(:,2) = feval(odefile, t + hA(1), y + f*hB(:,1), args(:)(*)); */
  hB[0] = h * rt_ODE3_B[0][0];
  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[0]);
  rtsiSetdX(si, f1);
  cart_trial_simple_output();
  cart_trial_simple_derivatives();

  /* f(:,3) = feval(odefile, t + hA(2), y + f*hB(:,2), args(:)(*)); */
  for (i = 0; i <= 1; i++) {
    hB[i] = h * rt_ODE3_B[1][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1]);
  }

  rtsiSetT(si, t + h*rt_ODE3_A[1]);
  rtsiSetdX(si, f2);
  cart_trial_simple_output();
  cart_trial_simple_derivatives();

  /* tnew = t + hA(3);
     ynew = y + f*hB(:,3); */
  for (i = 0; i <= 2; i++) {
    hB[i] = h * rt_ODE3_B[2][i];
  }

  for (i = 0; i < nXc; i++) {
    x[i] = y[i] + (f0[i]*hB[0] + f1[i]*hB[1] + f2[i]*hB[2]);
  }

  rtsiSetT(si, tnew);
  rtsiSetSimTimeStep(si,MAJOR_TIME_STEP);
}

/* Model output function */
void cart_trial_simple_output(void)
{
  /* local block i/o variables */
  real_T rtb_InverseModulus1;
  real_T rtb_HILReadEncoder2;
  real_T rtb_Sum2;
  real_T rtb_Sum2_tmp;
  real_T *lastU;
  if (rtmIsMajorTimeStep(cart_trial_simple_M)) {
    /* set solver stop time */
    if (!(cart_trial_simple_M->Timing.clockTick0+1)) {
      rtsiSetSolverStopTime(&cart_trial_simple_M->solverInfo,
                            ((cart_trial_simple_M->Timing.clockTickH0 + 1) *
        cart_trial_simple_M->Timing.stepSize0 * 4294967296.0));
    } else {
      rtsiSetSolverStopTime(&cart_trial_simple_M->solverInfo,
                            ((cart_trial_simple_M->Timing.clockTick0 + 1) *
        cart_trial_simple_M->Timing.stepSize0 +
        cart_trial_simple_M->Timing.clockTickH0 *
        cart_trial_simple_M->Timing.stepSize0 * 4294967296.0));
    }
  }                                    /* end MajorTimeStep */

  /* Update absolute time of base rate at minor time step */
  if (rtmIsMinorTimeStep(cart_trial_simple_M)) {
    cart_trial_simple_M->Timing.t[0] = rtsiGetT(&cart_trial_simple_M->solverInfo);
  }

  if (rtmIsMajorTimeStep(cart_trial_simple_M)) {
    /* S-Function (hil_read_encoder_block): '<S1>/HIL Read Encoder1' */

    /* S-Function Block: cart_trial_simple/Quarc_Plant2/HIL Read Encoder1 (hil_read_encoder_block) */
    {
      t_error result = hil_read_encoder(cart_trial_simple_DW.HILInitialize_Card,
        &cart_trial_simple_P.HILReadEncoder1_channels, 1,
        &cart_trial_simple_DW.HILReadEncoder1_Buffer);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(cart_trial_simple_M, _rt_error_message);
      } else {
        rtb_HILReadEncoder2 = cart_trial_simple_DW.HILReadEncoder1_Buffer;
      }
    }

    /* Gain: '<S1>/mm//cn' */
    cart_trial_simple_B.mmcn = cart_trial_simple_P.mmcn_Gain *
      rtb_HILReadEncoder2;

    /* S-Function (inverse_modulus_block): '<S1>/Inverse Modulus' */
    /* S-Function Block: cart_trial_simple/Quarc_Plant2/Inverse Modulus (inverse_modulus_block) */
    {
      static const real_T sampling_period = 0.001;
      real_T half_range = cart_trial_simple_P.InverseModulus_Modulus / 2.0;
      real_T du, dy;
      if (cart_trial_simple_DW.InverseModulus_FirstSample) {
        cart_trial_simple_DW.InverseModulus_FirstSample = false;
        cart_trial_simple_DW.InverseModulus_PreviousInput =
          cart_trial_simple_B.mmcn;
      }

      du = (real_T) cart_trial_simple_B.mmcn -
        cart_trial_simple_DW.InverseModulus_PreviousInput;
      if (du > half_range) {
        cart_trial_simple_DW.InverseModulus_Revolutions =
          cart_trial_simple_DW.InverseModulus_Revolutions - 1;
        dy = du - cart_trial_simple_P.InverseModulus_Modulus;
      } else if (du < -half_range) {
        cart_trial_simple_DW.InverseModulus_Revolutions =
          cart_trial_simple_DW.InverseModulus_Revolutions + 1;
        dy = du + cart_trial_simple_P.InverseModulus_Modulus;
      } else {
        dy = du;
      }

      cart_trial_simple_B.InverseModulus = cart_trial_simple_B.mmcn +
        cart_trial_simple_DW.InverseModulus_Revolutions *
        cart_trial_simple_P.InverseModulus_Modulus;
      cart_trial_simple_DW.InverseModulus_PreviousInput =
        cart_trial_simple_B.mmcn;
    }

    /* S-Function (hil_read_encoder_block): '<S1>/HIL Read Encoder 2' */

    /* S-Function Block: cart_trial_simple/Quarc_Plant2/HIL Read Encoder 2 (hil_read_encoder_block) */
    {
      t_error result = hil_read_encoder(cart_trial_simple_DW.HILInitialize_Card,
        &cart_trial_simple_P.HILReadEncoder2_channels, 1,
        &cart_trial_simple_DW.HILReadEncoder2_Buffer);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(cart_trial_simple_M, _rt_error_message);
      } else {
        rtb_HILReadEncoder2 = cart_trial_simple_DW.HILReadEncoder2_Buffer;
      }
    }

    /* Gain: '<S1>/mm//cn - 2' */
    cart_trial_simple_B.mmcn2 = cart_trial_simple_P.mmcn2_Gain *
      rtb_HILReadEncoder2;

    /* S-Function (inverse_modulus_block): '<S1>/Inverse Modulus1' */
    /* S-Function Block: cart_trial_simple/Quarc_Plant2/Inverse Modulus1 (inverse_modulus_block) */
    {
      static const real_T sampling_period = 0.001;
      real_T half_range = cart_trial_simple_P.InverseModulus1_Modulus / 2.0;
      real_T du, dy;
      if (cart_trial_simple_DW.InverseModulus1_FirstSample) {
        cart_trial_simple_DW.InverseModulus1_FirstSample = false;
        cart_trial_simple_DW.InverseModulus1_PreviousInput =
          cart_trial_simple_B.mmcn2;
      }

      du = (real_T) cart_trial_simple_B.mmcn2 -
        cart_trial_simple_DW.InverseModulus1_PreviousInput;
      if (du > half_range) {
        cart_trial_simple_DW.InverseModulus1_Revolutions =
          cart_trial_simple_DW.InverseModulus1_Revolutions - 1;
        dy = du - cart_trial_simple_P.InverseModulus1_Modulus;
      } else if (du < -half_range) {
        cart_trial_simple_DW.InverseModulus1_Revolutions =
          cart_trial_simple_DW.InverseModulus1_Revolutions + 1;
        dy = du + cart_trial_simple_P.InverseModulus1_Modulus;
      } else {
        dy = du;
      }

      rtb_InverseModulus1 = cart_trial_simple_B.mmcn2 +
        cart_trial_simple_DW.InverseModulus1_Revolutions *
        cart_trial_simple_P.InverseModulus1_Modulus;
      cart_trial_simple_DW.InverseModulus1_PreviousInput =
        cart_trial_simple_B.mmcn2;
    }
  }

  /* FromWorkspace: '<Root>/From Workspace' */
  {
    real_T *pDataValues = (real_T *)
      cart_trial_simple_DW.FromWorkspace_PWORK.DataPtr;
    real_T *pTimeValues = (real_T *)
      cart_trial_simple_DW.FromWorkspace_PWORK.TimePtr;
    int_T currTimeIndex = cart_trial_simple_DW.FromWorkspace_IWORK.PrevIndex;
    real_T t = cart_trial_simple_M->Timing.t[0];

    /* Get index */
    if (t <= pTimeValues[0]) {
      currTimeIndex = 0;
    } else if (t >= pTimeValues[2000]) {
      currTimeIndex = 1999;
    } else {
      if (t < pTimeValues[currTimeIndex]) {
        while (t < pTimeValues[currTimeIndex]) {
          currTimeIndex--;
        }
      } else {
        while (t >= pTimeValues[currTimeIndex + 1]) {
          currTimeIndex++;
        }
      }
    }

    cart_trial_simple_DW.FromWorkspace_IWORK.PrevIndex = currTimeIndex;

    /* Post output */
    {
      real_T t1 = pTimeValues[currTimeIndex];
      real_T t2 = pTimeValues[currTimeIndex + 1];
      if (t1 == t2) {
        if (t < t1) {
          cart_trial_simple_B.MeasuredPositionmm = pDataValues[currTimeIndex];
        } else {
          cart_trial_simple_B.MeasuredPositionmm = pDataValues[currTimeIndex + 1];
        }
      } else {
        real_T f1 = (t2 - t) / (t2 - t1);
        real_T f2 = 1.0 - f1;
        real_T d1;
        real_T d2;
        int_T TimeIndex = currTimeIndex;
        d1 = pDataValues[TimeIndex];
        d2 = pDataValues[TimeIndex + 1];
        cart_trial_simple_B.MeasuredPositionmm = (real_T) rtInterpolate(d1, d2,
          f1, f2);
        pDataValues += 2001;
      }
    }
  }

  /* Sum: '<Root>/Sum1' */
  cart_trial_simple_B.Sum1 = cart_trial_simple_B.MeasuredPositionmm -
    cart_trial_simple_B.InverseModulus;

  /* Derivative: '<Root>/Derivative' incorporates:
   *  Clock: '<Root>/Clock'
   */
  rtb_Sum2_tmp = cart_trial_simple_M->Timing.t[0];
  if ((cart_trial_simple_DW.TimeStampA >= rtb_Sum2_tmp) &&
      (cart_trial_simple_DW.TimeStampB >= rtb_Sum2_tmp)) {
    rtb_Sum2 = 0.0;
  } else {
    rtb_Sum2 = cart_trial_simple_DW.TimeStampA;
    lastU = &cart_trial_simple_DW.LastUAtTimeA;
    if (cart_trial_simple_DW.TimeStampA < cart_trial_simple_DW.TimeStampB) {
      if (cart_trial_simple_DW.TimeStampB < rtb_Sum2_tmp) {
        rtb_Sum2 = cart_trial_simple_DW.TimeStampB;
        lastU = &cart_trial_simple_DW.LastUAtTimeB;
      }
    } else if (cart_trial_simple_DW.TimeStampA >= rtb_Sum2_tmp) {
      rtb_Sum2 = cart_trial_simple_DW.TimeStampB;
      lastU = &cart_trial_simple_DW.LastUAtTimeB;
    }

    rtb_Sum2 = (cart_trial_simple_B.Sum1 - *lastU) / (rtb_Sum2_tmp - rtb_Sum2);
  }

  /* End of Derivative: '<Root>/Derivative' */

  /* Sum: '<Root>/Sum2' incorporates:
   *  Gain: '<Root>/Kd'
   *  Gain: '<Root>/Ki'
   *  Gain: '<Root>/Kp'
   *  Integrator: '<Root>/Integrator'
   */
  rtb_Sum2 = (cart_trial_simple_P.Kp_Gain * cart_trial_simple_B.Sum1 +
              cart_trial_simple_P.Kd_Gain * rtb_Sum2) +
    cart_trial_simple_P.Ki_Gain * cart_trial_simple_X.Integrator_CSTATE;

  /* Saturate: '<Root>/Voltage Safety' */
  if (rtb_Sum2 > cart_trial_simple_P.VoltageSafety_UpperSat) {
    /* Saturate: '<Root>/Voltage Safety' */
    cart_trial_simple_B.MeasuredPositionmm_n =
      cart_trial_simple_P.VoltageSafety_UpperSat;
  } else if (rtb_Sum2 < cart_trial_simple_P.VoltageSafety_LowerSat) {
    /* Saturate: '<Root>/Voltage Safety' */
    cart_trial_simple_B.MeasuredPositionmm_n =
      cart_trial_simple_P.VoltageSafety_LowerSat;
  } else {
    /* Saturate: '<Root>/Voltage Safety' */
    cart_trial_simple_B.MeasuredPositionmm_n = rtb_Sum2;
  }

  /* End of Saturate: '<Root>/Voltage Safety' */

  /* Gain: '<S1>/Cable Gain' */
  cart_trial_simple_B.CableGain = cart_trial_simple_P.CableGain_Gain *
    cart_trial_simple_B.MeasuredPositionmm_n;
  if (rtmIsMajorTimeStep(cart_trial_simple_M)) {
    /* S-Function (hil_write_analog_block): '<S1>/HIL Write Analog' */

    /* S-Function Block: cart_trial_simple/Quarc_Plant2/HIL Write Analog (hil_write_analog_block) */
    {
      t_error result;
      result = hil_write_analog(cart_trial_simple_DW.HILInitialize_Card,
        &cart_trial_simple_P.HILWriteAnalog_channels, 1,
        &cart_trial_simple_B.CableGain);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(cart_trial_simple_M, _rt_error_message);
      }
    }
  }

  /* Clock: '<Root>/Clock' */
  cart_trial_simple_B.Clock = rtb_Sum2_tmp;
  if (rtmIsMajorTimeStep(cart_trial_simple_M)) {
  }
}

/* Model update function */
void cart_trial_simple_update(void)
{
  real_T *lastU;

  /* Update for Derivative: '<Root>/Derivative' */
  if (cart_trial_simple_DW.TimeStampA == (rtInf)) {
    cart_trial_simple_DW.TimeStampA = cart_trial_simple_M->Timing.t[0];
    lastU = &cart_trial_simple_DW.LastUAtTimeA;
  } else if (cart_trial_simple_DW.TimeStampB == (rtInf)) {
    cart_trial_simple_DW.TimeStampB = cart_trial_simple_M->Timing.t[0];
    lastU = &cart_trial_simple_DW.LastUAtTimeB;
  } else if (cart_trial_simple_DW.TimeStampA < cart_trial_simple_DW.TimeStampB)
  {
    cart_trial_simple_DW.TimeStampA = cart_trial_simple_M->Timing.t[0];
    lastU = &cart_trial_simple_DW.LastUAtTimeA;
  } else {
    cart_trial_simple_DW.TimeStampB = cart_trial_simple_M->Timing.t[0];
    lastU = &cart_trial_simple_DW.LastUAtTimeB;
  }

  *lastU = cart_trial_simple_B.Sum1;

  /* End of Update for Derivative: '<Root>/Derivative' */
  if (rtmIsMajorTimeStep(cart_trial_simple_M)) {
    rt_ertODEUpdateContinuousStates(&cart_trial_simple_M->solverInfo);
  }

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++cart_trial_simple_M->Timing.clockTick0)) {
    ++cart_trial_simple_M->Timing.clockTickH0;
  }

  cart_trial_simple_M->Timing.t[0] = rtsiGetSolverStopTime
    (&cart_trial_simple_M->solverInfo);

  {
    /* Update absolute timer for sample time: [0.001s, 0.0s] */
    /* The "clockTick1" counts the number of times the code of this task has
     * been executed. The absolute time is the multiplication of "clockTick1"
     * and "Timing.stepSize1". Size of "clockTick1" ensures timer will not
     * overflow during the application lifespan selected.
     * Timer of this task consists of two 32 bit unsigned integers.
     * The two integers represent the low bits Timing.clockTick1 and the high bits
     * Timing.clockTickH1. When the low bit overflows to 0, the high bits increment.
     */
    if (!(++cart_trial_simple_M->Timing.clockTick1)) {
      ++cart_trial_simple_M->Timing.clockTickH1;
    }

    cart_trial_simple_M->Timing.t[1] = cart_trial_simple_M->Timing.clockTick1 *
      cart_trial_simple_M->Timing.stepSize1 +
      cart_trial_simple_M->Timing.clockTickH1 *
      cart_trial_simple_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Derivatives for root system: '<Root>' */
void cart_trial_simple_derivatives(void)
{
  XDot_cart_trial_simple_T *_rtXdot;
  _rtXdot = ((XDot_cart_trial_simple_T *) cart_trial_simple_M->derivs);

  /* Derivatives for Integrator: '<Root>/Integrator' */
  _rtXdot->Integrator_CSTATE = cart_trial_simple_B.Sum1;
}

/* Model initialize function */
void cart_trial_simple_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<S1>/HIL Initialize' */

  /* S-Function Block: cart_trial_simple/Quarc_Plant2/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q2_usb", "0", &cart_trial_simple_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(cart_trial_simple_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options
      (cart_trial_simple_DW.HILInitialize_Card,
       "d0=digital;d1=digital;led=auto;update_rate=normal;decimation=1", 63);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(cart_trial_simple_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(cart_trial_simple_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(cart_trial_simple_M, _rt_error_message);
      return;
    }

    if ((cart_trial_simple_P.HILInitialize_AIPStart && !is_switching) ||
        (cart_trial_simple_P.HILInitialize_AIPEnter && is_switching)) {
      cart_trial_simple_DW.HILInitialize_AIMinimums[0] =
        (cart_trial_simple_P.HILInitialize_AILow);
      cart_trial_simple_DW.HILInitialize_AIMinimums[1] =
        (cart_trial_simple_P.HILInitialize_AILow);
      cart_trial_simple_DW.HILInitialize_AIMaximums[0] =
        cart_trial_simple_P.HILInitialize_AIHigh;
      cart_trial_simple_DW.HILInitialize_AIMaximums[1] =
        cart_trial_simple_P.HILInitialize_AIHigh;
      result = hil_set_analog_input_ranges
        (cart_trial_simple_DW.HILInitialize_Card,
         cart_trial_simple_P.HILInitialize_AIChannels, 2U,
         &cart_trial_simple_DW.HILInitialize_AIMinimums[0],
         &cart_trial_simple_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(cart_trial_simple_M, _rt_error_message);
        return;
      }
    }

    if ((cart_trial_simple_P.HILInitialize_AOPStart && !is_switching) ||
        (cart_trial_simple_P.HILInitialize_AOPEnter && is_switching)) {
      cart_trial_simple_DW.HILInitialize_AOMinimums[0] =
        (cart_trial_simple_P.HILInitialize_AOLow);
      cart_trial_simple_DW.HILInitialize_AOMinimums[1] =
        (cart_trial_simple_P.HILInitialize_AOLow);
      cart_trial_simple_DW.HILInitialize_AOMaximums[0] =
        cart_trial_simple_P.HILInitialize_AOHigh;
      cart_trial_simple_DW.HILInitialize_AOMaximums[1] =
        cart_trial_simple_P.HILInitialize_AOHigh;
      result = hil_set_analog_output_ranges
        (cart_trial_simple_DW.HILInitialize_Card,
         cart_trial_simple_P.HILInitialize_AOChannels, 2U,
         &cart_trial_simple_DW.HILInitialize_AOMinimums[0],
         &cart_trial_simple_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(cart_trial_simple_M, _rt_error_message);
        return;
      }
    }

    if ((cart_trial_simple_P.HILInitialize_AOStart && !is_switching) ||
        (cart_trial_simple_P.HILInitialize_AOEnter && is_switching)) {
      cart_trial_simple_DW.HILInitialize_AOVoltages[0] =
        cart_trial_simple_P.HILInitialize_AOInitial;
      cart_trial_simple_DW.HILInitialize_AOVoltages[1] =
        cart_trial_simple_P.HILInitialize_AOInitial;
      result = hil_write_analog(cart_trial_simple_DW.HILInitialize_Card,
        cart_trial_simple_P.HILInitialize_AOChannels, 2U,
        &cart_trial_simple_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(cart_trial_simple_M, _rt_error_message);
        return;
      }
    }

    if (cart_trial_simple_P.HILInitialize_AOReset) {
      cart_trial_simple_DW.HILInitialize_AOVoltages[0] =
        cart_trial_simple_P.HILInitialize_AOWatchdog;
      cart_trial_simple_DW.HILInitialize_AOVoltages[1] =
        cart_trial_simple_P.HILInitialize_AOWatchdog;
      result = hil_watchdog_set_analog_expiration_state
        (cart_trial_simple_DW.HILInitialize_Card,
         cart_trial_simple_P.HILInitialize_AOChannels, 2U,
         &cart_trial_simple_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(cart_trial_simple_M, _rt_error_message);
        return;
      }
    }

    if ((cart_trial_simple_P.HILInitialize_EIPStart && !is_switching) ||
        (cart_trial_simple_P.HILInitialize_EIPEnter && is_switching)) {
      cart_trial_simple_DW.HILInitialize_QuadratureModes[0] =
        cart_trial_simple_P.HILInitialize_EIQuadrature;
      cart_trial_simple_DW.HILInitialize_QuadratureModes[1] =
        cart_trial_simple_P.HILInitialize_EIQuadrature;
      result = hil_set_encoder_quadrature_mode
        (cart_trial_simple_DW.HILInitialize_Card,
         cart_trial_simple_P.HILInitialize_EIChannels, 2U,
         (t_encoder_quadrature_mode *)
         &cart_trial_simple_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(cart_trial_simple_M, _rt_error_message);
        return;
      }
    }

    if ((cart_trial_simple_P.HILInitialize_EIStart && !is_switching) ||
        (cart_trial_simple_P.HILInitialize_EIEnter && is_switching)) {
      cart_trial_simple_DW.HILInitialize_InitialEICounts[0] =
        cart_trial_simple_P.HILInitialize_EIInitial;
      cart_trial_simple_DW.HILInitialize_InitialEICounts[1] =
        cart_trial_simple_P.HILInitialize_EIInitial;
      result = hil_set_encoder_counts(cart_trial_simple_DW.HILInitialize_Card,
        cart_trial_simple_P.HILInitialize_EIChannels, 2U,
        &cart_trial_simple_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(cart_trial_simple_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (inverse_modulus_block): '<S1>/Inverse Modulus' */

  /* S-Function Block: cart_trial_simple/Quarc_Plant2/Inverse Modulus (inverse_modulus_block) */
  {
    cart_trial_simple_DW.InverseModulus_FirstSample = true;
    cart_trial_simple_DW.InverseModulus_Revolutions = 0;
  }

  /* Start for S-Function (inverse_modulus_block): '<S1>/Inverse Modulus1' */

  /* S-Function Block: cart_trial_simple/Quarc_Plant2/Inverse Modulus1 (inverse_modulus_block) */
  {
    cart_trial_simple_DW.InverseModulus1_FirstSample = true;
    cart_trial_simple_DW.InverseModulus1_Revolutions = 0;
  }

  /* Start for FromWorkspace: '<Root>/From Workspace' */
  {
    static real_T pTimeValues0[] = { 0.0, 0.001, 0.002, 0.003, 0.004, 0.005,
      0.006, 0.007, 0.008, 0.0090000000000000011, 0.01, 0.011, 0.012,
      0.013000000000000001, 0.014, 0.015, 0.016, 0.017, 0.018000000000000002,
      0.019, 0.02, 0.021, 0.022, 0.023, 0.024, 0.025, 0.026000000000000002,
      0.027, 0.028, 0.029, 0.03, 0.031, 0.032, 0.033, 0.034, 0.035,
      0.036000000000000004, 0.037, 0.038, 0.039, 0.04, 0.041, 0.042,
      0.043000000000000003, 0.044, 0.045, 0.046, 0.047, 0.048, 0.049, 0.05,
      0.051000000000000004, 0.052000000000000005, 0.053, 0.054, 0.055, 0.056,
      0.057, 0.058, 0.059000000000000004, 0.06, 0.061, 0.062, 0.063, 0.064,
      0.065, 0.066, 0.067, 0.068, 0.069, 0.07, 0.071000000000000008,
      0.072000000000000008, 0.073, 0.074, 0.075, 0.076, 0.077, 0.078, 0.079,
      0.08, 0.081, 0.082, 0.083, 0.084, 0.085, 0.086000000000000007,
      0.087000000000000008, 0.088, 0.089, 0.09, 0.091, 0.092, 0.093, 0.094,
      0.095, 0.096, 0.097, 0.098, 0.099, 0.1, 0.101, 0.10200000000000001,
      0.10300000000000001, 0.10400000000000001, 0.105, 0.106, 0.107, 0.108,
      0.109, 0.11, 0.111, 0.112, 0.113, 0.114, 0.115, 0.116, 0.117,
      0.11800000000000001, 0.11900000000000001, 0.12, 0.121, 0.122, 0.123, 0.124,
      0.125, 0.126, 0.127, 0.128, 0.129, 0.13, 0.131, 0.132, 0.133, 0.134, 0.135,
      0.136, 0.137, 0.138, 0.139, 0.14, 0.14100000000000001, 0.14200000000000002,
      0.14300000000000002, 0.14400000000000002, 0.145, 0.146, 0.147, 0.148,
      0.149, 0.15, 0.151, 0.152, 0.153, 0.154, 0.155, 0.156, 0.157, 0.158, 0.159,
      0.16, 0.161, 0.162, 0.163, 0.164, 0.165, 0.166, 0.167, 0.168, 0.169, 0.17,
      0.171, 0.17200000000000001, 0.17300000000000001, 0.17400000000000002,
      0.17500000000000002, 0.176, 0.177, 0.178, 0.179, 0.18, 0.181, 0.182, 0.183,
      0.184, 0.185, 0.186, 0.187, 0.188, 0.189, 0.19, 0.191, 0.192, 0.193, 0.194,
      0.195, 0.196, 0.197, 0.198, 0.199, 0.2, 0.201, 0.202, 0.203,
      0.20400000000000001, 0.20500000000000002, 0.20600000000000002,
      0.20700000000000002, 0.20800000000000002, 0.209, 0.21, 0.211, 0.212, 0.213,
      0.214, 0.215, 0.216, 0.217, 0.218, 0.219, 0.22, 0.221, 0.222, 0.223, 0.224,
      0.225, 0.226, 0.227, 0.228, 0.229, 0.23, 0.231, 0.232, 0.233, 0.234,
      0.23500000000000001, 0.23600000000000002, 0.23700000000000002,
      0.23800000000000002, 0.23900000000000002, 0.24, 0.241, 0.242, 0.243, 0.244,
      0.245, 0.246, 0.247, 0.248, 0.249, 0.25, 0.251, 0.252, 0.253, 0.254, 0.255,
      0.256, 0.257, 0.258, 0.259, 0.26, 0.261, 0.262, 0.263, 0.264, 0.265, 0.266,
      0.267, 0.268, 0.269, 0.27, 0.271, 0.272, 0.273, 0.274, 0.275, 0.276, 0.277,
      0.278, 0.279, 0.28, 0.281, 0.28200000000000003, 0.28300000000000003,
      0.28400000000000003, 0.28500000000000003, 0.28600000000000003,
      0.28700000000000003, 0.28800000000000003, 0.289, 0.29, 0.291, 0.292, 0.293,
      0.294, 0.295, 0.296, 0.297, 0.298, 0.299, 0.3, 0.301, 0.302, 0.303, 0.304,
      0.305, 0.306, 0.307, 0.308, 0.309, 0.31, 0.311, 0.312, 0.313, 0.314, 0.315,
      0.316, 0.317, 0.318, 0.319, 0.32, 0.321, 0.322, 0.323, 0.324, 0.325, 0.326,
      0.327, 0.328, 0.329, 0.33, 0.331, 0.332, 0.333, 0.334, 0.335, 0.336, 0.337,
      0.338, 0.339, 0.34, 0.341, 0.342, 0.343, 0.34400000000000003,
      0.34500000000000003, 0.34600000000000003, 0.34700000000000003,
      0.34800000000000003, 0.34900000000000003, 0.35000000000000003,
      0.35100000000000003, 0.352, 0.353, 0.354, 0.355, 0.356, 0.357, 0.358,
      0.359, 0.36, 0.361, 0.362, 0.363, 0.364, 0.365, 0.366, 0.367, 0.368, 0.369,
      0.37, 0.371, 0.372, 0.373, 0.374, 0.375, 0.376, 0.377, 0.378, 0.379, 0.38,
      0.381, 0.382, 0.383, 0.384, 0.385, 0.386, 0.387, 0.388, 0.389, 0.39, 0.391,
      0.392, 0.393, 0.394, 0.395, 0.396, 0.397, 0.398, 0.399, 0.4, 0.401, 0.402,
      0.403, 0.404, 0.405, 0.406, 0.40700000000000003, 0.40800000000000003,
      0.40900000000000003, 0.41000000000000003, 0.41100000000000003,
      0.41200000000000003, 0.41300000000000003, 0.41400000000000003,
      0.41500000000000004, 0.41600000000000004, 0.417, 0.418, 0.419, 0.42, 0.421,
      0.422, 0.423, 0.424, 0.425, 0.426, 0.427, 0.428, 0.429, 0.43, 0.431, 0.432,
      0.433, 0.434, 0.435, 0.436, 0.437, 0.438, 0.439, 0.44, 0.441, 0.442, 0.443,
      0.444, 0.445, 0.446, 0.447, 0.448, 0.449, 0.45, 0.451, 0.452, 0.453, 0.454,
      0.455, 0.456, 0.457, 0.458, 0.459, 0.46, 0.461, 0.462, 0.463, 0.464, 0.465,
      0.466, 0.467, 0.468, 0.46900000000000003, 0.47000000000000003,
      0.47100000000000003, 0.47200000000000003, 0.47300000000000003,
      0.47400000000000003, 0.47500000000000003, 0.47600000000000003,
      0.47700000000000004, 0.47800000000000004, 0.47900000000000004, 0.48, 0.481,
      0.482, 0.483, 0.484, 0.485, 0.486, 0.487, 0.488, 0.489, 0.49, 0.491, 0.492,
      0.493, 0.494, 0.495, 0.496, 0.497, 0.498, 0.499, 0.5, 0.501, 0.502, 0.503,
      0.504, 0.505, 0.506, 0.507, 0.508, 0.509, 0.51, 0.511, 0.512, 0.513, 0.514,
      0.515, 0.516, 0.517, 0.518, 0.519, 0.52, 0.521, 0.522, 0.523, 0.524, 0.525,
      0.526, 0.527, 0.528, 0.529, 0.53, 0.531, 0.532, 0.533, 0.534, 0.535, 0.536,
      0.537, 0.538, 0.539, 0.54, 0.541, 0.542, 0.543, 0.544, 0.545, 0.546, 0.547,
      0.548, 0.549, 0.55, 0.551, 0.552, 0.553, 0.554, 0.555, 0.556, 0.557, 0.558,
      0.559, 0.56, 0.561, 0.562, 0.56300000000000006, 0.56400000000000006,
      0.56500000000000006, 0.56600000000000006, 0.56700000000000006,
      0.56800000000000006, 0.56900000000000006, 0.57000000000000006,
      0.57100000000000006, 0.57200000000000006, 0.57300000000000006,
      0.57400000000000007, 0.57500000000000007, 0.57600000000000007, 0.577,
      0.578, 0.579, 0.58, 0.581, 0.582, 0.583, 0.584, 0.585, 0.586, 0.587, 0.588,
      0.589, 0.59, 0.591, 0.592, 0.593, 0.594, 0.595, 0.596, 0.597, 0.598, 0.599,
      0.6, 0.601, 0.602, 0.603, 0.604, 0.605, 0.606, 0.607, 0.608, 0.609, 0.61,
      0.611, 0.612, 0.613, 0.614, 0.615, 0.616, 0.617, 0.618, 0.619, 0.62, 0.621,
      0.622, 0.623, 0.624, 0.625, 0.626, 0.627, 0.628, 0.629, 0.63, 0.631, 0.632,
      0.633, 0.634, 0.635, 0.636, 0.637, 0.638, 0.639, 0.64, 0.641, 0.642, 0.643,
      0.644, 0.645, 0.646, 0.647, 0.648, 0.649, 0.65, 0.651, 0.652, 0.653, 0.654,
      0.655, 0.656, 0.657, 0.658, 0.659, 0.66, 0.661, 0.662, 0.663, 0.664, 0.665,
      0.666, 0.667, 0.668, 0.669, 0.67, 0.671, 0.672, 0.673, 0.674, 0.675, 0.676,
      0.677, 0.678, 0.679, 0.68, 0.681, 0.682, 0.683, 0.684, 0.685, 0.686, 0.687,
      0.68800000000000006, 0.68900000000000006, 0.69000000000000006,
      0.69100000000000006, 0.69200000000000006, 0.69300000000000006,
      0.69400000000000006, 0.69500000000000006, 0.69600000000000006,
      0.69700000000000006, 0.69800000000000006, 0.69900000000000007,
      0.70000000000000007, 0.70100000000000007, 0.70200000000000007,
      0.70300000000000007, 0.704, 0.705, 0.706, 0.707, 0.708, 0.709, 0.71, 0.711,
      0.712, 0.713, 0.714, 0.715, 0.716, 0.717, 0.718, 0.719, 0.72, 0.721, 0.722,
      0.723, 0.724, 0.725, 0.726, 0.727, 0.728, 0.729, 0.73, 0.731, 0.732, 0.733,
      0.734, 0.735, 0.736, 0.737, 0.738, 0.739, 0.74, 0.741, 0.742, 0.743, 0.744,
      0.745, 0.746, 0.747, 0.748, 0.749, 0.75, 0.751, 0.752, 0.753, 0.754, 0.755,
      0.756, 0.757, 0.758, 0.759, 0.76, 0.761, 0.762, 0.763, 0.764, 0.765, 0.766,
      0.767, 0.768, 0.769, 0.77, 0.771, 0.772, 0.773, 0.774, 0.775, 0.776, 0.777,
      0.778, 0.779, 0.78, 0.781, 0.782, 0.783, 0.784, 0.785, 0.786, 0.787, 0.788,
      0.789, 0.79, 0.791, 0.792, 0.793, 0.794, 0.795, 0.796, 0.797, 0.798, 0.799,
      0.8, 0.801, 0.802, 0.803, 0.804, 0.805, 0.806, 0.807, 0.808, 0.809, 0.81,
      0.811, 0.812, 0.81300000000000006, 0.81400000000000006,
      0.81500000000000006, 0.81600000000000006, 0.81700000000000006,
      0.81800000000000006, 0.81900000000000006, 0.82000000000000006,
      0.82100000000000006, 0.82200000000000006, 0.82300000000000006,
      0.82400000000000007, 0.82500000000000007, 0.82600000000000007,
      0.82700000000000007, 0.82800000000000007, 0.82900000000000007,
      0.83000000000000007, 0.83100000000000007, 0.83200000000000007, 0.833,
      0.834, 0.835, 0.836, 0.837, 0.838, 0.839, 0.84, 0.841, 0.842, 0.843, 0.844,
      0.845, 0.846, 0.847, 0.848, 0.849, 0.85, 0.851, 0.852, 0.853, 0.854, 0.855,
      0.856, 0.857, 0.858, 0.859, 0.86, 0.861, 0.862, 0.863, 0.864, 0.865, 0.866,
      0.867, 0.868, 0.869, 0.87, 0.871, 0.872, 0.873, 0.874, 0.875, 0.876, 0.877,
      0.878, 0.879, 0.88, 0.881, 0.882, 0.883, 0.884, 0.885, 0.886, 0.887, 0.888,
      0.889, 0.89, 0.891, 0.892, 0.893, 0.894, 0.895, 0.896, 0.897, 0.898, 0.899,
      0.9, 0.901, 0.902, 0.903, 0.904, 0.905, 0.906, 0.907, 0.908, 0.909, 0.91,
      0.911, 0.912, 0.913, 0.914, 0.915, 0.916, 0.917, 0.918, 0.919, 0.92, 0.921,
      0.922, 0.923, 0.924, 0.925, 0.926, 0.927, 0.928, 0.929, 0.93, 0.931, 0.932,
      0.933, 0.934, 0.935, 0.936, 0.937, 0.93800000000000006,
      0.93900000000000006, 0.94000000000000006, 0.94100000000000006,
      0.94200000000000006, 0.94300000000000006, 0.94400000000000006,
      0.94500000000000006, 0.94600000000000006, 0.94700000000000006,
      0.94800000000000006, 0.94900000000000007, 0.95000000000000007,
      0.95100000000000007, 0.95200000000000007, 0.95300000000000007,
      0.95400000000000007, 0.95500000000000007, 0.95600000000000007,
      0.95700000000000007, 0.95800000000000007, 0.95900000000000007, 0.96, 0.961,
      0.962, 0.963, 0.964, 0.965, 0.966, 0.967, 0.968, 0.969, 0.97, 0.971, 0.972,
      0.973, 0.974, 0.975, 0.976, 0.977, 0.978, 0.979, 0.98, 0.981, 0.982, 0.983,
      0.984, 0.985, 0.986, 0.987, 0.988, 0.989, 0.99, 0.991, 0.992, 0.993, 0.994,
      0.995, 0.996, 0.997, 0.998, 0.999, 1.0, 1.0010000000000001, 1.002,
      1.0030000000000001, 1.004, 1.0050000000000001, 1.006, 1.0070000000000001,
      1.008, 1.0090000000000001, 1.01, 1.0110000000000001, 1.012,
      1.0130000000000001, 1.014, 1.0150000000000001, 1.016, 1.0170000000000001,
      1.018, 1.0190000000000001, 1.02, 1.0210000000000001, 1.022,
      1.0230000000000001, 1.024, 1.025, 1.026, 1.027, 1.028, 1.029, 1.03, 1.031,
      1.032, 1.033, 1.034, 1.035, 1.036, 1.037, 1.038, 1.039, 1.04, 1.041, 1.042,
      1.043, 1.044, 1.045, 1.046, 1.047, 1.048, 1.049, 1.05, 1.051, 1.052, 1.053,
      1.054, 1.055, 1.056, 1.057, 1.058, 1.059, 1.06, 1.061, 1.062, 1.063, 1.064,
      1.065, 1.066, 1.067, 1.068, 1.069, 1.07, 1.071, 1.072, 1.073, 1.074, 1.075,
      1.076, 1.077, 1.078, 1.079, 1.08, 1.081, 1.082, 1.083, 1.084, 1.085, 1.086,
      1.087, 1.088, 1.089, 1.09, 1.091, 1.092, 1.093, 1.094, 1.095, 1.096, 1.097,
      1.098, 1.099, 1.1, 1.101, 1.102, 1.103, 1.104, 1.105, 1.106, 1.107, 1.108,
      1.109, 1.11, 1.111, 1.112, 1.113, 1.114, 1.115, 1.116, 1.117, 1.118, 1.119,
      1.12, 1.121, 1.122, 1.123, 1.124, 1.125, 1.1260000000000001, 1.127,
      1.1280000000000001, 1.129, 1.1300000000000001, 1.131, 1.1320000000000001,
      1.133, 1.1340000000000001, 1.135, 1.1360000000000001, 1.137,
      1.1380000000000001, 1.139, 1.1400000000000001, 1.141, 1.1420000000000001,
      1.143, 1.1440000000000001, 1.145, 1.1460000000000001, 1.147,
      1.1480000000000001, 1.149, 1.1500000000000001, 1.151, 1.1520000000000001,
      1.153, 1.154, 1.155, 1.156, 1.157, 1.158, 1.159, 1.16, 1.161, 1.162, 1.163,
      1.164, 1.165, 1.166, 1.167, 1.168, 1.169, 1.17, 1.171, 1.172, 1.173, 1.174,
      1.175, 1.176, 1.177, 1.178, 1.179, 1.18, 1.181, 1.182, 1.183, 1.184, 1.185,
      1.186, 1.187, 1.188, 1.189, 1.19, 1.191, 1.192, 1.193, 1.194, 1.195, 1.196,
      1.197, 1.198, 1.199, 1.2, 1.201, 1.202, 1.203, 1.204, 1.205, 1.206, 1.207,
      1.208, 1.209, 1.21, 1.211, 1.212, 1.213, 1.214, 1.215, 1.216, 1.217, 1.218,
      1.219, 1.22, 1.221, 1.222, 1.223, 1.224, 1.225, 1.226, 1.227, 1.228, 1.229,
      1.23, 1.231, 1.232, 1.233, 1.234, 1.235, 1.236, 1.237, 1.238, 1.239, 1.24,
      1.241, 1.242, 1.243, 1.244, 1.245, 1.246, 1.247, 1.248, 1.249, 1.25,
      1.2510000000000001, 1.252, 1.2530000000000001, 1.254, 1.2550000000000001,
      1.256, 1.2570000000000001, 1.258, 1.2590000000000001, 1.26,
      1.2610000000000001, 1.262, 1.2630000000000001, 1.264, 1.2650000000000001,
      1.266, 1.2670000000000001, 1.268, 1.2690000000000001, 1.27,
      1.2710000000000001, 1.272, 1.2730000000000001, 1.274, 1.2750000000000001,
      1.276, 1.2770000000000001, 1.278, 1.2790000000000001, 1.28, 1.281, 1.282,
      1.283, 1.284, 1.285, 1.286, 1.287, 1.288, 1.289, 1.29, 1.291, 1.292, 1.293,
      1.294, 1.295, 1.296, 1.297, 1.298, 1.299, 1.3, 1.301, 1.302, 1.303, 1.304,
      1.305, 1.306, 1.307, 1.308, 1.309, 1.31, 1.311, 1.312, 1.313, 1.314, 1.315,
      1.316, 1.317, 1.318, 1.319, 1.32, 1.321, 1.322, 1.323, 1.324, 1.325, 1.326,
      1.327, 1.328, 1.329, 1.33, 1.331, 1.332, 1.333, 1.334, 1.335, 1.336, 1.337,
      1.338, 1.339, 1.34, 1.341, 1.342, 1.343, 1.344, 1.345, 1.346, 1.347, 1.348,
      1.349, 1.35, 1.351, 1.352, 1.353, 1.354, 1.355, 1.356, 1.357, 1.358, 1.359,
      1.36, 1.361, 1.362, 1.363, 1.364, 1.365, 1.366, 1.367, 1.368, 1.369, 1.37,
      1.371, 1.372, 1.373, 1.374, 1.375, 1.3760000000000001, 1.377,
      1.3780000000000001, 1.379, 1.3800000000000001, 1.381, 1.3820000000000001,
      1.383, 1.3840000000000001, 1.385, 1.3860000000000001, 1.387,
      1.3880000000000001, 1.389, 1.3900000000000001, 1.391, 1.3920000000000001,
      1.393, 1.3940000000000001, 1.395, 1.3960000000000001, 1.397,
      1.3980000000000001, 1.399, 1.4000000000000001, 1.401, 1.4020000000000001,
      1.403, 1.4040000000000001, 1.405, 1.4060000000000001, 1.407, 1.408, 1.409,
      1.41, 1.411, 1.412, 1.413, 1.414, 1.415, 1.416, 1.417, 1.418, 1.419, 1.42,
      1.421, 1.422, 1.423, 1.424, 1.425, 1.426, 1.427, 1.428, 1.429, 1.43, 1.431,
      1.432, 1.433, 1.434, 1.435, 1.436, 1.437, 1.438, 1.439, 1.44, 1.441, 1.442,
      1.443, 1.444, 1.445, 1.446, 1.447, 1.448, 1.449, 1.45, 1.451, 1.452, 1.453,
      1.454, 1.455, 1.456, 1.457, 1.458, 1.459, 1.46, 1.461, 1.462, 1.463, 1.464,
      1.465, 1.466, 1.467, 1.468, 1.469, 1.47, 1.471, 1.472, 1.473, 1.474, 1.475,
      1.476, 1.477, 1.478, 1.479, 1.48, 1.481, 1.482, 1.483, 1.484, 1.485, 1.486,
      1.487, 1.488, 1.489, 1.49, 1.491, 1.492, 1.493, 1.494, 1.495, 1.496, 1.497,
      1.498, 1.499, 1.5, 1.5010000000000001, 1.502, 1.5030000000000001, 1.504,
      1.5050000000000001, 1.506, 1.5070000000000001, 1.508, 1.5090000000000001,
      1.51, 1.5110000000000001, 1.512, 1.5130000000000001, 1.514,
      1.5150000000000001, 1.516, 1.5170000000000001, 1.518, 1.5190000000000001,
      1.52, 1.5210000000000001, 1.522, 1.5230000000000001, 1.524,
      1.5250000000000001, 1.526, 1.5270000000000001, 1.528, 1.5290000000000001,
      1.53, 1.5310000000000001, 1.532, 1.5330000000000001, 1.534,
      1.5350000000000001, 1.536, 1.537, 1.538, 1.539, 1.54, 1.541, 1.542, 1.543,
      1.544, 1.545, 1.546, 1.547, 1.548, 1.549, 1.55, 1.551, 1.552, 1.553, 1.554,
      1.555, 1.556, 1.557, 1.558, 1.559, 1.56, 1.561, 1.562, 1.563, 1.564, 1.565,
      1.566, 1.567, 1.568, 1.569, 1.57, 1.571, 1.572, 1.573, 1.574, 1.575, 1.576,
      1.577, 1.578, 1.579, 1.58, 1.581, 1.582, 1.583, 1.584, 1.585, 1.586, 1.587,
      1.588, 1.589, 1.59, 1.591, 1.592, 1.593, 1.594, 1.595, 1.596, 1.597, 1.598,
      1.599, 1.6, 1.601, 1.602, 1.603, 1.604, 1.605, 1.606, 1.607, 1.608, 1.609,
      1.61, 1.611, 1.612, 1.613, 1.614, 1.615, 1.616, 1.617, 1.618, 1.619, 1.62,
      1.621, 1.622, 1.623, 1.624, 1.625, 1.6260000000000001, 1.627,
      1.6280000000000001, 1.629, 1.6300000000000001, 1.631, 1.6320000000000001,
      1.633, 1.6340000000000001, 1.635, 1.6360000000000001, 1.637,
      1.6380000000000001, 1.639, 1.6400000000000001, 1.641, 1.6420000000000001,
      1.643, 1.6440000000000001, 1.645, 1.6460000000000001, 1.647,
      1.6480000000000001, 1.649, 1.6500000000000001, 1.651, 1.6520000000000001,
      1.653, 1.6540000000000001, 1.655, 1.6560000000000001, 1.657,
      1.6580000000000001, 1.659, 1.6600000000000001, 1.661, 1.6620000000000001,
      1.663, 1.6640000000000001, 1.665, 1.666, 1.667, 1.668, 1.669, 1.67, 1.671,
      1.672, 1.673, 1.674, 1.675, 1.676, 1.677, 1.678, 1.679, 1.68, 1.681, 1.682,
      1.683, 1.684, 1.685, 1.686, 1.687, 1.688, 1.689, 1.69, 1.691, 1.692, 1.693,
      1.694, 1.695, 1.696, 1.697, 1.698, 1.699, 1.7, 1.701, 1.702, 1.703, 1.704,
      1.705, 1.706, 1.707, 1.708, 1.709, 1.71, 1.711, 1.712, 1.713, 1.714, 1.715,
      1.716, 1.717, 1.718, 1.719, 1.72, 1.721, 1.722, 1.723, 1.724, 1.725, 1.726,
      1.727, 1.728, 1.729, 1.73, 1.731, 1.732, 1.733, 1.734, 1.735, 1.736, 1.737,
      1.738, 1.739, 1.74, 1.741, 1.742, 1.743, 1.744, 1.745, 1.746, 1.747, 1.748,
      1.749, 1.75, 1.7510000000000001, 1.752, 1.7530000000000001, 1.754,
      1.7550000000000001, 1.756, 1.7570000000000001, 1.758, 1.7590000000000001,
      1.76, 1.7610000000000001, 1.762, 1.7630000000000001, 1.764,
      1.7650000000000001, 1.766, 1.7670000000000001, 1.768, 1.7690000000000001,
      1.77, 1.7710000000000001, 1.772, 1.7730000000000001, 1.774,
      1.7750000000000001, 1.776, 1.7770000000000001, 1.778, 1.7790000000000001,
      1.78, 1.7810000000000001, 1.782, 1.7830000000000001, 1.784,
      1.7850000000000001, 1.786, 1.7870000000000001, 1.788, 1.7890000000000001,
      1.79, 1.7910000000000001, 1.792, 1.793, 1.794, 1.795, 1.796, 1.797, 1.798,
      1.799, 1.8, 1.801, 1.802, 1.803, 1.804, 1.805, 1.806, 1.807, 1.808, 1.809,
      1.81, 1.811, 1.812, 1.813, 1.814, 1.815, 1.816, 1.817, 1.818, 1.819, 1.82,
      1.821, 1.822, 1.823, 1.824, 1.825, 1.826, 1.827, 1.828, 1.829, 1.83, 1.831,
      1.832, 1.833, 1.834, 1.835, 1.836, 1.837, 1.838, 1.839, 1.84, 1.841, 1.842,
      1.843, 1.844, 1.845, 1.846, 1.847, 1.848, 1.849, 1.85, 1.851, 1.852, 1.853,
      1.854, 1.855, 1.856, 1.857, 1.858, 1.859, 1.86, 1.861, 1.862, 1.863, 1.864,
      1.865, 1.866, 1.867, 1.868, 1.869, 1.87, 1.871, 1.872, 1.873, 1.874, 1.875,
      1.8760000000000001, 1.877, 1.8780000000000001, 1.879, 1.8800000000000001,
      1.881, 1.8820000000000001, 1.883, 1.8840000000000001, 1.885,
      1.8860000000000001, 1.887, 1.8880000000000001, 1.889, 1.8900000000000001,
      1.891, 1.8920000000000001, 1.893, 1.8940000000000001, 1.895,
      1.8960000000000001, 1.897, 1.8980000000000001, 1.899, 1.9000000000000001,
      1.901, 1.9020000000000001, 1.903, 1.9040000000000001, 1.905,
      1.9060000000000001, 1.907, 1.9080000000000001, 1.909, 1.9100000000000001,
      1.911, 1.9120000000000001, 1.913, 1.9140000000000001, 1.915,
      1.9160000000000001, 1.917, 1.9180000000000001, 1.919, 1.92, 1.921, 1.922,
      1.923, 1.924, 1.925, 1.926, 1.927, 1.928, 1.929, 1.93, 1.931, 1.932, 1.933,
      1.934, 1.935, 1.936, 1.937, 1.938, 1.939, 1.94, 1.941, 1.942, 1.943, 1.944,
      1.945, 1.946, 1.947, 1.948, 1.949, 1.95, 1.951, 1.952, 1.953, 1.954, 1.955,
      1.956, 1.957, 1.958, 1.959, 1.96, 1.961, 1.962, 1.963, 1.964, 1.965, 1.966,
      1.967, 1.968, 1.969, 1.97, 1.971, 1.972, 1.973, 1.974, 1.975, 1.976, 1.977,
      1.978, 1.979, 1.98, 1.981, 1.982, 1.983, 1.984, 1.985, 1.986, 1.987, 1.988,
      1.989, 1.99, 1.991, 1.992, 1.993, 1.994, 1.995, 1.996, 1.997, 1.998, 1.999,
      2.0 } ;

    static real_T pDataValues0[] = { 0.0, 0.00025, 0.001, 0.00225, 0.004,
      0.0062499999999999995, 0.009, 0.01225, 0.016, 0.02025,
      0.024999999999999998, 0.030249999999999992, 0.036, 0.04225, 0.049,
      0.056249999999999994, 0.064, 0.072250000000000009, 0.081, 0.09025,
      0.099999999999999992, 0.11025000000000001, 0.12099999999999997,
      0.13224999999999998, 0.144, 0.15625, 0.169, 0.18225, 0.196,
      0.21025000000000002, 0.22499999999999998, 0.24025, 0.256, 0.27225,
      0.28900000000000003, 0.30625, 0.324, 0.34224999999999994, 0.361,
      0.38024999999999992, 0.39999999999999997, 0.42025000000000007,
      0.44100000000000006, 0.46225000000000005, 0.48399999999999987, 0.50625,
      0.52899999999999991, 0.55225, 0.576, 0.60025000000000006, 0.625,
      0.65025000000000011, 0.676, 0.70224999999999993, 0.729, 0.75625, 0.784,
      0.81225, 0.84100000000000008, 0.87025, 0.89999999999999991,
      0.93024999999999991, 0.961, 0.99224999999999985, 1.024, 1.05625, 1.089,
      1.12225, 1.1560000000000001, 1.19025, 1.225, 1.26025, 1.296,
      1.3322499999999997, 1.3689999999999998, 1.40625, 1.444, 1.4822499999999998,
      1.5209999999999997, 1.56025, 1.5999999999999999, 1.64025,
      1.6810000000000003, 1.72225, 1.7640000000000002, 1.80625,
      1.8490000000000002, 1.8922500000000002, 1.9359999999999995, 1.98025, 2.025,
      2.0702499999999997, 2.1159999999999997, 2.1622500000000002, 2.209,
      2.2562499999999996, 2.304, 2.35225, 2.4010000000000002, 2.45025, 2.5,
      2.5502500000000006, 2.6010000000000004, 2.6522500000000004, 2.704,
      2.7562500000000005, 2.8090000000000006, 2.8622500000000004, 2.916,
      2.9702500000000009, 3.0250000000000008, 3.0802500000000008,
      3.136000000000001, 3.19225, 3.249, 3.30625, 3.3640000000000003,
      3.4222500000000005, 3.481, 3.5402500000000003, 3.600000000000001,
      3.6602500000000009, 3.721, 3.7822500000000003, 3.8440000000000012, 3.90625,
      3.9689999999999994, 4.0322499999999994, 4.096, 4.1602500000000004, 4.225,
      4.29025, 4.356, 4.42225, 4.489, 4.55625, 4.6240000000000006,
      4.6922500000000005, 4.761, 4.83025, 4.9, 4.9702500000000009, 5.041,
      5.11225, 5.184, 5.2562500000000005, 5.3290000000000015, 5.4022500000000013,
      5.4760000000000018, 5.5502500000000019, 5.6250000000000009,
      5.7002500000000005, 5.7760000000000016, 5.8522500000000015,
      5.929000000000002, 6.0062500000000014, 6.0840000000000023, 6.16225, 6.241,
      6.3202500000000006, 6.3999999999999995, 6.4802500000000007, 6.561,
      6.6422500000000007, 6.7240000000000011, 6.80625, 6.889, 6.97225,
      7.0560000000000009, 7.1402500000000009, 7.225, 7.3102500000000008,
      7.3960000000000008, 7.4822500000000014, 7.5690000000000008,
      7.6562500000000009, 7.7440000000000007, 7.832250000000001,
      7.9210000000000012, 8.010250000000001, 8.1000000000000014, 8.19025,
      8.2809999999999988, 8.37225, 8.4639999999999986, 8.5562499999999986,
      8.6490000000000009, 8.7422499999999985, 8.836, 8.93025, 9.0249999999999986,
      9.12025, 9.216, 9.31225, 9.409, 9.50625, 9.604000000000001, 9.70225, 9.801,
      9.9002500000000015, 10.0, 10.1, 10.2, 10.3, 10.4, 10.5, 10.6, 10.7, 10.8,
      10.9, 11.0, 11.1, 11.2, 11.3, 11.4, 11.5, 11.6, 11.7, 11.8, 11.9, 12.0,
      12.1, 12.2, 12.3, 12.4, 12.5, 12.6, 12.7, 12.8, 12.9, 13.0, 13.1, 13.2,
      13.3, 13.4, 13.5, 13.600000000000001, 13.7, 13.8, 13.9, 14.0,
      14.100000000000001, 14.2, 14.3, 14.399999999999999, 14.5, 14.6, 14.7, 14.8,
      14.9, 15.0, 15.100000000000001, 15.2, 15.3, 15.4, 15.5, 15.600000000000001,
      15.7, 15.8, 15.9, 16.0, 16.1, 16.2, 16.3, 16.4, 16.5, 16.6, 16.7, 16.8,
      16.9, 17.0, 17.1, 17.200000000000003, 17.3, 17.4, 17.5, 17.6, 17.7, 17.8,
      17.9, 18.0, 18.1, 18.200000000000003, 18.3, 18.4, 18.5, 18.6,
      18.700000000000003, 18.799999999999997, 18.9, 19.0, 19.1, 19.2, 19.3, 19.4,
      19.5, 19.6, 19.700000000000003, 19.8, 19.9, 20.0, 20.1, 20.200000000000003,
      20.3, 20.4, 20.5, 20.6, 20.7, 20.8, 20.9, 21.0, 21.1, 21.200000000000003,
      21.3, 21.4, 21.5, 21.6, 21.700000000000003, 21.8, 21.9, 22.0, 22.1, 22.2,
      22.3, 22.4, 22.5, 22.6, 22.7, 22.8, 22.9, 23.0, 23.1, 23.200000000000003,
      23.3, 23.4, 23.5, 23.6, 23.700000000000003, 23.8, 23.900000000000002, 24.0,
      24.1, 24.200000000000003, 24.3, 24.400000000000002, 24.5, 24.6, 24.7,
      24.799999999999997, 24.9, 25.0, 25.1, 25.2, 25.299999999999997, 25.4, 25.5,
      25.599999999999998, 25.699999999999996, 25.799999999999997, 25.9, 26.0,
      26.099999999999998, 26.2, 26.299999999999997, 26.4, 26.499999999999996,
      26.599999999999998, 26.7, 26.799999999999997, 26.9, 27.0,
      27.099999999999998, 27.2, 27.299999999999997, 27.4, 27.5,
      27.599999999999998, 27.7, 27.8, 27.9, 28.0, 28.099999999999998, 28.2, 28.3,
      28.4, 28.5, 28.6, 28.7, 28.8, 28.9, 29.0, 29.1, 29.2, 29.3,
      29.400000000000002, 29.5, 29.599999999999998, 29.7, 29.799999999999997,
      29.9, 30.0, 30.099999999999998, 30.2, 30.299999999999997, 30.4, 30.5,
      30.599999999999998, 30.7, 30.8, 30.9, 31.0, 31.099999999999998, 31.2,
      31.299999999999997, 31.4, 31.499999999999996, 31.599999999999998,
      31.699999999999996, 31.799999999999997, 31.9, 31.999999999999996,
      32.099999999999994, 32.199999999999996, 32.3, 32.4, 32.5,
      32.599999999999994, 32.7, 32.8, 32.9, 33.0, 33.099999999999994, 33.2, 33.3,
      33.4, 33.5, 33.599999999999994, 33.7, 33.8, 33.9, 34.0, 34.099999999999994,
      34.2, 34.3, 34.4, 34.5, 34.6, 34.7, 34.8, 34.9, 35.0, 35.1, 35.2, 35.3,
      35.4, 35.5, 35.6, 35.7, 35.8, 35.900000000000006, 36.0, 36.1, 36.2, 36.3,
      36.400000000000006, 36.5, 36.6, 36.7, 36.8, 36.900000000000006, 37.0,
      37.099999999999994, 37.199999999999996, 37.3, 37.399999999999991, 37.5,
      37.599999999999994, 37.699999999999996, 37.8, 37.9, 38.0,
      38.099999999999994, 38.199999999999996, 38.3, 38.4, 38.5,
      38.599999999999994, 38.7, 38.8, 38.9, 39.0, 39.099999999999994, 39.2, 39.3,
      39.4, 39.5, 39.599999999999994, 39.7, 39.8, 39.9, 40.0, 40.09975, 40.199,
      40.29775, 40.396, 40.49375, 40.591, 40.68775, 40.784, 40.87975, 40.975,
      41.06975, 41.164, 41.25775, 41.351, 41.44375, 41.536, 41.62775, 41.719,
      41.80975, 41.9, 41.98975, 42.079, 42.16775, 42.256, 42.34375, 42.431,
      42.51775, 42.604, 42.689750000000004, 42.775, 42.85975, 42.944, 43.02775,
      43.111, 43.19375, 43.276, 43.35775, 43.439, 43.51975, 43.6, 43.67975,
      43.759, 43.83775, 43.916, 43.99375, 44.071, 44.14775, 44.224000000000004,
      44.29975, 44.375, 44.44975, 44.524, 44.59775, 44.671, 44.74375, 44.816,
      44.88775, 44.959, 45.02975, 45.1, 45.16975, 45.239, 45.30775, 45.376,
      45.44375, 45.511, 45.57775, 45.644, 45.70975, 45.775, 45.83975, 45.904,
      45.96775, 46.031, 46.09375, 46.156, 46.21775, 46.278999999999996, 46.33975,
      46.4, 46.45975, 46.519, 46.57775, 46.636, 46.69375, 46.751000000000005,
      46.80775, 46.864, 46.91975, 46.975, 47.02975, 47.084, 47.13775, 47.191,
      47.24375, 47.296, 47.347750000000005, 47.399, 47.44975, 47.5, 47.54975,
      47.599000000000004, 47.64775, 47.696, 47.74375, 47.791, 47.83775, 47.884,
      47.92975, 47.975, 48.01975, 48.064, 48.10775, 48.150999999999996, 48.19375,
      48.236000000000004, 48.27775, 48.319, 48.35975, 48.4, 48.439750000000004,
      48.479, 48.51775, 48.556, 48.59375, 48.631, 48.66775, 48.704, 48.73975,
      48.775, 48.80975, 48.844, 48.87775, 48.911, 48.94375, 48.976, 49.00775,
      49.039, 49.06975, 49.1, 49.12975, 49.159, 49.18775, 49.216,
      49.243750000000006, 49.271, 49.29775, 49.324, 49.34975, 49.375, 49.39975,
      49.424, 49.44775, 49.471000000000004, 49.493750000000006,
      49.516000000000005, 49.53775, 49.559, 49.579750000000004, 49.6,
      49.619749999999996, 49.638999999999996, 49.65775, 49.676, 49.69375, 49.711,
      49.72775, 49.744, 49.75975, 49.775, 49.78975, 49.804, 49.817750000000004,
      49.831, 49.84375, 49.856, 49.86775, 49.879, 49.88975, 49.900000000000006,
      49.90975, 49.919, 49.92775, 49.936, 49.94375, 49.951, 49.957750000000004,
      49.964, 49.96975, 49.975, 49.97975, 49.984, 49.98775, 49.991, 49.99375,
      49.996, 49.997749999999996, 49.999, 49.99975, 50.0, 50.0, 50.0, 50.0, 50.0,
      50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0,
      50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0,
      50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0,
      50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0,
      50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0,
      50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0,
      50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0,
      50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0,
      50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0,
      50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0,
      50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0,
      50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0,
      50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0,
      50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0,
      50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0,
      50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0,
      50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0,
      50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0,
      50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0,
      50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0,
      50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0,
      50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0,
      50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0,
      50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0,
      50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 50.0, 49.99975, 49.999,
      49.997749999999996, 49.996, 49.99375, 49.991, 49.98775, 49.984, 49.97975,
      49.975, 49.96975, 49.964, 49.957750000000004, 49.951, 49.94375, 49.936,
      49.92775, 49.919, 49.90975, 49.900000000000006, 49.88975, 49.879, 49.86775,
      49.856, 49.84375, 49.831, 49.817750000000004, 49.804, 49.78975, 49.775,
      49.75975, 49.744, 49.72775, 49.711, 49.69375, 49.676, 49.65775,
      49.638999999999996, 49.619749999999996, 49.6, 49.579750000000004, 49.559,
      49.53775, 49.516000000000005, 49.493750000000006, 49.471000000000004,
      49.44775, 49.424, 49.39975, 49.375, 49.34975, 49.324, 49.29775, 49.271,
      49.243750000000006, 49.216, 49.18775, 49.159, 49.12975, 49.1, 49.06975,
      49.039, 49.00775, 48.976, 48.94375, 48.911, 48.87775, 48.844, 48.80975,
      48.775, 48.73975, 48.704, 48.66775, 48.631, 48.59375, 48.556, 48.51775,
      48.479, 48.439750000000004, 48.4, 48.35975, 48.319, 48.27775,
      48.236000000000004, 48.19375, 48.150999999999996, 48.10775, 48.064,
      48.01975, 47.975, 47.92975, 47.884, 47.83775, 47.791, 47.74375, 47.696,
      47.64775, 47.599000000000004, 47.54975, 47.5, 47.44975, 47.399,
      47.347750000000005, 47.296, 47.24375, 47.191, 47.13775, 47.084, 47.02975,
      46.975, 46.91975, 46.864, 46.80775, 46.751000000000005, 46.69375, 46.636,
      46.57775, 46.519, 46.45975, 46.4, 46.33975, 46.278999999999996, 46.21775,
      46.156, 46.09375, 46.031, 45.96775, 45.904, 45.83975, 45.775, 45.70975,
      45.644, 45.57775, 45.511, 45.44375, 45.376, 45.30775, 45.239, 45.16975,
      45.1, 45.02975, 44.959, 44.88775, 44.816, 44.74375, 44.671, 44.59775,
      44.524, 44.44975, 44.375, 44.29975, 44.224000000000004, 44.14775, 44.071,
      43.99375, 43.916, 43.83775, 43.759, 43.67975, 43.6, 43.51975, 43.439,
      43.35775, 43.276, 43.19375, 43.111, 43.02775, 42.944, 42.85975, 42.775,
      42.689750000000004, 42.604, 42.51775, 42.431, 42.34375, 42.256, 42.16775,
      42.079, 41.98975, 41.9, 41.80975, 41.719, 41.62775, 41.536, 41.44375,
      41.351, 41.25775, 41.164, 41.06975, 40.975, 40.87975, 40.784, 40.68775,
      40.591, 40.49375, 40.396, 40.29775, 40.199, 40.09975, 40.0, 39.9, 39.8,
      39.7, 39.599999999999994, 39.5, 39.4, 39.3, 39.2, 39.099999999999994, 39.0,
      38.9, 38.8, 38.7, 38.599999999999994, 38.5, 38.4, 38.3, 38.199999999999996,
      38.099999999999994, 38.0, 37.9, 37.8, 37.699999999999996,
      37.599999999999994, 37.5, 37.399999999999991, 37.3, 37.199999999999996,
      37.099999999999994, 37.0, 36.900000000000006, 36.8, 36.7, 36.6, 36.5,
      36.400000000000006, 36.3, 36.2, 36.1, 36.0, 35.900000000000006, 35.8, 35.7,
      35.6, 35.5, 35.4, 35.3, 35.2, 35.1, 35.0, 34.9, 34.8, 34.7, 34.6, 34.5,
      34.4, 34.3, 34.2, 34.099999999999994, 34.0, 33.9, 33.8, 33.7,
      33.599999999999994, 33.5, 33.4, 33.3, 33.2, 33.099999999999994, 33.0, 32.9,
      32.8, 32.7, 32.599999999999994, 32.5, 32.4, 32.3, 32.199999999999996,
      32.099999999999994, 31.999999999999996, 31.9, 31.799999999999997,
      31.699999999999996, 31.599999999999998, 31.499999999999996, 31.4,
      31.299999999999997, 31.2, 31.099999999999998, 31.0, 30.9, 30.8, 30.7,
      30.599999999999998, 30.5, 30.4, 30.299999999999997, 30.2,
      30.099999999999998, 30.0, 29.9, 29.799999999999997, 29.7,
      29.599999999999998, 29.5, 29.400000000000002, 29.3, 29.2, 29.1, 29.0, 28.9,
      28.8, 28.7, 28.6, 28.5, 28.4, 28.3, 28.2, 28.099999999999998, 28.0, 27.9,
      27.8, 27.7, 27.599999999999998, 27.5, 27.4, 27.299999999999997, 27.2,
      27.099999999999998, 27.0, 26.9, 26.799999999999997, 26.7,
      26.599999999999998, 26.499999999999996, 26.4, 26.299999999999997, 26.2,
      26.099999999999998, 26.0, 25.9, 25.799999999999997, 25.699999999999996,
      25.599999999999998, 25.5, 25.4, 25.299999999999997, 25.2, 25.1, 25.0, 24.9,
      24.799999999999997, 24.7, 24.6, 24.5, 24.400000000000002, 24.3,
      24.200000000000003, 24.1, 24.0, 23.900000000000002, 23.8,
      23.700000000000003, 23.6, 23.5, 23.4, 23.3, 23.200000000000003, 23.1, 23.0,
      22.9, 22.8, 22.7, 22.6, 22.5, 22.4, 22.3, 22.2, 22.1, 22.0, 21.9, 21.8,
      21.700000000000003, 21.6, 21.5, 21.4, 21.3, 21.200000000000003, 21.1, 21.0,
      20.9, 20.8, 20.7, 20.6, 20.5, 20.4, 20.3, 20.200000000000003, 20.1, 20.0,
      19.9, 19.8, 19.700000000000003, 19.6, 19.5, 19.4, 19.3, 19.2, 19.1, 19.0,
      18.9, 18.799999999999997, 18.700000000000003, 18.6, 18.5, 18.4, 18.3,
      18.200000000000003, 18.1, 18.0, 17.9, 17.8, 17.7, 17.6, 17.5, 17.4, 17.3,
      17.200000000000003, 17.1, 17.0, 16.9, 16.8, 16.7, 16.6, 16.5, 16.4, 16.3,
      16.2, 16.1, 16.0, 15.9, 15.8, 15.7, 15.600000000000001, 15.5, 15.4, 15.3,
      15.2, 15.100000000000001, 15.0, 14.9, 14.8, 14.7, 14.6, 14.5,
      14.399999999999999, 14.3, 14.2, 14.100000000000001, 14.0, 13.9, 13.8, 13.7,
      13.600000000000001, 13.5, 13.4, 13.3, 13.2, 13.1, 13.0, 12.9, 12.8, 12.7,
      12.6, 12.5, 12.4, 12.3, 12.2, 12.1, 12.0, 11.9, 11.8, 11.7, 11.6, 11.5,
      11.4, 11.3, 11.2, 11.1, 11.0, 10.9, 10.8, 10.7, 10.6, 10.5, 10.4, 10.3,
      10.2, 10.1, 10.0, 9.9002500000000015, 9.801, 9.70225, 9.604000000000001,
      9.50625, 9.409, 9.31225, 9.216, 9.12025, 9.0249999999999986, 8.93025,
      8.836, 8.7422499999999985, 8.6490000000000009, 8.5562499999999986,
      8.4639999999999986, 8.37225, 8.2809999999999988, 8.19025,
      8.1000000000000014, 8.010250000000001, 7.9210000000000012,
      7.832250000000001, 7.7440000000000007, 7.6562500000000009,
      7.5690000000000008, 7.4822500000000014, 7.3960000000000008,
      7.3102500000000008, 7.225, 7.1402500000000009, 7.0560000000000009, 6.97225,
      6.889, 6.80625, 6.7240000000000011, 6.6422500000000007, 6.561,
      6.4802500000000007, 6.3999999999999995, 6.3202500000000006, 6.241, 6.16225,
      6.0840000000000023, 6.0062500000000014, 5.929000000000002,
      5.8522500000000015, 5.7760000000000016, 5.7002500000000005,
      5.6250000000000009, 5.5502500000000019, 5.4760000000000018,
      5.4022500000000013, 5.3290000000000015, 5.2562500000000005, 5.184, 5.11225,
      5.041, 4.9702500000000009, 4.9, 4.83025, 4.761, 4.6922500000000005,
      4.6240000000000006, 4.55625, 4.489, 4.42225, 4.356, 4.29025, 4.225,
      4.1602500000000004, 4.096, 4.0322499999999994, 3.9689999999999994, 3.90625,
      3.8440000000000012, 3.7822500000000003, 3.721, 3.6602500000000009,
      3.600000000000001, 3.5402500000000003, 3.481, 3.4222500000000005,
      3.3640000000000003, 3.30625, 3.249, 3.19225, 3.136000000000001,
      3.0802500000000008, 3.0250000000000008, 2.9702500000000009, 2.916,
      2.8622500000000004, 2.8090000000000006, 2.7562500000000005, 2.704,
      2.6522500000000004, 2.6010000000000004, 2.5502500000000006, 2.5, 2.45025,
      2.4010000000000002, 2.35225, 2.304, 2.2562499999999996, 2.209,
      2.1622500000000002, 2.1159999999999997, 2.0702499999999997, 2.025, 1.98025,
      1.9359999999999995, 1.8922500000000002, 1.8490000000000002, 1.80625,
      1.7640000000000002, 1.72225, 1.6810000000000003, 1.64025,
      1.5999999999999999, 1.56025, 1.5209999999999997, 1.4822499999999998, 1.444,
      1.40625, 1.3689999999999998, 1.3322499999999997, 1.296, 1.26025, 1.225,
      1.19025, 1.1560000000000001, 1.12225, 1.089, 1.05625, 1.024,
      0.99224999999999985, 0.961, 0.93024999999999991, 0.89999999999999991,
      0.87025, 0.84100000000000008, 0.81225, 0.784, 0.75625, 0.729,
      0.70224999999999993, 0.676, 0.65025000000000011, 0.625,
      0.60025000000000006, 0.576, 0.55225, 0.52899999999999991, 0.50625,
      0.48399999999999987, 0.46225000000000005, 0.44100000000000006,
      0.42025000000000007, 0.39999999999999997, 0.38024999999999992, 0.361,
      0.34224999999999994, 0.324, 0.30625, 0.28900000000000003, 0.27225, 0.256,
      0.24025, 0.22499999999999998, 0.21025000000000002, 0.196, 0.18225, 0.169,
      0.15625, 0.144, 0.13224999999999998, 0.12099999999999997,
      0.11025000000000001, 0.099999999999999992, 0.09025, 0.081,
      0.072250000000000009, 0.064, 0.056249999999999994, 0.049, 0.04225, 0.036,
      0.030249999999999992, 0.024999999999999998, 0.02025, 0.016, 0.01225, 0.009,
      0.0062499999999999995, 0.004, 0.00225, 0.001, 0.00025, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0,
      0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0, 0.0 } ;

    cart_trial_simple_DW.FromWorkspace_PWORK.TimePtr = (void *) pTimeValues0;
    cart_trial_simple_DW.FromWorkspace_PWORK.DataPtr = (void *) pDataValues0;
    cart_trial_simple_DW.FromWorkspace_IWORK.PrevIndex = 0;
  }

  /* InitializeConditions for Derivative: '<Root>/Derivative' */
  cart_trial_simple_DW.TimeStampA = (rtInf);
  cart_trial_simple_DW.TimeStampB = (rtInf);

  /* InitializeConditions for Integrator: '<Root>/Integrator' */
  cart_trial_simple_X.Integrator_CSTATE = cart_trial_simple_P.Integrator_IC;
}

/* Model terminate function */
void cart_trial_simple_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<S1>/HIL Initialize' */

  /* S-Function Block: cart_trial_simple/Quarc_Plant2/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    hil_task_stop_all(cart_trial_simple_DW.HILInitialize_Card);
    hil_monitor_stop_all(cart_trial_simple_DW.HILInitialize_Card);
    is_switching = false;
    if ((cart_trial_simple_P.HILInitialize_AOTerminate && !is_switching) ||
        (cart_trial_simple_P.HILInitialize_AOExit && is_switching)) {
      cart_trial_simple_DW.HILInitialize_AOVoltages[0] =
        cart_trial_simple_P.HILInitialize_AOFinal;
      cart_trial_simple_DW.HILInitialize_AOVoltages[1] =
        cart_trial_simple_P.HILInitialize_AOFinal;
      num_final_analog_outputs = 2U;
    } else {
      num_final_analog_outputs = 0;
    }

    if (num_final_analog_outputs > 0) {
      result = hil_write_analog(cart_trial_simple_DW.HILInitialize_Card,
        cart_trial_simple_P.HILInitialize_AOChannels, num_final_analog_outputs,
        &cart_trial_simple_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(cart_trial_simple_M, _rt_error_message);
      }
    }

    hil_task_delete_all(cart_trial_simple_DW.HILInitialize_Card);
    hil_monitor_delete_all(cart_trial_simple_DW.HILInitialize_Card);
    hil_close(cart_trial_simple_DW.HILInitialize_Card);
    cart_trial_simple_DW.HILInitialize_Card = NULL;
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/

/* Solver interface called by GRT_Main */
#ifndef USE_GENERATED_SOLVER

void rt_ODECreateIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEDestroyIntegrationData(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

void rt_ODEUpdateContinuousStates(RTWSolverInfo *si)
{
  UNUSED_PARAMETER(si);
  return;
}                                      /* do nothing */

#endif

void MdlOutputs(int_T tid)
{
  cart_trial_simple_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  cart_trial_simple_update();
  UNUSED_PARAMETER(tid);
}

void MdlInitializeSizes(void)
{
}

void MdlInitializeSampleTimes(void)
{
}

void MdlInitialize(void)
{
}

void MdlStart(void)
{
  cart_trial_simple_initialize();
}

void MdlTerminate(void)
{
  cart_trial_simple_terminate();
}

/* Registration function */
RT_MODEL_cart_trial_simple_T *cart_trial_simple(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)cart_trial_simple_M, 0,
                sizeof(RT_MODEL_cart_trial_simple_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&cart_trial_simple_M->solverInfo,
                          &cart_trial_simple_M->Timing.simTimeStep);
    rtsiSetTPtr(&cart_trial_simple_M->solverInfo, &rtmGetTPtr
                (cart_trial_simple_M));
    rtsiSetStepSizePtr(&cart_trial_simple_M->solverInfo,
                       &cart_trial_simple_M->Timing.stepSize0);
    rtsiSetdXPtr(&cart_trial_simple_M->solverInfo, &cart_trial_simple_M->derivs);
    rtsiSetContStatesPtr(&cart_trial_simple_M->solverInfo, (real_T **)
                         &cart_trial_simple_M->contStates);
    rtsiSetNumContStatesPtr(&cart_trial_simple_M->solverInfo,
      &cart_trial_simple_M->Sizes.numContStates);
    rtsiSetNumPeriodicContStatesPtr(&cart_trial_simple_M->solverInfo,
      &cart_trial_simple_M->Sizes.numPeriodicContStates);
    rtsiSetPeriodicContStateIndicesPtr(&cart_trial_simple_M->solverInfo,
      &cart_trial_simple_M->periodicContStateIndices);
    rtsiSetPeriodicContStateRangesPtr(&cart_trial_simple_M->solverInfo,
      &cart_trial_simple_M->periodicContStateRanges);
    rtsiSetErrorStatusPtr(&cart_trial_simple_M->solverInfo, (&rtmGetErrorStatus
      (cart_trial_simple_M)));
    rtsiSetRTModelPtr(&cart_trial_simple_M->solverInfo, cart_trial_simple_M);
  }

  rtsiSetSimTimeStep(&cart_trial_simple_M->solverInfo, MAJOR_TIME_STEP);
  cart_trial_simple_M->intgData.y = cart_trial_simple_M->odeY;
  cart_trial_simple_M->intgData.f[0] = cart_trial_simple_M->odeF[0];
  cart_trial_simple_M->intgData.f[1] = cart_trial_simple_M->odeF[1];
  cart_trial_simple_M->intgData.f[2] = cart_trial_simple_M->odeF[2];
  cart_trial_simple_M->contStates = ((real_T *) &cart_trial_simple_X);
  rtsiSetSolverData(&cart_trial_simple_M->solverInfo, (void *)
                    &cart_trial_simple_M->intgData);
  rtsiSetSolverName(&cart_trial_simple_M->solverInfo,"ode3");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = cart_trial_simple_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;

    /* polyspace +2 MISRA2012:D4.1 [Justified:Low] "cart_trial_simple_M points to
       static memory which is guaranteed to be non-NULL" */
    cart_trial_simple_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    cart_trial_simple_M->Timing.sampleTimes =
      (&cart_trial_simple_M->Timing.sampleTimesArray[0]);
    cart_trial_simple_M->Timing.offsetTimes =
      (&cart_trial_simple_M->Timing.offsetTimesArray[0]);

    /* task periods */
    cart_trial_simple_M->Timing.sampleTimes[0] = (0.0);
    cart_trial_simple_M->Timing.sampleTimes[1] = (0.001);

    /* task offsets */
    cart_trial_simple_M->Timing.offsetTimes[0] = (0.0);
    cart_trial_simple_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(cart_trial_simple_M, &cart_trial_simple_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = cart_trial_simple_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    cart_trial_simple_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(cart_trial_simple_M, 5.0);
  cart_trial_simple_M->Timing.stepSize0 = 0.001;
  cart_trial_simple_M->Timing.stepSize1 = 0.001;

  /* External mode info */
  cart_trial_simple_M->Sizes.checksums[0] = (1104401914U);
  cart_trial_simple_M->Sizes.checksums[1] = (1958855855U);
  cart_trial_simple_M->Sizes.checksums[2] = (1565509693U);
  cart_trial_simple_M->Sizes.checksums[3] = (524800929U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    cart_trial_simple_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(cart_trial_simple_M->extModeInfo,
      &cart_trial_simple_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(cart_trial_simple_M->extModeInfo,
                        cart_trial_simple_M->Sizes.checksums);
    rteiSetTPtr(cart_trial_simple_M->extModeInfo, rtmGetTPtr(cart_trial_simple_M));
  }

  cart_trial_simple_M->solverInfoPtr = (&cart_trial_simple_M->solverInfo);
  cart_trial_simple_M->Timing.stepSize = (0.001);
  rtsiSetFixedStepSize(&cart_trial_simple_M->solverInfo, 0.001);
  rtsiSetSolverMode(&cart_trial_simple_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  cart_trial_simple_M->blockIO = ((void *) &cart_trial_simple_B);
  (void) memset(((void *) &cart_trial_simple_B), 0,
                sizeof(B_cart_trial_simple_T));

  /* parameters */
  cart_trial_simple_M->defaultParam = ((real_T *)&cart_trial_simple_P);

  /* states (continuous) */
  {
    real_T *x = (real_T *) &cart_trial_simple_X;
    cart_trial_simple_M->contStates = (x);
    (void) memset((void *)&cart_trial_simple_X, 0,
                  sizeof(X_cart_trial_simple_T));
  }

  /* states (dwork) */
  cart_trial_simple_M->dwork = ((void *) &cart_trial_simple_DW);
  (void) memset((void *)&cart_trial_simple_DW, 0,
                sizeof(DW_cart_trial_simple_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    cart_trial_simple_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 19;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  cart_trial_simple_M->Sizes.numContStates = (1);/* Number of continuous states */
  cart_trial_simple_M->Sizes.numPeriodicContStates = (0);
                                      /* Number of periodic continuous states */
  cart_trial_simple_M->Sizes.numY = (0);/* Number of model outputs */
  cart_trial_simple_M->Sizes.numU = (0);/* Number of model inputs */
  cart_trial_simple_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  cart_trial_simple_M->Sizes.numSampTimes = (2);/* Number of sample times */
  cart_trial_simple_M->Sizes.numBlocks = (26);/* Number of blocks */
  cart_trial_simple_M->Sizes.numBlockIO = (8);/* Number of block outputs */
  cart_trial_simple_M->Sizes.numBlockPrms = (78);/* Sum of parameter "widths" */
  return cart_trial_simple_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
