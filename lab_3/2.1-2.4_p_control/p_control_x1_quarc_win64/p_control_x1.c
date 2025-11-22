/*
 * p_control_x1.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "p_control_x1".
 *
 * Model version              : 13.0
 * Simulink Coder version : 9.6 (R2021b) 14-May-2021
 * C source code generated on : Fri Nov 14 09:56:38 2025
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "p_control_x1.h"
#include "p_control_x1_private.h"
#include "p_control_x1_dt.h"

/* Block signals (default storage) */
B_p_control_x1_T p_control_x1_B;

/* Block states (default storage) */
DW_p_control_x1_T p_control_x1_DW;

/* Real-time model */
static RT_MODEL_p_control_x1_T p_control_x1_M_;
RT_MODEL_p_control_x1_T *const p_control_x1_M = &p_control_x1_M_;
real_T look1_binlxpw(real_T u0, const real_T bp0[], const real_T table[],
                     uint32_T maxIndex)
{
  real_T frac;
  real_T yL_0d0;
  uint32_T bpIdx;
  uint32_T iLeft;
  uint32_T iRght;

  /* Column-major Lookup 1-D
     Search method: 'binary'
     Use previous index: 'off'
     Interpolation method: 'Linear point-slope'
     Extrapolation method: 'Linear'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  /* Prelookup - Index and Fraction
     Index Search method: 'binary'
     Extrapolation method: 'Linear'
     Use previous index: 'off'
     Use last breakpoint for index at or above upper limit: 'off'
     Remove protection against out-of-range input in generated code: 'off'
   */
  if (u0 <= bp0[0U]) {
    iLeft = 0U;
    frac = (u0 - bp0[0U]) / (bp0[1U] - bp0[0U]);
  } else if (u0 < bp0[maxIndex]) {
    /* Binary Search */
    bpIdx = maxIndex >> 1U;
    iLeft = 0U;
    iRght = maxIndex;
    while (iRght - iLeft > 1U) {
      if (u0 < bp0[bpIdx]) {
        iRght = bpIdx;
      } else {
        iLeft = bpIdx;
      }

      bpIdx = (iRght + iLeft) >> 1U;
    }

    frac = (u0 - bp0[iLeft]) / (bp0[iLeft + 1U] - bp0[iLeft]);
  } else {
    iLeft = maxIndex - 1U;
    frac = (u0 - bp0[maxIndex - 1U]) / (bp0[maxIndex] - bp0[maxIndex - 1U]);
  }

  /* Column-major Interpolation 1-D
     Interpolation method: 'Linear point-slope'
     Use last breakpoint for index at or above upper limit: 'off'
     Overflow mode: 'portable wrapping'
   */
  yL_0d0 = table[iLeft];
  return (table[iLeft + 1U] - yL_0d0) * frac + yL_0d0;
}

real_T rt_remd_snf(real_T u0, real_T u1)
{
  real_T u1_0;
  real_T y;
  if (rtIsNaN(u0) || rtIsNaN(u1) || rtIsInf(u0)) {
    y = (rtNaN);
  } else if (rtIsInf(u1)) {
    y = u0;
  } else {
    if (u1 < 0.0) {
      u1_0 = ceil(u1);
    } else {
      u1_0 = floor(u1);
    }

    if ((u1 != 0.0) && (u1 != u1_0)) {
      u1_0 = fabs(u0 / u1);
      if (!(fabs(u1_0 - floor(u1_0 + 0.5)) > DBL_EPSILON * u1_0)) {
        y = 0.0 * u0;
      } else {
        y = fmod(u0, u1);
      }
    } else {
      y = fmod(u0, u1);
    }
  }

  return y;
}

