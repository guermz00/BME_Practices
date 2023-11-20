import cv2

def detect_shapes(image_path):
    # Read the image
    image = cv2.imread(image_path)
    gray = cv2.cvtColor(image, cv2.COLOR_BGR2GRAY)
    blurred = cv2.GaussianBlur(gray, (5, 5), 0)
    thresh = cv2.threshold(blurred, 60, 255, cv2.THRESH_BINARY)[1]

    # Find contours in the thresholded image
    contours, _ = cv2.findContours(thresh.copy(), cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    shapes_detected = []  # List to store names of detected shapes

    # Loop over the contours
    for c in contours:
        # Compute the moment of contour
        M = cv2.moments(c)
        if M["m00"] != 0:
            cX = int((M["m10"] / M["m00"]))
            cY = int((M["m01"] / M["m00"]))
        else:
            cX, cY = 0, 0

        shape = "unidentified"
        peri = cv2.arcLength(c, True)
        approx = cv2.approxPolyDP(c, 0.04 * peri, True)

        # Identify shape based on the number of vertices
        if len(approx) == 3:
            shape = "triangle"
        elif len(approx) == 4:
            # Compute the bounding box of the contour and use the bounding box to compute the aspect ratio
            (x, y, w, h) = cv2.boundingRect(approx)
            ar = w / float(h)
            shape = "square" if ar >= 0.95 and ar <= 1.05 else "rectangle"
        elif len(approx) > 4:
            shape = "circle"

        # Add the detected shape to the list
        shapes_detected.append(shape)

        # Draw the shape on the image
        cv2.drawContours(image, [c], -1, (0, 255, 0), 2)
        cv2.putText(image, shape, (cX, cY), cv2.FONT_HERSHEY_SIMPLEX, 0.5, (255, 255, 255), 2)

    # Save the processed image with detected shapes
    cv2.imwrite('detected_shapes.jpg', image)

    # Display the image with detected shapes
    cv2.imshow('Detected Shapes', image)
    cv2.waitKey(0)  # Wait for a key press to close the window
    cv2.destroyAllWindows()  # Close all windows

    return shapes_detected



while True:
    user_input = input("Press 'Y' to capture image and move motor...").strip().upper()
    if user_input == 'Y':
        capture_image()
        detected_shape = detect_shapes('image.jpg')
        
        # Decide what to do based on the detected shape
        if detected_shape == "square":
            # Move the motor in some way
            steps = 50
        elif detected_shape == "rectangle":
            # Move the motor in a different way
            steps = 100
        else:
            # If no recognized shape, maybe do nothing or alert the user
            steps = 0
            print("No recognized shape.")

        if steps > 0:
            send_command_to_arduino(steps)