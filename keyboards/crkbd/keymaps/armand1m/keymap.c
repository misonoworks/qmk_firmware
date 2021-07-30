/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>
Copyright 2021 Armando Magalhaes <@armand1m>

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#include QMK_KEYBOARD_H

enum custom_keycodes {
    ARROW_FUNCTION = SAFE_RANGE
};

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
      case ARROW_FUNCTION:
        if (record->event.pressed) {
            SEND_STRING("() => {}");
        } else {
            SEND_STRING(SS_TAP(X_LEFT) SS_TAP(X_ENTER));
        }
        return false;
    }

    return true;
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [0] = LAYOUT_split_3x6_3(
            KC_TAB,               KC_Q,           KC_W,    KC_E,    KC_R,    KC_T,           KC_Y,    KC_U,    KC_I,    KC_O,                  KC_P,       KC_BSPC,
     LT(1, KC_ESC),        LT(2, KC_A),    LT(3, KC_S),    KC_D,    KC_F,    KC_G,           KC_H,    KC_J,    KC_K,    KC_L,               KC_SCLN,       KC_QUOT,
     OSM(MOD_LSFT), MT(MOD_LCTL, KC_Z),           KC_X,    KC_C,    KC_V,    KC_B,           KC_N,    KC_M, KC_COMM,  KC_DOT, MT(MOD_RCTL, KC_SLSH), OSM(MOD_RSFT),
                                     KC_LALT,       LGUI(KC_SPACE),   LGUI_T(KC_SPC),    MT(MOD_RSFT, KC_ENT),  MO(2), KC_RALT
  ),

  [1] = LAYOUT_split_3x6_3(
      _______,      KC_1,      KC_2,      KC_3,      KC_4,      KC_5,                    KC_6,      KC_7,      KC_8,        KC_9,      KC_0, _______,
      _______,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,                 KC_LEFT,   KC_DOWN,     KC_UP,    KC_RIGHT,   XXXXXXX, _______,
      _______,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,   XXXXXXX,                 XXXXXXX,   XXXXXXX,   _______,     _______,   _______, _______,
                                                  _______, _______, _______,     _______, _______, _______
  ),

  [2] = LAYOUT_split_3x6_3(
      _______,   KC_EXLM,     KC_AT,   KC_HASH,         KC_DLR, KC_PERC,             KC_CIRC, KC_AMPR, KC_ASTR, KC_LPRN, KC_RPRN, _______,
      _______,   XXXXXXX,   XXXXXXX,   XXXXXXX, ARROW_FUNCTION,   KC_LT,             KC_MINS,  KC_EQL, KC_LBRC, KC_RBRC, KC_BSLS,  KC_GRV,
      _______,   XXXXXXX,   XXXXXXX,   XXXXXXX,        XXXXXXX,   KC_GT,             KC_UNDS, KC_PLUS, KC_LCBR, KC_RCBR, KC_PIPE, KC_TILD,
                                                  _______, _______, _______,     _______, _______, _______
  ),

  [3] = LAYOUT_split_3x6_3(
      _______,   XXXXXXX,   XXXXXXX,   XXXXXXX, LALT(LSFT(KC_0)),   XXXXXXX,             XXXXXXX,       XXXXXXX,       XXXXXXX, XXXXXXX, LGUI(LSFT(KC_4)), XXXXXXX,
      _______,   XXXXXXX,   XXXXXXX,   XXXXXXX,          XXXXXXX,   XXXXXXX,             XXXXXXX, LGUI(KC_MINS), LGUI(KC_PLUS), XXXXXXX,          XXXXXXX, XXXXXXX,
      _______,   XXXXXXX,   XXXXXXX,   XXXXXXX,          XXXXXXX,   XXXXXXX,             XXXXXXX,       XXXXXXX,       XXXXXXX, XXXXXXX,          XXXXXXX, XXXXXXX,
                                                  _______, _______, _______,     _______, _______, _______
  ),
};

#ifdef OLED_DRIVER_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {

  if (!is_keyboard_master()) {
    return OLED_ROTATION_180; // flips the display 180 degrees if offhand
  }
  return rotation;
}

void render_bootmagic_status(bool status) {
    /* Show Ctrl-Gui Swap options */
    static const char PROGMEM logo[][2][3] = {
        {{0x97, 0x98, 0}, {0xb7, 0xb8, 0}},
        {{0x95, 0x96, 0}, {0xb5, 0xb6, 0}},
    };
    if (status) {
        oled_write_ln_P(logo[0][0], false);
        oled_write_ln_P(logo[0][1], false);
    } else {
        oled_write_ln_P(logo[1][0], false);
        oled_write_ln_P(logo[1][1], false);
    }
}

void oled_render_amsterdam_flag(void) {
    // 'Flag_of_Amsterdam', 128x32px
    static const char PROGMEM amsterdam_flag[] = {
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xf8, 0xf0, 0xe0, 0xc0, 0x80, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xf8, 0xf0, 0xe0, 0xc0, 0x80, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf0, 0xf8, 0xf8, 0xf0, 0xe0, 0xc0, 0x80,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xf8, 0xf0, 0xe0, 0xc0, 0x80,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xf8, 0xf0, 0xe0, 0xc0,
        0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xf8, 0xf8, 0xf0, 0xe0,
        0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff,
        0xfe, 0xfc, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff, 0xff, 0xff,
        0xff, 0xfe, 0xfc, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03, 0x01,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x3f, 0x7f, 0xff, 0xff,
        0xff, 0xff, 0xfe, 0xfc, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x3f, 0x1f, 0x0f, 0x07, 0x03,
        0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x7f,
        0x3f, 0x3f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 0x80, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff, 0xff, 0xff,
        0xff, 0x7f, 0x3f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xf8, 0xf0, 0xe0, 0xc0, 0x80,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc0, 0xe0, 0xf0, 0xf8, 0xfc, 0xfe, 0xff, 0xff,
        0xff, 0xff, 0x7f, 0x3f, 0x1f, 0x3f, 0x7f, 0xff, 0xff, 0xff, 0xfe, 0xfc, 0xfc, 0xf8, 0xf0, 0xe0,
        0xc0, 0x80, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x0f, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x0f, 0x07, 0x03, 0x01, 0x00,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x1f, 0x0f, 0x07, 0x03, 0x01,
        0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x1f, 0x0f, 0x07, 0x03,
        0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x03, 0x07, 0x0f, 0x1f, 0x0f, 0x07, 0x03,
        0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
    };
    oled_write_raw_P(amsterdam_flag, sizeof(amsterdam_flag));
}

void oled_task_user(void) {
    oled_render_amsterdam_flag();
}
#endif // OLED_DRIVER_ENABLE
