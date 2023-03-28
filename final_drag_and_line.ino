// Output pins:

const int fourwayswitch = A6; // input from function switch

const int lmotorDIR = 7; // Left motor dirn input 1

const int rmotorDIR = 8; // Right motor dirn input 3

const int lmotorPWM = 9; // Left motor PWM pin

const int rmotorPWM = 10; // Right motor PWM pin

const int LED13 = 13; // ext LED Red

const int rside = A0; // left side sensor input

const int rfront = A1; // front left line sensor input

const int lfront = A2; // front right left sensor input

const int lside = A3; // right side sensor input

const int sensorLED1 = 6; // 1st diagnostic LED on sensor board

const int sensorLED2 = 11; // 2nd diagnostic LED on sensor board

const int trigger = 12; // trigger for sensor LEDs

// Inputs from among us susi baka

int switchvoltage =
    0; // analogue value coming back from reading function or 4 way switch

int fnswvalue = 0; // value (in range 0 to 16) of 4 way function switch

int rfrontsens = 0; // Right front sensor value

int lfrontsens = 0; // Left front sensor value

int rsidesens = 0; // Right side sensor value

int lsidesens = 0; // Left side sensor value

signed int sensdiff = 0; // Difference between front sensors

// Motor variables

int basespeed = 50; // Base speed

int rightspeed = 0; // Right motor speed

int leftspeed = 0; // Left motor speed

int speeddif = 20; // amount to adjust motor speed by

int straightspeed = 60;

int i = 0; // loop counter
int starttime = millis();
int howlongtime;

void functionswitch() {

  switchvoltage = analogRead(fourwayswitch);

  fnswvalue = 16;

  if (switchvoltage > 87)
    fnswvalue = fnswvalue - 1;

  if (switchvoltage > 171)
    fnswvalue = fnswvalue - 1;

  if (switchvoltage > 242)
    fnswvalue = fnswvalue - 1;

  if (switchvoltage > 310)
    fnswvalue = fnswvalue - 1;

  if (switchvoltage > 369)
    fnswvalue = fnswvalue - 1;

  if (switchvoltage > 411)
    fnswvalue = fnswvalue - 1;

  if (switchvoltage > 449)
    fnswvalue = fnswvalue - 1;

  if (switchvoltage > 492)
    fnswvalue = fnswvalue - 1;

  if (switchvoltage > 532)
    fnswvalue = fnswvalue - 1;

  if (switchvoltage > 556)
    fnswvalue = fnswvalue - 1;

  if (switchvoltage > 579)
    fnswvalue = fnswvalue - 1;

  if (switchvoltage > 601)
    fnswvalue = fnswvalue - 1;

  if (switchvoltage > 622)
    fnswvalue = fnswvalue - 1;

  if (switchvoltage > 638)
    fnswvalue = fnswvalue - 1;

  if (switchvoltage < 654)
    fnswvalue = fnswvalue - 1;

  if (switchvoltage > 654)
    fnswvalue = 0;

  if (switchvoltage > 999)
    fnswvalue = 16;
}

void motortest() {

  digitalWrite(lmotorDIR, HIGH);

  digitalWrite(rmotorDIR, HIGH);

  rightspeed = 70;

  leftspeed = 70;

  analogWrite(rmotorPWM, rightspeed); // set right motor speed

  analogWrite(lmotorPWM, leftspeed); // set left motor speed
}

void setup() {

  pinMode(lmotorDIR, OUTPUT);

  pinMode(lmotorPWM, OUTPUT);

  pinMode(rmotorDIR, OUTPUT);

  pinMode(rmotorPWM, OUTPUT);

  pinMode(LED13, OUTPUT);

  pinMode(sensorLED1, OUTPUT);

  pinMode(sensorLED2, OUTPUT);

  pinMode(trigger, OUTPUT);

  // read both line sensors then the two side sensors

  digitalWrite(trigger, HIGH);

  delayMicroseconds(150); // wait for LED to light up fully

  lfrontsens = analogRead(lfront);

  rfrontsens = analogRead(rfront);

  rsidesens = analogRead(rside); // read right side photo sensor input

  lsidesens = analogRead(lside); // read left side photo sensor input

  digitalWrite(trigger, LOW);

  Serial.begin(9600);

  switchvoltage = analogRead(fourwayswitch);

  Serial.print(" switchvoltage ");

  Serial.print(" ");

  Serial.print(switchvoltage);

  Serial.println(" ");
}

