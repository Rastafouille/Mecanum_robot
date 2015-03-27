#include <Wire.h>
#include <math.h>

//Front motors
int E1 = 3; //M1 Speed Control
int E2 = 11; //M2 Speed Control
int M1 = 12; //M1 Direction Control
int M2 = 13; //M2 Direction Control

//Rear motors
int E3 = 6; //M1 Speed Control
int E4 = 5; //M2 Speed Control
int M3 = 8; //M1 Direction Control
int M4 = 7; //M2 Direction Control

//parametre
int limit=25;
float V;
float teta=1000;
int leftspeed = 255; //255 is maximum speed
int rightspeed = 150;
// parametre nunchuk
int max_y=225;
int min_y=15;
int max_x=225;
int min_x=15;

// Pas de temps
int time=10;
byte joy_x_axis = 0; // joystick axe x (0-255)
byte joy_y_axis = 0; // joystick axe y (0-255)
int accel_x_axis = 0; // accéléromètre axe x
int accel_y_axis = 0; // accéléromètre axe y
int accel_z_axis = 0; // accéléromètre axe z
 
 // byte outbuf[5] contains bits for z and c buttons
 // it also contains the least significant bits for the accelerometer data
 // so we have to check each bit of byte outbuf[5]
byte z_button = 0; // bouton Z
byte c_button = 0; // bouton c
byte buffer[6]; // Buffer contenant les 6 précieux octets qui nous intéresse
byte cnt = 0; // index courant de buffer

void setup()
{
  int i;
  for(i=3;i<=13;i++)
  pinMode(i, OUTPUT);
 
  // INITIALISATION NUNCHUCK sur le port serie
  Serial.begin(9600);
  byte cnt;
  Wire.begin();        
  Wire.beginTransmission(0x52);        // device address
  Wire.write(0x40);                    // 1st initialisation register
  Wire.write(0x00);                    // 1st initialisation value
  Wire.endTransmission();
  nunchuck_zero();
  Serial.print ("end setup nunchuk\n");
}
 
void nunchuck_zero()
  {Wire.beginTransmission (0x52);    Wire.write (0x00); Wire.endTransmission ();}
 
void nunchuck()
{
  //Acquisition NUNCHUCK
  Wire.requestFrom (0x52,6);
  while (Wire.available ()) {buffer[cnt] = Wire.read();cnt++;}
  if (cnt >= 5)
    {
  // Print the input data we have recieved
  // accel data is 10 bits long so we read 8 bits, then we have to add
  // on the last 2 bits.  That is why I multiply them by 2 * 2
  joy_x_axis = buffer[0]; // joystick axe x (0-255)
  joy_y_axis = buffer[1]; // joystick axe y (0-255)
  accel_x_axis = buffer[2] * 4; // accéléromètre axe x
  accel_y_axis = buffer[3] * 4; // accéléromètre axe y
  accel_z_axis = buffer[4] * 4; // accéléromètre axe z
 // byte outbuf[5] contains bits for z and c buttons
 // it also contains the least significant bits for the accelerometer data
 // so we have to check each bit of byte outbuf[5]
  z_button = 0; // bouton Z
  c_button = 0; // bouton c
 
  if ((buffer[5] >> 0) & 1)
    z_button = 1;
  if ((buffer[5] >> 1) & 1)
    c_button = 1;
  if ((buffer[5] >> 2) & 1)
    accel_x_axis += 2;
  if ((buffer[5] >> 4) & 1)
    accel_y_axis += 2;
  if ((buffer[5] >> 5) & 1)
    accel_y_axis += 1;
  if ((buffer[5] >> 6) & 1)
    accel_z_axis += 2;
  if ((buffer[5] >> 7) & 1)
    accel_z_axis += 1;
 // affichage sur le moniteur série pour débugage
//  Serial.print (joy_x_axis, DEC);Serial.print ("\t");
//  Serial.print (joy_y_axis, DEC);Serial.print ("\t");
//  Serial.print (accel_x_axis, DEC);Serial.print ("\t");
//  Serial.print (accel_y_axis, DEC);Serial.print ("\t");
//  Serial.print (accel_z_axis, DEC);Serial.print ("\t");
//  Serial.print (z_button, DEC);Serial.print ("\t");
//  Serial.print (c_button, DEC);Serial.print ("\t"); 
//  Serial.println();
    }
   cnt = 0;
  nunchuck_zero();
}

