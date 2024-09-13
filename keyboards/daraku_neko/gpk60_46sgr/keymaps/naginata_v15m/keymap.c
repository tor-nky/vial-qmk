/* SPDX-License-Identifier: GPL-2.0-or-later */

#include QMK_KEYBOARD_H

#include "eeconfig.h"
#include "vial.h"

#include "keymap.h"
#include "os_key_override.h"

#include "keymap_japanese.h"

#ifdef OS_DETECTION_ENABLE
#   include "os_detection.h"
#endif

// 薙刀式
#include "naginata.h"
#ifdef OLED_ENABLE
  bool update_oled = true;
  bool ng_state = false;
#endif
// 薙刀式

// Defines names for use in layer keycodes and the keymap
enum layer_names {
  _QWERTY,
// 薙刀式
  _NAGINATA, // 薙刀式入力レイヤー
// 薙刀式
  _NUMPAD,
  _LOWER,
  _RAISE,
  _ADJUST,
};

#define US_KEY QK_KB_0
#define US2JIS QK_KB_1

#define LOWER MO(_LOWER)
#define RAISE MO(_RAISE)
#define ADJUST MO(_ADJUST)
#define NUMPAD TG(_NUMPAD)
// [_QWERTY]
#define OP_ESC LALT_T(KC_ESC)
#define CTL_TAB LCTL_T(KC_TAB)
#define CM_EISU LGUI_T(KC_LNG2)
#define LOW_BS LT(_LOWER, KC_BSPC)
#define LS_SPC LSFT_T(KC_SPC)
#define RS_SPC RSFT_T(KC_SPC)
#define RAI_ENT LT(_RAISE, KC_ENT)
#define OP_KANA RALT_T(KC_LNG1)
#define SFT_DEL RSFT_T(KC_DEL)
// [_LOWER]
#define ADJ_ENT LT(_ADJUST, KC_PENT)
// [_RAISE]
#define CM_LBRC LGUI(KC_LBRC)
#define CM_RBRC LGUI(KC_RBRC)
#define WSHOOT  SGUI(KC_5)

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
  [_QWERTY] = LAYOUT(
  //,-----------------------------------------------------.      ,--------------------------------------------------------------.
       OP_ESC,    KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,           KC_Y,    KC_U,    KC_I,    KC_O,   KC_P,  KC_MINS, KC_BSPC,
  //|--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
      CTL_TAB,    KC_A,    KC_S,    KC_D,    KC_F,    KC_G,           KC_H,    KC_J,    KC_K,    KC_L, KC_SCLN, KC_QUOT,  KC_ENT,
  //|--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
      KC_LSFT,    KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,           KC_N,    KC_M, KC_COMM,  KC_DOT, KC_SLSH, SFT_DEL,
  //|--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------|
      KC_CAPS,                   KC_LGUI,  LOW_BS,  LS_SPC,         RS_SPC, RAI_ENT, KC_LALT,                    NUMPAD
  //`--------'                 `--------+--------+--------'      `--------------------------'                 `--------'
  ),

  [_LOWER] = LAYOUT(
  //,-----------------------------------------------------.      ,--------------------------------------------------------------.
       KC_GRV, KC_CIRC, KC_RBRC, KC_AMPR, KC_LBRC, KC_BSLS,        KC_COLN,    KC_7,    KC_8,    KC_9, KC_PSLS, KC_PMNS, _______,
  //|--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
      _______, KC_EXLM,   KC_AT, KC_PIPE, KC_LPRN, KC_RPRN,         KC_EQL,    KC_4,    KC_5,    KC_6, KC_PPLS, KC_PAST, _______,
  //|--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
      _______, KC_TILD,  KC_DLR, KC_HASH, KC_LCBR, KC_RCBR,           KC_0,    KC_1,    KC_2,    KC_3, KC_PDOT, KC_PERC,
  //|--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------|
      _______,                   _______, _______, _______,        _______, ADJ_ENT, _______,                   _______
  //`--------'                 `--------+--------+--------'      `--------------------------'                 `--------'
  ),

  [_RAISE] = LAYOUT(
  //,-----------------------------------------------------.      ,--------------------------------------------------------------.
       KC_PWR,   KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,        KC_MS_L, KC_MS_D, KC_MS_U, KC_MS_R, KC_BTN1, KC_BTN2, _______,
  //|--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
      _______,   KC_F6,   KC_F7,   KC_F8,   KC_F9,  KC_F10,        KC_LEFT, KC_DOWN,   KC_UP, KC_RGHT, KC_BTN3,  WSHOOT, _______,
  //|--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
      _______,  KC_F11,  KC_F12, KC_PSCR, KC_SCRL, KC_PAUS,        KC_HOME, KC_PGDN, KC_PGUP,  KC_END, KC_WH_D, KC_WH_U,
  //|--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------|
      _______,                   _______,  ADJUST, _______,        _______, _______, _______,                   _______
  //`--------'                 `--------+--------+--------'      `--------------------------'                 `--------'
  ),

  [_ADJUST] = LAYOUT(
  //,-----------------------------------------------------.      ,--------------------------------------------------------------.
      QK_BOOT, XXXXXXX, XXXXXXX, KC_MPRV, KC_MPLY, KC_MNXT,        XXXXXXX, XXXXXXX, XXXXXXX, XXXXXXX,  US2JIS,   NK_ON, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
      RGB_TOG, RGB_HUI, RGB_SAI, RGB_VAI, KC_VOLU, KC_BRIU,        XXXXXXX,  QK_RBT, NG_KOTI,  NG_MLV,  US_KEY,  NK_OFF, XXXXXXX,
  //|--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
      RGB_MOD, RGB_HUD, RGB_SAD, RGB_VAD, KC_VOLD, KC_BRID,       NGSW_WIN,NGSW_MAC,NGSW_LNX, NG_TAYO, NG_SHOS, KC_RSFT,
  //|--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------|
      XXXXXXX,                   _______, _______, _______,        _______, _______, _______,                   XXXXXXX
  //`--------'                 `--------+--------+--------'      `--------------------------'                 `--------'
  ),

    [_NUMPAD] = LAYOUT(
  //,-----------------------------------------------------.      ,--------------------------------------------------------------.
      _______, _______, _______, _______, _______, _______,        KC_COLN,   KC_P7,   KC_P8,   KC_P9, KC_PSLS, KC_PMNS, _______,
  //|--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,         KC_EQL,   KC_P4,   KC_P5,   KC_P6, KC_PPLS, KC_PAST, _______,
  //|--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
      _______, _______, _______, _______, _______, _______,          KC_P0,   KC_P1,   KC_P2,   KC_P3, KC_PDOT, KC_PERC,
  //|--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------|
      _______,                   _______, _______, _______,        _______, _______, KC_COMM,                   _______
  //`--------'                 `--------+--------+--------'      `--------------------------'                 `--------'
  ),

