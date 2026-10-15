#pragma once

#include QMK_KEYBOARD_H

// Bongo cat on the right-hand OLED. Each paw goes down while a key on that
// half is held, and it idles after a few seconds without keys. The master owns
// the full matrix, so it pushes the cat state to the other half over a split
// transaction (SPLIT_TRANSACTION_IDS_USER).

// Call from keyboard_post_init_user.
void bongocat_init(void);

// Call from housekeeping_task_user.
void bongocat_task(void);

// Call from oled_task_user on the right half.
void bongocat_render(void);
