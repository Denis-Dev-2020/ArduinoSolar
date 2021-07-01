#define STEPPER_PIN_1 9
#define STEPPER_PIN_2 10
#define STEPPER_PIN_3 11
#define STEPPER_PIN_4 12
#define SCANNER_INDICATOR_LED 13
#define MAX_ANGLE_105 597

////////// OHM METTER //////////////////////////////////////
const int sensorPin = A5;
int sensorValue = 0;
float Vin = 5;
float Vout = 0;
float Rref = 2200;
float R = 0;
//////////////////////////////////////////////////////////////

int step_number = 0;
double VoltageRead = 0;
double AmperageRead = 0;
double PanelVoltArray[3];
double PanelAmpArray[3];
double PanelWattArray[3];
double ScanRadar[32];
double TourbineVolt = 0;
double TourbineAmp = 0;
double TourbineWatt = 0;
/////////////// ANALOG READ PINS ///////////////////
int analogPin1 = A0;
int AnalogRead1 = 0;
int analogPin2 = A1;
int AnalogRead2 = 0;
int analogPin3 = A2;
int AnalogRead3 = 0;
int analogTourbinePin4 = A3;
int analogTourbine = 0;
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
  PrintOhmMeter();
  StartWorking();
}


void StartWorking(){
  int MostEfficientPlace = 0;
  for (int i = 0 ; i < MAX_ANGLE_105 ; i++){
    if(i%100 == 0){
      MostEfficientPlace = ScanForMaxWatt();
      //Serial.println(MostEfficientPlace);
      for(int GoingBackForMostEfficientPlace = 0 ; GoingBackForMostEfficientPlace < 16 ; GoingBackForMostEfficientPlace++){
            OneStep(true);
            delay(2);
      }
      for(int GoingFowardForMostEfficientPlace = 0 ; GoingFowardForMostEfficientPlace < MostEfficientPlace ; GoingFowardForMostEfficientPlace++){
            OneStep(false);
            delay(2);
      }
            digitalWrite(SCANNER_INDICATOR_LED, HIGH);
////////////// STAY ON EFFICIENT PLACE TEMPO /////////
            delay(50);
//////////////////////////////////////////////////////
            digitalWrite(SCANNER_INDICATOR_LED, LOW);
      for(int GoingBackFromForMostEfficientPlace = 0 ; GoingBackFromForMostEfficientPlace < MostEfficientPlace ; GoingBackFromForMostEfficientPlace++){
            OneStep(true);
            delay(2);
      }
      for(int GoingToWhereWeLeft = 0 ; GoingToWhereWeLeft < 16 ; GoingToWhereWeLeft++){
            OneStep(false);
            delay(2);
      } 
    }
    OneStep(false);
//////////////// DAYTIME TEMPO //////////////////////
    delay(2);
/////////////////////////////////////////////////////
  }
  ReadPrintStatsSolar();
  ReadPrintTourbineStat();
///////////// GO BACK END OF THE DAY /////////////////
  delay(1000);
  for (int i = 0 ; i < MAX_ANGLE_105 ; i++){
    OneStep(true);
    delay(2);
  }
////////////////////////////////////////////////////// 
}
int ScanForMaxWatt(){
  for (int i = 0 ; i < 16 ; i++){
    OneStep(true);
    delay(2);
  }
  for (int i = 0 ; i < 32 ; i++){
    digitalWrite(SCANNER_INDICATOR_LED, HIGH);
    ScanRadar[i] = analogRead(analogPin1);
    OneStep(false);
    digitalWrite(SCANNER_INDICATOR_LED, LOW);
////////////////// SCANNING TEMPO ////////////////////
    delay(10);
//////////////////////////////////////////////////////
  }
  for (int i = 0 ; i < 16 ; i++){
    OneStep(true);
    delay(2);
  } 
  //PrintArray(ScanRadar,32);
  return ReadMaxFromArray(ScanRadar,32);
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
  Serial.print(a[i]);
  Serial.print(" ,");
  }
  Serial.println("]");
}
void ReadPrintTourbineStat (){
  TourbineVolt = (analogRead(analogTourbinePin4)/1023)*5;
  TourbineAmp = (TourbineVolt / 220)*1000;
  TourbineWatt = (TourbineVolt*TourbineAmp)/1000;
  Serial.println("___________________________________");
  Serial.println("Tourbine : ");
  Serial.print("Voltage (v) : ");
  Serial.println(TourbineVolt);
  Serial.print("Amper   (mA): ");
  Serial.println(TourbineAmp);
  Serial.print("Watt    (w) : ");
  Serial.println(TourbineWatt);
  Serial.println("___________________________________");
}
void ReadPrintStatsSolar (){
  VoltageRead = 0;
  AnalogRead1 = analogRead(analogPin1);
  VoltageRead = AnalogRead1;
  PanelVoltArray[0] = (VoltageRead/1023)*5;
  AmperageRead = (VoltageRead / 220)*1000;
  PanelAmpArray[0] = AmperageRead;

  AnalogRead2 = analogRead(analogPin2);
  VoltageRead = AnalogRead2;
  PanelVoltArray[1] = (VoltageRead/1023)*5;
  AmperageRead = (VoltageRead / 220)*1000;
  PanelAmpArray[1] = AmperageRead;

  AnalogRead3 = analogRead(analogPin3);
  VoltageRead = AnalogRead3;
  PanelVoltArray[2] = (VoltageRead/1023)*5;
  AmperageRead = (VoltageRead / 220)*1000;
  PanelAmpArray[2] = AmperageRead;

  VoltageRead = 0;
  PanelWattArray[0] = (PanelVoltArray[0]*PanelAmpArray[0])/1000;
  PanelWattArray[1] = (PanelVoltArray[1]*PanelAmpArray[1])/1000;
  PanelWattArray[2] = (PanelVoltArray[2]*PanelAmpArray[2])/1000;
  
  Serial.println("___________________________________");
  Serial.println("Solar    : ");
  Serial.print("Voltage (v) : ");
  PrintArray(PanelVoltArray,3);
  Serial.print("Amper   (mA): ");
  PrintArray(PanelAmpArray,3);
  Serial.print("Watt    (w) : ");
  PrintArray(PanelWattArray,3);
  Serial.println("___________________________________");
}
void PrintOhmMeter(){
  sensorValue = analogRead(sensorPin);  // Read Vout on analog input pin A0 (Arduino can sense from 0-1023, 1023 is 5V)
  Vout = (Vin * sensorValue) / 1023;    // Convert Vout to volts
  R = Rref * (1 / ((Vin / Vout) - 1));  // Formula to calculate tested resistor's value
  Serial.print("R: ");                  
  Serial.println(R);
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
