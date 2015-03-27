/*
The sensor outputs provided by the library are the raw 16-bit values
obtained by concatenating the 8-bit high and low accelerometer and
magnetometer data registers. They can be converted to units of g and
gauss using the conversion factors specified in the datasheet for your
particular device and full scale setting (gain).

Example: An LSM303D gives a magnetometer X axis reading of 1982 with
its default full scale setting of +/- 4 gauss. The M_GN specification
in the LSM303D datasheet (page 10) states a conversion factor of 0.160
mgauss/LSB (least significant bit) at this FS setting, so the raw
reading of -1982 corresponds to 1982 * 0.160 = 317.1 mgauss =
0.3171 gauss.

In the LSM303DLHC, LSM303DLM, and LSM303DLH, the acceleration data
registers actually contain a left-aligned 12-bit number, so the lowest
4 bits are always 0, and the values should be shifted right by 4 bits
(divided by 16) to be consistent with the conversion factors specified
in the datasheets.

Example: An LSM303DLH gives an accelerometer Z axis reading of -16144
with its default full scale setting of +/- 2 g. Dropping the lowest 4
bits gives a 12-bit raw value of -1009. The LA_So specification in the
LSM303DLH datasheet (page 11) states a conversion factor of 1 mg/digit
at this FS setting, so the value of -1009 corresponds to -1009 * 1 =
1009 mg = 1.009 g.
*/

#include <Wire.h>
#include <LSM303.h>
#include <ZumoMotors.h>

long timer=0;
int gonzalez=50;
int rampe=0;
int vleft = 0;
int vright = 0;

LSM303 compass;
ZumoMotors motors;

void setup() {
  Serial.begin(115200);
  Serial.println("Serial");
  Wire.begin();
  compass.init();
  compass.enableDefault();
}


void loop()
{
  
  
       if((millis()-timer)>=20)  // Main loop runs at 50Hz
  //  if((millis()-timer)>=40)  // Main loop runs at 25Hz
  {
         if (millis() > 2000 & millis() <= 3000)
           {vleft = 200;
            vright = 200;
            motors.setLeftSpeed(vleft);
            motors.setRightSpeed(vright);}
         else if (millis() > 3000 & millis() <= 3200)
           {vleft = -200;
            vright = 200;
            motors.setLeftSpeed(vleft);
            motors.setRightSpeed(vright);}
         else if (millis() > 3200 & millis() <= 4200)
           {vleft = 200;
            vright = 200;
            motors.setLeftSpeed(vleft);
            motors.setRightSpeed(vright);}
         else if (millis() > 4200 & millis() <= 4400)
           {vleft = -200;
            vright = 200;
            motors.setLeftSpeed(vleft);
            motors.setRightSpeed(vright);}
         else if (millis() > 4400 & millis() <= 5400)
           {vleft = 200;
            vright = 200;
            motors.setLeftSpeed(vleft);
            motors.setRightSpeed(vright);}
         //else if (millis() > 5400 & millis() <= 5600)
         //  {motors.setLeftSpeed(-200);
         //   motors.setRightSpeed(200);}
         //else if (millis() > 5600 & millis() <= 6600)
         //  {motors.setLeftSpeed(200);
         //   motors.setRightSpeed(200);}
         //else if (millis() > 6600 & millis() <= 6800)
         //  {motors.setLeftSpeed(-200);
         //   motors.setRightSpeed(200);}
         //else if (millis() > 6800 & millis() <= 7800)
         //  {motors.setLeftSpeed(200);
         //   motors.setRightSpeed(200);}
         else
          {vleft = 0;
           vright = 0;
           motors.setLeftSpeed(vleft);
           motors.setRightSpeed(vright);} 
 }
  compass.read();
  timer = millis();

 

  
  Serial.print("!");
  Serial.print("AN:");
  Serial.print(timer); 
  Serial.print (",");   
  Serial.print (compass.a.x);
  Serial.print (",");
  Serial.print (compass.a.y); 
  Serial.print (","); 
  Serial.print (compass.a.z);
  Serial.print (","); 
  Serial.print (compass.m.x);
  Serial.print (",");
  Serial.print (compass.m.y);
  Serial.print (",");  
  Serial.print (compass.m.z);  
  Serial.print(",");
  Serial.print (vleft);
  Serial.print (","); 
  Serial.print (vright); 
  Serial.println(); 
  
  delay(100);
}

