
import serial
from math import sqrt
import matplotlib.pyplot as plt
import numpy as np 
i=0
j=0
centrale = list()
commander = list()
vitesse =[]
angle=[]

#ser = serial.Serial(port='/dev/ttyUSB0', baudrate=9600, timeout=1) #connection Xbee
ser = serial.Serial(port='/dev/ttyUSB0', baudrate=38400, timeout=0.1) #connection filaire
    
done=False
while done==False:
    line = ser.readline()
    #reception trame commander
    if line.startswith('!Commander:'):
        line = line.replace("!Commander:", "")
        line = line.replace("\r\n", "")
        commander.append(line.split(','))
        print commander[i]
        #construction et envoie trame consigne
        vitesse.append(int((( float(commander[i][1]) -128) /102+1)*100))
        angle.append(int((((float(commander[i][2])-128)/102)*90+90)*100))
        consigne="~X;"+str(vitesse[i])+";"+str(angle[i])+";#"
        ser.write(consigne)
        print consigne
        i=i+1
    # reception trame accelero/magneto/gyro
    if line.startswith('!AN'):
        line = line.replace("!AN:", "")
        line = line.replace("\r\n", "")
        centrale.append(line.split(','))
        print centrale[j]
        j=j+1

ser.close

