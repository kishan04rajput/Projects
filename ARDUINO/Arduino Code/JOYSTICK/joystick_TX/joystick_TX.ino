int xAxis, yAxis;
void setup() {
  Serial.begin(9600); // Default communication rate of the Bluetooth module
}
void loop() {
  xAxis = analogRead(A0); // Read Joysticks X-axis
  yAxis = analogRead(A1); // Read Joysticks Y-axis
  
  // Send the values via the serial port to the slave HC-05 Bluetooth device
  Serial.print(xAxis/100); // Dividing by 4 for converting from 0 - 1023 to 0 - 256, (1 byte) range
  Serial.println(yAxis/100);
  delay(100);
}
