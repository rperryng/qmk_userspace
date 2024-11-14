/* Copyright 2020 ZSA Technology Labs, Inc <@zsa>
 * Copyright 2020 Jack Humbert <jack.humb@gmail.com>
 * Copyright 2020 Christopher Courtney, aka Drashna Jael're  (@drashna) <drashna@live.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */



#include QMK_KEYBOARD_H
#include "swapper.h"
#include "oneshot.h"
#include "version.h"

enum layers {
    BASE,
    SYM,
    NAV,
    MOUSE,
    NUM,
};

enum custom_keycodes {
    // callum oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,

    SW_WIN,
    SW_CTRL,
    SW_ALT,
};

// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    ┌──────┬─────┬─────┬─────┬───────────┬─────┬─────┐                                                                            ┌─────┬─────┬─────┬─────┬─────┬─────┬──────┐
//    │      │     │     │     │           │     │     │                                                                            │     │     │     │     │     │     │      │
//    ├──────┼─────┼─────┼─────┼───────────┼─────┼─────┤                                                                            ├─────┼─────┼─────┼─────┼─────┼─────┼──────┤
//    │ tab  │  q  │  w  │  f  │     p     │  b  │     │                                                                            │     │  j  │  l  │  u  │  y  │  ;  │ bspc │
//    ├──────┼─────┼─────┼─────┼───────────┼─────┼─────┤                                                                            ├─────┼─────┼─────┼─────┼─────┼─────┼──────┤
//    │ lctl │  a  │  r  │  s  │     t     │  g  │     │                                                                            │     │  m  │  n  │  e  │  i  │  o  │ esc  │
//    ├──────┼─────┼─────┼─────┼───────────┼─────┼─────┘                                                                            └─────┼─────┼─────┼─────┼─────┼─────┼──────┤
//    │ lsft │  z  │  x  │  c  │     d     │  v  │                                                                                        │  k  │  h  │  ,  │  .  │  /  │ rsft │
//    ├──────┼─────┼─────┼─────┼───────────┼─────┘                    ┌───────────────┐               ┌──────────────┐                    └─────┼─────┼─────┼─────┼─────┼──────┤
//    │      │     │     │     │ TO(MOUSE) │                          │               │               │              │                          │     │     │     │     │      │
//    └──────┴─────┴─────┴─────┴───────────┘           ┌──────────────┼───────────────┼─────┐   ┌─────┼──────────────┼──────────────┐           └─────┴─────┴─────┴─────┴──────┘
//                                                     │ LT(SYM, esc) │ LT(NAV, lgui) │     │   │     │ LT(NAV, ent) │ LT(SYM, spc) │
//                                                     └──────────────┴───────────────┴─────┘   └─────┴──────────────┴──────────────┘
[BASE] = LAYOUT(
  _______ , _______ , _______ , _______ , _______   , _______ , _______ ,                                                                                                  _______ , _______ , _______ , _______ , _______ , _______ , _______,
  KC_TAB  , KC_Q    , KC_W    , KC_F    , KC_P      , KC_B    , _______ ,                                                                                                  _______ , KC_J    , KC_L    , KC_U    , KC_Y    , KC_SCLN , KC_BSPC,
  KC_LCTL , KC_A    , KC_R    , KC_S    , KC_T      , KC_G    , _______ ,                                                                                                  _______ , KC_M    , KC_N    , KC_E    , KC_I    , KC_O    , KC_ESC ,
  KC_LSFT , KC_Z    , KC_X    , KC_C    , KC_D      , KC_V    ,                                                                                                                      KC_K    , KC_H    , KC_COMM , KC_DOT  , KC_SLSH , KC_RSFT,
  _______ , _______ , _______ , _______ , TO(MOUSE) ,                                       _______          ,                         _______         ,                                       _______ , _______ , _______ , _______ , _______,
                                                                          LT(SYM, KC_ESC) , LT(NAV, KC_LGUI) , _______ ,     _______ , LT(NAV, KC_ENT) , LT(SYM, KC_SPC)
),

