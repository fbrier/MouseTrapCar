

//===================================================
//===================================================
void OnBtnUpArrow()
{
   Serial.println("OnBtnUpArrow");
   driveLegs++;  
   RecalcStopPoint();
}

//===================================================
//===================================================
void OnBtnDownArrow()
{
   if (driveLegs != 0)
   {
      driveLegs--; 
      RecalcStopPoint();
   }
}

//===================================================
//===================================================
void OnBtnForward()
{
   curDriveLeg++;
   numTicks = 0;
   ChangeGear(FORWARD_GEAR);
}

//===================================================
//===================================================
void OnBtnReverse()
{
   curDriveLeg++;
   numTicks = 0;
   ChangeGear(REVERSE_GEAR);   
}

//===================================================
//===================================================
void OnBtnPlay_Pause()
{
   ChangeGear(BRAKE_GEAR);    
}

//===================================================
//===================================================
void OnBtnPowerOn_Off()
{
  ChangeGear(UNKNOWN_GEAR);   
}

//===================================================
//===================================================
void translateIR()
{
   switch (results.value)
   {
      
      case 0xff22dd:  Serial.println("Back"); break;
      case 0xffc23d:  Serial.println("Forward"); break;
      
      case 0xff6897:  Serial.println("0"); break;
      case 0xff9867:  Serial.println("eq"); break;
      case 0xffb04f:  Serial.println("step"); break;
      case 0xff30cf:  Serial.println("1"); break;
      case 0xff18e7:  Serial.println("2"); break;
      case 0xff7a85:  Serial.println("3"); break;
      case 0xff10ef:  Serial.println("4"); break;
      case 0xff38c7:  Serial.println("5"); break;
      case 0xff5aa5:  Serial.println("6"); break;
      case 0xff42bd:  Serial.println("7"); break;
      case 0xff4ab5:  Serial.println("8"); break;
      case 0xff52ad:  Serial.println("9"); break;
      case 0xffffffff:  Serial.println("Repeat"); break;
      case 0xFFE21D: Serial.println("Function"); break;

      case 0xFFA25D:  Serial.println("PowerOn\Off"); OnBtnPowerOn_Off(); break; 
      case 0xff629d:  Serial.println("Vol+"); OnBtnForward(); break;        
      case 0xffa857:  Serial.println("Vol-"); OnBtnReverse(); break;                 
      case 0xFF02FD: Serial.println("Play\\Pause"); OnBtnPlay_Pause(); break;
      case 0xFFE01F: Serial.println("Down"); OnBtnDownArrow(); break;
      case 0xFF906F: Serial.println("Up"); OnBtnUpArrow(); break;

      default:
      Serial.print("Value not listed : 0x");
      Serial.println(results.value, HEX);
      
   }
   delay(500); // Stop from getting an immediate repeat
}