// 薙刀式
  [_NAGINATA] = LAYOUT(
  //,-----------------------------------------------------.      ,--------------------------------------------------------------.
      _______,    NG_Q,    NG_W,    NG_E,    NG_R,    NG_T,           NG_Y,    NG_U,    NG_I,    NG_O,    NG_P, _______, _______,
  //|--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
      _______,    NG_A,    NG_S,    NG_D,    NG_F,    NG_G,           NG_H,    NG_J,    NG_K,    NG_L, NG_SCLN, _______, _______,
  //|--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------+--------|
      _______,    NG_Z,    NG_X,    NG_C,    NG_V,    NG_B,           NG_N,    NG_M, NG_COMM,  NG_DOT, NG_SLSH, _______,
  //|--------+--------+--------+--------+--------+--------|      |--------+--------+--------+--------+--------+--------|
      _______,                   _______, _______, NG_SHFT,        NG_SHFT, _______, _______,                   _______
  //`--------'                 `--------+--------+--------'      `--------------------------'                 `--------'
  ),
// 薙刀式

  [6] = LAYOUT(
    _______,  _______,    _______,    _______,    _______,    _______,         _______,    _______,    _______,    _______,    _______,    _______, _______, \
    _______,  _______,    _______,    _______,    _______,    _______,         _______,    _______,    _______,    _______,    _______,    _______, _______, \
    _______,  _______,    _______,    _______,    _______,    _______,         _______,    _______,    _______,    _______,    _______,    _______, \
    _______,                          _______,    _______,    _______,         _______,    _______,    _______,                            _______ \
  ),

  [7] = LAYOUT(
    _______,  _______,    _______,    _______,    _______,    _______,         _______,    _______,    _______,    _______,    _______,    _______, _______, \
    _______,  _______,    _______,    _______,    _______,    _______,         _______,    _______,    _______,    _______,    _______,    _______, _______, \
    _______,  _______,    _______,    _______,    _______,    _______,         _______,    _______,    _______,    _______,    _______,    _______, \
    _______,                          _______,    _______,    _______,         _______,    _______,    _______,                            _______ \
  ),
};

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

