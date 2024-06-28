#! /bin/python

import cv2
import numpy as np

def detect_color(hsv_frame, lower_bound, upper_bound):
    """Detect color in the frame within the specified HSV bounds."""
    mask = cv2.inRange(hsv_frame, lower_bound, upper_bound)
    result = cv2.bitwise_and(hsv_frame, hsv_frame, mask=mask)
    return result, mask

def main():
    # Define the HSV range for red color
    red_lower_bound1 = np.array([0, 70, 50])
    red_upper_bound1 = np.array([10, 255, 255])
    red_lower_bound2 = np.array([170, 70, 50])
    red_upper_bound2 = np.array([180, 255, 255])
    
    # Define the HSV range for green color
    green_lower_bound = np.array([40, 40, 40])
    green_upper_bound = np.array([90, 255, 255])

    # Initialize the camera
    cap = cv2.VideoCapture(0)

    if not cap.isOpened():
        print("Error: Could not open camera.")
        return

    while True:
        # Capture frame-by-frame
        ret, frame = cap.read()

        if not ret:
            print("Failed to grab frame.")
            break

        # Convert the frame to HSV color space
        hsv_frame = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)

        # Detect red color
        red_result1, red_mask1 = detect_color(hsv_frame, red_lower_bound1, red_upper_bound1)
        red_result2, red_mask2 = detect_color(hsv_frame, red_lower_bound2, red_upper_bound2)
        red_mask = cv2.bitwise_or(red_mask1, red_mask2)

        # Detect green color
        green_result, green_mask = detect_color(hsv_frame, green_lower_bound, green_upper_bound)

        # Determine if there is a significant amount of red or green in the frame
        red_count = cv2.countNonZero(red_mask)
        green_count = cv2.countNonZero(green_mask)

        if red_count > green_count:
            print("Red pole detected.")
        elif green_count > red_count:
            print("Green pole detected.")
        else:
            print("No significant pole detected.")

        # Display the results
        cv2.imshow('Frame', frame)
        cv2.imshow('Red Mask', red_mask)
        cv2.imshow('Green Mask', green_mask)

        # Press 'q' to quit the video stream
        if cv2.waitKey(1) & 0xFF == ord('q'):
            break

    # Release the camera and close all OpenCV windows
    cap.release()
    cv2.destroyAllWindows()

if __name__ == "__main__":
    main()