//    ┌─────┬─────────┬─────────┬────────┬────────┬─────┬─────┐                                               ┌─────┬─────┬─────┬─────┬─────┬──────┬─────┐
//    │     │         │         │        │        │     │     │                                               │     │     │     │     │     │      │     │
//    ├─────┼─────────┼─────────┼────────┼────────┼─────┼─────┤                                               ├─────┼─────┼─────┼─────┼─────┼──────┼─────┤
//    │     │   esc   │    [    │   {    │   (    │  ^  │     │                                               │     │  $  │  )  │  }  │  ]  │ bspc │     │
//    ├─────┼─────────┼─────────┼────────┼────────┼─────┼─────┤                                               ├─────┼─────┼─────┼─────┼─────┼──────┼─────┤
//    │     │ OS_SHFT │ OS_CTRL │ OS_ALT │ OS_CMD │  @  │     │                                               │     │  +  │  -  │  _  │  |  │  =   │     │
//    ├─────┼─────────┼─────────┼────────┼────────┼─────┼─────┘                                               └─────┼─────┼─────┼─────┼─────┼──────┼─────┤
//    │     │         │    &    │   #    │   %    │  *  │                                                           │  ~  │  `  │  '  │  "  │  \   │     │
//    ├─────┼─────────┼─────────┼────────┼────────┼─────┘               ┌─────┐               ┌─────┐               └─────┼─────┼─────┼─────┼──────┼─────┤
//    │     │         │         │        │        │                     │     │               │     │                     │     │     │     │      │     │
//    └─────┴─────────┴─────────┴────────┴────────┘           ┌─────────┼─────┼─────┐   ┌─────┼─────┼─────────┐           └─────┴─────┴─────┴──────┴─────┘
//                                                            │ MO(NUM) │     │     │   │     │     │ MO(NUM) │
//                                                            └─────────┴─────┴─────┘   └─────┴─────┴─────────┘
[SYM] = LAYOUT(
  _______ , _______ , _______ , _______ , _______ , _______ , _______ ,                                                                 _______ , _______ , _______ , _______ , _______ , _______ , _______,
  _______ , KC_ESC  , KC_LBRC , KC_LCBR , KC_LPRN , KC_CIRC , _______ ,                                                                 _______ , KC_DLR  , KC_RPRN , KC_RCBR , KC_RBRC , KC_BSPC , _______,
  _______ , OS_SHFT , OS_CTRL , OS_ALT  , OS_CMD  , KC_AT   , _______ ,                                                                 _______ , KC_PLUS , KC_MINS , KC_UNDS , KC_PIPE , KC_EQL  , _______,
  _______ , _______ , KC_AMPR , KC_HASH , KC_PERC , KC_ASTR ,                                                                                     KC_TILD , KC_GRV  , KC_QUOT , KC_DQT  , KC_BSLS , _______,
  _______ , _______ , _______ , _______ , _______ ,                               _______ ,                         _______ ,                               _______ , _______ , _______ , _______ , _______,
                                                                        MO(NUM) , _______ , _______ ,     _______ , _______ , MO(NUM)
),