void keyboard_post_init_user(void) {
    os_key_override_init();

    naginata_config.raw = eeconfig_read_user();
    switch (naginata_config.key_os_override) {
        case KEY_OS_OVERRIDE_DISABLE:
            remove_all_os_key_overrides();
            break;
        case US_KEY_JP_OS_OVERRIDE_DISABLE:
            register_us_key_on_jp_os_overrides();
            break;
        case JP_KEY_US_OS_OVERRIDE_DISABLE:
            register_jp_key_on_us_os_overrides();
            break;
    }
}

#define DEFFERED_KEY_RECORD_LEN 6
static keyrecord_t deferred_key_record[DEFFERED_KEY_RECORD_LEN];

static void push_deferred_key_record(uint16_t keycode, keyevent_t *event) {
    for (int i = 0; i < DEFFERED_KEY_RECORD_LEN; i++) {
        if (deferred_key_record[i].keycode == KC_NO) {
            keyrecord_t record     = {.event = *event, .keycode = keycode};
            deferred_key_record[i] = record;
            return;
        }
    }
}

bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    // To apply key overrides to keycodes combined shift modifier, separate to two actions
    if (keycode >= QK_MODS && keycode <= QK_MODS_MAX) {
        if (record->event.pressed) {
            register_mods(QK_MODS_GET_MODS(keycode));
            uint16_t   deferred_keycode   = QK_MODS_GET_BASIC_KEYCODE(keycode);
            keyevent_t deferred_key_event = (keyevent_t){.type = KEY_EVENT, .key = (keypos_t){.row = VIAL_MATRIX_MAGIC, .col = VIAL_MATRIX_MAGIC}, .pressed = 1, .time = (timer_read() | 1)};
            push_deferred_key_record(deferred_keycode, &deferred_key_event);
        } else {
            uint16_t   deferred_keycode   = QK_MODS_GET_BASIC_KEYCODE(keycode);
            keyevent_t deferred_key_event = ((keyevent_t){.type = KEY_EVENT, .key = (keypos_t){.row = VIAL_MATRIX_MAGIC, .col = VIAL_MATRIX_MAGIC}, .pressed = 0, .time = (timer_read() | 1)});
            unregister_mods(QK_MODS_GET_MODS(keycode));
            push_deferred_key_record(deferred_keycode, &deferred_key_event);
        }
        return false;
    }

    if (record->event.pressed) {
        switch (keycode) {
            case QK_KB_0:
            remove_all_os_key_overrides();
            naginata_config.key_os_override = KEY_OS_OVERRIDE_DISABLE;
            eeconfig_update_user(naginata_config.raw);
            return false;

            case QK_KB_1:
            register_us_key_on_jp_os_overrides();
            naginata_config.key_os_override = US_KEY_JP_OS_OVERRIDE_DISABLE;
            eeconfig_update_user(naginata_config.raw);
            return false;

            case QK_KB_2:
            register_jp_key_on_us_os_overrides();
            naginata_config.key_os_override = JP_KEY_US_OS_OVERRIDE_DISABLE;
            eeconfig_update_user(naginata_config.raw);
            return false;

// 薙刀式 OLEDを使う場合
#ifdef OLED_ENABLE
            case NGSW_WIN...NG_KOTI:
            if (record->event.pressed) {
                update_oled = true; // 設定をOLED表示に反映する
            }
            break;
#endif
// 薙刀式
        }
    }

    // 薙刀式
    if (!process_naginata(keycode, record))
        return false;
    // 薙刀式

    return true;
}

void housekeeping_task_user(void) {
    for (int i = 0; i < DEFFERED_KEY_RECORD_LEN; i++) {
        if (deferred_key_record[i].keycode != KC_NO) {
            g_vial_magic_keycode_override = deferred_key_record[i].keycode;
            action_exec(deferred_key_record[i].event);
            deferred_key_record[i].keycode = KC_NO;
        } else {
            break;
        }
    }
}

void matrix_init_user(void) {
    // 薙刀式
    uint16_t ngonkeys[] = {KC_H, KC_J};
    uint16_t ngoffkeys[] = {KC_F, KC_G};
    set_naginata(_NAGINATA, ngonkeys, ngoffkeys);
    // 薙刀式

    // 自動でOSによってレイヤーや薙刀式の設定を切り替える
#ifdef OS_DETECTION_ENABLE
    wait_ms(400);
    switch (detected_host_os()) {
    case OS_WINDOWS:
        switchOS(NG_WIN);
        break;
    case OS_MACOS:
    case OS_IOS:
        switchOS(NG_MAC);
        break;
    case OS_LINUX:
        switchOS(NG_LINUX);
        break;
    default:
        break;
    }
#endif
}

