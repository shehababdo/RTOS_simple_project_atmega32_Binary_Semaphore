/*
 * Binnary_Semaphore_02.c
 *
 * Created: 8/12/2023 10:17:32 AM
 * Author : Shehab Abdo
 */ 

#include "DIO.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"
#define F_CPU 16000000
#include "util/delay.h"

TaskHandle_t Task_Init_handler=NULL;
TaskHandle_t Task_LED_handler=NULL;
TaskHandle_t Task_BUTTON_handler=NULL;

SemaphoreHandle_t  Sema_Handle_1=NULL;
void Task_Init(void* ptr_1)
{
	while (1)
	{
		DIO_set_pinDir(PORT_B,PIN_0,DIO_PIN_INPUT);
		DIO_set_pinDir(PORT_C,PIN_2,DIO_PIN_OUTPUT);
			 
		vTaskSuspend(Task_Init_handler);
	}
}

void Task_LED(void* ptr_2)
{
	
	Sema_Handle_1=xSemaphoreCreateBinary();
	 xSemaphoreTake(Sema_Handle_1,(TickType_t) 0 );  //cause it has been created just above it so it will succeed to take sema
	 
	 while (1)
	 {
		 xSemaphoreTake(Sema_Handle_1,(TickType_t) portMAX_DELAY );
		 DIO_TOGGLE(PORT_C,PIN_2);
		 
	 }
}

void Task_BUTTON(void* ptr_3)
{
	uint8 val=0;
	while (1)
	{
		DIO_read_pin(PORT_B,PIN_0,&val);
		while(GET_BIT(PINB,PIN_0)==DIO_PIN_HIGH);
		_delay_ms(10);
		

		if (val==DIO_PIN_HIGH)
		{
			if (xSemaphoreGive(Sema_Handle_1)!=pdTRUE)
			{
				//if semaphore not given 
				DDRA=0x55;
			}
			
		}

	}	
}

int main(void)
{
	xTaskCreate
	(
		Task_Init,			 //ptr to the task
		"Task_Init_",		 //name of the task
		200,				 //size (its random here)
		NULL,				 //parametr sent
		3,					 //priority (highest)	
		&Task_Init_handler  //handler
	);
			
	xTaskCreate(
	Task_LED,			 //ptr to the task
	"Task_LED_",		 //name of the task
	200,				 //size (its random here)
	NULL,				 //parametr sent
	2,					 //priority (2nd)
	&Task_LED_handler  //handler		
	);

	xTaskCreate(
	Task_BUTTON,			 //ptr to the task
	"Task_BUTTON_",		 //name of the task
	200,				 //size (its random here)
	NULL,				 //paramert sent
	1,					 //priority (lowest)
	&Task_BUTTON_handler  //handler
	);	
	
   vTaskStartScheduler();
    while (1) 
    {
    }
}

