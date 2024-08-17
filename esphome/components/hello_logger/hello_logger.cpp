#include "esphome/core/helpers.h"
#include "esphome/core/log.h"

namespace esphome {
namespace hellologger{

    static const char *TAG = "hellologger.component";

    void setup(){
        ESP_LOGD(TAG, 'Hello Logger');
    }

    void loop() {

    }

    void hellologger::dump_config(){
        ESP_LOGCONFIG(TAG, "Empty component");
    }

}  // namespace hellologger
}  // namespace esphome
