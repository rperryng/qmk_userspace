#include QMK_KEYBOARD_H
#include "oneshot.h"
#include "swapper.h"

enum layers {
    LA_BASE,

    // tri-layers, which must be defined in this order / together...?
    LA_SYMB,
    LA_SYMB_ALT,
    LA_NAVI,
    LA_NUM,
    LA_NUM_ALT,

    // other layers
    LA_MOUS,
    LA_MOUS_SCROL,
};

enum keycodes {
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,
    OS_CNCL,
    OS_HYPER,

    SW_WIN,
    SW_CTRL,
    SW_ALT,
    SW_REV,
    SW_WIN_GRAVE,

    LAYOUT_SWITCH,
    TRILAYER_SET_NEXT,
    DYNAMIC_SYMB,
};

// New enum for trilayer sets
enum trilayer_sets {
    TRI_NORMAL,    // SYMB + NAVI = NUM
    TRI_FULL_ALT,  // SYMB_ALT + NAVI = NUM_ALT
    TRI_SET_COUNT  // Used for cycling through sets
};

// Track the active trilayer set
uint8_t active_trilayer_set = TRI_NORMAL;

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    ┌───┬───┬───┬─────────────┬─────────────┐                                      ┌─────┬──────────┬───┬───┬───┐
//    │ q │ w │ f │      p      │      b      │                                      │  j  │    l     │ u │ y │ ; │
//    ├───┼───┼───┼─────────────┼─────────────┤                                      ├─────┼──────────┼───┼───┼───┤
//    │ a │ r │ s │      t      │      g      │                                      │  m  │    n     │ e │ i │ o │
//    ├───┼───┼───┼─────────────┼─────────────┤                                      ├─────┼──────────┼───┼───┼───┤
//    │ z │ x │ c │      d      │      v      │                                      │  k  │    h     │ , │ . │ / │
//    └───┴───┴───┼─────────────┼─────────────┼───────────────────┐   ┌──────────────┼─────┼──────────┼───┴───┴───┘
//                │ TO(LA_MOUS) │ MO(LA_NAVI) │ TRILAYER_SET_NEXT │   │ DYNAMIC_SYMB │ spc │ OS_HYPER │
//                └─────────────┴─────────────┴───────────────────┘   └──────────────┴─────┴──────────┘
[LA_BASE] = LAYOUT_split_3x5_3(
  KC_Q , KC_W , KC_F , KC_P        , KC_B        ,                                        KC_J   , KC_L     , KC_U     , KC_Y   , KC_SCLN,
  KC_A , KC_R , KC_S , KC_T        , KC_G        ,                                        KC_M   , KC_N     , KC_E     , KC_I   , KC_O   ,
  KC_Z , KC_X , KC_C , KC_D        , KC_V        ,                                        KC_K   , KC_H     , KC_COMMA , KC_DOT , KC_SLSH,
                       TO(LA_MOUS) , MO(LA_NAVI) , TRILAYER_SET_NEXT ,     DYNAMIC_SYMB , KC_SPC , OS_HYPER
),

//    ┌─────┬─────┬─────┬─────┬─────┐               ┌─────────┬────────┬────────┬─────────┬─────────┐
//    │     │     │     │     │     │               │    |    │   =    │   +    │    -    │         │
//    ├─────┼─────┼─────┼─────┼─────┤               ├─────────┼────────┼────────┼─────────┼─────────┤
//    │  (  │  )  │  {  │  }  │  _  │               │ OS_CNCL │ OS_CMD │ OS_ALT │ OS_CTRL │ OS_SHFT │
//    ├─────┼─────┼─────┼─────┼─────┤               ├─────────┼────────┼────────┼─────────┼─────────┤
//    │  [  │  ]  │  <  │  >  │     │               │    ~    │   `    │   '    │    "    │    \    │
//    └─────┴─────┴─────┼─────┼─────┼─────┐   ┌─────┼─────────┼────────┼────────┴─────────┴─────────┘
//                      │     │     │     │   │     │         │        │
//                      └─────┴─────┴─────┘   └─────┴─────────┴────────┘
[LA_SYMB] = LAYOUT_split_3x5_3(
  _______ , _______ , _______ , _______ , _______ ,                         KC_PIPE , KC_EQL  , KC_PLUS , KC_MINS , _______,
  KC_LPRN , KC_RPRN , KC_LCBR , KC_RCBR , KC_UNDS ,                         OS_CNCL , OS_CMD  , OS_ALT  , OS_CTRL , OS_SHFT,
  KC_LBRC , KC_RBRC , KC_LT   , KC_GT   , _______ ,                         KC_TILD , KC_GRV  , KC_QUOT , KC_DQT  , KC_BSLS,
                                _______ , _______ , _______ ,     _______ , _______ , _______
),

