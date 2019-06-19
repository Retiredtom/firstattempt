/**********************************************************************
* Filename    : 18_74hc595.c
* Description : Use 74HC595 to control LEDs.
* Author      : Robot
* E-mail      : support@sunfounder.com
* website     : www.sunfounder.com
* Update      : Cavon    2016/07/01
**********************************************************************/
#include <wiringPi.h>
#include <stdio.h>

#define   SDI   0   //serial data input
#define   RCLK  1   //memory clock input(STCP)
#define   SRCLK 2   //shift register clock input(SHCP)

unsigned char LED[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80};


void pulse(int pin){
	digitalWrite(pin, 0);
	digitalWrite(pin, 1);
}

void SIPO(unsigned char byte){
	int i;

	for(i=0;i<8;i++){
		digitalWrite(SDI, ((byte & (0x80 >> i)) > 0));
		pulse(SRCLK);
	}
}

void init(void){
	pinMode(SDI, OUTPUT); 
	pinMode(RCLK, OUTPUT); 
	pinMode(SRCLK, OUTPUT); 

	digitalWrite(SDI, 0);
	digitalWrite(RCLK, 0);
	digitalWrite(SRCLK, 0);
}

int main(void){
	int i;

	if(wiringPiSetup() == -1){ //when initialize wiring failed, print messageto screen
		printf("setup wiringPi failed !");
		return 1; 
	}

	init();


	printf("\n");
	printf("\n");
	printf("========================================\n");
	printf("|           LEDs with 74HC595          |\n");
	printf("|    ------------------------------    |\n");
	printf("|         DS connect to GPIO0          |\n");
	printf("|         STCP connect to GPIO1        |\n");
	printf("|        SHCP connect to GPIO 2        |\n");
	printf("|                                      |\n");
	printf("|       Control LEDs with 74HC595      |\n");
	printf("|                                      |\n");
	printf("|                            SunFounder|\n");
	printf("========================================\n");
	printf("\n");
	printf("\n");

	while(1){
		for(i=0;i<8;i++){
			SIPO(LED[i]);
			pulse(RCLK);
			delay(150);
			//printf("i = %d\n",i);
		}
		delay(500);

		for(i=0;i<3;i++){
			SIPO(0xff);
			pulse(RCLK);
			delay(100);
			SIPO(0x00);
			pulse(RCLK);
			delay(100);
		}
		delay(500);
//		digitalWrite(RCLK,0);

		for(i=0;i<8;i++){
			SIPO(LED[8-i-1]);
			pulse(RCLK);
			delay(150);
		}
		delay(500);

	    for(i=0;i<3;i++){
			SIPO(0xff);
			pulse(RCLK);
			delay(100);
			SIPO(0x00);
			pulse(RCLK);
			delay(100);
		}
		delay(500);
	}

	return 0;
}

