import serial

arduino = serial.Serial('/dev/ttyACM1', 9600)

print('Python side started')
print(arduino.readline().decode('utf-8'))

while(True):
    arduino.write(input('>>> ').encode('utf-8'))
    print(arduino.readline().decode('utf-8'))

