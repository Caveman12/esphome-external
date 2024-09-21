#pragma once

#include "esphome/core/component.h"

namespace esphome {
namespace simplepid {

class SimplePID : public Component  {

 public:

  // Main Functions
  void setup() override;
  void loop() override;
  void dump_config() override;

  // Set Parameters Functions
  void set_p(float proportional) {(*this).p_=proportional;}
  void set_i(float integral) {(*this).i_=integral;}

  // Get Parameters Functions
  float get_p() {return (*this).p_;}
  float get_i() {return (*this).i_;}

 private:
  float p_ = 0;
  float i_ = 0;
  
};


}  // namespace simplepid
}  // namespace esphome