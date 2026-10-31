# Hardware Components

## Project: Arduino Line Follower Robot

This document lists the hardware components used in the development of the autonomous line-following robot.

## 1. Component Inventory

| Component | Quantity | Description |
| Arduino Uno R3 | 1 | Main microcontroller responsible for processing sensor inputs and controlling the motors. |
| TCRT5000 5-Channel Sensor Array | 1 | Detects black and white surface patterns using infrared sensors. |
| L298N Motor Driver Module | 1 | Controls the direction and speed of the two DC motors. |
| N20 DC Geared Motors | 2 | Provides mechanical movement for the robot. |
| Robot Wheels | 2 | Transfers motor rotation into movement. |
| 7.4V 2S Battery Pack | 1 | Supplies electrical power to the robot. |
| Robot Chassis | 1 | Supports and secures the electronic and mechanical components. |
| Jumper Wires | As needed | Connects the electronic components. |

## 2. Component Descriptions

### Arduino Uno R3
- Microcontroller: ATmega328P
- Operating voltage: 5V
- Digital I/O pins: 14
- Analog input pins: 6
- PWM outputs: 6
- Role: Processes infrared sensor readings and generates motor control signals.

### TCRT5000 5-Channel Infrared Sensor Array
- Sensor type: Reflective infrared
- Number of channels: 5
- Detection method: Infrared reflection
- Role: Detects the black tracking line against a white background.

### L298N Motor Driver
- Driver type: Dual H-bridge
- Motor channels: 2
- Control inputs: IN1, IN2, IN3, IN4
- PWM inputs: ENA and ENB
- Role: Controls the direction and speed of the left and right motors.

### N20 DC Geared Motors
- Quantity: 2
- Configuration: Left and right drive motors
- Role: Provides differential movement for steering and navigation.
- Note: Verify the rated voltage and RPM of the specific motors used.

### Battery Pack
- Configuration: 2-cell lithium-ion battery pack
- Nominal voltage: 7.4V
- Fully charged voltage: 8.4V
- Role: Supplies power to the motor driver and robot electronics.

## 3. System Configuration

The Arduino Uno serves as the main controller. The TCRT5000 sensor array provides line-position information, while the Arduino processes the readings and sends direction and PWM signals to the L298N motor driver.

The motor driver independently controls the left and right N20 motors to adjust the robot's movement.

## 4. Additional Notes

- Verify the motor voltage rating before connecting the battery.
- Ensure a common ground between the Arduino and motor driver.
- Calibrate the infrared sensors before operation.
- Check the battery voltage and polarity before powering the system.
