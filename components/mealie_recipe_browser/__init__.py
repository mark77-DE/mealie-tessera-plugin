"""Mealie recipe browser: ESPHome code generation for the Tessera plugin."""

import esphome.codegen as cg
import esphome.config_validation as cv
from esphome.components import smart_display
from esphome.const import CONF_ID

DEPENDENCIES = ["smart_display"]

CONF_CONFIG_ENTRY_ID = "config_entry_id"

mealie_ns = cg.esphome_ns.namespace("mealie_recipe_browser")
MealieRecipeBrowser = mealie_ns.class_("MealieRecipeBrowser", cg.Component)

CONFIG_SCHEMA = cv.Schema(
    {
        cv.GenerateID(): cv.declare_id(MealieRecipeBrowser),
        cv.Required(CONF_CONFIG_ENTRY_ID): cv.string,
    }
).extend(cv.COMPONENT_SCHEMA)


async def to_code(config):
    var = cg.new_Pvariable(config[CONF_ID])
    await cg.register_component(var, config)
    cg.add(var.set_config_entry_id(config[CONF_CONFIG_ENTRY_ID]))
    await smart_display.register_plugin(var, __file__)
