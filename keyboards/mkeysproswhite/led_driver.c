//
// Credit for reverse engineering and most of the source code here: Hansem Ro (hansemro)
//

#include "hal.h"
#include "gpio.h"
#include "quantum.h"
#include "led_driver.h"

#ifdef LED_MATRIX_ENABLE

#ifdef NL
#error "NL already defined"
#endif
#define NL NO_LED

led_config_t g_led_config = {
    { // KEY Matrix to LED Index
//          Col1 Col2 Col3 Col4 Col5 Col6 Col7 Col8 Col9 Col10 Col11 Col12 Col13 Col14 Col15
/*Row1*/{   0,   1,   2,   3,   4,   5,   6,   7,   8,   9,    10,   11,   12,   13,   14},
/*Row2*/{   16,  17,  18,  19,  20,  21,  22,  23,  24,  25,   26,   27,   28,   NL,   29},
/*Row3*/{   33,  34,  35,  36,  37,  38,  39,  40,  41,  42,   43,   44,   45,   46,   30},
/*Row4*/{   50,  51,  52,  53,  54,  55,  56,  57,  58,  59,   60,   61,   NL,   62,   47},
/*Row5*/{   63,  NL,  64,  65,  66,  67,  68,  69,  70,  71,   72,   73,   NL,   74,   75},
/*Row6*/{   76,  77,  78,  NL,  NL,  NL,  79,  NL,  NL,  80,   81,   82,   83,   84,   85},
/*Row7*/{   NL,  15,  31,  32,  NL,  NL,  NL,  NL,  48,  49,   NL,   NL,   NL,   NL,   86},
    }, { // LED Index to Physical Position
        {  0,   0}, { 26,   0}, { 39,   0}, { 52,   0}, { 65,   0}, { 84,   0}, { 97,   0}, {110,   0}, {123,   0}, {143,   0}, {156,   0}, {169,   0}, {182,   0}, {198,   0}, {211,   0}, {224,   0},
        {  0,  17}, { 13,  17}, { 26,  17}, { 39,  17}, { 52,  17}, { 65,  17}, { 78,  17}, { 91,  17}, {104,  17}, {117,  17}, {130,  17}, {143,  17}, {156,  17}, {175,  17}, {198,  17}, {211,  17}, {224,  17},
        {  3,  29}, { 19,  29}, { 32,  29}, { 45,  29}, { 58,  29}, { 71,  29}, { 84,  29}, { 97,  29}, {110,  29}, {123,  29}, {136,  29}, {149,  29}, {162,  29}, {172,  29}, {198,  29}, {211,  29}, {224,  29},
        {  5,  41}, { 23,  41}, { 36,  41}, { 49,  41}, { 62,  41}, { 75,  41}, { 88,  41}, {101,  41}, {114,  41}, {127,  41}, {140,  41}, {153,  41}, {174,  41},
        {  8,  52}, { 29,  52}, { 42,  52}, { 55,  52}, { 68,  52}, { 81,  52}, { 94,  52}, {107,  52}, {120,  52}, {133,  52}, {146,  52}, {170,  52}, {211,  52},
        {  2,  64}, { 18,  64}, { 34,  64}, { 83,  64}, {131,  64}, {148,  64}, {164,  64}, {180,  64}, {198,  64}, {211,  64}, {224,  64},
    }, { // LED Index to Flag
        4,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,  4, 4, 4,
        4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    4,
        4,    4, 4, 4, 4, 4, 4, 4, 4, 4, 4,    4,     4,
        4, 4, 4,          4,          4, 4, 4, 4,  4, 4, 4,
    }
};

uint8_t led_brightness[MATRIX_ROWS * MBIA043_NUM_CHANNELS];

static uint32_t LEDA_GPIO_ROW_PINS[MATRIX_ROWS] = {
    LED_ROW7_PIN,
    LED_ROW1_PIN,
    LED_ROW2_PIN,
    LED_ROW3_PIN,
    LED_ROW4_PIN,
    LED_ROW5_PIN,
    LED_ROW6_PIN,
};
static unsigned int LED_ROW_NUM = 0;

/* Disable row pins by setting to tristate */
static void mbia043_reset_row_pins(void) {
    for (int i = 0; i < MATRIX_ROWS; i++) {
        writePinLow(LEDA_GPIO_ROW_PINS[i]);
    }
    return;
}

