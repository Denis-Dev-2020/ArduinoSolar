#define STEPPER_PIN_1 9
#define STEPPER_PIN_2 10
#define STEPPER_PIN_3 11
#define STEPPER_PIN_4 12
#define SCANNER_INDICATOR_LED 13

int step_number = 0;
double VoltageRead = 0;
double AmperageRead = 0;
double PanelVoltArray[3];
double PanelAmpArray[3];
double PanelWattArray[3];
double ScanRadar[16] = {1,2,3,4,5,56,54,34,8,4,22,111,1,0,34,111};
/////////////// ANALOG READ PINS ///////////////////
int analogPin1 = A0;
int AnalogRead1 = 0;
int analogPin2 = A1;
int AnalogRead2 = 0;
int analogPin3 = A2;
int AnalogRead3 = 0;
///////////////////////////////////////////////////








void setup() {
pinMode(STEPPER_PIN_1, OUTPUT);
pinMode(STEPPER_PIN_2, OUTPUT);
pinMode(STEPPER_PIN_3, OUTPUT);
pinMode(STEPPER_PIN_4, OUTPUT);
pinMode(SCANNER_INDICATOR_LED, OUTPUT);
}





void loop() {
  Serial.begin(9600);
  
  for (int i = 0 ; i < 597 ; i++){
    if(i%100 == 0){
      ScanForMaxWatt();
    }
    OneStep(false);
    delay(20);
  }




  ReadPrintStats();


///////////// GO BACK END OF THE DAY /////////////////
  delay(5000);
  for (int i = 0 ; i < 597 ; i++){
    OneStep(true);
    delay(2);
  }
//////////////////////////////////////////////////////

}






void ScanForMaxWatt(){
  digitalWrite(SCANNER_INDICATOR_LED, HIGH);
  for (int i = 0 ; i < 8 ; i++){
    for(int j = 0 ; j < 3 ; j++){
    OneStep(true);
    delay(20);
    }
  }
  for (int i = 0 ; i < 16 ; i++){
    ScanRadar[i] = analogRead(analogPin1);
    for(int j = 0 ; j < 3 ; j++){
    OneStep(false);
    delay(50);
    }
  }
  for (int i = 0 ; i < 8 ; i++){
    for(int j = 0 ; j < 3 ; j++){
    OneStep(true);
    delay(20);
    }  
  } 

  PrintArraySize16(ScanRadar);
  Serial.println(ReadMaxFromArray(ScanRadar));
  digitalWrite(SCANNER_INDICATOR_LED, LOW); 
}
int ReadMaxFromArray (double a[]){
  int Max = 0;
  int index = 0;
  for (int i = 0 ; i < 16 ; i++){
    if(a[i]>Max){
      Max = a[i];
      index = i;
    }
  }
  Serial.print("Max : ");
  Serial.println(Max);
  Serial.print("Index : ");
  Serial.println(index);
  return index;
}
void PrintArraySize3(double a[]){
  Serial.print("[ ");
  for (int i = 0 ; i < 3 ; i++){
  Serial.print(a[i]);
  Serial.print(" ,");
  }
  Serial.println("]");
}
void PrintArraySize16(double a[]){
  Serial.print("[ ");
  for (int i = 0 ; i < 16 ; i++){
  Serial.print(a[i]);
  Serial.print(" ,");
  }
  Serial.println("]");
}
void ReadPrintStats (){
  AnalogRead1 = analogRead(analogPin1);
  VoltageRead = AnalogRead1 * 0.0049;
  PanelVoltArray[0] = VoltageRead;
  AmperageRead = (VoltageRead / 220)*1000;
  PanelAmpArray[0] = AmperageRead;

  AnalogRead2 = analogRead(analogPin2);
  VoltageRead = AnalogRead2 * 0.0049;
  PanelVoltArray[1] = VoltageRead;
  AmperageRead = (VoltageRead / 220)*1000;
  PanelAmpArray[1] = AmperageRead;

  AnalogRead3 = analogRead(analogPin3);
  VoltageRead = AnalogRead3 * 0.0049;
  PanelVoltArray[2] = VoltageRead;
  AmperageRead = (VoltageRead / 220)*1000;
  PanelAmpArray[2] = AmperageRead;

  PanelWattArray[0] = (PanelVoltArray[0]*PanelAmpArray[0])/1000;
  PanelWattArray[1] = (PanelVoltArray[1]*PanelAmpArray[1])/1000;
  PanelWattArray[2] = (PanelVoltArray[2]*PanelAmpArray[2])/1000;
  
  Serial.println("___________________________________");
  Serial.print("Voltage (v) : ");
  PrintArraySize3(PanelVoltArray);
  Serial.print("Amper   (mA): ");
  PrintArraySize3(PanelAmpArray);
  Serial.print("Watt    (w) : ");
  PrintArraySize3(PanelWattArray);
  Serial.println("___________________________________");
}
void OneStep(bool dir){
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
