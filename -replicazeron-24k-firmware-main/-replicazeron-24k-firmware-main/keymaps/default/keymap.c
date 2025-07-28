// Copyright 2024 carlos4276
// SPDX-License-Identifier: GPL-2.0-or-later

#include QMK_KEYBOARD_H
#include "analog.h"

// Layer definitions
enum layers {
    _BASE = 0,
    _MACRO1,
    _MACRO2,
    _FUNCTION
};

// Custom keycodes
enum custom_keycodes {
    MACRO_TOGGLE = SAFE_RANGE,
    LED_TOGGLE,
    JOY_MODE
};

// Global variables
static uint8_t current_macro_layer = 0;
static bool led1_state = false;
static bool led2_state = false;
static bool joystick_mode = true;

// Keymap layout
const uint16_t PROGMEM keymaps[][MATRIX_ROWS][MATRIX_COLS] = {
    /* Base Layer - Layout Default
     * ┌───┬───┬───┬───┬───┬───┐
     * │ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │
     * ├───┼───┼───┼───┼───┼───┤
     * │ Q │ W │ E │ R │ T │ Y │
     * ├───┼───┼───┼───┼───┼───┤
     * │ A │ S │ D │ F │ G │ H │
     * ├───┼───┼───┼───┼───┼───┤
     * │ Z │ X │ C │ V │ B │ N │
     * └───┴───┴───┴───┴───┴───┘
     */
    [_BASE] = LAYOUT(
        KC_1,    KC_2,    KC_3,    KC_4,    KC_5,    KC_6,
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_T,    KC_Y,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_G,    KC_H,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N
    ),

    /* Macro Layer 1 - Gaming Mode
     * ┌───┬───┬───┬───┬───┬───┐
     * │F1 │F2 │F3 │F4 │F5 │F6 │
     * ├───┼───┼───┼───┼───┼───┤
     * │ Q │ W │ E │ R │TAB│ Y │
     * ├───┼───┼───┼───┼───┼───┤
     * │ A │ S │ D │ F │SHF│ H │
     * ├───┼───┼───┼───┼───┼───┤
     * │CTL│ X │ C │SPC│ B │ N │
     * └───┴───┴───┴───┴───┴───┘
     */
    [_MACRO1] = LAYOUT(
        KC_F1,   KC_F2,   KC_F3,   KC_F4,   KC_F5,   KC_F6,
        KC_Q,    KC_W,    KC_E,    KC_R,    KC_TAB,  KC_Y,
        KC_A,    KC_S,    KC_D,    KC_F,    KC_LSFT, KC_H,
        KC_LCTL, KC_X,    KC_C,    KC_SPC,  KC_B,    KC_N
    ),

    /* Macro Layer 2 - Productivity Mode
     * ┌───┬───┬───┬───┬───┬───┐
     * │F7 │F8 │F9 │F10│F11│F12│
     * ├───┼───┼───┼───┼───┼───┤
     * │Cut│Cpy│Pst│Und│Red│ Y │
     * ├───┼───┼───┼───┼───┼───┤
     * │All│Sav│Del│Fnd│ G │ H │
     * ├───┼───┼───┼───┼───┼───┤
     * │ Z │ X │ C │ V │ B │ N │
     * └───┴───┴───┴───┴───┴───┘
     */
    [_MACRO2] = LAYOUT(
        KC_F7,   KC_F8,   KC_F9,   KC_F10,  KC_F11,  KC_F12,
        C(KC_X), C(KC_C), C(KC_V), C(KC_Z), C(KC_Y), KC_Y,
        C(KC_A), C(KC_S), KC_DEL,  C(KC_F), KC_G,    KC_H,
        KC_Z,    KC_X,    KC_C,    KC_V,    KC_B,    KC_N
    ),

    /* Function Layer - Configuración
     * ┌───┬───┬───┬───┬───┬───┐
     * │LED│JOY│MAC│   │   │   │
     * ├───┼───┼───┼───┼───┼───┤
     * │   │   │   │   │   │   │
     * ├───┼───┼───┼───┼───┼───┤
     * │   │   │   │   │   │   │
     * ├───┼───┼───┼───┼───┼───┤
     * │   │   │   │   │   │   │
     * └───┴───┴───┴───┴───┴───┘
     */
    [_FUNCTION] = LAYOUT(
        LED_TOGGLE, JOY_MODE, MACRO_TOGGLE, KC_NO, KC_NO, KC_NO,
        KC_NO,      KC_NO,    KC_NO,        KC_NO, KC_NO, KC_NO,
        KC_NO,      KC_NO,    KC_NO,        KC_NO, KC_NO, KC_NO,
        KC_NO,      KC_NO,    KC_NO,        KC_NO, KC_NO, KC_NO
    )
};

// Joystick configuration (solo 1 joystick con X,Y)
joystick_config_t joystick_axes[JOYSTICK_AXIS_COUNT] = {
    JOYSTICK_AXIS_VIRTUAL,  // Joystick X
    JOYSTICK_AXIS_VIRTUAL   // Joystick Y
};

