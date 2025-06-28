void controlHover()
{
	// ========== Roll Control PID ==========
  errorRoll = rollSetpoint - gyro_roll_input;
	ControllerIRoll += Gain_I_roll * errorRoll;
	if (ControllerIRoll > maxController){ ControllerIRoll = maxController; }
	else if (ControllerIRoll < maxController * -1){ ControllerIRoll = maxController * -1; }
	ControlRoll = Gain_P_roll * errorRoll + ControllerIRoll + Gain_D_roll * (errorRoll - ControllerDRollLast);
	if (ControlRoll > maxController){ ControlRoll = maxController; }
	else if (ControlRoll < maxController * -1){ ControlRoll = maxController * -1; }
	ControllerDRollLast = errorRoll;

	// // ========== Pitch Control PID ==========
	// errorPitch = pitchSetpoint - gyro_pitch_input;
	// ControllerIPitch += Gain_I_pitch * errorPitch;
	// if (ControllerIPitch > maxController){ ControllerIPitch = maxController; }
	// else if (ControllerIPitch < maxController * -1){ ControllerIPitch = maxController * -1; }
	// ControlPitch = Gain_P_pitch * errorPitch + ControllerIPitch + Gain_D_pitch * (errorPitch - ControllerDPitchLast);
  // if (ControlPitch > maxController){ ControlPitch = maxController; }
	// else if (ControlPitch < maxController * -1){ ControlPitch = maxController * -1; }
	// ControllerDPitchLast = errorPitch;

	// ========== Yaw Control PID ==========
	errorYaw = yawSetpoint - gyro_yaw_input;
	ControllerIYaw += Gain_I_yaw * errorYaw;
	if (ControllerIYaw > maxController){ ControllerIYaw = maxController; }
	else if (ControllerIYaw < maxController * -1){ ControllerIYaw = maxController * -1; }
	ControlYaw = Gain_P_yaw * errorYaw + ControllerIYaw + Gain_D_yaw * (errorYaw - ControllerDYawLast);
	if (ControlYaw > maxController){ ControlYaw = maxController; }
	else if (ControlYaw < maxController * -1){ ControlYaw = maxController * -1; }
	ControllerDYawLast = errorYaw;


// Coba Cascade PID
  // // OUTER LOOP: P Controller untuk Roll
  // rollAngleError = rollAngleSetpoint - rollLevel;
  // rollRateSetpoint = Gain_P_angle_roll * rollAngleError;

  // // INNER LOOP: PID Controller Roll Rate
  // errorRoll = rollRateSetpoint - gyro_roll_input;
  // ControllerIRoll += Gain_I_roll * errorRoll;
  // if (ControllerIRoll > maxController) { ControllerIRoll = maxController; }
  // else if (ControllerIRoll < maxController * -1) { ControllerIRoll = maxController * -1; }
  // ControlRoll = Gain_P_roll * errorRoll + ControllerIRoll + Gain_D_roll * (errorRoll - ControllerDRollLast);
  // if (ControlRoll > maxController) { ControlRoll = maxController; }
  // else if (ControlRoll < maxController * -1) { ControlRoll = maxController * -1; }
  // ControllerDRollLast = errorRoll;


  // OUTER LOOP: P Controller untuk Pitch
  pitchAngleError = pitchAngleSetpoint - pitchLevel;
  pitchRateSetpoint = Gain_P_angle_pitch * pitchAngleError;

  // INNER LOOP: PID Controller Pitch Rate)
  errorPitch = pitchRateSetpoint - gyro_pitch_input;
	ControllerIPitch += Gain_I_pitch * errorPitch;
	if (ControllerIPitch > maxController){ ControllerIPitch = maxController; }
	else if (ControllerIPitch < maxController * -1){ ControllerIPitch = maxController * -1; }
	ControlPitch = Gain_P_pitch * errorPitch + ControllerIPitch + Gain_D_pitch * (errorPitch - ControllerDPitchLast);
  if (ControlPitch > maxController){ ControlPitch = maxController; }
	else if (ControlPitch < maxController * -1){ ControlPitch = maxController * -1; }
	ControllerDPitchLast = errorPitch;


  // // OUTER LOOP: P Controller untuk Yaw
  // yawAngleError = yawAngleSetpoint - yawLevel;
  // yawRateSetpoint = Gain_P_angle_yaw * yawAngleError;

  // // INNER LOOP: PID Controller Yaw Rate)
  // errorYaw = yawRateSetpoint - gyro_yaw_input;
	// ControllerIYaw += Gain_I_yaw * errorYaw;
	// if (ControllerIYaw > maxController){ ControllerIYaw = maxController; }
	// else if (ControllerIYaw < maxController * -1){ ControllerIYaw = maxController * -1; }
	// ControlYaw = Gain_P_yaw * errorYaw + ControllerIYaw + Gain_D_yaw * (errorYaw - ControllerDYawLast);
  // if (ControlYaw > maxController){ ControlYaw = maxController; }
	// else if (ControlYaw < maxController * -1){ ControlYaw = maxController * -1; }
	// ControllerDYawLast = errorYaw;
  
  pulse_length_esc1 = throttle_channel - (ControlRoll) - (ControlPitch) + (ControlYaw);  // M1 kanan depan
  pulse_length_esc2 = throttle_channel + (ControlRoll) + (ControlPitch) + (ControlYaw);  // M2 kiri belakang
  pulse_length_esc3 = throttle_channel + (ControlRoll) - (ControlPitch) - (ControlYaw);  // M3 kiri depan
  pulse_length_esc4 = throttle_channel - (ControlRoll) + (ControlPitch) - (ControlYaw);  // M4 kanan belakang

  pulse_length_esc1 = constrain(pulse_length_esc1, 1100, 2000);
  pulse_length_esc2 = constrain(pulse_length_esc2, 1100, 2000);
  pulse_length_esc3 = constrain(pulse_length_esc3, 1100, 2000);
  pulse_length_esc4 = constrain(pulse_length_esc4, 1100, 2000);
}