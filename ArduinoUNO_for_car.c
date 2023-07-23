#include <IRremote.h>
//舵机
int servopin = 2;  //设置舵机驱动脚到数字口2
int myangle;       //定义角度变量
int pulsewidth;    //定义脉宽变量
int val;
const int TrigPin = A0;
const int EchoPin = A1;
unsigned long distance=0;
//电机速度
#define speed 150
//小车速度控制引脚
int PWMA=10;
int PWMB=9;
//小车方向控制引脚
int INPUT1=11;
int INPUT3=8;
//小车行进状态
int stat=7;
//红外避障
int OUT_left=6;
int OUT_right=5;
int SR_left;//左避障红外传感器障碍
int SR_right;//右避障红外传感器障碍

//小车模式切换MODE=1为蓝牙控制，MODE=2为自主避障
int stat_mode=1;//默认为模式1
/**************************************设置****************************************/
void setup()
{
  //初始化电机驱动IO为输出方式
  pinMode(PWMA,OUTPUT);
  pinMode(PWMB,OUTPUT);
  pinMode(INPUT1,OUTPUT);
  pinMode(INPUT3,OUTPUT);
  //LED指示灯
  pinMode(13, OUTPUT);
  //超声波设置
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
  //舵机接口
  pinMode(servopin, OUTPUT);  //设定舵机接口为输出接口
  //红外避障
  pinMode(OUT_left,INPUT);
  pinMode(OUT_right,INPUT);
  //串口设置
  Serial.begin(9600);	
}

/***************************************舵机****************************************/
void servopulse(int servopin, int myangle) {
  pulsewidth = (myangle * 11) + 500;  //将角度转化为500-2480 的脉宽值
  digitalWrite(servopin, HIGH);       //将舵机接口电平置高
  delayMicroseconds(pulsewidth);      //延时脉宽值的微秒数
  digitalWrite(servopin, LOW);        //将舵机接口电平置低
  delay(20 - pulsewidth / 1000);      //延时周期内剩余时间
}

//让舵机转到指定角度
void servo_angle(int angle)
{
  for (int i = 0; i <= 50; i++)  //给予舵机足够的时间让它转到指定角度
  {
    servopulse(servopin, angle);
  }
}
/***************************************电机****************************************/
void run()
{
  digitalWrite(INPUT3,LOW);//左电机向前 
  analogWrite(PWMB,speed);
  digitalWrite(INPUT1,LOW);//右电机向前 
  analogWrite(PWMA,speed);
}

void back()
{
  digitalWrite(INPUT3,HIGH);//左电机向后 
  analogWrite(PWMB,speed);
  digitalWrite(INPUT1,HIGH);//右电机向后
  analogWrite(PWMA,speed);
}

void brake()
{
  digitalWrite(INPUT3,LOW); 
  analogWrite(PWMB,0);//左电机不动
  digitalWrite(INPUT1,LOW);
  analogWrite(PWMA,0);//右电机不动
}

void left()
{
  digitalWrite(INPUT3,LOW);
  analogWrite(PWMB,0);//左电机不动 
  digitalWrite(INPUT1,LOW);//右电机向前 
  analogWrite(PWMA,speed);
}

void right()
{
  digitalWrite(INPUT3,LOW);//左电机向前
  analogWrite(PWMB,speed); 
  digitalWrite(INPUT1,LOW); 
  analogWrite(PWMA,0);//右电机不动
}

void spin_left()
{
  digitalWrite(INPUT3,HIGH);//左电机向后
  analogWrite(PWMB,speed); 
  digitalWrite(INPUT1,LOW); //右电机向前
  analogWrite(PWMA,speed);
}

void spin_right()
{
  digitalWrite(INPUT3,LOW);//左电机向前
  analogWrite(PWMB,speed); 
  digitalWrite(INPUT1,HIGH); //右电机向后
  analogWrite(PWMA,speed);
}

/*******************************************超声波测距**************************************/
//超声波距离测量
void distance_measure()
{
  unsigned long temp;
  digitalWrite(TrigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(TrigPin, HIGH);
  delayMicroseconds(10);       // 产生一个10us的高脉冲去触发TrigPin
  digitalWrite(TrigPin, LOW);  // 检测脉冲宽度，并计算出距离
  temp = pulseIn(EchoPin, HIGH) / 58.00;
  if(temp<1000)
  {
    distance=temp;
  }
}

/******************************************红外避障*******************************/
void avoid()
{
  //左右红外避障
  SR_left=digitalRead(OUT_left);
  SR_right=digitalRead(OUT_right);
  //超声波测距
  distance_measure();
  if(distance >30)//正前方距离大于20cm
  {
    if(SR_left==HIGH & SR_right==HIGH)//前面没有障碍物
    {
      stat=1;//前进
    }
    else if(SR_left==HIGH & SR_right==LOW)//右边有障碍物
    {
      stat=5;//左旋转
    }
    else if(SR_left==LOW & SR_right==HIGH)//左边有障碍物
    {
      stat=6;//右旋转
    }
  } 
  else if(distance <=45)
  {
    if(SR_left==LOW & SR_right==LOW)//前面有障碍物
    {
      stat=7;//刹车
    }
    else if(SR_left==HIGH & SR_right==HIGH)//前面无障碍物
    {
      stat=5;//左旋转
    }
    else if(SR_left==HIGH & SR_right==LOW)//右边有障碍物
    {
      stat=5;//左旋转
    }
    else if(SR_left==LOW & SR_right==HIGH)//左边有障碍物
    {
      stat=6;//右旋转
    }
  }
}
/********************************************main*************************************/
void loop()
{
  //蓝牙控制小车模式切换
  while(Serial.available()){
    char c=Serial.read();
    if(stat_mode==1 & c=='F')//蓝牙控制模式
    {
      digitalWrite(13,HIGH); 
      stat=1;
    }
    else if(stat_mode==1 & c=='B')
    {
      digitalWrite(13,HIGH); 
      stat=2;
    }
    else if(stat_mode==1 & c=='L')
    {
      digitalWrite(13,HIGH); 
      stat=3;
    }
    else if(stat_mode==1 & c=='R')
    {
      digitalWrite(13,HIGH); 
      stat=4;
    }
    else if(stat_mode==1 & c=='l')
    {
      digitalWrite(13,HIGH); 
      stat=5;
    }
    else if(stat_mode==1 & c=='r')
    {
      digitalWrite(13,HIGH); 
      stat=6;
    }
    else if(stat_mode==1 & c=='S')
    {
      digitalWrite(13,HIGH); 
      stat=7;
    }
    else if(stat_mode==1 & c=='2')
    {
      digitalWrite(13,HIGH);
      stat=1;
      stat_mode=2;
    }
    else if(stat_mode==2 & c=='1')
    {
      digitalWrite(13,HIGH);
      stat=7;
      stat_mode=1;
    }
    digitalWrite(13,LOW);
  }
  
  switch(stat){
    case 1:
      run();
      break;
    case 2:
      back();
      break;
    case 3:
      left();
      break;
    case 4:
      right();
      break;
    case 5:
      spin_left();
      break;
    case 6:
      spin_right();
      break;
    case 7:
      brake();
      break;
  }
  if(stat_mode==2)
  {
    avoid();
  }

}
