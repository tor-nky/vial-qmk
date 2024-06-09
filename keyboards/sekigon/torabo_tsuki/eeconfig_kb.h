
#pragma  once

#include "quantum.h"

#define EECONFIG_KB_VERSION 1

typedef union
{
    struct {
        uint8_t version;
        // 1-
        struct {
            uint8_t cpi_200; // cpi in 200 unit
            uint8_t fine_layer;
            uint8_t fine_div;
            uint8_t rough_layer;
            uint8_t rough_mul;
            int8_t  rotate; // degrees
        } cursor;
        // 8-
        struct {
            struct {
                uint8_t enable : 1;
            } options;
            uint8_t layer;
            uint16_t timeout; // AUTO_MOUSE_TIME in 4ms unit
        } aml;
        // 12-
        struct {
            uint8_t layer;
            struct {
                uint8_t invert : 1;
                uint8_t snap : 1;
            } options;
            uint8_t divide;
        } scroll;
        struct {
            uint8_t type;
            uint8_t mode;
        } battery;
    };
    uint8_t bytes[EECONFIG_KB_DATA_SIZE];
} eeconfig_kb_t;
_Static_assert(sizeof(eeconfig_kb_t) == EECONFIG_KB_DATA_SIZE, "Invalid eeconfig_kb_t size");
_Static_assert(offsetof(eeconfig_kb_t, aml) == 8, "Id is changed");
_Static_assert(offsetof(eeconfig_kb_t, scroll) == 12, "Id is changed");

extern eeconfig_kb_t eeconfig_kb;
void via_custom_value_command_kb(uint8_t *data, uint8_t length);

void battery_type_init(int32_t _);