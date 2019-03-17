
// extern enum GearPositions;



#include <WString.h>
#include <HardwareSerial.h>
#include <USBAPI.h>
#include "Transmission.h"

extern String gearStrings[];

// We will force the tranny into a Neutral Forward Position
Transmission::Transmission() : _stepper(K_StepsPerRevolution, 8, 10, 9, 11)
{
   _numSteps = NR_R + R_B + B_F + F_NF;
   _currentGear = UNKNOWN_GEAR;
   _stepper.setSpeed(K_RolePerMinute);
   pinMode(DRIVE_ROT_INPUT_PIN, INPUT);

   Serial.print("Init: ");
   Serial.println(_numSteps);
}

void Transmission::Init()
{

}
//########################################
// Go to Forward FROM curGear
//########################################
int Transmission::GoForward()
{
   int numSteps = 0;
   
   switch (_currentGear)
   {
      case REVERSE_GEAR:
      // We need to move through the brake to forward
         numSteps = R_B + B_F;
      break;
      
      case NEUTRAL_F_GEAR:
      // We need to move to forward
         numSteps = NF_F;
      break;
      
      case NEUTRAL_R_GEAR:
      // We need to move through the reverse, brake to forward
         numSteps = NR_R + R_B + B_F;
      break;

      case BRAKE_GEAR:
      // We need to move to the Forward position
         numSteps = B_F;
      break;
      
      case FORWARD_GEAR:  // FALL THROUGH
      default:
      numSteps = 0;
      break;
   }

   Serial.print("Forward: ");
   Serial.println(numSteps);
   
   return numSteps;
}

//########################################
// Go to Reverse FROM curGear
//########################################
int Transmission::GoReverse()
{
   int numSteps = 0;
   
   switch (_currentGear)
   {
      case FORWARD_GEAR:
      // We need to move through the brake to Reverse
      numSteps = F_B + B_R;
      break;
      
      case NEUTRAL_F_GEAR:
      // We need to move to forward, brake, reverse
      numSteps = NF_F + F_B + B_R;
      break;
      
      case NEUTRAL_R_GEAR:
      // We need to move to te reverse
      numSteps = NR_R;
      break;

      case BRAKE_GEAR:
      // We need to move to the brake position
      numSteps = B_R;
      break;
      
      case REVERSE_GEAR:  // FALL THROUGH
      default:
      numSteps = 0;
      break;
   }

   Serial.print("Reverse: ");
   Serial.println(numSteps);
   return numSteps;
}
//########################################
// Go to EITHER Neutral FROM curGear
//########################################
int Transmission::GoNeutral()
{
   int numSteps = 0;
   
   switch (_currentGear)
   {
      case FORWARD_GEAR:
      // We need to move to Neutral Forward
      numSteps = F_NF;
      break;
      
      case REVERSE_GEAR:
      // We need to move to Neutral Reverse
      numSteps = R_NR;
      break;

      case BRAKE_GEAR:
      // We need to move to the Neutral Forward position
      numSteps = B_F + F_NF;
      break;
      
      case NEUTRAL_R_GEAR:  // FALL THROUGH
      case NEUTRAL_F_GEAR:  // FALL THROUGH
      default:
      numSteps = 0;
      break;
   }
   
   Serial.print("neutral: ");
   Serial.println(numSteps);  
   return numSteps;
}

//########################################
// Go to Brake FROM curGear
//########################################
int Transmission::GoBrake()
{
   int numSteps = 0;
   
   switch (_currentGear)
   {
      case FORWARD_GEAR:
      // We need to move through the brake to Reverse
      numSteps = F_B;
      break;
      
      case REVERSE_GEAR:
      numSteps = R_B;
      break;
      
      case NEUTRAL_F_GEAR:
      // We need to move to forward, brake, reverse
      numSteps = NF_F + F_B ;
      break;
      
      case NEUTRAL_R_GEAR:
      // We need to move to te reverse
      numSteps = NR_R + R_B;
      break;

      case BRAKE_GEAR:  // FALL THROUGH
      default:
      numSteps = 0;
      break;
   }
   Serial.print("Break: ");
   Serial.println(numSteps);    
   return numSteps;
}


void Transmission::ChangeGear(int requestedGear)
{
   String myStr = "ABC";
   int steps2move = 0;

   String cGear = GEAR_NAMES[_currentGear];
   String rGear = GEAR_NAMES[requestedGear];
   
   Serial.print("Current Gear: ");
   Serial.println(cGear);
   Serial.print("Requested Gear: ");
   Serial.println(rGear);
   
   switch (requestedGear)
   {
      case FORWARD_GEAR:
         steps2move = GoForward();
      break;
      
      case REVERSE_GEAR:
         steps2move = GoReverse();
      break;
      
      case NEUTRAL_F_GEAR:
      case NEUTRAL_R_GEAR:
         steps2move = GoNeutral();
      break;
      
      case BRAKE_GEAR:
         steps2move = GoBrake();
      break;
      
      case UNKNOWN_GEAR:
         // ToDo: Put this in the constructor. Is UNKNOWN_GEAR a possibility at this point?
         //steps2move = Init();
      break;
   }  

   if (requestedGear != UNKNOWN_GEAR)
   {
      _currentGear = requestedGear;
   }
   else
   {
      _currentGear = NEUTRAL_F_GEAR;
   }
      
   Serial.println(steps2move);
   _stepper.step(steps2move);
   delay(500);
}

