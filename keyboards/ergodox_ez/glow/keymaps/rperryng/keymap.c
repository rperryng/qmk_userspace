#include QMK_KEYBOARD_H
#include "oneshot.h"
#include "swapper.h"
#include "version.h"

enum layers {
    LA_BASE,
    LA_SYMB,
    LA_NAVI,
    LA_MOUS,
    LA_MOUS_SCROL,
    LA_NUM
};


enum keycodes {
    // Custom oneshot mod implementation with no timers.
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,

    SW_WIN,
    SW_CTRL,
    SW_ALT,
};

const uint16_t PROGMEM esc_combo[] = {KC_R, KC_S, KC_E, KC_I, COMBO_END};
// const uint16_t PROGMEM base_combo[] = {MS_DOWN, MS_RGHT, MS_BTN2, XXXXXXX, COMBO_END};
combo_t key_combos[] = {
    COMBO(esc_combo, KC_ESC),
    // COMBO(base_combo, TO(LA_BASE)),
};


// clang-format off
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    ┌─────────────┬─────┬─────┬─────┬─────┬─────┬─────┐                                       ┌─────┬─────┬─────┬─────┬─────────────┬─────────────┬──────┐
//    │             │     │     │     │     │     │     │                                       │     │     │     │     │             │             │      │
//    ├─────────────┼─────┼─────┼─────┼─────┼─────┼─────┤                                       ├─────┼─────┼─────┼─────┼─────────────┼─────────────┼──────┤
//    │             │  j  │  l  │  u  │  y  │  ;  │     │                                       │     │  q  │  w  │  f  │      p      │      b      │      │
//    ├─────────────┼─────┼─────┼─────┼─────┼─────┼─────┘                                       └─────┼─────┼─────┼─────┼─────────────┼─────────────┼──────┤
//    │             │  m  │  n  │  e  │  i  │  o  │                                                   │  a  │  r  │  s  │      t      │      g      │      │
//    ├─────────────┼─────┼─────┼─────┼─────┼─────┼─────┐                                       ┌─────┼─────┼─────┼─────┼─────────────┼─────────────┼──────┤
//    │             │  k  │  h  │  ,  │  .  │  /  │     │                                       │     │  z  │  x  │  c  │      d      │      v      │      │
//    ├─────────────┼─────┼─────┼─────┼─────┼─────┴─────┘                                       └─────┴─────┼─────┼─────┼─────────────┼─────────────┼──────┤
//    │ MO(LA_SYMB) │ spc │     │     │     │                                                               │     │     │ TO(LA_MOUS) │ MO(LA_NAVI) │ lsft │
//    └─────────────┴─────┴─────┴─────┴─────┘                 ┌─────┬─────┐   ┌─────┬─────┐                 └─────┴─────┴─────────────┴─────────────┴──────┘
//                                                            │     │     │   │     │     │
//                                                            └─────┼─────┤   ├─────┼─────┘
//                                                                  │     │   │     │
//                                                      ┌─────┬─────┼─────┤   ├─────┼─────┬─────┐
//                                                      │     │     │     │   │     │     │     │
//                                                      └─────┴─────┴─────┘   └─────┴─────┴─────┘
[LA_BASE] = LAYOUT_ergodox_pretty(
  _______     , _______ , _______ , _______  , _______ , _______ , _______ ,                                                                 _______ , _______ , _______ , _______ , _______     , _______     , _______,
  _______     , KC_J    , KC_L    , KC_U     , KC_Y    , KC_SCLN , _______ ,                                                                 _______ , KC_Q    , KC_W    , KC_F    , KC_P        , KC_B        , _______,
  _______     , KC_M    , KC_N    , KC_E     , KC_I    , KC_O    ,                                                                                     KC_A    , KC_R    , KC_S    , KC_T        , KC_G        , _______,
  _______     , KC_K    , KC_H    , KC_COMMA , KC_DOT  , KC_SLSH , _______ ,                                                                 _______ , KC_Z    , KC_X    , KC_C    , KC_D        , KC_V        , _______,
  MO(LA_SYMB) , KC_SPC  , _______ , _______  , _______ ,                                                                                                         _______ , _______ , TO(LA_MOUS) , MO(LA_NAVI) , KC_LSFT,
                                                                                       _______ , _______ ,     _______ , _______                                                                                        ,
                                                                                                 _______ ,     _______                                                                                                  ,
                                                                             _______ , _______ , _______ ,     _______ , _______ , _______
),

