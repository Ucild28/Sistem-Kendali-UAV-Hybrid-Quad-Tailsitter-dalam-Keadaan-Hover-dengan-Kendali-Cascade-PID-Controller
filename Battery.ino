void batterypercent() { // masukkan fungsi ini di loop
  adc   = analogRead(PC1);
  vin   = (adc * 5.0) / 1023.0;
  vout  = (vin / (7500.0 / (30000.0 + 7500.0)))-3.1;
  Serial.print(vout);
  Serial.print(" V");
  
  if(vout >=14.7){
    float percentage = fmap(vout, 14.7, 16.8, 0, 100);
    Serial.print("(");
    Serial.print(percentage);
    Serial.println(" %)");
  }
  else{Serial.println("(0.0%)");}
}

float fmap(float x, float in_min, float in_max, float out_min, float out_max) {
  return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}