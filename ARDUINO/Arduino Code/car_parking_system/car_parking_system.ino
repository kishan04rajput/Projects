//A[5] minute;       A[4] seconds
//CAR_PARKING_SYSTEM
#include<LiquidCrystal.h>
LiquidCrystal lcd(2, 3, 4, 5, 6, 7); //(rs, en, d4, d5, d6, d7);
int ir[4] = {A0, A1, A2, A3}, i, A[7] = {3};
void setup() {
  // put your setup code here, to run once:
  pinMode(ir[1], INPUT);
  pinMode(ir[2], INPUT);
  pinMode(ir[3], INPUT);
  pinMode(ir[0], INPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(2, 0);
  lcd.print("CAR PARKING");
  lcd.setCursor(5, 1);
  lcd.print("SYSTEM");
  while (A[0] > 0)
  {
    lcd.setCursor(15, 1);
    lcd.print(A[0]);
    A[0]--;
    delay(996);
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  /*A[0] = digitalRead(ir1);
    A[1] = digitalRead(ir2);
    A[2] = digitalRead(ir3);
    stateir4 = digitalRead(ir4);*/
  for (i = 0; i < 4; i++)
    A[i] = digitalRead(ir[i]);
  lcd.clear();
  digitalWrite(LED_BUILTIN, 0);
  if (A[0] == LOW && A[1] == LOW && A[2] == LOW && A[3]  == LOW)
    //if (((A[0]  && A[1] && A[2] && A[3]) == LOW) = 1)
    //if (A[0]  == A[1] == A[2] == A[3] == LOW)
    //if(A[0]==(A[1]==!(A[2]==!(A[3]==LOW))))
  {
    if (A[6] == 0)
    {
      A[6] = 1;
      A[5] = 0;
      A[4] = 0;
    }
    digitalWrite(LED_BUILTIN, 1);
    lcd.setCursor(2, 0);
    lcd.print("ALL OCCUPIED");
    CLOCK();
  }
  //else if (A[0] == HIGH && A[1] == HIGH && A[2] == HIGH && A[3] == HIGH)
  else if (A[0] && A[1]  && A[2]  && A[3])
    //else if(1)
  {
    if (A[6] == 1)
    {
      A[4] = 0;
      A[5] = 0;
      A[6] = 0;
    }
    lcd.setCursor(4, 0);
    lcd.print("ALL EMPTY");
    CLOCK();
  }
  else
  {
    A[4] = 0;
    A[5] = 0;
    lcd.setCursor(2, 0);
    lcd.print("EMPTY SLOTS");
    lcd.setCursor(6, 1);
    lcd.print("1234");
    if (A[0] == 0)
    {
      lcd.setCursor(6, 1);
      lcd.print(" ");
    }
    if (A[1] == LOW)
    {
      lcd.setCursor(7, 1);
      lcd.print(" ");
    }
    if (A[2] == LOW)
    {
      lcd.setCursor(8, 1);
      lcd.print(" ");
    }
    if (A[3] == LOW)
    {
      lcd.setCursor(9, 1);
      lcd.print(" ");
    }
  }
  delay(100);
}
void CLOCK()
{
  lcd.setCursor(13, 1);
  lcd.print(":");
  if (A[4] <= 9)
  {
    if (A[5] > 9 && A[5] <= 99)
      lcd.setCursor(11, 1);
    else
      lcd.setCursor(12, 1);
    lcd.print(A[5]);
    lcd.setCursor(13, 1);
    lcd.print(":0");
    lcd.setCursor(15, 1);
    lcd.print(A[4]);
    //A[4]=10;
  }
  else if (A[4] > 9)
  {
    if (A[5] > 9 && A[5] <= 99)
      lcd.setCursor(11, 1);
    else
      lcd.setCursor(12, 1);
    lcd.print(A[5]);
    lcd.setCursor(14, 1);
    //A[4] = 60;
    if (A[4] > 59)
    {
      if (A[5] > 9 && A[5] <= 99)
        lcd.setCursor(11, 1);
      else
        lcd.setCursor(12, 1);
      lcd.print(++A[5]);
      lcd.setCursor(13, 1);
      lcd.print(":0");
      A[4] = 0;
    }
  }
  else
  {
    lcd.setCursor(15, 1);
  }
  lcd.print(A[4]++);
  delay(950);
}
