
#include <avr/interrupt.h>

#include "NovaStepperCtrler.h"


#ifndef PI
#define PI 3.14159265f
#endif

#ifndef EPSILON
#define EPSILON 0.0001f
#endif


#define PRESCALER 256

static NovaStepperCtrler* CtrlerInstancePtr = (NovaStepperCtrler*)0;

static volatile uint16_t left_toggle_value;
static volatile uint16_t right_toggle_value;


// Timer2 compare match interrupt handler
ISR(OC2A_vect)
{
  static uint8_t left_counter, right_counter;

  left_counter++;
  right_counter++;

  if (left_counter >= left_toggle_value)
  {
    left_counter = 0;
    CtrlerInstancePtr->tick(NovaStepperCtrler::MOTOR_L);
  }

  if (right_counter >= right_toggle_value)
  {
    right_counter = 0;
    CtrlerInstancePtr->tick(NovaStepperCtrler::MOTOR_R);
  }
}



NovaStepperCtrler::NovaStepperCtrler()
{
}


void NovaStepperCtrler::init(int left_clk_pin, int right_clk_pin, int left_dir_pin, int right_dir_pin, float wheel_radius, int counts_per_rev)
{
  _clk_pin[MOTOR_L] = left_clk_pin;
  _clk_pin[MOTOR_R] = right_clk_pin;

  _dir_pin[MOTOR_L] = left_dir_pin;
  _dir_pin[MOTOR_R] = right_dir_pin;

  _wheel_radius = wheel_radius;
  _counts_per_rev = counts_per_rev;

  cli();

  // Initilize timer2 - CTC mode, PRESCALER=256, compare match interrupt enabled with rate = fclk_IO / (N * (1 + OCRnx))
  TCCR2A = _BV(WGM21);              // CTC
  TCCR2B = _BV(CS22) | _BV(CS21);   // PRESCALER=256
  OCR2A = 0;                        // compare match interrupt freq = F_CPU / (PRESCALER * (1 + 0))

  CtrlerInstancePtr = this;

  sei();
}


void NovaStepperCtrler::tick(MOTOR_IDX motor)
{
  if (_curr_dir[motor] == DIR_STOP)
  {
    return;
  }
  else if (digitalRead(_clk_pin[motor]) == 0)
  {
    digitalWrite(_clk_pin[motor], 1);
    _encoder[motor] += (_curr_dir[motor] == DIR_REV)? -1 : 1;

    if (_encoder[motor] >= _counts_per_rev)
    {
      _encoder[motor] -= _counts_per_rev;
    }
    else if (_encoder[motor] < 0)
    {
      _encoder[motor] += _counts_per_rev;
    }
  }
  else
  {
    digitalWrite(_clk_pin[motor], 0);
  }
}


void NovaStepperCtrler::setVelocity(MOTOR_IDX motor, float vel)
{
  if (vel < -EPSILON)
  {
    _curr_dir[motor] == DIR_REV;
    vel = - vel;
  }
  else if (vel > EPSILON)
  {
    _curr_dir[motor] == DIR_FWD;
  }
  else
  {
    _curr_dir[motor] == DIR_STOP;
  }

  // Convert velocity in m/s to motor clock frequency
  float freq = vel / (PI * _wheel_radius) * _counts_per_rev;

  // counter value for toggle clk pin = compare match interrupt rate / (freq * 2) - 1
  int32_t toggle_value = F_CPU / PRESCALER / (uint32_t)(freq * 2) - 1;

  if (toggle_value < 0)
  {
    toggle_value = 0;
  }
  else if (toggle_value > 65535)
  {
    toggle_value = 65535;
  }

  if (motor == MOTOR_L)
  {
    cli();
    left_toggle_value = (uint16_t)toggle_value;
    sei();
  }
  else
  {
    cli();
    right_toggle_value = (uint16_t)toggle_value;
    sei();
  }
}


uint16_t NovaStepperCtrler::getEncoder(MOTOR_IDX motor)
{
  uint16_t ret;

  cli();
  ret = _encoder[motor];
  sei();

  return ret;
}