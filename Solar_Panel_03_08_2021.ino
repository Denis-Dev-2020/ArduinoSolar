#include <Servo.h>

#define West 90
#define East 15
#define StartingPosition 15

int Position = StartingPosition;
Servo Servo1; 





int OneStepEast(){
  if (Borders()) {
    Position = Position + 1;
    Servo1.write(Position);
    Serial.print("East - ");
    Serial.println(Position);
    delay(50);
  }
}
int OneStepWest(){
  if (Borders()) {
    Position = Position - 1;
    Servo1.write(Position);
    Serial.print("West - ");
    Serial.println(Position);
    delay(50);
  }
}
bool Borders () {
  if ((Position<91)&&(Position>14)) {
    return true;
  }
return false;
}
int GoEastUntilBorder () {
    while (Borders()) {
    OneStepEast();
    }
    Position = 90;
    Servo1.write(90);
}
int GoWestUntilBorder () {
    while (Borders()) {
    OneStepWest();
    }
    Position = 15;
    Servo1.write(15);
}




 
void setup() {
  Serial.begin(9600);
  delay(2000);
  Servo1.attach(7); 
}


void loop(){
  Serial.println("############## Start ##############");
  GoEastUntilBorder();
  Serial.println("############## finished east ##############");
  GoWestUntilBorder();
  Serial.println("############## finished west ##############");
  GoEastUntilBorder();
  Serial.println("############## finished returning back ##############");
}
