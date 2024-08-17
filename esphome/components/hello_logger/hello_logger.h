#pragma once

#include <utility>
#include "esphome/components/binary_sensor.h"
#include "esphome/core/automation.h"
#include "esphome/core/component.h"

// based on https://github.com/m5stack/M5Unit-MiniEncoderC/blob/main/src/Unit_MiniEncoderC.cpp
// https://docs.m5stack.com/en/hat/MiniEncoderC%20Hat

namespace esphome {
namespace hellologger{

    class HelloLogger : public component{

    public:
        void setup() override;
        void loop() override;
        void dump_config() override;
    
    }
}  // namespace hellologger
}  // namespace esphome