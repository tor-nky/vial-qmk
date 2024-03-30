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

#define MAX_QUEUE   1024
#define INTERVAL_MS 8

// キュー
static char queue[MAX_QUEUE];
static char *queue_begin = queue,
            *queue_end = queue;
static unsigned queue_size = 0;
// 時間記録
static uint16_t last_send_time = 0;
static uint16_t delay = 0;

// キューの先頭から一個取り出す
static char front_pop(void) {
    if (!queue_size) return '\0';

    char keycode = *queue_begin;
    queue_begin++;
    queue_size--;
    if (queue_begin == queue + MAX_QUEUE) {
        queue_begin = queue;
    }
    return keycode;
}

// キュー内の文字列の送出
static void bmp_send_loop(void) {
    uint16_t elapsed_time = timer_elapsed(last_send_time);
    if (elapsed_time < delay) {
        return;
    }

    last_send_time = timer_read();
    delay = 0;
    while (delay < 60) {
        char ascii_code = front_pop();
        if (!ascii_code) break;
        if (ascii_code == SS_QMK_PREFIX) {
            ascii_code = front_pop();
            if (ascii_code == SS_TAP_CODE) {
                // tap
                uint8_t keycode = front_pop();
                tap_code(keycode);
                delay += (INTERVAL_MS) * 2;
            } else if (ascii_code == SS_DOWN_CODE) {
                // down
                uint8_t keycode = front_pop();
                register_code(keycode);
                delay += INTERVAL_MS;
            } else if (ascii_code == SS_UP_CODE) {
                // up
                uint8_t keycode = front_pop();
                unregister_code(keycode);
                delay += INTERVAL_MS;
            } else if (ascii_code == SS_DELAY_CODE) {
                // delay
                int     ms      = 0;
                uint8_t keycode = front_pop();
                while (isdigit(keycode)) {
                    ms *= 10;
                    ms += keycode - '0';
                    keycode = front_pop();
                }
                delay += ms;
                return;
            }
        } else {
            send_char(ascii_code);
            delay += INTERVAL_MS;
        }
    }
}

// キューに文字列を追加
void bmp_append_string(const char *string) {
    int string_size = strlen(string);
    // もし十分な空きがないなら何もしない
    if (string_size > (MAX_QUEUE) - queue_size) return;

    queue_size += string_size;
    unsigned buffer_after_size = queue + MAX_QUEUE - queue_end;
    // 折り返す必要あり
    if (string_size > buffer_after_size) {
        memcpy(queue_end, string, buffer_after_size);
        string_size -= buffer_after_size;
        memcpy(queue, string + buffer_after_size, string_size);
        queue_end = queue + string_size;
    } else {
        memcpy(queue_end, string, string_size);
        queue_end += string_size;
    }
}

// 全ての QMK 処理の最後に、次の繰り返しを開始する前に呼び出される関数
void housekeeping_task_user(void) {
    bmp_send_loop();
}
