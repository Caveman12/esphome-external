#include "esphome/core/helpers.h"
#include "esphome/core/log.h"

namespace esphome {
namespace hellologger{

    static const char* const TAG = "component.hellologger";

    void setup(){
        ESP_LOGI(TAG, 'Hello');
    }

    void loop() {

    }


}  // namespace hellologger
}  // namespace esphome
