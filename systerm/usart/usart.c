#include "usart.h"	  

//extern u8 USART_REC_Finish_FLAG;
//extern int sp;
//extern char SendData[20];
//�������´���,֧��printf����,������Ҫѡ��use MicroLIB	  
#if 1
#pragma import(__use_no_semihosting)             
//��׼����Ҫ��֧�ֺ���                 
struct __FILE 
{ 
	int handle; 
	/* Whatever you require here. If the only file you are using is */ 
	/* standard output using printf() for debugging, no file handling */ 
	/* is required. */ 
};
/* FILE is typedef�� d in stdio.h. */ 
FILE __stdout;       
//����_sys_exit()�Ա���ʹ�ð�����ģʽ    
void _sys_exit(int x) 
{ 
	x = x; 
} 

int fgetc(FILE *stream)
{
    while(!(USART1->SR & (1 << 5))){};//????????
    return USART1->DR;
}
//�ض���fputc���� 
int fputc(int ch, FILE *f)
{      

	while((USART1->SR&0X40)==0);//ѭ������,ֱ���������   
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
	temp=(float)(pclk2*1000000)/(bound*16);//�õ�USARTDIV
	mantissa=temp;				 //�õ���������
	fraction=(temp-mantissa)*16; //�õ�С������	 
    mantissa<<=4;
	mantissa+=fraction; 
	RCC->APB2ENR|=1<<2;   //ʹ��PORTA��ʱ��  
	RCC->APB2ENR|=1<<14;  //ʹ�ܴ���ʱ�� 
	GPIOA->CRH&=0XFFFFF00F;//IO״̬����
	GPIOA->CRH|=0X000008B0;//IO״̬����
		  
	RCC->APB2RSTR|=1<<14;   //��λ����1
	RCC->APB2RSTR&=~(1<<14);//ֹͣ��λ	   	   
	//����������
 	USART1->BRR=mantissa; // ����������	 
	USART1->CR1|=0X200C;  //1λֹͣ,��У��λ.

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
  //USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);   //�����ж�	 
  //USART_ITConfig(USART1, USART_IT_TXE, ENABLE);	   //�����ж�
  USART_Cmd(USART1, ENABLE);
  USART_ITConfig(USART1, USART_IT_RXNE, ENABLE); //�����ж�ʹ��
	
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0); 						
  NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;   
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0; 
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE; 
  NVIC_Init(&NVIC_InitStructure); 

}*/
//�����ַ�
char usart1_getc(void)
{
    char temp = 0;
    while(USART_GetFlagStatus(USART1,USART_FLAG_RXNE)!= SET);
    temp = USART_ReceiveData(USART1);
    return temp;
}

//�����ַ���
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
			if(USART_ReceiveData(USART1)=='\n')	 //���ڵ������ֱ����ǵ��ϻ��з�
				{ 
					sp=0;
					USART_REC_Finish_FLAG = 1;
					for(i=0;i<20;i++)           //i �ַ�������
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
        USART_ClearITPendingBit(USART1, USART_IT_RXNE);	//��������жϱ�־
				
    }
	}
*/


