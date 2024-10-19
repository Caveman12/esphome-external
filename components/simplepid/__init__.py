import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, output, binary_sensor
from esphome.const import (
    CONF_ID
)

simplepid_ns = cg.esphome_ns.namespace("simplepid")
SimplePID = simplepid_ns.class_("SimplePID", cg.Component)
 
CONF_ID = "id"
CONF_P = "p"
CONF_I = "i"
CONF_BIAS = "bias"
CONF_DEADBAND = "deadband"
CONF_SETPOINT = "setpoint_variable"
CONF_CONTROL_VARIABLE = "control_variable"
CONF_DIRECTION = "direction"
CONF_ENABLE = "enable"
# Add Enable Sensor or binary here.

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(CONF_ID): cv.declare_id(SimplePID),
        cv.Required(CONF_P): cv.float_,
        cv.Required(CONF_SETPOINT): cv.float_, # Could this be a sensor or does it need to be something else? Could we use a number?
        cv.Required(CONF_CONTROL_VARIABLE): cv.use_id(sensor.Sensor),
        cv.Optional(CONF_I): cv.float_,
        cv.Optional(CONF_BIAS): cv.float_range(0.0, 100.0, True, True),
        cv.Optional(CONF_DEADBAND, default=0.0): cv.float_,
        cv.Optional(CONF_DIRECTION): cv.boolean,
        cv.Optional(CONF_ENABLE):  cv.use_id(binary_sensor.BinarySensor)
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)

    sens = await cg.get_variable(config[CONF_CONTROL_VARIABLE])
    cg.add(var.set_control_sensor(sens))

    cg.add(var.set_setpoint_variable(config[CONF_SETPOINT]))
    cg.add(var.set_p(config[CONF_P]))
    
    if CONF_I in config:
        cg.add(var.set_i(config[CONF_I]))
    
    if CONF_BIAS in config:
        cg.add(var.set_bias(config[CONF_BIAS]))

    if CONF_DIRECTION in config:
        cg.add(var.set_direction(config[CONF_DIRECTION]))
    
    if CONF_ENABLE in config:
        enab = await cg.get_variable(config[CONF_ENABLE])
        cg.add(var.set_enable_sensor(enab))
    else:
        cg.add(var.set_enable_sensor("nullptr"))