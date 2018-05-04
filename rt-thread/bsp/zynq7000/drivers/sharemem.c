#include <rthw.h>
#include <rtthread.h>
#ifdef MOTOR_MISC_COMPONENT
#include <rtdevice.h>
#include "sharemem.h"


static rt_err_t rt_sharemem_init(struct rt_device *dev)
{
    rt_err_t result = RT_EOK;
    struct rt_sharemem_device *sharememdev;

    RT_ASSERT(dev != RT_NULL);
    sharememdev = (struct rt_sharemem_device *)dev;

    /* apply configuration */
    if (sharememdev->ops->configure)
        result = sharememdev->ops->configure(sharememdev, &sharememdev->config);
    return result;
}

static rt_err_t rt_sharemem_open(struct rt_device *dev, rt_uint16_t oflag)
{
    rt_err_t result = RT_EOK;
    struct rt_sharemem_device *sharememdev;

    RT_ASSERT(dev != RT_NULL);
    sharememdev = (struct rt_sharemem_device *)dev;
	//result = sharememdev->ops->control(sharememdev,CMD_INTENABLE,0);
	
	return result;
}

static rt_err_t rt_sharemem_close(struct rt_device *dev)
{
    rt_err_t result = RT_EOK;

    return result;
}


static rt_size_t rt_sharemem_read(struct rt_device *dev,
                                rt_off_t          pos,
                                void             *buffer,
                                rt_size_t         size)
{
    rt_err_t result = RT_EOK;
	struct rt_sharemem_device *sharememdev;

    RT_ASSERT(dev != RT_NULL);
    sharememdev = (struct rt_sharemem_device *)dev;

    RT_ASSERT(buffer != RT_NULL);
	
	result = sharememdev->ops->readmem(sharememdev,buffer,size);
	
    return result;


}


static rt_size_t rt_sharemem_write(struct rt_device *dev,
                                rt_off_t          pos,
                                void             *buffer,
                                rt_size_t         size)

{
    rt_err_t result = RT_EOK;
	struct rt_sharemem_device *sharememdev;

    RT_ASSERT(dev != RT_NULL);
    sharememdev = (struct rt_sharemem_device *)dev;

    RT_ASSERT(buffer != RT_NULL);
	
	result = sharememdev->ops->writemem(sharememdev,buffer,size);
	
    return result;
}

rt_err_t rt_hw_sharemem_register(struct rt_sharemem_device *sharememdev,
                               const char              *name,
                               rt_uint32_t              flag,
                               void                    *data)
{
    struct rt_device *device;
    RT_ASSERT(sharememdev != RT_NULL);

    device = &(sharememdev->parent);

    device->type        = RT_Device_Class_Miscellaneous;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;

    device->init        = rt_sharemem_init;
    device->open        = rt_sharemem_open;
    device->close       = rt_sharemem_close;
    device->write        = rt_sharemem_write;
	device->read        = rt_sharemem_read;
    device->user_data   = data;

    /* register a character device */
    return rt_device_register(device, name, flag);
}
#endif

