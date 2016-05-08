#pragma once

#include <stdint.h>
#include <arduino.h>

class NovaStepperCtrler
{
public:
  typedef enum
  {
    MOTOR_L = 0,
    MOTOR_R = 1
  } MOTOR_IDX;

  typedef enum
  {
    DIR_REV  = -1,
    DIR_STOP = 0,
    DIR_FWD  = 1
  } MOTOR_DIR;

  typedef enum
  {
    CLK_15625HZ,
    CLK_31250HZ,
    CLK_62500HZ
  } CLK_RATE;

  // Constructor
  NovaStepperCtrler();

  // Initialize
  // max_velocity = clk_rate / 2 / counts_per_rev * PI * wheel_radius
  // min_velocity = clk_rate / 2 / counts_per_rev * PI * wheel_radius / 65535
  void init(uint8_t left_clk_pin, uint8_t right_clk_pin, uint8_t left_dir_pin, uint8_t right_dir_pin, float wheel_radius, int16_t counts_per_rev, CLK_RATE clk_rate=CLK_15625HZ);

  // Set speed of specfic motor, vel>0.00001f as froward, vel<0.00001f as reverse, else stopped
  void setVelocity(MOTOR_IDX motor, float vel);

  // Update clk output and virtual encoder value
  void tick(MOTOR_IDX motor, uint8_t clk_output);

  // Get virtual encoder value
  uint16_t getEncoder(MOTOR_IDX motor);

private:
  float _wheel_radius;            // wheel radius
  int16_t _counts_per_rev;        // how many steps for a full turn
  // CLK_RATE _clk_rate;             // clk rate for stepper motors
  uint8_t _clk_pin[2];            // clk pin for stepper motors
  uint8_t _dir_pin[2];            // dir pin for stepper motors
  volatile int8_t _curr_dir[2];   // current dir of stepper motors
  volatile int16_t _encoder[2];   // holds virtual encoder value
};
