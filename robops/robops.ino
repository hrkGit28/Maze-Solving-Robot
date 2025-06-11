
int motor_lA = 9;
int motor_lB = 10;
int motor_enableA = 11;

int motor_rA = 3;
int motor_rB = 4;
int motor_enableB = 5;

int trigger_front = A0;
int echo_front = A1;

int trigger_left = A2;
int echo_left = A3;

int trigger_right = A4;
int echo_right = A5;
void setup() {
  // put your setup code here, to run once:
  pinMode(motor_lA,OUTPUT);   //left motors forward
  pinMode(motor_lB,OUTPUT);   //left motors reverse
  pinMode(motor_enableA, OUTPUT);

  pinMode(motor_rA,OUTPUT);   //right motors reverse
  pinMode(motor_rB,OUTPUT);   //rignt motors forward
  pinMode(motor_enableB, OUTPUT);

  pinMode(trigger_front,OUTPUT);
  pinMode(echo_front,INPUT);

  pinMode(trigger_left,OUTPUT);
  pinMode(echo_left,INPUT);

  pinMode(trigger_right,OUTPUT);
  pinMode(echo_right,INPUT);
  
  analogWrite(motor_enableA, 255);
  analogWrite(motor_enableB, 255);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
   long duration_front, distance_front, duration_left, distance_left, duration_right, distance_right;
    
  //Calculating distance
  
  digitalWrite(trigger_front, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_front, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_front, LOW);
  duration_front = pulseIn(echo_front, HIGH);
  distance_front= duration_front*0.034/2;

  digitalWrite(trigger_left, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_left, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_left, LOW);
  duration_left = pulseIn(echo_left, HIGH);
  distance_left= duration_left*0.034/2;

  digitalWrite(trigger_right, LOW);
  delayMicroseconds(2);
  digitalWrite(trigger_right, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigger_right, LOW);
  duration_right = pulseIn(echo_right, HIGH);
  distance_right= duration_right*0.034/2;

  Serial.print("left=");
  Serial.println(distance_left);
   Serial.print("right=");
  Serial.println(distance_right);
   Serial.print("front");
  Serial.println(distance_front);

 if (distance_left<20&&distance_front>5&&distance_right<20)//Straight path
    {
     forward();
    }

  if (distance_left>20&&distance_front<5&&distance_right<20)//Left turn
    {
     left();
     forward();
    }

  if (distance_left<20&&distance_front<5&&distance_right>20)//Right Turn
    {
      right();
      forward();
    }

  if (distance_left>20&&distance_front<5&&distance_right>20)//T Intersection
    {
      left(); // As left is possible
    }

  if (distance_left>20&&distance_front>5&&distance_right<20)//Left T Intersection
    {
      left();// As Left is possible
    }

  if (distance_left<20&&distance_front>5&&distance_right>20)//Right T Tntersection
    {
     forward();//As Straight path is possible
    }

  if(distance_left<20&&distance_front<5&&distance_right<20){ // Dead end
    if(distance_right>=distance_left){
     right();
     delay(420);
     forward();
     }//As no other direction is possible
     if(distance_left>=distance_right){
      left();
      delay(420);
      forward();
      }
    }

  if (distance_left>20&&distance_front>5&&distance_right>20)//4 Lane intersection
    {
     left(); //As no other direction is possible
    }

  
}
void forward(){
  digitalWrite(motor_lA,1);
  digitalWrite(motor_lB,0);
  digitalWrite(motor_rA,0);
  digitalWrite(motor_rB,1);
  delay(50);
}


void right(){
  digitalWrite(motor_lA,1);
  digitalWrite(motor_lB,0);
  digitalWrite(motor_rA,1);
  digitalWrite(motor_rB,0);
 delay(430);
}


void left(){
  digitalWrite(motor_lA,0);
  digitalWrite(motor_lB,1);
  digitalWrite(motor_rA,0);
  digitalWrite(motor_rB,1);
  delay(430);
}



void Stop(){
  digitalWrite(motor_lA,0);
  digitalWrite(motor_lB,0);
  digitalWrite(motor_rA,0);
  digitalWrite(motor_rB,0);
  delay(300);
}

