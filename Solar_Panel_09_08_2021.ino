// tom degrees  130,15
#include <Servo.h>
#define West 173
#define East 7
#define StartingPosition 0
#define SCANNER_INDICATOR_LED_1 13
#define SCANNER_INDICATOR_LED_2 12
#define Analog4Scanner A1
#define ScanStationsQuantity 29
int Position = StartingPosition;
int scanNum = 0;
Servo Servo1; 
Servo Servo2; 
int OneStepEast(){
  if (Borders()) {
    Position = Position + 1;
    Servo1.write(Position);
    Servo2.write(Position);
    Serial.print("East - ");
    Serial.println(Position);
    delay(50);
  }
}

int OneStepEastEnd(){
  if (Borders()) {
    Position = Position + 1;
    Servo1.write(Position);
    Servo2.write(Position);
    Serial.print("East - ");
    Serial.println(Position);
    delay(2);
  }
}

int OneStepWest(){
  if (Borders()) {
    Position = Position - 1;
    Servo1.write(Position);
    Servo2.write(Position);
    Serial.print("West - ");
    Serial.println(Position);
    delay(2);
  }
}

bool Borders () {
  if ((Position<(West+1))&&(Position>(East-1))) {
    return true;
  }
return false;
}
int GoEastUntilBorder () {
    while (Borders()) { 
    OneStepEast();
    }
    Position = West;
   // Servo1.write(West);
}

int GoEastUntilBorderEnd () {
    while (Borders()) { 
    OneStepEastEnd();
    }
    Position = West;
   // Servo1.write(West);
}
int GoWestUntilBorderWithScan () {
    while (Borders()) {
  if (Position%ScanStationsQuantity==0) {
    scanNum++;
    Serial.println("---------------- Scan ! ----------------   #");
    Serial.print(scanNum);
    Serial.println("");
    ScanAndWait();
  }
    OneStepWest();
    }
    Position = East;
   // Servo1.write(East);
}
int ScanAndWait () {
  int Best = ScanForBestPlace();
  Serial.println(Best);
  Servo1.write(Position+Best-6);
  Servo2.write(Position+Best-6);
  delay(6000);
}
int ScanForBestPlace () {
  double arr[12];
  for (int i = 0 ; i < 6 ; i++) {
    OneStepEast();    
  }
  for (int i = 0 ; i < 12 ; i++) {
    OneStepWest();    
    delay(500);
    arr[i] = (double)((double)(((analogRead(Analog4Scanner))*(double)100)/(double)145)/(double)145) ; 

  }
  for (int i = 0 ; i < 6 ; i++) {
    OneStepEast();    
  }
  PrintArray(arr,12);
  return (ReadMaxFromArray(arr,12));
}
int GoWestUntilBorder () {
    while (Borders()) {
    OneStepWest();
    }
    Position = East;
   // Servo1.write(East);
}
/////////////////// Array Manipulation Functions /////////////////////////
int ReadMaxFromArray (double a[],int s){
  int Max = 0;
  int index = 0;
  for (int i = 0 ; i < s ; i++){
    if(a[i]>Max){
      Max = a[i];
      index = i;
    }
  }
  return index;
}
void PrintArray(double a[],int s){
  Serial.print("[ ");
  for (int i = 0 ; i < s ; i++){
    Serial.print((double)a[i]);
    Serial.print(" ,");
  }
  Serial.println("]");
}
///////////////////////////////////////////////////////////////////////////
void setup() {
  Serial.begin(9600);
  delay(2000);
  Servo1.attach(22);
  Servo2.attach(24); 
}   
void loop(){
  
  Serial.println("############## Start ##############");
  GoEastUntilBorder();
  Serial.println("############## finished east ##############");
  GoWestUntilBorderWithScan ();
  Serial.println("############## finished west ##############");
  scanNum = 0;
  GoEastUntilBorder();
  Serial.println("############## finished returning back ##############");

  delay(100);
  
}





