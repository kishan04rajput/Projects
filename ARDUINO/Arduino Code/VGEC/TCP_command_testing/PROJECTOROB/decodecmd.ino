void decodecmd(String Rdata)
{
  

  if (Rdata.substring(12, 14) == "SS")
  {
 Serial.println(" distance of nearest obstacle is uploded to the server");
  }
  else if (Rdata.substring(12, 14) == "SR")
  {
    String newtim = Rdata.substring(14, 24);// set RTC by current time
    long inttime = newtim.toInt();
    RTC.adjust(DateTime(inttime));

    Serial.println("rtc set ok=" + newtim);
  }
  else if ((Rdata.substring(13, 15) == "SS") || (Rdata.substring(13, 15) == "SH") )
  {

    int point = Rdata.indexOf("I");

    String  sindex = Rdata.substring(point + 1);

    long iindex = sindex.toInt();


  }
 else if (Rdata.substring(12, 14) == "SX")
  
    {
      Serial.println("ALL STOP AT ONCE");
        analogWrite(D0, 0);
         analogWrite(D1, 0);
          analogWrite(D2, 0);
           analogWrite(D3, 0);
      client.print(Rdata.substring(0, 12) + "DX)");
    }
    
  else if (Rdata.substring(12, 14) == "SF")

    {
      analogWrite(D1, 1);
      Serial.println("FORWARD START");
      delay(5000);
      analogWrite(D1,0);
      client.print(Rdata.substring(0, 12) + "DF)");
      }
  
  
  else if (Rdata.substring(12, 14) == "SB")

    {
      Serial.println("REVERSE ON");
        analogWrite(D2, 1);
           delay(5000);
      analogWrite(D2,0);
      client.print(Rdata.substring(0, 12) + "DB)");
         
    }

   
  
  else if (Rdata.substring(12, 14) == "SD")
 
    {
      Serial.println("LEFT ON");
        analogWrite(D3, 0);
           delay(5000);
      analogWrite(D3,0);
      client.print(Rdata.substring(0, 12) + "DD)");
    }

  
else if (Rdata.substring(12, 14) == "SJ")
  
    {
      Serial.println("RIGHT ON");
        analogWrite(D4, 0);
           delay(5000);
      analogWrite(D4,0);
      client.print(Rdata.substring(0, 12) + "Dw0)");
    

  
 

   

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
