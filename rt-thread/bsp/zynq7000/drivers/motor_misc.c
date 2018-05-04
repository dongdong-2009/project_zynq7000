
#include <rthw.h>
#include <rtthread.h>
#ifdef MOTOR_MISC_COMPONENT
#include <rtdevice.h>
#include "motor_misc.h"


static rt_err_t rt_motor_misc_init(struct rt_device *dev)
{
    rt_err_t result = RT_EOK;
    struct rt_motor_misc_device *motor_miscdev;

    RT_ASSERT(dev != RT_NULL);
    motor_miscdev = (struct rt_motor_misc_device *)dev;

    /* apply configuration */
    if (motor_miscdev->ops->configure)
        result = motor_miscdev->ops->configure(motor_miscdev, &motor_miscdev->config);
    return result;
}

static rt_err_t rt_motor_misc_open(struct rt_device *dev, rt_uint16_t oflag)
{
    rt_err_t result = RT_EOK;
    struct rt_motor_misc_device *motor_miscdev;

    RT_ASSERT(dev != RT_NULL);
    motor_miscdev = (struct rt_motor_misc_device *)dev;
	//result = motor_miscdev->ops->control(motor_miscdev,CMD_INTENABLE,0);
	
	return result;
}

static rt_err_t rt_motor_misc_close(struct rt_device *dev)
{
    rt_err_t result = RT_EOK;

    return result;
}
static rt_err_t rt_motor_misc_control(struct rt_device *dev,
                                  rt_uint8_t        cmd,
                                  void             *args)
{
    struct rt_motor_misc_device *motor_miscdev;

    RT_ASSERT(dev != RT_NULL);
    motor_miscdev = (struct rt_motor_misc_device *)dev;

    /* control device */
    motor_miscdev->ops->control(motor_miscdev, cmd, args);

    return RT_EOK;
}

static rt_size_t rt_motor_misc_read(struct rt_device *dev,
                                rt_off_t          pos,
                                void             *buffer,
                                rt_size_t         size)

{
    struct rt_motor_misc_device *motor_miscdev;
	unsigned long *pmotor_miscvalue,motor_miscvalue;

    RT_ASSERT(dev != RT_NULL);
    motor_miscdev = (struct rt_motor_misc_device *)dev;

    RT_ASSERT(buffer != RT_NULL);
    pmotor_miscvalue = (unsigned long *)buffer;
	
	motor_miscvalue = motor_miscdev->ops->getIntrState(motor_miscdev);

	*pmotor_miscvalue = motor_miscvalue;
	
    return 1;
}

rt_err_t rt_hw_motor_misc_register(struct rt_motor_misc_device *motor_miscdev,
                               const char              *name,
                               rt_uint32_t              flag,
                               void                    *data)
{
    struct rt_device *device;
    RT_ASSERT(motor_miscdev != RT_NULL);

    device = &(motor_miscdev->parent);

    device->type        = RT_Device_Class_Miscellaneous;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;

    device->init        = rt_motor_misc_init;
    device->open        = rt_motor_misc_open;
    device->close       = rt_motor_misc_close;
    device->control     = rt_motor_misc_control;
    device->read        = rt_motor_misc_read;
    device->user_data   = data;

    /* register a character device */
    return rt_device_register(device, name, flag);
}
#endif


