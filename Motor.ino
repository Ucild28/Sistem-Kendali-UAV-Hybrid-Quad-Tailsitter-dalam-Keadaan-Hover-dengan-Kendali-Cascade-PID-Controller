void motor_setup()
{
  M1.attach(PE0, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);
  M2.attach(PE1, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);
  M3.attach(PE2, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);
  M4.attach(PE3, MIN_PULSE_LENGTH, MAX_PULSE_LENGTH);
}

void update_motor()
{ 
  if(ch5==0)
  {
    armStatus            = 0;
		ControllerIRoll      = 0;
		ControllerIPitch     = 0;
		ControllerIYaw       = 0;
		ControllerDRollLast  = 0;
		ControllerDPitchLast = 0;
		ControllerDYawLast   = 0;
    setHeading           = headingDegrees;
    M1.writeMicroseconds(MIN_PULSE_LENGTH);
    M2.writeMicroseconds(MIN_PULSE_LENGTH);
    M3.writeMicroseconds(MIN_PULSE_LENGTH);
    M4.writeMicroseconds(MIN_PULSE_LENGTH);
    pulse_length_esc1 = 1000;
    pulse_length_esc2 = 1000;
    pulse_length_esc3 = 1000;
    pulse_length_esc4 = 1000;
  }

  if(ch5==1 && throttle_channel<=1000) {armStatus=1;}

  if(armStatus==1 && ch6 ==0)
  {
    controlHover();
  
    M1.writeMicroseconds(pulse_length_esc1);
    M2.writeMicroseconds(pulse_length_esc2);
    M3.writeMicroseconds(pulse_length_esc3);
    M4.writeMicroseconds(pulse_length_esc4);
  }
}