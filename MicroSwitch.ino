void setup() {
  Serial.begin(9600);
  delay(2000);
}
void loop() {
  MicroSwitch(48,50);
  delay(1000);
}
int MicroSwitch (int digitalPin_NUMBER_1 , int digitalPin_NUMBER_2) {
  int val1 = 0;
  int val2 = 0;
  val1 = digitalRead(digitalPin_NUMBER_1);
  val2 = digitalRead(digitalPin_NUMBER_2);
  if (val1==1) {
    //Serial.println("Red Light");
    return 1;
  }else {
    //Serial.println("Green Light");
    return 2;
  }
}
