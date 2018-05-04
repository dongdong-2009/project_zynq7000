#include <rthw.h>
#include <rtthread.h>
#ifdef USER_MOTOR_MISC
#include <rtdevice.h>
#include "drv_motor_misc.h"
#include "drv_pwm.h"
#include "xadc_drv.h"
#include "myqep.h"
#include "qep.h"
#include "drv_qep.h"
#include "motor_misc.h"



struct hw_motor_misc_device motor_misc_hw_device1;
Misc_HandleTypeDef motor_misc_handle;
rt_motor_misc_t motor_misc_device1;


struct hw_motor_misc_device
{
	Misc_HandleTypeDef motor_mischandle;

};
static void motor_misc_intr(int irqno, void *param)
{
	
    struct hw_motor_misc_device *pdev = (struct hw_motor_misc_device *)param;
	unsigned long motor_miscvalue;
	rt_device_t device;
	
	device = rt_device_find("pwm1");
	rt_device_control(device,CMD_PWMDISABLE,NULL);
	rt_device_close(device);
	
	device = rt_device_find("adc1");
	rt_device_close(device);
	
	device = rt_device_find("qep1");
	rt_device_control(device,CMD_QEPDISABLE,NULL);
	rt_device_close(device);
	
	motor_miscvalue = pdev->motor_mischandle.Local_Instance->intr_state_reg;
	if((motor_miscvalue & TZ1_FAULT) == TZ1_FAULT)
	{
		rt_kprintf("TZ1 fault\r\n");
	}
	if((motor_miscvalue & TZ2_FAULT) == TZ2_FAULT)
	{
		rt_kprintf("TZ2 fault\r\n");
	}
	if((motor_miscvalue & VOE_FAULT) == VOE_FAULT)
	{
		rt_kprintf("VOE fault\r\n");
	}
	if((motor_miscvalue & SC_FAULT) == SC_FAULT)
	{
		rt_kprintf("SC fault\r\n");
	}
	if((motor_miscvalue & EA_FAULT) == EA_FAULT)
	{
		rt_kprintf("EA fault\r\n");
	}
	if((motor_miscvalue & EB_FAULT) == EB_FAULT)
	{
		rt_kprintf("EB fault\r\n");
	}
	
	device = rt_device_find("motor_misc1");
	rt_device_control(device,CMD_MISC_CLR_RLY,NULL);
	rt_device_control(device,CMD_MISC_INTDISABLE,NULL);
	rt_device_close(device);
	
    rt_kprintf("shutdown...\n");
    rt_hw_interrupt_disable();
	pdev->motor_mischandle.Local_Instance->intr_ctrl_reg.clr_flag = 1;
	while(1);
	pdev->motor_mischandle.Local_Instance->intr_ctrl_reg.clr_flag = 0;

}



static rt_err_t motor_misc_configure(struct rt_motor_misc_device *motor_miscdev, struct motor_misc_configure *cfg)
{
	struct hw_motor_misc_device *pdev;

	
    RT_ASSERT(motor_miscdev != RT_NULL);
	pdev = motor_miscdev->parent.user_data;

	
	pdev->motor_mischandle.Local_Instance->break_duty_reg = motor_miscdev->config.breakduty;
	pdev->motor_mischandle.Local_Instance->fan_duty_reg = motor_miscdev->config.fanduty;
	pdev->motor_mischandle.Local_Instance->intr_ctrl_reg.clr_flag = motor_miscdev->config.clrflag;
	pdev->motor_mischandle.Local_Instance->pwm_ctrl_reg.break_en = motor_miscdev->config.pwmen;
	pdev->motor_mischandle.Local_Instance->pwm_ctrl_reg.fan_en = motor_miscdev->config.fanen;
	
	rt_kprintf("motor_misc init complete\r\n");
	
    return RT_EOK;
}

static void motor_misc_delay_us(unsigned int us)
{
    volatile unsigned int len;
    for (; us > 0; us --)
        for (len = 0; len < 20; len++ );
}

