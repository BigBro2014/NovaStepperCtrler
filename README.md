# Dual Stepper Controller With Virtual Encoder For Arduino UNO

### Usage:

```
#include <NovaStepperCtrler.h>


// Define motor dir pins here
#define LEFT_CLK_PIN  2
#define RIGHT_CLK_PIN 3
#define LEFT_DIR_PIN  4
#define RIGHT_DIR_PIN 5

// Connect motors:
// Pin11(OC2A)    -- CLK_L
// Pin3 (OC2B)    -- CLK_R
// LEFT_DIR_PIN   -- DIR_L
// RIGHT_DIR_PIN  -- DIR_R

#define WHEEL_RADIUS 0.1f
#define COUNTS_PER_REV 1600


NovaStepperCtrler ctrler;
ctrler.init(LEFT_CLK_PIN, RIGHT_CLK_PIN, LEFT_DIR_PIN, RIGHT_DIR_PIN, WHEEL_RADIUS, COUNTS_PER_REV);

...

ctrler.setVelocity(NovaStepperCtrler::MOTOR_L, vel_left);
ctrler.setVelocity(NovaStepperCtrler::MOTOR_R, vel_right);

...

uint16_t encoders_left = ctrler.getEncoder(NovaStepperCtrler::MOTOR_L);
uint16_t encoders_right = ctrler.getEncoder(NovaStepperCtrler::MOTOR_R);

...
```