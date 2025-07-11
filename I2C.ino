// const uint16_t I2C_TIMEOUT = 1000; // Used to check for errors in I2C communication

uint8_t i2cWrite(uint8_t Address, uint8_t registerAddress, uint8_t data, bool sendStop) {
	return i2cWrite(Address, registerAddress, &data, 1, sendStop); // Returns 0 on success
}

uint8_t i2cWrite(uint8_t Address, uint8_t registerAddress, uint8_t *data, uint8_t length, bool sendStop) {
	Wire.beginTransmission(Address);
	Wire.write(registerAddress);
	Wire.write(data, length);
	uint8_t rcode = Wire.endTransmission(sendStop); // Returns 0 on success
	if (rcode) {
		Serial.print(F("i2cWrite failed: "));
		Serial.println(rcode);
	}
	return rcode; // See: http://arduino.cc/en/Reference/WireEndTransmission
}

uint8_t i2cRead(uint8_t Address, uint8_t registerAddress, uint8_t *data, uint8_t nbytes) {
	uint32_t timeOutTimer;
	Wire.beginTransmission(Address);
	Wire.write(registerAddress);
	uint8_t rcode = Wire.endTransmission(false); // Don't release the bus
	if (rcode) {
		Serial.print(F("i2cRead failed: "));
		Serial.println(rcode);
		return rcode; // See: http://arduino.cc/en/Reference/WireEndTransmission
	}
	Wire.requestFrom(Address, nbytes, (uint8_t)true); // Send a repeated start and then release the bus after reading
	for (uint8_t i = 0; i < nbytes; i++) {
		if (Wire.available())
			data[i] = Wire.read();
		else {
			timeOutTimer = micros();
			while (((micros() - timeOutTimer) < I2C_TIMEOUT) && !Wire.available());
			if (Wire.available())
				data[i] = Wire.read();
			else {
				Serial.println(F("i2cRead timeout"));
				return 5; // This error value is not already taken by endTransmission
			}
		}
	}
	return 0; // Success
}