/* Flush a row's RGB values to MBIA043s starting with output channel 16
 * to buffers. Requires OVERALL_LATCH instruction afterwards to update
 * comparators from buffers.
 * */
static inline void mbia043_write_value_row(int row) {
    writePinLow(MBIA043_LE_PIN);
    for (int i = 0; i < MBIA043_NUM_CHANNELS - MATRIX_COLS; i++) {
        mbia043_shift_data_instr(0, MBIA043_SHIFT_REG_WIDTH, MBIA043_DATA_LATCH);
    }
    for (int i = MATRIX_COLS - 1; i >= 0; i--) {
        mbia043_shift_data_instr(led_brightness[g_led_config.matrix_co[row][i]] << 8, MBIA043_SHIFT_REG_WIDTH, MBIA043_DATA_LATCH);
    }
    writePinLow(MBIA043_SDI_PIN);
    writePinLow(MBIA043_DCLK_PIN);
    return;
}

static void mbia043_set_value(int index, uint8_t value) {
    led_brightness[index] = value;
}

static void mbia043_set_value_all(uint8_t value) {
    for (int i = 0; i < LED_MATRIX_LED_COUNT; i++) {
        led_brightness[i] = value;
    }
}

static void mbia043_flush(void) { }

/* BFTM1 timer routine to update/flush RGB values one row at a time */
static void timer_callback(GPTDriver *gptp) {
    mbia043_reset_row_pins();
    mbia043_send_instruction(MBIA043_GLOBAL_LATCH);
    setPinOutput(LEDA_GPIO_ROW_PINS[LED_ROW_NUM]);
    writePinHigh(LEDA_GPIO_ROW_PINS[LED_ROW_NUM]);
    mbia043_write_value_row(LED_ROW_NUM);
    LED_ROW_NUM = (LED_ROW_NUM + 1);
    if(LED_ROW_NUM >= MATRIX_ROWS) {
        LED_ROW_NUM = 0;
    }
    return;
}

/* BFTM1 timer configuration:
 * - Input frequency = 48 MHz
 * - Compare value = 40,000 ticks
 */
static const GPTConfig BFTM1_config = {
    .frequency = HT32_CK_AHB_FREQUENCY,
    .callback = timer_callback,
};

/* GPTM1 PWM configuration:
 * - Input frequency = 48 MHz
 * - Output frequency = 3.6 MHz
 */
static const PWMConfig GPTM1_config = {
    .frequency = HT32_CK_AHB_FREQUENCY,
    .period = (HT32_CK_AHB_FREQUENCY / 3600000) - 1,
    .callback = NULL,
    .channels = {
        [0] = {
            .mode = PWM_OUTPUT_ACTIVE_LOW,
            .callback = NULL,
        },
    },
};

void mbia043_init(void) {
    /* Configure MBIA pins */
    setPinOutput(MBIA043_DCLK_PIN);
    setPinOutput(MBIA043_GCLK_PIN);
    setPinOutput(MBIA043_LE_PIN);
    setPinOutput(MBIA043_SDI_PIN);
    writePinHigh(MBIA043_DCLK_PIN);
    writePinHigh(MBIA043_LE_PIN);
    writePinHigh(MBIA043_SDI_PIN);
    setPinInput(MBIA043_SDO_PIN);

#ifdef MBIA043_HAS_POWER_PIN
    /* Power on MBIA */
    setPinOutput(MBIA043_PWRCTRL_PIN);
    writePinLow(MBIA043_PWRCTRL_PIN);
#endif

    /* Start/configure PWM (at GCLK pin) */
    pwmStart(&PWMD_GPTM1, &GPTM1_config);
    writePinHigh(MBIA043_GCLK_PIN);
    palSetLineMode(MBIA043_GCLK_PIN, PAL_MODE_OUTPUT_PUSHPULL | PAL_MODE_HT32_AF(AFIO_TM));

    int len = 0;
    /* Wait until shift register becomes ready */
    while (len != MBIA043_SHIFT_REG_WIDTH) {
        len = mbia043_get_shift_register_length();
    }

    /* Set configuration */
    uint16_t mbia043_config = 0xc;
    mbia043_write_configuration(mbia043_config);

    /* Start PWM and BFTM1 */
    pwmEnableChannel(&PWMD_GPTM1, 0, PWM_FRACTION_TO_WIDTH(&PWMD_GPTM1, 2, 1));
    gptStart(&GPTD_BFTM1, &BFTM1_config);
    if (GPTD_BFTM1.state == GPT_READY) {
        gptStartContinuous(&GPTD_BFTM1, 40000UL);
    }

    return;
}

