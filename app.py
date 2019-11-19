import serial

ser = serial.Serial('/dev/ttyACM0',9600)
readOut = 0
while True:
	readOut = int(ser.readline().decode('ascii'))
	print (readOut)
