
#define STEPPER_PIN_1 9
#define STEPPER_PIN_2 10
#define STEPPER_PIN_3 11
#define STEPPER_PIN_4 12
#define SCANNER_INDICATOR_LED 13

/////////////// Global Variables /////////////////////////////////
int MAX_ANGLE_105 = 597;
int Counter = 0;
int DEG_UNTIL_STATION = 21;
int step_number = 0;
//////////////////////////////////////////////////////////////////


//////// Move single degree in wanted direction  /////////////////
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
//////////////////////////////////////////////////////////////////




int ScanForMaxWatt () {
  for (int i = 0 ; i < 16 ; i++){
    //OneStep(true);
    delay(2);
  }
  for (int i = 0 ; i < 32 ; i++){
    digitalWrite(SCANNER_INDICATOR_LED, HIGH);
    //ScanRadar[i] = analogRead(analogPin1);
    //OneStep(false);
    digitalWrite(SCANNER_INDICATOR_LED, LOW);
////////////////// SCANNING TEMPO ////////////////////
    delay(10);
//////////////////////////////////////////////////////
  }
  for (int i = 0 ; i < 16 ; i++){
    //OneStep(true);
    delay(2);
  } 
  //PrintArray(ScanRadar,32);
 // return ReadMaxFromArray(ScanRadar,32);
  return 0;
}







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








int AreYouGotToX () {
  if (Counter%DEG_UNTIL_STATION == 0){
    // Start Scanning
  }
return 0; 
}





int IsThereReturnValue (int x) {
  int a = 0;
  if ( x == 98 ) {
    // Go To new Place and wait 5 minutes
    return a;
  } 
  return 0;
}






void setup() {



}

void loop() {
  delay(5000);
  Serial.begin(9600);
  PrintArray(arr,10);
  Serial.print(ReadMaxFromArray(arr,10));
}