/* Model output function */
void p_control_x1_output(void)
{
  /* local block i/o variables */
  real_T rtb_HILReadEncoderTimebase_o1;
  real_T rtb_HILReadEncoderTimebase_o2;
  real_T Output_tmp;
  real_T u0;

  /* S-Function (hil_read_encoder_timebase_block): '<S1>/HIL Read Encoder Timebase' */

  /* S-Function Block: p_control_x1/Plant/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_read_encoder(p_control_x1_DW.HILReadEncoderTimebase_Task,
      1, &p_control_x1_DW.HILReadEncoderTimebase_Buffer[0]);
    if (result < 0) {
      rtb_HILReadEncoderTimebase_o1 = 0;
      rtb_HILReadEncoderTimebase_o2 = 0;
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(p_control_x1_M, _rt_error_message);
    } else {
      rtb_HILReadEncoderTimebase_o1 =
        p_control_x1_DW.HILReadEncoderTimebase_Buffer[0];
      rtb_HILReadEncoderTimebase_o2 =
        p_control_x1_DW.HILReadEncoderTimebase_Buffer[1];
    }
  }

  /* Gain: '<S1>/mm//cn' */
  p_control_x1_B.mmcn = p_control_x1_P.mmcn_Gain * rtb_HILReadEncoderTimebase_o1;

  /* S-Function (inverse_modulus_block): '<S1>/Inverse Modulus' */
  /* S-Function Block: p_control_x1/Plant/Inverse Modulus (inverse_modulus_block) */
  {
    static const real_T sampling_period = 0.001;
    real_T half_range = p_control_x1_P.InverseModulus_Modulus / 2.0;
    real_T du, dy;
    if (p_control_x1_DW.InverseModulus_FirstSample) {
      p_control_x1_DW.InverseModulus_FirstSample = false;
      p_control_x1_DW.InverseModulus_PreviousInput = p_control_x1_B.mmcn;
    }

    du = (real_T) p_control_x1_B.mmcn -
      p_control_x1_DW.InverseModulus_PreviousInput;
    if (du > half_range) {
      p_control_x1_DW.InverseModulus_Revolutions =
        p_control_x1_DW.InverseModulus_Revolutions - 1;
      dy = du - p_control_x1_P.InverseModulus_Modulus;
    } else if (du < -half_range) {
      p_control_x1_DW.InverseModulus_Revolutions =
        p_control_x1_DW.InverseModulus_Revolutions + 1;
      dy = du + p_control_x1_P.InverseModulus_Modulus;
    } else {
      dy = du;
    }

    p_control_x1_B.InverseModulus = p_control_x1_B.mmcn +
      p_control_x1_DW.InverseModulus_Revolutions *
      p_control_x1_P.InverseModulus_Modulus;
    p_control_x1_DW.InverseModulus_PreviousInput = p_control_x1_B.mmcn;
  }

  /* Gain: '<S1>/mm//cn - 2' */
  p_control_x1_B.mmcn2 = p_control_x1_P.mmcn2_Gain *
    rtb_HILReadEncoderTimebase_o2;

  /* S-Function (inverse_modulus_block): '<S1>/Inverse Modulus1' */
  /* S-Function Block: p_control_x1/Plant/Inverse Modulus1 (inverse_modulus_block) */
  {
    static const real_T sampling_period = 0.001;
    real_T half_range = p_control_x1_P.InverseModulus1_Modulus / 2.0;
    real_T du, dy;
    if (p_control_x1_DW.InverseModulus1_FirstSample) {
      p_control_x1_DW.InverseModulus1_FirstSample = false;
      p_control_x1_DW.InverseModulus1_PreviousInput = p_control_x1_B.mmcn2;
    }

    du = (real_T) p_control_x1_B.mmcn2 -
      p_control_x1_DW.InverseModulus1_PreviousInput;
    if (du > half_range) {
      p_control_x1_DW.InverseModulus1_Revolutions =
        p_control_x1_DW.InverseModulus1_Revolutions - 1;
      dy = du - p_control_x1_P.InverseModulus1_Modulus;
    } else if (du < -half_range) {
      p_control_x1_DW.InverseModulus1_Revolutions =
        p_control_x1_DW.InverseModulus1_Revolutions + 1;
      dy = du + p_control_x1_P.InverseModulus1_Modulus;
    } else {
      dy = du;
    }

    p_control_x1_B.InverseModulus1 = p_control_x1_B.mmcn2 +
      p_control_x1_DW.InverseModulus1_Revolutions *
      p_control_x1_P.InverseModulus1_Modulus;
    p_control_x1_DW.InverseModulus1_PreviousInput = p_control_x1_B.mmcn2;
  }

  /* Clock: '<S2>/Clock' incorporates:
   *  Clock: '<Root>/Clock'
   *  Clock: '<Root>/Clock1'
   */
  Output_tmp = p_control_x1_M->Timing.t[0];

  /* SignalConversion: '<S2>/Output' incorporates:
   *  Clock: '<S2>/Clock'
   *  Constant: '<S2>/Constant'
   *  Lookup_n-D: '<S2>/Look-Up Table1'
   *  Math: '<S2>/Math Function'
   *  S-Function (sfun_tstart): '<S2>/startTime'
   *  Sum: '<S2>/Sum'
   */
  p_control_x1_B.Output = look1_binlxpw(rt_remd_snf(Output_tmp - (0.0),
    p_control_x1_P.Constant_Value), p_control_x1_P.LookUpTable1_bp01Data,
    p_control_x1_P.s, 2000U);

  /* Gain: '<Root>/Kp' incorporates:
   *  Sum: '<Root>/Sum'
   */
  u0 = (p_control_x1_B.Output - p_control_x1_B.InverseModulus) *
    p_control_x1_P.Kp_Gain;

  /* Saturate: '<Root>/Saturation' */
  if (u0 > p_control_x1_P.Saturation_UpperSat) {
    /* Saturate: '<Root>/Saturation' */
    p_control_x1_B.Saturation = p_control_x1_P.Saturation_UpperSat;
  } else if (u0 < p_control_x1_P.Saturation_LowerSat) {
    /* Saturate: '<Root>/Saturation' */
    p_control_x1_B.Saturation = p_control_x1_P.Saturation_LowerSat;
  } else {
    /* Saturate: '<Root>/Saturation' */
    p_control_x1_B.Saturation = u0;
  }

  /* End of Saturate: '<Root>/Saturation' */

  /* Gain: '<S1>/Cable Gain' */
  p_control_x1_B.CableGain = p_control_x1_P.CableGain_Gain *
    p_control_x1_B.Saturation;

  /* S-Function (hil_write_analog_block): '<S1>/HIL Write Analog' */

  /* S-Function Block: p_control_x1/Plant/HIL Write Analog (hil_write_analog_block) */
  {
    t_error result;
    result = hil_write_analog(p_control_x1_DW.HILInitialize_Card,
      &p_control_x1_P.HILWriteAnalog_channels, 1, &p_control_x1_B.CableGain);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(p_control_x1_M, _rt_error_message);
    }
  }

  /* Clock: '<Root>/Clock' */
  p_control_x1_B.Clock = Output_tmp;

  /* Clock: '<Root>/Clock1' */
  p_control_x1_B.Clock1 = Output_tmp;
}

