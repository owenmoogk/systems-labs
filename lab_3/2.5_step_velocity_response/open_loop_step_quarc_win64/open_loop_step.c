/*
 * open_loop_step.c
 *
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * Code generation for model "open_loop_step".
 *
 * Model version              : 13.2
 * Simulink Coder version : 9.6 (R2021b) 14-May-2021
 * C source code generated on : Mon Nov 10 10:50:31 2025
 *
 * Target selection: quarc_win64.tlc
 * Note: GRT includes extra infrastructure and instrumentation for prototyping
 * Embedded hardware selection: Intel->x86-64 (Windows64)
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#include "open_loop_step.h"
#include "open_loop_step_private.h"
#include "open_loop_step_dt.h"

/* Block signals (default storage) */
B_open_loop_step_T open_loop_step_B;

/* Block states (default storage) */
DW_open_loop_step_T open_loop_step_DW;

/* Real-time model */
static RT_MODEL_open_loop_step_T open_loop_step_M_;
RT_MODEL_open_loop_step_T *const open_loop_step_M = &open_loop_step_M_;

/* Model output function */
void open_loop_step_output(void)
{
  /* local block i/o variables */
  real_T rtb_InverseModulus;
  real_T rtb_InverseModulus1;
  real_T temp;

  /* S-Function (hil_read_encoder_timebase_block): '<S3>/HIL Read Encoder Timebase' */

  /* S-Function Block: open_loop_step/Plant/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_read_encoder(open_loop_step_DW.HILReadEncoderTimebase_Task,
      1, &open_loop_step_DW.HILReadEncoderTimebase_Buffer[0]);
    if (result < 0) {
      rtb_InverseModulus = 0;
      rtb_InverseModulus1 = 0;
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(open_loop_step_M, _rt_error_message);
    } else {
      rtb_InverseModulus = open_loop_step_DW.HILReadEncoderTimebase_Buffer[0];
      rtb_InverseModulus1 = open_loop_step_DW.HILReadEncoderTimebase_Buffer[1];
    }
  }

  /* Gain: '<S3>/mm//cn' */
  open_loop_step_B.mmcn = open_loop_step_P.mmcn_Gain * rtb_InverseModulus;

  /* S-Function (inverse_modulus_block): '<S3>/Inverse Modulus' */
  /* S-Function Block: open_loop_step/Plant/Inverse Modulus (inverse_modulus_block) */
  {
    static const real_T sampling_period = 0.001;
    real_T half_range = open_loop_step_P.InverseModulus_Modulus / 2.0;
    real_T du, dy;
    if (open_loop_step_DW.InverseModulus_FirstSample) {
      open_loop_step_DW.InverseModulus_FirstSample = false;
      open_loop_step_DW.InverseModulus_PreviousInput = open_loop_step_B.mmcn;
    }

    du = (real_T) open_loop_step_B.mmcn -
      open_loop_step_DW.InverseModulus_PreviousInput;
    if (du > half_range) {
      open_loop_step_DW.InverseModulus_Revolutions =
        open_loop_step_DW.InverseModulus_Revolutions - 1;
      dy = du - open_loop_step_P.InverseModulus_Modulus;
    } else if (du < -half_range) {
      open_loop_step_DW.InverseModulus_Revolutions =
        open_loop_step_DW.InverseModulus_Revolutions + 1;
      dy = du + open_loop_step_P.InverseModulus_Modulus;
    } else {
      dy = du;
    }

    rtb_InverseModulus = open_loop_step_B.mmcn +
      open_loop_step_DW.InverseModulus_Revolutions *
      open_loop_step_P.InverseModulus_Modulus;
    open_loop_step_DW.InverseModulus_PreviousInput = open_loop_step_B.mmcn;
  }

  /* Gain: '<S3>/mm//cn - 2' */
  open_loop_step_B.mmcn2 = open_loop_step_P.mmcn2_Gain * rtb_InverseModulus1;

  /* S-Function (inverse_modulus_block): '<S3>/Inverse Modulus1' */
  /* S-Function Block: open_loop_step/Plant/Inverse Modulus1 (inverse_modulus_block) */
  {
    static const real_T sampling_period = 0.001;
    real_T half_range = open_loop_step_P.InverseModulus1_Modulus / 2.0;
    real_T du, dy;
    if (open_loop_step_DW.InverseModulus1_FirstSample) {
      open_loop_step_DW.InverseModulus1_FirstSample = false;
      open_loop_step_DW.InverseModulus1_PreviousInput = open_loop_step_B.mmcn2;
    }

    du = (real_T) open_loop_step_B.mmcn2 -
      open_loop_step_DW.InverseModulus1_PreviousInput;
    if (du > half_range) {
      open_loop_step_DW.InverseModulus1_Revolutions =
        open_loop_step_DW.InverseModulus1_Revolutions - 1;
      dy = du - open_loop_step_P.InverseModulus1_Modulus;
    } else if (du < -half_range) {
      open_loop_step_DW.InverseModulus1_Revolutions =
        open_loop_step_DW.InverseModulus1_Revolutions + 1;
      dy = du + open_loop_step_P.InverseModulus1_Modulus;
    } else {
      dy = du;
    }

    rtb_InverseModulus1 = open_loop_step_B.mmcn2 +
      open_loop_step_DW.InverseModulus1_Revolutions *
      open_loop_step_P.InverseModulus1_Modulus;
    open_loop_step_DW.InverseModulus1_PreviousInput = open_loop_step_B.mmcn2;
  }

  /* SignalGenerator: '<Root>/Signal Generator1' */
  temp = open_loop_step_P.SignalGenerator1_Frequency *
    open_loop_step_M->Timing.t[0];
  if (temp - floor(temp) >= 0.5) {
    /* SignalGenerator: '<Root>/Signal Generator1' */
    open_loop_step_B.SignalGenerator1 =
      open_loop_step_P.SignalGenerator1_Amplitude;
  } else {
    /* SignalGenerator: '<Root>/Signal Generator1' */
    open_loop_step_B.SignalGenerator1 =
      -open_loop_step_P.SignalGenerator1_Amplitude;
  }

  /* End of SignalGenerator: '<Root>/Signal Generator1' */

  /* Gain: '<S3>/Cable Gain' */
  open_loop_step_B.CableGain = open_loop_step_P.CableGain_Gain *
    open_loop_step_B.SignalGenerator1;

  /* S-Function (hil_write_analog_block): '<S3>/HIL Write Analog' */

  /* S-Function Block: open_loop_step/Plant/HIL Write Analog (hil_write_analog_block) */
  {
    t_error result;
    result = hil_write_analog(open_loop_step_DW.HILInitialize_Card,
      &open_loop_step_P.HILWriteAnalog_channels, 1, &open_loop_step_B.CableGain);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(open_loop_step_M, _rt_error_message);
    }
  }

  /* SampleTimeMath: '<S1>/TSamp'
   *
   * About '<S1>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  open_loop_step_B.TSamp = rtb_InverseModulus * open_loop_step_P.TSamp_WtEt;

  /* Sum: '<S1>/Diff' incorporates:
   *  UnitDelay: '<S1>/UD'
   */
  open_loop_step_B.Diff = open_loop_step_B.TSamp - open_loop_step_DW.UD_DSTATE;

  /* DiscreteTransferFcn: '<Root>/Discrete Transfer Fcn' */
  open_loop_step_B.DiscreteTransferFcn =
    open_loop_step_P.DiscreteTransferFcn_NumCoef *
    open_loop_step_DW.DiscreteTransferFcn_states;

  /* SampleTimeMath: '<S2>/TSamp'
   *
   * About '<S2>/TSamp':
   *  y = u * K where K = 1 / ( w * Ts )
   */
  open_loop_step_B.TSamp_d = rtb_InverseModulus1 * open_loop_step_P.TSamp_WtEt_h;

  /* Sum: '<S2>/Diff' incorporates:
   *  UnitDelay: '<S2>/UD'
   */
  open_loop_step_B.Diff_a = open_loop_step_B.TSamp_d -
    open_loop_step_DW.UD_DSTATE_p;

  /* DiscreteTransferFcn: '<Root>/Discrete Transfer Fcn1' */
  open_loop_step_B.DiscreteTransferFcn1 =
    open_loop_step_P.DiscreteTransferFcn1_NumCoef *
    open_loop_step_DW.DiscreteTransferFcn1_states;
}

