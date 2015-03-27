const int button = 12; 
const int led = 13; 
int buttonState;

void setup() {
  Serial.begin(9600);      
  pinMode (button, INPUT);
  pinMode (led, OUTPUT);
  //setDestination();
  blink(led, 3);
}

void loop() {
buttonState = digitalRead(button);
Serial.print(buttonState);
Serial.print("    ");
  if (buttonState == 1) {digitalWrite(led, HIGH);Serial.println(1);}
  else{digitalWrite(led, LOW);Serial.println(0);}
  delay(50);
}


// Blink 
void blink(int thisPin, int howManyTimes) {
  for (int blinks=0; blinks< howManyTimes; blinks++) {
    digitalWrite(thisPin, HIGH);
    delay(200);
    digitalWrite(thisPin, LOW);
    delay(200);  
  }
}


