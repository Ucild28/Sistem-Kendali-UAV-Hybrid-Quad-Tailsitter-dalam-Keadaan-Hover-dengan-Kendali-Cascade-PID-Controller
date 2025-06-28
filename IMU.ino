void init_imu()
{
  #if ARDUINO >= 157
  Wire.setClock(400000UL); // Set I2C frequency to 400kHz
  #else
	TWBR = ((F_CPU / 400000UL) - 16) / 2; // Set I2C frequency to 400kHz
  #endif

	i2cData[0] = 7; // Set the sample rate to 1000Hz - 8kHz/(7+1) = 1000Hz
	i2cData[1] = 0x00; // Disable FSYNC and set 260 Hz Acc filtering, 256 Hz Gyro filtering, 8 KHz sampling
	i2cData[2] = 0x08; // Set Gyro Full Scale Range to �250deg/s
	i2cData[3] = 0x10; // Set Accelerometer Full Scale Range to �2g
	while (i2cWrite(MPU6050, 0x19, i2cData, 4, false)); // Write to all four registers at once
	while (i2cWrite(MPU6050, 0x6B, 0x01, true)); // PLL with X axis gyroscope reference and disable sleep mode

	while (i2cRead(MPU6050, 0x75, i2cData, 1));
	if (i2cData[0] != 0x68) { // Read "WHO_AM_I" register
		Serial.print(F("Error reading sensor"));
		while (1);
	}

	delay(100); // Wait for sensor to stabilize

	/* Set kalman and gyro starting angle */
  while (i2cRead(MPU6050, 0x3B, i2cData, 6));
  accX = (int16_t)((i2cData[0] << 8) | i2cData[1]);
  accY = (int16_t)((i2cData[2] << 8) | i2cData[3]);
  accZ = (int16_t)((i2cData[4] << 8) | i2cData[5]);

  #ifdef RESTRICT_PITCH 
  pitch = atan2(accZ, sqrt(accX * accX + accY * accY)) * RAD_TO_DEG; 
  roll  = atan2(accY, sqrt(accX * accX + accZ * accZ)) * RAD_TO_DEG; 
  #else 
  pitch = atan2(accZ, sqrt(accX * accX + accY * accY)) * RAD_TO_DEG; 
  roll  = atan2(accY, accZ) * RAD_TO_DEG; 
  #endif

  kalmanZ.setAngle(roll);
  kalmanY.setAngle(pitch);
  gyroZangle = roll;
  gyroYangle = pitch;
  compAngleZ = roll;
  compAngleY = pitch;

  timer = micros();

	Serial.print("Gyro Calibration");
	for (cal_int = 0; cal_int < 2000; cal_int++)
	{
		gyro_signal();
		gyro_roll_cal  += gyro_roll ;
		gyro_pitch_cal += gyro_pitch;
		gyro_yaw_cal   += gyro_yaw  ;
		if (cal_int % 100 == 0){ Serial.print("."); }
		delay(4);
	}

	Serial.print("done!");
	gyro_pitch_cal /= 2000;
	gyro_roll_cal  /= 2000;
	gyro_yaw_cal   /= 2000;
}


void gyro_signal()
{
  if (i2cRead(MPU6050, 0x3B, i2cData, 14) != 0) 
  {
    Serial.println(F("Gyro read failed!"));
    return;
  }

  int16_t gyroX = (i2cData[8]  << 8) | i2cData[9];
  int16_t gyroY = (i2cData[10] << 8) | i2cData[11];
  int16_t gyroZ = (i2cData[12] << 8) | i2cData[13];

  gyro_roll  = gyroZ * -1;    // Roll pakai sumbu Z
  gyro_pitch = gyroY;         // Pitch tetap pakai sumbu Y
  gyro_yaw   = gyroX * -1;    // Yaw pakai sumbu X
}


