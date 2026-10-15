#include QMK_KEYBOARD_H
#include "oneshot.h"
#include "swapper.h"
#include "bongocat.h"
#include "keymap.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    ┌─────┬─────┬─────┬─────┬─────────────┐                             ┌─────┬───┬───┬───┬──────────┐
//    │  q  │  w  │  f  │  p  │      b      │                             │  j  │ l │ u │ y │    ;     │
//    ├─────┼─────┼─────┼─────┼─────────────┤                             ├─────┼───┼───┼───┼──────────┤
//    │  a  │  r  │  s  │  t  │      g      │                             │  m  │ n │ e │ i │    o     │
//    ├─────┼─────┼─────┼─────┼─────────────┤                             ├─────┼───┼───┼───┼──────────┤
//    │  z  │  x  │  c  │  d  │      v      │                             │  k  │ h │ , │ . │    /     │
//    ├─────┼─────┼─────┼─────┼─────────────┼───────┐   ┌─────────────────┼─────┼───┴───┴───┼──────────┤
//    │     │     │     │     │ MO(LA_NAVI) │ SNIPE │   │ MO(LA_SYMB_ALT) │ spc │           │ OS_HYPER │
//    └─────┴─────┴─────┴─────┴─────────────┴───────┘   └─────────────────┴─────┘           └──────────┘
[LA_BASE] = LAYOUT_right_ball(
  KC_Q    , KC_W    , KC_F    , KC_P    , KC_B        ,                               KC_J   , KC_L , KC_U     , KC_Y   , KC_SCLN ,
  KC_A    , KC_R    , KC_S    , KC_T    , KC_G        ,                               KC_M   , KC_N , KC_E     , KC_I   , KC_O    ,
  KC_Z    , KC_X    , KC_C    , KC_D    , KC_V        ,                               KC_K   , KC_H , KC_COMMA , KC_DOT , KC_SLSH ,
  _______ , _______ , _______ , _______ , MO(LA_NAVI) , SNIPE ,     MO(LA_SYMB_ALT) , KC_SPC ,                            OS_HYPER
),

//    ┌──────┬──────┬─────────┬──────┬────────────┐               ┌─────┬─────────┬─────────┬─────────┬─────┐
//    │      │      │ SCRL_MO │      │            │               │     │         │         │         │     │
//    ├──────┼──────┼─────────┼──────┼────────────┤               ├─────┼─────────┼─────────┼─────────┼─────┤
//    │ lsft │ lctl │  lalt   │ lgui │ SNIPE_FINE │               │     │ MS_BTN1 │ MS_BTN2 │ MS_BTN3 │     │
//    ├──────┼──────┼─────────┼──────┼────────────┤               ├─────┼─────────┼─────────┼─────────┼─────┤
//    │      │      │         │      │            │               │     │ MS_BTN1 │ MS_BTN2 │ MS_BTN3 │     │
//    ├──────┼──────┼─────────┼──────┼────────────┼─────┐   ┌─────┼─────┼─────────┴─────────┴─────────┼─────┤
//    │      │      │         │      │            │     │   │     │     │                             │     │
//    └──────┴──────┴─────────┴──────┴────────────┴─────┘   └─────┴─────┘                             └─────┘
[LA_MOUSE] = LAYOUT_right_ball(
  _______ , _______ , SCRL_MO , _______ , _______    ,                         _______ , _______ , _______ , _______ , _______,
  KC_LSFT , KC_LCTL , KC_LALT , KC_LGUI , SNIPE_FINE ,                         _______ , MS_BTN1 , MS_BTN2 , MS_BTN3 , _______,
  _______ , _______ , _______ , _______ , _______    ,                         _______ , MS_BTN1 , MS_BTN2 , MS_BTN3 , _______,
  _______ , _______ , _______ , _______ , _______    , _______ ,     _______ , _______ ,                               _______
),

