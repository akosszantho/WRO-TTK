#include <opencv2/opencv.hpp>
#include <wiringPi.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>

using namespace cv;

// Define GPIO pins for ultrasound sensors and serial communication
#define TRIG_PIN_FRONT 0
#define ECHO_PIN_FRONT 1
#define TRIG_PIN_LEFT 2
#define ECHO_PIN_LEFT 3
#define TRIG_PIN_RIGHT 4
#define ECHO_PIN_RIGHT 5
#define TRIG_PIN_BACK 6
#define ECHO_PIN_BACK 7

// Define serial port
#define SERIAL_PORT "/dev/serial0"

// Function to measure distance using an ultrasonic sensor
int measureDistance(int trigPin, int echoPin) {
    digitalWrite(trigPin, LOW);
    delay(30);
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);

    while (digitalRead(echoPin) == LOW);
    long startTime = micros();
    while (digitalRead(echoPin) == HIGH);
    long travelTime = micros() - startTime;

    // Get distance in cm
    int distance = travelTime / 58;
    return distance;
}

// Function to send motor and servo commands to Arduino
void sendCommandsToArduino(int motorSpeed1, int motorSpeed2, int servoPosition) {
    char command[20];
    snprintf(command, sizeof(command), "%d %d %d\n", motorSpeed1, motorSpeed2, servoPosition);
    FILE *serial = fopen(SERIAL_PORT, "w");
    if (serial != NULL) {
        fprintf(serial, "%s", command);
        fclose(serial);
    }
}

// Function to detect color and return a corresponding action
void processFrame(Mat frame, int &motorSpeed1, int &motorSpeed2, int &servoPosition) {
    // Convert the frame to HSV color space
    Mat hsv;
    cvtColor(frame, hsv, COLOR_BGR2HSV);

    // Define color ranges for detection
    Scalar lowerRed = Scalar(0, 100, 100);
    Scalar upperRed = Scalar(10, 255, 255);
    Scalar lowerGreen = Scalar(50, 100, 100);
    Scalar upperGreen = Scalar(70, 255, 255);

    // Threshold the HSV image to get only the colors specified
    Mat redMask, greenMask;
    inRange(hsv, lowerRed, upperRed, redMask);
    inRange(hsv, lowerGreen, upperGreen, greenMask);

    // Calculate the moments of the detected areas
    Moments redMoments = moments(redMask, true);
    Moments greenMoments = moments(greenMask, true);

//EDIT피피피피피피피피피피피피피피피피피피피피피피피피피피피피피피피피피피

    // If significant red color is detected
    if (redMoments.m00 > 10000) {
        // Adjust actions based on red detection (e.g., stop or avoid obstacle)
        motorSpeed1 = 0;
        motorSpeed2 = 0;
    }

    // If significant green color is detected
    if (greenMoments.m00 > 10000) {
        // Adjust actions based on green detection (e.g., continue moving forward)
        motorSpeed1 = 150;
        motorSpeed2 = 150;
    }
}

//EDIT^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^

int main(void) {
    // Initialize wiringPi
    if (wiringPiSetup() == -1) {
        fprintf(stderr, "wiringPi setup failed\n");
        return 1;
    }

    // Set up ultrasound sensor pins
    pinMode(TRIG_PIN_FRONT, OUTPUT);
    pinMode(ECHO_PIN_FRONT, INPUT);
    pinMode(TRIG_PIN_LEFT, OUTPUT);
    pinMode(ECHO_PIN_LEFT, INPUT);
    pinMode(TRIG_PIN_RIGHT, OUTPUT);
    pinMode(ECHO_PIN_RIGHT, INPUT);
    pinMode(TRIG_PIN_BACK, OUTPUT);
    pinMode(ECHO_PIN_BACK, INPUT);

    // Set up serial communication
    FILE *serial = fopen(SERIAL_PORT, "w");
    if (serial == NULL) {
        fprintf(stderr, "Serial port setup failed\n");
        return 1;
    }
    fclose(serial);

    // Open the camera
    VideoCapture cap(0);
    if (!cap.isOpened()) {
        fprintf(stderr, "Error opening video stream\n");
        return -1;
    }

    // Main control loop
    while (1) {
        // Measure distances
        int distanceFront = measureDistance(TRIG_PIN_FRONT, ECHO_PIN_FRONT);
        int distanceLeft = measureDistance(TRIG_PIN_LEFT, ECHO_PIN_LEFT);
        int distanceRight = measureDistance(TRIG_PIN_RIGHT, ECHO_PIN_RIGHT);
        int distanceBack = measureDistance(TRIG_PIN_BACK, ECHO_PIN_BACK);

        // Process camera frame
        Mat frame;
        cap >> frame;

        int motorSpeed1 = 150; // Placeholder value
        int motorSpeed2 = 150; // Placeholder value
        int servoPosition = 90; // Placeholder value (90 degrees is centered)

        // Process frame for color detection
        processFrame(frame, motorSpeed1, motorSpeed2, servoPosition);

        // Logic to adjust speeds and steering based on sensor input
        if (distanceFront < 20) {
            // Example logic: stop if an obstacle is too close in front
            motorSpeed1 = 0;
            motorSpeed2 = 0;
        }

        // Send commands to Arduino
        sendCommandsToArduino(motorSpeed1, motorSpeed2, servoPosition);

        // Delay before the next loop iteration
        delay(100);
    }

    // Release the camera
    cap.release();

    return 0;
}
