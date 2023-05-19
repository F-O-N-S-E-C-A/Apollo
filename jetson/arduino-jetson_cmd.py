import threading
import serial

# Serial configuration
SERIAL_PORT = '/dev/ttyTHS1'
BAUD_RATE = 9600

stop = False

# Create a serial connection
ser = serial.Serial(SERIAL_PORT, BAUD_RATE)

# Function to send messages
def send_message():
    global stop
    while not stop:
        message = input(">")
        if message == 'exit':
            stop = True
        else:
            ser.write(message.strip().encode())

# Function to receive messages
def receive_message():
    global stop
    while not stop:
        if ser.in_waiting:
            message = ser.readline().decode().strip()
            print("echo:", message)

# Create and start the send thread
send_thread = threading.Thread(target=send_message)
send_thread.start()

# Create and start the receive thread
receive_thread = threading.Thread(target=receive_message)
receive_thread.start()

# Wait for the threads to finish (this will never happen as they run indefinitely)
send_thread.join()
receive_thread.join()

# Close the serial connection
ser.close()
