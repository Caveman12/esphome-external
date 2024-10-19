#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"
#include "esphome/core/hal.h"
#include "esphome/components/binary_sensor/binary_sensor.h"

#include <cmath>

namespace esphome {
namespace simplepid {

class SimplePID : public Component  {

 public:

  /* Base ESPHome Function Overrides */
  void setup() override;
  void loop() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::LATE; }

  /* Set Functions */
  void set_p(float proportional) {this->p_ = proportional;}
  void set_i(float integral) {this->i_ = integral;}
  void set_d(float derviative) {(*this).d_= derviative;}
  void set_bias(float bias) {(*this).bias_ = bias;}
  void set_deadband(float deadband) { this->db_ = deadband;}
  void set_control_sensor(sensor::Sensor *sensor) { this->control_sensor = sensor;}
  void set_direction(bool direction) {this->direction_action = direction;}
  void set_enable_sensor(binary_sensor:: BinarySensor *binarysensor);

  // Setpoint Calculations
  void set_setpoint_variable(float setpoint) {this->setpoint_variable = setpoint;}
  void set_setpoint_deadband_high();
  void set_setpoint_deadband_low();

  /* Calculation Functions */
  void error_calc();
  float set_time_between_states();
  void publish_state();
  void compute_output(); // Calcute output from 0-100%
  float compute_propotional(); // Calculate P protion of output
  float compute_integral(); // Calculate I protion of output

  /* Get Functions */
  float get_p() {return this->p_;}
  float get_i() {return this->i_;}
  float get_db() {return this->db_;}
  float get_bias() {return this->bias_;}

  /* Get Setpoints */
  float get_setpoint_variable() { return this->setpoint_variable; }
  float get_setpoint_deadband_high() { return this->setpoint_deadband_high; }
  float get_setpoint_deadband_low() { return this->setpoint_deadband_low; }

 private:
  // Input variables

  /* {p_} Propotional Constant
   * Currently - a propotion of the error
   * Future - based on linear offset from the value
   */
  float p_ = 0.0;

  /* {i_} Integral Constant
   * Step function increase as Rate per minute
   */
  float i_ = NAN;

  /* {d_} Dervivative Constant
   * Currently - Not Used
   * Future - Nothing Planned
   */
  float d_ = NAN;

  float bias_ = NAN;
  
  float db_ = NAN;

  bool in_deadband();

  /* Setpoint Values: */
  float setpoint_variable = 0.0;
  float setpoint_deadband_high = 0.0;
  float setpoint_deadband_low = 0.0;

  /* Control Variables */
  float control_variable = 0.0;
  
  /* {direction_action} Direction Action of the PID Loop
   * True = Direct Acting
   * False = Reverse Acting
   * 
   * Initialized as Direct Acting
   */
  bool direction_action = true;

  uint32_t last_cycle = 0;

  // Output Values
  float output = 0.0;
  float error_value = 0.0;

  //Sensor Values
  sensor::Sensor *control_sensor{nullptr};
  binary_sensor::BinarySensor *enable_sensor{nullptr};
  
  //Enable Goes here { Enable sets the output to zero}
  bool enable = false;
  
};

}  // namespace simplepid
}  // namespace esphome