void stop(void) //Stop
{
  digitalWrite(E1,LOW);
  digitalWrite(E2,LOW);
  digitalWrite(E3,LOW);
  digitalWrite(E4,LOW);
}

void forward(char a,char b)
{
  analogWrite (E1,a);
  digitalWrite(M1,LOW);
  analogWrite (E2,b);
  digitalWrite(M2,LOW);
  analogWrite (E3,a);
  digitalWrite(M3,LOW);
  analogWrite (E4,b);
  digitalWrite(M4,LOW);
}

void reverse (char a,char b)
{
  analogWrite (E1,a);
  digitalWrite(M1,HIGH);
  analogWrite (E2,b);
  digitalWrite(M2,HIGH);
  analogWrite (E3,a);
  digitalWrite(M3,HIGH);
  analogWrite (E4,b);
  digitalWrite(M4,HIGH);
}

void diag1 (char a,char b)
{
  analogWrite (E2,b);
  digitalWrite(M2,LOW);
  analogWrite (E4,b);
  digitalWrite(M4,LOW);
  digitalWrite(E1,LOW);
  digitalWrite(E3,LOW);
}

void diag2 (char a,char b)
{
  analogWrite (E2,b);
  digitalWrite(M2,HIGH);
  analogWrite (E4,b);
  digitalWrite(M4,HIGH);
  digitalWrite(E1,LOW);
  digitalWrite(E3,LOW);
}

void left (char a,char b)
{
  analogWrite (E1,a);
  digitalWrite(M1,HIGH);
  analogWrite (E2,b);
  digitalWrite(M2,LOW);
  analogWrite (E3,a);
  digitalWrite(M3,HIGH);
  analogWrite (E4,b);
  digitalWrite(M4,LOW);
}

void right (char a,char b)
{
  analogWrite (E1,a);
  digitalWrite(M1,LOW);
  analogWrite (E2,b);
  digitalWrite(M2,HIGH);
  analogWrite (E3,a);
  digitalWrite(M3,LOW);
  analogWrite (E4,b);
  digitalWrite(M4,HIGH);
}
 
void rot_horaire (char a,char b)
{
  analogWrite (E1,a);
  digitalWrite(M1,LOW);
  analogWrite (E2,b);
  digitalWrite(M2,HIGH);
  analogWrite (E3,a);
  digitalWrite(M3,HIGH);
  analogWrite (E4,b);
  digitalWrite(M4,LOW);
}
void rot_antihoraire (char a,char b)
{
  analogWrite (E1,a);
  digitalWrite(M1,HIGH);
  analogWrite (E2,b);
  digitalWrite(M2,LOW);
  analogWrite (E3,a);
  digitalWrite(M3,LOW);
  analogWrite (E4,b);
  digitalWrite(M4,HIGH);
}
void dirteta (int teta,int a,int b)
{
    if (teta>=0 && teta<45) 
     {
      V=-(float)a*(-1.0+1.0/45.0*(float)teta);
      analogWrite (E1,a);digitalWrite(M1,LOW);
      analogWrite (E2,V);digitalWrite(M2,LOW);
      analogWrite (E3,a);digitalWrite(M3,LOW);
      analogWrite (E4,V);digitalWrite(M4,LOW);
    }
    if (teta>=45 && teta<90) 
     {
      V=(float)a*(-1.0+1.0/45.0*(float)teta);
      analogWrite (E1,a);digitalWrite(M1,LOW);
      analogWrite (E2,V);digitalWrite(M2,HIGH);
      analogWrite (E3,a);digitalWrite(M3,LOW);
      analogWrite (E4,V);digitalWrite(M4,HIGH);
    }
     if (teta>=90 && teta<135) 
     {
      V=-(float)a*(-1.0+1.0/45.0*((float)teta-90.0));
      analogWrite (E1,V);digitalWrite(M1,LOW);
      analogWrite (E2,a);digitalWrite(M2,HIGH);
      analogWrite (E3,V);digitalWrite(M3,LOW);
      analogWrite (E4,a);digitalWrite(M4,HIGH);
     }
     if (teta>=135 && teta<180) 
     {
      V=(float)a*(-1.0+1.0/45.0*((float)teta-90.0));
      analogWrite (E1,V);digitalWrite(M1,HIGH);
      analogWrite (E2,a);digitalWrite(M2,HIGH);
      analogWrite (E3,V);digitalWrite(M3,HIGH);
      analogWrite (E4,a);digitalWrite(M4,HIGH);
    }
    if (teta>=180 && teta<225) 
     {
      V=(float)a*(1.0-1.0/45.0*((float)teta-180.0));
      analogWrite (E1,a);digitalWrite(M1,HIGH);
      analogWrite (E2,V);digitalWrite(M2,HIGH);
      analogWrite (E3,a);digitalWrite(M3,HIGH);
      analogWrite (E4,V);digitalWrite(M4,HIGH);
     }
     if (teta>=225 && teta<270) 
     {
      V=-(float)a*(1.0-1.0/45.0*((float)teta-180.0));
      analogWrite (E1,a);digitalWrite(M1,HIGH);
      analogWrite (E2,V);digitalWrite(M2,LOW);
      analogWrite (E3,a);digitalWrite(M3,HIGH);
      analogWrite (E4,V);digitalWrite(M4,LOW);
     }
       if (teta>=270 && teta<315) 
     {
      V=(float)a*(1.0-1.0/45.0*((float)teta-270.0));
      analogWrite (E1,V);digitalWrite(M1,HIGH);
      analogWrite (E2,a);digitalWrite(M2,LOW);
      analogWrite (E3,V);digitalWrite(M3,HIGH);
      analogWrite (E4,a);digitalWrite(M4,LOW);
     }
      if (teta>=315 && teta<360) 
     {
      V=-(float)a*(1.0-1.0/45.0*((float)teta-270.0));
      analogWrite (E1,V);digitalWrite(M1,LOW);
      analogWrite (E2,a);digitalWrite(M2,LOW);
      analogWrite (E3,V);digitalWrite(M3,LOW);
      analogWrite (E4,a);digitalWrite(M4,LOW);
     }
  //Serial.print(teta); Serial.print ("\t");Serial.print(a); Serial.print ("\t");Serial.println(V,4);
  
}

