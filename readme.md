# STM32 Smart Darkness Detection Audio System

Embedded systems project using the STM32L476RG microcontroller for real-time darkness detection and audio alert generation. The system integrates analog sensors, GPIO peripherals, a passive buzzer, and a PAM8302 audio amplifier to create an interactive light-sensitive alarm system.

---

## Project Overview

This project was developed using low-level register programming on the STM32L476RG Nucleo board without HAL libraries. The system continuously monitors ambient light using an LDR sensor and compares the reading against an adjustable threshold set by a potentiometer.

When darkness is detected:
- LED indicator activates
- Passive buzzer generates audio alerts
- PAM8302 amplifier outputs audio to an external speaker
- Push-button control enables or disables music playback

---

## Features

- Real-time darkness detection
- Adjustable sensitivity threshold
- LED visual alert
- Passive buzzer audio output
- PAM8302 amplified speaker output
- Push-button playback control
- Software debouncing
- ADC sensor integration
- Register-level STM32 programming

---

## Hardware Components

| Component | Function |
|---|---|
| STM32L476RG | Main microcontroller |
| LDR Sensor | Ambient light detection |
| Potentiometer | Adjustable threshold |
| LED | Visual indicator |
| Passive Buzzer | Audio alert |
| PAM8302 Amplifier | Speaker amplification |
| Push Button | User control |
| BC547 Transistor | Buzzer driver |

---

## System Block Diagram

```text
LDR Sensor (ADC6)
        │
        ▼
STM32L476RG MCU ───► LED (PA6)
        │
        ├──► Passive Buzzer (PA7)
        │
        └──► PAM8302 Amplifier (PA8)
                        │
                        ▼
                    Speaker

Potentiometer (ADC7) → Sensitivity Control
Push Button (PC13) → Music Enable/Disable
```

---

## Software Architecture

- GPIO configuration using STM32 registers
- ADC configuration for analog sensor readings
- Timer-based delays for software debouncing
- Main polling loop for real-time monitoring
- Audio signal control through GPIO outputs

---

## Development Environment

- STM32CubeIDE
- STM32L476RG Nucleo Board
- Embedded C
- Register-level programming

---

## Future Improvements

- PWM audio tone generation
- Interrupt-driven button handling
- OLED status display
- Low-power sleep modes
- Bluetooth audio integration

---

## Author

Developed for Embedded Systems Engineering coursework and real-time STM32 hardware experimentation.