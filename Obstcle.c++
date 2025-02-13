#include <AFMotor.h>  // Include the AFMotor library

// Create motor objects for M1 and M2
AF_DCMotor motor1(1);  // Motor connected to M1
AF_DCMotor motor2(2);  // Motor connected to M2

// Define ultrasonic sensor pins
const int trigPin = 6;  // Trig pin connected to digital pin 6
const int echoPin = 7;  // Echo pin connected to digital pin 7

void setup() {
  // Set ultrasonic sensor pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize serial communication for debugging
  Serial.begin(9600); 
  Serial.println("Bluetooth Connected! Ready for commands.");

  // Set motor speed (0-255)
  motor1.setSpeed(200);
  motor2.setSpeed(200);
}

void loop() {
  // Measure distance using the ultrasonic sensor
  long distance = measureDistance();

  // Debugging: Print distance to Serial Monitor
  Serial.print("Distance: ");
  Serial.println(distance);


  // Obstacle avoidance logic
  if (distance <= 10) {
    stopMotors();
    
  }

  // Check for Bluetooth command
  if (Serial.available() > 0) {
    char command = Serial.read();  // Read the incoming command
    Serial.print("Received Command: ");
    Serial.println(command);

    // Motor control based on received command
    if (command == 'F') {
      moveForward();
    } else if (command == 'B') {
      moveBackward();
    } else if (command == 'L') {
      turnLeft();
    } else if (command == 'R') {
      turnRight();
    } else if (command == 'S') {
      stopMotors();
    }
  }

  // Small delay for stability
  delay(100);
}

// Function to measure distance using the ultrasonic sensor
long measureDistance() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  long duration = pulseIn(echoPin, HIGH);
  long distance = duration * 0.034 / 2;
  return distance;
}

// Function to move the car forward
void moveForward() {
  motor1.run(FORWARD);
  motor2.run(FORWARD);
}

// Function to move the car backward
void moveBackward() {
  motor1.run(BACKWARD);
  motor2.run(BACKWARD);
}

// Function to turn left
void turnLeft() {
  motor1.run(BACKWARD);
  motor2.run(FORWARD);
}

// Function to turn right
void turnRight() {
  motor1.run(FORWARD);
  motor2.run(BACKWARD);
}

// Function to stop the car
void stopMotors() {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
}