///////////////////////////////////////////////////////////////////////////
void loop()
{
  nunchuck();
  //delay(100);

if (joy_y_axis<(125+limit) && joy_y_axis>(125-limit) && joy_x_axis<(125-limit)) {teta=270;}
else if (joy_y_axis<(125+limit) && joy_y_axis>(125-limit) && joy_x_axis>(125+limit)) {teta=90;}
else if (joy_x_axis<(125+limit) && joy_x_axis>(125-limit) && joy_y_axis>(125+limit)) {teta=0;}
else if (joy_x_axis<(125+limit) && joy_x_axis>(125-limit) && joy_y_axis<(125-limit)) {teta=180;}


else if (joy_x_axis>(125+limit) && joy_y_axis>(125+limit)) {teta=45;}
else if (joy_x_axis>(125+limit) && joy_y_axis<(125-limit)) {teta=135;}
else if (joy_x_axis<(125-limit) && joy_y_axis<(125-limit)) {teta=225;}
else if (joy_x_axis<(125-limit) && joy_y_axis>(125+limit)) {teta=315;}

// pilotage au degres pres mais pas robuste avec un nunchuck...
//else if (joy_y_axis>(125+limit) && joy_x_axis>(125+limit)){teta=360.0/(2.0*3.14)*atan(((float)joy_x_axis-125.0)/((float)joy_y_axis-125.0));}
//else if (joy_y_axis>(125+limit) && joy_x_axis<(125-limit)){teta=360.0+360.0/(2.0*3.14)*atan(((float)joy_x_axis-125.0)/((float)joy_y_axis-125.0));}
//else if (joy_y_axis<(125-limit) && joy_x_axis>(125+limit)){teta=180.0+360.0/(2.0*3.14)*atan(((float)joy_x_axis-125.0)/((float)joy_y_axis-125.0));}
//else if (joy_y_axis<(125-limit) && joy_x_axis<(125-limit)){teta=180.0+360.0/(2.0*3.14)*atan(((float)joy_x_axis-125.0)/((float)joy_y_axis-125.0));}
else {teta=1000;}

  Serial.println (teta);
  
//pilotage moteur avec le joystick
if (teta!=1000)
  {//Serial.println (teta); 
dirteta ((int)teta,leftspeed,rightspeed);}
  else
  {stop();}
//pilotage avec boutons
if (z_button==0 && c_button==0 )
  {rot_horaire (leftspeed,rightspeed);}
else if (z_button==1 && c_button==0 )
  {rot_antihoraire (leftspeed,rightspeed);}
//else
 // {stop();}
}

