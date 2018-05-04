/*
 * File      : UserGUI.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2015, RT-Thread Development Team
 *
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License along
 *  with this program; if not, write to the Free Software Foundation, Inc.,
 *  51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
 *
 * Change Logs:
 * Date           Author       Notes
 * 2015-12-04     long.he      the first version
 */

#include <rtthread.h>
#ifdef RT_USING_STEMWIN
#include "WM.h"
#include <components.h>
#include "GUI.h"
#include "stm32f7xx_hal.h"

extern LTDC_HandleTypeDef                   hltdc;  
void LTDC_IRQHandler()
{
	rt_interrupt_enter();
	HAL_LTDC_IRQHandler(&hltdc);
	rt_interrupt_leave();
}

/* ��ʱ��1��ʱ���� */
static void timeout1(void* parameter)
{
	//rt_kprintf("s1\r\n");
	//k_TouchUpdate();
	//rt_kprintf("GPIOH10 = %d  , GPIOH11= %d\r\n", HAL_GPIO_ReadPin(GPIOH, GPIO_PIN_10),HAL_GPIO_ReadPin(GPIOH, GPIO_PIN_11));
}


void rt_userGUI_entry(void *parameter)
{
	WM_HWIN hwin;
	
	static rt_timer_t timer1;
	timer1 = rt_timer_create("timer1", /* ��ʱ�������� timer1 */
	timeout1, /* ��ʱʱ�ص��Ĵ����� */
	RT_NULL, /* ��ʱ��������ڲ��� */
	100, /* ��ʱ���ȣ���OS TickΪ��λ����10��OS Tick */
	RT_TIMER_FLAG_PERIODIC); /* �����Զ�ʱ�� */
	/* ������ʱ�� */
	if (timer1 != RT_NULL) rt_timer_start(timer1);
	
	__HAL_RCC_CRC_CLK_ENABLE(); /* Enable the CRC Module */
	GUI_Init();
	WM_MULTIBUF_Enable(1);
  	GUI_SetLayerVisEx (1, 0);
  	GUI_SelectLayer(0);
  
 	GUI_SetBkColor(GUI_WHITE);
  	GUI_Clear();  

   /* Set General Graphical proprieties */
  	k_SetGuiProfile();
	k_StartUp();
	GUI_X_Delay(10);
	GUI_Clear(); 
	
	DlgTask();
	#if 0
	hwin = CreateFramewin();
	while(1)
		{
			GUI_Exec();
			GUI_X_Delay(1);
		}
	#endif
}


int userGUI_hw_init(void)
{
	//BSP_TS_Init(480,320);
	
	return 0;
}
INIT_BOARD_EXPORT(userGUI_hw_init);



int rt_userGUI_init()
{
    rt_thread_t tid;
	
	tid = rt_thread_create("userGUI",
                           rt_userGUI_entry, RT_NULL,
                           2048, RT_THREAD_PRIORITY_MAX-2, 20);
    if (tid != RT_NULL) rt_thread_startup(tid);

    return 0;
}
INIT_APP_EXPORT(rt_userGUI_init);
#endif
