import serial
import sys

ser = serial.Serial(port="COM5", baudrate=115200)
print(ser.readline().decode(), end=" ")
ser.write("<Check>".encode())
print(ser.readline().decode(), end=" ")
print(ser.readline().decode(), end=" ")
print(ser.readline().decode(), end=" ")
print(ser.readline().decode(), end=" ")
sys.stdout.flush()

#!Need to put all python comands in one file; with check on serial port if open;
#!while jumping files, serial port deos not remain open
#!also opening the serial port again, causes the arduino to reset
