#include "esphome/core/log.h"
#include "simplepid.h"

namespace esphome {
namespace simplepid {

static const char *TAG = "simplepid";

void SimplePID::setup() {
    this->control_sensor->add_on_state_callback( [this](float state) {
        this->control_variable = state;
        this->error_calc();
        this->compute_output();
        this->publish_state();
    });

    ESP_LOGD(TAG, "Simple PID Setup");
}

void SimplePID::loop() {

}

void SimplePID::dump_config() {
    ESP_LOGCONFIG(TAG, "Simple PID:");
    ESP_LOGCONFIG(TAG, "  Propotional: %.1f", get_p());
    ESP_LOGCONFIG(TAG, "  Integral: %.1f", get_i());
    ESP_LOGCONFIG(TAG, "  Bias: %.1f", get_bias());
    ESP_LOGCONFIG(TAG, "  Setpoint: %.1f", get_setpoint_variable());
}

void SimplePID::error_calc() {
    if(this->control_sensor != nullptr){ // Add enable check here
        this->error_value=this->control_variable - this->setpoint_variable;
    }
    else {
        ESP_LOGV(TAG, "Control Sensor is Null Pointer");
    }
}

void SimplePID::compute_output() {
    if(this->control_sensor != nullptr){ // Add enable check here
        this->output = this->p_*this->error_value;
    }
    else {
        this->output=0.0;
        ESP_LOGV(TAG, "Control Sensor is Null Pointer");
    }
}

void SimplePID::publish_state() {
    ESP_LOGD(TAG, "Simple PID - State:");
    ESP_LOGD(TAG, "  Error: %.1f", this->error_value);
    ESP_LOGD(TAG, "  Output: %.1f", this->output);
}

}  // namespace simplepid
}  // namespace esphome