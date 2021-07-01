#define STOPPER_NC 48
#define STOPPER_COM 50

int ScanForStopper () {
  int stopFlag = 0;
  if (digitalRead(STOPPER_NC) == HIGH) {
    stopFlag = 1;
  }
    if (digitalRead(STOPPER_COM) == HIGH) {
    stopFlag = 2;
  }
  return stopFlag;
}


void Count(){
for (int i = 0 ; i < 10000 && digitalRead(STOPPER_COM)== 1; i++){
Serial.println(i);
delay(100);
}


  
}




void PrintStats(){
Serial.print("C ");
Serial.println(digitalRead(STOPPER_COM));
Serial.print("N ");
Serial.println(digitalRead(STOPPER_NC));
delay(2);
}


void setup() {

}

void loop() {
Serial.begin(9600);

Count();

}
