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

#define DYNAMIC_KEYMAP_LAYER_COUNT 8
#define WEAR_LEVELING_BACKING_SIZE (8192 * 2)
#define WEAR_LEVELING_LOGICAL_SIZE 8192

#define VIAL_DEFAULT_PERMISSIVE_HOLD
// #define VIAL_DEFAULT_IGNORE_MOD_TAP_INTERRUPT
// #define VIAL_DEFAULT_RETRO_TAPPING


#define QK_NG (QK_KB_0 + 3) // 薙刀式シフトキーのキーコード開始位置

#define NG_USE_KAWASEMI // Mac汎用 → かわせみ専用
#define UNICODE_KEY_MAC KC_NO   // Keycodes used for starting Unicode input on different platforms

// Forces the keyboard to wait for a USB connection to be established before it starts up
#define WAIT_FOR_USB
