
#include <rthw.h>
#include <rtthread.h>
#ifdef PWM_COMPONENT
#include <rtdevice.h>
#include "drv_pwm.h"


static rt_err_t rt_pwm_init(struct rt_device *dev)
{
    rt_err_t result = RT_EOK;
    struct rt_pwm_device *pwmdev;

    RT_ASSERT(dev != RT_NULL);
    pwmdev = (struct rt_pwm_device *)dev;
	
    /* apply configuration */
    if (pwmdev->ops->configure)
        result = pwmdev->ops->configure(pwmdev, &pwmdev->config);
	rt_kprintf("%x\r\n", result);
    return result;
}

static rt_err_t rt_pwm_open(struct rt_device *dev, rt_uint16_t oflag)
{

	return RT_EOK;
}

static rt_err_t rt_pwm_close(struct rt_device *dev)
{

    return RT_EOK;
}
static rt_err_t rt_pwm_control(struct rt_device *dev,
                                  rt_uint8_t        cmd,
                                  void             *args)
{
    struct rt_pwm_device *pwmdev;

    RT_ASSERT(dev != RT_NULL);
    pwmdev = (struct rt_pwm_device *)dev;

    /* control device */
    pwmdev->ops->control(pwmdev, cmd, args);

    return RT_EOK;
}


rt_err_t rt_hw_pwm_register(struct rt_pwm_device *pwm,
                               const char              *name,
                               rt_uint32_t              flag,
                               void                    *data)
{
    struct rt_device *device;
    RT_ASSERT(pwm != RT_NULL);

    device = &(pwm->parent);

    device->type        = RT_Device_Class_Miscellaneous;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;

    device->init        = rt_pwm_init;
    device->open        = rt_pwm_open;
    device->close       = rt_pwm_close;
    device->control     = rt_pwm_control;
    device->user_data   = data;

    /* register a character device */
    return rt_device_register(device, name, flag);
}
#endif
