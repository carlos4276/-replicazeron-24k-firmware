#pragma once

#include "config_common.h"

// Configuración de matrix para 24 PINES DIRECTOS (4x6)
#define MATRIX_ROWS 4
#define MATRIX_COLS 6

// Pines analógicos para 1 SOLO joystick
#define ANALOG_JOYSTICK_X_AXIS_PIN PAL_LINE(GPIOA, 6)
#define ANALOG_JOYSTICK_Y_AXIS_PIN PAL_LINE(GPIOA, 7)

// Pin para click del joystick
#define ANALOG_JOYSTICK_CLICK_PIN PAL_LINE(GPIOA, 8)

// Pin para pulsador macro (switch físico)
#define MACRO_SWITCH_PIN PAL_LINE(GPIOC, 14)

// Pines para LEDs indicadores
#define LED_1_PIN PAL_LINE(GPIOC, 13)
#define LED_2_PIN PAL_LINE(GPIOB, 15)

// Configuración de joystick (solo 1 joystick = 2 ejes)
#define JOYSTICK_AXES_COUNT 2
#define JOYSTICK_BUTTON_COUNT 1

// Configuración USB
#define VENDOR_ID       0xFEED
#define PRODUCT_ID      0x0000
#define DEVICE_VER      0x0001
#define MANUFACTURER    "Carlos4276"
#define PRODUCT         "Replicazeron 24k"

// Configuración adicional
#define DEBOUNCE 5
#define TAPPING_TERM 200

// Configuración ADC
#define ADC_RESOLUTION 10
