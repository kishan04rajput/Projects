// include the library code:
#include <TimerOne.h>
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(12, 11, 6, 5, 4, 3);

//Enter here you data
const char pin_number[] = "****";        // Write the pin number of the SIM card

int onModulePin = 2;
char aux_string[30];
int8_t answer;
int flag = 0;

char frame[200];
char latitude[15];
char longitude[15];
char altitude[6];
char date[16];
char time[7];
char satellites[3];
char speedOTG[10];
char course[10];

unsigned int counter = 0;
int b1a = 6;  // L9110 B-1A
int b1b = 9;  // L9110 B-1B

int temp = 0, i;

void setup() {
   pinMode(b1a, OUTPUT);
  pinMode(b1b, OUTPUT);

  Timer1.initialize(1000000); // set timer for 1sec
  attachInterrupt(0, docount, RISING);  // increase counter when speed sensor pin goes High
  Timer1.attachInterrupt( timerIsr ); // enable the timer
  
  lcd.begin(16, 2); // set up the number of columns and rows on the LCD 

  pinMode(onModulePin, OUTPUT);
  Serial.begin(115200);

  Serial.println("Starting...");// Print a message to serial monitor
  lcd.print("Starting...");      // Print a message to the LCD.
  power_on();    // Powering the module

  delay(5000);

  //sets the PIN code
  sprintf(aux_string, "AT+CPIN=%s", pin_number);
  sendATcommand(aux_string, "OK", 2000);

  delay(3000);

  Serial.println("Connecting to the network...");
  lcd.setCursor(0, 0);
  lcd.print("Connecting to ");
  lcd.setCursor(0, 1); // set the cursor to column 0, line 1
  lcd.print("the network   "); // print to the second line

  //Check network registration
  while ( (sendATcommand("AT+CREG?", "+CREG: 0,1", 1000) ||
    sendATcommand("AT+CREG?", "+CREG: 0,5", 1000)) == 0 );

  sendATcommand("AT+CLIP=1", "OK", 1000);

  while ( start_GPS() == 0);

  Serial.println("Connected to the network!!");
  lcd.clear(); // clear the LCD
  lcd.setCursor(0, 0); // set the cursor to column 0, line 0
  lcd.print("Connected to  ");
  lcd.setCursor(0, 1);
  // print to the second line
  lcd.print("the network!  ");
  
  delay(1000);

  while (Serial.available() != 0)
  {
    Serial.read();
  }
}

void loop() {
  
  serialEvent();
  if (temp)
  {
    tracking();
  }
    
  get_GPS();
  delay(500);

  Serial.print("Latitude: ");
  Serial.print(latitude);
  Serial.print(" / Longitude: ");
  Serial.println(longitude);

  lcd.setCursor(0, 0); 
  lcd.print("Lat:");
  lcd.setCursor(4, 0); 
  lcd.print(latitude);

  lcd.setCursor(0, 1);
  lcd.print("Lon:");
  lcd.setCursor(4, 1);
  lcd.print(longitude); 
  
  delay(1000);
}


/************************************************************************
 ****               Definition of functions                          ****
 ************************************************************************/

void lcd_status()
{
  lcd.clear();
  lcd.print("Message Sent");
  delay(2000);
  lcd.clear();
  lcd.print("System Ready");
  return;
}

void send_sms()
{
  Serial.write(26);
}


void send_data(String message)
{
  Serial.println(message);
  delay(200);
}


void init_sms()
{
  Serial.println("AT+CMGF=1");
  delay(400);
  Serial.println("AT+CMGS=\"+919723327896\"");   //your 10 digit cell no. here
  delay(400);
}


void ssprintf() {
  //float lo = .toFloat();
  //float la = .toFloat();
  sprintf("https://www.google.co.in/maps/@%f,%f,14z", longitude,latitude );
}

void docount()  // counts from the speed sensor
{
  counter++;  // increase +1 the counter value
}

void timerIsr()
{
  Timer1.detachInterrupt();  //stop the timer
  Serial.print("BUS Speed: ");
  int rotation = (counter / 20);  // divide by number of holes in Disc
  Serial.print(rotation, DEC);
  //Serial.println(" Rotation per seconds");
  counter = 0; //  reset counter to zero
  Timer1.attachInterrupt( timerIsr );  //enable the timer
}

void tracking()
{
  //coordinate2dec();
  convert2Degrees(latitude);
  convert2Degrees(longitude);
  init_sms();
  send_data("Vehicle Tracking Alert:");
  send_data("Your Vehicle Current Location is:");
  Serial.print("Latitude:");
  send_data(latitude);
  Serial.print("Longitude:");
  send_data(longitude);
  send_data("CAMERA: USERNAME:xxxxx\n PASSWORD:xxxxx");
  //send_data("https://www.google.co.in/maps/@'longitude','latitude',14z");
  send_data("ssprintf();");
  send_data("timerIsr();");
  send_sms();
  delay(2000);
  lcd_status();
}

void serialEvent()
{
  while (Serial.available())
  {
    if (Serial.find("Track Vehicle"))
    {
      temp = 1;
      break;
    }
    else
      temp = 0;
  }
}

void power_on() {

  uint8_t answer = 0;

  // checks if the module is started
  answer = sendATcommand("AT", "OK", 2000);
  if (answer == 0)
  {
    // power on pulse
    digitalWrite(onModulePin, HIGH);
    delay(3000);
    digitalWrite(onModulePin, LOW);

    // waits for an answer from the module
    while (answer == 0) {   // Send AT every two seconds and wait for the answer
      answer = sendATcommand("AT", "OK", 2000);
    }
  }

}


