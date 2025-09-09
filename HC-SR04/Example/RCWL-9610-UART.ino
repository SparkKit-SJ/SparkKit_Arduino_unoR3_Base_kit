/*
 模块：          RCWL-9610 16MM分体式开放式超声波测距模块 
 版本：          V2.0
 日期：          20220710
 主控芯片：       RCWL-9610
 功能：          UART模式下RCWL-9610超声波测距模块测距并串口显示
 注意：          需要设置模块在UART模式
 测试板：         RCWL-3310
 编写：          无锡日晨物联科技有限公司
 方案定制：       13915288564
 IIC数据格式：    RCWL-9610串口输出3个8BIT数据，距离MM值=24位数据转换成10进制/10000。
 连线：
   -VCC               = 3.3V/5.5V
   -Trig_RX_SCL_I/O   = A5
   -Echo_TX_SDA       = A4
   -GND               = GND
*/

#include "SoftwareSerial.h"
SoftwareSerial mySerial(A4, A5);                      // A4为RX, A5为TX;  A4接模块TX,A5接模块RX
float     Data_h = 0;                                 //高8位数据
float     Data_m = 0;                                 //中8位数据
float     Data_l = 0;                                 //低8位数据
float     distance = 0;                               //距离数据十进制值

void setup()
{ 
  Serial.begin(9600);                                 //定义串口波特率9600 出厂默认波特率9600
  mySerial.begin(9600);                               //定义模拟串口波特率
  Serial.println("RCWL-9610-UART 测距开始："); 
}

void loop() 
{
    Data_h = 0;
    Data_m = 0;   
    Data_l = 0;
    distance=0;                                        //初始化3个8BIT距离数据和距离值为0
    
    mySerial.flush();                                  //清模拟串口缓存数据
    mySerial.write(0XA0);                              //发送开始测距命令0XA0，0XA0为开始测试命令数据
    
   delay(150);                                         //测量周期延时，一个周期为120mS,设置150MS,留余量  
     
   if (mySerial.available()>0)                         //等待接收完3个数据
   {
    Data_h= mySerial.read();                           //读取缓存数据
    Data_m= mySerial.read(); 
    Data_l= mySerial.read(); 
   }
  else
   {
    Data_h= 0;                                         //读不到缓存数据，数据清0
    Data_m= 0; 
    Data_l= 0;     
    }
    
   distance=(Data_h*65536+Data_m*256+Data_l)/10000;    //计算成CM值 
       
   Serial.print("距离：");                              //去掉该"距离："和"CM"可串口绘图
   
   if ((1<=distance)&&(900>=distance))                 //1CM-9M之间数值显示 
    {
   Serial.print(distance);
   Serial.print("CM");                                 //串口输出距离数据，去掉该"距离："和"CM"可串口绘图
    } 
   else 
    {
     Serial.println();    
     Serial.print(Data_h);
     Serial.println();    
     Serial.print(Data_m);P
     Serial.println();    
     Serial.print(Data_l);    
     Serial.println();      
   Serial.print(" - - - - ");                          //无效数值数值显示 - - - - 
    }
    Serial.println();                                  //换行
    
    delay(20);                                         //单次测离完成后加30mS的延时再进行下次测量。防止近距离测量时，测量到上次余波，导致测量不准确。
    delay(100);                                        //延时100mS再次测量，延时可不要
}
