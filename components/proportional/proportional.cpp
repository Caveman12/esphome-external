#include "esphome/core/log.h"
#include "proportional.h"

namespace esphome {
namespace proportional {

static const char *TAG = "porportional";

void SimplePID::setup() {
    ESP_LOGI(TAG, "Proportional Setup");
}

void SimplePID::loop() {

}

void SimplePID::dump_config(){
    ESP_LOGCONFIG(TAG, "Proportional:");
} 

}  // namespace simplepid
}  // namespace esphome