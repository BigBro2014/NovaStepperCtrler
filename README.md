# Dual Stepper Controller With Virtual Encoder For Arduino UNO

### Hardware Connection:
  - Pin11(OC2A) ---------- CLK_L
  - Pin3 (OC2B) ---------- CLK_R
  - LEFT_DIR_PIN ----- DIR_L
  - RIGHT_DIR_PIN ---- DIR_R

### Usage:

```
#include <NovaStepperCtrler.h>

// Define motor dir pins here
#define LEFT_DIR_PIN  6
#define RIGHT_DIR_PIN 7

NovaStepperCtrler ctrler(LEFT_DIR_PIN, RIGHT_DIR_PIN);

...

ctrler.SetVelocity(NovaStepperCtrler::MOTOR_L, vel_left);
ctrler.SetVelocity(NovaStepperCtrler::MOTOR_R, vel__right);

...

encoders_left = ctrler.GetEncoder(NovaStepperCtrler::MOTOR_L);
encoders_right = ctrler.GetEncoder(NovaStepperCtrler::MOTOR_R);

...
```