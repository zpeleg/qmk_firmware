#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

extern uint8_t is_master;

enum layer_number {
  _QWERTY = 0,
  _LOWER,
  _RAISE,
  _ADJUST,
  _SHORTCUTS
};

enum custom_keycodes {
    SMILE = SAFE_RANGE,
    SMILE_HEB,
    SHRUG,
    TFLIP,
    POOP,
    LAUNCH_TERMINAL
};

// these don't work very good...
#define CHANGE_LANG_ENG LSFT(LALT(KC_0))
#define CHANGE_LANG_HEB LSFT(LALT(KC_1))

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {


 [_QWERTY] = LAYOUT( \
  KC_ESC,   KC_1,                   KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_EQL, \
  KC_TAB,   KC_Q,                   KC_W,    KC_E,    KC_R,    KC_T,                     KC_Y,    KC_U,    KC_I,    KC_O,    KC_P,    KC_MINS, \
  KC_LALT,  KC_A,                   KC_S,    KC_D,    KC_F,    KC_G,                     KC_H,    KC_J,    KC_K,    KC_L,    KC_SCLN, KC_QUOT, \
  KC_LSFT,  KC_Z,   KC_X,    KC_C,    KC_V,    KC_B, LT(_SHORTCUTS, KC_LBRC),  LCTL_T(KC_RBRC),  KC_N,    KC_M,    KC_COMM, KC_DOT,  KC_SLSH, LWIN(KC_SPC), \
                 KC_LGUI, MO(_RAISE), KC_LCTRL, LSFT_T(KC_ENT), KC_SPC, KC_BSPC, MO(_LOWER), KC_DEL \
),
[_LOWER] = LAYOUT( \
  _______, _______ , _______, _______, _______, _______,                   _______,    KC_7,    KC_8,    KC_9, KC_ASTR, _______, \
  _______, _______, KC_HOME,   KC_UP,  KC_END, KC_PGUP,                    _______,    KC_4,    KC_5,    KC_6, KC_PLUS, _______, \
  _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,                    _______,    KC_1,    KC_2,    KC_3, KC_BSLS, _______, \
  _______, KC_PIPE, _______, KC_GRV, _______, _______, _______, _______, _______, _______,    KC_DOT,    KC_0,  KC_EQL, _______, \
                             _______, _______, _______, _______, _______, _______, _______, _______\
),
[_RAISE] = LAYOUT( \
  _______, KC_F1,     KC_F2,   KC_F3,   KC_F4,   KC_F5,                     KC_F6,   KC_F7,   KC_F8,    KC_F9,  KC_F10,  KC_F11, \
  _______, _______, KC_HOME,   KC_UP,  KC_END, KC_PGUP,                    _______, _______, _______,   KC_INS, KC_PSCR,  KC_F12, \
  _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, KC_PGDN,                    _______, _______, _______,  _______, KC_CAPS, _______, \
  _______, KC_PIPE, _______, KC_GRV, _______, _______, _______, _______, _______, KC__MUTE, KC__VOLDOWN,  KC__VOLUP, KC_MPLY, _______, \
                             _______, _______, _______, _______, _______,  _______, _______, _______\
),

  [_ADJUST] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
                             _______, _______, _______, _______, _______,  _______, _______, _______ \
  ),
  [_SHORTCUTS] = LAYOUT( \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, POOP,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX,   TFLIP,   SHRUG, SMILE_HEB, SMILE,                   XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, \
  XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,\
                             _______, _______, _______, _______, _______,  _______, _______, _______ \
  )
};

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

//SSD1306 OLED update loop, make sure to enable OLED_DRIVER_ENABLE=yes in rules.mk
#ifdef OLED_DRIVER_ENABLE

oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master())
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  return rotation;
}

// When you add source files to SRC in rules.mk, you can use functions.
const char *read_layer_state(void);
const char *read_logo(void);
void set_keylog(uint16_t keycode, keyrecord_t *record);
const char *read_keylog(void);
const char *read_keylogs(void);

// const char *read_mode_icon(bool swap);
// const char *read_host_led_state(void);
// void set_timelog(void);
// const char *read_timelog(void);

void oled_task_user(void) {
  if (is_keyboard_master()) {
    // If you want to change the display of OLED, you need to change here
    // oled_write_ln("hello darkness my old friend", false);
    oled_write_ln(read_layer_state(), false);
    oled_write_ln(read_keylog(), false);
    oled_write_ln(read_keylogs(), false);
    //oled_write_ln(read_mode_icon(keymap_config.swap_lalt_lgui), false);
    //oled_write_ln(read_host_led_state(), false);
    //oled_write_ln(read_timelog(), false);
  } else {
    oled_write(read_logo(), false);
  }
}
#endif // OLED_DRIVER_ENABLE

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (record->event.pressed) {
#ifdef OLED_DRIVER_ENABLE
    set_keylog(keycode, record);
#endif
    // set_timelog();
  }
  if (record->event.pressed){

    switch (keycode) {
    case SMILE:
        SEND_STRING(":)");
        break;
    case SMILE_HEB:
        SEND_STRING(":(");
        break;
    case SHRUG:
        //send_unicode_string("¯\\_(ツ)_/¯");
        break;
    case TFLIP:
        //send_unicode_string("(╯°□°)╯︵ ┻━┻");
        break;
    case POOP:
        //send_unicode_string("💩");
        break;
    }
  }
  return true;
}

void matrix_init_user(void) {
    set_unicode_input_mode(UC_WINC);
}
