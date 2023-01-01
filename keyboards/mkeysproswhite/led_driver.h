//
// Credit for reverse engineering and most of the source code here: Hansem Ro (hansemro)
//

#pragma once

#include <stdint.h>

#define MBIA043_NUM_CHANNELS 16
#define MBIA043_SHIFT_REG_WIDTH 10 // bits

#ifndef MBIA043_LE_PIN
    #error "MBIA043_LE_PIN is not defined"
#endif

#ifndef MBIA043_SDI_PIN
    #error "MBIA043_SDI_PIN is not defined"
#endif

#ifndef MBIA043_SDO_PIN
    #error "MBIA043_SDO_PIN is not defined"
#endif

#ifndef MBIA043_DCLK_PIN
    #error "MBIA043_DCLK_PIN is not defined"
#endif

#ifndef MBIA043_GCLK_PIN
    #error "MBIA043_GCLK_PIN is not defined"
#endif

/* Pin used to control power supply to MBIA(s) */
#ifdef MBIA043_HAS_POWER_PIN
#ifndef MBIA043_DCLK_PIN
    #error "MBIA043_DCLK_PIN is not defined"
#endif
#endif

/* INSTRUCTIONS: */
/* Move data in shift-register to a single buffer */
#define MBIA043_DATA_LATCH                  1
/* Move data in all buffers to comparators */
#define MBIA043_GLOBAL_LATCH                2
/* Move configuration register to shift-register */
#define MBIA043_READ_CONFIGURATION          4
/* If previous instruction was MBIA043_ENABLE_WRITE_CONFIGURATION, then move
 * data in shift-register to configuration register
 */
#define MBIA043_WRITE_CONFIGURATION         8
/* Enable MBIA043_WRITE_CONFIGURATION */
#define MBIA043_ENABLE_WRITE_CONFIGURATION  18

/* FUNCTIONS */
void mbia043_init(void);

void mbia043_send_instruction(int instr);
void mbia043_shift_data(uint16_t data, int shift_amount);
void mbia043_shift_data_instr(uint16_t data, int shift_amount, int instr);
uint16_t mbia043_shift_recv(uint16_t data, int shift_amount);

/* MBIA043 has 10-bit (undocumented) configuration register.
 * By default, it is configured to 0b0000000010.
 * On several boards, it is reconfigured to 0b0000001100.
 */
void mbia043_write_configuration(uint16_t config);

/* Returns a length of MBIA043_SHIFT_REG_WIDTH when ready. */
int mbia043_get_shift_register_length(void);
