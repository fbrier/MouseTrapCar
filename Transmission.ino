
// extern enum GearPositions;


// NF - Neutral
// F - Forward
// R - Reverse
// B - Break
// FROM_TO
#define NF_F -1000
#define F_B -150
#define B_R -250
#define R_NR -1000
#define NR_R +1000
#define R_B +150
#define B_F +250
#define F_NF +1000
extern String gearStrings[];

//########################################
// Go to Forward FROM curGear
//########################################
int GoForward(int curGear)
{
   int numSteps = 0;
   
   switch (curGear)
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
int GoReverse(int curGear)
{
   int numSteps = 0;
   
   switch (curGear)
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
int GoNeutral(int curGear)
{
   int numSteps = 0;
   
   switch (curGear)
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
int GoBrake(int curGear)
{
   int numSteps = 0;
   
   switch (curGear)
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

// We will force the tranny into a Neutral Forward Position
int InitTransmission()
{
   int numSteps = NR_R + R_B + B_F + F_NF;

   Serial.print("Init: ");
   Serial.println(numSteps);   
   return numSteps;
}

void ChangeGear(int requestedGear)
{
   String myStr = "ABC";
   static int currentGear = UNKNOWN_GEAR;
   int steps2move = 0;

   String cGear = gearStrings[currentGear];
   String rGear = gearStrings[requestedGear];
   
   Serial.print("Current Gear: ");
   Serial.println(cGear);
   Serial.print("Requested Gear: ");
   Serial.println(rGear);
   
   switch (requestedGear)
   {
      case FORWARD_GEAR:
      steps2move = GoForward(currentGear);
      break;
      
      case REVERSE_GEAR:
      steps2move = GoReverse(currentGear);
      break;
      
      case NEUTRAL_F_GEAR:
      case NEUTRAL_R_GEAR:
      steps2move = GoNeutral(currentGear);
      break;
      
      case BRAKE_GEAR:
      steps2move = GoBrake(currentGear);
      break;
      
      case UNKNOWN_GEAR:
      steps2move = InitTransmission();
      break;
   }  

   if (requestedGear != UNKNOWN_GEAR)
   {
      currentGear = requestedGear;
   }
   else
   {
      currentGear = NEUTRAL_F_GEAR;
   }
      
   Serial.println(steps2move);
   myStepper.step(steps2move);
   delay(500);
}

