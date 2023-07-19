/********************(C) COPRIGHT 2019 Crownto electronic **************************
 * �ļ���  ��main.c
 * ����    ��        
 * Ӳ�����ӣ�
 * LCD1602:RS -> PA11; RW -> PA12; E -> PA15;
 *         D0~D7 -> PB3~PB10
 * PHģ��: VCC -> 5V; GND -> GND; PO -> PA2;
 *
 * ��������������PHֵҺ����ʾ(ADC1��PA2��DMA��ʽ��ȡ)��
             ���ڽ��ղ������õ�PHֵ��������115200����
 *           ��������λ����ʾPHֵ��
 * ����    �����е���
**********************************************************************************/
#include "stm32f10x.h"
#include "bsp_usart1.h"
#include <string.h>
#include "delay.h"
#include "driver_1602.h"
#include "math.h"
#include "bsp_adc.h"
#include "DS18B20.h"
#include "adc.h"


GPIO_InitTypeDef  GPIO_InitStructure; 
unsigned char AD_CHANNEL=0;
unsigned long PH_num=0,PU_V=0;
float PH_Value=0;
u8 ph_temp=0,tu_temp=0;
u16 ph_result=0,tu_result=0;
u16 adc_1,adc_2;
u16 adc_v_1,adc_v_2;

u8 ISendByte(unsigned char sla,unsigned char c);
u8 IRcvByte(unsigned char sla);	
u8 SPIx_ReadWriteByte(u8 TxData);

unsigned char  Tx[20];   //���߷��ͻ���
extern uint8_t ch;
extern char rx_buf[100];
char *pch=(char *)&ch;
char *jiancha1="+QIOPEN: 1,0";
char *jiancha2="+QIURC: \"recv\",11";
float temperature;
float turdity;
unsigned short zhuodu;//�Ƕ�
// ADC1ת���ĵ�ѹֵͨ��MDA��ʽ����SRAM
extern __IO uint16_t ADC_ConvertedValue;

// �ֲ����������ڱ���ת�������ĵ�ѹֵ 	 
float ADC_ConvertedValueLocal;  

/***************************************************************************
 * ��  �� : MAIN����
 * ��  �� : ��
 * ����ֵ : ��
 **************************************************************************/
 
void GPIO_Configuration(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	/* Enable the GPIO  Clock */					 		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOB|RCC_APB2Periph_GPIOC| RCC_APB2Periph_AFIO|RCC_APB2Periph_SPI1,ENABLE);
	
	//GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable,ENABLE);		//����������ΪJTAG�ڵ�GPIO��
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_JTAGDisable,ENABLE);		//����PB����IO��JTAG����
	
	
//1602 D0~D7 ����	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|
	GPIO_Pin_7|GPIO_Pin_8|GPIO_Pin_9|GPIO_Pin_10 ;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; /*I/O ���� */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; /*I/O ����ٶ�*/
	GPIO_Init(GPIOB, &GPIO_InitStructure);

	
//1602 EN RS RW ����	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_11|GPIO_Pin_12|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; /*I/O ���� */
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_10MHz; /*I/O ����ٶ�*/
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
   /* Configure  DRDY */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	

	
}

void PH_Value_Conversion()
{
	
	  ADC_ConvertedValueLocal =(float) ADC_ConvertedValue/4096*3.3; // ��ȡת����ADֵ
	
		PH_Value=-5.7541*ADC_ConvertedValueLocal+16.654;
	
    
	if(PH_Value<=0.0){PH_Value=0.0;}
	if(PH_Value>=14.0){PH_Value=14.0;}
	
		  /*��ʾ��ѹ*/
	Tx[0]=(int)(PH_Value*100)/1000+'0';	
	Tx[1]=(int)(PH_Value*100)%1000/100+'0';
	Tx[2]='.';
	Tx[3]=(int)(PH_Value*100)%100/10+'0';
	Tx[4]=(int)(PH_Value*100)%10+'0';
}

void Display_Data()
{
		//��ʾPHֵ	
		LCD_printchar(3,0,Tx[0]);
		LCD_printchar(4,0,Tx[1]);
		LCD_printchar(5,0,Tx[2]);
		LCD_printchar(6,0,Tx[3]);
		LCD_printchar(7,0,Tx[4]);
}

/**
  * @brief  ������
  * @param  ��
  * @retval ��
  */
int main(void)
{	
		GPIO_Configuration();
    /* ����USART1 */
    USART1_Config();
		// ADC ��ʼ��
	  ADCx_Init();  
    /* ��ʼ��LCD1602 */
		LCD_init(); 
	
	ADC_init(ADC_CH3);
	 DS18B20_Init();
     
	LCD_printstring(0,0,"PH:"); 

  char str1[]="AAT+QIOPEN=1,0,\"TCP\",\"172.28.0.4\",8009,0,2\r";
	char str2[]="hELLO\r";
	char str3[]="AT+QICLOSE=0\r";
	delay_ms(100);
	//printf("%s",str1);
	printf("%s",str1);
	delay_ms(1000);
	printf("Hello Server\r\n");
	//printf("h%s",str2);
	delay_ms(1000);
	printf("%s",str3);
	
	//while(1){
	//printf("AAT+QIOPEN=1,1,\"TCP LISTENER\",\"127.0.0.1\",0,2020,2\r\n");
	//delay_ms(1000);
	//printf("%s\n",rx_buf);
	
	/*if(strstr(pch,jiancha1)!=NULL)
		break;
	else{
	printf("AT+QICLOSE=11\r\n");
	delay_ms(1000);	
	printf("AT+QICLOSE=1\r\n");
	delay_ms(1000);
	}
	}*/
	
	//while(1){
	//if(!strcmp(pch,jiancha2)){
	printf("AT+QIRD=11,1500");
	printf("%s\n",rx_buf);
	//}}
	//printf("AT+QIRD=11,1500");
	//delay_ms(1000);
	//printf("AT+QICLOSE=11");
	//delay_ms(1000);
	//printf("AT+QICLOSE=1");

	
  
	
  /*while(1)
	{	
	temperature=DS18B20_Get_Temp();
	zhuodu=Get_Adc_Average(ADC_CH3,10);
	PH_Value_Conversion();	
	Display_Data();
	
	turdity=(float)zhuodu*(3.3/4096);
	turdity = turdity*100/3.3;
	if(turdity > 100) turdity = 100;
	turdity=100-turdity-47;
	if(turdity<0) turdity=0;
	
		
		
	printf("%s\r\n",Tx);
	printf("%.2f\r\n",temperature);
		
	printf("%.2f\r\n",turdity);
	delay_ms(1000);
		
	}	*/
}
/*********************************************END OF FILE**********************/
