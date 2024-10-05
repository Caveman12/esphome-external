#include "esphome/core/log.h"
#include "simplepid.h"

namespace esphome {
namespace simplepid {

static const char *TAG = "simplepid";

void SimplePID::setup() {
    this->control_sensor->add_on_state_callback( [this](float state) {
        this->control_variable = state;
        this->error_calc();
        this->compute_output();
        this->publish_state();
    });

    ESP_LOGD(TAG, "Simple PID Setup");
}

void SimplePID::loop() {

}

void SimplePID::dump_config() {
    ESP_LOGCONFIG(TAG, "Simple PID:");
    ESP_LOGCONFIG(TAG, "  Propotional: %.1f", get_p());
    ESP_LOGCONFIG(TAG, "  Integral: %.1f", get_i());
    ESP_LOGCONFIG(TAG, "  Bias: %.1f", get_bias());
    ESP_LOGCONFIG(TAG, "  Setpoint: %.1f", get_setpoint_variable());
}

void SimplePID::error_calc() {
    if(this->control_sensor != nullptr){ // Add enable check here

        if (this->direction_action)
        {
            // Direct Acting
            // As the Error Increases, the Output Increases
            this->error_value=this->control_variable - this->setpoint_variable;
        
        }
        else {
            // Reverse Acting
            // As the Error Increases, the Output Decreases
            this->error_value=this->setpoint_variable - this->control_variable;

        }   
    }
}

void SimplePID::compute_output() {
    if(this->control_sensor != nullptr) { // Add enable check here
        float p_var = compute_propotional();
        float i_var = compute_integral(); 
        float temp_out = p_var+i_var;
        
        // Add enable If statement here to return 0.0
        if (0 < temp_out && temp_out < 100) {
            this->output = temp_out;
        }
        else if ( temp_out > 100 ) {
            this->output = 100.0;
        }
        else {
            this->output = 0.0;
        }
    }
    else {
        this->output=0.0;
        ESP_LOGV(TAG, "Control Sensor is Null Pointer");
    }
}

// Need to work on this.
void SimplePID::publish_state() {
    ESP_LOGD(TAG, "Simple PID - State:");
    ESP_LOGD(TAG, "  Error: %.1f", this->error_value);
    ESP_LOGD(TAG, "  Output: %.1f", this->output);
}

float SimplePID::compute_propotional() { 
    return this->error_value*this->p_;
}

float SimplePID:: compute_integral() { // Need to setup rate calculation by frist creating the time function
    float temp_time = this->set_time_between_states();
    
    if (this->direction_action)
    {
        // Direct Acting
        // As the Error Increases, the Output Increases
        if (this->error_value>0) {
            // Output Positive Value
            return ((this->i_/60000)*(temp_time));
        }
        else {
            // Output Negative Value
            return (0-((this->i_/60000)*(temp_time)));
        }
        
    }
    else {
        // Reverse Acting
        // As the Error Increases, the Output Decreases
        if (this->error_value<0) {
            // Output Positive Value
            return 0.0;
        }
        else {
            // Output Negative Value
            return 0.0;
        }

    }
}

float SimplePID::set_time_between_states() {
    uint32_t now = millis();
    uint32_t deltat = now - this->last_cycle;

    this->last_cycle = now;

    return deltat / 1000.0f; // Shopuld return ms
}

}  // namespace simplepid
}  // namespace esphome