/* Model update function */
void open_loop_step_update(void)
{
  /* Update for UnitDelay: '<S1>/UD' */
  open_loop_step_DW.UD_DSTATE = open_loop_step_B.TSamp;

  /* Update for DiscreteTransferFcn: '<Root>/Discrete Transfer Fcn' */
  open_loop_step_DW.DiscreteTransferFcn_states = (open_loop_step_B.Diff -
    open_loop_step_P.DiscreteTransferFcn_DenCoef[1] *
    open_loop_step_DW.DiscreteTransferFcn_states) /
    open_loop_step_P.DiscreteTransferFcn_DenCoef[0];

  /* Update for UnitDelay: '<S2>/UD' */
  open_loop_step_DW.UD_DSTATE_p = open_loop_step_B.TSamp_d;

  /* Update for DiscreteTransferFcn: '<Root>/Discrete Transfer Fcn1' */
  open_loop_step_DW.DiscreteTransferFcn1_states = (open_loop_step_B.Diff_a -
    open_loop_step_P.DiscreteTransferFcn1_DenCoef[1] *
    open_loop_step_DW.DiscreteTransferFcn1_states) /
    open_loop_step_P.DiscreteTransferFcn1_DenCoef[0];

  /* Update absolute time for base rate */
  /* The "clockTick0" counts the number of times the code of this task has
   * been executed. The absolute time is the multiplication of "clockTick0"
   * and "Timing.stepSize0". Size of "clockTick0" ensures timer will not
   * overflow during the application lifespan selected.
   * Timer of this task consists of two 32 bit unsigned integers.
   * The two integers represent the low bits Timing.clockTick0 and the high bits
   * Timing.clockTickH0. When the low bit overflows to 0, the high bits increment.
   */
  if (!(++open_loop_step_M->Timing.clockTick0)) {
    ++open_loop_step_M->Timing.clockTickH0;
  }

  open_loop_step_M->Timing.t[0] = open_loop_step_M->Timing.clockTick0 *
    open_loop_step_M->Timing.stepSize0 + open_loop_step_M->Timing.clockTickH0 *
    open_loop_step_M->Timing.stepSize0 * 4294967296.0;

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
    if (!(++open_loop_step_M->Timing.clockTick1)) {
      ++open_loop_step_M->Timing.clockTickH1;
    }

    open_loop_step_M->Timing.t[1] = open_loop_step_M->Timing.clockTick1 *
      open_loop_step_M->Timing.stepSize1 + open_loop_step_M->Timing.clockTickH1 *
      open_loop_step_M->Timing.stepSize1 * 4294967296.0;
  }
}

