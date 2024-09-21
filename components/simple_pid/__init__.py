import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, output
from esphome.const import CONF_ID

simple_pid_ns = cg.esphome_ns.namespace("simple_pid")
SimplePID = simple_pid_ns.class_("SimplePID", cg.EntityBase)

SIMPLEPID_SCHEMA = cv.ENTITY_BASE_SCHEMA.extend(
    {
        cv.GenerateID(): cv.declare_id(SimplePID)
    }
)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)