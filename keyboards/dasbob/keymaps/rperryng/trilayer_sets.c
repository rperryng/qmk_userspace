#include "trilayer_sets.h"

// Update trilayer state based on active configuration set
layer_state_t update_trilayer_state(
    layer_state_t state,
    uint8_t active_set
) {
    const trilayer_config_t *config = get_trilayer_config(active_set);
    return update_tri_layer_state(state, config->upper_layer, config->lower_layer, config->adjust_layer);
}

// Process trilayer-related keycodes
bool process_trilayer_keys(
    uint8_t *active_set,
    uint16_t cycle_keycode, uint16_t lower_keycode, uint16_t upper_keycode,
    uint16_t keycode, keyrecord_t *record
) {
    uint8_t set_count = get_trilayer_set_count();

    // Handle TLS_LOWER / TLS_UPPER
    if (keycode == lower_keycode) {
        if (record->event.pressed) {
            layer_on(get_trilayer_config(*active_set)->lower_layer);
        } else {
            // Turn off all possible lower layers
            for (uint8_t i = 0; i < set_count; i++) {
                layer_off(get_trilayer_config(i)->lower_layer);
            }
        }
        return false;
    }

    if (keycode == upper_keycode) {
        if (record->event.pressed) {
            layer_on(get_trilayer_config(*active_set)->upper_layer);
        } else {
            // Turn off all possible upper layers
            for (uint8_t i = 0; i < set_count; i++) {
                layer_off(get_trilayer_config(i)->upper_layer);
            }
        }
        return false;
    }

    // Handle trilayer set cycling
    if (keycode == cycle_keycode && record->event.pressed) {
        *active_set = (*active_set + 1) % set_count;
        return false;
    }

    return true;
}
