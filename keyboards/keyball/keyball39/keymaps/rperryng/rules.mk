# Elite-Pi (RP2040) controllers rather than the Pro Micro the build guide
# assumes. Set here so `qmk userspace-compile` produces the right .uf2 without
# needing CONVERT_TO on the command line.
CONVERT_TO = elite_pi

# No LEDs are soldered on this build. This is also required to compile: Keyball
# still uses the pre-0.28.0 RGBLED_NUM name, renamed to RGBLIGHT_LED_COUNT
# upstream with no compat shim.
RGBLIGHT_ENABLE = no

OLED_ENABLE = yes

# Ported from the dasbob keymap.
EXTRAKEY_ENABLE = yes   # Media/volume keys on LA_MEDIA
CAPS_WORD_ENABLE = yes  # CW_TOGG on LA_NAVI
TRI_LAYER_ENABLE = yes  # update_tri_layer_state() for LA_NAVI + LA_SYMB_ALT -> LA_NUM_ALT

SRC += oneshot.c
SRC += swapper.c
