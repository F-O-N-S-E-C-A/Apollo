#define SPEED 140 //default 140    
#define TURN_SPEED 160    
#define var_speed 100

#define speedPinR 12 //9   //  Front Wheel PWM pin connect Right MODEL-X ENA 
#define RightMotorDirPin1  7//22    //Front Right Motor direction pin 1 to Right MODEL-X IN1  (K1)
#define RightMotorDirPin2  8//24   //Front Right Motor direction pin 2 to Right MODEL-X IN2   (K1)

#define LeftMotorDirPin1  5//26    //Front Left Motor direction pin 1 to Right MODEL-X IN3 (K3)
#define LeftMotorDirPin2  6//28   //Front Left Motor direction pin 2 to Right MODEL-X IN4 (K3)
#define speedPinL 11//10   //  Front Wheel PWM pin connect Right MODEL-X ENB

#define speedPinRB 10//11   //  Rear Wheel PWM pin connect Left MODEL-X ENA 
#define RightMotorDirPin1B  26//5    //Rear Right Motor direction pin 1 to Left  MODEL-X IN1 ( K1)
#define RightMotorDirPin2B 28//6    //Rear Right Motor direction pin 2 to Left  MODEL-X IN2 ( K1) 

#define LeftMotorDirPin1B 22 //7    //Rear Left Motor direction pin 1 to Left  MODEL-X IN3  (K3)
#define LeftMotorDirPin2B 24 //8  //Rear Left Motor direction pin 2 to Left  MODEL-X IN4 (K3)
#define speedPinLB 9 //12    //  Rear Wheel PWM pin connect Left MODEL-X ENB


float x = 0.0;
float y = 0.0;
float theta = 0.0;

// --------- movement functions control ---------

void front(int speed){
   RL_fwd(speed);
   RR_fwd(speed);
   FR_fwd(speed);
   FL_fwd(speed); 
}

void back(int speed){
   RL_bck(speed);
   RR_bck(speed);
   FR_bck(speed);
   FL_bck(speed); 
}

void right_shift(int speed_fl_fwd,int speed_rl_bck ,int speed_rr_fwd,int speed_fr_bck) {
  FL_fwd(speed_fl_fwd); 
  RL_bck(speed_rl_bck); 
  RR_fwd(speed_rr_fwd);
  FR_bck(speed_fr_bck);
}

void left_shift(int speed_fl_bck,int speed_rl_fwd ,int speed_rr_bck,int speed_fr_fwd){
   FL_bck(speed_fl_bck);
   RL_fwd(speed_rl_fwd);
   RR_bck(speed_rr_bck);
   FR_fwd(speed_fr_fwd);
}

void left_turn(int speed){
   RL_bck(0);
   RR_fwd(speed);
   FR_fwd(speed);
   FL_bck(0); 
}

void right_turn(int speed){
   RL_fwd(speed);
   RR_bck(0);
   FR_bck(0);
   FL_fwd(speed); 
}

void left_back(int speed){
   RL_fwd(0);
   RR_bck(speed);
   FR_bck(speed);
   FL_fwd(0); 
}

void right_back(int speed){
   RL_bck(speed);
   RR_fwd(0);
   FR_fwd(0);
   FL_bck(speed); 
}

void rot_right(int speed){
   RL_fwd(speed);
   RR_bck(speed);
   FR_bck(speed);
   FL_fwd(speed);
}

void rot_left(int speed){
   RL_bck(speed);
   RR_fwd(speed);
   FR_fwd(speed);
   FL_bck(speed);
}

// --------- single wheel control ---------

void FR_fwd(int speed)  //front-right wheel forward turn
{
  digitalWrite(RightMotorDirPin1,HIGH);
  digitalWrite(RightMotorDirPin2,LOW); 
  analogWrite(speedPinR,speed);
}
void FR_bck(int speed) // front-right wheel backward turn
{
  digitalWrite(RightMotorDirPin1,LOW);
  digitalWrite(RightMotorDirPin2,HIGH); 
  analogWrite(speedPinR,speed);
}
void FL_fwd(int speed) // front-left wheel forward turn
{
  digitalWrite(LeftMotorDirPin1,HIGH);
  digitalWrite(LeftMotorDirPin2,LOW);
  analogWrite(speedPinL,speed);
}
void FL_bck(int speed) // front-left wheel backward turn
{
  digitalWrite(LeftMotorDirPin1,LOW);
  digitalWrite(LeftMotorDirPin2,HIGH);
  analogWrite(speedPinL,speed);
}

