# HC-SR04 (2020 Version) Ultrasonic Ranging Module – User Manual



## Overview

The **HC-SR04 (2020 version)** is a fully backward-compatible ultrasonic ranging module with the same dimensions as the legacy HC-SR04. The upgraded version integrates **UART and I²C interfaces** in addition to the original GPIO trigger/echo mode. By configuring external resistors, the module can operate in **GPIO, UART, or I²C modes**.

Key enhancements include:

- Minimum blind zone of **2 cm**
- Typical maximum detection distance of **4.5 m**
- Ultra-low operating current of **2.2 mA**
- Upgraded demodulation chip **RCWL-9206**, with built-in MCU supporting UART and I²C
- Simplified external circuitry and wider supply voltage (3–5.5 V)

------

## Features

- Professional ultrasonic demodulation and ranging IC **RCWL-9206**
- Supports **GPIO, UART, I²C** interfaces
- Wide supply range: **3.0 – 5.5 V**
- Low power consumption: **2.2 mA typical**
- Minimum blind zone: **2 cm**
- Backward hardware/software compatibility with legacy **HC-SR04**
- Measurement range: **2 cm – 450 cm** (on flat wall target)
- Simplified peripheral design
- Operating temperature: **-10 °C to +70 °C** (depending on transducer housing)

------

## Electrical & Performance Parameters

| Parameter                            | Condition            | Min  | Typ           | Max  | Unit |
| ------------------------------------ | -------------------- | ---- | ------------- | ---- | ---- |
| Supply Voltage (Vcc)                 | —                    | 3.0  | —             | 5.5  | V    |
| Operating Current                    | —                    | 2.2  | —             | 3.0  | mA   |
| Max Detection Range                  | Flat wall target     | 350  | 450           | 600  | cm   |
| Operating Frequency                  | —                    | —    | 40            | —    | kHz  |
| Blind Zone                           | Random within zone   | 2    | —             | 4    | cm   |
| Accuracy                             | Constant temperature | —    | ±2            | —    | %    |
| Resolution                           | Theoretical          | —    | 1             | —    | mm   |
| Detection Angle                      | Max beam spread      | ±15  | ±20           | —    | °    |
| Measurement Cycle Time               | —                    | —    | 200           | —    | ms   |
| Interfaces                           | —                    | —    | GPIO/UART/I²C | —    |      |
| Operating Temp (Plastic transducer)  | —                    | -10  | —             | 60   | °C   |
| Operating Temp (Aluminum transducer) | —                    | -10  | —             | 70   | °C   |

------

## Pin Definition

| Pin  | Name        | GPIO Mode   | UART Mode | I²C Mode | Description                   |
| ---- | ----------- | ----------- | --------- | -------- | ----------------------------- |
| 1    | Vcc         | —           | —         | —        | Power Supply (3–5.5 V)        |
| 2    | Trig/Rx/SCL | Trig Input  | Rx        | SCL      | Trigger / UART Rx / I²C Clock |
| 3    | Echo/Tx/SDA | Echo Output | Tx        | SDA      | Echo / UART Tx / I²C Data     |
| 4    | GND         | —           | —         | —        | Ground Reference              |

------

## Mode Selection

| Mode | R4 Setting | R5 Setting | Default |
| ---- | ---------- | ---------- | ------- |
| GPIO | NC         | NC         | ✔       |
| UART | NC         | 10 kΩ      | —       |
| I²C  | 10 kΩ      | NC         | —       |

------

## Operation

### 1. GPIO Mode (Legacy HC-SR04 Compatible)

![image-20250909153341583](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20250909153341583.png)

- MCU outputs a **>10 µs HIGH pulse** on Trig.

- Module responds with a **HIGH pulse** on Echo, proportional to the measured distance.

- Distance calculation:

  d=T×C2d = \frac{T \times C}{2}

  Where *T* = Echo pulse width, *C* = Speed of sound.

- Speed of sound temperature formula:

  C=331.45+0.61×t[m/s]C = 331.45 + 0.61 \times t \quad [m/s]

  Example values:

  - At 0 °C: 330.45 m/s
  - At 20 °C: 342.62 m/s
  - At 40 °C: 354.85 m/s

> Note: Temperature compensation is required for accurate measurement.

------

### 2. UART Mode

- Baud rate: **9600, N, 8, 1**
- Command/Response:

| Command | Response               | Description                                                  |
| ------- | ---------------------- | ------------------------------------------------------------ |
| 0xA0    | BYTE_H, BYTE_M, BYTE_L | Distance (mm) = ((BYTE_H << 16) + (BYTE_M << 8) + BYTE_L) / 1000 |
| 0xF1    | String                 | Company & firmware version info                              |

**UART Mode Operation:**

Connect the module via a serial port. When the external MCU or PC sends command `0xA0`, the module performs a ranging operation and then returns three bytes of distance data: **BYTE_H, BYTE_M, BYTE_L**.

The distance calculation formula (unit: mm) is as follows:

![image-20250909153230378](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20250909153230378.png)

------

### 3. I²C Mode

- Address: **0x57** (7-bit)

- Write Command:

  ![image-20250909152747603](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20250909152747603.png)

- Read Command:

  ![image-20250909152800178](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20250909152800178.png)

| Operation | I²C Address              | Command / Return Value | Description                                                  |
| --------- | ------------------------ | ---------------------- | ------------------------------------------------------------ |
| Write     | **0xAE** (write address) | `0x01`                 | Start ranging command. The module begins a measurement cycle (max measurement time ≈ 200 ms). |
| Read      | **0xAF** (read address)  | BYTE_H, BYTE_M, BYTE_L | Returns 3 bytes of ranging data, with the most significant byte first. |

![image-20250909153117276](C:\Users\lenovo\AppData\Roaming\Typora\typora-user-images\image-20250909153117276.png)



------

## Application Notes

1. Avoid hot-plugging; always connect **GND first** if power is applied.
2. For irregular surfaces or long distances, perform **multiple measurements and average**.
3. Minimum interval between two measurements: **200 ms**.

