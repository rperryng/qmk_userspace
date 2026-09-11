#pragma once

#include QMK_KEYBOARD_H

// Layer definitions (matching those in keymap.c)
enum layers {
    LA_BASE,

    // auto-activated on trackball movement
    LA_MOUSE,

    // tri-layers
    LA_SYMB_ALT,
    LA_NAVI,
    LA_NUM_ALT,

    // Keyball hardware config (CPI / auto-mouse-layer tuning)
    LA_KBC,

    // Function Keys
    LA_FUNC,

    // Media
    LA_MEDIA,
};

// Custom keycode enums (matching those in keymap.c)
enum keycodes {
    // oneshot mods
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,
    OS_CNCL,
    OS_HYPER,

    // oneshot layers
    OSL_FUNC,

    SW_WIN,
    SW_CTRL,
    SW_ALT,
    SW_REV,
    SW_WIN_GRAVE,
};
