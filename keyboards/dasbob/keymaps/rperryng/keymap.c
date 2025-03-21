#include QMK_KEYBOARD_H
#include "oneshot.h"
#include "swapper.h"

enum layers {
    LA_BASE,
    LA_SYMB,
    LA_NAVI,
    LA_MOUS,
    LA_MOUS_SCROL,
    LA_NUM,
};

enum keycodes {
    OS_SHFT = SAFE_RANGE,
    OS_CTRL,
    OS_ALT,
    OS_CMD,
    OS_CNCL,

    SW_WIN,
    SW_CTRL,
    SW_ALT,
    SW_REV,
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
//    ┌───┬───┬───┬─────────────┬─────────┐                       ┌─────┬──────────┬───┬───┬───┐
//    │ q │ w │ f │      p      │    b    │                       │  j  │    l     │ u │ y │ ; │
//    ├───┼───┼───┼─────────────┼─────────┤                       ├─────┼──────────┼───┼───┼───┤
//    │ a │ r │ s │      t      │    g    │                       │  m  │    n     │ e │ i │ o │
//    ├───┼───┼───┼─────────────┼─────────┤                       ├─────┼──────────┼───┼───┼───┤
//    │ z │ x │ c │      d      │    v    │                       │  k  │    h     │ , │ . │ / │
//    └───┴───┴───┼─────────────┼─────────┼─────────┐   ┌─────────┼─────┼──────────┼───┴───┴───┘
//                │ TO(LA_MOUS) │ TL_UPPR │ TL_LOWR │   │ TL_LOWR │ spc │ OS_HYPER │
//                └─────────────┴─────────┴─────────┘   └─────────┴─────┴──────────┘
[LA_BASE] = LAYOUT_split_3x5_3(
  KC_Q , KC_W , KC_F , KC_P        , KC_B    ,                         KC_J   , KC_L     , KC_U     , KC_Y   , KC_SCLN,
  KC_A , KC_R , KC_S , KC_T        , KC_G    ,                         KC_M   , KC_N     , KC_E     , KC_I   , KC_O   ,
  KC_Z , KC_X , KC_C , KC_D        , KC_V    ,                         KC_K   , KC_H     , KC_COMMA , KC_DOT , KC_SLSH,
                       TO(LA_MOUS) , TL_UPPR , TL_LOWR ,     TL_LOWR , KC_SPC , OS_HYPER
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

//    ┌─────────┬─────────┬────────┬────────┬─────────┐               ┌──────┬─────────┬─────┬──────┬─────┐
//    │         │         │        │        │         │               │      │ CW_TOGG │ tab │ bspc │     │
//    ├─────────┼─────────┼────────┼────────┼─────────┤               ├──────┼─────────┼─────┼──────┼─────┤
//    │ OS_SHFT │ OS_CTRL │ OS_ALT │ OS_CMD │ OS_CNCL │               │ left │  down   │ up  │ rght │     │
//    ├─────────┼─────────┼────────┼────────┼─────────┤               ├──────┼─────────┼─────┼──────┼─────┤
//    │ SW_REV  │ SW_CTRL │ SW_ALT │ SW_WIN │         │               │ home │   ent   │ esc │ end  │     │
//    └─────────┴─────────┴────────┼────────┼─────────┼─────┐   ┌─────┼──────┼─────────┼─────┴──────┴─────┘
//                                 │        │         │     │   │     │      │         │
//                                 └────────┴─────────┴─────┘   └─────┴──────┴─────────┘
[LA_NAVI] = LAYOUT_split_3x5_3(
  _______ , _______ , _______ , _______ , _______ ,                         _______ , CW_TOGG  , KC_TAB , KC_BSPC  , _______,
  OS_SHFT , OS_CTRL , OS_ALT  , OS_CMD  , OS_CNCL ,                         KC_LEFT , KC_DOWN  , KC_UP  , KC_RIGHT , _______,
  SW_REV  , SW_CTRL , SW_ALT  , SW_WIN  , _______ ,                         KC_HOME , KC_ENTER , KC_ESC , KC_END   , _______,
                                _______ , _______ , _______ ,     _______ , _______ , _______
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
    case TL_LOWR:
    case TL_UPPR:
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
bool sw_rev_active = false;

oneshot_state os_shft_state = os_up_unqueued;
oneshot_state os_ctrl_state = os_up_unqueued;
oneshot_state os_alt_state = os_up_unqueued;
oneshot_state os_cmd_state = os_up_unqueued;

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
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
    return update_tri_layer_state(state, LA_SYMB, LA_NAVI, LA_NUM);
}
