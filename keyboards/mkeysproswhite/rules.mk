# MCU
MCU = cortex-m0plus
ARMV = 6
USE_FPU = no
MCU_FAMILY = HT32
MCU_SERIES = HT32F523xx
MCU_LDSCRIPT = HT32F52352_PROSWHITE
MCU_STARTUP = ht32f523xx

BOARD = MKEYS_PRO_S_WHITE

OPT_DEFS = -DCORTEX_VTOR_INIT=0x3200 -DCRT0_VTOR_INIT

# Bootloader selection
BOOTLOADER = custom

# Build Options
#   change yes to no to disable
#
BOOTMAGIC_ENABLE = yes       # Enable Bootmagic Lite
MOUSEKEY_ENABLE = no         # Mouse keys
EXTRAKEY_ENABLE = yes        # Audio control and System control
CONSOLE_ENABLE = no          # Console for debug
COMMAND_ENABLE = yes         # Commands for debug and configuration
NKRO_ENABLE = no             # Enable N-Key Rollover
BACKLIGHT_ENABLE = no        # Enable keyboard backlight functionality
RGBLIGHT_ENABLE = no         # Enable keyboard RGB underglow
AUDIO_ENABLE = no            # Audio output
DEBOUNCE_TYPE = sym_eager_pk # Eager debounce

# Custom RGB matrix handling
# RGB_MATRIX_ENABLE = yes
# RGB_MATRIX_DRIVER = custom

# Keys
CUSTOM_MATRIX = lite
KEY_LOCK_ENABLE = no

# Other features
RAW_ENABLE = no
MIDI_ENABLE = no
VIRTSER_ENABLE = no
COMBO_ENABLE = no

LAYOUTS = tkl_ansi

# Master Keys Pro S White
SRC = \
	matrix.c \
