import serial
print('Hello World')
ser = serial.Serial('/dev/ttyACM0', 9600)
while True:
    print(ser.readline())

