#pragma once
#include "stdint.h"

#define TH(n) (_QK_TAP_HOLD + n)

#define shiftActive() \
  (keyboard_report->mods & (MOD_BIT(KC_LSFT) | MOD_BIT(KC_RSFT)))

#define ACTION_TAP_HOLD_SHIFT(kc_tap, kc_tap_shift, kc_hold, kc_hold_shift) \
  { kc_tap, kc_tap_shift, kc_hold, kc_hold_shift, 0, th_default }

#define ACTION_TAP_HOLD(kc_tap, kc_hold) \
  ACTION_TAP_HOLD_SHIFT(kc_tap, LSFT(kc_tap), kc_hold, LSFT(kc_hold))

#ifndef TAP_HOLD_DELAY
  #define TAP_HOLD_DELAY 200
#endif

typedef enum {
  th_default,
  th_first_press
} tap_hold_state;

typedef struct {
  uint16_t KC_tap;
  uint16_t KC_tap_shift;
  uint16_t KC_hold;
  uint16_t KC_hold_shift;
  uint16_t timer;
  tap_hold_state state;
} tap_hold_action_t;

extern tap_hold_action_t tap_hold_actions[];
const extern uint16_t QK_TAP_HOLD;
const extern uint16_t QK_TAP_HOLD_SIZE;
// const extern uint16_t QK_TAP_HOLD_MAX;
// uint16_t QK_TAP_HOLD_MAX = sizeof(tap_hold_actions)/sizeof(tap_hold_actions[0]);

void process_record_tap_hold(uint16_t keycode, keyrecord_t *record);
void matrix_scan_tap_hold(void);
void selectAndSendKey(tap_hold_action_t *t, bool is_held);
void tap(uint16_t keycode);

void matrix_scan_tap_hold(void) {
  for (uint8_t i = 0; i <= QK_TAP_HOLD_SIZE-1; i++) {
    if (tap_hold_actions[i].state == th_first_press && timer_elapsed(tap_hold_actions[i].timer) >= TAP_HOLD_DELAY) {
      tap_hold_actions[i].state = th_default;
      selectAndSendKey(&tap_hold_actions[i], true);
    }
  }
}

void tap(uint16_t keycode) {
  if (keycode == KC_NO) {
    return;
  }

  uint8_t prev_mods = get_mods();
  uint8_t mods = 0;

  if ((keycode & QK_RSFT) == QK_RSFT) {
    mods |= MOD_BIT(KC_RSFT);
  } else if ((keycode & QK_LSFT) == QK_LSFT) {
    mods |= MOD_BIT(KC_LSFT);
  }
  if ((keycode & QK_RCTL) == QK_RCTL) {
    mods |= MOD_BIT(KC_RCTL);
  } else if ((keycode & QK_LCTL) == QK_LCTL) {
    mods |= MOD_BIT(KC_LCTL);
  }
  if ((keycode & QK_RGUI) == QK_RGUI) {
    mods |= MOD_BIT(KC_RGUI);
  } else if ((keycode & QK_LGUI) == QK_LGUI) {
    mods |= MOD_BIT(KC_LGUI);
  }
  if ((keycode & QK_RALT) == QK_RALT) {
    mods |= MOD_BIT(KC_RALT);
  } else if ((keycode & QK_LALT) == QK_LALT) {
    mods |= MOD_BIT(KC_LALT);
  }

  set_mods(mods);
  send_keyboard_report();

  register_code(keycode);
  unregister_code(keycode);

  set_mods(prev_mods);
  send_keyboard_report();
}

void selectAndSendKey(tap_hold_action_t *t, bool is_held) {
  if (shiftActive()) {
    tap(is_held ? t->KC_hold_shift : t->KC_tap_shift);
  } else {
    tap(is_held ? t->KC_hold : t->KC_tap);
  }
}

void process_record_tap_hold(uint16_t keycode, keyrecord_t *record) {
  if (QK_TAP_HOLD <= keycode && keycode <= QK_TAP_HOLD+QK_TAP_HOLD_SIZE-1) {
    uint16_t idx = keycode - QK_TAP_HOLD;
    tap_hold_action_t *t = &tap_hold_actions[idx];
    if (record->event.pressed) {
      t->timer = timer_read();
      t->state = th_first_press;
    } else {
      if (t->state == th_first_press) {
        t->state = th_default;
        selectAndSendKey(t, false);
      }
    }
  } else {
    for (int i = 0; i < QK_TAP_HOLD_SIZE; ++i) {
      tap_hold_action_t *t = &tap_hold_actions[i];
      if (t->state == th_first_press) {
        t->state = th_default;
        selectAndSendKey(t, false);
      }
    }
  }
}
