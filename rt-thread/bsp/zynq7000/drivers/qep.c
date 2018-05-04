
#include <rthw.h>
#include <rtthread.h>
#ifdef QEP_COMPONENT
#include <rtdevice.h>
#include "drv_qep.h"


static rt_err_t rt_qep_init(struct rt_device *dev)
{
    rt_err_t result = RT_EOK;
    struct rt_qep_device *qepdev;

    RT_ASSERT(dev != RT_NULL);
    qepdev = (struct rt_qep_device *)dev;

    /* apply configuration */
    if (qepdev->ops->configure)
        result = qepdev->ops->configure(qepdev, &qepdev->config);
	//rt_kprintf("qep init\r\n");
    return result;
}

static rt_err_t rt_qep_open(struct rt_device *dev, rt_uint16_t oflag)
{
    return RT_EOK;
}

static rt_err_t rt_qep_close(struct rt_device *dev)
{

    return RT_EOK;
}
static rt_err_t rt_qep_control(struct rt_device *dev,
                                  rt_uint8_t        cmd,
                                  void             *args)
{
    struct rt_qep_device *qepdev;

    RT_ASSERT(dev != RT_NULL);
    qepdev = (struct rt_qep_device *)dev;

    /* control device */
    qepdev->ops->control(qepdev, cmd, args);

    return RT_EOK;
}
static rt_size_t rt_qep_read(struct rt_device *dev,
                                rt_off_t          pos,
                                void             *buffer,
                                rt_size_t         size)
{
	struct rt_qep_device *qepdev;
	Qep_ValueTypeDef *pqepvalue,qepvalue;

	RT_ASSERT(dev != RT_NULL);
	qepdev = (struct rt_qep_device *)dev;

	RT_ASSERT(buffer != RT_NULL);
	pqepvalue = (Qep_HandleTypeDef *)buffer;
	
	qepvalue = qepdev->ops->getQepValue(qepdev);
	
	memcpy(pqepvalue,&qepvalue,sizeof(Qep_ValueTypeDef));
	
	return 1;
}


rt_err_t rt_hw_qep_register(struct rt_qep_device *qep,
                               const char              *name,
                               rt_uint32_t              flag,
                               void                    *data)
{
    struct rt_device *device;
    RT_ASSERT(qep != RT_NULL);

    device = &(qep->parent);

    device->type        = RT_Device_Class_Miscellaneous;
    device->rx_indicate = RT_NULL;
    device->tx_complete = RT_NULL;

    device->init        = rt_qep_init;
    device->open        = rt_qep_open;
    device->close       = rt_qep_close;
    device->control     = rt_qep_control;
	device->read        = rt_qep_read;
    device->user_data   = data;

    /* register a character device */
    return rt_device_register(device, name, flag);
}
#endif