#include "vial.h"
#include "dynamic_keymap.h"
#include "send_string.h"

#ifdef VIA_ENABLE
#    include "via.h"
#    define DYNAMIC_KEYMAP_EEPROM_START (VIA_EEPROM_CONFIG_END)
#else
#    include "eeconfig.h"
#    define DYNAMIC_KEYMAP_EEPROM_START (EECONFIG_SIZE)
#endif

#ifdef ENCODER_ENABLE
#    include "encoder.h"
#else
#    define NUM_ENCODERS 0
#endif

#ifndef DYNAMIC_KEYMAP_EEPROM_MAX_ADDR
#    define DYNAMIC_KEYMAP_EEPROM_MAX_ADDR (TOTAL_EEPROM_BYTE_COUNT - 1)
#endif

// If DYNAMIC_KEYMAP_EEPROM_ADDR not explicitly defined in config.h,
#ifndef DYNAMIC_KEYMAP_EEPROM_ADDR
#    define DYNAMIC_KEYMAP_EEPROM_ADDR DYNAMIC_KEYMAP_EEPROM_START
#endif

// Encoders are located right after the dynamic keymap
#define VIAL_ENCODERS_EEPROM_ADDR (DYNAMIC_KEYMAP_EEPROM_ADDR + (DYNAMIC_KEYMAP_LAYER_COUNT * MATRIX_ROWS * MATRIX_COLS * 2))
#define DYNAMIC_KEYMAP_ENCODER_EEPROM_ADDR VIAL_ENCODERS_EEPROM_ADDR

#define VIAL_ENCODERS_SIZE (NUM_ENCODERS * DYNAMIC_KEYMAP_LAYER_COUNT * 2 * 2)

// QMK settings area is just past encoders
#define VIAL_QMK_SETTINGS_EEPROM_ADDR (VIAL_ENCODERS_EEPROM_ADDR + VIAL_ENCODERS_SIZE)

#ifdef QMK_SETTINGS
#include "qmk_settings.h"
#define VIAL_QMK_SETTINGS_SIZE (sizeof(qmk_settings_t))
#else
#define VIAL_QMK_SETTINGS_SIZE 0
#endif

// Tap-dance
#define VIAL_TAP_DANCE_EEPROM_ADDR (VIAL_QMK_SETTINGS_EEPROM_ADDR + VIAL_QMK_SETTINGS_SIZE)

#ifdef VIAL_TAP_DANCE_ENABLE
#define VIAL_TAP_DANCE_SIZE (sizeof(vial_tap_dance_entry_t) * VIAL_TAP_DANCE_ENTRIES)
#else
#define VIAL_TAP_DANCE_SIZE 0
#endif

// Combos
#define VIAL_COMBO_EEPROM_ADDR (VIAL_TAP_DANCE_EEPROM_ADDR + VIAL_TAP_DANCE_SIZE)

#ifdef VIAL_COMBO_ENABLE
#define VIAL_COMBO_SIZE (sizeof(vial_combo_entry_t) * VIAL_COMBO_ENTRIES)
#else
#define VIAL_COMBO_SIZE 0
#endif

// Key overrides
#define VIAL_KEY_OVERRIDE_EEPROM_ADDR (VIAL_COMBO_EEPROM_ADDR + VIAL_COMBO_SIZE)

#ifdef VIAL_KEY_OVERRIDE_ENABLE
#define VIAL_KEY_OVERRIDE_SIZE (sizeof(vial_key_override_entry_t) * VIAL_KEY_OVERRIDE_ENTRIES)
#else
#define VIAL_KEY_OVERRIDE_SIZE 0
#endif

// Dynamic macro
#ifndef DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR
#    define DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR (VIAL_KEY_OVERRIDE_EEPROM_ADDR + VIAL_KEY_OVERRIDE_SIZE)
#endif

// Dynamic macros are stored after the keymaps and use what is available
// up to and including DYNAMIC_KEYMAP_EEPROM_MAX_ADDR.
#ifndef DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE
#    define DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE (DYNAMIC_KEYMAP_EEPROM_MAX_ADDR - DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR + 1)
#endif

