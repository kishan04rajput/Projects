void decodecmd(String Rdata)
{
  if (Rdata.substring(12, 14) == "SS")
  {

   produc=0;
    c_index++;

  }
  else if (Rdata.substring(12, 14) == "SR")
  {
    String newtime = Rdata.substring(14, 24);// set RTC by current time
    long inttime = newtime.toInt();
    RTC.adjust(DateTime(inttime));

    Serial.println("rtc set ok=" + newtime);
  }
  else if ((Rdata.substring(13, 15) == "SS") || (Rdata.substring(13, 15) == "SH") )
  {

    int point = Rdata.indexOf("I");

    String  sindex = Rdata.substring(point + 1);

    long iindex = sindex.toInt();


  }
  else if (Rdata.substring(12, 14) == "SP")
  {
    if (Rdata.substring(14) == "0")
    {
      digitalWrite(D0, 1);
      Serial.println("Power OFF");
      lcd.print("POWER OFF");
      delay(5000);
      lcd.clear();
      client.print(Rdata.substring(0, 12) + "DP0)");
  


    }

    if (Rdata.substring(14) == "1")
    {
      digitalWrite(D0, 0);
      Serial.println("Power ON");
      lcd.print("POWER ON");
       delay(5000);
      lcd.clear();
      client.print(Rdata.substring(0, 12) + "DP1)");
 
    }


  }
  else if (Rdata.substring(12, 14) == "SM")
  {

    if (Rdata.substring(14) == "0")
    {
      Serial.println("MOTOR 1 OFF");
      client.print(Rdata.substring(0, 12) + "DM0)");
         
    }

    if (Rdata.substring(14) == "1")
    {
      Serial.println("MOTOR 1 ON");
      client.print(Rdata.substring(0, 12) + "DM1)");
      Serial.print(Rdata.substring(0, 12) + "DM1)");
         
      
    }
  }
  else if (Rdata.substring(12, 14) == "SN")
  {

    if (Rdata.substring(14) == "0")
    {
      Serial.println("MOTOR 2 OFF");
      client.print(Rdata.substring(0, 12) + "DN0)");
    }

    if (Rdata.substring(14) == "1")
    {
      Serial.println("MOTOR 2 ON");
      client.print(Rdata.substring(0, 12) + "DN1)");
    }

  }
  else if (Rdata.substring(12, 14) == "SA")
  {
    String RPM = Rdata.substring(14);
    Serial.println("Set RPM=" + RPM);
    client.print(Rdata.substring(0, 12) + "DA" + RPM + ")");
    p_index = c_index;
    
   
  }
  else if (Rdata.substring(12, 14) == "ST")
  {
    String temp = Rdata.substring(14);
    Serial.println("Set temperature=" + temp);
    client.print(Rdata.substring(0, 12) + "DT" + temp + ")");

  }
  else if (Rdata.substring(12, 14) == "SL")
  {

    String level = Rdata.substring(14);
    Serial.println("Set level=" + level);

    client.print(Rdata.substring(0, 12) + "DL" + level + ")");

  }

else if (Rdata.substring(12, 14) == "SX")
  
    {
      Serial.println("ALL STOP AT ONCE");
        digitalWrite(D3, 0);
         digitalWrite(D4, 0);
          digitalWrite(D5, 0);
           digitalWrite(D6, 0);
      client.print(Rdata.substring(0, 12) + "DX)");
    }
    
  else if (Rdata.substring(12, 14) == "SF")

    { 
      if(inches>7)
      {
        
      
      digitalWrite(D3, 1);
       digitalWrite(D4, 0);
      Serial.println("FORWARD START");
    
      client.print(Rdata.substring(0, 12) + "DF)");
      }
      }
  
  
  else if (Rdata.substring(12, 14) == "SB")

    {
      Serial.println("REVERSE ON");
        digitalWrite(D4, 1);
         digitalWrite(D3, 0);
           delay(5000);
      digitalWrite(D4,0);
       digitalWrite(D3, 0);
      client.print(Rdata.substring(0, 12) + "DB)");
         
    }

   
  
  else if (Rdata.substring(12, 14) == "SD")
 
    {
      Serial.println("LEFT ON");
        digitalWrite(D5, 1);
        digitalWrite(D6, 0);
           delay(5000);
      digitalWrite(D5,0);
      digitalWrite(D6, 0);
      client.print(Rdata.substring(0, 12) + "DD)");
    }

  
else if (Rdata.substring(12, 14) == "SJ")
  
    {
      Serial.println("RIGHT ON");
        digitalWrite(D6, 1);
        digitalWrite(D5, 0);
           delay(5000);
      digitalWrite(D6,0);
      digitalWrite(D5, 0);
      client.print(Rdata.substring(0, 12) + "DJ)");
     }
}
