/*
 * VMM Bus Driver
 *
 * COPYRIGHT (C) 2015, Shanghai Real-Thread Technology Co., Ltd
 *      http://www.rt-thread.com
 *
 *  This file is part of RT-Thread (http://www.rt-thread.org)
 *
 *  All rights reserved.
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
 * 2015-01-07     Grissiom     add comment
 */

#include <rtthread.h>

#ifdef RT_USING_VBUS
#include <rtdevice.h>
#include <vbus.h>
#include <board.h>
#include "userconf.h"
#include "xscugic.h"





extern XScuGic ScuGic1_InstancePtr;

struct rt_vbus_ring rt_vbus_rings[2] SECTION("vbus_ring");

int rt_vbus_do_init(void)
{
    return rt_vbus_init(&rt_vbus_rings[0], &rt_vbus_rings[1]);
}
INIT_COMPONENT_EXPORT(rt_vbus_do_init);

static void vbus_sfi_handler(void *CallBackRef)
{
	
	rt_kprintf("in the vbus_sfi_handler\r\n");
	rt_vbus_isr(CPU1_VBUS_SFI_ID, CallBackRef);
}


int rt_vbus_hw_init(void)
{
	#if 0
	XScuGic_Connect(&ScuGic1_InstancePtr, CPU1_VBUS_SFI_ID,vbus_sfi_handler, &ScuGic1_InstancePtr);
	XScuGic_Enable(&ScuGic1_InstancePtr, CPU1_VBUS_SFI_ID);
	#endif
	rt_hw_interrupt_clear(CPU1_VBUS_SFI_ID);
	rt_hw_interrupt_install(CPU1_VBUS_SFI_ID,vbus_sfi_handler,(void *)0, "vbus_sfi");
	
	arm_gic_set_cpu(0, CPU1_VBUS_SFI_ID, 1 << rt_cpu_get_smp_id());
	rt_hw_interrupt_umask(CPU1_VBUS_SFI_ID);


	rt_kprintf("the CPU ID is %d\r\n", rt_cpu_get_smp_id());

    return 0;
}

int rt_vbus_hw_eoi(int irqnr, void *param)
{
    /* Nothing to do here as we cleared the interrupt in IRQHandler. */
	rt_kprintf(" in the rt_vbus_hw_eoi\r\n");
    return 0;
}

struct rt_vbus_dev rt_vbus_chn_devx[] = {
    {
        .req =
        {
            .prio = 30,
            .name = "vecho",
            .is_server = 1,
            .recv_wm.low = RT_VMM_RB_BLK_NR / 3,
            .recv_wm.high = RT_VMM_RB_BLK_NR * 2 / 3,
            .post_wm.low = RT_VMM_RB_BLK_NR / 3,
            .post_wm.high = RT_VMM_RB_BLK_NR * 2 / 3,
        }
    },
    {
        .req =
        {
            .name = RT_NULL,
        }
    },
};

#endif /* RT_USING_VBUS */

