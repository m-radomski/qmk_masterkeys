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

/* USB Device descriptor parameter */
#define VENDOR_ID 0x2000
#define PRODUCT_ID 0x0608
#define DEVICE_VER 0x0420
#define MANUFACTURER github.com/m-radomski
#define PRODUCT chomiboard2.0
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
