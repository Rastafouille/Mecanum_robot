#include <PinChangeInt.h>
#include <PinChangeIntConfig.h>

#include <fuzzy_table.h>
#include <PID_Beta6.h>

#include <MotorWheel.h>


#ifndef MICROS_PER_SEC
#define MICROS_PER_SEC 1000000
#endif

 
irqISR(irq1,isr1);
MotorWheel wheel1(9,8,6,7,&irq1);	// Motor PWM:Pin9, DIR:Pin8, 
									// Encoder A:Pin6, B:Pin7

void setup() {    
	TCCR1B=TCCR1B&0xf8|0x01;	// Pin9,Pin10 PWM 31250Hz, Silent PWM

	wheel1.setSpeedMMPS(100,DIR_ADVANCE);
	wheel1.PIDEnable(KC,TAUI,TAUD,10);

	Serial.begin(19200);
}

void loop() {
	wheel1.PIDRegulate();
	if(millis()%500==0) {
		Serial.print("speedRPM> ");
		Serial.println(wheel1.getSpeedRPM(),DEC);
		Serial.print("MMPS  --> ");
		Serial.println(wheel1.getSpeedMMPS(),DEC);

        //wheel1.debugger();
	}
}

