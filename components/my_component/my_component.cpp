#include "esphome/core/log.h"
#include "my_component.h"

namespace esphome {
namespace my_component {

static const char *TAG = "my_component.component";

void MyComponent::setup() {
    ESP_LOGI(TAG, "My Component is setup");
}

void MyComponent::loop() {
    ESP_LOGI(TAG, "My Component is Here");
}

void MyComponent::dump_config(){
    ESP_LOGCONFIG(TAG, "My component");
}


}  // namespace My_component
}  // namespace esphome