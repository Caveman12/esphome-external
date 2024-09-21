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
  void set_p(float p){SimplePID.p_ = p}
  void set_i(float i){SimplePID.i_ = i}

 private:
  float p_ = 0;
  float i_ = 0;
  
};


}  // namespace simpepid
}  // namespace esphome