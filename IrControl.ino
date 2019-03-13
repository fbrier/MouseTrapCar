

//===================================================
//===================================================
void OnBtnUpArrow()
{
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
      
      case 0xff22dd:  Serial.println("LEFT"); break;
      case 0xff02df:  Serial.println("-OK-"); break;
      case 0xffc23d:  Serial.println("Right"); break;
      
      case 0xff6897:  Serial.println("1"); break;
      case 0xff9867:  Serial.println("2"); break;
      case 0xffb04f:  Serial.println("3"); break;
      case 0xff30cf:  Serial.println("4"); break;
      case 0xff18e7:  Serial.println("5"); break;
      case 0xff7a85:  Serial.println("6"); break;
      case 0xff10ef:  Serial.println("7"); break;
      case 0xff38c7:  Serial.println("8"); break;
      case 0xff42bd:  Serial.println("9"); break;
      case 0xff4ab5:  Serial.println("0"); break;
      case 0xff52ad:  Serial.println("????"); break;
      case 0xffFFFF:  Serial.println("Repeat"); break;

      case 0xff0001:  Serial.println("PowerOn\Off"); break;    //OnBtnPowerOn_Off()
      case 0xff0002:  Serial.println("Button Up"); break;      //OnBtnUpArrow()
      case 0xff0003:  Serial.println("Button Down"); break;    //OnBtnDownArrow()
      case 0xff629d:  Serial.println("Forward"); break;        //OnBtnForward()
      case 0xffa857:  Serial.println("Reverse"); break;        //OnBtnReverse()
      case 0xff0004:  Serial.println("Pause"); break;          // OnBtnPlay_Pause()

      
      default:
      Serial.print("Value not listed : 0x");
      Serial.println(results.value);
      
   }
   delay(500); // Stop from getting an immediate repeat
}
