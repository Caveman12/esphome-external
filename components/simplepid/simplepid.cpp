#include "esphome/core/log.h"
#include "simplepid.h"

namespace esphome {
namespace simplepid {

static const char *TAG = "simplepid";

void SimplePID::setup() {
    ESP_LOGI(TAG, "Simple PID Setup");
}

void SimplePID::loop() {

}

void SimplePID::dump_config(){
    ESP_LOGCONFIG(TAG, "Simple PID:");
    ESP_LOGCONFIG(TAG, "  Propotional: %.1f", get_p());
    ESP_LOGCONFIG(TAG, "  Integral: %.1f", get_i());
    ESP_LOGCONFIG(TAG, "  Bias: %.1f", get_bias());
}

void SimplePID::error_calc() {
    
}

void SimplePID::set_control_variable(sensor::Sensor *sensor) {

}

}  // namespace simplepid
}  // namespace esphome