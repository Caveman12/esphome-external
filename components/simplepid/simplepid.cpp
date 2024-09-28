#include "esphome/core/log.h"
#include "simplepid.h"

namespace esphome {
namespace simplepid {

static const char *TAG = "simplepid";

void SimplePID::setup() {
    this->control_sensor->add_on_state_callback([this](float state) {
        //Add setting the control variable
        this->publish_state();
    });
    ESP_LOGI(TAG, "Simple PID Setup");
}

void SimplePID::loop() {
    this->error_calc();
    ESP_LOGD(TAG, "Error: %.1f", this->error_value);
}

void SimplePID::dump_config() {
    ESP_LOGCONFIG(TAG, "Simple PID:");
    ESP_LOGCONFIG(TAG, "  Propotional: %.1f", get_p());
    ESP_LOGCONFIG(TAG, "  Integral: %.1f", get_i());
    ESP_LOGCONFIG(TAG, "  Bias: %.1f", get_bias());
    ESP_LOGCONFIG(TAG, "  Setpopint: %.1f", get_setpoint_variable());
}

void SimplePID::error_calc() {
    if(this->control_sensor != nullptr){ // Add enable check here
        this->error_value=control_variable - setpoint_variable;
    }
}

void SimplePID::compute_control_variable() {

}

}  // namespace simplepid
}  // namespace esphome