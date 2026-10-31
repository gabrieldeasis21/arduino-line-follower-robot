# Pin Configuration and Wiring

## Project: Arduino Line Follower Robot

This document describes the pin assignments and electrical connections between the Arduino Uno R3, TCRT5000 sensor array, and L298N motor driver.

## 1. TCRT5000 Sensor Array Connections

The five-channel infrared sensor array connects to the Arduino's analog-capable pins, configured as digital inputs.

| TCRT5000 Pin | Arduino Uno Pin | Function |
| OUT1 | A0 | Far-left sensor |
| OUT2 | A1 | Left sensor |
| OUT3 | A2 | Center sensor |
| OUT4 | A3 | Right sensor |
| OUT5 | A4 | Far-right sensor |
| VCC | 5V | Sensor power supply |
| GND | GND | Ground connection |

### Sensor Position Mapping

| Sensor | Position Weight |
| OUT1 | -2 |
| OUT2 | -1 |
| OUT3 | 0 |
| OUT4 | +1 |
| OUT5 | +2 |

The sensor outputs are interpreted as follows in the current source code:

- LOW: Black line detected.
- HIGH: White surface detected.

This polarity must be verified against the actual sensor module.

## 2. L298N Motor Driver Connections

### Left Motor

| L298N Pin | Arduino Uno Pin | Function |
| ENA | D5 | Left motor PWM speed control |
| IN1 | D7 | Left motor direction control |
| IN2 | D8 | Left motor direction control |
| OUT1 | Left motor terminal | Motor output |
| OUT2 | Left motor terminal | Motor output |

### Right Motor

| L298N Pin | Arduino Uno Pin | Function |
| ENB | D6 | Right motor PWM speed control |
| IN3 | D9 | Right motor direction control |
| IN4 | D10 | Right motor direction control |
| OUT3 | Right motor terminal | Motor output |
| OUT4 | Right motor terminal | Motor output |

Remove the ENA and ENB jumpers when using Arduino PWM control.

## 3. Power Supply Connections

| Power Source | Connection | Purpose |
| 7.4V battery positive | L298N motor supply input | Motor power |
| 7.4V battery negative | L298N GND | Power ground |
| Arduino GND | L298N GND | Common ground |
| Arduino 5V | TCRT5000 VCC | Sensor power |

The Arduino can use a separate regulated supply or its VIN input, provided the voltage is within the board's recommended input range.

Do not connect the 7.4V battery directly to the Arduino 5V pin.

## 4. Complete Arduino Pin Summary

| Arduino Pin | Connected Component | Purpose |
| A0 | TCRT5000 OUT1 | Far-left detection |
| A1 | TCRT5000 OUT2 | Left detection |
| A2 | TCRT5000 OUT3 | Center detection |
| A3 | TCRT5000 OUT4 | Right detection |
| A4 | TCRT5000 OUT5 | Far-right detection |
| D5 | L298N ENA | Left motor PWM |
| D6 | L298N ENB | Right motor PWM |
| D7 | L298N IN1 | Left motor direction |
| D8 | L298N IN2 | Left motor direction |
| D9 | L298N IN3 | Right motor direction |
| D10 | L298N IN4 | Right motor direction |

## 5. Wiring Verification Checklist

- [ ] All five infrared sensor outputs are connected.
- [ ] Sensor VCC and GND are connected correctly.
- [ ] ENA and ENB jumpers are removed.
- [ ] Left and right motors are connected to their respective outputs.
- [ ] Battery polarity is verified.
- [ ] Arduino and L298N share a common ground.
- [ ] Motor directions are tested individually.
- [ ] Sensor polarity is verified before running the robot.
