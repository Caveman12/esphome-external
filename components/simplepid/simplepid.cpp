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
    this->enable_sensor->add_on_state_callback( [this](float state) {
        this->enable = state;
        if (this->enable) {
            this->error_calc();
        }
        this->compute_output();
        this->publish_state();
    });

    ESP_LOGD(TAG, "Simple PID Setup");
}

void SimplePID::loop() {

}

void SimplePID::dump_config() {
    ESP_LOGCONFIG(TAG, "Simple PID:");
    ESP_LOGCONFIG(TAG, "  Control Variable: %s", this->control_sensor->get_name());
    ESP_LOGCONFIG(TAG, "  Setpoint: %.1f", get_setpoint_variable());
    if (this->direction_action) {
        ESP_LOGCONFIG(TAG, "  Direction: Direct Acting");
    }
    else {
        ESP_LOGCONFIG(TAG, "  Direction: Reverse Acting");
    }
    ESP_LOGCONFIG(TAG, "  Propotional: %.1f", get_p());
    if (!std::isnan(this->i_)) {
        ESP_LOGCONFIG(TAG, "  Integral: %.1f", get_i());
    }
    if (!std::isnan(this->db_)) {
        ESP_LOGCONFIG(TAG, "  Deadband: %.1f", get_db());
    }
    if (!std::isnan(this->bias_)) {
        ESP_LOGCONFIG(TAG, "  Bias: %.1f", get_bias());
    }
}

bool SimplePID::in_deadband() {
    return ( ( this->control_variable>this->get_setpoint_deadband_high() ) && ( this->control_variable<this->get_setpoint_deadband_low() ) );
}

void SimplePID::set_setpoint_deadband_high() {
    if (std::isnan(this->db_)) {
        this->setpoint_deadband_high = NAN;
    } else {
        this->setpoint_deadband_high = this->setpoint_variable+this->db_;
    }
}

void SimplePID::set_setpoint_deadband_low() {
    if (std::isnan(this->db_)) {
        this->setpoint_deadband_low = NAN;
    } else {
        this->setpoint_deadband_low = this->setpoint_variable-this->db_;
    }
}

void SimplePID::error_calc() {
    if(this->control_sensor != nullptr){ // Add enable check here
        
        if (in_deadband()) {
            // Check for inside Deadband
            // If inside Deadband Then return zero
            this->error_value = 0.0;

        }
        else if (this->direction_action)
        {
            // Direct Acting
            // As the Error Increases, the Output Increases
            // set error to correct value either above or below the deadband
            if (this->get_setpoint_deadband_high()<this->control_variable) {
                this->error_value = this->get_setpoint_deadband_high() - this->control_variable;
            } else {
                this->error_value = this->get_setpoint_deadband_low() - this->control_variable;
            }
        }
        else {
            // Reverse Acting
            // As the Error Increases, the Output Decreases
            // set error to correct value either above or below the deadband
            if (this->get_setpoint_deadband_high()<this->control_variable) {
                this->error_value = this->control_variable - this->get_setpoint_deadband_high();
            } else {
                this->error_value = this->control_variable - this->get_setpoint_deadband_low();
            }

        }   
    }
}

void SimplePID::compute_output() {
    if( (this->control_sensor != nullptr) && (this->enable) ) {
        float p_var = compute_propotional();
        float i_var = compute_integral();
        float temp_out = 0.0;
        
        // Check if a bias is being used
        if (!std::isnan(this->bias_)) {
            temp_out = p_var+this->bias_+i_var;
        }
        else {
            temp_out = p_var+i_var;
        }

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
    ESP_LOGD(TAG, "  Output: %.1f", this->output);
    if (this->enable) {
        ESP_LOGD(TAG, "  Enable: True");
        ESP_LOGD(TAG, "  Error: %.1f", this->error_value);
    }
    else {
        ESP_LOGD(TAG, "  Enable: False");
    }
    
}

float SimplePID::compute_propotional() { 
    return this->error_value*this->p_;
}

float SimplePID:: compute_integral() { // Need to setup rate calculation by frist creating the time function
    float temp_time = this->set_time_between_states();
    
    if (std::isnan(this->i_)) {
        return 0.0;
    }
     else if (this->direction_action)
    {
        // Direct Acting
        // As the Error Increases, the Output Increases
        if (this->error_value>0) {
            // Output Positive Value
            return (this->output)+((this->i_/60000)*(temp_time));
        }
        else {
            // Output Negative Value
            return (this->output)+(0-((this->i_/60000)*(temp_time)));
        }
        
    }
    else {
        // Reverse Acting
        // As the Error Increases, the Output Decreases
        if (this->error_value<0) {
            // Output Negative Value
            return (0-((this->i_/60000)*(temp_time)));
        }
        else {
            // Output Positive Value
            return ((this->i_/60000)*(temp_time));
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