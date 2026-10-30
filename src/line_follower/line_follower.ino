
/*
 * ============================================================
 * PROJECT: Arduino Line Follower Robot
 * AUTHOR: Gabriel De Asis
 * BOARD: Arduino Uno R3
 *
 * HARDWARE:
 * - Arduino Uno R3
 * - 5-channel TCRT5000 infrared sensor array
 * - L298N dual H-bridge motor driver
 * - 2x N20 DC geared motors
 * - 7.4V 2S battery pack
 *
 * DESCRIPTION:
 * Autonomous robot that follows a black line on a white
 * surface using infrared sensor detection and proportional
 * steering control.
 * ============================================================
 */

// ============================================================
// 1. SENSOR CONFIGURATION
// ============================================================

// Sensor order: Far Left -> Far Right
const int sensors[5] = {
  A0, A1, A2, A3, A4
};

// Sensor output when detecting a black line.
// Change to HIGH if your sensor array uses HIGH for black.
const int BLACK = LOW;

// Position weights for each sensor
const int sensorWeights[5] = {
  -2, -1, 0, 1, 2
};

// ============================================================
// 2. L298N MOTOR DRIVER CONFIGURATION
// ============================================================

// Left motor
const int ENA = 5;
const int IN1 = 7;
const int IN2 = 8;

// Right motor
const int ENB = 6;
const int IN3 = 9;
const int IN4 = 10;

// ============================================================
// 3. CONTROL PARAMETERS
// ============================================================

int baseSpeed = 130;
const int maxSpeed = 200;
const int minSpeed = 0;

// Proportional gain
float Kp = 45.0;

// Previous line position
int lastError = 0;

// ============================================================
// 4. SETUP
// ============================================================

void setup() {

  Serial.begin(9600);

  // Initialize sensor pins
  for (int i = 0; i < 5; i++) {
    pinMode(sensors[i], INPUT);
  }

  // Initialize motor driver pins
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);

  pinMode(ENB, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);

  // Stop motors before starting
  stopMotors();

  delay(1000);

  Serial.println("Line Follower Robot Initialized");
}

// ============================================================
// 5. MAIN LOOP
// ============================================================

void loop() {

  // Read the current line position
  int error = readLinePosition();

  // Check whether the line is detected
  bool lineDetected = false;

  for (int i = 0; i < 5; i++) {

    if (digitalRead(sensors[i]) == BLACK) {
      lineDetected = true;
      break;
    }
  }

  // Handle line-loss recovery
  if (!lineDetected) {

    if (lastError < 0) {

      // Search left
      setMotors(-100, 100);

    } else if (lastError > 0) {

      // Search right
      setMotors(100, -100);

    } else {

      // Stop when previous direction is unknown
      stopMotors();
    }

    return;
  }

  // Calculate proportional correction
  int correction = Kp * error;

  // Calculate individual motor speeds
  int leftSpeed = baseSpeed + correction;
  int rightSpeed = baseSpeed - correction;

  // Restrict motor speed to valid PWM range
  leftSpeed = constrain(
    leftSpeed,
    minSpeed,
    maxSpeed
  );

  rightSpeed = constrain(
    rightSpeed,
    minSpeed,
    maxSpeed
  );

  // Apply motor commands
  setMotors(leftSpeed, rightSpeed);

  // Debugging information
  Serial.print("Error: ");
  Serial.print(error);

  Serial.print(" | Left: ");
  Serial.print(leftSpeed);

  Serial.print(" | Right: ");
  Serial.println(rightSpeed);

  delay(5);
}

// ============================================================
// 6. LINE POSITION DETECTION
// ============================================================

int readLinePosition() {

  int weightedSum = 0;
  int activeSensors = 0;

  for (int i = 0; i < 5; i++) {

    int sensorValue = digitalRead(sensors[i]);

    if (sensorValue == BLACK) {

      weightedSum += sensorWeights[i];

      activeSensors++;
    }
  }

  // Calculate average position of detected sensors
  if (activeSensors > 0) {

    int error = weightedSum / activeSensors;

    lastError = error;

    return error;
  }

  // Return previous position if line is lost
  return lastError;
}

// ============================================================
// 7. MOTOR CONTROL
// ============================================================

void setMotors(int leftSpeed, int rightSpeed) {

  // LEFT MOTOR DIRECTION
  if (leftSpeed >= 0) {

    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);

  } else {

    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
  }

  // RIGHT MOTOR DIRECTION
  if (rightSpeed >= 0) {

    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);

  } else {

    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
  }

  // Apply PWM speed
  analogWrite(
    ENA,
    constrain(abs(leftSpeed), 0, 255)
  );

  analogWrite(
    ENB,
    constrain(abs(rightSpeed), 0, 255)
  );
}

// ============================================================
// 8. STOP MOTORS
// ============================================================

void stopMotors() {

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);

  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);
}
