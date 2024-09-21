import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, output
from esphome.const import CONF_ID, CONF_NAME

simple_pid_ns = cg.esphome_ns.namespace("simple_pid")
SimplePID = simple_pid_ns.class_("SimplePID", cg.Component)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(SimplePID),
        cv.Optional(CONF_NAME)
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID, CONF_NAME])
    await cg.register_component(var, config)