/* Model update function */
void p_control_x1_update(void)
{
  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++p_control_x1_M->Timing.clockTick0)) {
    ++p_control_x1_M->Timing.clockTickH0;
  }

  p_control_x1_M->Timing.t[0] = p_control_x1_M->Timing.clockTick0 *
    p_control_x1_M->Timing.stepSize0 + p_control_x1_M->Timing.clockTickH0 *
    p_control_x1_M->Timing.stepSize0 * 4294967296.0;

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
    if (!(++p_control_x1_M->Timing.clockTick1)) {
      ++p_control_x1_M->Timing.clockTickH1;
    }

    p_control_x1_M->Timing.t[1] = p_control_x1_M->Timing.clockTick1 *
      p_control_x1_M->Timing.stepSize1 + p_control_x1_M->Timing.clockTickH1 *
      p_control_x1_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Model initialize function */
void p_control_x1_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<S1>/HIL Initialize' */

  /* S-Function Block: p_control_x1/Plant/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q2_usb", "0", &p_control_x1_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(p_control_x1_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(p_control_x1_DW.HILInitialize_Card,
      "d0=digital;d1=digital;led=auto;update_rate=normal;decimation=1", 63);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(p_control_x1_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(p_control_x1_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(p_control_x1_M, _rt_error_message);
      return;
    }

    if ((p_control_x1_P.HILInitialize_AIPStart && !is_switching) ||
        (p_control_x1_P.HILInitialize_AIPEnter && is_switching)) {
      p_control_x1_DW.HILInitialize_AIMinimums[0] =
        (p_control_x1_P.HILInitialize_AILow);
      p_control_x1_DW.HILInitialize_AIMinimums[1] =
        (p_control_x1_P.HILInitialize_AILow);
      p_control_x1_DW.HILInitialize_AIMaximums[0] =
        p_control_x1_P.HILInitialize_AIHigh;
      p_control_x1_DW.HILInitialize_AIMaximums[1] =
        p_control_x1_P.HILInitialize_AIHigh;
      result = hil_set_analog_input_ranges(p_control_x1_DW.HILInitialize_Card,
        p_control_x1_P.HILInitialize_AIChannels, 2U,
        &p_control_x1_DW.HILInitialize_AIMinimums[0],
        &p_control_x1_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(p_control_x1_M, _rt_error_message);
        return;
      }
    }

    if ((p_control_x1_P.HILInitialize_AOPStart && !is_switching) ||
        (p_control_x1_P.HILInitialize_AOPEnter && is_switching)) {
      p_control_x1_DW.HILInitialize_AOMinimums[0] =
        (p_control_x1_P.HILInitialize_AOLow);
      p_control_x1_DW.HILInitialize_AOMinimums[1] =
        (p_control_x1_P.HILInitialize_AOLow);
      p_control_x1_DW.HILInitialize_AOMaximums[0] =
        p_control_x1_P.HILInitialize_AOHigh;
      p_control_x1_DW.HILInitialize_AOMaximums[1] =
        p_control_x1_P.HILInitialize_AOHigh;
      result = hil_set_analog_output_ranges(p_control_x1_DW.HILInitialize_Card,
        p_control_x1_P.HILInitialize_AOChannels, 2U,
        &p_control_x1_DW.HILInitialize_AOMinimums[0],
        &p_control_x1_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(p_control_x1_M, _rt_error_message);
        return;
      }
    }

    if ((p_control_x1_P.HILInitialize_AOStart && !is_switching) ||
        (p_control_x1_P.HILInitialize_AOEnter && is_switching)) {
      p_control_x1_DW.HILInitialize_AOVoltages[0] =
        p_control_x1_P.HILInitialize_AOInitial;
      p_control_x1_DW.HILInitialize_AOVoltages[1] =
        p_control_x1_P.HILInitialize_AOInitial;
      result = hil_write_analog(p_control_x1_DW.HILInitialize_Card,
        p_control_x1_P.HILInitialize_AOChannels, 2U,
        &p_control_x1_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(p_control_x1_M, _rt_error_message);
        return;
      }
    }

    if (p_control_x1_P.HILInitialize_AOReset) {
      p_control_x1_DW.HILInitialize_AOVoltages[0] =
        p_control_x1_P.HILInitialize_AOWatchdog;
      p_control_x1_DW.HILInitialize_AOVoltages[1] =
        p_control_x1_P.HILInitialize_AOWatchdog;
      result = hil_watchdog_set_analog_expiration_state
        (p_control_x1_DW.HILInitialize_Card,
         p_control_x1_P.HILInitialize_AOChannels, 2U,
         &p_control_x1_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(p_control_x1_M, _rt_error_message);
        return;
      }
    }

    if ((p_control_x1_P.HILInitialize_EIPStart && !is_switching) ||
        (p_control_x1_P.HILInitialize_EIPEnter && is_switching)) {
      p_control_x1_DW.HILInitialize_QuadratureModes[0] =
        p_control_x1_P.HILInitialize_EIQuadrature;
      p_control_x1_DW.HILInitialize_QuadratureModes[1] =
        p_control_x1_P.HILInitialize_EIQuadrature;
      result = hil_set_encoder_quadrature_mode
        (p_control_x1_DW.HILInitialize_Card,
         p_control_x1_P.HILInitialize_EIChannels, 2U, (t_encoder_quadrature_mode
          *) &p_control_x1_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(p_control_x1_M, _rt_error_message);
        return;
      }
    }

    if ((p_control_x1_P.HILInitialize_EIStart && !is_switching) ||
        (p_control_x1_P.HILInitialize_EIEnter && is_switching)) {
      p_control_x1_DW.HILInitialize_InitialEICounts[0] =
        p_control_x1_P.HILInitialize_EIInitial;
      p_control_x1_DW.HILInitialize_InitialEICounts[1] =
        p_control_x1_P.HILInitialize_EIInitial;
      result = hil_set_encoder_counts(p_control_x1_DW.HILInitialize_Card,
        p_control_x1_P.HILInitialize_EIChannels, 2U,
        &p_control_x1_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(p_control_x1_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S1>/HIL Read Encoder Timebase' */

  /* S-Function Block: p_control_x1/Plant/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader(p_control_x1_DW.HILInitialize_Card,
      p_control_x1_P.HILReadEncoderTimebase_SamplesI,
      p_control_x1_P.HILReadEncoderTimebase_Channels, 2,
      &p_control_x1_DW.HILReadEncoderTimebase_Task);
    if (result >= 0) {
      result = hil_task_set_buffer_overflow_mode
        (p_control_x1_DW.HILReadEncoderTimebase_Task, (t_buffer_overflow_mode)
         (p_control_x1_P.HILReadEncoderTimebase_Overflow - 1));
    }

    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(p_control_x1_M, _rt_error_message);
    }
  }

  /* Start for S-Function (inverse_modulus_block): '<S1>/Inverse Modulus' */

  /* S-Function Block: p_control_x1/Plant/Inverse Modulus (inverse_modulus_block) */
  {
    p_control_x1_DW.InverseModulus_FirstSample = true;
    p_control_x1_DW.InverseModulus_Revolutions = 0;
  }

  /* Start for S-Function (inverse_modulus_block): '<S1>/Inverse Modulus1' */

  /* S-Function Block: p_control_x1/Plant/Inverse Modulus1 (inverse_modulus_block) */
  {
    p_control_x1_DW.InverseModulus1_FirstSample = true;
    p_control_x1_DW.InverseModulus1_Revolutions = 0;
  }
}

