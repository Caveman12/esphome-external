#pragma once

#include "esphome/core/component.h"
#include "esphome/core/entity_base.h"

namespace esphome {
namespace simplepid {

class SimplePID {
 public:
  void setup() override;
  void loop() override;
  void dump_config() override;
};


}  // namespace simpepid
}  // namespace esphome