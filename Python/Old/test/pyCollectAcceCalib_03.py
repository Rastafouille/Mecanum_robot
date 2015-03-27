__author__ = 'NM242826'

import serial

repDataTraj = "data_trajectory/square/"

# Check your COM port and baud rate
ser = serial.Serial(port='/dev/ttyUSB0', baudrate=9600, timeout=1)

#f = open(repDataTraj + "square_05.txt", 'w')

ind = 0
while ind < 1000:
    line = ser.readline()
    #print line
    if line.startswith('!AN'):
        line = line.replace("!AN:", "")
        print ind, line
        #f.write(line)                      # Write to the output log file
        ind += 1
#f.close
ser.close
