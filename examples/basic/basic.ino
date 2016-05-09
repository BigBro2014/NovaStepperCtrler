#include <NovaStepperCtrler.h>


// Define motor dir pins here
#define LEFT_CLK_PIN  2
#define RIGHT_CLK_PIN 3
#define LEFT_DIR_PIN  4
#define RIGHT_DIR_PIN 5


#define WHEEL_RADIUS 0.1f
#define COUNTS_PER_REV 200

NovaStepperCtrler ctrler;
uint32_t curr_time = 0;
uint32_t last_time = 0;
uint16_t last_encoders_left = 0;
uint16_t last_encoders_right = 0;

void setup() {
  // put your setup code here, to run once:

  Serial.begin(115200);

  delay(10000);

  pinMode(LEFT_CLK_PIN, OUTPUT);
  pinMode(RIGHT_CLK_PIN, OUTPUT);
  pinMode(LEFT_DIR_PIN, OUTPUT);
  pinMode(RIGHT_DIR_PIN, OUTPUT);

  ctrler.init(LEFT_CLK_PIN, RIGHT_CLK_PIN, LEFT_DIR_PIN, RIGHT_DIR_PIN, WHEEL_RADIUS, COUNTS_PER_REV, NovaStepperCtrler::CLK_62500HZ);

  ctrler.setVelocity(NovaStepperCtrler::MOTOR_L, 0.7f);
  ctrler.setVelocity(NovaStepperCtrler::MOTOR_R, 0.9f);
}

void loop() {
  // put your main code here, to run repeatedly:

  delay(100);

  curr_time = millis();
  uint16_t encoders_left = ctrler.getEncoder(NovaStepperCtrler::MOTOR_L);
  uint16_t encoders_right = ctrler.getEncoder(NovaStepperCtrler::MOTOR_R);

  double diff;

  Serial.print("encoder: ");
  Serial.print(encoders_left);
  Serial.print(", ");
  Serial.println(encoders_right);

  Serial.print("real velocity: ");

  diff = (int32_t)encoders_left - last_encoders_left;
  if (diff < 0)
    diff += COUNTS_PER_REV;
  Serial.print(diff / COUNTS_PER_REV * PI * WHEEL_RADIUS * 1000 / (curr_time - last_time), 4);

  Serial.print(", ");

  diff = (int32_t)encoders_right - last_encoders_right;
  if (diff < 0)
    diff += COUNTS_PER_REV;
  Serial.println(diff / COUNTS_PER_REV * PI * WHEEL_RADIUS * 1000 / (curr_time - last_time), 4);

  last_time = curr_time;
  last_encoders_left = encoders_left;
  last_encoders_right = encoders_right;
}
