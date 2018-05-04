
#include <rthw.h>
#include <rtthread.h>
#ifdef ADC_COMPONENT
#include <rtdevice.h>
#include "adc.h"


static rt_err_t rt_adc_init(struct rt_device *dev)
{
    rt_err_t result = RT_EOK;
    struct rt_adc_device *adcdev;

    RT_ASSERT(dev != RT_NULL);
    adcdev = (struct rt_adc_device *)dev;

    /* apply configuration */
    if (adcdev->ops->configure)
        result = adcdev->ops->configure(adcdev, &adcdev->config);
	//rt_kprintf("%x\r\n", result);
    return result;
}

static rt_err_t rt_adc_open(struct rt_device *dev, rt_uint16_t oflag)
{
    rt_err_t result = RT_EOK;
	
	return result;
}

static rt_err_t rt_adc_close(struct rt_device *dev)
{
    rt_err_t result = RT_EOK;

    return result;
}
static rt_err_t rt_adc_control(struct rt_device *dev,
                                  rt_uint8_t        cmd,
                                  void             *args)
{
    struct rt_adc_device *adcdev;

    RT_ASSERT(dev != RT_NULL);
    adcdev = (struct rt_adc_device *)dev;

    /* control device */
    adcdev->ops->control(adcdev, cmd, args);

    return RT_EOK;
}

static rt_size_t rt_adc_read(struct rt_device *dev,
                                rt_off_t          pos,
                                void             *buffer,
                                rt_size_t         size)

{
    struct rt_adc_device *adcdev;
	QIEMW_ADC_HandleTypeDef *padcvalue,adcvalue;

    RT_ASSERT(dev != RT_NULL);
    adcdev = (struct rt_adc_device *)dev;

    RT_ASSERT(buffer != RT_NULL);
    padcvalue = (QIEMW_ADC_HandleTypeDef *)buffer;
	
	adcvalue = adcdev->ops->getAdcValue(adcdev);

	memcpy(padcvalue,&adcvalue,sizeof(QIEMW_ADC_HandleTypeDef));
	
    return 1;
}

rt_err_t rt_hw_adc_register(struct rt_adc_device *adcdev,
                               const char              *name,
                               rt_uint32_t              flag,
                               void                    *data)
{
    struct rt_device *device;
    RT_ASSERT(adcdev != RT_NULL);

    device = &(adcdev->parent);

    device->type        = RT_Device_Class_Miscellaneous;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;

    device->init        = rt_adc_init;
    device->open        = rt_adc_open;
    device->close       = rt_adc_close;
    device->control     = rt_adc_control;
    device->read        = rt_adc_read;
    device->user_data   = data;

    /* register a character device */
    return rt_device_register(device, name, flag);
}
#endif

