#include <Omni4WD.h>




Omni4WD::Omni4WD(MotorWheel* wheelUL,MotorWheel* wheelLL,
			MotorWheel* wheelLR,MotorWheel* wheelUR):
			_wheelUL(wheelUL),_wheelLL(wheelLL),
			_wheelLR(wheelLR),_wheelUR(wheelUR) {
	setSwitchMotorsStat(MOTORS_FB);
}
unsigned char Omni4WD::getSwitchMotorsStat() const {
	return _switchMotorsStat;
}
unsigned char Omni4WD::setSwitchMotorsStat(unsigned char switchMotorsStat) {
	if(MOTORS_FB<=switchMotorsStat && switchMotorsStat<=MOTORS_BF)
		_switchMotorsStat=switchMotorsStat;
	return getSwitchMotorsStat();
}
unsigned char Omni4WD::switchMotors() {
	if(getSwitchMotorsStat()==MOTORS_FB) {
		setSwitchMotorsStat(MOTORS_BF);
	} else {
		setSwitchMotorsStat(MOTORS_FB);
	}
	MotorWheel* temp=_wheelUL;
	_wheelUL=_wheelLR;
	_wheelLR=temp;
	temp=_wheelLL;
	_wheelLL=_wheelUR;
	_wheelUR=temp;

	return getSwitchMotorsStat();
}
unsigned char Omni4WD::switchMotorsReset() {
	if(getSwitchMotorsStat()==MOTORS_BF) switchMotors();
	return getSwitchMotorsStat();
}

unsigned char Omni4WD::getCarStat() const {
    return _carStat;
}
unsigned char Omni4WD::setCarStat(unsigned char carStat) {
    if(STAT_UNKNOWN<=carStat && carStat<=STAT_UPPERRIGHT)
        return _carStat=carStat;
    else
        return STAT_UNKNOWN;
}

