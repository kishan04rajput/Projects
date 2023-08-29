/* CONNECT  GREEN, YELLOW AND RED LIGHTS FROM 0 TO 8 PIN RESPECTIVELY....
    ULTRASONIC SENSOR
    CONNECT TRIGGER PIN TO 13 AND ECHO PIN TO 12 NUMBER PIN OF ARDUINO....
*/
const unsigned int TRIG_PIN = 13;
const unsigned int ECHO_PIN = 12;
const unsigned int BAUD_RATE = 9600;

void setup() {
  pinMode(TRIG_PIN, OUTPUT);
  pinMode(ECHO_PIN, INPUT);
  Serial.begin(BAUD_RATE);
}

void loop() {
  digitalWrite(TRIG_PIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG_PIN, LOW);


  const unsigned long duration = pulseIn(ECHO_PIN, HIGH);
  int distance = duration / 29 / 2;
  if (distance == 400) {
    digitalWrite(0, HIGH);
    if (distance == 360) {
      digitalWrite(1, HIGH);
      if (distance == 320) {
        digitalWrite(2, HIGH);
        if (distance == 280) {
          digitalWrite(3, HIGH);
          if (distance == 240) {
            digitalWrite(4, HIGH);
            if (distance == 200) {
              digitalWrite(5, HIGH);
              if (distance == 160) {
                digitalWrite(6, HIGH);
                if (distance == 120) {
                  digitalWrite(7, HIGH);
                  if (distance == 80) {
                    digitalWrite(8, HIGH);
                  }
                }
              }
            }
          }
        }
      }
    }
  }
  else {
    digitalWrite(0, LOW);
    digitalWrite(1, LOW);
    digitalWrite(2, LOW);
    digitalWrite(3, LOW);
    digitalWrite(4, LOW);
    digitalWrite(5, LOW);
    digitalWrite(6, LOW);
    digitalWrite(7, LOW);
    digitalWrite(8, LOW);
  }
  delay(100);
}