void RR_fwd(int speed)  //rear-right wheel forward turn
{
  digitalWrite(RightMotorDirPin1B, HIGH);
  digitalWrite(RightMotorDirPin2B,LOW); 
  analogWrite(speedPinRB,speed);
}
void RR_bck(int speed)  //rear-right wheel backward turn
{
  digitalWrite(RightMotorDirPin1B, LOW);
  digitalWrite(RightMotorDirPin2B,HIGH); 
  analogWrite(speedPinRB,speed);
}
void RL_fwd(int speed)  //rear-left wheel forward turn
{
  digitalWrite(LeftMotorDirPin1B,HIGH);
  digitalWrite(LeftMotorDirPin2B,LOW);
  analogWrite(speedPinLB,speed);
}
void RL_bck(int speed)    //rear-left wheel backward turn
{
  digitalWrite(LeftMotorDirPin1B,LOW);
  digitalWrite(LeftMotorDirPin2B,HIGH);
  analogWrite(speedPinLB,speed);
}
 
void stop_Stop()    //Stop
{
  analogWrite(speedPinLB,0);
  analogWrite(speedPinRB,0);
  analogWrite(speedPinL,0);
  analogWrite(speedPinR,0);
}

//Pins initialize
void init_GPIO()
{
  pinMode(RightMotorDirPin1, OUTPUT); 
  pinMode(RightMotorDirPin2, OUTPUT); 
  pinMode(speedPinL, OUTPUT);  
 
  pinMode(LeftMotorDirPin1, OUTPUT);
  pinMode(LeftMotorDirPin2, OUTPUT); 
  pinMode(speedPinR, OUTPUT);
  pinMode(RightMotorDirPin1B, OUTPUT); 
  pinMode(RightMotorDirPin2B, OUTPUT); 
  pinMode(speedPinLB, OUTPUT);  
 
  pinMode(LeftMotorDirPin1B, OUTPUT);
  pinMode(LeftMotorDirPin2B, OUTPUT); 
  pinMode(speedPinRB, OUTPUT);

  stop_Stop();
}

void setup()
{
  Serial1.begin(9600);  // UART1 communication with Jetson Nano
  Serial.begin(9600);
  init_GPIO();
  delay (1000);
  Serial.println("GPIO init complete...");
 
  front(SPEED);
  delay(100);
  stop_Stop();
  delay(100);
  Serial.println("Advance movement complete...");
  
  back(SPEED);
  delay(100);
  stop_Stop();
  delay(100);
  Serial.println("Back movement complete...");

}

void loop(){

  delay(20);

  int speed = 100; 

  if (Serial1.available()) {
    String data = Serial1.readStringUntil('\n');

    // get the speed and trim
    int commaIndex = data.indexOf(',');
    if (commaIndex != -1) {
      String numberString = data.substring(commaIndex + 1);
      data = data.substring(0, commaIndex);
      speed = numberString.toInt();
    }

    //Serial.print("Received: ");
    //Serial.println(data);

    if(data.equals("front") || data.equals("f")){
      front(speed);
    }

    else if(data.equals("stop") || data.equals("s")){
      stop_Stop();
    }

    else if(data.equals("back") || data.equals("b")){
      back(speed);
    } 

    else if(data.equals("front_diagonal_left") || data.equals("fdl")){
      FL_fwd(speed);
      RR_fwd(speed);
    }

    else if(data.equals("front_diagonal_right") || data.equals("fdr")){
      FR_fwd(speed);
      RL_fwd(speed);
    }

    else if(data.equals("back_diagonal_left") || data.equals("bdl")){
      FR_bck(speed);
      RL_bck(speed);
    }

    else if(data.equals("back_diagonal_right") || data.equals("bdr")){
      FL_bck(speed);
      RR_bck(speed);
    }

    else if(data.equals("turn_left") || data.equals("tl")){
      rot_left(speed);
    }

    else if(data.equals("smooth_turn_left") || data.equals("stl")){
      FL_fwd(speed-60);
      FR_fwd(speed+50);
      RR_fwd(speed+100);
      RL_fwd(speed-40);
    }

    else if(data.equals("smooth_turn_right") || data.equals("str")){
      FR_fwd(speed-60);
      FL_fwd(speed+50);
      RL_fwd(speed+100);
      RR_fwd(speed-40);
    }

    else if(data.equals("turn_right") || data.equals("tr")){
      rot_right(speed);
    } 

    else if(data.equals("rotate_right") || data.equals("rr")){
      rot_right(speed);
    } 

    else if(data.equals("rotate_left") || data.equals("rl")){
      rot_left(speed);
    }

    else if(data.equals("shift_left") || data.equals("sl")){
      left_shift(speed,speed,speed,speed);
    }

    else if(data.equals("shift_right") || data.equals("sr")){
      right_shift(speed,speed,speed,speed);
    }

    else {
      Serial1.println("Invalid command");
    }

    delay(100);
    stop_Stop();

  }
    // Echo back the received data
    // Serial1.print(data);
}
