VIA_ENABLE = yes
VIAL_ENABLE = yes
VIAL_INSECURE = yes


# QMK_SETTINGS = yes

# TAP_DANCE_ENABLE = yes
# COMBO_ENABLE = yes
# KEY_OVERRIDE_ENABLE = yes
# MAGIC_ENABLE = yes
# GRAVE_ESC_ENABLE = yes

include keyboards/daraku_neko/gpk60_46sgr/keymaps/naginata_v15m/key_override/rules.mk
VPATH += keyboards/daraku_neko/gpk60_46sgr/keymaps/naginata_v15m/key_override

GIT_DESCRIBE := $(shell git describe --tags --long --dirty="\\*" 2>/dev/null)
CFLAGS += -DGIT_DESCRIBE=$(GIT_DESCRIBE)

# Override raw_hid_receive to support both of VIA and VIAL
$(BUILD_DIR)/obj_daraku_neko_gpk60_46sgr_naginata_v15m/quantum/dynamic_keymap.o:: CFLAGS += -Ddynamic_keymap_macro_send=dynamic_keymap_macro_send_vial

OS_DETECTION_ENABLE = yes

RING_BUFFERED_6KRO_REPORT_ENABLE = yes
	# USB 6-Key Rollover - Instead of stopping any new input once 6 keys
	# are pressed, the oldest key is released and the new key is pressed.
DEBOUNCE_TYPE = sym_defer_pk	# debouncing per key.
