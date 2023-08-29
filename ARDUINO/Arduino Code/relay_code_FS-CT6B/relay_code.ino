//Receiver input to Arduino connection
int ch5 = 2, ch6 = 3;
//Arduino output pins
int r1 = 4, r2 = 5;
//Sensing variable
int r1v=0, r2v=0;
void setup() {
  // put your setup code here, to run once:
  //INPUT FROM RECEIVER
  pinMode(ch5, INPUT);
  pinMode(ch6, INPUT);
  //Relay Output
  pinMode(r1, OUTPUT);
  pinMode(r2, OUTPUT);
  //SERIAL COMMUNICATION STARTS
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  r1v = map(pulseIn(ch5, HIGH), 1100, 1800, 0, 255);
  r2v = map(pulseIn(ch6, HIGH), 1100, 1800, 0, 255);
  //RELAY 1 OUTPUT
  if (r1v <= 50)
  {
    digitalWrite(r1, LOW);
    Serial.print("Relay 1 is OFF \n");
  }
  else if (r1v >= 200)
  {
    digitalWrite(r1, HIGH);
    Serial.print("Relay 1 is ON \n");
  }
  //RELAY 2 OUTPUT
  if (r2v <= 50)
  {
    digitalWrite(r2, LOW);
    Serial.print("Relay 2 is OFF \n");
  }
  else if (r2v >= 200)
  {
    digitalWrite(r2, HIGH);
    Serial.print("Relay 2 is ON \n");
  }
  delay(100);
}
