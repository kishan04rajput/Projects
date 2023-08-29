// include the library code:

#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

//----------------- store the custom characters in arrays ---------------------//

byte smile[8] =

{

  0b00000,

  0b00000,

  0b01010,

  0b00000,

  0b10001,

  0b01110,

  0b00000,

  0b00000

};

byte cry[8] =

{

  0b00000,

  0b00000,

  0b01010,

  0b01010,

  0b00000,

  0b00000,

  0b01110,

  0b10001

};

//----------------- store the custom characters in arrays ---------------------//

// give the LED pin a name:

int led = 6;

int i = 0;

void setup()

{

  //---- create custom characters ----//

  lcd.createChar(1, smile);

  lcd.createChar(2, cry);

  //---- create custom characters ----//

  // initialize the led pin as an output.

  pinMode(led, OUTPUT);

  // set up the lcd's number of columns and rows:

  lcd.begin(16, 2);

  lcd.print("CHIKI CHIKI CHU");

  delay(2000);

}

void loop()

{

  lcd.setCursor(0, 1);

  for (i = 0; i < 16; i ++)

    lcd.write(1);

  //---- blink LED -----//

  digitalWrite(led, HIGH);

  delay(500);

  digitalWrite(led, LOW);

  delay(200);

  //---- blink LED -----//

  lcd.setCursor(0, 1);

  for (i = 0; i < 16; i ++)

    lcd.write(2);

  //---- blink LED -----//

  digitalWrite(led, HIGH);

  delay(500);

  digitalWrite(led, LOW);

  delay(200);

  //---- blink LED -----//

}
