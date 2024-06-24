// Copyright 2022 Framework Computer
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "factory.h"

const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
     /*
     *         ┌────┬────┬────┬────┐
     *  4 keys │Esc │Calc│ =  │ <- │
     *         ├────┼────┼────┼────┤
     *  4 keys │ Num│ /  │ *  │ -  │
     *         ├────┼────┼────┼────┤
     *  3 keys │ 7  │ 8  │ 9  │ +  │
     *         ├────┼────┼────┼────┤
     *  4 keys │ 4  │ 5  │ 6  │ +  │
     *         ├────┼────┼────┼────┤
     *  3 keys │ 1  │ 2  │ 3  │Entr│
     *         ├────┼────┼────┼────┤
     *  3 keys │ 0  │ 0  │ .  │Entr│
     *         └────┴────┴────┴────┴
     * 21 total
     */
    /*
   *         ┌────┬────┬────┬────┐
   *  4 keys │Esc │Calc│ =  │ <- │
   *         ├────┼────┼────┼────┤
   *  4 keys │ Num│ /  │ *  │ -  │
   *         ├────┼────┼────┼────┤
   *  3 keys │ 7  │ 8  │ 9  │ +  │
   *         ├────┼────┼────┼────┤
   *  4 keys │ 4  │ 5  │ 6  │ +  │
   *         ├────┼────┼────┼────┤
   *  3 keys │ 1  │ 2  │ 3  │Entr│
   *         ├────┼────┼────┼────┤
   *  3 keys │ 0  │ 0  │ .  │Entr│
   *         └────┴────┴────┴────┴
   * 21 total
   */
    [0] = LAYOUT(
        TO(0),   TO(1),   RGB_VAD, RGB_VAI,
        KC_NUM,  KC_PSLS, KC_PAST, KC_PMNS,
        KC_P7,   KC_P8,   KC_P9,   KC_PPLS,
        KC_P4,   KC_P5,   KC_P6,   KC_PPLS,
        KC_P1,   KC_P2,   KC_P3,   KC_PENT,
        KC_P0,   KC_P0,   KC_PDOT, KC_PENT
    ),
    [1] = LAYOUT(
        TO(0),   TO(1),   RGB_VAD, RGB_VAI,
        PB_1,  PB_2, PB_3,  PB_4,
        PB_5,  PB_6, PB_7, PB_8,
        PB_9,   PB_10,   PB_11,   PB_12,
        PB_13,   PB_14,   PB_15,   PB_16,
        PB_17,   PB_18,   PB_19,   PB_20
    ),
};

const uint8_t programNumToLedIndex[20] = {
    4, 0, 20, 18,
    7, 1, 21, 16,
    6, 3, 23, 19,
    9, 11, 15, 13,
    8, 10, 14, 12
};

uint8_t macroColours[20][3];


bool rgb_matrix_indicators_user(void) {
    if (!IS_LAYER_ON(1)) {
        return true;
    }

    for (uint8_t index = 0; index < 20; index++) {

        uint8_t brightness = rgb_matrix_get_val();

        uint8_t red = macroColours[index][0] * brightness / 255;
        uint8_t green = macroColours[index][1] * brightness / 255;
        uint8_t blue = macroColours[index][2] * brightness / 255;

        rgb_matrix_set_color(programNumToLedIndex[index],
            red, green, blue);
    }

    return true;
}

void handle_macro_hid(uint8_t *data, uint8_t length) {
    // Your code goes here
    // `data` is a pointer to the buffer containing the received HID report
    // `length` is the length of the report - always `RAW_EPSIZE`

    for (uint8_t index = 0; index < length; index++) {
        uint8_t buttonNum = data[index];

        if (buttonNum == 255) { // clear code
            memset(macroColours, 0, sizeof(macroColours));

            return;
        }

        buttonNum &= ~0x80;
        if (buttonNum == 0 || buttonNum > 20) {
            return;
        }

        uint8_t red = data[++index];
        uint8_t green = data[++index];
        uint8_t blue = data[++index];

        macroColours[buttonNum - 1][0] = red;
        macroColours[buttonNum - 1][1] = green;
        macroColours[buttonNum - 1][2] = blue;
    }
}

bool led_update_user(led_t led_state) {
    // Change layer if numlock state changes, either triggered by OS or
    // by numlock key on this keyboard
    if (led_state.num_lock) {
        layer_on(0);
    } else {
        layer_on(1);
    }
    return true;
}