VIA_ENABLE = yes
VIAL_ENABLE = yes
VIAL_INSECURE = yes

SRC += quantizer_mouse.c raw_hid.c

include keyboards/sekigon/keyboard_quantizer/mini/keymaps/naginata_v15m/cli/rules.mk
include keyboards/sekigon/keyboard_quantizer/mini/keymaps/naginata_v15m/key_override/rules.mk
VPATH += keyboards/sekigon/keyboard_quantizer/mini/keymaps/naginata_v15m/cli
VPATH += keyboards/sekigon/keyboard_quantizer/mini/keymaps/naginata_v15m/key_override

GIT_DESCRIBE := $(shell git describe --tags --long --dirty="\\*" 2>/dev/null)
CFLAGS += -DGIT_DESCRIBE=$(GIT_DESCRIBE)

# Override raw_hid_receive to support both of VIA and VIAL
$(BUILD_DIR)/obj_sekigon_keyboard_quantizer_mini_naginata_v15m/quantum/via.o:: CFLAGS += -Draw_hid_receive=raw_hid_receive_vial
$(BUILD_DIR)/obj_sekigon_keyboard_quantizer_mini_naginata_v15m/quantum/dynamic_keymap.o:: CFLAGS += -Ddynamic_keymap_macro_send=dynamic_keymap_macro_send_vial
SRC += tmk_core/protocol/bmp/via_qmk.c


OS_DETECTION_ENABLE = yes