//    ┌─────┬─────┬─────┬─────┬─────┐               ┌─────────┬────────┬────────┬─────────┬─────────┐
//    │  !  │  *  │ spc │  @  │  &  │               │    |    │   =    │   +    │    -    │         │
//    ├─────┼─────┼─────┼─────┼─────┤               ├─────────┼────────┼────────┼─────────┼─────────┤
//    │  (  │  )  │  {  │  }  │  _  │               │ OS_CNCL │ OS_CMD │ OS_ALT │ OS_CTRL │ OS_SHFT │
//    ├─────┼─────┼─────┼─────┼─────┤               ├─────────┼────────┼────────┼─────────┼─────────┤
//    │  [  │  ]  │  <  │  >  │  %  │               │    ~    │   `    │   '    │    "    │    \    │
//    ├─────┼─────┼─────┼─────┼─────┼─────┐   ┌─────┼─────────┼────────┴────────┴─────────┼─────────┤
//    │     │     │     │     │     │     │   │     │         │                           │         │
//    └─────┴─────┴─────┴─────┴─────┴─────┘   └─────┴─────────┘                           └─────────┘
[LA_SYMB_ALT] = LAYOUT_right_ball(
  KC_EXLM , KC_ASTR , KC_SPC  , KC_AT   , KC_AMPR ,                         KC_PIPE , KC_EQL , KC_PLUS , KC_MINS , _______,
  KC_LPRN , KC_RPRN , KC_LCBR , KC_RCBR , KC_UNDS ,                         OS_CNCL , OS_CMD , OS_ALT  , OS_CTRL , OS_SHFT,
  KC_LBRC , KC_RBRC , KC_LT   , KC_GT   , KC_PERC ,                         KC_TILD , KC_GRV , KC_QUOT , KC_DQT  , KC_BSLS,
  _______ , _______ , _______ , _______ , _______ , _______ ,     _______ , _______ ,                              _______
),

//    ┌─────────┬──────────────┬─────────┬────────────┬──────────────┐               ┌──────┬──────┬─────┬──────┬─────┐
//    │ CW_TOGG │ MO(LA_MEDIA) │ SCRL_MO │ MO(LA_KBC) │              │               │ app  │ pscr │ tab │ bspc │     │
//    ├─────────┼──────────────┼─────────┼────────────┼──────────────┤               ├──────┼──────┼─────┼──────┼─────┤
//    │ OS_SHFT │   OS_CTRL    │ OS_ALT  │   OS_CMD   │   OS_CNCL    │               │ left │ down │ up  │ rght │     │
//    ├─────────┼──────────────┼─────────┼────────────┼──────────────┤               ├──────┼──────┼─────┼──────┼─────┤
//    │ SW_REV  │   SW_CTRL    │ SW_ALT  │   SW_WIN   │ SW_WIN_GRAVE │               │ home │ ent  │ esc │ end  │     │
//    ├─────────┼──────────────┼─────────┼────────────┼──────────────┼─────┐   ┌─────┼──────┼──────┴─────┴──────┼─────┤
//    │         │              │         │            │              │     │   │     │      │                   │     │
//    └─────────┴──────────────┴─────────┴────────────┴──────────────┴─────┘   └─────┴──────┘                   └─────┘
[LA_NAVI] = LAYOUT_right_ball(
  CW_TOGG , MO(LA_MEDIA) , SCRL_MO , MO(LA_KBC) , _______      ,                         KC_APP  , KC_PSCR  , KC_TAB , KC_BSPC  , _______,
  OS_SHFT , OS_CTRL      , OS_ALT  , OS_CMD     , OS_CNCL      ,                         KC_LEFT , KC_DOWN  , KC_UP  , KC_RIGHT , _______,
  SW_REV  , SW_CTRL      , SW_ALT  , SW_WIN     , SW_WIN_GRAVE ,                         KC_HOME , KC_ENTER , KC_ESC , KC_END   , _______,
  _______ , _______      , _______ , _______    , _______      , _______ ,     _______ , _______ ,                                _______
),

//    ┌─────┬─────┬─────┬─────┬─────┐               ┌──────────┬───┬───┬───┬─────┐
//    │  ^  │  $  │ spc │  @  │     │               │          │ # │ ! │ % │  &  │
//    ├─────┼─────┼─────┼─────┼─────┤               ├──────────┼───┼───┼───┼─────┤
//    │  6  │  4  │  0  │  2  │  _  │               │    no    │ 3 │ 1 │ 5 │  7  │
//    ├─────┼─────┼─────┼─────┼─────┤               ├──────────┼───┼───┼───┼─────┤
//    │     │  -  │  *  │  8  │     │               │ OSL_FUNC │ 9 │ , │ . │  /  │
//    ├─────┼─────┼─────┼─────┼─────┼─────┐   ┌─────┼──────────┼───┴───┴───┼─────┤
//    │     │     │     │     │     │     │   │     │          │           │     │
//    └─────┴─────┴─────┴─────┴─────┴─────┘   └─────┴──────────┘           └─────┘
[LA_NUM_ALT] = LAYOUT_right_ball(
  KC_CIRC , KC_DLR  , KC_SPC  , KC_AT   , _______ ,                         _______  , KC_HASH , KC_EXLM  , KC_PERC , KC_AMPR ,
  KC_6    , KC_4    , KC_0    , KC_2    , KC_UNDS ,                         XXXXXXX  , KC_3    , KC_1     , KC_5    , KC_7    ,
  _______ , KC_MINS , KC_ASTR , KC_8    , _______ ,                         OSL_FUNC , KC_9    , KC_COMMA , KC_DOT  , KC_SLASH,
  _______ , _______ , _______ , _______ , _______ , _______ ,     _______ , _______  ,                                _______
),

