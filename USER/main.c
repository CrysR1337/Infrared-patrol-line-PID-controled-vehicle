#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
//ALIENTEK Mini STM32开发板范例代码3
//串口实验   
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司
 int main(void)
 {	
	u8 t;
	u8 len;	
	u16 times=0; 
	 
	 u8 Res;
 
	delay_init();	    	 //延时函数初始化	
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);// 设置中断优先级分组2
	uart_init(115200);	 //串口初始化为9600
	LED_Init();		  	 //初始化与LED连接的硬件接口 
 
	while(1)
	{
		if(USART_RX_STA)//if(USART_RX_STA&0x8000)
		{					   
			len=USART_RX_STA&0x3fff;//得到此次接收到的数据长度
			printf("\r\nmessage recieve\r\n");
			for(t=0;t<len;t++)
			{
				USART1->DR=USART_RX_BUF[t];
				while((USART1->SR&0X40)==0);//等待发送结束
			}
			printf("\r\n\r\n");//插入换行
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
			if(times%30==0)LED1=!LED1;//闪烁LED,提示系统正在运行.
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


