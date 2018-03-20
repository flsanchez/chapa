import serial
import time
import sys

ser = serial.Serial('/dev/ttyACM0',9600)
print "Iniciando comunicacion...",
time.sleep(2)
print "OK!"

while True:

	print "1. On"
	print "2. Off"
	print "3. Direccion"
	print "4. Velocidad +"
	print "5. Velocidad -"
	print "q. Salir"
	sel1 = raw_input("Ingrese seleccion:")

	if sel1 == '1':
		ser.write('1')
	if sel1 == '2':
		ser.write('0')
	if sel1 == '3':
		ser.write('d')
		time.sleep(0.1)
		ser.write('1')
	if sel1 == '4':
		ser.write('+')
	if sel1 == '5':
		ser.write('-')
	if sel1 == 'q':
		break

ser.close()

