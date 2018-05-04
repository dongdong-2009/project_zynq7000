/*
 * File      : cpu.c
 * This file is part of RT-Thread RTOS
 * COPYRIGHT (C) 2013, RT-Thread Develop Team
 *
 * The license and distribution terms for this file may be
 * found in the file LICENSE in this distribution or at
 * http://www.rt-thread.org/license/LICENSE
 *
 * Change Logs:
 * Date           Author       Notes
 * 2013-07-20     Bernard      first version
 */

#include <rthw.h>
#include <rtthread.h>
#include "zynq7000.h"
#include "drv_pwm.h"
#ifdef USER_USING_XADC
#include "xadc_drv.h"
#endif
#include "myqep.h"
#include "qep.h"
#include "drv_qep.h"
#include "motor_misc.h"
#ifdef USER_USING_AD7606
#include "AD7606_drv.h"
#endif
/**
 * reset cpu by dog's time-out
 *
 */
void rt_hw_cpu_reset()
{
    while (1);  /* loop forever and wait for reset to happen */

    /* NEVER REACHED */
}

/**
 *  shutdown CPU
 *
 */
void rt_hw_cpu_shutdown()
{
    rt_uint32_t level;
	
	rt_device_t device;
	#if 1
	device = rt_device_find("motor_misc1");
	if(device != NULL)
	{
		
		rt_kprintf("misc shut %d\r\n",device);
		rt_device_control(device,CMD_MISC_CLR_RLY,NULL);
		rt_device_control(device,CMD_MISC_INTDISABLE,NULL);
		rt_device_close(device);
	}
	
	device = rt_device_find("pwm1");
	if(device != NULL)
	{
		rt_kprintf("pwm1 shut\n");
		rt_device_control(device,CMD_PWMDISABLE,NULL);
		rt_device_close(device);
	}
	
	device = rt_device_find("adc1");
	if(device != NULL)
	{
		
		rt_kprintf("adc1 shut\n");
		rt_device_close(device);
	}
	
	device = rt_device_find("qep1");
	if(device != NULL)
	{
		rt_kprintf("qep1 shut\n");
		rt_device_control(device,CMD_QEPDISABLE,NULL);
		rt_device_close(device);
	}
	#endif
    rt_kprintf("shutdown...\n");
	
	
    level = rt_hw_interrupt_disable();
	
    while (level)
    {
        RT_ASSERT(0);
    }
}

