void compass_init()
{
	// while (!compass.begin())
	// {
	// 	Serial.println("Could not find a valid HMC5883L sensor, check wiring!");
	// 	delay(500);
	// }

	// Set measurement range
	compass.setRange(HMC5883L_RANGE_1_3GA);

	// Set measurement mode
	compass.setMeasurementMode(HMC5883L_CONTINOUS);

	// Set data rate
	compass.setDataRate(HMC5883L_DATARATE_30HZ);

	// Set number of samples averaged
	compass.setSamples(HMC5883L_SAMPLES_8);

	// Set calibration offset. See HMC5883L_calibration.ino
  compass.setOffset(-40,-112,-71);
}

void compass_update()
{
	Vector norm = compass.readNormalize();
  // compass_compentation();

	// Calculate heading
	// float heading = atan2(norm.YAxis, norm.XAxis);
  // float heading = atan2(norm.ZAxis, norm.XAxis);
  float heading = atan2(-norm.XAxis, norm.ZAxis);

	float   declinationAngle = (0.0 + (41.0 / 60.0)) / (180 / M_PI);
	heading += declinationAngle;

	// Correct for heading < 0deg and heading > 360deg
	if (heading < 0) { heading += 2 * PI; }
	if (heading > 2 * PI) { heading -= 2 * PI; }

	// Convert to degrees
	headingDegrees = heading * 180 / M_PI;

  // Jika CH5 off atau yaw aktif → heading bebas
  if (ch5 == 0 || yaw_mapping < 1240 || yaw_mapping > 1260) {
    head = 0;
    setHeading = headingDegrees;
  }

  // Jika CH5 on dan yaw netral → kunci heading
  if (ch5 == 1 && yaw_mapping >= 1240 && yaw_mapping <= 1260 && head == 0) {
    setHeading = headingDegrees;
    head = 1;
  }

  heading_reference = headingDegrees - setHeading;
  if(heading_reference >   180) { heading_reference -= 360;}
  if(heading_reference < - 180) { heading_reference += 360;}
}

// void compass_compentation()
// {
//  Vector norm = compass.readNormalize();
//  acc_x = ax*2.0 / 32768.0;
//  acc_y = ay*2.0 / 32768.0;

//  acc_x = constrain(acc_x, -1, 1);
//  acc_y = constrain(acc_y, -1, 1);

//  compensatePitch = asin(acc_x);
//  compensateRoll  = asin(-acc_y);

//  cosComRoll  = cos(compensateRoll);
//  sinComRoll  = sin(compensateRoll);
//  cosComPitch = cos(compensatePitch);
//  sinComPitch = sin(compensatePitch);

//  Yh = norm.YAxis*cosComRoll + norm.ZAxis*sinComRoll;
//  Xh = norm.XAxis*cosComPitch - norm.YAxis*sinComRoll*sinComPitch - norm.ZAxis*cosComRoll*sinComPitch;
//  Yh = norm.YAxis*cosComRoll + norm.ZAxis*sinComRoll;
//  Xh = norm.XAxis*cosComPitch + norm.YAxis*sinComRoll*sinComPitch - norm.ZAxis*cosComRoll*sinComPitch;
// }





// void compass_init()
// {
//   // Inisialisasi HMC5883L
//   // while (!compass.begin()) {
//   //   Serial.println("Could not find a valid HMC5883L sensor, check wiring!");
//   //   delay(500);
//   // }

//   compass.setRange(HMC5883L_RANGE_1_3GA);
//   compass.setMeasurementMode(HMC5883L_CONTINOUS);
//   compass.setDataRate(HMC5883L_DATARATE_30HZ);
//   compass.setSamples(HMC5883L_SAMPLES_8);

//   // Set hasil kalibrasi offset sesuai hasil manual kalibrasi kamu
//   compass.setOffset(-40, -112, -71);
//     // compass.setOffset(-75,-52,-104);
// }


// void compass_update()
// {
//   Vector norm = compass.readNormalize();  // Baca kompas (sudah dikalibrasi & dinormalisasi)

//   // Data akselerometer dari MPU6050 (raw) → dikonversi ke satuan 'g'
//   float acc_xg = ax * 2.0 / 32768.0;   // X = kanan
//   float acc_yg = ay * 2.0 / 32768.0;   // Y = atas

//   acc_xg = constrain(acc_xg, -1.0, 1.0);
//   acc_yg = constrain(acc_yg, -1.0, 1.0);

//   // Hitung pitch dan roll (radian)
//   float pitch = asin(acc_xg);        // sensor tegak → X = pitch
//   float roll  = asin(-acc_yg);       // sensor tegak → Y = roll

//   // Pre-hitung trigonometri
//   float cosPitch = cos(pitch);
//   float sinPitch = sin(pitch);
//   float cosRoll  = cos(roll);
//   float sinRoll  = sin(roll);

//   // ======= TILT COMPENSATION UNTUK SENSOR BERDIRI (Z = depan) =======
//   float Xh = norm.XAxis * cosPitch
//            + norm.YAxis * sinRoll * sinPitch
//            - norm.ZAxis * cosRoll * sinPitch;

//   float Zh = norm.ZAxis * cosRoll
//            + norm.YAxis * sinRoll;

//   // Heading dihitung dari X-Z (karena kompas berdiri)
//   float heading = atan2(-Xh, Zh);  // -Xh agar CW = positif
//   // ===============================================================

//   // Tambah deklinasi Yogyakarta ≈ +0°41′
//   float declination = (0.0 + 41.0 / 60.0) * (PI / 180.0);
//   heading += declination;

//   // Normalisasi ke [0, 2π]
//   if (heading < 0) heading += 2 * PI;
//   if (heading > 2 * PI) heading -= 2 * PI;

//   // Ubah ke derajat
//   headingDegrees = heading * 180.0 / PI;

//   // Hitung selisih heading
//   heading_reference = setHeading - headingDegrees;
//   if (heading_reference > 180.0)  heading_reference -= 360.0;
//   if (heading_reference < -180.0) heading_reference += 360.0;
// }
