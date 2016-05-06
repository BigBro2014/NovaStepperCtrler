#pragma once

#include <stdint.h>
#include <arduino.h>

class NovaStepperCtrler
{
public:
  enum MOTOR_IDX
  {
    MOTOR_L = 0,
    MOTOR_R = 1
  };

  enum MOTOR_DIR
  {
    DIR_REV  = -1,
    DIR_STOP = 0,
    DIR_FWD  = 1
  };

  // Constructor
  NovaStepperCtrler();

  // Initialize
  void init(int left_clk_pin, int right_clk_pin, int left_dir_pin, int right_dir_pin, float wheel_radius, int counts_per_rev);
  
  // Set speed of specfic motor, vel>0 as froward, vel<0 as reverse
  void setVelocity(MOTOR_IDX motor, float vel);

  // Update clk output and virtual encoder value
  void tick(MOTOR_IDX motor);

  // Get virtual encoder value
  uint16_t getEncoder(MOTOR_IDX motor);

private:
  float _wheel_radius;            // wheel radius
  uint16_t _counts_per_rev;       // how many steps for a full turn
  uint8_t _clk_pin[2];            // clk pin for stepper motors
  uint8_t _dir_pin[2];            // dir pin for stepper motors
  uint8_t _curr_dir[2];           // current dir of stepper motors
  int16_t _encoder[2];            // holds virtual encoder value
};