//    ┌───┬───┬─────┬─────┬─────┐               ┌─────────┬────────┬────────┬─────────┬─────────┐
//    │ ! │ @ │ spc │  |  │     │               │    |    │   =    │   +    │    -    │         │
//    ├───┼───┼─────┼─────┼─────┤               ├─────────┼────────┼────────┼─────────┼─────────┤
//    │ ( │ ) │  {  │  }  │  _  │               │ OS_CNCL │ OS_CMD │ OS_ALT │ OS_CTRL │ OS_SHFT │
//    ├───┼───┼─────┼─────┼─────┤               ├─────────┼────────┼────────┼─────────┼─────────┤
//    │ [ │ ] │  <  │  >  │     │               │    ~    │   `    │   '    │    "    │    \    │
//    └───┴───┴─────┼─────┼─────┼─────┐   ┌─────┼─────────┼────────┼────────┴─────────┴─────────┘
//                  │     │     │     │   │     │         │        │
//                  └─────┴─────┴─────┘   └─────┴─────────┴────────┘
[LA_SYMB_ALT] = LAYOUT_split_3x5_3(
  KC_EXLM , KC_AT   , KC_SPC  , KC_PIPE , _______ ,                         KC_PIPE , KC_EQL  , KC_PLUS , KC_MINS , _______,
  KC_LPRN , KC_RPRN , KC_LCBR , KC_RCBR , KC_UNDS ,                         OS_CNCL , OS_CMD  , OS_ALT  , OS_CTRL , OS_SHFT,
  KC_LBRC , KC_RBRC , KC_LT   , KC_GT   , _______ ,                         KC_TILD , KC_GRV  , KC_QUOT , KC_DQT  , KC_BSLS,
                                _______ , _______ , _______ ,     _______ , _______ , _______
),

//    ┌─────────┬─────────┬────────┬────────┬──────────────┐               ┌──────┬─────────┬─────┬──────┬─────┐
//    │         │         │        │        │              │               │      │ CW_TOGG │ tab │ bspc │     │
//    ├─────────┼─────────┼────────┼────────┼──────────────┤               ├──────┼─────────┼─────┼──────┼─────┤
//    │ OS_SHFT │ OS_CTRL │ OS_ALT │ OS_CMD │   OS_CNCL    │               │ left │  down   │ up  │ rght │     │
//    ├─────────┼─────────┼────────┼────────┼──────────────┤               ├──────┼─────────┼─────┼──────┼─────┤
//    │ SW_REV  │ SW_CTRL │ SW_ALT │ SW_WIN │ SW_WIN_GRAVE │               │ home │   ent   │ esc │ end  │     │
//    └─────────┴─────────┴────────┼────────┼──────────────┼─────┐   ┌─────┼──────┼─────────┼─────┴──────┴─────┘
//                                 │        │              │     │   │     │      │         │
//                                 └────────┴──────────────┴─────┘   └─────┴──────┴─────────┘
[LA_NAVI] = LAYOUT_split_3x5_3(
  _______ , _______ , _______ , _______ , _______      ,                         _______ , CW_TOGG  , KC_TAB , KC_BSPC  , _______,
  OS_SHFT , OS_CTRL , OS_ALT  , OS_CMD  , OS_CNCL      ,                         KC_LEFT , KC_DOWN  , KC_UP  , KC_RIGHT , _______,
  SW_REV  , SW_CTRL , SW_ALT  , SW_WIN  , SW_WIN_GRAVE ,                         KC_HOME , KC_ENTER , KC_ESC , KC_END   , _______,
                                _______ , _______      , _______ ,     _______ , _______ , _______
),

