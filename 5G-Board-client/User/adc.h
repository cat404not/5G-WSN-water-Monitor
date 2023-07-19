/**
  ******************************************************************************
  * @file    adc.c
  * @author  ���ĳ� 
	* @qq      269426626
  * @version V1.0
  * @date    2016.9.10
  * @note    �˳���ΪARM��ADC�ĵײ���
  ******************************************************************************
  */

#ifdef __cplusplus
 extern "C" {
#endif
#include "stm32f10x.h"
#include "delay.h"
#define u16 unsigned short
#define u8 unsigned  char

/* ADC1??�������̨� ???��?����? */
#define ADC_CH0   0       // PA0
#define ADC_CH1   1  			// PA1
#define ADC_CH2   2  			// PA2
#define ADC_CH3   3  			// PA3
#define ADC_CH4   4  			// PA4
#define ADC_CH5   5  			// PA5
#define ADC_CH6   6  			// PA6
#define ADC_CH7   7  			// PA7
#define ADC_CH8   8  			// PB0
#define ADC_CH9   9  			// PB1
#define ADC_CH10  10   		// PC0
#define ADC_CH11  11   		// PC1
#define ADC_CH12  12   		// PC2
#define ADC_CH13  13   		// PC3
#define ADC_CH14  14   		// PC4
#define ADC_CH15  15   		// PC5


//ADC1 API
void ADC_init(u8 ADC_CHx);
u16 Get_Adc(u8 ADC_CHx);
u16 Get_Adc_Average(u8 ADC_CHx,u8 times);


 /**
 * @brief   		ADC��ʼ������
 * @code
 *      				// ��ʼ��ADCͨ��4
 *      				ADC_init(ADC_CH4);
 * @endcode
 * @param[in]   ADC_CHx ADCͨ���ţ�   ֵ��ADC_CH0~ADC_CH15
 */
void ADC_init(u8 ADC_CHx)
{    
	switch(ADC_CHx)
	{
		case ADC_CH0: RCC->APB2ENR|=1<<2; GPIOA->CRL&=0XFFFFFFF0; break;
		case ADC_CH1: RCC->APB2ENR|=1<<2; GPIOA->CRL&=0XFFFFFF0F; break;
		case ADC_CH2: RCC->APB2ENR|=1<<2; GPIOA->CRL&=0XFFFFF0FF; break;
		case ADC_CH3: RCC->APB2ENR|=1<<2; GPIOA->CRL&=0XFFFF0FFF; break;
		case ADC_CH4: RCC->APB2ENR|=1<<2; GPIOA->CRL&=0XFFF0FFFF; break;
		case ADC_CH5: RCC->APB2ENR|=1<<2; GPIOA->CRL&=0XFF0FFFFF; break;
		case ADC_CH6: RCC->APB2ENR|=1<<2; GPIOA->CRL&=0XF0FFFFFF; break;
		case ADC_CH7: RCC->APB2ENR|=1<<2; GPIOA->CRL&=0X0FFFFFFF; break;
		case ADC_CH8: RCC->APB2ENR|=1<<3; GPIOB->CRL&=0XFFFFFFF0; break;
		case ADC_CH9: RCC->APB2ENR|=1<<3; GPIOB->CRL&=0XFFFFFF0F; break;
		case ADC_CH10:RCC->APB2ENR|=1<<4; GPIOC->CRL&=0XFFFFFFF0; break;
		case ADC_CH11:RCC->APB2ENR|=1<<4; GPIOC->CRL&=0XFFFFFF0F; break;
		case ADC_CH12:RCC->APB2ENR|=1<<4; GPIOC->CRL&=0XFFFFF0FF; break;
		case ADC_CH13:RCC->APB2ENR|=1<<4; GPIOC->CRL&=0XFFFF0FFF; break;
		case ADC_CH14:RCC->APB2ENR|=1<<4; GPIOC->CRL&=0XFFF0FFFF; break;
		case ADC_CH15:RCC->APB2ENR|=1<<4; GPIOC->CRL&=0XFF0FFFFF; break;
	}
																																								//ͨ��10/11����			 
	RCC->APB2ENR|=1<<9;    																												//ADC1ʱ��ʹ��	  
	RCC->APB2RSTR|=1<<9;   																												//ADC1��λ
	RCC->APB2RSTR&=~(1<<9);																												//��λ����	    
	RCC->CFGR&=~(3<<14);  																												//��Ƶ��������	
																																								//SYSCLK/DIV2=12M ADCʱ������Ϊ12M,ADC���ʱ�Ӳ��ܳ���14M!
																																								//���򽫵���ADC׼ȷ���½�! 
	RCC->CFGR|=2<<14;      	 
	ADC1->CR1&=0XF0FFFF;   																												//����ģʽ����
	ADC1->CR1|= 0<<16;
	ADC1->CR1|= ~(1<<8);
	ADC1->CR2|= 1<<20;
	ADC1->CR2&= ~(1<<1);
	ADC1->CR2|= 7<<17;
	ADC1->CR2&=~(1<<11); 
	ADC1->SMPR2&=~(7<<3);
	ADC1->SQR1&=~(0XF<<20);
	ADC1->SQR1|=0<<20;  
	ADC1->CR2|=1<<0;	
	ADC1->CR2|=1<<3;
	while(ADC1->CR2&(1<<3));
	ADC1->CR2|=1<<2;
	while(ADC1->CR2&(1<<2));
}				  

 /**
 * @brief   		�õ�ADCת��ֵ����
 * @code
 *      				// �õ�ADCͨ��4ֵ
 *      				Get_Adc(ADC_CH4);
 * @endcode
 * @param[in]   ADC_CHx ADCͨ���ţ�   ֵ��ADC_CH0~ADC_CH15
 */
u16 Get_Adc(u8 ADC_CHx)   
{
																															//����ת������	  		 
	ADC1->SQR3&=0XFFFFFFE0;																			//��������1 ͨ��ch
	ADC1->SQR3|=ADC_CHx;		  			    
	ADC1->CR2|=1<<22;       																		//��������ת��ͨ�� 
	while(!(ADC1->SR&1<<1));																		//�ȴ�ת������	 	   
	return ADC1->DR;																						//����adcֵ	
}

 /**
 * @brief   		�õ�ADCת��ƽ��ֵ����
 * @code
 *      				// �õ�ADCͨ��4ֵ������Ϊ20
 *      				Get_Adc_Average(ADC_CH4��20);
 * @endcode
 * @param[in]   ADC_CHx ADCͨ���ţ�   ֵ��ADC_CH0~ADC_CH15
 * @param[in]   times  ƽ������        
 */
u16 Get_Adc_Average(u8 ADC_CHx,u8 times)
{
	u32 temp_val=0;
	u8 t;
	for(t=0;t<times;t++)
	{
		temp_val+=Get_Adc(ADC_CHx);
		//SYSTICK_DelayMs(5);	 
	}
	return temp_val/times;
} 