//    ┌─────┬────────────┬────────┬────────┬─────────┬─────────┬─────┐                                       ┌─────┬─────┬─────┬─────┬─────┬────────────┬─────┐
//    │     │            │        │        │         │         │     │                                       │     │     │     │     │     │            │     │
//    ├─────┼────────────┼────────┼────────┼─────────┼─────────┼─────┤                                       ├─────┼─────┼─────┼─────┼─────┼────────────┼─────┤
//    │     │     $      │   )    │   }    │    ]    │  bspc   │     │                                       │     │     │  [  │  {  │  (  │     ^      │     │
//    ├─────┼────────────┼────────┼────────┼─────────┼─────────┼─────┘                                       └─────┼─────┼─────┼─────┼─────┼────────────┼─────┤
//    │     │     !      │ OS_CMD │ OS_ALT │ OS_CTRL │ OS_SHFT │                                                   │  +  │  -  │  _  │  |  │     =      │     │
//    ├─────┼────────────┼────────┼────────┼─────────┼─────────┼─────┐                                       ┌─────┼─────┼─────┼─────┼─────┼────────────┼─────┤
//    │     │     ~      │   `    │   '    │    "    │    \    │     │                                       │     │     │  &  │  #  │  *  │     %      │     │
//    ├─────┼────────────┼────────┼────────┼─────────┼─────────┴─────┘                                       └─────┴─────┼─────┼─────┼─────┼────────────┼─────┤
//    │     │ MO(LA_NUM) │        │        │         │                                                                   │     │     │     │ MO(LA_NUM) │     │
//    └─────┴────────────┴────────┴────────┴─────────┘                     ┌─────┬─────┐   ┌─────┬─────┐                 └─────┴─────┴─────┴────────────┴─────┘
//                                                                         │     │     │   │     │     │
//                                                                         └─────┼─────┤   ├─────┼─────┘
//                                                                               │     │   │     │
//                                                                   ┌─────┬─────┼─────┤   ├─────┼─────┬─────┐
//                                                                   │     │     │     │   │     │     │     │
//                                                                   └─────┴─────┴─────┘   └─────┴─────┴─────┘
[LA_SYMB] = LAYOUT_ergodox_pretty(
  _______ , _______    , _______ , _______ , _______ , _______ , _______ ,                                                                 _______ , _______ , _______ , _______ , _______ , _______    , _______,
  _______ , KC_DLR     , KC_RPRN , KC_RCBR , KC_RBRC , KC_BSPC , _______ ,                                                                 _______ , _______ , KC_LBRC , KC_LCBR , KC_LPRN , KC_CIRC    , _______,
  _______ , KC_EXLM    , OS_CMD  , OS_ALT  , OS_CTRL , OS_SHFT ,                                                                                     KC_PLUS , KC_MINS , KC_UNDS , KC_PIPE , KC_EQL     , _______,
  _______ , KC_TILD    , KC_GRV  , KC_QUOT , KC_DQT  , KC_BSLS , _______ ,                                                                 _______ , _______ , KC_AMPR , KC_HASH , KC_ASTR , KC_PERC    , _______,
  _______ , MO(LA_NUM) , _______ , _______ , _______ ,                                                                                                         _______ , _______ , _______ , MO(LA_NUM) , _______,
                                                                                     _______ , _______ ,     _______ , _______                                                                                   ,
                                                                                               _______ ,     _______                                                                                             ,
                                                                           _______ , _______ , _______ ,     _______ , _______ , _______
),

