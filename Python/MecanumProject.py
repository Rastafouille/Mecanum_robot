# -*- coding: utf-8 -*-
"""
Created on Sat Mar 28 21:21:57 2015

@author: rastafouille
"""
import serial
from math import sqrt
import matplotlib.pyplot as plt
import numpy as np 
import cwiid
import time



def main():
    i=0
    j=0
    Robot = list()
    commander = list()
    vitesse =[]
    angle=[]
    led = 0
    rpt_mode = 0
    rumble = 0
    mesg = False
    global wiimote

    try:
        print 'Press 1 + 2 on your Wii Remote now to connect it...'
        wiimote = cwiid.Wiimote()
        ComWiimote=1
        print 'Wiimote connected !!!'
        wiimote.rumble = 1
        print 'niveau batterie sur 208 : ',wiimote.state['battery']
        print 'Press PLUS and MINUS together to disconnect and quit.\n'
        time.sleep(0.5)
        wiimote.rumble = 0
    except RuntimeError:
        print 'Wiimote connexion failed ...'
        ComWiimote =0
    
    
    try:
        #ser = serial.Serial(port='/dev/ttyUSB0', baudrate=9600, timeout=1) #connection Xbee
        ser = serial.Serial(port='/dev/ttyUSB0', baudrate=38400, timeout=0.1) #connection filaire
        ComSerie =1
        print 'Serial communication done !!'
    except :
        print 'Serial connexion failed ...'
        ComSerie =0  

    Exit=False
    while Exit==False:
        time.sleep(0.1)
        if ComSerie==1:    
            line = ser.readline()
            
            # reception trame Robot
            if line.startswith('!AN'):
                line = line.replace("!AN:", "")
                line = line.replace("\r\n", "")
                Robot.append(line.split(','))
                print 'trame robot recue : ',Robot[j]
                j=j+1
                
        if ComWiimote==1:
            # lecture wiimote            
            wiimote.rpt_mode = cwiid.RPT_BTN | cwiid.RPT_ACC | cwiid.RPT_EXT
            WiiState=wiimote.state
            print 'Wii State =',WiiState
            print 'Nunchuck',wiimote.state['nunchuk']['buttons'],wiimote.state['nunchuk']['stick'][0],wiimote.state['nunchuk']['stick'][1]  
            
            
#           vitesse.append(int((( float(commander[i][1]) -128) /102+1)*100))
#           angle.append(int((((float(commander[i][2])-128)/102)*90+90)*100))
            #construction et envoie trame consigne            
            if ComSerie==1:                
                consigne="~X;"+str(wiimote.state['nunchuk']['buttons'])+";"+str(wiimote.state['nunchuk']['stick'][0])+";"+str(wiimote.state['nunchuk']['stick'][1])+";#"
                ser.write(consigne)
                print 'trame consigne envoyée : ',consigne
                i=i+1
            # Detection + et - pour exit     
            if (wiimote.state['buttons'] - cwiid.BTN_PLUS - cwiid.BTN_MINUS == 0):
                wiimote.rumble = 1
                time.sleep(0.5)
                wiimote.rumble = 0
                Exit=True
                
    print '\nClosing connection ...'
    if ComSerie==1: 
        ComSerie=0
        ser.close
    if ComWiimote==1:
        wiimote.close()
        ComWiimote=0
main()