BOOTLOADER = qmk-hid
BOOTLOADER_SIZE = 512

SWAP_HANDS_ENABLE = yes

OLED_ENABLE = yes
OLED_DRIVER = SSD1306
COMBO_ENABLE = no
SWAP_HANDS_ENABLE = yes
MOUSEKEY_ENABLE = yes
MAGIC_ENABLE = yes
COMBO_ENABLE = yes
WPM_ENABLE = yes

GRAVE_ESC_ENABLE = no
SPACE_CADET_ENABLE = no
MUSIC_ENABLE = no

ifeq ($(strip $(OLED_ENABLE)), yes)
    ifdef OCEAN_DREAM_ENABLE
        ifeq ($(strip $(OCEAN_DREAM_ENABLE)), yes)
            SRC += ocean_dream.c
            OPT_DEFS += -DOCEAN_DREAM_ENABLE
        endif
    endif
    ifndef OCEAN_DREAM_ENABLE
        SRC += ocean_dream.c
        OPT_DEFS += -DOCEAN_DREAM_ENABLE
    endif
endif

SRC += $(KEYMAP_OUTPUT)/src/keymap_configurator.c

.SECONDEXPANSION:
$(KEYMAP_OUTPUT)/src/keymap_configurator.c: $$(KEYMAP_PATH)/pfn.json
	$(QMK_BIN) json2c --quiet --output $@ $<