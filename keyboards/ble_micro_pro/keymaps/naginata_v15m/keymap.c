/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H

// 薙刀式
#include "naginata.h"
#define _NAGINATA 1 // 薙刀式入力レイヤー
// 薙刀式


// Defines the keycodes used by our macros in process_record_user
enum custom_keycodes {
    US_KEY = NG_SAFE_RANGE,
    US2JIS,
};

const uint16_t PROGMEM keymaps[1][MATRIX_ROWS][MATRIX_COLS] = {{{
    KC_A, KC_B, KC_C, KC_D, KC_E, KC_F, KC_G, KC_H, KC_I, KC_J, KC_K, KC_L, KC_M, KC_N, KC_O, KC_P, KC_R, KC_S, KC_T
}}};

const uint16_t PROGMEM encoder_map[1][NUM_ENCODERS][NUM_DIRECTIONS] = {{{KC_MS_U, KC_MS_D}}};

#if defined(RGBLIGHT_ENABLE) || defined(RGB_MATRIX_ENABLE)
layer_state_t layer_state_set_user(layer_state_t state) {
  if (naginata_state()) {
    if (naginata_config.tategaki) {
      rgblight_sethsv_noeeprom(HSV_RED);
    } else {
      rgblight_sethsv_noeeprom(HSV_CYAN);
    }
  } else {
    rgblight_sethsv(HSV_GOLD);
  }
  return state;
}
#endif

void matrix_init_user(void) {
  // 薙刀式
  uint16_t ngonkeys[] = {KC_H, KC_J};
  uint16_t ngoffkeys[] = {KC_F, KC_G};
  set_naginata(_NAGINATA, ngonkeys, ngoffkeys);
  // 薙刀式
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
  // 薙刀式
  if (!process_naginata(keycode, record))
    return false;
  // 薙刀式

  return true;
}