/* Model initialize function */
void open_loop_step_initialize(void)
{
  /* Start for S-Function (hil_initialize_block): '<S3>/HIL Initialize' */

  /* S-Function Block: open_loop_step/Plant/HIL Initialize (hil_initialize_block) */
  {
    t_int result;
    t_boolean is_switching;
    result = hil_open("q2_usb", "0", &open_loop_step_DW.HILInitialize_Card);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(open_loop_step_M, _rt_error_message);
      return;
    }

    is_switching = false;
    result = hil_set_card_specific_options(open_loop_step_DW.HILInitialize_Card,
      "d0=digital;d1=digital;led=auto;update_rate=normal;decimation=1", 63);
    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(open_loop_step_M, _rt_error_message);
      return;
    }

    result = hil_watchdog_clear(open_loop_step_DW.HILInitialize_Card);
    if (result < 0 && result != -QERR_HIL_WATCHDOG_CLEAR) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(open_loop_step_M, _rt_error_message);
      return;
    }

    if ((open_loop_step_P.HILInitialize_AIPStart && !is_switching) ||
        (open_loop_step_P.HILInitialize_AIPEnter && is_switching)) {
      open_loop_step_DW.HILInitialize_AIMinimums[0] =
        (open_loop_step_P.HILInitialize_AILow);
      open_loop_step_DW.HILInitialize_AIMinimums[1] =
        (open_loop_step_P.HILInitialize_AILow);
      open_loop_step_DW.HILInitialize_AIMaximums[0] =
        open_loop_step_P.HILInitialize_AIHigh;
      open_loop_step_DW.HILInitialize_AIMaximums[1] =
        open_loop_step_P.HILInitialize_AIHigh;
      result = hil_set_analog_input_ranges(open_loop_step_DW.HILInitialize_Card,
        open_loop_step_P.HILInitialize_AIChannels, 2U,
        &open_loop_step_DW.HILInitialize_AIMinimums[0],
        &open_loop_step_DW.HILInitialize_AIMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(open_loop_step_M, _rt_error_message);
        return;
      }
    }

    if ((open_loop_step_P.HILInitialize_AOPStart && !is_switching) ||
        (open_loop_step_P.HILInitialize_AOPEnter && is_switching)) {
      open_loop_step_DW.HILInitialize_AOMinimums[0] =
        (open_loop_step_P.HILInitialize_AOLow);
      open_loop_step_DW.HILInitialize_AOMinimums[1] =
        (open_loop_step_P.HILInitialize_AOLow);
      open_loop_step_DW.HILInitialize_AOMaximums[0] =
        open_loop_step_P.HILInitialize_AOHigh;
      open_loop_step_DW.HILInitialize_AOMaximums[1] =
        open_loop_step_P.HILInitialize_AOHigh;
      result = hil_set_analog_output_ranges(open_loop_step_DW.HILInitialize_Card,
        open_loop_step_P.HILInitialize_AOChannels, 2U,
        &open_loop_step_DW.HILInitialize_AOMinimums[0],
        &open_loop_step_DW.HILInitialize_AOMaximums[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(open_loop_step_M, _rt_error_message);
        return;
      }
    }

    if ((open_loop_step_P.HILInitialize_AOStart && !is_switching) ||
        (open_loop_step_P.HILInitialize_AOEnter && is_switching)) {
      open_loop_step_DW.HILInitialize_AOVoltages[0] =
        open_loop_step_P.HILInitialize_AOInitial;
      open_loop_step_DW.HILInitialize_AOVoltages[1] =
        open_loop_step_P.HILInitialize_AOInitial;
      result = hil_write_analog(open_loop_step_DW.HILInitialize_Card,
        open_loop_step_P.HILInitialize_AOChannels, 2U,
        &open_loop_step_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(open_loop_step_M, _rt_error_message);
        return;
      }
    }

    if (open_loop_step_P.HILInitialize_AOReset) {
      open_loop_step_DW.HILInitialize_AOVoltages[0] =
        open_loop_step_P.HILInitialize_AOWatchdog;
      open_loop_step_DW.HILInitialize_AOVoltages[1] =
        open_loop_step_P.HILInitialize_AOWatchdog;
      result = hil_watchdog_set_analog_expiration_state
        (open_loop_step_DW.HILInitialize_Card,
         open_loop_step_P.HILInitialize_AOChannels, 2U,
         &open_loop_step_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(open_loop_step_M, _rt_error_message);
        return;
      }
    }

    if ((open_loop_step_P.HILInitialize_EIPStart && !is_switching) ||
        (open_loop_step_P.HILInitialize_EIPEnter && is_switching)) {
      open_loop_step_DW.HILInitialize_QuadratureModes[0] =
        open_loop_step_P.HILInitialize_EIQuadrature;
      open_loop_step_DW.HILInitialize_QuadratureModes[1] =
        open_loop_step_P.HILInitialize_EIQuadrature;
      result = hil_set_encoder_quadrature_mode
        (open_loop_step_DW.HILInitialize_Card,
         open_loop_step_P.HILInitialize_EIChannels, 2U,
         (t_encoder_quadrature_mode *)
         &open_loop_step_DW.HILInitialize_QuadratureModes[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(open_loop_step_M, _rt_error_message);
        return;
      }
    }

    if ((open_loop_step_P.HILInitialize_EIStart && !is_switching) ||
        (open_loop_step_P.HILInitialize_EIEnter && is_switching)) {
      open_loop_step_DW.HILInitialize_InitialEICounts[0] =
        open_loop_step_P.HILInitialize_EIInitial;
      open_loop_step_DW.HILInitialize_InitialEICounts[1] =
        open_loop_step_P.HILInitialize_EIInitial;
      result = hil_set_encoder_counts(open_loop_step_DW.HILInitialize_Card,
        open_loop_step_P.HILInitialize_EIChannels, 2U,
        &open_loop_step_DW.HILInitialize_InitialEICounts[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(open_loop_step_M, _rt_error_message);
        return;
      }
    }
  }

  /* Start for S-Function (hil_read_encoder_timebase_block): '<S3>/HIL Read Encoder Timebase' */

  /* S-Function Block: open_loop_step/Plant/HIL Read Encoder Timebase (hil_read_encoder_timebase_block) */
  {
    t_error result;
    result = hil_task_create_encoder_reader(open_loop_step_DW.HILInitialize_Card,
      open_loop_step_P.HILReadEncoderTimebase_SamplesI,
      open_loop_step_P.HILReadEncoderTimebase_Channels, 2,
      &open_loop_step_DW.HILReadEncoderTimebase_Task);
    if (result >= 0) {
      result = hil_task_set_buffer_overflow_mode
        (open_loop_step_DW.HILReadEncoderTimebase_Task, (t_buffer_overflow_mode)
         (open_loop_step_P.HILReadEncoderTimebase_Overflow - 1));
    }

    if (result < 0) {
      msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
        (_rt_error_message));
      rtmSetErrorStatus(open_loop_step_M, _rt_error_message);
    }
  }

  /* Start for S-Function (inverse_modulus_block): '<S3>/Inverse Modulus' */

  /* S-Function Block: open_loop_step/Plant/Inverse Modulus (inverse_modulus_block) */
  {
    open_loop_step_DW.InverseModulus_FirstSample = true;
    open_loop_step_DW.InverseModulus_Revolutions = 0;
  }

  /* Start for S-Function (inverse_modulus_block): '<S3>/Inverse Modulus1' */

  /* S-Function Block: open_loop_step/Plant/Inverse Modulus1 (inverse_modulus_block) */
  {
    open_loop_step_DW.InverseModulus1_FirstSample = true;
    open_loop_step_DW.InverseModulus1_Revolutions = 0;
  }

  /* InitializeConditions for UnitDelay: '<S1>/UD' */
  open_loop_step_DW.UD_DSTATE = open_loop_step_P.DiscreteDerivative_ICPrevScaled;

  /* InitializeConditions for DiscreteTransferFcn: '<Root>/Discrete Transfer Fcn' */
  open_loop_step_DW.DiscreteTransferFcn_states =
    open_loop_step_P.DiscreteTransferFcn_InitialStat;

  /* InitializeConditions for UnitDelay: '<S2>/UD' */
  open_loop_step_DW.UD_DSTATE_p =
    open_loop_step_P.DiscreteDerivative1_ICPrevScale;

  /* InitializeConditions for DiscreteTransferFcn: '<Root>/Discrete Transfer Fcn1' */
  open_loop_step_DW.DiscreteTransferFcn1_states =
    open_loop_step_P.DiscreteTransferFcn1_InitialSta;
}

