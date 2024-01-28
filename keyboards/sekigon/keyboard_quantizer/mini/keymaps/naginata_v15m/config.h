/* Copyright 2020 sekigon-gonnoc
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

#pragma once

#define VIAL_KEYBOARD_UID {0x05, 0xE4, 0xA1, 0x7F, 0xDC, 0x87, 0xCB, 0x2A}
#define VIAL_UNLOCK_COMBO_ROWS { 0, 1 }
#define VIAL_UNLOCK_COMBO_COLS { 0, 1 }

#define MATRIX_COLS_DEFAULT 8
#define MATRIX_MSGES_ROW 31

#define DYNAMIC_KEYMAP_LAYER_COUNT 8
#define WEAR_LEVELING_BACKING_SIZE (8192 * 2)
#define WEAR_LEVELING_LOGICAL_SIZE 8192


#define QK_NG (QK_KB_0 + 3) // 薙刀式シフトキーのキーコード開始位置

// Linuxで使うときは下1行を有効にする
//#define USB_POLLING_INTERVAL_MS 8   // sets the USB polling rate in milliseconds
//#define TAP_CODE_DELAY 24   // Sets the delay between `register_code` and `unregister_code`

#define NG_USE_KAWASEMI // Mac汎用 → かわせみ専用

#ifdef NG_USE_KAWASEMI
// Keycodes used for starting Unicode input on different platforms
#   define UNICODE_KEY_MAC KC_NO   // かわせみ3用
#endif

// Forces the keyboard to wait for a USB connection to be established before it starts up
#define WAIT_FOR_USB
