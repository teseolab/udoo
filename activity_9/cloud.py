#!/usr/bin/env python
# This program logs a Arduino Sensor on an Udoo Neo to a #Thingspeak Channel
# To use, get a Thingspeak.com account, set up a channel,
# and capture the Channel Key at #https://thingspeak.com/docs/tutorials/
# Then paste channel ID in the code for the value of "key" below.
# Then run as sudo python   FileName1.py
import httplib, urllib
import time
import serial
# seconds to sleep between posts to the channel, API #limit min 15 sec
sleep = 16
#'Put your Thingspeak Channel Key here'
# Thingspeak channel to update
# Public channel URL: https://s.ntnu.no/udoo_g[1,2,3,4]
key_1 = '7D30EE5AN79TNLK9'
key_2 = '0NZKLVGQT2VMTUHI'
key_3 = '6EY6UZDVIEDZM1II'
key_4 = 'X1KTLH3E77V2QNK7'
DEBUG = False
# set to True to get more debug prints in the Python console
DEBUG = False # set to True to get more debug prints in the Python console
#Create serial device for reading serial
arduino = serial.Serial('/dev/ttyMCC',115200,timeout=0)
arduino.flushOutput()
arduino.flushInput()
serial_buffer = ""
line = ""

# sensor coefficient name
sensorValue1 = '0'
temp1 = 0

#init for arduino so Arduino knows it can send data.
arduino.write("I\n")

def ReadArduino(arduino_out):
	global serial_buffer, line
	arduino_out = ""
	serial_data = arduino.read() 		# Read 1 character
	while serial_data: 					# If there is a character proceed
		serial_buffer += serial_data 	# Add character to buffer
		if DEBUG: print "ReadArduino:Serial buffer:",(repr(serial_buffer))
		# if there is a new line in it, then create Line string
		if "\r\n" in serial_buffer:
			if DEBUG: print "ReadArduino:New Line:",(repr(serial_buffer))
			line = serial_buffer
			serial_buffer = "" 			# empty Serial buffer
		serial_data = arduino.read()
		# if there is a Line string then finish reading the Line
		if line:
			# strip string for unwanted characters
			line = line.replace("\r\n", "")
			#line = line.strip(",")
			arduino_out = line
			if DEBUG: print "ReadArduino:arduino_out:", arduino_out
			line = ""
			if arduino_out == "": arduino_out = None
			# add the last character to the new buffer
			serial_buffer += serial_data
			return arduino_out

#Report Udoo Neo Arduino Sensor data to Thingspeak Channel
def writesensordata():
	global temp1, sensorValue1
	while True:
		#read arduino data and make it a integer value
		sensorValue1 = ReadArduino(sensorValue1)
		if sensorValue1 is None:
			sensorValue1 = '0'
		temp1 = (sensorValue1)
		params = urllib.urlencode({'field1': temp1,'key':key })
		headers = {"Content-type": "application/x-www-form-urlencoded","Accept": "text/plain"}
		conn = httplib.HTTPConnection("api.thingspeak.com:80")
		try:
			conn.request("POST", "/update", params, headers)
			response = conn.getresponse()
			print temp1
			print response.status, response.reason
			data = response.read()
			conn.close()
		except:
			print "connection failed"
		break

#sleep for desired amount of time
if __name__ == "__main__":
	while True:
		writesensordata()
		time.sleep(sleep)
	sleep(1800)
