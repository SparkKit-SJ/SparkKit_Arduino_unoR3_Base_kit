/*
 模块：          RCWL-9610 16MM分体式开放式超声波测距模块
 版本：          V2.0
 日期：          20220710 
 主控芯片：       RCWL-9610
 功能：          单总线模式下RCWL-9610超声波测距模块测距并串口显示
 注意：          需要设置模块在1-WIRE模式
 编写：          无锡日晨物联科技有限公司
 测试板：         RCWL-3310
 方案定制：       13915288564
 连线：
   -VCC               = 3.3V/5.5V
   -Trig_RX_SCL_I/O   = A5
   -Echo_TX_SDA       不接
   -GND               = GND
*/

float       distance;
const int   trig_echo=A5;                         //Trig_RX_SCL_I/O 接A5脚

void setup()
{
  Serial.begin(9600);                             //波特率9600
  pinMode(trig_echo,OUTPUT);                      //设置Trig_RX_SCL_I/O为输出
  Serial.println("RCWL-9610-1-WIRE 测距开始：");
}

void loop()
{
 pinMode(trig_echo,OUTPUT);                       //设置Trig_RX_SCL_I/O为输出
 
 digitalWrite(trig_echo,HIGH);
 delayMicroseconds(10);
 digitalWrite(trig_echo,LOW);                     //Trig_RX_SCL_I/O脚输出10US高电平脉冲触发信号     

 pinMode(trig_echo,INPUT);                        //设置Trig_RX_SCL_I/O为输入，接收模块反馈的距离信号
  
 distance  = pulseIn(trig_echo,HIGH);             //计数接收到的高电平时间
 //Serial.print("原始值: ");
 //Serial.print(distance);
 distance  = distance*340/2/10000;                //计算距离 1：声速：340M/S  2：实际距离为1/2声速距离 3：计数时钟为1US//温补公式：c=(331.45+0.61t/℃)m•s-1 (其中331.45是在0度）
 Serial.print("距离: ");
 Serial.print(distance);                          
 Serial.println("CM");                            //串口输出距离信号
 //digitalWrite(trig_echo,LOW);   
 pinMode(trig_echo,OUTPUT);                       //设置Trig_RX_SCL_I/O为输出，准备下次测量
 //Serial.println("");                            //换行
 delay(20);                                       //单次测离完成后加30mS的延时再进行下次测量。防止近距离测量时，测量到上次余波，导致测量不准确。
 delay(100);                                      //延时200mS再次测量，延时可不要
} 
