#include <rthw.h>
#include <rtthread.h>
#ifdef USER_USING_MOTORLOWLEVEL 
#ifdef USER_USING_XADC
#include <rtdevice.h>
#include "xadc_drv.h"




struct hw_adc_device adc_hw_device1;
ADC_HandleTypeDef adc_handle;
rt_adc_t adc_device1;


struct hw_adc_device
{
	ADC_HandleTypeDef adchandle;

};

void adc_intr(void)
{
	static unsigned int i = 40;
	adc_handle.INTC_Instance->ipisr |= EOSINTR;
	i--;
	if(i == 0)
	{
		i = 50;
		
		rt_kprintf("in the adc_intr\r\n")
	}
}

static rt_err_t adc_configure(struct rt_adc_device *adcdev, struct adc_configure *cfg)
{
	struct hw_adc_device *pdev = adcdev->parent.user_data;
	
	rt_kprintf("adc init complete\r\n");
	
    return RT_EOK;
}
static rt_err_t adc_control(struct rt_adc_device *adcdev, int cmd, void *arg)
{
    struct hw_adc_device *pdev;

    RT_ASSERT(adcdev != RT_NULL);

    pdev = adcdev->parent.user_data;

    switch (cmd)
    {
	case CMD_INTDISABLE:
		pdev->adchandle.INTC_Instance->gier = ~GIEINTR;

		break;
	case CMD_INTENABLE:

		pdev->adchandle.INTC_Instance->ipier |= EOSINTR;
		pdev->adchandle.INTC_Instance->gier = GIEINTR;
		rt_hw_interrupt_clear(pdev->adchandle.irq_nr);
		rt_hw_interrupt_install(pdev->adchandle.irq_nr,adc_intr,(void *)0, "adc_intr");
		
		//arm_gic_set_cpu(0, pdev->adchandle.irq_nr, 1 << rt_cpu_get_smp_id());
		rt_hw_interrupt_umask(pdev->adchandle.irq_nr);
		rt_kprintf("ipier = %x\r\ngier = %x\r\n",pdev->adchandle.INTC_Instance->ipier,pdev->adchandle.INTC_Instance->gier);

		break;
	default: 
			break;
    }

    return RT_EOK;
}

static QIEMW_ADC_HandleTypeDef adc_getValue(struct rt_adc_device *adcdev)
{
    struct hw_adc_device *pdev;
	QIEMW_ADC_HandleTypeDef adcvalue;

    RT_ASSERT(adcdev != RT_NULL);

    pdev = adcdev->parent.user_data;

	adcvalue.PhaseA.qI1_value = pdev->adchandle.Hard_Instance->vauxpn0;
	rt_kprintf("aux0  = %x\r\n",adcvalue.PhaseA.qI1_value>>4);
	return adcvalue;


}


static const struct rt_adc_ops _adc_ops =
{
    adc_configure,
    adc_control,
    adc_getValue,
};

void ADC_MSP_Init(ADC_HandleTypeDef *adc)
{
}




int adc_hw_init(void)
{

	struct adc_configure adc_config = RT_ADC_CONFIG_DEFAULT;
	adc_device1.config = adc_config;
	adc_device1.ops = &_adc_ops;
	
	adc_handle.Local_Instance = ADC_LOCAL_BASEADDR;
	adc_handle.INTC_Instance = ADC_INTC_BASEADDR;
	adc_handle.Hard_Instance = ADC_HARD_BASEADDR;
	adc_handle.irq_nr = CPU1_IRQ_ID;

	adc_hw_device1.adchandle= adc_handle;

	rt_hw_adc_register(&adc_device1, "adc1",
                          RT_DEVICE_FLAG_RDONLY,
                          &adc_hw_device1);

	return 0;

}

INIT_BOARD_EXPORT(adc_hw_init);

#endif
#endif
/*
int pwm_config_init(void)
{
	rt_device_t device;

	rt_kprintf("pwm init\r\n");
	device = rt_device_find("pwm1");
	if(device == NULL) printf("device not found \r\n");
	rt_device_open(device,NULL);
	rt_device_init(device);
	rt_device_close(device);
	return 0;
}
INIT_DEVICE_EXPORT(pwm_config_init);
*/