/* Model terminate function */
void open_loop_step_terminate(void)
{
  /* Terminate for S-Function (hil_initialize_block): '<S3>/HIL Initialize' */

  /* S-Function Block: open_loop_step/Plant/HIL Initialize (hil_initialize_block) */
  {
    t_boolean is_switching;
    t_int result;
    t_uint32 num_final_analog_outputs = 0;
    hil_task_stop_all(open_loop_step_DW.HILInitialize_Card);
    hil_monitor_stop_all(open_loop_step_DW.HILInitialize_Card);
    is_switching = false;
    if ((open_loop_step_P.HILInitialize_AOTerminate && !is_switching) ||
        (open_loop_step_P.HILInitialize_AOExit && is_switching)) {
      open_loop_step_DW.HILInitialize_AOVoltages[0] =
        open_loop_step_P.HILInitialize_AOFinal;
      open_loop_step_DW.HILInitialize_AOVoltages[1] =
        open_loop_step_P.HILInitialize_AOFinal;
      num_final_analog_outputs = 2U;
    } else {
      num_final_analog_outputs = 0;
    }

    if (num_final_analog_outputs > 0) {
      result = hil_write_analog(open_loop_step_DW.HILInitialize_Card,
        open_loop_step_P.HILInitialize_AOChannels, num_final_analog_outputs,
        &open_loop_step_DW.HILInitialize_AOVoltages[0]);
      if (result < 0) {
        msg_get_error_messageA(NULL, result, _rt_error_message, sizeof
          (_rt_error_message));
        rtmSetErrorStatus(open_loop_step_M, _rt_error_message);
      }
    }

    hil_task_delete_all(open_loop_step_DW.HILInitialize_Card);
    hil_monitor_delete_all(open_loop_step_DW.HILInitialize_Card);
    hil_close(open_loop_step_DW.HILInitialize_Card);
    open_loop_step_DW.HILInitialize_Card = NULL;
  }
}

