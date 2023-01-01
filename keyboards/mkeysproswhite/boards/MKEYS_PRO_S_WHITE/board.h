/*
    ChibiOS - Copyright (C) 2020 Codetector <codetector@codetector.cn>

    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at

        http://www.apache.org/licenses/LICENSE-2.0

    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/

#pragma once
/*
 * Setup for Cooler Master Masterkeys Pro S White
 */

/*
 * Board identifier.
 */
#define BOARD_NAME "Masterkeys Pro S White"

#define HT32F52352

#define FLASH_SIZE (0x10000 - 0x4000) // 64kB - 16kB

#define MBIA043_GCLK_PIN       PAL_LINE(IOPORTC, 10)
#define MBIA043_DCLK_PIN       PAL_LINE(IOPORTA, 14)
#define MBIA043_SDI_PIN        PAL_LINE(IOPORTC, 12)
#define MBIA043_SDO_PIN        PAL_LINE(IOPORTB, 0)
#define MBIA043_LE_PIN         PAL_LINE(IOPORTA, 15)
#define MBIA043_HAS_POWER_PIN
#define MBIA043_PWRCTRL_PIN    PAL_LINE(IOPORTC, 11)

#define LED_ROW1_PIN PAL_LINE(IOPORTC, 15)
#define LED_ROW2_PIN PAL_LINE(IOPORTC, 14)
#define LED_ROW3_PIN PAL_LINE(IOPORTB, 5)
#define LED_ROW4_PIN PAL_LINE(IOPORTB, 4)
#define LED_ROW5_PIN PAL_LINE(IOPORTB, 3)
#define LED_ROW6_PIN PAL_LINE(IOPORTB, 2)
#define LED_ROW7_PIN PAL_LINE(IOPORTD, 3)

#if !defined(_FROM_ASM_)
#    ifdef __cplusplus
extern "C" {
#    endif
void boardInit(void);
#    ifdef __cplusplus
}
#    endif
#endif /* _FROM_ASM_ */