void gyroaccell_signal()
{
  while (i2cRead(MPU6050, 0x3B, i2cData, 14));
  accX    = (int16_t)((i2cData[0]  << 8) | i2cData[1]);
  accY    = (int16_t)((i2cData[2]  << 8) | i2cData[3]);
  accZ    = (int16_t)((i2cData[4]  << 8) | i2cData[5]);
  tempRaw = (int16_t)((i2cData[6]  << 8) | i2cData[7]);
  gyroX   = (int16_t)((i2cData[8]  << 8) | i2cData[9]);
  gyroY   = (int16_t)((i2cData[10] << 8) | i2cData[11]);
  gyroZ   = (int16_t)((i2cData[12] << 8) | i2cData[13]);

  gyro_roll  = gyroZ * -1;    // Roll = Z
  gyro_pitch = gyroY;         // Pitch = Y
  gyro_yaw   = gyroX * -1;    // Yaw = X

  double dt = (double)(micros() - timer) / 1000000;
  timer = micros();

  #ifdef RESTRICT_PITCH 
  pitch = atan2(accZ, sqrt(accX * accX + accY * accY)) * RAD_TO_DEG; 
  roll  = atan2(accY, sqrt(accX * accX + accZ * accZ)) * RAD_TO_DEG; 
  #else 
  pitch = atan2(accZ, sqrt(accX * accX + accY * accY)) * RAD_TO_DEG; 
  roll  = atan2(accY, accZ) * RAD_TO_DEG; 
  #endif

  gyroZrate = gyroZ / 131.0; // Convert to deg/s Untuk roll
  gyroYrate = gyroY / 131.0; // Convert to deg/s Untuk pitch
  gyroXrate = gyroX / 131.0; // Convert to deg/s untuk yaw

#ifdef RESTRICT_PITCH
  // Roll = Z axis
  if ((roll < -90 && kalAngleZ > 90) || (roll > 90 && kalAngleZ < -90)) {
    kalmanZ.setAngle(roll);
    compAngleZ = roll;
    kalAngleZ  = roll;
    gyroZangle = roll;
  } else {
    kalAngleZ = kalmanZ.getAngle(roll, gyroZrate, dt);
  }

  if (abs(kalAngleZ) > 90)
    gyroYrate = -gyroYrate;
    kalAngleY = kalmanY.getAngle(pitch, gyroYrate, dt);
  // Tambahan untuk Yaw = X axis
  // float yaw = gyroXangle;
    // static float yaw = 0.0; // estimasi yaw awal (state)
    // yaw += gyroXrate * dt;  // integrasi gyro X (yaw rate)
    kalAngleX = kalmanX.getAngle(yaw, gyroXrate, dt);

#else
  // Pitch = Y axis
  if ((pitch < -90 && kalAngleY > 90) || (pitch > 90 && kalAngleY < -90)) {
    kalmanY.setAngle(pitch);
    compAngleY = pitch;
    kalAngleY  = pitch;
    gyroYangle = pitch;
  } else {
    kalAngleY = kalmanY.getAngle(pitch, gyroYrate, dt);
  }

  if (abs(kalAngleY) > 90)
    gyroZrate = -gyroZrate;
    kalAngleZ = kalmanZ.getAngle(roll, gyroZrate, dt);

    // Tambahan untuk Yaw = X axis
    // float yaw = gyroXangle;
    kalAngleX = kalmanX.getAngle(yaw, gyroXrate, dt);
#endif

gyroZangle += gyroZrate * dt; // Roll  (Z)
gyroYangle += gyroYrate * dt; // Pitch (Y)
gyroXangle += gyroXrate * dt; // Yaw   (X)

if (gyroZangle < -180 || gyroZangle > 180)
  gyroZangle = kalAngleZ;
if (gyroYangle < -180 || gyroYangle > 180)
  gyroYangle = kalAngleY;
if (gyroXangle < -180 || gyroXangle > 180)
  gyroXangle = kalAngleX;
}