//    ┌────────────┬──────┬──────┬─────┬──────┬─────┬─────┐                                       ┌─────┬─────────┬─────────┬────────┬────────┬─────┬────────────┐
//    │            │      │      │     │      │     │     │                                       │     │         │         │        │        │     │            │
//    ├────────────┼──────┼──────┼─────┼──────┼─────┼─────┤                                       ├─────┼─────────┼─────────┼────────┼────────┼─────┼────────────┤
//    │            │      │      │ tab │ bspc │     │     │                                       │     │         │         │        │        │     │            │
//    ├────────────┼──────┼──────┼─────┼──────┼─────┼─────┘                                       └─────┼─────────┼─────────┼────────┼────────┼─────┼────────────┤
//    │            │ left │ down │ up  │ rght │     │                                                   │ OS_SHFT │ OS_CTRL │ OS_ALT │ OS_CMD │     │            │
//    ├────────────┼──────┼──────┼─────┼──────┼─────┼─────┐                                       ┌─────┼─────────┼─────────┼────────┼────────┼─────┼────────────┤
//    │            │ home │ ent  │ ent │ end  │     │     │                                       │     │         │ SW_CTRL │ SW_ALT │ SW_WIN │     │            │
//    ├────────────┼──────┼──────┼─────┼──────┼─────┴─────┘                                       └─────┴─────────┼─────────┼────────┼────────┼─────┼────────────┤
//    │ MO(LA_NUM) │      │      │     │      │                                                                   │         │        │        │     │ MO(LA_NUM) │
//    └────────────┴──────┴──────┴─────┴──────┘                 ┌─────┬─────┐   ┌─────┬─────┐                     └─────────┴────────┴────────┴─────┴────────────┘
//                                                              │     │     │   │     │     │
//                                                              └─────┼─────┤   ├─────┼─────┘
//                                                                    │     │   │     │
//                                                        ┌─────┬─────┼─────┤   ├─────┼─────┬─────┐
//                                                        │     │     │     │   │     │     │     │
//                                                        └─────┴─────┴─────┘   └─────┴─────┴─────┘
[LA_NAVI] = LAYOUT_ergodox_pretty(
  _______    , _______ , _______  , _______  , _______  , _______ , _______ ,                                                                 _______ , _______ , _______ , _______ , _______ , _______ , _______   ,
  _______    , _______ , _______  , KC_TAB   , KC_BSPC  , _______ , _______ ,                                                                 _______ , _______ , _______ , _______ , _______ , _______ , _______   ,
  _______    , KC_LEFT , KC_DOWN  , KC_UP    , KC_RIGHT , _______ ,                                                                                     OS_SHFT , OS_CTRL , OS_ALT  , OS_CMD  , _______ , _______   ,
  _______    , KC_HOME , KC_ENTER , KC_ENTER , KC_END   , _______ , _______ ,                                                                 _______ , _______ , SW_CTRL , SW_ALT  , SW_WIN  , _______ , _______   ,
  MO(LA_NUM) , _______ , _______  , _______  , _______  ,                                                                                                         _______ , _______ , _______ , _______ , MO(LA_NUM),
                                                                                        _______ , _______ ,     _______ , _______                                                                                   ,
                                                                                                  _______ ,     _______                                                                                             ,
                                                                              _______ , _______ , _______ ,     _______ , _______ , _______
),

