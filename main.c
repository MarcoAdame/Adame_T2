/*
 * Marco Federico Adame Oropeza
 */

/**
 * @file    LecturaEscrituraPinDig.c
 * @brief   Application entry point.
 */
//#include <stdio.h>
//#include "board.h"
//#include "peripherals.h"
//#include "pin_mux.h"
//#include "clock_config.h"
//#include "MK64F12.h"
//#include "fsl_debug_console.h"
/**Standard input/output to debug console*/
#include <stdio.h>
/**Standard integer definition provided by the compiler*/
#include <stdint.h>
#include "MK64F12.h"
#include "fsl_gpio.h"
#include "fsl_port.h"
#include "fsl_common.h"

#define LED_R 22u  	//PortB
#define LED_B 21u	//PortB
#define LED_G 26u	//PortE
#define RED		0x00400000
#define BLUE	0x00200000
#define GREEN	0x04000000

#define SW_2 6u //PortC
#define PUSH_2 0x40

#define SW_3 4u //PortA
#define PUSH_3 0x10

#define CORE_FREQ 21000000u
#define DELAY 1000000u

gpio_pin_config_t sw_config = {
		kGPIO_DigitalInput,
		0,
};

void ledOff(){
	GPIOB->PDOR |= RED;
	GPIOB->PDOR |= BLUE;
	GPIOE->PDOR |= GREEN;
}
int main(void) {
	int i=0, cont=0;
	//Encender relojes
		//Registra para habilitar el clock del puerto B
		SIM->SCGC5 = 0x2400; //activacion del reloj puerto B y E
		SIM->SCGC5 |= 0xA00; //Activacion del reloj del puerto A y C
	//Configurar el puerto para que se comporte como GPIO
		//Outputs
		PORTB->PCR[LED_R] = 0x00000100;
		PORTB->PCR[LED_B] = 0x00000100;
		PORTE->PCR[LED_G] = 0x00000100;


		//INPUTS
		//GPIOA->PDIR = PUSH_2;
		PORT_SetPinMux(PORTA,SW_3, kPORT_MuxAsGpio);
		PORT_SetPinMux(PORTC,SW_2, kPORT_MuxAsGpio);
		GPIO_PinInit(GPIOC, SW_2,&sw_config);
		GPIO_PinInit(GPIOA, SW_3,&sw_config);

		//OUTPUS
		//Registro de salida
			GPIOB->PDOR = 0x00400000;  	//LED_R
			GPIOB->PDOR |= 0x00200000;	//LED_B
			GPIOE->PDOR = 0x04000000;

	//Direccion de registro   (Input / Output)
	GPIOB->PDDR = 0x00400000;  	//LED_R
	GPIOB->PDDR |= 0x00200000;	//LED_B
	GPIOE->PDDR = 0x04000000;




    while(1) {

       	if(!GPIO_PinRead(GPIOC,SW_2)&&!GPIO_PinRead(GPIOA,SW_3)){
    		//blanco
    		ledOff();
    		GPIOB->PDOR ^= RED;
    		GPIOB->PDOR ^= BLUE;
    		GPIOE->PDOR ^= GREEN;
    		i=0;
    		cont=0;
    		printf("White\n");
    		SDK_DelayAtLeastUs(DELAY, CORE_FREQ);
    	}else{
    		if(!GPIO_PinRead(GPIOC,SW_2)){
    			i=1;
    		}
    		if(!GPIO_PinRead(GPIOA,SW_3)){
    			i=-1;
    		}
    	}

    	switch(cont){
    	case 1: //amarillo
    		ledOff();
    		GPIOB->PDOR ^= RED;
    		GPIOE->PDOR ^= GREEN;
    		printf("Yellow \n");
    		SDK_DelayAtLeastUs(DELAY, CORE_FREQ);

    		break;
    	case 2: //rojo
    		ledOff();
    		GPIOB->PDOR ^= RED;
    		printf("Red \n");
    		SDK_DelayAtLeastUs(DELAY, CORE_FREQ);

    		break;
    	case 3: //morado
    	    ledOff();
    	    GPIOB->PDOR ^= RED;
    	    GPIOB->PDOR ^= BLUE;
    	    printf("Purple \n");
    	    SDK_DelayAtLeastUs(DELAY, CORE_FREQ);
    	    break;
    	case 4: //azul
    		ledOff();
    		GPIOB->PDOR ^= BLUE;
    		printf("Blue \n");
    		SDK_DelayAtLeastUs(DELAY, CORE_FREQ);
    		break;
    	case 5: //verde
    		ledOff();
    		GPIOE->PDOR ^= GREEN;
    		printf("Green \n");
    		SDK_DelayAtLeastUs(DELAY, CORE_FREQ);
    		break;
    	default:

    		break;
    	}
    	if(cont==5 && i==1)
    		cont=0;
    	if((cont<=1) && i==-1)
    		cont=6;

    	cont=cont+i;


    }
    return 0 ;
}
