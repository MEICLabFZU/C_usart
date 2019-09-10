#include "sys.h"
#include <stdio.h>
#include <string.h>




char a_N,a_O,b;

void delay_s()
{
	int i;
	for(i=0;i<1;i++)
	 delay_ms(1000);
}
int main()
{
  Stm32_Clock_Init(9);
	delay_init();  
	uart1_init(72,115200);
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

	motor_init();
/*	while(1)
	{
	turn_3(10);
	turn_4(16);
	}
*/
  printf("123\n\r");
	turn_3(10);
	turn_4(16);
	while(1)
	{

		b=getchar();
		printf("%c\n\r",b);
		
		if(b!='\0')
		{		

			
		switch(b)
		{
			case 'B': turn_3(5);delay_ms(1000);turn_4(10);;break;// printf("zhusheqi\n\r");
			case 'Q': turn_3(10);delay_ms(1000);turn_4(22);;break;//printf("shuyedai\n\r"); 
			case 'H': turn_3(10);delay_ms(1000);turn_4(10);;break;//printf("shabu\n\r");
			case 'N': turn_3(5);delay_ms(1000);turn_4(22);;break;;//printf("yaoping\n\r");
			default: turn_3(5);delay_ms(1000);turn_3(10);break;//printf("zhe shi sha\n\r");
		}	
		delay_ms(1000);
		turn_4(16);;
	   
	}
		else {;} 	
	}
	
}

