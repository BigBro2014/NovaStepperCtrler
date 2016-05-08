# Dual Stepper Controller With Virtual Encoder For Arduino UNO/Leonardo

### Brief:
NovaStepperCtrler is a arduino based Dual Stepper Controller for robots that uses Timer2(or Timer3 for leanardo).
It has virtual encoders for each motor, whose resolution eaquals to step count of full revolution.

### Member Functions
- init(uint8_t left_clk_pin, uint8_t right_clk_pin, uint8_t left_dir_pin, uint8_t right_dir_pin, float wheel_radius, int16_t counts_per_rev, CLK_RATE clk_rate=CLK_15625HZ):
  Set clk pins, dir pins, wheel radius(in 'm'), counts per rev(200 or 400) & clock rate(CLK_15625HZ or CLK_31250HZ or CLK_62500HZ, higher takes more CPU time but has higher resolution)

  Suppose v as velocity, c as internal counter value
  v = clk_rate / 2 / counts_per_rev * PI * wheel_radius / c
  c = clk_rate / 2 / counts_per_rev * PI * wheel_radius / v

  velocity resolution = dv/dc
                      = -(clk_rate / 2 / counts_per_rev * PI * wheel_radius) / (c * c)
                      = -v / c
                      = -v / (clk_rate / 2 / counts_per_rev * PI * wheel_radius / v)
                      = -v * v / (clk_rate / 2 / counts_per_rev * PI * wheel_radius)
                      = -2 * v * v * counts_per_rev / clk_rate / PI / wheel_radius


  vmax = clk_rate / 2 / counts_per_rev * PI * wheel_radius
  vmin = clk_rate / 2 / counts_per_rev * PI * wheel_radius / 65535

- setVelocity(MOTOR_IDX motor, float vel):
  Set velocity(in 'm/s') of specified motor(NovaStepperCtrler::MOTOR_L or NovaStepperCtrler::MOTOR_R)


- getEncoder(MOTOR_IDX motor):
  Get encoder value(between [0, counts_per_rev)) of specified motor(NovaStepperCtrler::MOTOR_L or NovaStepperCtrler::MOTOR_R)



### Usage:

```
#include <NovaStepperCtrler.h>


// Define motor dir pins here
#define LEFT_CLK_PIN  2
#define RIGHT_CLK_PIN 3
#define LEFT_DIR_PIN  4
#define RIGHT_DIR_PIN 5


#define WHEEL_RADIUS 0.1f
#define COUNTS_PER_REV 200


NovaStepperCtrler ctrler;
ctrler.init(LEFT_CLK_PIN, RIGHT_CLK_PIN, LEFT_DIR_PIN, RIGHT_DIR_PIN, WHEEL_RADIUS, COUNTS_PER_REV, NovaStepperCtrler::CLK_31250HZ);

...

ctrler.setVelocity(NovaStepperCtrler::MOTOR_L, vel_left);
ctrler.setVelocity(NovaStepperCtrler::MOTOR_R, vel_right);

...

uint16_t encoders_left = ctrler.getEncoder(NovaStepperCtrler::MOTOR_L);
uint16_t encoders_right = ctrler.getEncoder(NovaStepperCtrler::MOTOR_R);

...
```