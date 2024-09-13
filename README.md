## Language

- [English](#english)
- [中文](#中文)

---

### English

AlexBot Mini is our open-source bipedal robots, designed with enhanced performance and a more rational structure. We have developed a complete set of open-source hardware for the robot, including the driving system, which allows it to walk dynamically. While it may not match the performance of commercial robots like the Unitree H1, our design is open-source and cost-effective.

<div style="text-align: center;">
    <img src="https://github.com/Alexhuge1/Alexbot/assets/79268846/a2eb591e-d456-4b0f-b197-b859c2b0c155" alt="run">
</div>

### Mechanical & Structure

Our robot features a leg with five joints: a 3-DOF hip joint, a 1-DOF knee joint, and a 1-DOF ankle joint. To reduce the overall inertia of the lower leg, we have moved the knee joint motor to the hip area. We use the Daimiao DM-J8009 for the hip joint of the thigh, with a rated torque of 20Nm and a peak torque of 40Nm. Other joints use DM-J8006, and the ankle joint uses DM-J6006. The mechanical design was done in SolidWorks 2021, with topological optimization and structural finite element simulation using Altair Inspire. The thigh parts are CNC machined, with an estimated cost of around 5000 RMB.

<div style="text-align: center;">
    <img alt="Mechanical Design" src="https://github.com/Alexhuge1/Alexbot/assets/79268846/150308cd-8ca5-4cd7-801d-cbc1b5fc478d">
</div>

### Hardware & Actuators

The hardware includes an STM32H7B0 core board with a 9-axis gyroscope for outer loop control. The upper computer uses an NVIDIA Jetson Xavier NX, and we are considering whether the TX2 could also be suitable. The entire circuit includes two power distribution boards, a control board with the STM32H7B0VBT6 as the core, and the Jetson Xavier NX as the upper computer. The power supply provides 24V to the motors, with a step-down module to provide 5V and 19V for the control board and Jetson Xavier NX, respectively.

<div style="text-align: center;">
    <img alt="Hardware Overview" src="https://github.com/Alexhuge1/Alexbot/assets/79268846/45d509cd-a820-4300-86af-de6eaf1d7879">
</div>

### Imitation Learning, Full-Body MPC, and WBC

Our gait planning is showing promising results, and the team responsible for the algorithms has successfully made the robot walk. We have adjusted the joint limits in the URDF file according to the electrical control specifications, which can be viewed using the MuJoCo viewer.

<div style="text-align: center;">
    <img alt="Gait Planning" src="https://github.com/Alexhuge1/Alexbot/assets/79268846/ca007be0-8ff4-47b6-8b23-acb9bd97a089">
</div>

### Pricing

The total cost of the robot is estimated to be around 20,000 RMB. We have negotiated a price with Daimiao Motors, and they have agreed to provide the complete set of motors for 10,500 RMB, including a USB-to-CAN module and an H723 development board. The machining cost is estimated to be 6,000 RMB, and adding the Jetson and various bearings and standard parts, the total cost should be around 20,000 RMB.

### Documentation

Our open-source documentation includes中期文档和PPT, which are available for download. For more detailed technical information, please refer to our [Zhihu article](https://zhuanlan.zhihu.com/p/69235601413).

### Community

Our WeChat group has reached its maximum capacity, and we are now using an invitation-only system. If you are interested in joining, please contact YYXAwesome, and we will invite you to the group. Several individuals have already successfully replicated our robot, and we will update the BOM as needed.


---

### 中文

AlexBot是我们开源双足机器人的下一代产品，设计上注重提升性能和结构合理性。我们为机器人开发了一整套开源硬件，包括驱动系统，使其能够动态行走。虽然它的性能可能无法与Unitree H1等商业机器人相媲美，但我们的设计是开源且成本效益高的。

<div style="text-align: center;">
    <img alt="运行图" src="https://github.com/Alexhuge1/Alexbot/assets/79268846/a2eb591e-d456-4b0f-b197-b859c2b0c155">
</div>

#### 机械与结构

我们的机器人腿部设计有五个关节：3自由度的髋关节、1自由度的膝关节和1自由度的踝关节。为了降低小腿的整体惯量，我们将膝关节电机上移至髋部。我们使用达妙DM-J8009作为大腿的髋关节电机，额定扭矩为20Nm，峰值扭矩为40Nm。其他关节使用DM-J8006，踝关节使用DM-J6006。机械设计是在SolidWorks 2021中完成的，采用了拓扑优化和结构有限元仿真，使用的是Altair Inspire。大腿部分采用CNC加工，预计成本约为5000元人民币。

<div style="text-align: center;">
    <img alt="机械设计图" src="https://github.com/Alexhuge1/Alexbot/assets/79268846/150308cd-8ca5-4cd7-801d-cbc1b5fc478d">
</div>

#### 硬件与驱动器

硬件部分主要包括一个集成了九轴陀螺仪的STM32H7B0核心板，用于外环控制。上位机使用了英伟达的Jetson Xavier NX作为主电脑，我们也在考虑是否TX2也能够胜任。整个电路包括两个分电板、一个以STM32H7B0VBT6为核心的控制板和Jetson Xavier NX。电源为电机提供24V电压，并通过降压模块为控制板和Jetson Xavier NX提供5V和19V电压。

<div style="text-align: center;">
    <img alt="硬件概览" src="https://github.com/Alexhuge1/Alexbot/assets/79268846/45d509cd-a820-4300-86af-de6eaf1d7879">
</div>

#### 模仿学习算法、全身MPC和WBC

我们的步态规划已经取得了初步成果，负责算法的团队已经成功让机器人行走。我们根据电控的限位要求调整了URDF文件中的关节限制，可以通过MuJoCo查看器查看。

<div style="text-align: center;">
    <img alt="步态规划" src="https://github.com/Alexhuge1/Alexbot/assets/79268846/ca007be0-8ff4-47b6-8b23-acb9bd97a089">
</div>

#### 价格部分

机器人的整体价格预计在20000元人民币左右。我们已经与达妙电机谈妥价格，他们同意以10500元人民币的价格提供整套电机，并附送USB转CAN模块和H723开发板。加工费用预计为6000元人民币，加上Jetson和各种轴承及标准件，总成本应该在20000元人民币左右。


我们的开源文档包括中期文档和PPT，可供下载。有关更详细的技术信息，请参阅我们的[知乎文章](https://zhuanlan.zhihu.com/p/69235601413)。

#### 社区

我们的微信群已满200人，现在采用邀请制度。如果你有兴趣加入，请联络YYXAwesome，我们会邀请你加入群组。已有数人成功复制了我们的机器人，我们将根据需要更新BOM。
