/*
 * Copyright (c) 2018 Yaotian Feng
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#pragma once
#include "quantum.h"
#include <stdint.h>

typedef struct __attribute__((__packed__)) {
    uint8_t _dummy[10];
    bool    caps_lock;
} ble_capslock_t;
extern ble_capslock_t ble_capslock;

#define XXX KC_NO

// Matrix keymap
// clang-format off
#define LAYOUT_tkl_ansi( \
      K00,        K01,  K02,  K03,  K04,  K05,  K06,  K07,  K08,  K09,  K0A,  K0B,  K0C,      K0D,  K0E,  K61,  \
      K10,  K11,  K12,  K13,  K14,  K15,  K16,  K17,  K18,  K19,  K1A,  K1B,  K1C,  K1E,      K2E,  K62,  K63,  \
      K20,  K21,  K22,  K23,  K24,  K25,  K26,  K27,  K28,  K29,  K2A,  K2B,  K2C,  K2D,      K3E,  K68,  K69,  \
      K30,  K31,  K32,  K33,  K34,  K35,  K36,  K37,  K38,  K39,  K3A,  K3B,        K3D,                        \
      K40,        K42,  K43,  K44,  K45,  K46,  K47,  K48,  K49,  K4A,  K4B,        K4D,            K4E,        \
      K50,  K51,  K52,                    K56,                    K59,  K5A,  K5B,  K5C,      K5D,  K5E,  K6E   \
) { \
    { K00,  K01,  K02,  K03,  K04,  K05,  K06,  K07,  K08,  K09,  K0A,  K0B,  K0C,  K0D,  K0E },  \
    { K10,  K11,  K12,  K13,  K14,  K15,  K16,  K17,  K18,  K19,  K1A,  K1B,  K1C,  XXX,  K1E },  \
    { K20,  K21,  K22,  K23,  K24,  K25,  K26,  K27,  K28,  K29,  K2A,  K2B,  K2C,  K2D,  K2E },  \
    { K30,  K31,  K32,  K33,  K34,  K35,  K36,  K37,  K38,  K39,  K3A,  K3B,  XXX,  K3D,  K3E },  \
    { K40,  XXX,  K42,  K43,  K44,  K45,  K46,  K47,  K48,  K49,  K4A,  K4B,  XXX,  K4D,  K4E },  \
    { K50,  K51,  K52,  XXX,  XXX,  XXX,  K56,  XXX,  XXX,  K59,  K5A,  K5B,  K5C,  K5D,  K5E },  \
    { XXX,  K61,  K62,  K63,  XXX,  XXX,  XXX,  XXX,  K68,  K69,  XXX,  XXX,  XXX,  XXX,  K6E }   \
}
// clang-format on

enum AP2KeyCodes {
    KC_AP2_BT1 = SAFE_RANGE,
    KC_AP2_BT2,
    KC_AP2_BT3,
    KC_AP2_BT4,
    KC_AP2_BT_UNPAIR,
    KC_AP2_USB,
    KC_AP_LED_ON,
    KC_AP_LED_OFF,
    KC_AP_LED_TOG,
    KC_AP_LED_NEXT_PROFILE,
    KC_AP_LED_PREV_PROFILE,
    KC_AP_LED_NEXT_INTENSITY,
    KC_AP_LED_SPEED,
    KC_AP_RGB_VAI,
    KC_AP_RGB_VAD,
    KC_AP_RGB_TOG,
    KC_AP_RGB_MOD,
    AP2_SAFE_RANGE,
};

#undef SAFE_RANGE
#define SAFE_RANGE AP2_SAFE_RANGE
