#pragma once

#include QMK_KEYBOARD_H

// Structure to hold trilayer configuration
typedef struct {
    uint8_t lower_layer;
    uint8_t upper_layer;
    uint8_t adjust_layer;
} trilayer_config_t;

// Function to update the trilayer state
layer_state_t update_trilayer_state(layer_state_t state, uint8_t active_set);

// Function to handle trilayer keycodes
bool process_trilayer_keys(
    uint8_t *active_set,
    uint16_t cycle_keycode, uint16_t lower_keycode, uint16_t upper_keycode,
    uint16_t keycode, keyrecord_t *record
);

// Functions to be implemented by the consumer
uint8_t get_trilayer_set_count(void);
const trilayer_config_t* get_trilayer_config(uint8_t index);
