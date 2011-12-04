/**
  ******************************************************************************
  * @file    Project/STM32L1xx_StdPeriph_Template/stm32l1xx_it.c 
  * @author  MCD Application Team
  * @version V1.0.0
  * @date    31-December-2010
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
  * <h2><center>&copy; COPYRIGHT 2010 STMicroelectronics</center></h2>
  ******************************************************************************
  */ 

/* Includes ------------------------------------------------------------------*/
#include "stm32l1xx_it.h"

/** @addtogroup Template_Project
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
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
  TimingDelay_Decrement();
}

/******************************************************************************/
/*                 STM32L1xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32l1xx_md.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
 * @brief Handles the XMOS UART TX DMA interrupt request.
 * @param None
 * @return None
 */
void DMA1_Channel4_IRQHandler(void)
{

}

/**
 * @brief Handles the XMOS UART RX DMA interrupt request.
 * @param None
 * @return None
 */
void DMA1_Channel5_IRQHandler(void)
{
	uint8_t cmd_ack, opcode;
	if(DMA_GetITStatus(DMA1_IT_TC5))
	{
		// Coming from idle mode
		if(!uart_status.active)
		{
			uart_status.active = 1;
			uart_status.cmd_sent = 1;
			uart_status.master = 0;
			uart_handle_command(received_control_byte);
		}

		// Expecting ACK byte from XMOS
		else if(uart_status.active && uart_status.cmd_sent && uart_status.master && !uart_status.ack_sent)
		{
			uart_status.ack_sent = 1;
			cmd_ack = received_control_byte >> 7;
			opcode = (received_control_byte << 1) >> 1;		// Filter out CMD/ACK bit
			// Check message format
			if(!cmd_ack)	// Is a CMD
			{
				uart_status.error = 2;
				// TODO: Need error opcodes
			}
			else if(command != opcode)
			{
				uart_status.error = 3;
			}
			else
			{
				// TODO: Start data transmission
			}
		}

		// Receiving data after ACK, master mode
		else if(uart_status.active && uart_status.master && uart_status.cmd_sent && uart_status.ack_sent)
		{
			uart_handle_reply_data(opcode);
		}

		// Receiving data after ACK, slave mode
		else if(uart_status.active && !uart_status.master && uart_status.cmd_sent && uart_status.ack_sent)
		{
			// TODO : What is handled here vs uart_handle_command?
		}
	}
}
/**
  * @}
  */ 


/******************* (C) COPYRIGHT 2010 STMicroelectronics *****END OF FILE****/
