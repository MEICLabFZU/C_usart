#include "usart.h"	  

//extern u8 USART_REC_Finish_FLAG;
//extern int sp;
//extern char SendData[20];
//加入以下代码,支持printf函数,而不需要选择use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//标准库需要的支持函数                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
};
/* FILE is typedef’ d in stdio.h. */ 
FILE __stdout;       
//定义_sys_exit()以避免使用半主机模式    
void _sys_exit(int x) 
{ 
	x = x; 
} 

int fgetc(FILE *stream)
{
    while(!(USART1->SR & (1 << 5))){};//????????
    return USART1->DR;
}
//重定义fputc函数 
int fputc(int ch, FILE *f)
{      

	while((USART1->SR&0X40)==0);//循环发送,直到发送完毕   
	USART1->DR = (u8) ch;      

	return ch;
}
#endif 
//end
//////////////////////////////////////////////////////////////////

void uart1_init(u32 pclk2,u32 bound)
{  	 
	float temp;
	u16 mantissa;
	u16 fraction;	   
	temp=(float)(pclk2*1000000)/(bound*16);//得到USARTDIV
	mantissa=temp;				 //得到整数部分
	fraction=(temp-mantissa)*16; //得到小数部分	 
    mantissa<<=4;
	mantissa+=fraction; 
	RCC->APB2ENR|=1<<2;   //使能PORTA口时钟  
	RCC->APB2ENR|=1<<14;  //使能串口时钟 
	GPIOA->CRH&=0XFFFFF00F;//IO状态设置
	GPIOA->CRH|=0X000008B0;//IO状态设置
		  
	RCC->APB2RSTR|=1<<14;   //复位串口1
	RCC->APB2RSTR&=~(1<<14);//停止复位	   	   
	//波特率设置
 	USART1->BRR=mantissa; // 波特率设置	 
	USART1->CR1|=0X200C;  //1位停止,无校验位.

}
/*void usart_init()
{
  GPIO_InitTypeDef GPIO_InitStructure;
	USART_InitTypeDef USART_InitStructure; 
	NVIC_InitTypeDef NVIC_InitStructure;
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_USART1,ENABLE);
	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;	         
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);		   

  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10;	        
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;  
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz; 
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	

  USART_InitStructure.USART_BaudRate = 115200;
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

	 USART_Init(USART1, &USART_InitStructure); 
  //USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);   //接收中断	 
  //USART_ITConfig(USART1, USART_IT_TXE, ENABLE);	   //发送中断
  USART_Cmd(USART1, ENABLE);
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //接收中断使能
	
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0); 						
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;   
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
  NVIC_Init(&NVIC_InitStructure); 

}*/
//接收字符
char usart1_getc(void)
{
    char temp = 0;
    while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)!= SET);
    temp = USART_ReceiveData(USART1);
    return temp;
}

//接收字符串
int usart1_getstr(unsigned char* buff,int len)
{
   int i = 0;
   for(i = 0;i < len;i++)
  {
   buff[i] = usart1_getc();
  }
   return len;
}
/*
void USART1_IRQHandler(void)
{
    u8 i=0; 
	  char Rec_Buffer[20];
	  
    if(USART_GetFlagStatus(USART1,USART_IT_RXNE)==SET) 
    {
			if(USART_ReceiveData(USART1)=='\n')	 //串口调试助手必须是点上换行符
				{ 
					sp=0;
					USART_REC_Finish_FLAG = 1;
					for(i=0;i<20;i++)           //i 字符串长度
					Rec_Buffer[i]='\0';
				}
				else
					{
						if(sp==0)
							{
								for(i=0;i<20;i++)
								SendData[i]='\0';
							}	
							Rec_Buffer[sp] = USART_ReceiveData(USART1);
							SendData[sp]= Rec_Buffer[sp];
							sp=sp+1;
					}
		}
		if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET) 
    { 
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);	//清除接收中断标志
				
    }
	}
*/


