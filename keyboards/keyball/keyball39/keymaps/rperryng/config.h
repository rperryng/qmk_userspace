/*
This is the c configuration file for the keymap

Copyright 2022 @Yowkees
Copyright 2022 MURAOKA Taro (aka KoRoN, @kaoriya)

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#ifdef RGBLIGHT_ENABLE
//#    define RGBLIGHT_EFFECT_BREATHING
//#    define RGBLIGHT_EFFECT_RAINBOW_MOOD
//#    define RGBLIGHT_EFFECT_RAINBOW_SWIRL
//#    define RGBLIGHT_EFFECT_SNAKE
//#    define RGBLIGHT_EFFECT_KNIGHT
//#    define RGBLIGHT_EFFECT_CHRISTMAS
#    define RGBLIGHT_EFFECT_STATIC_GRADIENT
//#    define RGBLIGHT_EFFECT_RGB_TEST
//#    define RGBLIGHT_EFFECT_ALTERNATING
//#    define RGBLIGHT_EFFECT_TWINKLE
#endif

#define TAP_CODE_DELAY 5

// Elite-Pi (RP2040): make the board's reset button enter the bootloader on a
// double-tap. Not enabled by default, which means a flashed board can otherwise
// only be put into bootloader via the controller's BOOTSEL button or QK_BOOT.
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET
#define RP2040_BOOTLOADER_DOUBLE_TAP_RESET_TIMEOUT 500U


// Target layer is set to LA_MOUSE at runtime in keyboard_post_init_user.
#define POINTING_DEVICE_AUTO_MOUSE_ENABLE

// How long the mouse layer stays up after the trackball stops (QMK default 650).
#define AUTO_MOUSE_TIME 1300

// Trackball CPI while SNIPE is held, in units of 100 (default CPI is 500).
#define SNIPE_CPI 2
// CPI after tapping SNIPE_FINE while SNIPE is held. 1 (100) is the sensor floor.
#define SNIPE_FINE_CPI 1

// Bongo cat state, sent from master to the other half.
#define SPLIT_TRANSACTION_IDS_USER USER_BONGOCAT_SYNC
