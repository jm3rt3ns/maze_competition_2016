#include <Servo.h>
Servo servo_left;
Servo servo_right;

int front_sw = 7;
int side_sw = 2;
volatile bool front = 0;
volatile bool side = 0;

const int RIGHT_OFFSET = 3;
const int LEFT_OFFSET = 3;

int i = 0;

void setup()
{
  //set up servos
  servo_left.attach(12);
  servo_right.attach(11);
  
  Serial.begin(9600);
  delay(5000);
}

void loop()
{
  /*if(start==1){
  //if both low, drift left
  if(!side&&!front)
  {
    Turn_Left();
  }

  //if side high and front low, drift right
  if(side&&!front)
  {
    Drift_Left();
  }
  
  //if side low and front high, turn left
  if(!side&&front)
  {
    Turn_Right();
  }
  
  //if both high, turn right
  if(side&&front)
  {
    Turn_Right();
  }

  front = 0;
  side = 0;
  }*/

  long duration, inches_l,inches_f;
  pinMode(front_sw, OUTPUT);
  digitalWrite(front_sw,LOW);
  delayMicroseconds(2);
  digitalWrite(front_sw,HIGH);
  delayMicroseconds(5);
  digitalWrite(front_sw,LOW);

  pinMode(front_sw,INPUT);
  duration = pulseIn(front_sw,HIGH);

  inches_f = duration / 74 / 2;

  Serial.print("front: ");
  Serial.println(inches_f);
 
  pinMode(side_sw, OUTPUT);
  digitalWrite(side_sw,LOW);
  delayMicroseconds(2);
  digitalWrite(side_sw,HIGH);
  delayMicroseconds(5);
  digitalWrite(side_sw,LOW);

  pinMode(side_sw,INPUT);
  duration = pulseIn(side_sw,HIGH);

  inches_l = duration / 74 / 2;

  Serial.print("right: ");
  Serial.println(inches_l);
  
  //if left and front wall close, turn right
  if(inches_f<=5)
  {
    Turn_Right();
  }
  //if left of control limit, correct right
  else if(inches_l<5)
  {
    Correct_Right();
  }
  //if right of control limit, correct left
  else if(inches_l>6&&inches_l<8)
  {
    Correct_Left();
  }
  //if left wall super far away, turn left 90 degrees and move forward a couple inches
  else if(inches_l>7)
  {
    Turn_Left();
  }
  //otherwise if inside control limits move straight ahead
  else
  {
    Forward();
  }
}

/*void High()
{
  //run when either sensor changes
  side = digitalRead(side_sw);
  Serial.print("side: ");
  Serial.println(side);
  front = digitalRead(front_sw);
  Serial.print("front: ");
  Serial.println(front);
  
}*/

/*void Drift_Left(){
  servo_left.write(180-LEFT_OFFSET);
  servo_right.write(20+RIGHT_OFFSET);
}

void Drift_Right(){
  //servo_left.write(110-LEFT_OFFSET);
  //servo_right.write(80+RIGHT_OFFSET);
  
  servo_left.write(180-LEFT_OFFSET);
  servo_right.write(180-RIGHT_OFFSET);
  delay(100);
}*/

void Turn_Right()
{
  /*Reverse();
  delay(300);
  servo_left.write(180-LEFT_OFFSET);
  servo_right.write(180-RIGHT_OFFSET);
  delay(1000);

  while(!side)
  {
    side = digitalRead(side_sw);
    Drift_Left();
  }

  servo_left.write(180-LEFT_OFFSET);
  servo_right.write(180-RIGHT_OFFSET);
  delay(250);

  while(!side)
  {
    side = digitalRead(side_sw);
    Drift_Left();
  }*/

  servo_left.write(180-LEFT_OFFSET);
  servo_right.write(180-RIGHT_OFFSET);
  delay(500);
}

void Turn_Left(){
  Forward();
  delay(500);
  servo_left.write(0-LEFT_OFFSET);
  servo_right.write(0-RIGHT_OFFSET);
  delay(500);
  Forward();
  delay(1300);
}

void Stop()
{
  servo_left.write(90+LEFT_OFFSET);
  servo_right.write(90+RIGHT_OFFSET);
}

void Reverse()
{
  servo_left.write(0+LEFT_OFFSET);
  servo_right.write(180-RIGHT_OFFSET);
}

void Correct_Left()
{
  servo_left.write(0-LEFT_OFFSET);
  servo_right.write(0-RIGHT_OFFSET);
  delay(100);
  Forward();
  delay(500);
}

void Correct_Right()
{
  servo_left.write(180-LEFT_OFFSET);
  servo_right.write(180-RIGHT_OFFSET);
  delay(100);
  Forward();
  delay(500);
}

void Forward()
{
  servo_left.write(180+LEFT_OFFSET);
  servo_right.write(0-RIGHT_OFFSET);
}
