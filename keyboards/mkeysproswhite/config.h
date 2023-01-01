/*
 * Copyright (c) 2018 Charlie Waters
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

#include "pin_defs.h"

// key matrix size
#define MATRIX_ROWS 7
#define MATRIX_COLS 15
// layer size: MATRIX_ROWS * MATRIX_COLS * sizeof(uint16_t) = 140 bytes

#define BOOTMAGIC_LITE_ROW 0
#define BOOTMAGIC_LITE_COLUMN 0

#define DEBOUNCE 15

#define LINE_UART_TX B0
#define LINE_UART_RX B1

// inputs (rows are sampled)
#define MATRIX_ROW_PINS \
    { C4, A5, A6, A7, C8, B10, B11 }

// outputs (cols are pulled high)
#define MATRIX_COL_PINS \
    { D1, C1, D0, B8, A11, A0, A1, A2, A8, A4, C5, C9, C13, A10, B1 }

#define DIODE_DIRECTION COL2ROW

// Obins stock firmware has something similar to this already enabled, but disabled by default in QMK
#define PERMISSIVE_HOLD

#ifdef LED_MATRIX_ENABLE
#define LED_MATRIX_LED_COUNT 87
#define LED_MATRIX_KEYPRESSES
#define LED_MATRIX_FRAMEBUFFER_EFFECTS
#define LED_DISABLE_WHEN_USB_SUSPENDED
#define ENABLE_LED_MATRIX_ALPHAS_MODS
#define ENABLE_LED_MATRIX_BREATHING
#define ENABLE_LED_MATRIX_BAND
#define ENABLE_LED_MATRIX_BAND_PINWHEEL
#define ENABLE_LED_MATRIX_BAND_SPIRAL
#define ENABLE_LED_MATRIX_CYCLE_LEFT_RIGHT
#define ENABLE_LED_MATRIX_CYCLE_UP_DOWN
#define ENABLE_LED_MATRIX_CYCLE_OUT_IN
#define ENABLE_LED_MATRIX_DUAL_BEACON
#define ENABLE_LED_MATRIX_SOLID_REACTIVE_SIMPLE
#define ENABLE_LED_MATRIX_SOLID_REACTIVE_WIDE
#define ENABLE_LED_MATRIX_SOLID_REACTIVE_MULTIWIDE
#define ENABLE_LED_MATRIX_SOLID_REACTIVE_CROSS
#define ENABLE_LED_MATRIX_SOLID_REACTIVE_MULTICROSS
#define ENABLE_LED_MATRIX_SOLID_REACTIVE_NEXUS
#define ENABLE_LED_MATRIX_SOLID_REACTIVE_MULTINEXUS
#define ENABLE_LED_MATRIX_SOLID_SPLASH
#define ENABLE_LED_MATRIX_SOLID_MULTISPLASH
#define ENABLE_LED_MATRIX_WAVE_LEFT_RIGHT
#define ENABLE_LED_MATRIX_WAVE_UP_DOWN
#endif
