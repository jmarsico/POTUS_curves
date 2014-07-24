#include "PCA9685.h"

PCA9685::PCA9685(int _numBoards)
{
	numBoards = _numBoards;					//number of PCA9685 boards to be used
	
	int addr;
    string hexAddr;
    int hexAddrToInt;

	for(int i = 0; i < numBoards; i++)		//initialize an array of new board objects
	{
		addr = 40 + i;
        hexAddr = "0x" + ofToString(addr);
        int hexAddrToInt = ofHexToInt(hexAddr);

		ofLog() << "PCA9685: creating new board " << "hex: " << hexAddr << " int: " << hexAddrToInt;
		pwm[i] = new PWM(hexAddrToInt, true);
		pwm[i] -> setPWMFreq(6000);

	}
}

void PCA9685::setLED(int channel, int val)
{
	
	
	if(channel <=numBoards*16-1)		//check to make sure channel exists
	{
		int unit = 0;					//variable for index in pwm[] array
		int unitChan = channel;			//channel relative to it's board (0-16)
		
		unit = floor(channel/16);			//unit is channel/16, rounded down
		unitChan = channel - unit*16;		//re-interpret channel for this pwm[i]
		
		pwm[unit]->setPWM(unitChan, 0, val);	//write to the unit/channel
	}
}

	