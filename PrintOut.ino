void print_out()
{
  timeProgram = micros();
  if (timeProgram - previousTimeProgram >= 100000) 
  {
    //   double dt = (double)(micros() - timer) / 1000000;
    //   timer = micros();
    // Serial.print(dt,8) ; Serial.print("\t");
    // Serial.print(status) ; Serial.print("\t");
    // Serial.print(armStatus) ; Serial.print("\t");
    // Serial.print(roll_mapping) ; Serial.print("\t");
    // Serial.print(pitch_mapping) ; Serial.print("\t");
    // Serial.print(yaw_mapping) ; Serial.print("\t");
    // Serial.print(roll) ; Serial.print("\t");
    // Serial.print(pitch) ; Serial.print("\t");
    // Serial.print(yaw) ; Serial.print("\t");
    // Serial.print(head) ; Serial.print("\t");

    // Serial.print(kalAngleZ) ; Serial.print("\t"); //sudut roll
    Serial.print(kalAngleY) ; Serial.print("\t"); //sudut pitch
    // Serial.print(kalAngleX) ; Serial.print("\t");
    // Serial.print(pitchAngleSetpoint)  ; Serial.print("\t");
    // Serial.print(pitchAngleError) ; Serial.print("\t");
    // Serial.print(pitchRateSetpoint) ; Serial.print("\t");
    // Serial.print(errorRoll) ; Serial.print("\t");
    // Serial.print(errorPitch) ; Serial.print("\t");

    // Serial.print(rollAngleError) ; Serial.print("\t");
    // Serial.print(rollSetpoint) ; Serial.print("\t");
    Serial.print(pitchSetpoint) ; Serial.print("\t");
    // Serial.print(yawSetpoint) ; Serial.print("\t");
    // Serial.print(roll_input)  ; Serial.print("\t");
    // Serial.print(gyro_roll_input)  ; Serial.print("\t");
	  // Serial.print(gyro_pitch_input) ; Serial.print("\t");
    // Serial.print(headingDegrees)   ; Serial.print("\t");
    // Serial.print(setHeading); Serial.print("\t");
    // Serial.print(head); Serial.print("\t");
    // Serial.print(gyroZangle) ; Serial.print("\t");
    // Serial.print(rollLevel)  ; Serial.print("\t");
    // Serial.print(pitchLevel)  ; Serial.print("\t");
    // Serial.print(yawLevel)  ; Serial.print("\t");
    // Serial.print(ControllerIRoll) ; Serial.print("\t");
    // Serial.print(Gain_I_roll) ; Serial.print("\t");


    // Serial.print(heading_reference); Serial.print("\t"); //sudut yaw
    // Serial.print(errorYaw) ; Serial.print("\t");
    // Serial.print(gyro_yaw_input) ; Serial.print("\t");


    // Serial.print(ControlRoll) ; Serial.print("\t");
    // Serial.print(ControlPitch) ; Serial.print("\t");
    // Serial.print(ControlYaw) ; Serial.print("\t");
    // Serial.print(throttle_channel) ; Serial.print("\t");

    // Serial.print(pulse_length_esc1); Serial.print("\t");
    // Serial.print(pulse_length_esc2); Serial.print("\t");
    // Serial.print(pulse_length_esc3); Serial.print("\t");
    // Serial.print(pulse_length_esc4); Serial.print("\t");
    // gainTuningFeedback();
    // batterypercent(); Serial.print("\t");

    Serial.println();

    previousTimeProgram = micros();
  }
}

void gainTuningFeedback()
{
  Serial.print(Gain_P_roll,3)     ;Serial.print("\t");
  Serial.print(Gain_I_roll,4)     ;Serial.print("\t");
  Serial.print(Gain_D_roll,3)     ;Serial.print("\t");

  Serial.print(Gain_P_pitch,3)    ;Serial.print("\t");
  Serial.print(Gain_I_pitch,4)    ;Serial.print("\t");
  Serial.print(Gain_D_pitch,3)    ;Serial.print("\t");

  Serial.print(Gain_P_yaw,3)      ;Serial.print("\t");
  Serial.print(Gain_I_yaw,4)      ;Serial.print("\t");
  Serial.print(Gain_D_yaw,3)      ;Serial.print("\t");
}