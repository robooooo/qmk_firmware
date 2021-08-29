/* Copyright 2020 Boardsource
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include QMK_KEYBOARD_H
#define TAP_HOLD_DELAY 160
#include "process_tap_hold.h"

enum keycodes {
  _QK_TAP_HOLD = SAFE_RANGE,
};

const uint16_t QK_TAP_HOLD = _QK_TAP_HOLD;

// You can use the macros:22124124
// ACTION_TAP_HOLD_SHIFT(KC_TAP, KC_HOLD, KC_TAP_SHIFT, KC_HOLD_SHIFT)
// and ACTION_TAP_HOLD(KC_TAP, KC_HOLD)
tap_hold_action_t tap_hold_actions[] = {
  [0] = ACTION_TAP_HOLD(KC_0, KC_F10),

  [1] = ACTION_TAP_HOLD(KC_1, KC_F1),
  [2] = ACTION_TAP_HOLD(KC_2, KC_F2),
  [3] = ACTION_TAP_HOLD(KC_3, KC_F3),
  [4] = ACTION_TAP_HOLD(KC_4, KC_F4),
  [5] = ACTION_TAP_HOLD(KC_5, KC_F5),
  [6] = ACTION_TAP_HOLD(KC_6, KC_F6),
  [7] = ACTION_TAP_HOLD(KC_7, KC_F7),
  [8] = ACTION_TAP_HOLD(KC_8, KC_F8),
  [9] = ACTION_TAP_HOLD(KC_9, KC_F9),

  [10] = ACTION_TAP_HOLD(KC_MINS, KC_F11),
  [11] = ACTION_TAP_HOLD(KC_EQL, KC_F12),
  [12] = ACTION_TAP_HOLD(KC_NUBS, KC_F13),
  [13] = ACTION_TAP_HOLD(KC_NUHS, KC_F14),

  [14] = ACTION_TAP_HOLD(KC_DEL, KC_PSCR)
//   [15] = ACTION_TAP_HOLD(KC_PGUP, KC_HOME),
//   [16] = ACTION_TAP_HOLD(KC_PGDN, KC_END)
};

const uint16_t QK_TAP_HOLD_SIZE = sizeof(tap_hold_actions)/sizeof(tap_hold_actions[0]);

void matrix_scan_user(void) {
  matrix_scan_tap_hold();
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  process_record_tap_hold(keycode, record);
  return true;
}

// Defines names for use in layer keycodes and the keymap
enum layer_names {
    _BASE,
    _FAST,
    _FN
};

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base */
    [_BASE] = LAYOUT_all(
		KC_GESC, TH(1),   TH(2),     TH(3),      TH(4),       TH(5),    TH(6),   TH(7),   TH(8),   TH(9),   TH(0),    TH(10),  TH(11),  TH(12),  TH(13),  TH(14),
		KC_TAB,           KC_Q,      KC_W,       KC_E,        KC_R,     KC_T,    KC_Y,    KC_U,    KC_I,    KC_O,     KC_P,    KC_LBRC, KC_RBRC, KC_BSPC, KC_PGUP,
		KC_CAPS,          KC_A,      KC_S,       KC_D,        KC_F,     KC_G,    KC_H,    KC_J,    KC_K,    KC_L,     KC_SCLN, KC_QUOT,          KC_ENT,  KC_PGDN,
		KC_LSFT, KC_LSFT, KC_Z,      KC_X,       KC_C,        KC_V,     KC_B,    KC_N,    KC_M,    KC_COMM, KC_DOT,   KC_SLSH, KC_RSFT,          KC_UP,
		KC_LCTL, KC_LGUI, KC_LALT,               LT(_FN, KC_SPC),       LT(_FN, KC_SPC),  LT(_FN, KC_SPC),  OSL(_FN), KC_RALT, KC_RCTL, KC_LEFT, KC_DOWN, KC_RGHT
	),
    [_FAST] = LAYOUT_all(
        _______,  KC_1,   KC_2,      KC_3,       KC_4,        KC_5,     KC_6,    KC_7,    KC_8,    KC_9,    KC_0,     KC_MINS,   KC_EQL, KC_NUBS, KC_NUHS, KC_PSCR,
        _______,          _______,   _______,    _______,     _______,  _______, _______, _______, _______, _______,  _______,  _______, _______, _______, KC_DEL,
        _______,          _______,   _______,    _______,     _______,  _______, _______, _______, _______, _______,  _______,  _______,          _______, _______,
        _______, _______, _______,   _______,    _______,    _______,   _______, _______, _______, _______, _______,  _______,  _______,          _______,
        _______, _______, _______,               _______,               _______,          _______,          _______,  _______,  _______, _______, _______, _______
    ),
    [_FN] = LAYOUT_all(
        KC_GRV,  KC_F1,   KC_F2,      KC_F3,      KC_F4,       KC_F5,   KC_F6,   KC_F7,   KC_F8,   KC_F9,   KC_F10,   KC_F11,   KC_F12,  KC_F13,  KC_F14,    KC_INS,
        _______,          KC_MS_BTN1, KC_MS_UP,   KC_MS_BTN2,  _______, _______, _______, _______, _______, _______,  KC_MPLY,  KC_MPRV, KC_MNXT, _______,   KC_HOME,
        RESET,            KC_MS_LEFT, KC_MS_DOWN, KC_MS_RIGHT, _______, _______, _______, _______, _______, _______,  _______,  _______,          TG(_FAST), KC_END,
        _______, _______, RGB_RMOD,   RGB_MOD,    RGB_M_SW,    RGB_VAD, RGB_VAI, RGB_SPD, RGB_SPI, KC_VOLD, KC_VOLU,  KC_MUTE,  _______,          KC_PGUP,
        _______, _______, RGB_TOG,                _______,              _______,          _______,          _______,  _______,  _______, KC_HOME, KC_PGDN,   KC_END
    )
};