//    ┌─────┬─────┬─────────┬─────────┬─────────┬─────┬─────┐                                       ┌─────┬─────┬─────────┬─────────┬─────────┬───────────────────┬─────────────┐
//    │     │     │         │         │         │     │     │                                       │     │     │         │         │         │                   │             │
//    ├─────┼─────┼─────────┼─────────┼─────────┼─────┼─────┤                                       ├─────┼─────┼─────────┼─────────┼─────────┼───────────────────┼─────────────┤
//    │     │ no  │   no    │   no    │   no    │ no  │     │                                       │     │ no  │   no    │  MS_UP  │   no    │        no         │             │
//    ├─────┼─────┼─────────┼─────────┼─────────┼─────┼─────┘                                       └─────┼─────┼─────────┼─────────┼─────────┼───────────────────┼─────────────┤
//    │     │ no  │ MS_BTN1 │ MS_BTN2 │   no    │ no  │                                                   │ no  │ MS_LEFT │ MS_DOWN │ MS_RGHT │    TO(LA_BASE)    │             │
//    ├─────┼─────┼─────────┼─────────┼─────────┼─────┼─────┐                                       ┌─────┼─────┼─────────┼─────────┼─────────┼───────────────────┼─────────────┤
//    │     │ no  │ MS_ACL2 │ MS_ACL1 │ MS_ACL0 │ no  │     │                                       │     │ no  │   no    │ MS_BTN2 │ MS_BTN1 │        no         │             │
//    ├─────┼─────┼─────────┼─────────┼─────────┼─────┴─────┘                                       └─────┴─────┼─────────┼─────────┼─────────┼───────────────────┼─────────────┤
//    │     │     │         │         │         │                                                               │         │         │         │ MO(LA_MOUS_SCROL) │ MO(LA_NAVI) │
//    └─────┴─────┴─────────┴─────────┴─────────┘                 ┌─────┬─────┐   ┌─────┬─────┐                 └─────────┴─────────┴─────────┴───────────────────┴─────────────┘
//                                                                │     │     │   │     │     │
//                                                                └─────┼─────┤   ├─────┼─────┘
//                                                                      │     │   │     │
//                                                          ┌─────┬─────┼─────┤   ├─────┼─────┬─────┐
//                                                          │     │     │     │   │     │     │     │
//                                                          └─────┴─────┴─────┘   └─────┴─────┴─────┘
[LA_MOUS] = LAYOUT_ergodox_pretty(
  _______ , _______ , _______ , _______ , _______ , _______ , _______ ,                                                                 _______ , _______ , _______ , _______ , _______ , _______           , _______    ,
  _______ , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , _______ ,                                                                 _______ , XXXXXXX , XXXXXXX , MS_UP   , XXXXXXX , XXXXXXX           , _______    ,
  _______ , XXXXXXX , MS_BTN1 , MS_BTN2 , XXXXXXX , XXXXXXX ,                                                                                     XXXXXXX , MS_LEFT , MS_DOWN , MS_RGHT , TO(LA_BASE)       , _______    ,
  _______ , XXXXXXX , MS_ACL2 , MS_ACL1 , MS_ACL0 , XXXXXXX , _______ ,                                                                 _______ , XXXXXXX , XXXXXXX , MS_BTN2 , MS_BTN1 , XXXXXXX           , _______    ,
  _______ , _______ , _______ , _______ , _______ ,                                                                                                         _______ , _______ , _______ , MO(LA_MOUS_SCROL) , MO(LA_NAVI),
                                                                                  _______ , _______ ,     _______ , _______                                                                                              ,
                                                                                            _______ ,     _______                                                                                                        ,
                                                                        _______ , _______ , _______ ,     _______ , _______ , _______
),

