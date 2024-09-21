#pragma once

#include "esphome/core/component.h"

namespace esphome {
namespace simple_pid {

class SimplePID : public Component {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;
};


}  // namespace simpe_pid
}  // namespace esphome