#include <NovaStepperCtrler.h>


// Define motor dir pins here
#define LEFT_CLK_PIN  2
#define RIGHT_CLK_PIN 3
#define LEFT_DIR_PIN  4
#define RIGHT_DIR_PIN 5


#define WHEEL_RADIUS 0.1f
#define COUNTS_PER_REV 1600


NovaStepperCtrler ctrler;
float vel_left, vel_right;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  ctrler.init(LEFT_CLK_PIN, RIGHT_CLK_PIN, LEFT_DIR_PIN, RIGHT_DIR_PIN, WHEEL_RADIUS, COUNTS_PER_REV);
  
  vel_left = 0;
  vel_right = 0;
}

void loop() {
  // put your main code here, to run repeatedly:
  
  ctrler.setVelocity(NovaStepperCtrler::MOTOR_L, vel_left);
  ctrler.setVelocity(NovaStepperCtrler::MOTOR_R, vel_right);
  
  delay(1000);
  
  uint16_t encoders_left = ctrler.getEncoder(NovaStepperCtrler::MOTOR_L);
  uint16_t encoders_right = ctrler.getEncoder(NovaStepperCtrler::MOTOR_R);
  
  Serial.println(encoders_left);
  Serial.println(encoders_left);
}
