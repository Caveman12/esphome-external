#pragma once

#include "esphome/core/component.h"
#include "esphome/components/sensor/sensor.h"

namespace esphome {
namespace simplepid {

class SimplePID : public Component  {

 public:

  // Base Functions. From ESPHome templates
  void setup() override;
  void loop() override;
  void dump_config() override;
  float get_setup_priority() const override { return setup_priority::LATE; }

  // Calculation Functions
  void error_calc();

  // Set Parameters Functions
  void set_p(float proportional) {(*this).p_=proportional;}
  void set_i(float integral) {(*this).i_=integral;}
  void set_d(float derviative) {(*this).d_= derviative;}
  void set_bias(float bias) {(*this).bias_ = bias;}
  void set_deadband(float deadband) { this->db_ = deadband;}
  void set_control_variable(sensor::Sensor *sensor) { this->control_sensor=sensor;}
  void set_setpoint_variable(float setpoint) {this->setpoint_variable = setpoint;}

  // Set Control Parameters
  void compute_control_variable();
  void publish_state();

  // Get Parameters Functions
  float get_p() {return (*this).p_;}
  float get_i() {return (*this).i_;}
  float get_bias() {return (*this).bias_;}
  float get_setpoint_variable() {return this->setpoint_variable;}

 private:
  // Input variables
  float p_ = 0.0; //unit value where the output will be 100%
  float i_ = 0.0; //integral rate per Minute
  float d_ = 0.0; //NOT USED
  float bias_ = 0.0;
  float db_ = 0.0;
  float setpoint_variable = 0.0;
  float control_variable = 0.0;

  // Output Values
  float output = 0.0;
  float error_value = 0.0;

  //Sensor Values
  sensor::Sensor *control_sensor{nullptr};
  
  //Enable Goes here { Enable sets the output to zero}
  
};

}  // namespace simplepid
}  // namespace esphome