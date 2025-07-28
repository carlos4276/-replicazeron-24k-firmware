#pragma once

#include <stdint.h>
#include "gpio.h"

void analogInit(void);
int16_t analogReadPin(pin_t pin);
void analogStop(void);
