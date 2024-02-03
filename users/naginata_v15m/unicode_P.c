/* Copyright 2022 QMK / Satoru NAKAYA <@tor-nky>
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
#include "unicode_P.h"

// Keycodes used for starting Unicode input on different platforms
#ifndef UNICODE_KEY_MAC
#    define UNICODE_KEY_MAC KC_LEFT_ALT
#endif

// Delay finishing Unicode input, in ms
#ifndef UNICODE_FINISH_DELAY
#    define UNICODE_FINISH_DELAY 80
#endif

// Borrowed from https://github.com/qmk/qmk_firmware/blob/master/quantum/unicode/unicode.c
void unicode_input_finish(void) {
    extern unicode_config_t unicode_config;
    extern uint8_t          unicode_saved_mods;
    extern led_t            unicode_saved_led_state;

    switch (unicode_config.input_mode) {
        case UNICODE_MODE_MACOS:
            unregister_code(UNICODE_KEY_MAC);
            break;
        case UNICODE_MODE_LINUX:
            tap_code(KC_SPACE);
#if (UNICODE_FINISH_DELAY > TAP_CODE_DELAY)
            wait_ms(UNICODE_FINISH_DELAY - TAP_CODE_DELAY);
#endif
            if (unicode_saved_led_state.caps_lock) {
                tap_code(KC_CAPS_LOCK);
            }
            break;
        case UNICODE_MODE_WINDOWS:
            unregister_code(KC_LEFT_ALT);
            if (!unicode_saved_led_state.num_lock) {
                tap_code(KC_NUM_LOCK);
            }
            break;
        case UNICODE_MODE_WINCOMPOSE:
            tap_code(KC_ENTER);
            break;
        case UNICODE_MODE_EMACS:
            tap_code16(KC_ENTER);
            break;
    }

    set_mods(unicode_saved_mods); // Reregister previously set mods
}

#if defined(__AVR__)
// Borrowed from https://github.com/qmk/qmk_firmware/blob/master/quantum/unicode/utf8.c
// Borrowed from https://nullprogram.com/blog/2017/10/06/
const char *decode_utf8_P(const char *str, int32_t *code_point) {
    const char *next;

    if (pgm_read_byte(str) < 0x80) { // U+0000-007F
        *code_point = pgm_read_byte(str);
        next        = str + 1;
    } else if ((pgm_read_byte(str) & 0xE0) == 0xC0) { // U+0080-07FF
        *code_point = ((int32_t)(pgm_read_byte(str) & 0x1F) << 6) | ((int32_t)(pgm_read_byte(str + 1) & 0x3F) << 0);
        next        = str + 2;
    } else if ((pgm_read_byte(str) & 0xF0) == 0xE0) { // U+0800-FFFF
        *code_point = ((int32_t)(pgm_read_byte(str) & 0x0F) << 12) | ((int32_t)(pgm_read_byte(str + 1) & 0x3F) << 6) | ((int32_t)(pgm_read_byte(str + 2) & 0x3F) << 0);
        next        = str + 3;
    } else if ((pgm_read_byte(str) & 0xF8) == 0xF0 && (pgm_read_byte(str) <= 0xF4)) { // U+10000-10FFFF
        *code_point = ((int32_t)(pgm_read_byte(str) & 0x07) << 18) | ((int32_t)(pgm_read_byte(str + 1) & 0x3F) << 12) | ((int32_t)(pgm_read_byte(str + 2) & 0x3F) << 6) | ((int32_t)(pgm_read_byte(str + 3) & 0x3F) << 0);
        next        = str + 4;
    } else {
        *code_point = -1;
        next        = str + 1;
    }

    // part of a UTF-16 surrogate pair - invalid
    if (*code_point >= 0xD800 && *code_point <= 0xDFFF) {
        *code_point = -1;
    }

    return next;
}

// Borrowed from https://github.com/qmk/qmk_firmware/blob/master/quantum/unicode/unicode.c
void send_unicode_string_P(const char *str) {
    if (!str) {
        return;
    }

    while (pgm_read_byte(str)) {
        int32_t code_point = 0;
        str                = decode_utf8_P(str, &code_point);

        if (code_point >= 0) {
            register_unicode(code_point);
        }
    }
}
#endif