static rt_err_t motor_misc_control(struct rt_motor_misc_device *motor_miscdev, int cmd, void *arg)
{
    struct hw_motor_misc_device *pdev;
	unsigned int *temp;
	unsigned long motor_miscvalue;

    RT_ASSERT(motor_miscdev != RT_NULL);

    pdev = motor_miscdev->parent.user_data;

    switch (cmd)
    {
	case CMD_MISC_INTDISABLE:
		//rt_hw_interrupt_mask(pdev->motor_mischandle.irq_nr);
		
		pdev->motor_mischandle.Local_Instance->intr_ctrl_reg.clr_flag = 1;

		break;
	case CMD_MISC_INTENABLE:
		rt_hw_interrupt_mask(pdev->motor_mischandle.irq_nr);
		pdev->motor_mischandle.Local_Instance->intr_ctrl_reg.clr_flag = 0;
		
		motor_miscvalue = pdev->motor_mischandle.Local_Instance->intr_state_reg;
		rt_kprintf("isrstate: %x\r\n",motor_miscvalue);
		rt_hw_interrupt_clear(pdev->motor_mischandle.irq_nr);
		rt_hw_interrupt_install(pdev->motor_mischandle.irq_nr,motor_misc_intr,pdev, "motor_misc_intr");
		
		arm_gic_set_cpu(0, pdev->motor_mischandle.irq_nr, 1 << rt_cpu_get_smp_id());
		rt_hw_interrupt_umask(pdev->motor_mischandle.irq_nr);
		

		break;

	case CMD_MISC_SET_BREAK_DUTY:

		temp = arg;
		pdev->motor_mischandle.Local_Instance->break_duty_reg = *temp;

		break;

	case CMD_MISC_SET_FAN_DUTY: 
		temp = arg;
		pdev->motor_mischandle.Local_Instance->fan_duty_reg = *temp;
		break;

	case CMD_MISC_BREAKEN: 
		temp = arg;
		pdev->motor_mischandle.Local_Instance->pwm_ctrl_reg.break_en = *temp;
		break;

	case CMD_MISC_FANEN:
		temp = arg;
		pdev->motor_mischandle.Local_Instance->pwm_ctrl_reg.fan_en = *temp;
		break;

	case CMD_MISC_CLR_FLAG:
		pdev->motor_mischandle.Local_Instance->intr_ctrl_reg.clr_flag = 1;
		motor_misc_delay_us(1);
		pdev->motor_mischandle.Local_Instance->intr_ctrl_reg.clr_flag = 0;
		break;
	case CMD_MISC_SET_RLY:
		pdev->motor_mischandle.Local_Instance->pwm_ctrl_reg.RLY = 1;
		break;
	case CMD_MISC_CLR_RLY:
		pdev->motor_mischandle.Local_Instance->pwm_ctrl_reg.RLY = 0;
		break;
	default: 
			break;
    }

    return RT_EOK;
}

/*
**CODE = (VIN/5)*32768*(REF/2.5)=(VIN/5)*32768
* *IV,IW,IU,VUV,VVW = 2*VIN-3.3
**VDC,TEMP = VIN
*/


static unsigned long motor_misc_getState(struct rt_motor_misc_device *motor_miscdev)
{
    struct hw_motor_misc_device *pdev;
	unsigned long motor_miscvalue;


    RT_ASSERT(motor_miscdev != RT_NULL);

    pdev = motor_miscdev->parent.user_data;


	motor_miscvalue = pdev->motor_mischandle.Local_Instance->intr_state_reg;
	

	return motor_miscvalue;
}


static const struct rt_motor_misc_ops _motor_misc_ops =
{
    motor_misc_configure,
    motor_misc_control,
    motor_misc_getState,
};


int motor_misc_hw_init(void)
{

	struct motor_misc_configure motor_misc_config = RT_MISC_CONFIG_DEFAULT;
	motor_misc_device1.config = motor_misc_config;
	motor_misc_device1.ops = &_motor_misc_ops;
	
	motor_misc_handle.Local_Instance = MOTOR_MISC_LOCAL_BASEADDR;
	motor_misc_handle.irq_nr = CPU1_IRQF2P0_ID;

	motor_misc_hw_device1.motor_mischandle= motor_misc_handle;

	rt_hw_motor_misc_register(&motor_misc_device1, "motor_misc1",
                          RT_DEVICE_FLAG_RDONLY,
                          &motor_misc_hw_device1);

	return 0;

}

INIT_BOARD_EXPORT(motor_misc_hw_init);

#endif