//    ┌─────┬─────┬─────┬─────┬─────┐               ┌─────────┬──────────┬──────────┬─────────┬────────┐
//    │     │     │     │     │     │               │ AML_TO  │ AML_D50  │ AML_I50  │         │        │
//    ├─────┼─────┼─────┼─────┼─────┤               ├─────────┼──────────┼──────────┼─────────┼────────┤
//    │     │     │     │     │     │               │ CPI_D1K │ CPI_D100 │ CPI_I100 │ CPI_I1K │        │
//    ├─────┼─────┼─────┼─────┼─────┤               ├─────────┼──────────┼──────────┼─────────┼────────┤
//    │     │     │     │     │     │               │         │ KBC_SAVE │          │         │ QK_RBT │
//    ├─────┼─────┼─────┼─────┼─────┼─────┐   ┌─────┼─────────┼──────────┴──────────┴─────────┼────────┤
//    │     │     │     │     │     │     │   │     │         │                               │        │
//    └─────┴─────┴─────┴─────┴─────┴─────┘   └─────┴─────────┘                               └────────┘
[LA_KBC] = LAYOUT_right_ball(
  _______ , _______ , _______ , _______ , _______ ,                         AML_TO  , AML_D50  , AML_I50  , _______ , _______,
  _______ , _______ , _______ , _______ , _______ ,                         CPI_D1K , CPI_D100 , CPI_I100 , CPI_I1K , _______,
  _______ , _______ , _______ , _______ , _______ ,                         _______ , KBC_SAVE , _______  , _______ , QK_RBT ,
  _______ , _______ , _______ , _______ , _______ , _______ ,     _______ , _______ ,                                 _______
),

//    ┌─────┬─────┬─────┬─────┬────┐             ┌────┬─────┬─────┬────┬────┐
//    │ f16 │ f14 │ f10 │ f12 │ no │             │ no │ f13 │ f11 │ no │ no │
//    ├─────┼─────┼─────┼─────┼────┤             ├────┼─────┼─────┼────┼────┤
//    │ f6  │ f4  │ no  │ f2  │ no │             │ no │ f3  │ f1  │ f5 │ f7 │
//    ├─────┼─────┼─────┼─────┼────┤             ├────┼─────┼─────┼────┼────┤
//    │ no  │ no  │ no  │ f8  │ no │             │ no │ f9  │ no  │ no │ no │
//    ├─────┼─────┼─────┼─────┼────┼────┐   ┌────┼────┼─────┴─────┴────┼────┤
//    │ no  │ no  │ no  │ no  │ no │ no │   │ no │ no │                │ no │
//    └─────┴─────┴─────┴─────┴────┴────┘   └────┴────┘                └────┘
[LA_FUNC] = LAYOUT_right_ball(
  KC_F16  , KC_F14  , KC_F10  , KC_F12  , XXXXXXX ,                         XXXXXXX , KC_F13 , KC_F11  , XXXXXXX , XXXXXXX,
  KC_F6   , KC_F4   , XXXXXXX , KC_F2   , XXXXXXX ,                         XXXXXXX , KC_F3  , KC_F1   , KC_F5   , KC_F7  ,
  XXXXXXX , XXXXXXX , XXXXXXX , KC_F8   , XXXXXXX ,                         XXXXXXX , KC_F9  , XXXXXXX , XXXXXXX , XXXXXXX,
  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,     XXXXXXX , XXXXXXX ,                              XXXXXXX
),

//    ┌────┬────┬────┬────┬────┐             ┌──────┬──────┬──────┬──────┬──────┐
//    │ no │ no │ no │ no │ no │             │  no  │  no  │  no  │  no  │  no  │
//    ├────┼────┼────┼────┼────┤             ├──────┼──────┼──────┼──────┼──────┤
//    │ no │ no │ no │ no │ no │             │ mprv │ vold │ volu │ mnxt │ mute │
//    ├────┼────┼────┼────┼────┤             ├──────┼──────┼──────┼──────┼──────┤
//    │ no │ no │ no │ no │ no │             │  no  │  no  │  no  │  no  │  no  │
//    ├────┼────┼────┼────┼────┼────┐   ┌────┼──────┼──────┴──────┴──────┼──────┤
//    │ no │ no │ no │ no │ no │ no │   │ no │  no  │                    │ mply │
//    └────┴────┴────┴────┴────┴────┘   └────┴──────┘                    └──────┘
[LA_MEDIA] = LAYOUT_right_ball(
  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                         XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX,
  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                         KC_MPRV , KC_VOLD , KC_VOLU , KC_MNXT , KC_MUTE,
  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                         XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX,
  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,     XXXXXXX , XXXXXXX ,                               KC_MPLY
)
};