/* Model terminate function */
void p_control_x1_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<S1>/HIL Initialize' */

  /* S-Function Block: p_control_x1/Plant/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    hil_task_stop_all(p_control_x1_DW.HILInitialize_Card);
    hil_monitor_stop_all(p_control_x1_DW.HILInitialize_Card);
    is_switching = false;
    if ((p_control_x1_P.HILInitialize_AOTerminate && !is_switching) ||
        (p_control_x1_P.HILInitialize_AOExit && is_switching)) {
      p_control_x1_DW.HILInitialize_AOVoltages[0] =
        p_control_x1_P.HILInitialize_AOFinal;
      p_control_x1_DW.HILInitialize_AOVoltages[1] =
        p_control_x1_P.HILInitialize_AOFinal;
      num_final_analog_outputs = 2U;
    } else {
      num_final_analog_outputs = 0;
    }

    if (num_final_analog_outputs > 0) {
      result = hil_write_analog(p_control_x1_DW.HILInitialize_Card,
        p_control_x1_P.HILInitialize_AOChannels, num_final_analog_outputs,
        &p_control_x1_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(p_control_x1_M, _rt_error_message);
      }
    }

    hil_task_delete_all(p_control_x1_DW.HILInitialize_Card);
    hil_monitor_delete_all(p_control_x1_DW.HILInitialize_Card);
    hil_close(p_control_x1_DW.HILInitialize_Card);
    p_control_x1_DW.HILInitialize_Card = NULL;
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  p_control_x1_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  p_control_x1_update();
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
  p_control_x1_initialize();
}

void MdlTerminate(void)
{
  p_control_x1_terminate();
}

/* Registration function */
RT_MODEL_p_control_x1_T *p_control_x1(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)p_control_x1_M, 0,
                sizeof(RT_MODEL_p_control_x1_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&p_control_x1_M->solverInfo,
                          &p_control_x1_M->Timing.simTimeStep);
    rtsiSetTPtr(&p_control_x1_M->solverInfo, &rtmGetTPtr(p_control_x1_M));
    rtsiSetStepSizePtr(&p_control_x1_M->solverInfo,
                       &p_control_x1_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&p_control_x1_M->solverInfo, (&rtmGetErrorStatus
      (p_control_x1_M)));
    rtsiSetRTModelPtr(&p_control_x1_M->solverInfo, p_control_x1_M);
  }

  rtsiSetSimTimeStep(&p_control_x1_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&p_control_x1_M->solverInfo,"FixedStepDiscrete");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = p_control_x1_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;

    /* polyspace +2 MISRA2012:D4.1 [Justified:Low] "p_control_x1_M points to
       static memory which is guaranteed to be non-NULL" */
    p_control_x1_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    p_control_x1_M->Timing.sampleTimes =
      (&p_control_x1_M->Timing.sampleTimesArray[0]);
    p_control_x1_M->Timing.offsetTimes =
      (&p_control_x1_M->Timing.offsetTimesArray[0]);

    /* task periods */
    p_control_x1_M->Timing.sampleTimes[0] = (0.0);
    p_control_x1_M->Timing.sampleTimes[1] = (0.001);

    /* task offsets */
    p_control_x1_M->Timing.offsetTimes[0] = (0.0);
    p_control_x1_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(p_control_x1_M, &p_control_x1_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = p_control_x1_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    p_control_x1_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(p_control_x1_M, 4.0);
  p_control_x1_M->Timing.stepSize0 = 0.001;
  p_control_x1_M->Timing.stepSize1 = 0.001;

  /* External mode info */
  p_control_x1_M->Sizes.checksums[0] = (627868291U);
  p_control_x1_M->Sizes.checksums[1] = (1594098713U);
  p_control_x1_M->Sizes.checksums[2] = (496200345U);
  p_control_x1_M->Sizes.checksums[3] = (2938232106U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    p_control_x1_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(p_control_x1_M->extModeInfo,
      &p_control_x1_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(p_control_x1_M->extModeInfo,
                        p_control_x1_M->Sizes.checksums);
    rteiSetTPtr(p_control_x1_M->extModeInfo, rtmGetTPtr(p_control_x1_M));
  }

  p_control_x1_M->solverInfoPtr = (&p_control_x1_M->solverInfo);
  p_control_x1_M->Timing.stepSize = (0.001);
  rtsiSetFixedStepSize(&p_control_x1_M->solverInfo, 0.001);
  rtsiSetSolverMode(&p_control_x1_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  p_control_x1_M->blockIO = ((void *) &p_control_x1_B);
  (void) memset(((void *) &p_control_x1_B), 0,
                sizeof(B_p_control_x1_T));

  /* parameters */
  p_control_x1_M->defaultParam = ((real_T *)&p_control_x1_P);

  /* states (dwork) */
  p_control_x1_M->dwork = ((void *) &p_control_x1_DW);
  (void) memset((void *)&p_control_x1_DW, 0,
                sizeof(DW_p_control_x1_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    p_control_x1_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 20;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  p_control_x1_M->Sizes.numContStates = (0);/* Number of continuous states */
  p_control_x1_M->Sizes.numY = (0);    /* Number of model outputs */
  p_control_x1_M->Sizes.numU = (0);    /* Number of model inputs */
  p_control_x1_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  p_control_x1_M->Sizes.numSampTimes = (2);/* Number of sample times */
  p_control_x1_M->Sizes.numBlocks = (26);/* Number of blocks */
  p_control_x1_M->Sizes.numBlockIO = (9);/* Number of block outputs */
  p_control_x1_M->Sizes.numBlockPrms = (4080);/* Sum of parameter "widths" */
  return p_control_x1_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
