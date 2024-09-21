import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, output
from esphome.const import CONF_ID

proportional_ns = cg.esphome_ns.namespace("proportional")
Proportional = proportional_ns.class_("Proportional", cg.Component)

IS_PLATFORM_COMPONENT = True

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(Proportional)
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)