//    ┌────┬─────────┬─────────┬─────────┬───────────────────┐               ┌─────┬─────────┬─────────┬─────────┬────┐
//    │ no │   no    │  MS_UP  │   no    │        no         │               │ no  │   no    │   no    │   no    │ no │
//    ├────┼─────────┼─────────┼─────────┼───────────────────┤               ├─────┼─────────┼─────────┼─────────┼────┤
//    │ no │ MS_LEFT │ MS_DOWN │ MS_RGHT │    TO(LA_BASE)    │               │ no  │ MS_BTN1 │ MS_BTN2 │   no    │ no │
//    ├────┼─────────┼─────────┼─────────┼───────────────────┤               ├─────┼─────────┼─────────┼─────────┼────┤
//    │ no │   no    │ MS_BTN2 │ MS_BTN1 │        no         │               │ no  │ MS_ACL2 │ MS_ACL1 │ MS_ACL0 │ no │
//    └────┴─────────┴─────────┼─────────┼───────────────────┼─────┐   ┌─────┼─────┼─────────┼─────────┴─────────┴────┘
//                             │         │ MO(LA_MOUS_SCROL) │     │   │     │     │         │
//                             └─────────┴───────────────────┴─────┘   └─────┴─────┴─────────┘
[LA_MOUS] = LAYOUT_split_3x5_3(
  XXXXXXX , XXXXXXX , MS_UP   , XXXXXXX , XXXXXXX           ,                         XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX,
  XXXXXXX , MS_LEFT , MS_DOWN , MS_RGHT , TO(LA_BASE)       ,                         XXXXXXX , MS_BTN1 , MS_BTN2 , XXXXXXX , XXXXXXX,
  XXXXXXX , XXXXXXX , MS_BTN2 , MS_BTN1 , XXXXXXX           ,                         XXXXXXX , MS_ACL2 , MS_ACL1 , MS_ACL0 , XXXXXXX,
                                _______ , MO(LA_MOUS_SCROL) , _______ ,     _______ , _______ , _______
),

//    ┌────┬────┬────┬─────┬─────┐               ┌─────────┬─────────┬─────────┬─────────┬────┐
//    │ no │ no │ no │ no  │ no  │               │   no    │   no    │   no    │   no    │ no │
//    ├────┼────┼────┼─────┼─────┤               ├─────────┼─────────┼─────────┼─────────┼────┤
//    │ no │ no │ no │ no  │ no  │               │ MS_WHLL │ MS_WHLD │ MS_WHLU │ MS_WHLR │ no │
//    ├────┼────┼────┼─────┼─────┤               ├─────────┼─────────┼─────────┼─────────┼────┤
//    │ no │ no │ no │ no  │ no  │               │   no    │   no    │   no    │   no    │ no │
//    └────┴────┴────┼─────┼─────┼─────┐   ┌─────┼─────────┼─────────┼─────────┴─────────┴────┘
//                   │     │     │     │   │     │         │         │
//                   └─────┴─────┴─────┘   └─────┴─────────┴─────────┘
[LA_MOUS_SCROL] = LAYOUT_split_3x5_3(
  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                         XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX,
  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                         MS_WHLL , MS_WHLD , MS_WHLU , MS_WHLR , XXXXXXX,
  XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX ,                         XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX , XXXXXXX,
                                _______ , _______ , _______ ,     _______ , _______ , _______
),

//    ┌─────┬─────┬─────┬─────┬─────┐               ┌─────┬─────┬─────┬─────┬─────┐
//    │  1  │  2  │  3  │  4  │  5  │               │  6  │  7  │  8  │  9  │  0  │
//    ├─────┼─────┼─────┼─────┼─────┤               ├─────┼─────┼─────┼─────┼─────┤
//    │  !  │  @  │  #  │  $  │  %  │               │  ^  │  &  │  *  │     │     │
//    ├─────┼─────┼─────┼─────┼─────┤               ├─────┼─────┼─────┼─────┼─────┤
//    │     │     │     │     │     │               │     │     │     │     │     │
//    └─────┴─────┴─────┼─────┼─────┼─────┐   ┌─────┼─────┼─────┼─────┴─────┴─────┘
//                      │     │     │     │   │     │     │     │
//                      └─────┴─────┴─────┘   └─────┴─────┴─────┘
[LA_NUM] = LAYOUT_split_3x5_3(
  KC_1    , KC_2    , KC_3    , KC_4    , KC_5    ,                         KC_6    , KC_7    , KC_8    , KC_9    , KC_0   ,
  KC_EXLM , KC_AT   , KC_HASH , KC_DLR  , KC_PERC ,                         KC_CIRC , KC_AMPR , KC_ASTR , _______ , _______,
  _______ , _______ , _______ , _______ , _______ ,                         _______ , _______ , _______ , _______ , _______,
                                _______ , _______ , _______ ,     _______ , _______ , _______
),

