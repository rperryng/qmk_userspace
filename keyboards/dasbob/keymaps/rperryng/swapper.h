#pragma once

#include "quantum.h"
#include QMK_KEYBOARD_H
#include "keymap.h"      // Include keymap definitions

// Implements cmd-tab like behaviour on a single key. On first tap of trigger
// cmdish is held and tabish is tapped -- cmdish then remains held until the
// specified layer key is released.
//
// This behaviour is useful for more than just cmd-tab, hence: cmdish, tabish.
void update_swapper(
    bool *active,
    uint16_t cmdish,
    uint16_t tabish,
    uint16_t trigger,
    uint16_t layer_key,
    uint16_t keycode,
    keyrecord_t *record
);

// Handles the reverse swapper functionality that works in conjunction with other swappers
// Returns true if the key should be processed further, false if it should be ignored
bool update_reverse_swapper(
    bool *sw_ctrl_active,
    bool *sw_alt_active,
    bool *sw_win_active,
    uint16_t trigger,
    uint16_t keycode,
    keyrecord_t *record
);