unsigned int Omni4WD::setMotorAll(unsigned int speedMMPS,bool dir) {
	wheelULSetSpeedMMPS(speedMMPS,dir);
	wheelLLSetSpeedMMPS(speedMMPS,dir);
	wheelLRSetSpeedMMPS(speedMMPS,dir);
	wheelURSetSpeedMMPS(speedMMPS,dir);
	return wheelULGetSpeedMMPS();
}
unsigned int Omni4WD::setMotorAllStop() {
	return setMotorAll(0,DIR_ADVANCE);
}
unsigned int Omni4WD::setMotorAllAdvance(unsigned int speedMMPS) {
	return setMotorAll(speedMMPS,DIR_ADVANCE);
}
unsigned int Omni4WD::setMotorAllBackoff(unsigned int speedMMPS) {
	return setMotorAll(speedMMPS,DIR_BACKOFF);
}
unsigned int Omni4WD::setCarStop() {
	setCarStat(STAT_STOP);
	return setMotorAllStop();
}
unsigned int Omni4WD::setCarAdvance(unsigned int speedMMPS) {
	setCarStat(STAT_ADVANCE);
	wheelULSetSpeedMMPS(speedMMPS,DIR_ADVANCE);
	wheelLLSetSpeedMMPS(speedMMPS,DIR_ADVANCE);
	wheelLRSetSpeedMMPS(speedMMPS,DIR_BACKOFF);
	wheelURSetSpeedMMPS(speedMMPS,DIR_BACKOFF);
	return wheelULGetSpeedMMPS();
}
unsigned int Omni4WD::setCarBackoff(unsigned int speedMMPS) {
	setCarStat(STAT_BACKOFF);
	wheelULSetSpeedMMPS(speedMMPS,DIR_BACKOFF);
	wheelLLSetSpeedMMPS(speedMMPS,DIR_BACKOFF);
	wheelLRSetSpeedMMPS(speedMMPS,DIR_ADVANCE);
	wheelURSetSpeedMMPS(speedMMPS,DIR_ADVANCE);
	return wheelULGetSpeedMMPS();
}
unsigned int Omni4WD::setCarLeft(unsigned int speedMMPS) {
	setCarStat(STAT_LEFT);
	wheelULSetSpeedMMPS(speedMMPS,DIR_BACKOFF);
	wheelLLSetSpeedMMPS(speedMMPS,DIR_ADVANCE);
	wheelLRSetSpeedMMPS(speedMMPS,DIR_ADVANCE);
	wheelURSetSpeedMMPS(speedMMPS,DIR_BACKOFF);
	return wheelULGetSpeedMMPS();
}
unsigned int Omni4WD::setCarRight(unsigned int speedMMPS) {
	setCarStat(STAT_RIGHT);
	wheelULSetSpeedMMPS(speedMMPS,DIR_ADVANCE);
	wheelLLSetSpeedMMPS(speedMMPS,DIR_BACKOFF);
	wheelLRSetSpeedMMPS(speedMMPS,DIR_BACKOFF);
	wheelURSetSpeedMMPS(speedMMPS,DIR_ADVANCE);
	return wheelULGetSpeedMMPS();
}
unsigned int Omni4WD::setCarRotateLeft(unsigned int speedMMPS) {
	setCarStat(STAT_ROTATELEFT);
	return setMotorAllBackoff(speedMMPS);
}
unsigned int Omni4WD::setCarRotateRight(unsigned int speedMMPS) {
	setCarStat(STAT_ROTATERIGHT);
	return setMotorAllAdvance(speedMMPS);
}
unsigned int Omni4WD::setCarUpperLeft(unsigned int speedMMPS) {
	setCarStat(STAT_UPPERLEFT);
	wheelULSetSpeedMMPS(0,DIR_ADVANCE);
	wheelLLSetSpeedMMPS(speedMMPS,DIR_ADVANCE);
	wheelLRSetSpeedMMPS(0,DIR_ADVANCE);
	wheelURSetSpeedMMPS(speedMMPS,DIR_BACKOFF);
	return wheelLLGetSpeedMMPS();
}
unsigned int Omni4WD::setCarLowerLeft(unsigned int speedMMPS) {
	setCarStat(STAT_LOWERLEFT);
	wheelULSetSpeedMMPS(speedMMPS,DIR_BACKOFF);
	wheelLLSetSpeedMMPS(0,DIR_ADVANCE);
	wheelLRSetSpeedMMPS(speedMMPS,DIR_ADVANCE);
	wheelURSetSpeedMMPS(0,DIR_ADVANCE);
	return wheelULGetSpeedMMPS();
}
unsigned int Omni4WD::setCarLowerRight(unsigned int speedMMPS) {
	setCarStat(STAT_LOWERRIGHT);
	wheelULSetSpeedMMPS(0,DIR_ADVANCE);
	wheelLLSetSpeedMMPS(speedMMPS,DIR_BACKOFF);
	wheelLRSetSpeedMMPS(0,DIR_ADVANCE);
	wheelURSetSpeedMMPS(speedMMPS,DIR_ADVANCE);
	return wheelLLGetSpeedMMPS();
}
unsigned int Omni4WD::setCarUpperRight(unsigned int speedMMPS) {
	setCarStat(STAT_UPPERRIGHT);
	wheelULSetSpeedMMPS(speedMMPS,DIR_ADVANCE);
	wheelLLSetSpeedMMPS(0,DIR_ADVANCE);
	wheelLRSetSpeedMMPS(speedMMPS,DIR_BACKOFF);
	wheelURSetSpeedMMPS(0,DIR_ADVANCE);
	return wheelULGetSpeedMMPS();
}

