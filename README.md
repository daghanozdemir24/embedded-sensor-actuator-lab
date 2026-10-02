# Embedded Sensor & Actuator Implementations

A collection of peripheral control drivers, signal processing routines, and actuator interfaces implemented across **ESP32**, **ESP8266**, and **Arduino Leonardo** hardware architectures.

## 📁 Repository Modules

| File | Platform | Core Peripherals / Concepts | Description |
| :--- | :--- | :--- | :--- |
| `esp32_pwm_motor_control.ino` | ESP32 | LEDC Peripheral (`ledcAttach`), 5 kHz PWM | Motor speed modulation across 5 discrete levels (1–5) and stop mode (0) via UART. |
| `esp8266_sound_level_meter.ino` | ESP8266 | ADC (`A0`), Signal Windowing | Peak-to-peak amplitude measurement over a 50 ms sampling window mapped to sound intensity. |
| `leonardo_ultrasonic_radar.ino` | Arduino Leonardo | HC-SR04, Timers (`pulseIn`), Dynamic Alert | Time-of-flight distance calculation with proximity-scaled adaptive LED flashing rates. |

## 🛠️ Module Overviews

### 1. ESP32 Discrete PWM Motor Control (Levels 1–5)
* Utilizes ESP32 Core v3 `ledcAttach` API to drive motor gates via MOSFET.
* Operates at 5 kHz switching frequency with 8-bit resolution (0–255 duty cycle).
* Provides dynamic discrete speed control via serial terminal inputs from **Level 1 to Level 5**, plus **0** to stop:
  * `0`: 0% Duty (PWM = 0, Motor Stopped)
  * `1`: ~20% Duty (PWM = 50)
  * `2`: ~39% Duty (PWM = 100)
  * `3`: ~59% Duty (PWM = 150)
  * `4`: ~78% Duty (PWM = 200)
  * `5`: 100% Duty (PWM = 255, Full Speed)

### 2. ESP8266 Acoustic Peak-to-Peak Acquisition
* Samples the analog microphone output over a 50 ms temporal window to evaluate waveform envelope ($V_{max} - V_{min}$).
* Maps raw ADC signal amplitude to a normalized 1–100 scale using `map()` and `constrain()`.

### 3. Arduino Leonardo Ultrasonic Proximity Tracker
* Generates 10 µs trigger pulses for the HC-SR04 ultrasonic transducer.
* Measures echo pulse width using `pulseIn` to calculate obstacle distance:
```text
Distance (cm) = (Duration * 0.034) / 2
