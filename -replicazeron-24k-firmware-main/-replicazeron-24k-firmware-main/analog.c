#include "analog.h"
#include "quantum.h"
#include "hal.h"

static ADCDriver *adcp = &ADCD1;
static const ADCConfig adccfg = {};

static ADCConversionGroup adcgrp = {
    FALSE,          // circular
    1,              // num_channels
    NULL,           // end_cb
    NULL,           // error_cb
    0,              // cr1
    ADC_CR2_SWSTART, // cr2
    ADC_SMPR1_SMP_AN10(ADC_SAMPLE_239P5) | ADC_SMPR1_SMP_AN11(ADC_SAMPLE_239P5) |
    ADC_SMPR1_SMP_AN12(ADC_SAMPLE_239P5) | ADC_SMPR1_SMP_AN13(ADC_SAMPLE_239P5) |
    ADC_SMPR1_SMP_AN14(ADC_SAMPLE_239P5) | ADC_SMPR1_SMP_AN15(ADC_SAMPLE_239P5),
    ADC_SMPR2_SMP_AN0(ADC_SAMPLE_239P5) | ADC_SMPR2_SMP_AN1(ADC_SAMPLE_239P5) |
    ADC_SMPR2_SMP_AN2(ADC_SAMPLE_239P5) | ADC_SMPR2_SMP_AN3(ADC_SAMPLE_239P5) |
    ADC_SMPR2_SMP_AN4(ADC_SAMPLE_239P5) | ADC_SMPR2_SMP_AN5(ADC_SAMPLE_239P5) |
    ADC_SMPR2_SMP_AN6(ADC_SAMPLE_239P5) | ADC_SMPR2_SMP_AN7(ADC_SAMPLE_239P5) |
    ADC_SMPR2_SMP_AN8(ADC_SAMPLE_239P5) | ADC_SMPR2_SMP_AN9(ADC_SAMPLE_239P5),
    ADC_SQR1_NUM_CH(1),
    0,              // sqr2
    0               // sqr3
};

void analogInit(void) {
    adcStart(adcp, &adccfg);
}

int16_t analogReadPin(pin_t pin) {
    // Configurar pin como entrada analógica
    palSetPadMode(PAL_PORT(pin), PAL_PAD(pin), PAL_MODE_INPUT_ANALOG);
    
    // Obtener canal ADC del pin
    uint8_t adc_channel;
    switch (pin) {
        case PAL_LINE(GPIOA, 0): adc_channel = 0; break;
        case PAL_LINE(GPIOA, 1): adc_channel = 1; break;
        case PAL_LINE(GPIOA, 2): adc_channel = 2; break;
        case PAL_LINE(GPIOA, 3): adc_channel = 3; break;
        case PAL_LINE(GPIOA, 4): adc_channel = 4; break;
        case PAL_LINE(GPIOA, 5): adc_channel = 5; break;
        case PAL_LINE(GPIOA, 6): adc_channel = 6; break;
        case PAL_LINE(GPIOA, 7): adc_channel = 7; break;
        case PAL_LINE(GPIOB, 0): adc_channel = 8; break;
        case PAL_LINE(GPIOB, 1): adc_channel = 9; break;
        default: return 512; // Valor neutro si pin no válido
    }
    
    // Configurar canal específico
    adcgrp.sqr3 = ADC_SQR3_SQ1_N(adc_channel);
    
    // Buffer para resultado
    adcsample_t samples[1];
    
    // Realizar conversión
    adcConvert(adcp, &adcgrp, samples, 1);
    
    // Convertir de 12-bit a 10-bit para compatibilidad
    return (int16_t)(samples[0] >> 2);
}

void analogStop(void) {
    adcStop(adcp);
}
