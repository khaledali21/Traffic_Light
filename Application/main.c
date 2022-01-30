/*
 * UART_Driver.c
 *
 * Created: 1/24/2022 12:19:11 AM
 * Author : Khaled Ali
 */ 

#include "main.h"

LED_t led_red = {PORTB, PIN4};
LED_t led_yellow = {PORTB, PIN5};
LED_t led_green = {PORTB, PIN6};
LED_t led_err = {PORTB, PIN7};
uint8_t command[20];
int main(void)
{
	LED_u8Init(&led_red);
	LED_u8Init(&led_yellow);
	LED_u8Init(&led_green);
	LED_u8Init(&led_err);
	DIO_u8SetPinDirection(PORTD, PIN0, INPUT_PIN_NO_PULLUP);
	DIO_u8SetPinDirection(PORTD, PIN1, OUTPUT_PIN);
	UART_u8Init(9600);
	uint8_t data;
	uint8_t status;
    while (1) 
    {
		status = UART_u8ReceiveString(command, '\r');
		if(status == OK){
			if(strcmp(command, "START") == MATCHED){
				LED_u8ON(&led_green);
				LED_u8OFF(&led_yellow);
				LED_u8OFF(&led_red);
				LED_u8OFF(&led_err);
				UART_u8SendString("Green LED is on\n\r");
			}
			else if(strcmp(command, "WAIT") == MATCHED){
				LED_u8ON(&led_yellow);
				LED_u8OFF(&led_green);
				LED_u8OFF(&led_red);
				LED_u8OFF(&led_err);
				UART_u8SendString("Yellow LED is on\n\r");
			}
			else if(strcmp(command, "STOP") == MATCHED){
				LED_u8ON(&led_red);
				LED_u8OFF(&led_yellow);
				LED_u8OFF(&led_green);
				LED_u8OFF(&led_err);
				UART_u8SendString("Red LED is on\n\r");
			}
			else if(strcmp(command, "AT") == MATCHED){
				LED_u8OFF(&led_err);
				UART_u8SendString("OK\n\r");
			}
			else{
				LED_u8ON(&led_err);
				UART_u8SendString("Wrong Command\n\r");
			}
		}
		else{
				LED_u8ON(&led_err);
				UART_u8SendString("Something Went Wrong\n\r");			
		}
    }
}


//
//uint8_t str_cmp(uint8_t* str1, uint8_t* str2){
	//uint8_t i = 0;
	//
//}

