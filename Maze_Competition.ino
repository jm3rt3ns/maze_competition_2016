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
  if(!side&&!front)
  {
    servo_left.write(20);
    servo_right.write(180);
  }
  // reverse servo_left.write(0);
  // reverse servo_right.write(180);

  //if side high and front low, drift right
  if(side&&!front)
  {
    servo_left.write(0);
    servo_right.write(160);
  }
  
  //if side low and front high, turn left
  if(!side&&front)
  {
    servo_left.write(180);
    servo_right.write(180);
  }
  
  //if both high, turn right
  if(side&&front)
  {
    servo_left.write(0);
    servo_right.write(0);
  }
}
