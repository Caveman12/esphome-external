#include "esphome/core/log.h"
#include "simple_pid.h"

namespace esphome {
namespace simple_pid {

static const char *TAG = "simple_pid";

void SimplePID::setup() {
    ESP_LOGI(TAG, "Simple PID Setup");
}

void SimplePID::loop() {

}

void SimplePID::dump_config(){
    ESP_LOGCONFIG(TAG, "Simple PID Config");
}


}  // namespace SimplePID
}  // namespace esphome