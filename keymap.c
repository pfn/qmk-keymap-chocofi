#include QMK_KEYBOARD_H
#include <stdio.h>

enum my_layers {
    _QWERTY,
    _NUM,
    _SYM,
    _NAV,
    _MOUSE,
    _MEDIA,
    _COL6,
};

enum my_combos {
  RF_SHOS,
  UJ_SHOS,
  QA_ESC,
  AZ_TAB,
  PCLN_BS,
  CLNSLSH_QUOT,
  COMBO_COUNT
};

const uint16_t COMBO_LEN = COMBO_COUNT;

const uint16_t PROGMEM rf_shos_combo[]      = { KC_R, LT(_NAV, KC_F),             COMBO_END };
const uint16_t PROGMEM uj_shos_combo[]      = { KC_U, KC_J,                       COMBO_END };
const uint16_t PROGMEM qa_esc_combo[]       = { KC_Q, LCTL_T(KC_A),               COMBO_END };
const uint16_t PROGMEM az_tab_combo[]       = { LCTL_T(KC_A), LSFT_T(KC_Z),       COMBO_END };
const uint16_t PROGMEM pcln_bs_combo[]      = { KC_P, RCTL_T(KC_SCLN),            COMBO_END };
const uint16_t PROGMEM clnslsh_quot_combo[] = { RSFT_T(KC_SLSH), RCTL_T(KC_SCLN), COMBO_END };

combo_t key_combos[COMBO_COUNT] = {
    [RF_SHOS]      = COMBO(rf_shos_combo,      SH_OS),
    [UJ_SHOS]      = COMBO(uj_shos_combo,      SH_OS),
    [QA_ESC]       = COMBO(qa_esc_combo,       KC_ESC),
    [AZ_TAB]       = COMBO(az_tab_combo,       KC_TAB),
    [PCLN_BS]      = COMBO(pcln_bs_combo,      KC_BSPC),
    [CLNSLSH_QUOT] = COMBO(clnslsh_quot_combo, KC_QUOT),
};

void matrix_init_user(void) {
    combo_enable();
}

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
  if (!is_keyboard_master()) {
    return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
  }
  return rotation;
}

void oled_render_layer_state(void) {
    oled_write_P(PSTR("Layer: "), false);
    switch (get_highest_layer(layer_state | default_layer_state)) {
        case _QWERTY:
            oled_write_ln_P(PSTR("QWERTY"), false);
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

void oled_render_logo(void) {
    static const char PROGMEM crkbd_logo[] = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
        0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
        0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
        0};
    oled_write_P(crkbd_logo, false);
}

bool oled_task_user(void) {
    if (is_keyboard_master()) {
        oled_render_layer_state();
        render_mod_status(get_mods());
    } else {
        oled_render_logo();
    }
    return false;
}
#endif // OLED_ENABLE
