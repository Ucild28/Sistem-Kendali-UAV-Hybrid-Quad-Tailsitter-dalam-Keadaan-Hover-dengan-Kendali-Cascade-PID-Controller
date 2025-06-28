void mapremote()
{
  elrs_update(); // Update data from remote ELRS

  rollLevel  = kalAngleZ;
  pitchLevel = kalAngleY;
  yawLevel   = heading_reference;

  roll_mapping  = map(roll_channel, 988, 2011, 1000, 1500);
  pitch_mapping = map(pitch_channel, 988, 2011, 1000, 1500);
  yaw_mapping   = map(yaw_channel, 988, 2011, 1000, 1500);

//=========  Setpoint jika pakai PID  ===========
  rollSetpoint = 0;
	if (roll_mapping > 1255){ rollSetpoint = roll_mapping - 1255; }
	else if (roll_mapping < 1245){ rollSetpoint = roll_mapping - 1245; }
	rollSetpoint -= rollLevel;
	rollSetpoint /= 1.5;

  // pitchSetpoint = 0;
	// if (pitch_mapping > 1255){ pitchSetpoint = pitch_mapping - 1255; }
	// else if (pitch_mapping < 1245){ pitchSetpoint = pitch_mapping - 1245; }
	// pitchSetpoint -= pitchLevel;
	// pitchSetpoint /= 1.5;

  yawSetpoint = 0;
	if (yaw_mapping > 1255){ yawSetpoint = yaw_mapping - 1255; }
	else if (yaw_mapping < 1245){ yawSetpoint = yaw_mapping - 1245; }
	yawSetpoint -= yawLevel;
	yawSetpoint /= 1.5;



//=========  Setpoint jika pakai Cascade PID  =========

  // rollAngleSetpoint = 0;
	// if (roll_mapping > 1255){ rollAngleSetpoint = roll_mapping - 1255; }
	// else if (roll_mapping < 1245){ rollAngleSetpoint = roll_mapping - 1244; }
	// // rollAngleSetpoint -= rollLevel;
	// rollAngleSetpoint /= 1.5;

  pitchAngleSetpoint = 0;
	if (pitch_mapping > 1255){ pitchAngleSetpoint = pitch_mapping - 1255; }
	else if (pitch_mapping < 1245){ pitchAngleSetpoint = pitch_mapping - 1244; }
	rollAngleSetpoint -= pitchLevel;
	pitchAngleSetpoint /= 1.5;

  // yawAngleSetpoint = 0;
	// if (yaw_mapping > 1255){ yawAngleSetpoint = yaw_mapping - 1255; }
	// else if (yaw_mapping < 1245){ yawAngleSetpoint = yaw_mapping - 1244; }
	// // yawAngleSetpoint -= yawLevel;
	// yawAngleSetpoint /= 1.5;


  // ========== Channel 5 (ARM Switch) ==========
  if (ch5_channel < 1600) { 
    ch5 = 0;
    status = "DISARMED";
  } 
  if (ch5_channel > 1600) {
    ch5 = 1;
    status = "ARMED";
  }

  // ========== Channel 6 (Control Mode) ==========
  if (ch6_channel < 1400) { ch6 = 0; } 
  else { ch6 = 1; }
}

void serialEvent()
{
	while (Serial.available())
	{
		inChar = Serial.read();

    //========== roll gain feedback ==========
		if (inChar == 'q') { Gain_P_roll = Gain_P_roll + 0.01 ;  }
		if (inChar == 'w') { Gain_P_roll = Gain_P_roll - 0.01 ;	 }
		if (inChar == 'e') { Gain_I_roll = Gain_I_roll + 0.0001; }
		if (inChar == 'r') { Gain_I_roll = Gain_I_roll - 0.0001; }
		if (inChar == 't') { Gain_D_roll = Gain_D_roll + 0.01 ;	 }
		if (inChar == 'y') { Gain_D_roll = Gain_D_roll - 0.01 ;  }

    //========== pitch gain feedback ==========
		if (inChar == 'a')  { Gain_P_pitch = Gain_P_pitch + 0.01 ; }
		if (inChar == 's')  { Gain_P_pitch = Gain_P_pitch - 0.01 ; }
		if (inChar == 'd')  { Gain_I_pitch = Gain_I_pitch + 0.0001;}
		if (inChar == 'f')  { Gain_I_pitch = Gain_I_pitch - 0.0001;}
		if (inChar == 'g')  { Gain_D_pitch = Gain_D_pitch + 0.01 ; }
		if (inChar == 'h')  { Gain_D_pitch = Gain_D_pitch - 0.01 ; }

    //========== yaw gain feedback ==========
		if (inChar == 'z')  {	Gain_P_yaw = Gain_P_yaw + 0.001 ; }
		if (inChar == 'x')  { Gain_P_yaw = Gain_P_yaw - 0.001 ; }
		if (inChar == 'c')  { Gain_I_yaw = Gain_I_yaw + 0.0001; }
		if (inChar == 'v')  { Gain_I_yaw = Gain_I_yaw - 0.0001; }
		if (inChar == 'b')  { Gain_D_yaw = Gain_D_yaw + 0.001 ; }
		if (inChar == 'n')  { Gain_D_yaw = Gain_D_yaw - 0.001 ; }
	}
}
