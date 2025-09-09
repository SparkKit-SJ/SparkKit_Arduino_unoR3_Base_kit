
/*
 模块：          RCWL-9610 16MM分体式开放式超声波测距模块 
 版本：          V2.0
 日期：          20220710
 主控芯片：       RCWL-9610
 功能：          IIC模式下RCWL-9610超声波测距模块测距并串口显示
 注意：          需要设置模块在IIC模式
 测试板：         RCWL-3310
 编写：          无锡日晨物联科技有限公司
 方案定制：       13915288564
 IIC数据格式：    RCWL-9610的IIC输出3个8BIT数据，距离MM值=24位数据转换成10进制/10000。
 连线：
   -VCC               = 3.3V/5.5V
   -Trig_RX_SCL_I/O   = A5
   -Echo_TX_SDA       = A4
   -GND               = GND
*/

#include "SoftwareSerial.h"
#include <Wire.h> 
float               distance = 0;                       //距离数据十进制值
float               ds[3];                              //3个8BIT距离数据

void setup()
{
  Serial.begin(9600);                                   //定义串口波特率9600 出厂默认波特率9600
  Wire.begin();
  Serial.println("RCWL-9610 测距开始："); 
}

void loop() 
{
   char i = 0;
    ds[0]=0;
    ds[1]=0;
    ds[2]=0;                                            //初始化3个8BIT距离数据为0
    
   Wire.beginTransmission(0x57);                        //地址为0X57 写8位数据为AE，读8位数据位AF
   Wire.write(1);                                       //写命令0X01,0X01为开始测量命令 
   Wire.endTransmission();                              //IIC结束命令 
           
   delay(150);                                          //测量周期延时，一个周期为120mS,设置150MS,留余量    
   
   Wire.requestFrom(0x57,3);                            //地址为0X57 读3个8位距离数据       
    while (Wire.available())
    {
     ds[i++] = Wire.read();
    }        
    
   distance=(ds[0]*65536+ds[1]*256+ds[2])/10000;        //计算成CM值     
   Serial.print("距离："); 
   
   if ((1<=distance)&&(distance<=900))                  //1CM-9M之间数值显示 
    {
     #if 0
     Serial.println();    
     Serial.print(ds[0]);
     Serial.println();    
     Serial.print(ds[1]);
     Serial.println();    
     Serial.print(ds[2]);    
     Serial.println();      
     #endif                                             //#if 1，输出IIC的3个距离数据
     
    Serial.print(distance);
    Serial.print(" CM ");  
    }
   else 
    {
     Serial.println();    
     Serial.print(ds[0]);
     Serial.println();    
     Serial.print(ds[1]);
     Serial.println();    
     Serial.print(ds[2]);    
     Serial.println();  
      
    Serial.print(" - - - - ");                          //无效数值数值显示 - - - - 
    }
  
    Serial.println();                                   //换行
    
    delay(20);                                          //单次测离完成后加30mS的延时再进行下次测量。防止近距离测量时，测量到上次余波，导致测量不准确。
    delay(100);                                         //延时200mS再次测量，延时可不要
}
