# Dual Stepper Controller With Virtual Encoder For Arduino UNO/Leonardo - NOT FINISHED

### Class:
NovaStepperCtrler

### Member Functions
- init: Set clk pins, dir pins, wheel radius(in 'm'), counts per rev(between (0, 25600]) & clock rate(in CLK_15625HZ, CLK_31250HZ, CLK_62500HZ)
  max_velocity = clk_rate / 2 / counts_per_rev * PI * wheel_radius 
  min_velocity = clk_rate / 2 / counts_per_rev * PI * wheel_radius / 32768
  velocity_resolution = clk_rate / 2 / counts_per_rev * PI * wheel_radius / 2 ?

- setVelocity: Set velocity(in 'm/s') of specified motor(NovaStepperCtrler::MOTOR_L or NovaStepperCtrler::MOTOR_R)


- getEncoder: Get encoder value(between [0, counts_per_rev)) of specified motor(NovaStepperCtrler::MOTOR_L or NovaStepperCtrler::MOTOR_R)



### Usage:

```
#include <NovaStepperCtrler.h>


// Define motor dir pins here
#define LEFT_CLK_PIN  2
#define RIGHT_CLK_PIN 3
#define LEFT_DIR_PIN  4
#define RIGHT_DIR_PIN 5


#define WHEEL_RADIUS 0.1f
#define COUNTS_PER_REV 1600


NovaStepperCtrler ctrler;
ctrler.init(LEFT_CLK_PIN, RIGHT_CLK_PIN, LEFT_DIR_PIN, RIGHT_DIR_PIN, WHEEL_RADIUS, COUNTS_PER_REV, NovaStepperCtrler::CLK_15625HZ);

...

ctrler.setVelocity(NovaStepperCtrler::MOTOR_L, vel_left);
ctrler.setVelocity(NovaStepperCtrler::MOTOR_R, vel_right);

...

uint16_t encoders_left = ctrler.getEncoder(NovaStepperCtrler::MOTOR_L);
uint16_t encoders_right = ctrler.getEncoder(NovaStepperCtrler::MOTOR_R);

...
```