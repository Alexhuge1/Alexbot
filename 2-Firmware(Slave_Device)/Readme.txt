How to use the code
leg02包含了USART01与上位机(Jetson)通讯、CAN1接左腿五电机级联、CAN2接右腿五电机级联、SPI通讯接受BMI088数据
包含了时钟，定时器等底层设计，同时进行了一些些简单的封装，方便基于函数开发，简单介绍一下程序架构：
1.在dm_driver.c中,其中电机使用MIT协议进行力控，使用void mit_ctrl(FDCAN_HandleTypeDef* hcan, uint16_t motor_id, float pos, float vel,float kp, float kd, float torq)来控制。
2.在Frame_function.c，写了上下位机通信的部分，包含了下位机的接收和发送，其中规定了帧的格式，如果传参变量发生修改请修改此函数。
3.在BMI088driver.c中，写了六轴加速度计的部分，包含了姿态解算得到姿态的欧拉角和加速度，同时还写了函数包含了使用四阶龙格库塔法来解算从欧拉角变到四元数。
----------------------------------------------------------------------------------------------
leg02 contains a USART01 and the host computer (Jetson) communication, CAN1 to the left leg of the five motor cascade, CAN2 to the right leg of the five motor cascade, SPI communication to accept BMI088 data.
Contains a clock, timer and other underlying design, while some of the simple package, to facilitate the development of function-based, simple introduction to the program structure:
1. in dm_driver.c, where the motor using the MIT protocol for force control, using void
 mit_ctrl(FDCAN_HandleTypeDef* hcan, uint16_t motor_id, float pos, float
 vel,float kp, float kd, float torq) to control.
2. In Frame_function.c, write the upper and lower computer communication part, including the lower computer to receive and send, which specifies the format of the frame, if the pass parameter variable is changed, please modify this function.
3. In BMI088driver.c, wrote the part of the six-axis accelerometer, which contains the attitude solving to get the Euler angle and acceleration of the attitude, and also wrote the function which contains the solving to change from Euler angle to quaternion by using the fourth-order Lunger Kuta method.


