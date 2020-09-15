#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
//ALIENTEK Mini STM32�����巶������3
//����ʵ��   
//����֧�֣�www.openedv.com
//������������ӿƼ����޹�˾
 int main(void)
 {	
	u8 t;
	u8 len;	
	u16 times=0; 
	 
	 u8 Res;
 
	delay_init();	    	 //��ʱ������ʼ��	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// �����ж����ȼ�����2
	uart_init(115200);	 //���ڳ�ʼ��Ϊ9600
	LED_Init();		  	 //��ʼ����LED���ӵ�Ӳ���ӿ� 
 
	while(1)
	{
		if(USART_RX_STA)//if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//�õ��˴ν��յ������ݳ���
			printf("\r\nmessage recieve\r\n");
			for(t=0;t<len;t++)
			{
				USART1->DR=USART_RX_BUF[t];
				while((USART1->SR&0X40)==0);//�ȴ����ͽ���
			}
			printf("\r\n\r\n");//���뻻��
			//printf("%c\r\n\r\n",USART_RX_BUF[0]);
			USART_RX_STA=0;
		}else
		{
			times++;
			if(times%1000==0)
			{
				printf("5seconds test%d\r\n",times);
				//printf("test\r\n\r\n\r\n");
				//printf("%c\r\n\r\n",USART_RX_BUF[0]);
			}
			//if(times%200==0)printf("0.2seconds test\r\n");  
			if(times%30==0)LED1=!LED1;//��˸LED,��ʾϵͳ��������.
			delay_ms(10);   
		}
//		if(USART_RX_BUF[0])
//		{
//			LED0=!LED0;
//		}
//		else
//			LED0=0;
	}	 
}