const led_matrix_driver_t led_matrix_driver = {
    .init = mbia043_init,
    .flush = mbia043_flush,
    .set_value = mbia043_set_value,
    .set_value_all = mbia043_set_value_all,
};

/* Send 'instr' number of DCLK pulses while LE is asserted high. */
void inline mbia043_send_instruction(int instr) {
    writePinLow(MBIA043_LE_PIN);
    __NOP();
    __NOP();
    writePinHigh(MBIA043_LE_PIN);
    while (instr-- > 0) {
        __NOP();
        __NOP();
        writePinLow(MBIA043_DCLK_PIN);
        __NOP();
        __NOP();
        writePinHigh(MBIA043_DCLK_PIN);
    }
    writePinLow(MBIA043_LE_PIN);
    return;
}

/* Transmit data to shift-register with shift_amount number of DCLK pulses.
 *
 * Note: Transmission begins with MSB at data[15].
 */
void inline mbia043_shift_data(uint16_t data, int shift_amount) {
    while (shift_amount-- > 0) {
        __NOP();
        __NOP();
        writePinLow(MBIA043_DCLK_PIN);
        // set SDI to data[15]
        if(data & 0x8000) {
            writePinHigh(MBIA043_SDI_PIN);
        } else {
            writePinLow(MBIA043_SDI_PIN);
        }
        __NOP();
        __NOP();
        // clock in data
        writePinHigh(MBIA043_DCLK_PIN);
        data = (data & 0x7fff) << 1;
    }
    return;
}

/* Transmit data to shift-register with shift_amount number of DCLK pulses,
 * and assert LE for the last instr number of DCLK pulses.
 *
 * Note: Assumes instr is less than shift_amount.
 * Note: Transmission begins with MSB at data[15].
 */
void mbia043_shift_data_instr(uint16_t data, int shift_amount, int instr) {
    if (instr < shift_amount) {
        writePinLow(MBIA043_LE_PIN);
        mbia043_shift_data(data, shift_amount-instr);
        data = data << (shift_amount-instr);
        writePinHigh(MBIA043_LE_PIN);
        mbia043_shift_data(data, instr);
        writePinLow(MBIA043_LE_PIN);
    }
    return;
}

/* Transmit data to shift-register with shift_amount number of DCLK pulses,
 * and read shift_amount bits of data from (last-in-cascade) shift-register.
 *
 * Note: Transmission begins with MSB at data[15].
 */
uint16_t mbia043_shift_recv(uint16_t data, int shift_amount) {
    uint16_t recv = 0;
    while (shift_amount-- > 0) {
        __NOP();
        __NOP();
        writePinLow(MBIA043_DCLK_PIN);
        recv = (recv << 1) | readPin(MBIA043_SDO_PIN);
        // set SDI to data[15]
        // writePin(MBIA043_SDI_PIN, data & 0x8000);
        if(data & 0x8000) {
            writePinHigh(MBIA043_SDI_PIN);
        } else {
            writePinLow(MBIA043_SDI_PIN);
        }
        __NOP();
        __NOP();
        // clock in data
        writePinHigh(MBIA043_DCLK_PIN);
        data = (data & 0x7fff) << 1;
    }
    return recv;
}

/* Write configuration data to each MBIA043.
 *
 * Note: order of array follows order from SDO to SDI pins.
 */
void mbia043_write_configuration(uint16_t config) {
    mbia043_send_instruction(MBIA043_ENABLE_WRITE_CONFIGURATION);
    mbia043_shift_data_instr(config << 6, MBIA043_SHIFT_REG_WIDTH, MBIA043_WRITE_CONFIGURATION);
}

/* Find length of shift-register by clearing shift-register with 0s, writing
 * with 1s, and checking how many DCLK pulses until a 1 is detected.
 */
int mbia043_get_shift_register_length(void) {
    int len = 0;
    writePinLow(MBIA043_LE_PIN);
    // clear shift register
    mbia043_shift_data(0, MBIA043_SHIFT_REG_WIDTH);
    // write 1s until 1 appears on SDO
    int out = readPin(MBIA043_SDO_PIN);
    while (!out) {
        len++;
        mbia043_shift_data(1U << 15, 1);
        out = readPin(MBIA043_SDO_PIN);
    }
    return len;
}

#endif
