/*
    fan pin = 11
    lm35 = A1
    pir sensor = 3
    fan on/off = reset
    automatic/manual = 2
    fan speed control = A7
*/
int sensor = 3;
int state = LOW;
int val = 0, k;
const int lm35_pin = A1;
int temp_adc_val, fan, fan_switch = 2, speedc = A7, fan_switchv, speedcv;
float temp_val;
void setup() {
  // put your setup code here, to run once:
  //  pinMode(led, OUTPUT);
  pinMode(sensor, INPUT);
  pinMode(3, INPUT);
  pinMode(A0, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(2, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(A7, INPUT);
  pinMode(2, INPUT);
  pinMode(speedc, INPUT);
  digitalWrite(A0, 1);
  digitalWrite(A2, 0);
  digitalWrite(2, 1);
  digitalWrite(4, 0);
  Serial.begin(9600);
}

void loop() {
  fan_switchv = digitalRead(2);
  if (fan_switchv == HIGH)
  {
    digitalWrite(LED_BUILTIN, 0);
    if (k == 0)
    {
      Serial.println("AUTOMATIC MODE");
      delay(1000);
      k = 1;
    }
    // put your main code here, to run repeatedly:
    val = digitalRead(sensor);
    if (val == HIGH) {
      //Serial.println("MOTION DETECTED");
      temp_adc_val = analogRead(lm35_pin);
      temp_val = (temp_adc_val * 5.09);
      temp_val = (temp_val / 10);
      //Serial.print("Temperature=");
      Serial.print("Degree Celsius=");
      Serial.print(temp_val);
      fan = map(temp_val, 25, 50, 0, 255);
      if (fan > 255)
        fan = 255;
      analogWrite(11, fan);
      fan = map(fan, 0, 255, 0, 100);
      Serial.print("\nFAN SPEED=");
      Serial.println(fan);
      delay(1);
    }
  }
  else {
    //Serial.println("MOTION STOPPED");
    // analogWrite(11, 0);
    digitalWrite(LED_BUILTIN, 1);
    if (k == 1)
    {
      Serial.println("MANUAL MODE");
      delay(1000);
      k = 0;
    }
    speedcv = analogRead(speedc);
    speedcv = map(speedcv, 0, 1023, 0, 255);
    analogWrite(11, speedcv);
    speedcv = map(speedcv, 0, 255, 0, 100);
    Serial.println(speedcv);
  }
  delay(1);
}
