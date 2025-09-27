/*
Copyright 2019 @foostan
Copyright 2020 Drashna Jaelre <@drashna>

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
#include "quantum.h"
// Layers
enum {
  L_BASE,
  L_SYM,   // Symbols/Numbers/F-keys
  L_NAV,   // Navigation + tmux + editing
  L_APP    // "Layer 3" / Adjust
};

// Custom keycodes
enum custom_keycodes {
    TMUX_P = SAFE_RANGE,    // Ctrl+b, p
    TMUX_N,                 // Ctrl+b, n
    CPY_SMART,              // Copy (Mac: GUI+C, Terminal: Ctrl+Shift+C)
    PST_SMART,              // Paste (Mac: GUI+V, Terminal: Ctrl+Shift+V)
    TOG_MAC,                 // Toggle Mac/PC mode
    INP_ONE,
    INP_TWO
};

// ----------- Mac/PC toggle (defaults to MAC) ---------
static bool mac_mode = true;    //  false = PC/Terminal; true = Mac GUI

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  if (!record->event.pressed) return true;

  switch (keycode) {
    case TMUX_P: SEND_STRING(SS_LCTL("b") "p"); return false;
    case TMUX_N: SEND_STRING(SS_LCTL("b") "n"); return false;

    case CPY_SMART:
      if (mac_mode) tap_code16(G(KC_C));  // CMD+C
      else SEND_STRING(SS_LCTL(SS_LSFT("c"))); // Ctrl+Shift+C
      return false;

    case PST_SMART:
      if (mac_mode) tap_code16(G(KC_V));  // CMD+V
      else SEND_STRING(SS_LCTL(SS_LSFT("v"))); // Ctrl+Shift+V
      return false;

    case TOG_MAC:
      mac_mode = !mac_mode;
      // Optional tiny feedback: send text on toggle
      if (mac_mode) SEND_STRING(" [mac] ");
      else          SEND_STRING(" [pc] ");
      return false;

    case INP_ONE:
      tap_code(KC_LCTL);
      wait_ms(20);
      tap_code(KC_LCTL);
      wait_ms(20);
      tap_code(KC_1);
      return false;

    case INP_TWO:
      tap_code(KC_LCTL);
      wait_ms(20);
      tap_code(KC_LCTL);
      wait_ms(20);
      tap_code(KC_2);
      return false;
  }
  return true;
}

// ------- Leader sequences (right-thumb Leader) -------
void leader_end_user(void) {
  if (leader_sequence_two_keys(KC_T, KC_N)) {        // Leader T N -> tmux next
    SEND_STRING(SS_LCTL("b") "n");
  } else if (leader_sequence_two_keys(KC_T, KC_P)) {  // Leader T P -> tmux prev
    SEND_STRING(SS_LCTL("b") "p");
  } else if (leader_sequence_one_key(KC_M)) {         // Leader M -> toggle Mac/PC
    tap_code16(TOG_MAC);
  } else if (leader_sequence_two_keys(KC_W, KC_S)) {  // Leader W S -> Vim :w
    SEND_STRING(SS_TAP(X_ESC) ":w" SS_TAP(X_ENTER));
  }
}

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    [L_BASE] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,                         KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_DEL,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LCTL,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,                         KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,                         KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, KC_RALT,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                   KC_LGUI,  LT(L_SYM, KC_ENT),  LT(L_APP, KC_TAB),     RSFT_T(KC_BSPC),  LT(L_NAV, KC_SPC), QK_LEAD
              //------------------`--------------------------------'  `---------------------------------------------'

  ),

    [L_SYM] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_GRV,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,                        KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______,    KC_1,    KC_2,    KC_3,    KC_4,    KC_5,                         KC_6,    KC_7,    KC_8,    KC_9,    KC_0, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, KC_LPRN, KC_RPRN, KC_LCBR, KC_RCBR, KC_BSLS,                      KC_LBRC, KC_RBRC, KC_MINS,  KC_EQL, KC_BSLS, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

    [L_NAV] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
       KC_GRV, INP_ONE, INP_TWO, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_HOME, KC_PGDN, KC_PGUP,  KC_END, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_BSLS, _______,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      _______, XXXXXXX,XXXXXXX,CPY_SMART,PST_SMART,XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, _______,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  ),

    [L_APP] = LAYOUT_split_3x6_3(
  //,-----------------------------------------------------.                    ,-----------------------------------------------------.
      QK_BOOT, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RM_TOGG, RM_HUEU, RM_SATU, RM_VALU, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|                    |--------+--------+--------+--------+--------+--------|
      RM_NEXT, RM_HUED, RM_SATD, RM_VALD, XXXXXXX, XXXXXXX,                      XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------+--------|  |--------+--------+--------+--------+--------+--------+--------|
                                          _______, _______, _______,    _______, _______, _______
                                      //`--------------------------'  `--------------------------'
  )
};

#ifdef OLED_ENABLE
oled_rotation_t oled_init_user(oled_rotation_t rotation) {
    if (!is_keyboard_master()) {
        return OLED_ROTATION_180;  // flips the display 180 degrees if offhand
    }
    return rotation;
}

// DEBUG VERSION - Uses RGB to indicate OLED initialization status
void keyboard_post_init_user(void) {
    // Force RGB on with solid blue to show keyboard initialized
    #ifdef RGB_MATRIX_ENABLE
    rgb_matrix_enable_noeeprom();
    rgb_matrix_mode_noeeprom(RGB_MATRIX_SOLID_COLOR);
    rgb_matrix_sethsv_noeeprom(170, 255, 50);  // Blue
    #endif
}

void housekeeping_task_user(void) {
    static bool changed = false;
    static uint32_t change_timer = 0;

    if (!changed) {
        if (change_timer == 0) {
            change_timer = timer_read32();
        } else if (timer_elapsed32(change_timer) > 2000) {
            changed = true;
            #ifdef RGB_MATRIX_ENABLE
            rgb_matrix_sethsv_noeeprom(85, 255, 50);  // Green after 2 seconds
            #endif
        }
    }
}

bool oled_task_user(void) {
    // Absolute minimum OLED code
    oled_write_P(PSTR("TEST"), false);
    return false;
}

/* ORIGINAL FUNCTION - Restore once OLED is confirmed working
bool oled_task_user(void) {
    if (is_keyboard_master()) {
        // Host Keyboard Layer Status
        oled_write_P(PSTR("Layer: "), false);
        switch (get_highest_layer(layer_state)) {
            case L_BASE:
                oled_write_P(PSTR("Base\n"), false);
                break;
            case L_SYM:
                oled_write_P(PSTR("Symbol\n"), false);
                break;
            case L_NAV:
                oled_write_P(PSTR("Nav\n"), false);
                break;
            case L_APP:
                oled_write_P(PSTR("Adjust\n"), false);
                break;
            default:
                oled_write_P(PSTR("Undef\n"), false);
        }

        // Host Keyboard LED Status
        led_t led_state = host_keyboard_led_state();
        oled_write_P(led_state.caps_lock ? PSTR("CAP ") : PSTR("    "), false);

        // Mac/PC mode status
        oled_write_P(mac_mode ? PSTR("MAC") : PSTR("PC "), false);
    } else {
        // Corne logo or other graphic for secondary display
        static const char PROGMEM corne_logo[] = {
            // You can add a custom logo here
            0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87, 0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f, 0x90, 0x91, 0x92, 0x93, 0x94,
            0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7, 0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf, 0xb0, 0xb1, 0xb2, 0xb3, 0xb4,
            0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7, 0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf, 0xd0, 0xd1, 0xd2, 0xd3, 0xd4,
            0};
        oled_write_P(corne_logo, false);
    }
    return false;
}
*/
#endif
