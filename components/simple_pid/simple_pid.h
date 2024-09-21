#pragma once

#include "esphome/core/component.h"

namespace esphome {
namespace simplepid {

class SimplePID : public Component {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;
};


}  // namespace simpepid
}  // namespace esphome