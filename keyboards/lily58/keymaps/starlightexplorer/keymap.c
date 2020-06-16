#include QMK_KEYBOARD_H

#ifdef PROTOCOL_LUFA
  #include "lufa.h"
  #include "split_util.h"
#endif
#ifdef SSD1306OLED
  #include "ssd1306.h"
#endif

#ifdef RGBLIGHT_ENABLE
//Following line allows macro to read current RGB settings
extern rgblight_config_t rgblight_config;
#endif

extern uint8_t is_master;

#define _DVORAK 0
#define _CONTROL 1
#define _LIVE 2
#define _SWAP 3
#define _KBLL 4
#define _SYMLL 5

enum custom_keycodes {
    LYR_SFT = SAFE_RANGE,
    SYML = SAFE_RANGE,
    KBL = SAFE_RANGE,
};


const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {

/* DVORAK
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * | ESC  |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  | Del  |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Tab  |   '  |   ,  |   .  |   P  |   Y  |                    |   F  |   G  |   C  |   R  |   L  |  /   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * | Caps |   A  |   O  |   E  |   U  |   I  |-------.    ,-------|   D  |   H  |   T  |   N  |   S  |  -   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |*Shift|   ;  |   Q  |   J  |   K  |   X  |-------|    |-------|   B  |   M  |   W  |   V  |   Z  |RShift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |  OS  | Alt  | SYML | /Enter  /       \SPace \  |  KBL | CTRL |  OS  |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_DVORAK] = LAYOUT( \
  KC_ESC,            KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    KC_BSPC, \
  KC_TAB,            KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                     KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, \
  KC_CAPS,           KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                     KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS, \
  KC_LSFT_T(LYR_SFT),KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X, KC_LBRC,  KC_RBRC,  KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT, \
                              KC_LCMD, KC_LOPT,   SYML,    KC_ENT,            KC_SPC,      KBL,      KC_LCTL, KC_RCMD \
),
/* CONTROL
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |  Hm  | XXXX | PgUp | BRUP | V UP |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------| End  |   ^  | PgDn | BRDN | V DN |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|   <  |   v  |   >  |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */
[_CONTROL] = LAYOUT( \
  _______, _______, _______, _______, _______, _______,                   _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______,                   KC_HOME, XXXXXXX, KC_PGUP, KC_BRMD, KC_VOLU, _______, \
  _______, _______, _______, _______, _______, _______,                   KC_END,  KC_UP,   KC_PGDN, KC_BRMU, KC_VOLD, _______, \
  _______, _______, _______, _______, _______, _______, _______, _______, KC_LEFT, KC_DOWN, KC_RGHT, _______, _______, _______, \
                             _______, _______, _______, _______, _______,  _______, _______, _______\
),
/* LIVE
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |   G  |   H  |   T  |   R  |   N  |                    |   1  |   2  |   3  | NumL | XXXX |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   U  |   Y  |   I  |   F  |   D  |                    |   4  |   5  |   6  |   -  | V UP |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   A  |   ,  |   O  |   .  |   E  |-------.    ,-------|   7  |   8  |   9  |   +  | V DN |      |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |   ;  |   Q  |   J  |   K  |   S  |-------|    |-------|   0  |   0  |   .  |Enter | Mute |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_LIVE] = LAYOUT( \
  _______, KC_G,    KC_H,    KC_T,    KC_R,    KC_N,                        KC_P1,   KC_P2,   KC_P3,   KC_NLCK, XXXXXXX, _______, \
  _______, KC_U,    KC_Y,    KC_I,    KC_F,    KC_D,                        KC_P4,   KC_P5,   KC_P6,   KC_PMNS, KC_VOLU, _______, \
  _______, KC_A,    KC_COMM, KC_O,    KC_DOT,  KC_E,                        KC_P7,   KC_P8,   KC_P9,   KC_PPLS, KC_VOLD, _______, \
  _______, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_S,     _______, _______,  KC_P0,   KC_P0,   KC_PDOT, KC_PENT, KC_MUTE, _______, \
                             _______, _______, _______,  _______, _______,  _______, _______, _______ \
),
/* SWAP - Mutually Exclusive with 4: KBLL KEYBOARD LOCK
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   '  |   ,  |   .  |   P  |   Y  |                    |   F  |   G  |   C  |   R  |   L  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   A  |   O  |   E  |   U  |   I  |-------.    ,-------|   D  |   H  |   T  |   N  |   S  |      |
 * |------+------+------+------+------+------| SWAP  |    | SWAP  |------+------+------+------+------+------|
 * |      |   ;  |   Q  |   J  |   K  |   X  |-------|    |-------|   B  |   M  |   W  |   V  |   Z  |*Shift|
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      | SYML | /       /       \      \  | SYML | Alt  |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

[_SWAP] = LAYOUT( \
 _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, \
 _______, KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                     KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    _______, \
 _______, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                     KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    _______, \
 _______, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,  SH_OS,     SH_OS,  KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    KC_RSFT_T(LYR_SFT), \
                   _______, _______,   SYML,    _______,           _______,     SYML,     KC_LOPT, _______ \
),
/* KEYBOARD LOCK - Mutually Exclusive with 3: SWAP
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |      |   1  |   2  |   3  |   4  |   5  |                    |   6  |   7  |   8  |   9  |   0  |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   '  |   ,  |   .  |   P  |   Y  |                    |   F  |   G  |   C  |   R  |   L  |  /   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |   A  |   O  |   E  |   U  |   I  |-------.    ,-------|   D  |   H  |   T  |   N  |   S  |  -   |
 * |------+------+------+------+------+------|   [   |    |    ]  |------+------+------+------+------+------|
 * |      |   ;  |   Q  |   J  |   K  |   X  |-------|    |-------|   B  |   M  |   W  |   V  |   Z  |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_KBLL] = LAYOUT( \
  _______, KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                       KC_6,    KC_7,    KC_8,    KC_9,    KC_0,    _______, \
  _______, KC_QUOT, KC_COMM, KC_DOT,  KC_P,    KC_Y,                       KC_F,    KC_G,    KC_C,    KC_R,    KC_L,    KC_SLSH, \
  _______, KC_A,    KC_O,    KC_E,    KC_U,    KC_I,                       KC_D,    KC_H,    KC_T,    KC_N,    KC_S,    KC_MINS, \
  _______, KC_SCLN, KC_Q,    KC_J,    KC_K,    KC_X,    KC_LBRC, KC_RBRC,  KC_B,    KC_M,    KC_W,    KC_V,    KC_Z,    _______, \
                             _______, _______, _______, _______, _______,  _______, _______, _______ \
),
/* SYMBOL LOCK
 * ,-----------------------------------------.                    ,-----------------------------------------.
 * |  `   |      |      |      |      |      |                    |      |      |      |      |      |      |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |                    |      |      |      |      |      |  \   |
 * |------+------+------+------+------+------|                    |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------.    ,-------|      |      |      |      |      |  =   |
 * |------+------+------+------+------+------|       |    |       |------+------+------+------+------+------|
 * |      |      |      |      |      |      |-------|    |-------|      |      |      |      |      |      |
 * `-----------------------------------------/       /     \      \-----------------------------------------'
 *                   |      |      |      | /       /       \      \  |      |      |      |
 *                   |      |      |      |/       /         \      \ |      |      |      |
 *                   `----------------------------'           '------''--------------------'
 */

 [_SYMLL] = LAYOUT( \
  KC_GRV,  _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, _______, \
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, KC_BSLS, \
  _______, _______, _______, _______, _______, _______,                    _______, _______, _______, _______, _______, KC_EQL,  \
  _______, _______, _______, _______, _______, _______, _______, _______,  _______, _______, _______, _______, _______, _______, \
                             _______, _______, _______, _______, _______,  _______, _______, _______ \
),
};

int RGB_current_mode;

// Setting ADJUST layer RGB back to default
void update_tri_layer_RGB(uint8_t layer1, uint8_t layer2, uint8_t layer3) {
  if (IS_LAYER_ON(layer1) && IS_LAYER_ON(layer2)) {
    layer_on(layer3);
  } else {
    layer_off(layer3);
  }
}

void matrix_init_user(void) {
    #ifdef RGBLIGHT_ENABLE
      RGB_current_mode = rgblight_config.mode;
    #endif
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

  switch (keycode) {
    case QWERTY:
      if (record->event.pressed) {
        set_single_persistent_default_layer(_QWERTY);
      }
      return false;
      break;
    case LOWER:
      if (record->event.pressed) {
        layer_on(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_LOWER);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case RAISE:
      if (record->event.pressed) {
        layer_on(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      } else {
        layer_off(_RAISE);
        update_tri_layer_RGB(_LOWER, _RAISE, _ADJUST);
      }
      return false;
      break;
    case ADJUST:
        if (record->event.pressed) {
          layer_on(_ADJUST);
        } else {
          layer_off(_ADJUST);
        }
        return false;
        break;
  }
  return true;
}
