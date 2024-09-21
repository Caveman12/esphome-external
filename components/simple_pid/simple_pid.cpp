#include "esphome/core/log.h"
#include "simple_pid.h"

namespace esphome {
namespace simplepid {

static const char *TAG = "simplepid";

void SimplePID::setup() {
    ESP_LOGI(TAG, "Simple PID Setup");
}

void SimplePID::loop() {

}

void SimplePID::dump_config(){
    ESP_LOGCONFIG(TAG, "Simple PID Config");
}


}  // namespace simplepid
}  // namespace esphome