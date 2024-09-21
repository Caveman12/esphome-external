import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import sensor, output
from esphome.const import CONF_ID

proportional_ns = cg.esphome_ns.namespace("proportional")