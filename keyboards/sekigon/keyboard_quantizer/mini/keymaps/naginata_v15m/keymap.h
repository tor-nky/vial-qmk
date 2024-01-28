typedef enum {
    KEY_OS_OVERRIDE_DISABLE, /* Disable key override for JP/US OS */
    US_KEY_JP_OS_OVERRIDE_DISABLE, /* Enable US keyboard on JP OS */
    JP_KEY_US_OS_OVERRIDE_DISABLE, /* Enable JP keyboard on US OS */
} key_os_override_t;

// typedef union {
//   uint32_t raw;
//   struct {
//     uint8_t key_os_override;
//   };
// } user_config_t;
