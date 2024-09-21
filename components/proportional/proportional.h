#pragma once

#include "esphome/core/component.h"
#include "components/simple_pid/simplepid.h"

namespace esphome {
namespace proportional {

class Proportional : public SimplePID {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;
};


}  // namespace proportional
}  // namespace esphome