// ===============================================================
// Custom Oneshot
// ===============================================================
bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case OS_CNCL:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_layer_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case OS_CNCL:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_mod_key(uint16_t keycode) {
    switch (keycode) {
    case OS_SHFT:
    case OS_CTRL:
    case OS_ALT:
    case OS_CMD:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case MO(LA_NAVI):
    case MO(LA_SYMB_ALT):
    case SNIPE:
    case SNIPE_FINE:
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

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;
oneshot_state os_func_state = os_up_unqueued;

// ===============================================================
// Custom Swapper
// ===============================================================
bool sw_ctrl_active = false;
bool sw_alt_active = false;
bool sw_win_active = false;
bool sw_rev_active = false;
bool sw_win_grave_active = false;

// ===============================================================
// Snipe
// ===============================================================
bool snipe_held = false;

// ===============================================================
// QMK Hooks
// ===============================================================
bool is_mouse_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
    case SNIPE:
    case SNIPE_FINE:
        return true;
    default:
        // Only while already mousing, so oneshot mods keep the layer up for
        // shift/cmd-click without activating it during normal typing.
        return is_oneshot_mod_key(keycode) && layer_state_is(LA_MOUSE);
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Handle the reverse/shift modifier using the swapper module
    if (!update_reverse_swapper(
        &sw_ctrl_active, &sw_alt_active, &sw_win_active,
        SW_REV, keycode, record
    )) {
        return false;
    }

    update_swapper(
        &sw_ctrl_active, KC_LCTL, KC_TAB, SW_CTRL,
        MO(LA_NAVI), keycode, record
    );
    update_swapper(
        &sw_alt_active, KC_LALT, KC_TAB, SW_ALT,
        MO(LA_NAVI), keycode, record
    );
    update_swapper(
        &sw_win_active, KC_LGUI, KC_TAB, SW_WIN,
        MO(LA_NAVI), keycode, record
    );
    update_swapper(
        &sw_win_grave_active, KC_LGUI, KC_GRAVE, SW_WIN_GRAVE,
        MO(LA_NAVI), keycode, record
    );

    // Handle hyper key to queue up all modifiers at once
    if (update_oneshot_hyper(
        &os_shft_state,
        &os_ctrl_state,
        &os_alt_state,
        &os_cmd_state,
        OS_HYPER,
        keycode,
        record
    )) {
        return true;
    }

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

    bool handled = true;
    handled = update_oneshot_layer(
        &os_func_state, LA_FUNC, OSL_FUNC,
        keycode, record
    ) & handled;

    if (!handled) {
        return false;
    }

    switch (keycode) {
        case SNIPE: {
            static uint8_t saved_cpi;
            static uint16_t pressed_at;
            if (record->event.pressed) {
                saved_cpi = keyball_get_cpi();
                pressed_at = timer_read();
                snipe_held = true;
                keyball_set_cpi(SNIPE_CPI);
            } else {
                snipe_held = false;
                keyball_set_cpi(saved_cpi);
                // A tap (rather than a hold) manually exits the mouse layer.
                if (timer_elapsed(pressed_at) < TAPPING_TERM) {
                    auto_mouse_layer_off();
                }
            }
            return false;
        }
        case SNIPE_FINE:
            // Latches until SNIPE is released, which restores the CPI.
            if (record->event.pressed && snipe_held) {
                keyball_set_cpi(SNIPE_FINE_CPI);
            }
            return false;
    }

    return true;
}

void keyboard_post_init_user(void) {
    // Keyball restores its saved AML state (off unless KBC_SAVE'd) right
    // before this runs, so force it on here. AML_TO still toggles per session.
    set_auto_mouse_layer(LA_MOUSE);
    set_auto_mouse_enable(true);

    bongocat_init();
}

void housekeeping_task_user(void) {
    bongocat_task();
}

layer_state_t layer_state_set_user(layer_state_t state) {
    return update_tri_layer_state(state, LA_NAVI, LA_SYMB_ALT, LA_NUM_ALT);
}

#ifdef OLED_ENABLE

#    include "lib/oledkit/oledkit.h"

bool oled_task_user(void) {
    if (!is_keyboard_left()) {
        bongocat_render();
    } else {
        oledkit_render_logo_user();
    }
    return false;
}
#endif
