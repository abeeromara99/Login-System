/*
 * KPD_ass1.c
 *
 *  Created on: Dec 9, 2023
 *      Author: Abir Omara
 */




/* Lib layer */
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>
#define F_CPU   8000000UL

/* MCAL */
#include "DIO_interface.h"

/* HAL */
#include "KPD_interface.h"
#include "LCD_interface.h"

void Green_led (void);
void Red_led (void);
void Turn_Off_LED (void);

int main ()
{

	u8 Correct_password [4]={'1','2','3','4'};
	u8 Input_password [4];
	u8 Local_u8Counter=0;
	u8 Local_u8NumOfAttempts=0;
	u8 Local_u8NumOfMaxAttempts=3;

	u8 Local_u8Key;

	DIO_voidInit();
	LCD_voidInt();

	LCD_u8GoToXY(1,0);
	LCD_voidWriteString("Enter password");
	while (Local_u8NumOfAttempts !=Local_u8NumOfMaxAttempts)
	{
		while (Local_u8Counter != 4)
		{
			KPD_u8GetKeyState(&Local_u8Key);
			//if there are no switch pressed
			//no displaying on LCD
			if (Local_u8Key != KPD_u8_KEY_NOT_PRESSED)
			{
				LCD_u8GoToXY(2,Local_u8Counter);
				LCD_voidSendData(Local_u8Key);
				_delay_ms(200);
				LCD_u8GoToXY(2,Local_u8Counter);
				LCD_voidSendData('*');
				Input_password[Local_u8Counter]=Local_u8Key;
				Local_u8Counter++;
			}
		}

		if ((Input_password[0]==Correct_password[0]) && (Input_password[1]==Correct_password[1]) && (Input_password[2]==Correct_password[2])  &&(Input_password[3]==Correct_password[3]))
		{
			LCD_voidClearDisplay();
			LCD_u8GoToXY(1,0);
			LCD_voidWriteString("correct         password");
			Green_led();
			break;
		}
		else
		{
			LCD_voidClearDisplay();
			LCD_u8GoToXY(1,0);
			LCD_voidWriteString("incorrect       password");
			_delay_ms(500);
			LCD_voidClearDisplay();
			LCD_u8GoToXY(1,0);
			LCD_voidWriteString("try again");
			Local_u8Counter=0;
			Local_u8NumOfAttempts++;
		}
		if (Local_u8NumOfAttempts ==Local_u8NumOfMaxAttempts)
		{
			LCD_voidClearDisplay();
			LCD_u8GoToXY(1,0);
			LCD_voidWriteString("you tried 3     times");
			_delay_ms(500);
			LCD_voidClearDisplay();
			LCD_u8GoToXY(1,0);
			LCD_voidWriteString("wait for 5 sec  and try later");
			Red_led();
			_delay_ms(5000);
			Turn_Off_LED();
			LCD_voidClearDisplay();
			LCD_u8GoToXY(1,0);
			LCD_voidWriteString("Enter password");
			Local_u8NumOfAttempts=0;

		}
	}

	return 0;
}

void Green_led (void)
{
	DIO_u8SetPinValue(DIO_u8_PORTB,DIO_u8_PIN0,DIO_u8_PIN_HIGH);
}
void Red_led (void)
{
	DIO_u8SetPinValue(DIO_u8_PORTB,DIO_u8_PIN1,DIO_u8_PIN_HIGH);
}

void Turn_Off_LED (void)
{
	DIO_u8SetPinValue(DIO_u8_PORTB,DIO_u8_PIN0,DIO_u8_PIN_LOW);
	DIO_u8SetPinValue(DIO_u8_PORTB,DIO_u8_PIN1,DIO_u8_PIN_LOW);
}
