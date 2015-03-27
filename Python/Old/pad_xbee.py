import pygame
import serial
from math import sqrt
import matplotlib.pyplot as plt
import numpy as np 
i=0
centrale = list()
plt.ion()

pygame.init()
ser = serial.Serial(port='/dev/ttyUSB1', baudrate=9600, timeout=1) #connection Xbee
#ser = serial.Serial(port='/dev/ttyACM0', baudrate=9600, timeout=1) #connection filaire

# Count the joysticks the computer has
joystick_count=pygame.joystick.get_count()
if joystick_count == 0:
    # No joysticks!
    print ("Error, I didn't find any joysticks.")
else:
    # Use joystick #0 and initialize it
    my_joystick = pygame.joystick.Joystick(0)
    my_joystick.init()
    print ("numaxes=",my_joystick.get_numaxes())
    print ("numballs=",my_joystick.get_numballs())
    print ("numbuttons=",my_joystick.get_numbuttons())
    print ("numhats=",my_joystick.get_numhats())
    
             
clock = pygame.time.Clock()
 
done=False
while done==False:
 
    for event in pygame.event.get():
        if event.type == pygame.QUIT:
            done=True
             
    # As long as there is a joystick
    if joystick_count != 0:
        
        horiz_axis_pos= my_joystick.get_axis(2)     
        vert_axis_pos= my_joystick.get_axis(3)      
        bouton_croix=my_joystick.get_button(0)    
        bouton_rond=my_joystick.get_button(1)    
        bouton_carre=my_joystick.get_button(2)    
        bouton_triangle=my_joystick.get_button(3)    
        bouton_R1=my_joystick.get_button(5)  
        #bouton_select=my_joystick.get_button(6)  
        #bouton_start=my_joystick.get_button(7)  
        #bouton_central=my_joystick.get_button(8)
        #bouton_pad_gauche=my_joystick.get_button(9)
       # bouton_pad_droite=my_joystick.get_button(10)
        if bouton_triangle == 1:
            ser.write("z")
        elif bouton_carre==1:
            ser.write("q")
        elif bouton_croix==1:
            ser.write("s")
        elif bouton_rond==1:
            ser.write("d")
        elif bouton_R1==1:
            ser.write("a")
    line = ser.readline()
    if line.startswith('!AN'):
        line = line.replace("!AN:", "")
        line = line.replace("\r\n", "")
        centrale.append(line.split(','))
        print centrale[i]
        for k in range(i):
            plt.plot(k,float(centrale[i][1]),'-g',linewidth=1.5,markersize=10)
        plt.show(block=True)
    
        i=i+1
        

    vitesse =sqrt(pow(horiz_axis_pos,2)+pow(vert_axis_pos,2))/sqrt(2)
    print ("horiz_axis_pos=",pow(horiz_axis_pos,2))   
    print ("vert_axis_pos=",pow(vert_axis_pos,2))   
    print ("vitesse=",vitesse)

    #clock.tick(40)
ser.close
pygame.quit ()
