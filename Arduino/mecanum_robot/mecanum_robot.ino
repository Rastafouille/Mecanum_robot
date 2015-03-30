#include <Wire.h>
#include <LSM303.h>
long timer=0;

// Encoders
int sensorcount10 = 0;int sensorcount11 = 0;long count1 = 0;
int sensorcount20 = 0;int sensorcount21 = 0;long count2 = 0;
int sensorcount30 = 0;int sensorcount31 = 0;long count3 = 0;
int sensorcount40 = 0;int sensorcount41 = 0;long count4 = 0;

//Front motors
int M1S = 3; //M1 Speed Control
int M2S = 11; //M2 Speed Control
int M1D = 12; //M1 Direction Control
int M2D = 13; //M2 Direction Control

//Rear motors
int M3S = 6; //M3 Speed Control
int M4S = 5; //M4 Speed Control
int M3D = 8; //M3 Direction Control
int M4D = 7; //M4 Direction Control

// Compass I2c A4(SDA), A5(SCL)
LSM303 compass; 

// Buffer qui va contenir la trame série
#define TAILLE_MAX 32
 
// Buffer qui va contenir le texte (taille du buffer / 2, oui j'ai mis ça au pif)
char texte[TAILLE_MAX];
// Données utiles extraites
long int cons_vitesse,cons_angle,angle;
float vitesse;


void setup(void)
	{
	  int i;
	  for(i=3;i<=13;i++) {pinMode(i, OUTPUT);}
	  Serial.begin(115200);
	  Serial.println("Serial");
	  Wire.begin();
	  compass.init();
	  compass.enableDefault();
	}

void loop(void)
	{
	  // Récupération d'une trame + parsing
//	  if(recupInfo(texte,&cons_vitesse,&cons_angle)==1) {Serial.println("Erreur de trame 1!");}
//	  if(recupInfo(texte,&cons_vitesse,&cons_angle)==2) {Serial.println("Erreur de trame 2!");}
  
  RunForrestRun(200,200,-200,-200);
  EnvoieTrame(compass,count4/16);
  
//  if (analogRead(A0) < 600){sensorcount11 = 1;}
//  else {sensorcount11 = 0;}
//  if (sensorcount11 != sensorcount10){count1 ++;}
//  sensorcount10 = sensorcount11;
//  Serial.println(count1/16);
//  
//    if (analogRead(A1) < 600){sensorcount21 = 1;}
//  else {sensorcount21 = 0;}
//  if (sensorcount21 != sensorcount20){count2 ++;}
//  sensorcount20 = sensorcount21;
//  Serial.println(count2/16);
//  
//    if (analogRead(A2) < 600){sensorcount31 = 1;}
//  else {sensorcount31 = 0;}
//  if (sensorcount31 != sensorcount30){count3 ++;}
//  sensorcount30 = sensorcount31;
//  Serial.println(count3/16);
//  
    if (analogRead(A3) < 600){sensorcount41 = 1;}
  else {sensorcount41 = 0;}
  if (sensorcount41 != sensorcount40){count4 ++;}
  sensorcount40 = sensorcount41;
  //Serial.println(count4/16);

  delay(10);
  
	}

void stop(void) //Stop
	{
		digitalWrite(M1S,LOW);digitalWrite(M2S,LOW);digitalWrite(M3S,LOW);digitalWrite(M4S,LOW);
	}

//pilotage par roues, 255 max
void RunForrestRun(char V1,char V2,char V3,char V4)
	{
	  if (V1<0) {analogWrite (M1S,-V1);digitalWrite(M1D,LOW);}
	  else if (V1>=0) {analogWrite (M1S,V1);digitalWrite(M1D,HIGH);}
  
	  if (V2<0) {analogWrite (M2S,-V2);digitalWrite(M2D,LOW);}
	  else if (V2>=0) {analogWrite (M2S,V1);digitalWrite(M2D,HIGH);}
  
	  if (V3<0) {analogWrite (M3S,-V3);digitalWrite(M3D,LOW);}
	  else if (V3>=0) {analogWrite (M3S,V3);digitalWrite(M3D,HIGH);}
  
	  if (V4<0) {analogWrite (M4S,-V4);digitalWrite(M4D,LOW);}
	  else if (V4>=0) {analogWrite (M4S,V4);digitalWrite(M4D,HIGH);}
	}

int recupInfo(char *texte, long int *cons_vitesse,long int *cons_angle) 
	{
	  char c, buf[TAILLE_MAX + 1];
	  unsigned char i = 0;
	    if(Serial.available() > 1)
              {/* Attente de 2 char sur le port série */
	        while(Serial.read() != '~' && Serial.read() != 'X'); /* Tant que chaine != ~X -> boucle */
	        /* Remplissage du buffer */
	        do{
	            if(i == (TAILLE_MAX + 1)) /* Si la chaine a dépassé la taille max du buffer*/
	              return 1;/* retourne 1 -> erreur */
	        while(Serial.available() < 1); /* Attente d'un char sur le port série */ 
	            } 
	        while((buf[i++] = Serial.read()) != '#'); /* Tant que char != # (fléche) -> boucle */
 
	        /* Copie le texte au début de buf[] dans texte[] */
	        i = 0;
	  while((texte[i] = buf[i]) != '#') i++;
	  texte[i] = '\0';
	  /* Parse la chaine de caractères et extrait les champs */
	  if(sscanf(texte, "X;%d;%d;",cons_vitesse,cons_angle) != 2)
	    {return 2;} /* Si sscanf n'as pas pu extraire les 2 champs -> erreur*/
  
	  return 0;/* retourne 0 -> pas d'erreur */
	}
}

void EnvoieTrame(LSM303 compass,long count4)
  {
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
    Serial.print (",");  
    Serial.print (count4);  
//    Serial.print(",");
//    Serial.print (vleft);
//    Serial.print (","); 
//    Serial.print (vright); 
    Serial.println(); 
  }

