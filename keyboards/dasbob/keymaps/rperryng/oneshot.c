#include "print.h"
#include "oneshot.h"

void update_oneshot(
    oneshot_state *state,
    uint16_t mod,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            // Trigger keydown
            if (*state == os_up_unqueued) {
                register_code(mod);
            }
            *state = os_down_unused;
            dprintf("trigger down (on?), mod: %d, ? -> os_down_unused\n", mod);
        } else {
            // Trigger keyup
            switch (*state) {
            case os_down_unused:
                // If we didn't use the mod while trigger was held, queue it.
                *state = os_up_queued;
                dprintf("trigger up, mod: %d, os_down_unused -> os_up_queued\n", mod);
                break;
            case os_down_used:
                // If we did use the mod while trigger was held, unregister it.
                *state = os_up_unqueued;
                unregister_code(mod);
                dprintf("trigger up (off), mod: %d, os_down_used -> os_up_unqueued\n", mod);
                break;
            default:
                break;
            }
        }
    } else {
        if (record->event.pressed) {
            if (is_oneshot_cancel_key(keycode) && *state != os_up_unqueued) {
                // Cancel oneshot on designated cancel keydown.
                *state = os_up_unqueued;
                unregister_code(mod);
                dprintf("cancel (off), mod: %d, ? -> os_up_unqueued\n", mod);
            }
            if (!is_oneshot_ignored_key(keycode)) {
                switch (*state) {
                case os_up_queued:
                    *state = os_up_queued_used;
                    dprintf("key up (off), mod: %d, os_up_queued -> os_up_queued_used\n", mod);
                    break;
                case os_up_queued_used:
                    *state = os_up_unqueued;
                    unregister_code(mod);
                    dprintf("key up (off), mod: %d, os_up_queued_used -> os_up_unqueued\n", mod);
                    break;
                default:
                    break;
                }
            }
        } else {
            if (!is_oneshot_ignored_key(keycode)) {
                // On non-ignored keyup, consider the oneshot used.
                switch (*state) {
                case os_down_unused:
                    *state = os_down_used;
                    dprintf("key up, mod: %d, os_down_unused -> os_down_used\n", mod);
                    break;
                case os_up_queued:
                    *state = os_up_unqueued;
                    unregister_code(mod);
                    dprintf("key up (off), mod: %d, os_up_queued -> os_up_unqueued\n", mod);
                    break;
                case os_up_queued_used:
                    *state = os_up_unqueued;
                    unregister_code(mod);
                    dprintf("key up (off), mod: %d, os_up_queued_used -> os_up_unqueued\n", mod);
                    break;
                default:
                    break;
                }
            }
        }
    }
}

bool update_oneshot_layer(
    oneshot_state *state,
    uint16_t layer,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            // Trigger keydown
            if (*state == os_up_unqueued) {
                layer_on(layer);
            }
            *state = os_down_unused;
            dprintf("trigger down (on?), layer: %d, ? -> os_down_unused\n", layer);
            return false;
        } else {
            // Trigger keyup
            switch (*state) {
            case os_down_unused:
                // If we didn't use the layer while trigger was held, queue it.
                *state = os_up_queued;
                dprintf("trigger up, layer: %d, os_down_unused -> os_up_queued\n", layer);
                return false;
            case os_down_used:
                // If we did use the layer while trigger was held, turn off it.
                *state = os_up_unqueued;
                layer_off(layer);
                dprintf("trigger up (off), layer: %d, os_down_used -> os_up_unqueued\n", layer);
                return false;
            default:
                break;
            }
        }
    } else {
        if (record->event.pressed) {
            if (is_oneshot_layer_cancel_key(keycode) && *state != os_up_unqueued) {
                // Cancel oneshot layer on designated cancel keydown.
                *state = os_up_unqueued;
                layer_off(layer);
                dprintf("cancel (off), layer: %d, ? -> os_up_unqueued\n", layer);
                return false;
            }
            uint8_t key_layer = read_source_layers_cache(record->event.key);
            if (key_layer == layer) {
                // On non-ignored keyup, consider the oneshot used.
                switch (*state) {
                case os_down_unused:
                    *state = os_down_used;
                    dprintf("key down, layer: %d, os_down_unused -> os_down_used\n", layer);
                    return true;
                case os_up_queued:
                    if (is_oneshot_mod_key(keycode)) {
                        *state = os_up_unqueued;
                        layer_off(layer);
                        dprintf("key down, layer: %d, os_up_queued -> os_up_unqueued\n", layer);
                        return false;
                    } else {
                        *state = os_up_queued_used;
                        dprintf("key down, layer: %d, os_up_queued -> os_up_queued_used\n", layer);
                    }
                    return true;
               case os_up_queued_used:
                    *state = os_up_unqueued;
                    layer_off(layer);
                    dprintf("key down (off), layer: %d, os_up_queued_used -> os_up_unqueued\n", layer);
                    return false;
                default:
                    break;
                }
            }
        } else {
            // Ignore key ups from other layers
            uint8_t key_layer = read_source_layers_cache(record->event.key);
            if (key_layer == layer) {
                // On non-ignored keyup, consider the oneshot used.
                switch (*state) {
                case os_up_queued:
                    *state = os_up_unqueued;
                    layer_off(layer);
                    dprintf("key up (off), layer: %d, os_up_queued -> os_up_unqueued\n", layer);
                    return true;
                case os_up_queued_used:
                    *state = os_up_unqueued;
                    layer_off(layer);
                    dprintf("key up (off), layer: %d, os_up_queued_used -> os_up_unqueued\n", layer);
                    return true;
                default:
                    break;
                }
            }
        }
    }
    return true;
}

bool update_oneshot_hyper(
    oneshot_state *shft_state,
    oneshot_state *ctrl_state,
    oneshot_state *alt_state,
    oneshot_state *cmd_state,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            // Queue up all modifiers at once
            if (*shft_state == os_up_unqueued) {
                register_code(KC_LSFT);
                *shft_state = os_up_queued;
                dprintf("hyper: shift queued\n");
            }
            if (*ctrl_state == os_up_unqueued) {
                register_code(KC_LCTL);
                *ctrl_state = os_up_queued;
                dprintf("hyper: ctrl queued\n");
            }
            if (*alt_state == os_up_unqueued) {
                register_code(KC_LALT);
                *alt_state = os_up_queued;
                dprintf("hyper: alt queued\n");
            }
            if (*cmd_state == os_up_unqueued) {
                register_code(KC_LCMD);
                *cmd_state = os_up_queued;
                dprintf("hyper: cmd queued\n");
            }
        }
        return true;
    }
    return false;
}