//    ┌─────┬─────┬─────┬─────┬─────┐               ┌─────┬─────┬───┬───┬───┐
//    │  ^  │  #  │ spc │  @  │     │               │     │  #  │ ! │ % │ & │
//    ├─────┼─────┼─────┼─────┼─────┤               ├─────┼─────┼───┼───┼───┤
//    │  6  │  4  │  0  │  2  │  _  │               │     │  3  │ 1 │ 5 │ 7 │
//    ├─────┼─────┼─────┼─────┼─────┤               ├─────┼─────┼───┼───┼───┤
//    │     │     │     │  8  │     │               │     │  9  │ , │ . │ / │
//    └─────┴─────┴─────┼─────┼─────┼─────┐   ┌─────┼─────┼─────┼───┴───┴───┘
//                      │     │     │     │   │     │     │     │
//                      └─────┴─────┴─────┘   └─────┴─────┴─────┘
[LA_NUM_ALT] = LAYOUT_split_3x5_3(
  KC_CIRC , KC_HASH , KC_SPC  , KC_AT   , _______ ,                         _______ , KC_HASH , KC_EXLM  , KC_PERC , KC_AMPR ,
  KC_6    , KC_4    , KC_0    , KC_2    , KC_UNDS ,                         _______ , KC_3    , KC_1     , KC_5    , KC_7    ,
  _______ , _______ , _______ , KC_8    , _______ ,                         _______ , KC_9    , KC_COMMA , KC_DOT  , KC_SLASH,
                                _______ , _______ , _______ ,     _______ , _______ , _______
)
};

bool is_oneshot_cancel_key(uint16_t keycode) {
    switch (keycode) {
    case OS_CNCL:
        return true;
    default:
        return false;
    }
}

bool is_oneshot_ignored_key(uint16_t keycode) {
    switch (keycode) {
    case MO(LA_SYMB):
    case MO(LA_SYMB_ALT):
    case MO(LA_NAVI):
    case DYNAMIC_SYMB:
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
bool sw_rev_active = false;
bool sw_win_grave_active = false;

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // Handle dynamic symbol layer based on active_trilayer_set
    if (keycode == DYNAMIC_SYMB) {
        if (record->event.pressed) {
            if (active_trilayer_set == TRI_FULL_ALT) {
                layer_on(LA_SYMB_ALT);
            } else {
                layer_on(LA_SYMB);
            }
        } else {
            layer_off(LA_SYMB);
            layer_off(LA_SYMB_ALT);
        }
        return false;
    }

    // Handle trilayer set cycling
    if (keycode == TRILAYER_SET_NEXT && record->event.pressed) {
        active_trilayer_set = (active_trilayer_set + 1) % TRI_SET_COUNT;
        return false;
    }

    // Handle the reverse/shift modifier using the swapper module
    if (!update_reverse_swapper(
        &sw_ctrl_active,
        &sw_alt_active,
        &sw_win_active,
        SW_REV,
        keycode,
        record
    )) {
        return false;
    }
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
    update_swapper(
        &sw_win_grave_active, KC_LGUI, KC_GRAVE, SW_WIN_GRAVE,
        keycode, record
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

    return true;
}

layer_state_t layer_state_set_user(layer_state_t state) {
    // Use different trilayer combinations based on active_trilayer_set
    switch (active_trilayer_set) {
        case TRI_NORMAL:
            return update_tri_layer_state(state, LA_SYMB, LA_NAVI, LA_NUM);
        case TRI_FULL_ALT:
            return update_tri_layer_state(state, LA_SYMB_ALT, LA_NAVI, LA_NUM_ALT);
        default:
            return update_tri_layer_state(state, LA_SYMB, LA_NAVI, LA_NUM);
    }
}
