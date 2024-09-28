#include "esphome/core/log.h"
#include "simplepid.h"

namespace esphome {
namespace simplepid {

static const char *TAG = "simplepid";

void SimplePID::setup() {
    ESP_LOGI(TAG, "Simple PID Setup");
}

void SimplePID::loop() {
    this->error_calc();
    ESP_LOGI(TAG, "Error: %.1f", this->error_value);
}

void SimplePID::dump_config() {
    ESP_LOGCONFIG(TAG, "Simple PID:");
    ESP_LOGCONFIG(TAG, "  Propotional: %.1f", get_p());
    ESP_LOGCONFIG(TAG, "  Integral: %.1f", get_i());
    ESP_LOGCONFIG(TAG, "  Bias: %.1f", get_bias());
}

void SimplePID::error_calc() {
    if(this->control_sensor != nullptr){ // Add enable check here
        (*this).error_value=1.0;
    }
}

void SimplePID::compute_control_variable() {

}

}  // namespace simplepid
}  // namespace esphome