#define STEPPER_PIN_1 9
#define STEPPER_PIN_2 10
#define STEPPER_PIN_3 11
#define STEPPER_PIN_4 12
#define SCANNER_INDICATOR_LED 13
#define ANALOG_SCAN A 
/*  105 degrees = 597 steps                                               */
/////////////// Global Variables ///////////////////////////////////////////
int Counter = 0;
int Counter2 = 0;
int DEG_UNTIL_STATION = 21;
int step_number = 0;
int ScanningTempo = 10;
int Analog4Scanner = A3;
int StayBestPlace5min = (((1000*1)*60)*1);
int StayTillMorning = (((1000*1)*60)*3);
////////////////////////////////////////////////////////////////////////////
//////// Move single degree in wanted direction  ///////////////////////////
void AddSingleDegree (bool dir) {
  for (int i = 0 ; i <= 6 ; i++ ) {
    if(dir){
    switch(step_number){
      case 0:
        digitalWrite(STEPPER_PIN_1, HIGH);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 1:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, HIGH);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 2:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, HIGH);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 3:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, HIGH);
        break;
   }}else{
    switch(step_number){
      case 0:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, HIGH);
        break;
      case 1:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, HIGH);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 2:
        digitalWrite(STEPPER_PIN_1, LOW);
        digitalWrite(STEPPER_PIN_2, HIGH);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW);
        break;
      case 3:
        digitalWrite(STEPPER_PIN_1, HIGH);
        digitalWrite(STEPPER_PIN_2, LOW);
        digitalWrite(STEPPER_PIN_3, LOW);
        digitalWrite(STEPPER_PIN_4, LOW); 
    }}
  step_number++;
  if(step_number > 3){
    step_number = 0;
  } 
  }
  Counter++;
}
//////////////////////////////////////////////////////////////////////////
/////////// Returns 1 if Normaly Open and 2 if Normaly Closed ////////////
int MicroSwitch (int digitalPin_NUMBER_1 , int digitalPin_NUMBER_2) {
  int val1 = 0;
  int val2 = 0;
  val1 = digitalRead(digitalPin_NUMBER_1);
  val2 = digitalRead(digitalPin_NUMBER_2);
  if (val1==1) {
    return 1;
  }else {
    return 2;
  }
}
int TwoSwitches () {
  if (MicroSwitch(50,52)==2){
    return 1;
  }else if (MicroSwitch(46,48)==1){
    return 2;
  }
  return 0;
}
//////////////////////////////////////////////////////////////////////////
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
  return index;x
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
/////// Scanning 20 places for the best and then stays 5 min there ////////
int GetTheRightSpot () {
  int [20] ScanRadar;
  for (int i = 0 ; i < 10 ; i++){
    AddSingleDegree(false);
    delay(2);
  }
  for (int i = 0 ; i < 20 ; i++){
    digitalWrite(SCANNER_INDICATOR_LED, HIGH);
    ScanRadar[i] = analogRead(Analog4Scanner);
    AddSingleDegree(true);
    digitalWrite(SCANNER_INDICATOR_LED, LOW);
    delay(ScanningTempo);                 
  }
  for (int i = 0 ; i < 10 ; i++){
    AddSingleDegree(false);
    delay(2);
  }
  PrintArray(ScanRadar,20);
  return ReadMaxFromArray(ScanRadar,32);
}
int GoToRightPlace (int x) {
  for (int i = 0 ; i < x ; i++){
    AddSingleDegree(false);
    delay(2);
  }
  delay(StayBestPlace5min); 
}
///////////////////////////////////////////////////////////////////////////
////////////// Wait till morning and go back to day start /////////////////
int EndOfDay () {
  delay(StayTillMorning);
    for (; TwoSwitches()!=2 ;){
    AddSingleDegree(false);
    delay(2);
    }
    for (int i = 0 ; i<10 ; i++){
    AddSingleDegree(true);
    delay(2);
    }
}
///////////////////////////////////////////////////////////////////////////
////////////////////////////  SETUP  //////////////////////////////////////
void setup() {
  Serial.begin(9600);
  delay(2000);
}
///////////////////////////////////////////////////////////////////////////
////////////////////////  MAIN PROGRAM  ///////////////////////////////////
void loop() {
  for (int i=0; TwoSwitches()!=1 ;i++){
    AddSingleDegree(true);
    Counter2++;
    if (Counter2%DEG_UNTIL_STATION==0) {
      Counter2 = 0;
      GoToRightPlace(GetTheRightSpot());
    }
  }
  if (TwoSwitches()==1) {
    EndOfDay();
  }
}
///////////////////////////////////////////////////////////////////////////
