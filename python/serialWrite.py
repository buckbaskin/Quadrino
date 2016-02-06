import serial

print('Hello World')

ser = serial.Serial('/dev/ttyACM1', 9600)

for i in range(0,10):
    bytes_out = b''+str(i).encode('utf-8')+b'\n'
    print('python set: '+str(bytes_out.decode('utf-8')))
    ser.write(bytes_out)
    print('python got: '+str(ser.readline().decode('utf-8').strip()))

