#pragma once

#include "esphome/core/component.h"
#include "simplepid/simplepid.h"

namespace esphome {
namespace proportional {

class SimplePID : public Component  {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;
};


}  // namespace simpepid
}  // namespace esphome