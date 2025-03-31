#pragma once

#include QMK_KEYBOARD_H

// Layer definitions (matching those in keymap.c)
enum layers {
    LA_BASE,

    // Trilayer Sets
    LA_SYMB,
    LA_SYMB_ALT,
    LA_NAVI,
    LA_NUM,
    LA_NUM_ALT,

    // Mouse
    LA_MOUS,
    LA_MOUS_SCROL,

    // Function Keys
    LA_FUNC,
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

    TRILAYER_SET_NEXT,
    TLS_LOWER,
    TLS_UPPER,
};
