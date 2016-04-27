#include <Servo.h>
Servo servo_left;
Servo servo_right;

int front_sw = 2;
int side_sw = 3;
volatile bool front = 0;
volatile bool side = 0;

void setup()
{
  //set up servos
  servo_left.attach(11);
  servo_right.attach(12);

  // set up sensors
  pinMode(front_sw, INPUT);
  pinMode(side_sw, INPUT);
  attachInterrupt(digitalPinToInterrupt(front_sw), High, CHANGE);
  attachInterrupt(digitalPinToInterrupt(side_sw), High, CHANGE);
  
  Serial.begin(9600);
}

void loop()
{
}

void High()
{
  //run when either sensor changes
  side = digitalRead(side_sw);
  Serial.print("side: ");
  Serial.println(side);
  front = digitalRead(front_sw);
  Serial.print("front: ");
  Serial.println(front);

  //if both low, drift left
  servo_left.write(90);
  servo_right.write(90);

  //if side high and front low, drift right

  //if side low and front high, turn left

  //if both high, turn right
}