//    ┌─────┬─────────┬─────────┬────────┬────────┬─────┬─────┐                                               ┌─────┬──────┬──────┬──────┬──────┬──────┬─────┐
//    │     │         │         │        │        │     │     │                                               │     │      │      │      │      │      │     │
//    ├─────┼─────────┼─────────┼────────┼────────┼─────┼─────┤                                               ├─────┼──────┼──────┼──────┼──────┼──────┼─────┤
//    │     │         │         │        │        │     │     │                                               │     │ mprv │ vold │ volu │ mnxt │ mute │     │
//    ├─────┼─────────┼─────────┼────────┼────────┼─────┼─────┤                                               ├─────┼──────┼──────┼──────┼──────┼──────┼─────┤
//    │     │ OS_SHFT │ OS_CTRL │ OS_ALT │ OS_CMD │     │     │                                               │     │ left │ down │  up  │ rght │      │     │
//    ├─────┼─────────┼─────────┼────────┼────────┼─────┼─────┘                                               └─────┼──────┼──────┼──────┼──────┼──────┼─────┤
//    │     │         │ SW_CTRL │ SW_ALT │ SW_WIN │     │                                                           │ home │ tab  │      │ end  │      │     │
//    ├─────┼─────────┼─────────┼────────┼────────┼─────┘           ┌─────────┐               ┌─────────┐           └──────┼──────┼──────┼──────┼──────┼─────┤
//    │     │         │         │        │        │                 │         │               │         │                  │      │      │      │      │     │
//    └─────┴─────────┴─────────┴────────┴────────┘           ┌─────┼─────────┼─────┐   ┌─────┼─────────┼─────┐            └──────┴──────┴──────┴──────┴─────┘
//                                                            │     │ MO(NUM) │     │   │     │ MO(NUM) │     │
//                                                            └─────┴─────────┴─────┘   └─────┴─────────┴─────┘
[NAV] = LAYOUT(
  _______ , _______ , _______ , _______ , _______ , _______ , _______ ,                                                                 _______ , _______ , _______ , _______ , _______  , _______ , _______,
  _______ , _______ , _______ , _______ , _______ , _______ , _______ ,                                                                 _______ , KC_MPRV , KC_VOLD , KC_VOLU , KC_MNXT  , KC_MUTE , _______,
  _______ , OS_SHFT , OS_CTRL , OS_ALT  , OS_CMD  , _______ , _______ ,                                                                 _______ , KC_LEFT , KC_DOWN , KC_UP   , KC_RIGHT , _______ , _______,
  _______ , _______ , SW_CTRL , SW_ALT  , SW_WIN  , _______ ,                                                                                     KC_HOME , KC_TAB  , _______ , KC_END   , _______ , _______,
  _______ , _______ , _______ , _______ , _______ ,                               _______ ,                         _______ ,                               _______ , _______ , _______  , _______ , _______,
                                                                        _______ , MO(NUM) , _______ ,     _______ , MO(NUM) , _______
),

//    ┌─────┬─────┬─────────┬─────────┬─────────┬─────┬─────┐                                       ┌─────┬─────┬─────────┬─────────┬─────────┬─────┬─────┐
//    │     │     │         │         │         │     │     │                                       │     │     │         │         │         │     │     │
//    ├─────┼─────┼─────────┼─────────┼─────────┼─────┼─────┤                                       ├─────┼─────┼─────────┼─────────┼─────────┼─────┼─────┤
//    │     │ no  │   no    │  MS_UP  │   no    │ no  │     │                                       │     │ no  │   no    │   no    │   no    │ no  │     │
//    ├─────┼─────┼─────────┼─────────┼─────────┼─────┼─────┤                                       ├─────┼─────┼─────────┼─────────┼─────────┼─────┼─────┤
//    │     │ no  │ MS_LEFT │ MS_DOWN │ MS_RGHT │ no  │     │                                       │     │ no  │ MS_BTN1 │ MS_BTN2 │   no    │ no  │     │
//    ├─────┼─────┼─────────┼─────────┼─────────┼─────┼─────┘                                       └─────┼─────┼─────────┼─────────┼─────────┼─────┼─────┤
//    │     │ no  │   no    │   no    │   no    │ no  │                                                   │ no  │ MS_ACL2 │ MS_ACL1 │ MS_ACL0 │ no  │     │
//    ├─────┼─────┼─────────┼─────────┼─────────┼─────┘           ┌─────┐               ┌─────┐           └─────┼─────────┼─────────┼─────────┼─────┼─────┤
//    │     │     │         │         │         │                 │     │               │     │                 │         │         │         │     │     │
//    └─────┴─────┴─────────┴─────────┴─────────┘           ┌─────┼─────┼─────┐   ┌─────┼─────┼─────┐           └─────────┴─────────┴─────────┴─────┴─────┘
//                                                          │     │     │     │   │     │     │     │
//                                                          └─────┴─────┴─────┘   └─────┴─────┴─────┘
[MOUSE] = LAYOUT(
  _______ , _______ , _______ , _______ , _______ , _______ , _______ ,                                                                 _______ , _______ , _______ , _______ , _______ , _______ , _______,
  _______ , XXXXXXX , XXXXXXX , MS_UP   , XXXXXXX , XXXXXXX , _______ ,                                                                 _______ , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , _______,
  _______ , XXXXXXX , MS_LEFT , MS_DOWN , MS_RGHT , XXXXXXX , _______ ,                                                                 _______ , XXXXXXX , MS_BTN1 , MS_BTN2 , XXXXXXX , XXXXXXX , _______,
  _______ , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                                                                                     XXXXXXX , MS_ACL2 , MS_ACL1 , MS_ACL0 , XXXXXXX , _______,
  _______ , _______ , _______ , _______ , _______ ,                               _______ ,                         _______ ,                               _______ , _______ , _______ , _______ , _______,
                                                                        _______ , _______ , _______ ,     _______ , _______ , _______
),

