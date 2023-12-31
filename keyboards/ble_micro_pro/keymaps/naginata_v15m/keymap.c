/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H
#include "twpair_on_jis.h"

// 薙刀式
#include "naginata.h"
NGKEYS naginata_keys;
#define _NAGINATA   1
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

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    static bool is_us2jis = false;
    if (record->event.pressed) {
        switch (keycode) {
        case US_KEY:
            is_us2jis = false;
            return false;
        case US2JIS:
            is_us2jis = true;
            return false;
        case KC_PEQL:
            if (naginata_config.os != NG_MAC_DIC) {
                // JISキーボードに対しては twpair_on_jis() を使って「=」を出力する
                // USキーボードには KC_EQL を出力
                if (is_us2jis)
                    twpair_on_jis(KC_EQL, record);
                else
                    tap_code(KC_EQL);
                return false;
            }
            break;
        case KC_PCMM:
            if (!(naginata_config.os == NG_MAC_DIC && is_us2jis)) {
                // JISキーボード設定のMacでないなら、「,」を出力する
                tap_code(KC_COMM);
                return false;
            }
            break;
// 薙刀式 OLEDを使う場合
#ifdef OLED_ENABLE
        case NGSW_WIN...NG_KOTI:
            if (record->event.pressed)
                update_oled = true; // 設定をOLED表示に反映する
            break;
#endif
// 薙刀式
        }
    }

    // 薙刀式
    if (!process_naginata(keycode, record))
        return false;
    // 薙刀式

    // typewriter pairing on jis keyboard
    if (is_us2jis && !twpair_on_jis(keycode, record))
        return false;

  return true;
}

void matrix_init_user(void) {
    // 薙刀式
    uint16_t ngonkeys[] = {KC_H, KC_J};
    uint16_t ngoffkeys[] = {KC_F, KC_G};
    set_naginata(_NAGINATA, ngonkeys, ngoffkeys);
    // 薙刀式
}
