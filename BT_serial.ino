#include <Herkulex.h>
#include <Servo.h>
#include <SoftwareSerial.h>
// 최대 각도 수정 + 압력 수정
  Servo linear;
  int n1=251; // 모터 ID
  int n2=252;
  int n3=250;
  int n4=253;
  int FSR_Pin2 = A0; //아날로그 핀 (압력센서)
  int FSR_Pin1 = A1;
  int val = analogRead(FSR_Pin1);
  int m1 = 650;
  int m2 = 550;
  
  //////////////////void setup////////////////////
void setup()  
  {
 linear.attach(9,900,2100); //제어 핀 9번으로 설정 최대 최소 신호 시간 설정
   delay(100);
  
  Serial3.begin(57600);      // 블루투스 통신 57600
  Herkulex.begin(57600,10,11); //시리얼 통신 57600, rx=10 and tx=11 
  Herkulex.reboot(n1);         //모터 재부팅
   delay(200);
  Herkulex.reboot(n2);
   delay(200);
  Herkulex.reboot(n3);
   delay(200);
  Herkulex.reboot(n4);
   delay(500);
  Herkulex.initialize(); //모터 초기화
   delay(1000);  
  Serial.println("Start");
  linear.writeMicroseconds(900);  // 리니어 모터 최대수축 900us 
  
  }
  
  /////////////////////void loop///////////////
void loop(){
  int in_data = Serial3.read();           //시리얼 통신을 변수에 입력
     
   /////////////// 하체 다리 펴기//////////////
   if(in_data == '1')                  
   {
   while(analogRead(FSR_Pin1) < 600)
   {
    
     Herkulex.moveOne(n1, m2, 500, LED_BLUE);  //n1 모터
       delay(50); 
     Herkulex.moveOne(n2, m2, 500, LED_BLUE);  //n2 모터
       delay(500);
     m2=m2+10;
       delay(500);
     if(m2>700)       // 모터 동작범위 제한//
       {
       m2=650;
       break;}        // 모터 동작범위 제한//
    else if(analogRead(FSR_Pin1) > 600) // 압력센서 일정값이 되면 m1 을 초기값으로 돌리고 정지
       {
        m2=650;
       break;}//
       }
    }
    /////////////// 하체 다리 펴기//////////////
    
    ////////////////몸통 늘리기////////////////
    else if(in_data == '2')           
    {
     linear.writeMicroseconds(2100); // 최대확장 2100us
    }
    ////////////////몸통 늘리기////////////////
    
    /////////////////상체 다리 펴기//////////////////
    else if(in_data == '3')         
    {
      while(analogRead(FSR_Pin2) < 600)
    {
    
     Herkulex.moveOne(n3, m1, 500, LED_BLUE);  //n3 모터
       delay(50); 
     Herkulex.moveOne(n4, m1, 500, LED_BLUE);  //n4 모터
       delay(500);
     m1=m1+10;
       delay(500);
    if(m1>830) // 최대 펴지는 넓이 제한//
       {
       m1=650;
       break;}  //
    else if(analogRead(FSR_Pin2) > 600) // 압력센서 일정값이 되면 m1 을 초기값으로 돌리고 정지
       {
        m1=650;
       break;}//
       }
    }
   /////////////////상체 다리 펴기//////////////////

   
   ///////////////////하체 다리 접기///////////////
    else if(in_data == '4')                   
    {
      int m1 = 650;  
     Herkulex.moveOne(n1, m1, 2000, LED_BLUE);  //n1 모터
     delay(50); 
     Herkulex.moveOne(n2, m1, 2000, LED_BLUE);  //n2 모터
       delay(2000);     
    }
    
    /////////////////몸통 줄이기///////////////////////
    else if(in_data == '5')           
    {
     linear.writeMicroseconds(900); // 최대수축 900us
    }
     /////////////////////상체 다리 접기///////////////
    else if(in_data == '6')                   
    {   
     int m1 = 650;
     Herkulex.moveOne(n3, m1, 2000, LED_BLUE);  //n3 모터
     delay(50); 
     Herkulex.moveOne(n4, m1, 2000, LED_BLUE);  //n4 모터
       delay(2000); 
           
    }
     /////////////// 전부 수축하고 접기 ///////////////////
    else if(in_data == '7')
    {
      int m1 = 650;
      int m2 = 560;
      Herkulex.moveOne(n3, m1, 2000, LED_BLUE);  //n3 모터
     delay(50); 
     Herkulex.moveOne(n4, m1, 2000, LED_BLUE);  //n4 모터
       delay(2000);
     linear.writeMicroseconds(900); // 최대수축 900us
     Herkulex.moveOne(n1, m2, 2000, LED_BLUE);  //n1 모터
       delay(50); 
     Herkulex.moveOne(n2, m2, 2000, LED_BLUE);  //n2 모터
       delay(2000);
    }
   }
