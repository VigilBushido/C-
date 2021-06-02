// http://wwww.bajdi.com
// Robot with 2 geared DC motors controlled by L293D, µCU = ATmega1284P-PU
// Pixy tracking object, communicates via I2C with µCU
// Pixy mounted on pan/tilt kit, 2 SG90 servos
// Robot will try to follow the object
// Pixy data:
// block 1 X = 0 object detected on the left
// block 1 X = 319 object detected on the right
// block 1 Y = 0 object detected top
// block 1 Y = 199 object detected bottom
// block 1 width = 1 to 320
// block 1 height = 1 to 200

#include <Servo.h>
#include <Wire.h>
#include <PixyI2C.h>

PixyI2C pixy;
uint16_t blocks;
unsigned int objectSize;
unsigned long pixyTime;

Servo panServo; 
Servo tiltServo;
const int panServoLeft = 2100;
const int panServoCenter = 1450;
const int panServoRight = 750;
int panServoPos;
const int tiltServoUp = 2000;
const int tiltServoCenter = 1300;
const int tiltServoDown = 900;
int tiltServoPos;

const int EN1 = 3;        //pwm, enable motor 1 = pin 1 of L293D
const int direction1 = 13; //direcion motor 1 = pin 2 of L293D
const int EN2 = 14;        //pwm, enable motor 2 = pin 9 of L293D
const int direction2 = 15; //direction motor 2 = pin 15 of L293D

byte speedLeft = 100; 
byte speedRight = 100; 

const int lEncoder = 10;    // interrupt 0                                  
const int rEncoder = 11;    // interrupt 1

const int motorTime = 100;
unsigned long encoderTime;
volatile unsigned long lpulse = 121;            // width of left and right encoder pulses in uS
volatile unsigned long rpulse = 121;            // width of left and right encoder pulses in uS
volatile unsigned long ltime;             // remembers time of left  encoders last state change in uS
volatile unsigned long rtime;             // remembers time of right encoders last state change in uS 

void setup()
{
  Serial.begin(57600);
  pinMode(EN1, OUTPUT); 
  pinMode(direction1, OUTPUT);
  pinMode(EN2, OUTPUT);
  pinMode(direction2, OUTPUT);
  analogWrite(EN1, 0);
  analogWrite(EN2, 0);
  digitalWrite(lEncoder,1);                               // enable pullup resistor for left  encoder sensor
  digitalWrite(rEncoder,1);    
  attachInterrupt(0,Lencoder,CHANGE);                     // trigger left  encoder ISR on state change
  attachInterrupt(1,Rencoder,CHANGE);                     // trigger right encoder ISR on state change
  delay(50);
  panServo.attach(22);
  panServoPos = panServoCenter; 
  panServo.writeMicroseconds(panServoPos);
  tiltServo.attach(23);
  tiltServoPos = tiltServoCenter;
  tiltServo.writeMicroseconds(tiltServoPos);
  delay(500);
}

