#include "esphome/core/log.h"
#include "simple_pid.h"

namespace esphome {
namespace simple_pid {

static const char *TAG = "simple_pid";

void SimplePID::setup() {
    ESP_LOGI(TAG, "My Component is setup");
}

void SimplePID::loop() {

}

void SimplePID::dump_config(){
    ESP_LOGCONFIG(TAG, "My component");
}


}  // namespace SimplePID
}  // namespace esphome