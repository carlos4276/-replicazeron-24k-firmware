# Replicazeron 24k Firmware

Firmware QMK para el teclado Replicazeron 24k basado en Blue Pill (STM32F103) - Réplica del Azeron keypad.

## 🎮 Características
- **24 teclas** (matriz 4x6 con pines directos)
- **1 joystick analógico** (ejes X/Y + click)
- **Microcontrolador**: STM32F103 (Blue Pill)
- **3 layers**: Base, Gaming, Productivity
- **2 LEDs indicadores** de layer
- **Switch macro físico**
- **Compatible con QMK**

## 🔧 Hardware
### Asignación de Pines
```
🎮 JOYSTICK:
- X axis: A6
- Y axis: A7  
- Click: A8

🔘 MATRIZ 24 TECLAS:
- Row 0: A0, A1, A2, A3, A4, A5
- Row 1: B0, B1, B2, B3, B4, B5
- Row 2: B6, B7, B8, B9, B10, B11
- Row 3: B12, B13, B14, B15, C13, C15

🔴 CONTROLES:
- Macro switch: C14
- LED 1: C13
- LED 2: B15
```

## 📦 Compilación
El firmware se compila automáticamente con GitHub Actions cuando haces push al repositorio.

### Compilación Manual
```bash
cd qmk_firmware
make replicazeron_24k:default
```

## 🚀 Instalación
1. Descarga el archivo `.bin` de las GitHub Actions
2. Flashea usando STM32CubeProgrammer o dfu-util:
```bash
dfu-util -a 0 -s 0x08000000:leave -D replicazeron_24k_default.bin
```

## ⌨️ Layouts

### Layer Base (Default)
```
┌───┬───┬───┬───┬───┬───┐
│ 1 │ 2 │ 3 │ 4 │ 5 │ 6 │
├───┼───┼───┼───┼───┼───┤
│ Q │ W │ E │ R │ T │ Y │
├───┼───┼───┼───┼───┼───┤
│ A │ S │ D │ F │ G │ H │
├───┼───┼───┼───┼───┼───┤
│ Z │ X │ C │ V │ B │ N │
└───┴───┴───┴───┴───┴───┘
```

### Layer Gaming (LED1 encendido)
```
┌───┬───┬───┬───┬───┬───┐
│F1 │F2 │F3 │F4 │F5 │F6 │
├───┼───┼───┼───┼───┼───┤
│ Q │ W │ E │ R │TAB│ Y │
├───┼───┼───┼───┼───┼───┤
│ A │ S │ D │ F │SHF│ H │
├───┼───┼───┼───┼───┼───┤
│CTL│ X │ C │SPC│ B │ N │
└───┴───┴───┴───┴───┴───┘
```

### Layer Productivity (LED2 encendido)
```
┌───┬───┬───┬───┬───┬───┐
│F7 │F8 │F9 │F10│F11│F12│
├───┼───┼───┼───┼───┼───┤
│Cut│Cpy│Pst│Und│Red│ Y │
├───┼───┼───┼───┼───┼───┤
│All│Sav│Del│Fnd│ G │ H │
├───┼───┼───┼───┼───┼───┤
│ Z │ X │ C │ V │ B │ N │
└───┴───┴───┴───┴───┴───┘
```

## 🎮 Funcionamiento
- **Joystick**: Funciona como joystick de PC (X/Y axes)
- **Click joystick**: Envía ESPACIO
- **Switch macro**: Cicla entre layers (Base → Gaming → Productivity)
- **LEDs**: Indican el layer actual

## 📊 Estado del Build
![Build Status](https://github.com/carlos4276/-replicazeron-24k-firmware/workflows/Build%20QMK%20firmware/badge.svg)

## 📜 Licencia
GPL-2.0-or-later

## 👨‍💻 Autor
Carlos4276
