import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, output
from esphome.const import (
    CONF_ID
)

simplepid_ns = cg.esphome_ns.namespace("simplepid")
SimplePID = simplepid_ns.class_("SimplePID", cg.Component)
 
CONF_P = "p"
CONF_I = "i"
CONF_BIAS = "bias"
CONF_DEADBAND = "deadband"
CONF_SETPOINT = "setpoint_variable"
CONF_CONTROL_VARIABLE = "control_variable"
# Add Enable Sensor or binary here.

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(SimplePID),
        cv.Required(CONF_P): cv.float_,
        cv.Required(CONF_SETPOINT): cv.float_, # Could this be a sensor or does it need to be something else? Could we use a number?
        cv.Required(CONF_CONTROL_VARIABLE): cv.use_id(sensor.Sensor),
        cv.Optional(CONF_I, default=0.0): cv.float_,
        cv.Optional(CONF_BIAS, default=0.0): cv.float_range(0.0, 100.0, True, True),
        cv.Optional(CONF_DEADBAND, default=0.0): cv.float_
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    cg.add(var.set_p(config[CONF_P]))
    cg.add(var.set_i(config[CONF_I]))
    cg.add(var.set_bias(config[CONF_BIAS]))
    cg.add(var.set_setpoint_variable(config[CONF_SETPOINT]))

    sens = await cg.get_variable(config[CONF_CONTROL_VARIABLE])
    cg.add(var.set_control_sensor(sens))