/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#ifndef sd
#define sd
#include "stm32f10x_it.h"
//#include "bsp_sdio_sdcard.h"
#include "bsp_usart1.h"
#include "bsp_usart2.h"
#include "stm32f10x_usart.h"
#include <stdio.h>
uint8_t ch;
char rx_buf[100];
uint8_t rx_len = 0;


/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */


/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */


/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */


/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */



/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */


/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */


/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/
void USART1_IRQHandler(void)
{
#if 0
    bsp_USART1_IRQHandler();
#else
    

    if(USART_GetITStatus(USART1, USART_IT_RXNE) != RESET)
    {
        //ch = USART1->DR;
        ch = USART_ReceiveData(USART1);
//		if (ch == '\r') // ????????
//    {
//      //rx_buf[rx_len] = '\0'; // ?????????????????
//      //printf("Received string: %s\n", rx_buf); // ?????????
//      rx_len = 0; // ?????????
//    }
//    else
//    {
//      rx_buf[rx_len++] = ch; // ????????????????
//			
//    }
			
			
        printf( "%c", ch );    //�����ܵ�������ֱ�ӷ��ش�ӡ
    }
#endif

}
#endif


/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */
/*
 * ��������SDIO_IRQHandler
 * ����  ����SDIO_ITConfig(���������������sdio�ж�	��
 *		     ���ݴ������ʱ�����ж�
 * ����  ����
 * ���  ����
 */



/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
