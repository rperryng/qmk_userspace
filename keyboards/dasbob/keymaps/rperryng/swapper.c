#include "swapper.h"
#include "keymap.h"  // Include the keymap to get layer information

void update_swapper(
    bool *active,
    uint16_t cmdish,
    uint16_t tabish,
    uint16_t trigger,
    uint16_t layer_key,   // The key that activates the layer
    uint8_t check_layer,  // The layer to check for active status
    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            if (!*active) {
                *active = true;
                register_code(cmdish);
            }
            register_code(tabish);
        } else {
            unregister_code(tabish);
            // Don't unregister cmdish until we leave the layer
        }
    } else if (keycode == layer_key && !record->event.pressed) {
        // When we release the layer key, release the switcher's modifier if it's active
        if (*active) {
            unregister_code(cmdish);
            *active = false;
        }
    }

    // Additionally, if we're not in the layer anymore, make sure to release the modifier
    if (!layer_state_is(check_layer) && *active) {
        unregister_code(cmdish);
        *active = false;
    }
}

bool update_reverse_swapper(
    bool *sw_ctrl_active,
    bool *sw_alt_active,
    bool *sw_win_active,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            // If any swapper is active, immediately send shift+tab
            if (*sw_ctrl_active || *sw_alt_active || *sw_win_active) {
                register_code(KC_LSFT);
                register_code(KC_TAB);
            }
        } else {
            // When releasing trigger, release shift+tab if any swapper was active
            if (*sw_ctrl_active || *sw_alt_active || *sw_win_active) {
                unregister_code(KC_LSFT);
                unregister_code(KC_TAB);
            }
        }
        return false; // Don't process this key further
    }
    return true; // Process this key further
}

