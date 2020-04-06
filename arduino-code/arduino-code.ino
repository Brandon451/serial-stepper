#include "AccelStepper.h"
#include "MultiStepper.h"

#define s1d 4
#define s1e 5
#define s1p 6

#define s2d 7
#define s2e 8
#define s2p 9

unsigned long time1 = 0;
unsigned long diff = 0;

const byte buffSize = 40;
char inputBuffer[buffSize];
const char startMarker = '<';
const char endMarker = '>';
byte bytesRecvd = 0;
boolean readInProgress = false;
boolean newDataFromPC = false;

char messageFromPC[buffSize] = {0};

unsigned long curMillis;

unsigned long prevReplyToPCmillis = 0;
unsigned long replyToPCinterval = 1000;

// Array of desired stepper positions
long positions[2];

AccelStepper s1(AccelStepper::DRIVER, s1p, s1d);
AccelStepper s2(AccelStepper::DRIVER, s2p, s2d);

MultiStepper steppers;

void runStepper() {

  digitalWrite(s1e,HIGH);
  time1 = millis();
  steppers.moveTo(positions);
  steppers.runSpeedToPosition(); // Blocks until all are in position
  diff = millis() - time1;
  Serial.println(diff);
  
  Serial.print("Stepper 1 position: ");
  Serial.println(positions[0]);
  Serial.print("Stepper 2 position: ");
  Serial.println(positions[1]);
  Serial.println("========================================================================================\n");
  digitalWrite(s1e, LOW);
}

void parseData() {
  // split the data into its parts
  // assumes the data will be received as (eg) 0,1,35
  char * strtokIndx; // this is used by strtok() as an index

  strtokIndx = strtok(inputBuffer,","); // get the first part
  positions[0] = atoi(strtokIndx); //  convert to an integer
  
  strtokIndx = strtok(NULL, ","); // this continues where the previous call left off
  positions[1] = atoi(strtokIndx);

  runStepper();
  
/*  strtokIndx = strtok(NULL, ","); 
  newServoPos = atoi(strtokIndx); 
  
*/}

void getDatafromPC() {
  // receive data from PC and save it into inputBuffer
  if(Serial.available() > 0) {
    char x = Serial.read();

    // the order of these IF clauses is significant  
    if (x == endMarker) {
      readInProgress = false;
      newDataFromPC = true;
      inputBuffer[bytesRecvd] = 0;
      parseData();
    }
    
    if(readInProgress) {
      inputBuffer[bytesRecvd] = x;
      bytesRecvd ++;
      if (bytesRecvd == buffSize) {
        bytesRecvd = buffSize - 1;
      }
    }

    if (x == startMarker) { 
      bytesRecvd = 0; 
      readInProgress = true;
    }
  }
}

void setup() {

    Serial.begin(115200);

    //Use built-in led for debugging.
    pinMode(13, OUTPUT);                                  
    digitalWrite(13, LOW);

    steppers.addStepper(s1);
    steppers.addStepper(s2);

    //Predefined values - Tested till 1300
    s1.setMaxSpeed(100);
    s2.setMaxSpeed(800);

    //Enable both motors
    pinMode(s1e, OUTPUT);
    //digitalWrite(s1e, HIGH);
    pinMode(s2e, OUTPUT);
    //digitalWrite(s2e, HIGH);

    //Debugging
    digitalWrite(13, HIGH);                               
    delay(500);
    digitalWrite(13, LOW);

    Serial.println("<Arduino is ready>");
    while(true) {
      digitalWrite(13, HIGH);
      delay(50);
      digitalWrite(13, LOW);
      delay(50);
      getDatafromPC();
      if (String(inputBuffer).equals("Check")) break;
    }
    Serial.println("Out of loop");
}

void loop() {
  curMillis = millis();
  getDatafromPC();
  //replyPC();
}

/*void loop() {

  
  
  positions[0] = 8000;
  positions[1] = 200;
  steppers.moveTo(positions[0]);
  steppers.runSpeedToPosition(); // Blocks until all are in position
  delay(1000);
  
  // Move to a different coordinate
  positions[0] = -8000;
  positions[1] = 0;
  steppers.moveTo(positions[1]);
  steppers.runSpeedToPosition(); // Blocks until all are in position
  delay(1000);

}
*/