unsigned int Omni4WD::getCarSpeedMMPS() const {
	unsigned int speedMMPS=wheelULGetSpeedMMPS();
	if(wheelLLGetSpeedMMPS()>speedMMPS) speedMMPS=wheelLLGetSpeedMMPS();
	if(wheelLRGetSpeedMMPS()>speedMMPS) speedMMPS=wheelLRGetSpeedMMPS();
	if(wheelURGetSpeedMMPS()>speedMMPS) speedMMPS=wheelURGetSpeedMMPS();
	return speedMMPS;
}
unsigned int Omni4WD::setCarSpeedMMPS(unsigned int speedMMPS,unsigned int ms) {
	unsigned int carStat=getCarStat();
	unsigned int currSpeed=getCarSpeedMMPS();

	unsigned int (Omni4WD::*carAction)(unsigned int speedMMPS);
	switch(carStat) {
		case STAT_UNKNOWN:	// no break here
		case STAT_STOP:
			return currSpeed;
		case STAT_ADVANCE:
			carAction=&Omni4WD::setCarAdvance; break;
		case STAT_BACKOFF:
			carAction=&Omni4WD::setCarBackoff; break;
		case STAT_LEFT:
			carAction=&Omni4WD::setCarLeft; break;
		case STAT_RIGHT:
			carAction=&Omni4WD::setCarRight; break;
		case STAT_ROTATELEFT:
			carAction=&Omni4WD::setCarRotateLeft; break;
		case STAT_ROTATERIGHT:
			carAction=&Omni4WD::setCarRotateRight; break;
		case STAT_UPPERLEFT:
			carAction=&Omni4WD::setCarUpperLeft; break;
		case STAT_LOWERLEFT:
			carAction=&Omni4WD::setCarLowerLeft; break;
		case STAT_LOWERRIGHT:
			carAction=&Omni4WD::setCarLowerRight; break;
		case STAT_UPPERRIGHT:
			carAction=&Omni4WD::setCarUpperRight; break;
	}

	if(ms<100 || abs(speedMMPS-currSpeed)<10) {
		(this->*carAction)(speedMMPS);
		return getCarSpeedMMPS();
	}

	for(int time=0,speed=currSpeed;time<=ms;time+=50) {
		speed=map(time,0,ms,currSpeed,speedMMPS);
		(this->*carAction)(speed);
		delayMS(50);
	}

	(this->*carAction)(speedMMPS);
	return getCarSpeedMMPS();
}
unsigned int Omni4WD::setCarSlow2Stop(unsigned int ms) {
	return setCarSpeedMMPS(0,ms);
}

unsigned int Omni4WD::wheelULSetSpeedMMPS(unsigned int speedMMPS,bool dir) {
	return _wheelUL->setSpeedMMPS(speedMMPS,dir);
}
unsigned int Omni4WD::wheelULGetSpeedMMPS() const {
	return _wheelUL->getSpeedMMPS();
}
unsigned int Omni4WD::wheelLLSetSpeedMMPS(unsigned int speedMMPS,bool dir) {
	return _wheelLL->setSpeedMMPS(speedMMPS,dir);
}
unsigned int Omni4WD::wheelLLGetSpeedMMPS() const {
	return _wheelLL->getSpeedMMPS();
}
unsigned int Omni4WD::wheelLRSetSpeedMMPS(unsigned int speedMMPS,bool dir) {
	return _wheelLR->setSpeedMMPS(speedMMPS,dir);
}
unsigned int Omni4WD::wheelLRGetSpeedMMPS() const {
	return _wheelLR->getSpeedMMPS();
}
unsigned int Omni4WD::wheelURSetSpeedMMPS(unsigned int speedMMPS,bool dir) {
	return _wheelUR->setSpeedMMPS(speedMMPS,dir);
}
unsigned int Omni4WD::wheelURGetSpeedMMPS() const {
	return _wheelUR->getSpeedMMPS();
}
bool Omni4WD::PIDEnable(float kc,float taui,float taud,unsigned int interval) {
	return _wheelUL->PIDEnable(kc,taui,taud,interval) &&
			_wheelLL->PIDEnable(kc,taui,taud,interval) &&
			_wheelLR->PIDEnable(kc,taui,taud,interval) &&
			_wheelUR->PIDEnable(kc,taui,taud,interval);
}
bool Omni4WD::PIDRegulate() {
	return _wheelUL->PIDRegulate() && _wheelLL->PIDRegulate() && _wheelLR->PIDRegulate() && _wheelUR->PIDRegulate();
}
void Omni4WD::delayMS(unsigned int ms,bool debug) {
	for(int i=0;i<ms;i+=10) {
		PIDRegulate();
		if(debug && (i%500==0)) debugger();
		delay(10);
	}
}
		// new one