#ifndef DYNAMIC_KEYMAP_MACRO_DELAY
#    define DYNAMIC_KEYMAP_MACRO_DELAY TAP_CODE_DELAY
#endif

static uint16_t decode_keycode(uint16_t kc) {
    // map 0xFF01 => 0x0100; 0xFF02 => 0x0200, etc
    if (kc > 0xFF00)
        return (kc & 0xFF) << 8;
    return kc;
}

void dynamic_keymap_macro_send(uint8_t id) {
    if (id >= DYNAMIC_KEYMAP_MACRO_COUNT) {
        return;
    }

    // Check the last byte of the buffer.
    // If it's not zero, then we are in the middle
    // of buffer writing, possibly an aborted buffer
    // write. So do nothing.
    void *p = (void *)(DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR + DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE - 1);
    if (eeprom_read_byte(p) != 0) {
        return;
    }

    // Skip N null characters
    // p will then point to the Nth macro
    p         = (void *)(DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR);
    void *end = (void *)(DYNAMIC_KEYMAP_MACRO_EEPROM_ADDR + DYNAMIC_KEYMAP_MACRO_EEPROM_SIZE);
    while (id > 0) {
        // If we are past the end of the buffer, then the buffer
        // contents are garbage, i.e. there were not DYNAMIC_KEYMAP_MACRO_COUNT
        // nulls in the buffer.
        if (p == end) {
            return;
        }
        if (eeprom_read_byte(p) == 0) {
            --id;
        }
        ++p;
    }

    // Send the macro string one or three chars at a time
    // by making temporary 1 or 3 char strings
    char data[4] = {0, 0, 0, 0};
    // We already checked there was a null at the end of
    // the buffer, so this cannot go past the end
    while (1) {
        data[0] = eeprom_read_byte(p++);
        data[1] = 0;
        // Stop at the null terminator of this macro string
        if (data[0] == 0) {
            break;
        }
        if (data[0] == SS_QMK_PREFIX) {
            // If the char is magic, process it as indicated by the next character
            // (tap, down, up, delay)
            data[1] = eeprom_read_byte(p++);
            if (data[1] == 0)
                break;
            if (data[1] == SS_TAP_CODE || data[1] == SS_DOWN_CODE || data[1] == SS_UP_CODE) {
                // For tap, down, up, just stuff it into the array and send_string it
                data[2] = eeprom_read_byte(p++);
                if (data[2] != 0)
                    send_string(data);
            } else if (data[1] == VIAL_MACRO_EXT_TAP || data[1] == VIAL_MACRO_EXT_DOWN || data[1] == VIAL_MACRO_EXT_UP) {
                data[2] = eeprom_read_byte(p++);
                if (data[2] != 0) {
                    data[3] = eeprom_read_byte(p++);
                    if (data[3] != 0) {
                        uint16_t kc;
                        memcpy(&kc, &data[2], sizeof(kc));
                        kc = decode_keycode(kc);
                        switch (data[1]) {
                        case VIAL_MACRO_EXT_TAP:
                            vial_keycode_tap(kc);
                            break;
                        case VIAL_MACRO_EXT_DOWN:
                            vial_keycode_down(kc);
                            break;
                        case VIAL_MACRO_EXT_UP:
                            vial_keycode_up(kc);
                            break;
                        }
                    }
                }
            } else if (data[1] == SS_DELAY_CODE) {
                // Check delay code type is VIA(0xC) or not
                bool is_via = true;
                int  ms     = 0;
                for (int idx = 0; idx < 5; idx++) {
                    uint8_t c = eeprom_read_byte(p + idx);
                    if (c >= '0' && c <= '9') {
                        ms = ms * 10 + c - '0';
                    } else if (c == '|' && idx != 0) {
                        p += idx + 1;
                        break;
                    } else {
                        is_via = false;
                        break;
                    }
                }

                if (!is_via) {
                    // For delay, decode the delay and wait_ms for that amount
                    uint8_t d0 = eeprom_read_byte(p++);
                    uint8_t d1 = eeprom_read_byte(p++);
                    if (d0 == 0 || d1 == 0) break;
                    // we cannot use 0 for these, need to subtract 1 and use 255 instead of 256 for delay calculation
                    ms = (d0 - 1) + (d1 - 1) * 255;
                }

                while (ms--) wait_ms(1);
            }
        } else {
            // If the char wasn't magic, just send it
            send_string_with_delay(data, DYNAMIC_KEYMAP_MACRO_DELAY);
        }
    }
}