//    ┌─────┬─────┬─────┬─────┬──────────┬─────┬─────┐                                       ┌─────┬─────┬─────┬─────┬─────┬─────────┬─────┐
//    │     │     │     │     │          │     │     │                                       │     │     │     │     │     │         │     │
//    ├─────┼─────┼─────┼─────┼──────────┼─────┼─────┤                                       ├─────┼─────┼─────┼─────┼─────┼─────────┼─────┤
//    │     │  1  │  2  │  3  │    4     │  5  │     │                                       │     │  6  │  7  │  8  │  9  │    0    │     │
//    ├─────┼─────┼─────┼─────┼──────────┼─────┼─────┤                                       ├─────┼─────┼─────┼─────┼─────┼─────────┼─────┤
//    │     │     │     │     │          │     │     │                                       │     │     │     │     │     │         │     │
//    ├─────┼─────┼─────┼─────┼──────────┼─────┼─────┘                                       └─────┼─────┼─────┼─────┼─────┼─────────┼─────┤
//    │     │     │     │     │ TO(BASE) │     │                                                   │     │     │     │     │ QK_BOOT │     │
//    ├─────┼─────┼─────┼─────┼──────────┼─────┘           ┌─────┐               ┌─────┐           └─────┼─────┼─────┼─────┼─────────┼─────┤
//    │     │     │     │     │          │                 │     │               │     │                 │     │     │     │         │     │
//    └─────┴─────┴─────┴─────┴──────────┘           ┌─────┼─────┼─────┐   ┌─────┼─────┼─────┐           └─────┴─────┴─────┴─────────┴─────┘
//                                                   │     │     │     │   │     │     │     │
//                                                   └─────┴─────┴─────┘   └─────┴─────┴─────┘
[NUM] = LAYOUT(
  _______ , _______ , _______ , _______ , _______  , _______ , _______ ,                                                                 _______ , _______ , _______ , _______ , _______ , _______ , _______,
  _______ , KC_1    , KC_2    , KC_3    , KC_4     , KC_5    , _______ ,                                                                 _______ , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , _______,
  _______ , _______ , _______ , _______ , _______  , _______ , _______ ,                                                                 _______ , _______ , _______ , _______ , _______ , _______ , _______,
  _______ , _______ , _______ , _______ , TO(BASE) , _______ ,                                                                                     _______ , _______ , _______ , _______ , QK_BOOT , _______,
  _______ , _______ , _______ , _______ , _______  ,                               _______ ,                         _______ ,                               _______ , _______ , _______ , _______ , _______,
                                                                         _______ , _______ , _______ ,     _______ , _______ , _______
)
};

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case MO(SYM):
    case MO(NAV):
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case KC_ESC:
    case MO(SYM):
    case MO(NAV):
    case KC_LSFT:
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_CMD:
        return true;
    default:
        return false;
    }
}

bool sw_win_active = false;
bool sw_ctrl_active = false;
bool sw_alt_active = false;

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Update swapper state
    update_swapper(
        &sw_win_active, KC_LGUI, KC_TAB, SW_WIN,
        keycode, record
    );
    update_swapper(
        &sw_alt_active, KC_LALT, KC_TAB, SW_ALT,
        keycode, record
    );
    update_swapper(
        &sw_ctrl_active, KC_LCTL, KC_TAB, SW_CTRL,
        keycode, record
    );

    // Update one-shot state
    update_oneshot(
        &os_shft_state, KC_LSFT, OS_SHFT,
        keycode, record
    );
    update_oneshot(
        &os_ctrl_state, KC_LCTL, OS_CTRL,
        keycode, record
    );
    update_oneshot(
        &os_alt_state, KC_LALT, OS_ALT,
        keycode, record
    );
    update_oneshot(
        &os_cmd_state, KC_LCMD, OS_CMD,
        keycode, record
    );

    // Allow keycode to be processed downstream
    return true;
}

// layer_state_t layer_state_set_user(layer_state_t state) {
//     return update_tri_layer_state(state, SYM, NAV, MOUSE);
// }
