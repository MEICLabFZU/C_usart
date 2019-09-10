#include "motor.h"

void motor_init()
{
	//
	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure; 
	
  RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA |RCC_APB2Periph_GPIOB,ENABLE); 
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3|RCC_APB1Periph_TIM4,ENABLE);//| ,  
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7  ; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7; 
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOB, &GPIO_InitStructure);	/**/
	
	TIM_TimeBaseStructure.TIM_Period = 199; 
  TIM_TimeBaseStructure.TIM_Prescaler =7199; 
  TIM_TimeBaseStructure.TIM_ClockDivision = 0; 
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;  
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure); 
	TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure); 
	
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	
  TIM_OC2Init(TIM3, &TIM_OCInitStructure);
	TIM_OC2Init(TIM4, &TIM_OCInitStructure);
	
  TIM_OC2PreloadConfig(TIM3, TIM_OCPreload_Enable); 
	TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable); 
	
	TIM_Cmd(TIM3,ENABLE);
	TIM_Cmd(TIM4,ENABLE);
}

void turn_3( u8 a )
{ 
	 TIM_SetCompare2(TIM3,a);
}
void turn_4( u8 a )
{ 
	 TIM_SetCompare2(TIM4,a);
}





