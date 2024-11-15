#include "swapper.h"

void update_swapper(
    bool *active,
    uint16_t modifier,
    uint16_t tap_keycode,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
) {
    if (keycode == trigger) {
        if (record->event.pressed) {
            if (!*active) {
                *active = true;
                register_code(modifier);
            }
            register_code(tap_keycode);
        } else {
            unregister_code(tap_keycode);
            // Don't unregister modifier until some other key is hit or released.
        }
    } else if (*active) {
        unregister_code(modifier);
        *active = false;
    }
}
