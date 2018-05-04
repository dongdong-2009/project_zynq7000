/*
 * COPYRIGHT (C) 2013-2014, Shanghai Real-Thread Technology Co., Ltd
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
 */

#include <rthw.h>
#include <rtthread.h>

#include <board.h>

extern int rt_application_init(void);
void enable_fpu()
{
	/*Set bits [11:10] of the NSACR for access to CP10 and CP11 from both Secure and
	Non-secure states:*/
	asm volatile ("MRC p15, 0, r0, c1, c1, 2\n\t");
	asm volatile("ORR r0, r0, #3<<10\n\t");
	asm volatile("MCR p15, 0, r0, c1, c1, 2\n");

	/*Set the CPACR for access to CP10 and CP11:*/
	asm volatile("LDR r0, =(0xF << 20)\n");
	asm volatile("MCR p15, 0, r0, c1, c0, 2\n");
	
	/*Set the FPEXC EN bit to enable the FPU:*/
	asm volatile("MOV r3, #0x40000000\n");
	asm volatile("VMSR FPEXC, r3\n");
}

/**
 * This function will startup RT-Thread RTOS.
 */
void rtthread_startup(void)
{
    rt_hw_mmu_init();

    /* initialzie hardware interrupt */
    rt_hw_interrupt_init();

	enable_fpu();

    /* initialize board */
    rt_hw_board_init();

    /* show RT-Thread version */
    rt_show_version();

    /* initialize memory system */
#ifdef RT_USING_HEAP
    rt_system_heap_init(HEAP_BEGIN, HEAP_END);
#endif

    /* initialize scheduler system */
    rt_system_scheduler_init();

    /* initialize system timer */
    rt_system_timer_init();

    /* initialize soft timer thread */
    rt_system_timer_thread_init();

    /* initialize application */
    rt_application_init();

    /* initialize idle thread */
    rt_thread_idle_init();

    /* start scheduler */
    rt_system_scheduler_start();

    /* never reach here */
    return ;
}

int main(void)
{
    /* disable interrupt first */
    rt_hw_interrupt_disable();

    /* invoke rtthread_startup */
    rtthread_startup();

    return 0;
}

