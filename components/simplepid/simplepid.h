#pragma once

#include "esphome/core/component.h"

namespace esphome {
namespace simplepid {

class SimplePID : public Component  {

 public:

  // Base Functions. From ESPHome templates
  void setup() override;
  void loop() override;
  void dump_config() override;

  // Calculation Functions
  //void error_calc();

  // Set Parameters Functions
  void set_p(float proportional) {(*this).p_=proportional;}
  void set_i(float integral) {(*this).i_=integral;}
  void set_d(float derviative) {(*this).d_= derviative;}
  void set_bias(float bias) {(*this).bias_ = bias;}

  // Get Parameters Functions
  float get_p() {return (*this).p_;}
  float get_i() {return (*this).i_;}
  float get_bias() {return (*this).bias_;}

 private:
  // Input variables
  float p_ = 0.0; //unit value where the output will be 100%
  float i_ = 0.0; //integral rate per Minute
  float d_ = 0.0; //NOT USED
  float bias_ = 0.0;

  // Output Values
  float output = 0.0;
  
  
};


}  // namespace simplepid
}  // namespace esphome