#pragma once

#include "esphome/core/component.h"

namespace esphome {
namespace my_component {

class MyComponent : public Component {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;
};


}  // namespace My_component
}  // namespace esphome