//    ┌─────┬─────────┬─────────┬─────────┬─────────┬─────┬─────┐                                       ┌─────┬─────┬─────┬─────┬─────┬─────┬─────┐
//    │     │         │         │         │         │     │     │                                       │     │     │     │     │     │     │     │
//    ├─────┼─────────┼─────────┼─────────┼─────────┼─────┼─────┤                                       ├─────┼─────┼─────┼─────┼─────┼─────┼─────┤
//    │     │   no    │   no    │   no    │   no    │ no  │     │                                       │     │ no  │ no  │ no  │ no  │ no  │     │
//    ├─────┼─────────┼─────────┼─────────┼─────────┼─────┼─────┘                                       └─────┼─────┼─────┼─────┼─────┼─────┼─────┤
//    │     │ MS_WHLL │ MS_WHLD │ MS_WHLU │ MS_WHLR │ no  │                                                   │ no  │ no  │ no  │ no  │ no  │     │
//    ├─────┼─────────┼─────────┼─────────┼─────────┼─────┼─────┐                                       ┌─────┼─────┼─────┼─────┼─────┼─────┼─────┤
//    │     │   no    │   no    │   no    │   no    │ no  │     │                                       │     │ no  │ no  │ no  │ no  │ no  │     │
//    ├─────┼─────────┼─────────┼─────────┼─────────┼─────┴─────┘                                       └─────┴─────┼─────┼─────┼─────┼─────┼─────┤
//    │     │         │         │         │         │                                                               │     │     │     │     │     │
//    └─────┴─────────┴─────────┴─────────┴─────────┘                 ┌─────┬─────┐   ┌─────┬─────┐                 └─────┴─────┴─────┴─────┴─────┘
//                                                                    │     │     │   │     │     │
//                                                                    └─────┼─────┤   ├─────┼─────┘
//                                                                          │     │   │     │
//                                                              ┌─────┬─────┼─────┤   ├─────┼─────┬─────┐
//                                                              │     │     │     │   │     │     │     │
//                                                              └─────┴─────┴─────┘   └─────┴─────┴─────┘
[LA_MOUS_SCROL] = LAYOUT_ergodox_pretty(
  _______ , _______ , _______ , _______ , _______ , _______ , _______ ,                                                                 _______ , _______ , _______ , _______ , _______ , _______ , _______,
  _______ , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , _______ ,                                                                 _______ , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , _______,
  _______ , MS_WHLL , MS_WHLD , MS_WHLU , MS_WHLR , XXXXXXX ,                                                                                     XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , _______,
  _______ , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , _______ ,                                                                 _______ , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , _______,
  _______ , _______ , _______ , _______ , _______ ,                                                                                                         _______ , _______ , _______ , _______ , _______,
                                                                                  _______ , _______ ,     _______ , _______                                                                                ,
                                                                                            _______ ,     _______                                                                                          ,
                                                                        _______ , _______ , _______ ,     _______ , _______ , _______
),

//    ┌─────┬─────┬────────┬────────┬─────────┬─────────┬─────┐                                       ┌─────┬─────────┬─────────┬────────┬─────────────┬─────┬─────┐
//    │     │     │        │        │         │         │     │                                       │     │         │         │        │             │     │     │
//    ├─────┼─────┼────────┼────────┼─────────┼─────────┼─────┤                                       ├─────┼─────────┼─────────┼────────┼─────────────┼─────┼─────┤
//    │     │  6  │   7    │   8    │    9    │    0    │     │                                       │     │    1    │    2    │   3    │      4      │  5  │     │
//    ├─────┼─────┼────────┼────────┼─────────┼─────────┼─────┘                                       └─────┼─────────┼─────────┼────────┼─────────────┼─────┼─────┤
//    │     │     │ OS_CMD │ OS_ALT │ OS_CTRL │ OS_SHFT │                                                   │ OS_SHFT │ OS_CTRL │ OS_ALT │   OS_CMD    │     │     │
//    ├─────┼─────┼────────┼────────┼─────────┼─────────┼─────┐                                       ┌─────┼─────────┼─────────┼────────┼─────────────┼─────┼─────┤
//    │     │     │        │        │         │ QK_BOOT │     │                                       │     │         │         │        │ TO(LA_BASE) │     │     │
//    ├─────┼─────┼────────┼────────┼─────────┼─────────┴─────┘                                       └─────┴─────────┼─────────┼────────┼─────────────┼─────┼─────┤
//    │     │     │        │        │         │                                                                       │         │        │             │     │     │
//    └─────┴─────┴────────┴────────┴─────────┘                     ┌─────┬─────┐   ┌─────┬─────┐                     └─────────┴────────┴─────────────┴─────┴─────┘
//                                                                  │     │     │   │     │     │
//                                                                  └─────┼─────┤   ├─────┼─────┘
//                                                                        │     │   │     │
//                                                            ┌─────┬─────┼─────┤   ├─────┼─────┬─────┐
//                                                            │     │     │     │   │     │     │     │
//                                                            └─────┴─────┴─────┘   └─────┴─────┴─────┘
[LA_NUM] = LAYOUT_ergodox_pretty(
  _______ , _______ , _______ , _______ , _______ , _______ , _______ ,                                                                 _______ , _______ , _______ , _______ , _______     , _______ , _______,
  _______ , KC_6    , KC_7    , KC_8    , KC_9    , KC_0    , _______ ,                                                                 _______ , KC_1    , KC_2    , KC_3    , KC_4        , KC_5    , _______,
  _______ , _______ , OS_CMD  , OS_ALT  , OS_CTRL , OS_SHFT ,                                                                                     OS_SHFT , OS_CTRL , OS_ALT  , OS_CMD      , _______ , _______,
  _______ , _______ , _______ , _______ , _______ , QK_BOOT , _______ ,                                                                 _______ , _______ , _______ , _______ , TO(LA_BASE) , _______ , _______,
  _______ , _______ , _______ , _______ , _______ ,                                                                                                         _______ , _______ , _______     , _______ , _______,
                                                                                  _______ , _______ ,     _______ , _______                                                                                    ,
                                                                                            _______ ,     _______                                                                                              ,
                                                                        _______ , _______ , _______ ,     _______ , _______ , _______
)
};
// clang-format on

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case MO(LA_NAVI):
    case MO(LA_SYMB):
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case MO(LA_SYMB):
    case MO(LA_NAVI):
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

