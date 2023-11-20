import serial
import time
from picamera import PiCamera

# Initialize camera
camera = PiCamera()
camera.resolution = (1024, 768)

# Initialize serial communication with Arduino
ser = serial.Serial('/dev/ttyACM0', 9600, timeout=1)
ser.flush()

def capture_image():
    camera.capture('image.jpg')
    print("Image captured")

def send_command_to_arduino(command):
    ser.write("{}\n".format(command).encode('utf-8'))
    time.sleep(1)  # Wait for Arduino to process the command

while True:
    input("Press Enter to capture image and move motor...")
    capture_image()
    steps = 100  # Define the number of steps the motor should move
    send_command_to_arduino(steps)