void loop()

{

  digitalWrite(trigger, HIGH);

  delayMicroseconds(150); // wait for LED to light up fully

  lfrontsens = analogRead(lfront);

  rfrontsens = analogRead(rfront);

  rsidesens = analogRead(rside); // read right side photo sensor input

  lsidesens = analogRead(lside); // read left side photo sensor input

  digitalWrite(trigger, LOW);

  functionswitch();

  if (fnswvalue == 0)
    linefollow();

  else if (fnswvalue == 8)
    dragrace();
}

void linefollow() {

  sensdiff = lfrontsens - rfrontsens;

  speeddif = 30;

  if (sensdiff == 0) {

    digitalWrite(lmotorDIR, HIGH);

    digitalWrite(rmotorDIR, HIGH);

    rightspeed = straightspeed;

    leftspeed = straightspeed;

    analogWrite(rmotorPWM, rightspeed); // set right motor speed

    analogWrite(lmotorPWM, leftspeed); // set left motor speed

  } else if (sensdiff < 0) {

    digitalWrite(lmotorDIR, HIGH);

    digitalWrite(rmotorDIR, HIGH);

    rightspeed = basespeed + speeddif;

    leftspeed = basespeed - speeddif;

    analogWrite(rmotorPWM, rightspeed); // set right motor speed

    analogWrite(lmotorPWM, leftspeed); // set left motor speed

  } else if (sensdiff > 0) {

    digitalWrite(lmotorDIR, HIGH);

    digitalWrite(rmotorDIR, HIGH);

    rightspeed = basespeed - speeddif;

    leftspeed = basespeed + speeddif;

    analogWrite(rmotorPWM, rightspeed); // set right motor speed

    analogWrite(lmotorPWM, leftspeed); // set left motor speed
  }
}

void dragrace() {
  Serial.print("drag race");
  howlongtime = millis();
  sensdiff = lfrontsens - rfrontsens;

  speeddif = 30;

  while (howlongtime - starttime > 1000 and rsidesens < 650 and
         lsidesens < 550) {
    rightspeed = 0;
    leftspeed = 0;
    break;
  }

  if (sensdiff == 0) {

    digitalWrite(lmotorDIR, HIGH);

    digitalWrite(rmotorDIR, HIGH);

    rightspeed = straightspeed;

    leftspeed = straightspeed;

    analogWrite(rmotorPWM, rightspeed); // set right motor speed

    analogWrite(lmotorPWM, leftspeed); // set left motor speed

  } else if (sensdiff < 0) {

    digitalWrite(lmotorDIR, HIGH);

    digitalWrite(rmotorDIR, HIGH);

    rightspeed = basespeed + speeddif;

    leftspeed = basespeed - speeddif;
    analogWrite(rmotorPWM, rightspeed); // set right motor speed
    analogWrite(lmotorPWM, leftspeed);  // set left motor speed
  } else if (sensdiff > 0) {

    digitalWrite(lmotorDIR, HIGH);

    digitalWrite(rmotorDIR, HIGH);

    rightspeed = basespeed - speeddif;

    leftspeed = basespeed + speeddif;

    analogWrite(rmotorPWM, rightspeed); // set right motor speed

    analogWrite(lmotorPWM, leftspeed); // set left motor speed
  }
}

void phototest() {

  Serial.print("LS ");

  Serial.print(lsidesens); // send photo sensor values to serial monitor

  Serial.print(" LF ");

  Serial.print(lfrontsens);

  Serial.print(" RF ");

  Serial.print(rfrontsens); // dun dun dun dun dun dun dun dun dun dun dun dun
                            // dun dun dun dun dun dun dun dun dun dun dun dun
                            // dun dun dun dun dun dun

  Serial.print(" RS ");

  Serial.print(rsidesens);

  Serial.println(" ");

  delay(100);
}

void switchread()

{

  switchvoltage = analogRead(fourwayswitch); //*windows xp noises*

  Serial.print(" switchvoltage ");

  Serial.print(" ");

  Serial.print(switchvoltage);

  Serial.println(" ");

  if (switchvoltage > 654)
    fnswvalue = 0;

  if (switchvoltage > 999)
    fnswvalue = 16;
}

// koomalala koomalala koomala savesta
