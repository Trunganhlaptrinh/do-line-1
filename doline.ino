#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver();

#define SEN_1_PIN 39
#define SEN_2_PIN 36
#define SEN_3_PIN 2
#define SEN_4_PIN 32

void goForward() {
  pwm.setPWM(8,0,255);
  pwm.setPWM(9,4096,0);
  pwm.setPWM(10,0,255);
  pwm.setPWM(11,4096,0);
}
void goBackward() {
  pwm.setPWM(8,4096,0);
  pwm.setPWM(9,0,255);
  pwm.setPWM(11,0,255);
  pwm.setPWM(10,4096,0);
}
void turnLeft() {
  pwm.setPWM(8,4096,0);
  pwm.setPWM(9,0,255);
  pwm.setPWM(10,0,255);
  pwm.setPWM(11,4096,0);
}
void turnRight() {
  pwm.setPWM(9,4096,0);
  pwm.setPWM(8,0,255);
  pwm.setPWM(11,0,255);
  pwm.setPWM(10,4096,0);
}
void lineFollowing() {
  char cSen_Status = 0b00000000;
  cSen_Status = cRead_Sensor();
  Serial.println("hello ");

  if((cSen_Status == 0b00001001) || (cSen_Status == 0b00001011) || (cSen_Status == 0b00001101)) {
    goForward();
  }
  else if((cSen_Status == 0b00001110) || (cSen_Status == 0b00001100) || (cSen_Status == 0b00001000) || (cSen_Status == 0b00000000)){
  turnLeft();
  }
  else if((cSen_Status == 0b00000111) || (cSen_Status == 0b00000011) || (cSen_Status == 0b00000001)) {
  turnRight();
  }
  else if((cSen_Status == 0b00001111)) {
  goBackward();
  }
}
char cRead_Sensor() {
  short sSen_Pin[4] = {SEN_1_PIN,SEN_2_PIN,SEN_3_PIN,SEN_4_PIN};
  char cStatus = 0b00000000;
  for(short i = 0 ; i < 4 ; i++) {
    Serial.println(digitalRead(sSen_Pin[i]));
    cStatus = cStatus |(digitalRead(sSen_Pin[i]) << i);
  }
  return cStatus;
}

void setup() {
  Serial.begin(115200);
  pwm.begin();
  pwm.setOscillatorFrequency(27000000);
  pwm.setPWMFreq(50);

  pinMode(SEN_1_PIN,INPUT);
  pinMode(SEN_2_PIN,INPUT);
  pinMode(SEN_3_PIN,INPUT);
  pinMode(SEN_4_PIN,INPUT);
}
void loop() {
  lineFollowing();
}