/*========================================================================*
 * Start of Classic call interface                                        *
 *========================================================================*/
void MdlOutputs(int_T tid)
{
  open_loop_step_output();
  UNUSED_PARAMETER(tid);
}

void MdlUpdate(int_T tid)
{
  open_loop_step_update();
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
  open_loop_step_initialize();
}

void MdlTerminate(void)
{
  open_loop_step_terminate();
}

/* Registration function */
RT_MODEL_open_loop_step_T *open_loop_step(void)
{
  /* Registration code */

  /* initialize non-finites */
  rt_InitInfAndNaN(sizeof(real_T));

  /* initialize real-time model */
  (void) memset((void *)open_loop_step_M, 0,
                sizeof(RT_MODEL_open_loop_step_T));

  {
    /* Setup solver object */
    rtsiSetSimTimeStepPtr(&open_loop_step_M->solverInfo,
                          &open_loop_step_M->Timing.simTimeStep);
    rtsiSetTPtr(&open_loop_step_M->solverInfo, &rtmGetTPtr(open_loop_step_M));
    rtsiSetStepSizePtr(&open_loop_step_M->solverInfo,
                       &open_loop_step_M->Timing.stepSize0);
    rtsiSetErrorStatusPtr(&open_loop_step_M->solverInfo, (&rtmGetErrorStatus
      (open_loop_step_M)));
    rtsiSetRTModelPtr(&open_loop_step_M->solverInfo, open_loop_step_M);
  }

  rtsiSetSimTimeStep(&open_loop_step_M->solverInfo, MAJOR_TIME_STEP);
  rtsiSetSolverName(&open_loop_step_M->solverInfo,"FixedStepDiscrete");

  /* Initialize timing info */
  {
    int_T *mdlTsMap = open_loop_step_M->Timing.sampleTimeTaskIDArray;
    mdlTsMap[0] = 0;
    mdlTsMap[1] = 1;

    /* polyspace +2 MISRA2012:D4.1 [Justified:Low] "open_loop_step_M points to
       static memory which is guaranteed to be non-NULL" */
    open_loop_step_M->Timing.sampleTimeTaskIDPtr = (&mdlTsMap[0]);
    open_loop_step_M->Timing.sampleTimes =
      (&open_loop_step_M->Timing.sampleTimesArray[0]);
    open_loop_step_M->Timing.offsetTimes =
      (&open_loop_step_M->Timing.offsetTimesArray[0]);

    /* task periods */
    open_loop_step_M->Timing.sampleTimes[0] = (0.0);
    open_loop_step_M->Timing.sampleTimes[1] = (0.001);

    /* task offsets */
    open_loop_step_M->Timing.offsetTimes[0] = (0.0);
    open_loop_step_M->Timing.offsetTimes[1] = (0.0);
  }

  rtmSetTPtr(open_loop_step_M, &open_loop_step_M->Timing.tArray[0]);

  {
    int_T *mdlSampleHits = open_loop_step_M->Timing.sampleHitArray;
    mdlSampleHits[0] = 1;
    mdlSampleHits[1] = 1;
    open_loop_step_M->Timing.sampleHits = (&mdlSampleHits[0]);
  }

  rtmSetTFinal(open_loop_step_M, 8.0);
  open_loop_step_M->Timing.stepSize0 = 0.001;
  open_loop_step_M->Timing.stepSize1 = 0.001;

  /* External mode info */
  open_loop_step_M->Sizes.checksums[0] = (932916017U);
  open_loop_step_M->Sizes.checksums[1] = (1283051530U);
  open_loop_step_M->Sizes.checksums[2] = (728084338U);
  open_loop_step_M->Sizes.checksums[3] = (2879354361U);

  {
    static const sysRanDType rtAlwaysEnabled = SUBSYS_RAN_BC_ENABLE;
    static RTWExtModeInfo rt_ExtModeInfo;
    static const sysRanDType *systemRan[1];
    open_loop_step_M->extModeInfo = (&rt_ExtModeInfo);
    rteiSetSubSystemActiveVectorAddresses(&rt_ExtModeInfo, systemRan);
    systemRan[0] = &rtAlwaysEnabled;
    rteiSetModelMappingInfoPtr(open_loop_step_M->extModeInfo,
      &open_loop_step_M->SpecialInfo.mappingInfo);
    rteiSetChecksumsPtr(open_loop_step_M->extModeInfo,
                        open_loop_step_M->Sizes.checksums);
    rteiSetTPtr(open_loop_step_M->extModeInfo, rtmGetTPtr(open_loop_step_M));
  }

  open_loop_step_M->solverInfoPtr = (&open_loop_step_M->solverInfo);
  open_loop_step_M->Timing.stepSize = (0.001);
  rtsiSetFixedStepSize(&open_loop_step_M->solverInfo, 0.001);
  rtsiSetSolverMode(&open_loop_step_M->solverInfo, SOLVER_MODE_SINGLETASKING);

  /* block I/O */
  open_loop_step_M->blockIO = ((void *) &open_loop_step_B);
  (void) memset(((void *) &open_loop_step_B), 0,
                sizeof(B_open_loop_step_T));

  /* parameters */
  open_loop_step_M->defaultParam = ((real_T *)&open_loop_step_P);

  /* states (dwork) */
  open_loop_step_M->dwork = ((void *) &open_loop_step_DW);
  (void) memset((void *)&open_loop_step_DW, 0,
                sizeof(DW_open_loop_step_T));

  /* data type transition information */
  {
    static DataTypeTransInfo dtInfo;
    (void) memset((char_T *) &dtInfo, 0,
                  sizeof(dtInfo));
    open_loop_step_M->SpecialInfo.mappingInfo = (&dtInfo);
    dtInfo.numDataTypes = 20;
    dtInfo.dataTypeSizes = &rtDataTypeSizes[0];
    dtInfo.dataTypeNames = &rtDataTypeNames[0];

    /* Block I/O transition table */
    dtInfo.BTransTable = &rtBTransTable;

    /* Parameters transition table */
    dtInfo.PTransTable = &rtPTransTable;
  }

  /* Initialize Sizes */
  open_loop_step_M->Sizes.numContStates = (0);/* Number of continuous states */
  open_loop_step_M->Sizes.numY = (0);  /* Number of model outputs */
  open_loop_step_M->Sizes.numU = (0);  /* Number of model inputs */
  open_loop_step_M->Sizes.sysDirFeedThru = (0);/* The model is not direct feedthrough */
  open_loop_step_M->Sizes.numSampTimes = (2);/* Number of sample times */
  open_loop_step_M->Sizes.numBlocks = (22);/* Number of blocks */
  open_loop_step_M->Sizes.numBlockIO = (10);/* Number of block outputs */
  open_loop_step_M->Sizes.numBlockPrms = (88);/* Sum of parameter "widths" */
  return open_loop_step_M;
}

/*========================================================================*
 * End of Classic call interface                                          *
 *========================================================================*/
