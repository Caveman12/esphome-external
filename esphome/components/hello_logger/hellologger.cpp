#include "esphome/core/helpers.h"
#include "esphome/core/log.h"
#include "hellologger.h"

namespace esphome {
namespace hellologger{

    static const char *TAG = "hellologger.component";

    void setup(){
    }

    void loop() {

    }

    void HelloLogger::dump_config(){
        ESP_LOGCONFIG(TAG, "Empty component");
    }

}  // namespace hellologger
}  // namespace esphome
