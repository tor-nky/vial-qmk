VIA_ENABLE = yes
VIAL_ENABLE = yes
VIAL_INSECURE = yes


# QMK_SETTINGS = yes

# TAP_DANCE_ENABLE = yes
# COMBO_ENABLE = yes
# KEY_OVERRIDE_ENABLE = yes
# MAGIC_ENABLE = yes
# GRAVE_ESC_ENABLE = yes

include keyboards/tor_nky/coconut42/keymaps/naginata_v15m/key_override/rules.mk
VPATH += keyboards/tor_nky/coconut42/keymaps/naginata_v15m/key_override

GIT_DESCRIBE := $(shell git describe --tags --long --dirty="\\*" 2>/dev/null)
CFLAGS += -DGIT_DESCRIBE=$(GIT_DESCRIBE)

# Override raw_hid_receive to support both of VIA and VIAL
$(BUILD_DIR)/obj_tor_nky_coconut42_naginata_v15m/quantum/dynamic_keymap.o:: CFLAGS += -Ddynamic_keymap_macro_send=dynamic_keymap_macro_send_vial

OLED_ENABLE = yes
OS_DETECTION_ENABLE = yes
