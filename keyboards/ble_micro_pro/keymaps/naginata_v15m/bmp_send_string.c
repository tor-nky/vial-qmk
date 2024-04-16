/* Copyright 2024 QMK / Satoru NAKAYA <@tor-nky>
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
#include <ctype.h>
#include <string.h>

#define QUEUE_SIZE_MAX  1024
#define INTERVAL_TICK   8

// キュー
static char queue[QUEUE_SIZE_MAX];
static char *queue_read_p = queue,
            *queue_write_p = queue;
static size_t queue_size = 0;

// キューに文字列を追加
static void bmp_append_string(const char *string) {
    size_t string_size = strlen(string);
    // もし十分な空きがないなら何もしない
    if (string_size > (QUEUE_SIZE_MAX) - queue_size) return;

    queue_size += string_size;
    {
        size_t after_size = queue + (QUEUE_SIZE_MAX) - queue_write_p;
        // 折り返す必要あり
        if (string_size >= after_size) {
            memcpy(queue_write_p, string, after_size);  // 末尾の '\0' はコピーしない
            queue_write_p = queue;
            string += after_size;
            string_size -= after_size;
        }
    }
    if (string_size) {
        memcpy(queue_write_p, string, string_size); // 末尾の '\0' はコピーしない
        queue_write_p += string_size;
    }
}

// キューの先頭から一個取り出す
static char front_pop(void) {
    // キューが空なら退出
    if (!queue_size) return '\0';

    char keycode = *queue_read_p;
    queue_read_p++;
    queue_size--;
    // 末端処理
    if (queue_read_p == queue + (QUEUE_SIZE_MAX)) {
        queue_read_p = queue;
    }
    return keycode;
}

// キュー内の文字列の送出
// 参考: quantum/send_string/send_string.c
static void bmp_send_loop(void) {
    static uint32_t last_read_time = 0;
    static uint32_t interval = 0;
    // 時間が来なければ退出
    if (timer_elapsed32(last_read_time) < interval) return;

    last_read_time = timer_read32();
    interval = 0;
    while (interval < (INTERVAL_TICK) * 12) {
        char ascii_code = front_pop();
        if (!ascii_code) break;
        if (ascii_code == SS_QMK_PREFIX) {
            ascii_code = front_pop();
            if (ascii_code == SS_TAP_CODE) {
                // tap
                uint8_t keycode = front_pop();
                tap_code(keycode);
                interval += (INTERVAL_TICK) * 2;
            } else if (ascii_code == SS_DOWN_CODE) {
                // down
                uint8_t keycode = front_pop();
                register_code(keycode);
                interval += INTERVAL_TICK;
            } else if (ascii_code == SS_UP_CODE) {
                // up
                uint8_t keycode = front_pop();
                unregister_code(keycode);
                interval += INTERVAL_TICK;
            } else if (ascii_code == SS_DELAY_CODE) {
                // delay
                int     ms      = 0;
                uint8_t keycode = front_pop();
                while (isdigit(keycode)) {
                    ms *= 10;
                    ms += keycode - '0';
                    keycode = front_pop();
                }
                interval += ms < INTERVAL_TICK ? INTERVAL_TICK : ms;
                break;
            }
        } else {
            send_char(ascii_code);
            interval += (INTERVAL_TICK) * 2;
        }
    }
    // Bluetooth接続時の次回呼び出し間隔を設定
    if (interval) {
        BMPAPI->app.schedule_next_task(interval);
    }
}

// 文字列の出力
// 文字が一定数を超えたり、ディレイがあると遅延書き出し
void bmp_send_string(const char *string) {
    bmp_append_string(string);
    bmp_send_loop();
}

// 全ての QMK 処理の最後に、次の繰り返しを開始する前に呼び出される関数
void housekeeping_task_kb(void) {
    bmp_send_loop();
}