bool sw_ctrl_active = false;
bool sw_alt_active = false;
bool sw_win_active = false;

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Update swapper state
    update_swapper(
        &sw_ctrl_active, KC_LCTL, KC_TAB, SW_CTRL,
        keycode, record
    );
    update_swapper(
        &sw_alt_active, KC_LALT, KC_TAB, SW_ALT,
        keycode, record
    );
    update_swapper(
        &sw_win_active, KC_LGUI, KC_TAB, SW_WIN,
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

    return true;
}

// Runs just one time when the keyboard initializes.
void keyboard_post_init_user(void) {
#ifdef RGBLIGHT_COLOR_LAYER_0
    rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
};

// Runs whenever there is a layer state change.
layer_state_t layer_state_set_user(layer_state_t state) {
    ergodox_board_led_off();
    ergodox_right_led_1_off();
    ergodox_right_led_2_off();
    ergodox_right_led_3_off();

    uint8_t layer = get_highest_layer(state);
    switch (layer) {
        case 0:
#ifdef RGBLIGHT_COLOR_LAYER_0
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_0);
#endif
            break;
        case 1:
            ergodox_right_led_1_on();
#ifdef RGBLIGHT_COLOR_LAYER_1
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_1);
#endif
            break;
        case 2:
            ergodox_right_led_2_on();
#ifdef RGBLIGHT_COLOR_LAYER_2
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_2);
#endif
            break;
        case 3:
            ergodox_right_led_3_on();
#ifdef RGBLIGHT_COLOR_LAYER_3
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_3);
#endif
            break;
        case 4:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
#ifdef RGBLIGHT_COLOR_LAYER_4
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_4);
#endif
            break;
        case 5:
            ergodox_right_led_1_on();
            ergodox_right_led_3_on();
#ifdef RGBLIGHT_COLOR_LAYER_5
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_5);
#endif
            break;
        case 6:
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
#ifdef RGBLIGHT_COLOR_LAYER_6
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_6);
#endif
            break;
        case 7:
            ergodox_right_led_1_on();
            ergodox_right_led_2_on();
            ergodox_right_led_3_on();
#ifdef RGBLIGHT_COLOR_LAYER_7
            rgblight_setrgb(RGBLIGHT_COLOR_LAYER_7);
#endif
            break;
        default:
            break;
    }

    return state;
};
