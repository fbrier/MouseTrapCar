//www.elegoo.com
//2018.10.25

/*
  Stepper Motor Control - one revolution

  This program drives a unipolar or bipolar stepper motor.
  The motor is attached to digital pins 8 - 11 of the Arduino.


*/

#include <Stepper.h>
#include "IRremote.h"

#define IR_IN_PIN 16
#define DRIVE_ROT_INPUT_PIN 2

// Number of interrupts where all energy is used from the trap
#define K_MaxRotationInterruptCount 400  

// The amount of engergy to save for each turn around leg
#define K_ReserveEnergy 10



enum GearPositions
{
   UNKNOWN_GEAR,
   FORWARD_GEAR,
   REVERSE_GEAR,
   NEUTRAL_F_GEAR,
   NEUTRAL_R_GEAR,
   BRAKE_GEAR
};
String gearStrings[6] = { "UnK-Gear", "F-Gear", "R-Gear", "NF_Gear", "NR_Gear", "Brake" };

const int K_StepsPerRevolution = 2048;  // change this to fit the number of steps per revolution
const int K_RolePerMinute = 15;         // Adjustable range of 28BYJ-48 stepper is 0~17 rpm
unsigned int stopTicks = 0;
unsigned int driveLegs = 0;
unsigned int curDriveLeg = 0;
unsigned int numTicks = 0;

// initialize the stepper library on pins 8 through 11:
Stepper myStepper(K_StepsPerRevolution, 8, 10, 9, 11);
IRrecv irecv(IR_IN_PIN);
decode_results results;

//===================================================
//===================================================
void RecalcStopPoint()
{
   stopTicks = (K_MaxRotationInterruptCount / driveLegs) - K_ReserveEnergy; 
}

//===================================================
//===================================================
void DriveTickInterrupt(void)
{
   // If we are at the stop point
   if (numTicks > stopPoint)
   {
      // When going forward, move to the forward neutral position
      if (curDriveLeg % 2)
         ChangeGear(NEUTRAL_F_GEAR);
      else
         ChangeGear(NEUTRAL_R_GEAR);
   }
   
   static bool ledState = false;
   if (ledState)
      digitalWrite(LED_BUILTIN, LOW);
   else
      digitalWrite(LED_BUILTIN, HIGH);

   ledState = !ledState;
}

//===================================================
//===================================================
void setup() {
  myStepper.setSpeed(K_RolePerMinute);
  pinMode(DRIVE_ROT_INPUT_PIN, INPUT);

  attachInterrupt(0, DriveTickInterrupt, RISING);
  
  // initialize the serial port:
  Serial.begin(9600);

  pinMode(LED_BUILTIN, OUTPUT);
  irrecv.enableIRIn();
}

//===================================================
//===================================================
void loop() 
{  
   if (irrecv.decode(&results))
   {
      translateIR();
      irrecv.resume();  
   }

   /*
    // step one revolution  in one direction:
  static int runNumber = 0;
  
  if (runNumber == 0)
  {
  Serial.println("\r\n\r\n\r\nclockwise");
   
   ChangeGear(FORWARD_GEAR);
   delay(1000);
   ChangeGear(NEUTRAL_F_GEAR);
   delay(1000);
   ChangeGear(FORWARD_GEAR);
   delay(1000);
   ChangeGear(BRAKE_GEAR);   
   delay(1000);
   ChangeGear(NEUTRAL_F_GEAR);   
   delay(1000);
   ChangeGear(REVERSE_GEAR);   
   delay(1000);
   ChangeGear(NEUTRAL_R_GEAR);   
   delay(1000);
   ChangeGear(FORWARD_GEAR);   
   delay(1000);
  }
   delay(1000);
  runNumber++;
  */
  
  // myStepper.step(stepsPerRevolution);
  // delay(250);

  // myStepper.step(0);
  // step one revolution in the other direction:
  // Serial.println("counterclockwise");
  // myStepper.step(-stepsPerRevolution);
  // delay(500);
/*
  digitalWrite(LED_BUILTIN, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(500);                       // wait for a second
  digitalWrite(LED_BUILTIN, LOW);    // turn the LED off by making the voltage LOW
  delay(100);
  */
  // wait for a second
}