// Initialize keyboard
void keyboard_post_init_user(void) {
    // Initialize LED pins
    setPinOutput(LED_1_PIN);
    setPinOutput(LED_2_PIN);
    
    // Turn off LEDs initially
    writePinLow(LED_1_PIN);
    writePinLow(LED_2_PIN);
    
    // Initialize macro button pin
    setPinInputHigh(MACRO_SWITCH_PIN);
    
    // Initialize joystick click pin
    setPinInputHigh(ANALOG_JOYSTICK_CLICK_PIN);
    
    // Initialize analog system
    analogInit();
}

// Handle analog joystick reading
void matrix_scan_user(void) {
    if (joystick_mode) {
        // Read ÚNICO joystick analógico (A6, A7)
        int16_t x_axis = analogReadPin(ANALOG_JOYSTICK_X_AXIS_PIN);
        int16_t y_axis = analogReadPin(ANALOG_JOYSTICK_Y_AXIS_PIN);
        
        // Convert to joystick range (-512 to 512) with deadzone
        x_axis = (x_axis - 512);
        y_axis = (y_axis - 512);
        
        // Apply deadzone
        if (abs(x_axis) < 50) x_axis = 0;
        if (abs(y_axis) < 50) y_axis = 0;
        
        // Set joystick values
        joystick_set_axis(0, x_axis);
        joystick_set_axis(1, -y_axis); // Invert Y for correct direction
        
        // Handle joystick click
        static bool joy_click_prev = false;
        bool joy_click_current = !readPin(ANALOG_JOYSTICK_CLICK_PIN);
        
        if (joy_click_current && !joy_click_prev) {
            register_code(KC_SPC);
        } else if (!joy_click_current && joy_click_prev) {
            unregister_code(KC_SPC);
        }
        joy_click_prev = joy_click_current;
    }
    
    // Handle macro switch (physical button)
    static bool macro_pressed = false;
    bool macro_current = !readPin(MACRO_SWITCH_PIN);
    
    if (macro_current && !macro_pressed) {
        // Cycle through layers: Base -> Macro1 -> Macro2 -> Base
        current_macro_layer = (current_macro_layer + 1) % 3;
        
        // Update LEDs to show current layer
        switch(current_macro_layer) {
            case 0: // Base layer - LEDs off
                writePinLow(LED_1_PIN);
                writePinLow(LED_2_PIN);
                layer_clear();
                break;
            case 1: // Macro 1 - Gaming (LED1 on)
                writePinHigh(LED_1_PIN);
                writePinLow(LED_2_PIN);
                layer_clear();
                layer_on(_MACRO1);
                break;
            case 2: // Macro 2 - Productivity (LED2 on)
                writePinLow(LED_1_PIN);
                writePinHigh(LED_2_PIN);
                layer_clear();
                layer_on(_MACRO2);
                break;
        }
        
        // Brief confirmation flash
        wait_ms(200);
    }
    macro_pressed = macro_current;
}

// Handle custom keycodes
bool process_record_user(uint16_t keycode, keyrecord_t *record) {
    switch (keycode) {
        case MACRO_TOGGLE:
            if (record->event.pressed) {
                // Same as physical macro switch
                current_macro_layer = (current_macro_layer + 1) % 3;
                
                switch(current_macro_layer) {
                    case 0:
                        writePinLow(LED_1_PIN);
                        writePinLow(LED_2_PIN);
                        layer_clear();
                        break;
                    case 1:
                        writePinHigh(LED_1_PIN);
                        writePinLow(LED_2_PIN);
                        layer_clear();
                        layer_on(_MACRO1);
                        break;
                    case 2:
                        writePinLow(LED_1_PIN);
                        writePinHigh(LED_2_PIN);
                        layer_clear();
                        layer_on(_MACRO2);
                        break;
                }
            }
            return false;
            
        case LED_TOGGLE:
            if (record->event.pressed) {
                led1_state = !led1_state;
                led2_state = !led2_state;
                writePin(LED_1_PIN, led1_state);
                writePin(LED_2_PIN, led2_state);
            }
            return false;
            
        case JOY_MODE:
            if (record->event.pressed) {
                joystick_mode = !joystick_mode;
                
                // Visual feedback - blink both LEDs 3 times
                bool led1_prev = readPin(LED_1_PIN);
                bool led2_prev = readPin(LED_2_PIN);
                
                for (int i = 0; i < 3; i++) {
                    writePinHigh(LED_1_PIN);
                    writePinHigh(LED_2_PIN);
                    wait_ms(100);
                    writePinLow(LED_1_PIN);
                    writePinLow(LED_2_PIN);
                    wait_ms(100);
                }
                
                // Restore previous LED state
                writePin(LED_1_PIN, led1_prev);
                writePin(LED_2_PIN, led2_prev);
            }
            return false;
    }
    return true;
}

// Layer state indicator
layer_state_t layer_state_set_user(layer_state_t state) {
    return state;
}
