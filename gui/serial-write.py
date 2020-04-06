import serial
import sys

ser = serial.Serial(port="COM5", baudrate=115200)
var = input()
#ser.write(var.encode())
#ser.readline()
#ser.readline()
#print(ser.readline())
#print(ser.readline())
#print(ser.readline())
#ser.readline()
#ser.readline()