void loop()
{

  if (millis() - encoderTime >= 5)
  {
    encoderTime = millis();
    int lastPulseL = millis() - ltime;     // Check how much time has passed since last pulse
    int lastPulseR = millis() - rtime;

    if (lastPulseL > motorTime && speedLeft < 170)    // If the pulse is longer then the time we want speed up motor
    {
      speedLeft = speedLeft+2;
    }
    if (lastPulseL < motorTime && speedLeft > 0)      // // If the pulse is shorter then the time we want slow down motor
    {
      speedLeft = speedLeft-2;
    }

    if (lastPulseR > motorTime && speedRight < 170)
    {
      speedRight = speedRight+2;
    }
    if (lastPulseR < motorTime && speedRight > 0)
    {
      speedRight = speedRight-2;
    }
  }


  if (millis() - pixyTime >= 20)
  {
    pixyTime = millis();
    blocks = pixy.getBlocks();

    if (blocks)        // object detected
    {

      objectSize = pixy.blocks[0].width * pixy.blocks[0].height;

      if(objectSize > 400)
      {
        if (pixy.blocks[0].x > 150 && panServoPos > panServoRight)
        {
          panServoPos -= 10;
        }
        if (pixy.blocks[0].x < 170 && panServoPos < panServoLeft)
        {
          panServoPos += 10;
        }
        if (pixy.blocks[0].y > 90 && tiltServoPos > tiltServoDown)
        {
          tiltServoPos -= 10;
        }
        if (pixy.blocks[0].y < 110 && tiltServoPos < tiltServoUp)
        {
          tiltServoPos += 10;
        }

        if (objectSize < 20000)  // object far from robot
        {
          if(panServoPos < panServoCenter+200 && panServoPos > panServoCenter-200)
          {
            forward();
          }
          if (panServoPos >= panServoCenter+200)
          {
            left();
          }
          if (panServoPos <= panServoCenter-200)
          {
            right();
          }
        }

        if (objectSize >= 20000)    // object close to robot
        {
          if(panServoPos < panServoCenter+200 && panServoPos > panServoCenter-200)
          {
            backward();
          }
          if (panServoPos >= panServoCenter+200)
          {
            left();
          }
          if (panServoPos <= panServoCenter-200)
          {
            right();
          }
        }
      }
      else
      {
        centerServo();
        stop();
      }
    }
    else
    {
      centerServo();
      stop();
    }

    panServo.writeMicroseconds(panServoPos);
    tiltServo.writeMicroseconds(tiltServoPos);
    Serial.print("pixy.blocks[0].x = ");
    Serial.println(pixy.blocks[0].x);          
    Serial.print("pixy.blocks[0].y = ");
    Serial.println(pixy.blocks[0].y);          
    Serial.print("pixy.blocks[0].width = ");
    Serial.println(pixy.blocks[0].width);         
    Serial.print("pixy.blocks[0].height = ");
    Serial.println(pixy.blocks[0].height);       
    Serial.print("objectSize = ");
    Serial.println(objectSize); 
  }
}

void forward()
{
  digitalWrite(direction1, HIGH);
  digitalWrite(direction2, HIGH);  
  analogWrite(EN1, speedLeft);
  analogWrite(EN2, speedRight);
}

void stop()
{
  digitalWrite(direction1, LOW);  
  digitalWrite(direction2, LOW);  
  analogWrite(EN1, 0);
  analogWrite(EN2, 0);
}

void backward()
{
  digitalWrite(direction1, LOW); 
  digitalWrite(direction2, LOW);  
  analogWrite(EN1, speedLeft);
  analogWrite(EN2, speedRight);
}

void left()
{
  digitalWrite(direction1, LOW);
  digitalWrite(direction2, HIGH);  
  analogWrite(EN1, speedLeft);
  analogWrite(EN2, speedRight);
}

void right()
{
  digitalWrite(direction1, HIGH);
  digitalWrite(direction2, LOW);  
  analogWrite(EN1, speedLeft);
  analogWrite(EN2, speedRight);
}

//======================================================= ISR for left encoder =======================================================
void Lencoder()
{
  lpulse=millis()-ltime;                               // time between last state change and this state change
  ltime=millis();  // update ltime with time of most recent state change
  //lcount++;
}


//======================================================= ISR for right encoder ======================================================
void Rencoder()
{
  rpulse=millis()-rtime;                               // time between last state change and this state change
  rtime=millis();  // update ltime with time of most recent state change
  //rcount++;
}

void centerServo()
{
  if (panServoPos > panServoCenter) // center pan servo
  {
    panServoPos -= 10;
  }
  if (panServoPos < panServoCenter)  // center pan servo
  {
    panServoPos += 10;
  }
  if (tiltServoPos > tiltServoCenter) // center tilt servo
  {
    tiltServoPos -= 10;
  }
  if (tiltServoPos < tiltServoCenter) // center tilt servo
  {
    tiltServoPos += 10;
  }
}
