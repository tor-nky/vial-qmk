/* Copyright 2018-2020 eswai <@eswai> / Satoru NAKAYA <@tor-nky>
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

/*

  OSで日本語キーボード(logical bit pairing)と設定/認識されているキーボードで、
  USキーキャップの文字、記号(typewriter pairing)を正しく出力する。

  例: Shift + 2 で @ を入力する

  変換された文字はキーリピートが無効です。

  QMKのKey Overrides機能だとリピートが効く一方、キーマップで定義したJP_ATなどは機能しなかった。
  実際にシフト+KC_2を押した場合しか機能しない。

*/

#include QMK_KEYBOARD_H

#if defined(IS_QK_KB) || defined(KC_LNG9)
#   include "keymap_japanese.h"
#else
#   include "keymap_jp.h"
#endif


const uint16_t us2jis[][2] = {
  {KC_LPRN, JP_LPRN},
  {KC_RPRN, JP_RPRN},
  {KC_AT,   JP_AT},
  {KC_LBRC, JP_LBRC},
  {KC_RBRC, JP_RBRC},
  {KC_LCBR, JP_LCBR},
  {KC_RCBR, JP_RCBR},
  // {KC_MINS, JP_MINS},
  {KC_EQL,  JP_EQL},
  {KC_BSLS, JP_YEN},  // Mac対応
  // {KC_SCLN, JP_SCLN},
  {KC_QUOT, JP_QUOT},
  {KC_GRV,  JP_GRV},
  {KC_PLUS, JP_PLUS},
  {KC_COLN, JP_COLN},
  {KC_UNDS, JP_UNDS},
  {KC_PIPE, JP_PIPE},
  {KC_DQT,  JP_DQUO},
  {KC_ASTR, JP_ASTR},
  {KC_TILD, JP_TILD},
  {KC_AMPR, JP_AMPR},
  {KC_CIRC, JP_CIRC},
};

bool twpair_on_jis(uint16_t keycode, keyrecord_t *record) {
  if (!record->event.pressed) return true;

  uint16_t skeycode; // シフトビットを反映したキーコード
  uint8_t mods_lsft = get_mods() & MOD_BIT(KC_LSFT); // シフトキーの状態
  uint8_t mods_rsft = get_mods() & MOD_BIT(KC_RSFT);
  bool shifted = mods_lsft || mods_rsft;

  if (shifted) {
    skeycode = QK_LSFT | keycode;
  } else {
    skeycode = keycode;
  }

  for (int i = 0; i < sizeof(us2jis) / sizeof(us2jis[0]); i++) {
    if (us2jis[i][0] == skeycode) {
      if (((us2jis[i][1] & QK_LSFT) == QK_LSFT) == shifted) {
        tap_code(us2jis[i][1]);
      } else if (shifted) {
        del_mods(mods_lsft | mods_rsft);
        tap_code(us2jis[i][1]);
        add_mods(mods_lsft | mods_rsft);
      } else {
        add_mods(MOD_BIT(KC_LSFT));
        tap_code(us2jis[i][1]);
        del_mods(MOD_BIT(KC_LSFT));
      }
      return false;
    }
  }

  return true;
}
