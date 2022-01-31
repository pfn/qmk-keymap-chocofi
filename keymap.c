#include QMK_KEYBOARD_H

#include "ocean_dream.h"
#include "process_keymap.h"

enum my_layers {
    _QWERTY,
    _COLEMAK,
    _NUM,
    _SYM,
    _NAV,
    _MOUSE,
    _MEDIA,
    _COL6,
};

void matrix_init_user(void) {
    numpad_layer = _NUM;
    sym_layer = _SYM;
}

enum my_combos {
  RF_SHOS,
  UJ_SHOS,
  FG_CAPS,
  YH_NUM,
  QA_ESC,
  AZ_TAB,
  PCLN_BS,
  CLNSLSH_QUOT,
  COMBO_COUNT
};

const uint16_t COMBO_LEN = COMBO_COUNT;

#define COMBO_KEYS(name, keycodes...) const uint16_t PROGMEM name ## _combo[] = { keycodes, COMBO_END }
#define MAKE_COMBO(name, keycode) [name] = COMBO(name ## _combo, keycode)
COMBO_KEYS(RF_SHOS,      KC_R, LT(_NAV, KC_F));
COMBO_KEYS(UJ_SHOS,      KC_U, KC_J);
COMBO_KEYS(YH_NUM,       KC_Y, KC_H);
COMBO_KEYS(FG_CAPS,      LT(_NAV, KC_F), LT(_MOUSE, KC_G));
COMBO_KEYS(QA_ESC,       KC_Q, LCTL_T(KC_A));
COMBO_KEYS(AZ_TAB,       LCTL_T(KC_A), LSFT_T(KC_Z));
COMBO_KEYS(PCLN_BS,      KC_P, RCTL_T(KC_SCLN));
COMBO_KEYS(CLNSLSH_QUOT, RSFT_T(KC_SLSH), RCTL_T(KC_SCLN));

combo_t key_combos[COMBO_COUNT] = {
    MAKE_COMBO(RF_SHOS,      SH_OS),
    MAKE_COMBO(UJ_SHOS,      SH_OS),
    MAKE_COMBO(FG_CAPS,      KC_CAPS),
    MAKE_COMBO(YH_NUM,       OSL(_NUM)),
    MAKE_COMBO(QA_ESC,       KC_ESC),
    MAKE_COMBO(AZ_TAB,       KC_TAB),
    MAKE_COMBO(PCLN_BS,      KC_BSPC),
    MAKE_COMBO(CLNSLSH_QUOT, KC_QUOT)
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_270;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR("QWERTY"), false);
            break;
        case _COLEMAK:
            oled_write_ln_P(PSTR("COLEMAK"), false);
            break;
        case _NUM:
            oled_write_ln_P(PSTR("Numpad"), false);
            break;
        case _SYM:
            oled_write_ln_P(PSTR("Symbol"), false);
            break;
        case _NAV:
            oled_write_ln_P(PSTR("Navigation"), false);
            break;
        case _MOUSE:
            oled_write_ln_P(PSTR("Mouse"), false);
            break;
        case _MEDIA:
            oled_write_ln_P(PSTR("Media"), false);
            break;
        case _COL6:
            oled_write_ln_P(PSTR("Column6"), false);
            break;
    }
}

void render_mod_status(uint8_t modifiers) {
    oled_write_ln_P(PSTR(""), false);
    oled_write_P(PSTR("Mods:"), false);
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("S"), (modifiers & MOD_MASK_SHIFT));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("C"), (modifiers & MOD_MASK_CTRL));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("A"), (modifiers & MOD_MASK_ALT));
    oled_write_P(PSTR(" "), false);
    oled_write_P(PSTR("G"), (modifiers & MOD_MASK_GUI));
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        render_mod_status(get_mods());
    } else {
        if (is_oled_on()) render_stars();
    }
    return false;
}
#endif // OLED_ENABLE