int8_t sendATcommand(char* ATcommand, char* expected_answer, unsigned int timeout) {

  uint8_t x = 0,  answer = 0;
  char response[100];
  unsigned long previous;

  memset(response, '\0', 100);    // Initialice the string

  delay(100);

  while ( Serial.available() > 0) Serial.read();   // Clean the input buffer

  if (ATcommand[0] != '\0')
  {
    Serial.println(ATcommand);    // Send the AT command
  }


  x = 0;
  previous = millis();

  // this loop waits for the answer
  do {
    if (Serial.available() != 0) {  // if there are data in the UART input buffer, reads it and checks for the asnwer
      response[x] = Serial.read();
      //Serial.print(response[x]);
      x++;
      if (strstr(response, expected_answer) != NULL)    // check if the desired answer (OK) is in the response of the module
      {
        answer = 1;
      }
    }
  } 
  while ((answer == 0) && ((millis() - previous) < timeout));   // Waits for the asnwer with time out

    return answer;
}



int8_t start_GPS() {

  unsigned long previous;

  previous = millis();
  // starts the GPS
  sendATcommand("AT+CGPSPWR=1", "OK", 2000);
  sendATcommand("AT+CGPSRST=0", "OK", 2000);

  // waits for fix GPS
  while (( (sendATcommand("AT+CGPSSTATUS?", "2D Fix", 5000) ||
    sendATcommand("AT+CGPSSTATUS?", "3D Fix", 5000)) == 0 ) &&
    ((millis() - previous) < 90000));

  if ((millis() - previous) < 90000)
  {
    return 1;
  }
  else
  {
    return 0;
  }
}

int8_t get_GPS() {

  int8_t counter, answer;
  long previous;

  // First get the NMEA string
  // Clean the input buffer
  while ( Serial.available() > 0) Serial.read();
  // request Basic string
  sendATcommand("AT+CGPSINF=0", "AT+CGPSINF=0\r\n\r\n", 2000);

  counter = 0;
  answer = 0;
  memset(frame, '\0', 100);    // Initialize the string
  previous = millis();
  // this loop waits for the NMEA string
  do {

    if (Serial.available() != 0) {
      frame[counter] = Serial.read();
      counter++;
      // check if the desired answer is in the response of the module
      if (strstr(frame, "OK") != NULL)
      {
        answer = 1;
      }
    }
    // Waits for the asnwer with time out
  }
  while ((answer == 0) && ((millis() - previous) < 2000));

  frame[counter - 3] = '\0';

  // Parses the string
  strtok(frame, ",");
  strcpy(longitude, strtok(NULL, ",")); // Gets longitude
  strcpy(latitude, strtok(NULL, ",")); // Gets latitude
  strcpy(altitude, strtok(NULL, ".")); // Gets altitude
  strtok(NULL, ",");
  strcpy(date, strtok(NULL, ".")); // Gets date
  strtok(NULL, ",");
  strtok(NULL, ",");
  strcpy(satellites, strtok(NULL, ",")); // Gets satellites
  strcpy(speedOTG, strtok(NULL, ",")); // Gets speed over ground. Unit is knots.
  strcpy(course, strtok(NULL, "\r")); // Gets course

  convert2Degrees(latitude);
  convert2Degrees(longitude);

  return answer;
}




/* convert2Degrees ( input ) - performs the conversion from input
 * parameters in  DD°MM.mmm’ notation to DD.dddddd° notation.
 *
 * Sign '+' is set for positive latitudes/longitudes (North, East)
 * Sign '-' is set for negative latitudes/longitudes (South, West)
 *
 */
int8_t convert2Degrees(char* input) {

  float deg;
  float minutes;
  boolean neg = false;

  //auxiliar variable
  char aux[10];

  if (input[0] == '-')
  {
    neg = true;
    strcpy(aux, strtok(input + 1, "."));

  }
  else
  {
    strcpy(aux, strtok(input, "."));
  }

  // convert string to integer and add it to final float variable
  deg = atof(aux);

  strcpy(aux, strtok(NULL, '\0'));
  minutes = atof(aux);
  minutes /= 1000000;
  if (deg < 100)
  {
    minutes += deg;
    deg = 0;
  }
  else
  {
    minutes += int(deg) % 100;
    deg = int(deg) / 100;
  }

  // add minutes to degrees
  deg = deg + minutes / 60;


  if (neg == true)
  {
    deg *= -1.0;
  }

  neg = false;

  if ( deg < 0 ) {
    neg = true;
    deg *= -1;
  }

  float numeroFloat = deg;
  int parteEntera[10];
  int cifra;
  long numero = (long)numeroFloat;
  int size = 0;

  while (1) {
    size = size + 1;
    cifra = numero % 10;
    numero = numero / 10;
    parteEntera[size - 1] = cifra;
    if (numero == 0) {
      break;
    }
  }

  int indice = 0;
  if ( neg ) {
    indice++;
    input[0] = '-';
  }
  for (int i = size - 1; i >= 0; i--)
  {
    input[indice] = parteEntera[i] + '0';
    indice++;
  }

  input[indice] = '.';
  indice++;

  numeroFloat = (numeroFloat - (int)numeroFloat);
  for (int i = 1; i <= 6 ; i++)
  {
    numeroFloat = numeroFloat * 10;
    cifra = (long)numeroFloat;
    numeroFloat = numeroFloat - cifra;
    input[indice] = char(cifra) + 48;
    indice++;
  }
  input[indice] = '\0';
}
