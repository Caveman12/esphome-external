#include "esphome/core/log.h"
#include "proportional.h"

namespace esphome {
namespace proportional {

static const char *TAG = "proportional";

void Proportional::setup() {
    ESP_LOGI(TAG, "Proportional Only");
}

void Proportional::loop() {

}

void Proportional::dump_config(){
    ESP_LOGCONFIG(TAG, "Proportional Only");
}


}  // namespace Proportional
}  // namespace esphome