void Omni4WD::demoActions(unsigned int speedMMPS,unsigned int duration,
		unsigned int uptime,bool debug) {
	unsigned int (Omni4WD::*carAction[])(unsigned int speedMMPS)={
		&Omni4WD::setCarAdvance,
		&Omni4WD::setCarBackoff,
		&Omni4WD::setCarLeft,
		&Omni4WD::setCarRight,
		&Omni4WD::setCarUpperLeft,
		&Omni4WD::setCarLowerRight,
		&Omni4WD::setCarLowerLeft,
		&Omni4WD::setCarUpperRight,
		&Omni4WD::setCarRotateLeft,
		&Omni4WD::setCarRotateRight
	};

	for(int i=0;i<10;++i) {
		(this->*carAction[i])(0); // default parameters not available in function pointer
		setCarSpeedMMPS(speedMMPS,uptime);
		delayMS(duration,debug);
		setCarSlow2Stop(uptime);
	}
	setCarStop();
	delayMS(duration);
	//switchMotors();
}
/*		// original
void Omni4WD::demoActions(unsigned int speedMMPS,unsigned int uptime,
							unsigned int duration,bool debug) {
	setCarAdvance();
	setCarSpeedMMPS(speedMMPS,uptime);
	delayMS(duration,debug);
	setCarSlow2Stop(uptime);
	setCarBackoff();
	setCarSpeedMMPS(speedMMPS,uptime);
	delayMS(duration,debug);
	setCarSlow2Stop(uptime);
	setCarLeft();
	setCarSpeedMMPS(speedMMPS,uptime);
	delayMS(duration,debug);
	setCarSlow2Stop(uptime);
	setCarRight();
	setCarSpeedMMPS(speedMMPS,uptime);
	delayMS(duration,debug);
	setCarSlow2Stop(uptime);
	setCarUpperLeft();
	setCarSpeedMMPS(speedMMPS,uptime);
	delayMS(duration,debug);
	setCarSlow2Stop(uptime);
	setCarLowerRight();
	setCarSpeedMMPS(speedMMPS,uptime);
	delayMS(duration,debug);
	setCarSlow2Stop(uptime);
	setCarLowerLeft();
	setCarSpeedMMPS(speedMMPS,uptime);
	delayMS(duration,debug);
	setCarSlow2Stop(uptime);
	setCarUpperRight();
	setCarSpeedMMPS(speedMMPS,uptime);
	delayMS(duration,debug);
	setCarSlow2Stop(uptime);
	setCarRotateLeft();
	setCarSpeedMMPS(speedMMPS,uptime);
	delayMS(duration,debug);
	setCarSlow2Stop(uptime);
	setCarRotateRight();
	setCarSpeedMMPS(speedMMPS,uptime);
	delayMS(duration,debug);
	setCarSlow2Stop(uptime);
	setCarStop();
	delayMS(duration,debug);
	switchMotors();
}
 */
void Omni4WD::debugger(bool wheelULDebug,bool wheelLLDebug,bool wheelLRDebug,bool wheelURDebug) const {
	if(wheelULDebug) _wheelUL->debugger();
	if(wheelLLDebug) _wheelLL->debugger();
	if(wheelLRDebug) _wheelLR->debugger();
	if(wheelURDebug) _wheelUR->debugger();
}




