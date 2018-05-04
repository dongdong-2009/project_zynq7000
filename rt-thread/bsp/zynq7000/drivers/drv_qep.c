/*************************************************************************/

#include <rtthread.h>

//#undef USER_USING_MOTORLOWLEVEL
#ifdef USER_USING_MOTORLOWLEVEL 

#include "drv_qep.h"

struct hw_qep_device
{
	Qep_HandleTypeDef qep;

};

static void qepEnable(Qep_HandleTypeDef *qep)
{
	while(qep_enable(qep) != MYIP_SUCCESS);
}

static void qepDisable(Qep_HandleTypeDef *qep)
{
	while(qep_disable(qep)!= MYIP_SUCCESS);

}


static void qepSetMod(Qep_HandleTypeDef *qep,unsigned int mod)
{
	while(qep_set_mode(qep,mod)!= MYIP_SUCCESS);

}

static void qepSetPeriod(Qep_HandleTypeDef *qep,unsigned int period)
{
	while(qep_set_period(qep,period)!= MYIP_SUCCESS);

}


static rt_err_t qep_configure(struct rt_qep_device *qepdev, struct qep_configure *cfg)
{
	uint32_t mr;
	struct hw_qep_device *pdev = qepdev->parent.user_data;
	
	pdev->qep.state = MYIP_STATE_RESET;
	pdev->qep.init.mod= cfg->mod;
	pdev->qep.init.period= cfg->period;
	//rt_kprintf("addr = %x\r\n",&pdev->qep);
	QEP_Init(&pdev->qep);
	rt_kprintf("*****************qep init*****************\r\n");
	rt_kprintf("mod=%d,period = %d\r\n",cfg->mod,cfg->period);
	rt_kprintf("*****************end*****************\r\n");
    return RT_EOK;
}
static rt_err_t qep_control(struct rt_qep_device *qepdev, int cmd, void *arg)
{
    struct hw_qep_device *pdev;
	unsigned int *temp;

    RT_ASSERT(qepdev != RT_NULL);

    pdev = qepdev->parent.user_data;

    switch (cmd)
    {
    case CMD_QEPEN:
		qepEnable(&pdev->qep);
        break;

    case CMD_QEPDISABLE:
		qepDisable(&pdev->qep);
        break;
		
	case CMD_QEPSETMOD:
		temp = arg;
		qepSetMod(&pdev->qep,*temp);
		break;

	case CMD_QEPSETPERIOD:
		temp =arg;
		qepSetPeriod(&pdev->qep,*temp);
		break;
	default: 
			break;
    }

    return RT_EOK;
}


Qep_ValueTypeDef qep_getvalue(struct rt_qep_device *qepdev)
{
    struct hw_qep_device *pdev;
	Qep_ValueTypeDef data;
	
    RT_ASSERT(qepdev != RT_NULL);
    pdev = qepdev->parent.user_data;
	data.cnt = qep_read_cnt(&pdev->qep);
	data.turn = qep_read_turn(&pdev->qep);
	
	return data;
	
}

static const struct rt_qep_ops _qep_ops =
{
    qep_configure,
    qep_control,
    qep_getvalue,
};

void QEP_MSP_Init(Qep_HandleTypeDef *qep)
{
}


struct hw_qep_device qep_hw_device1;
Qep_HandleTypeDef qep_handle;
rt_qep_t qep_device1;




int qep_hw_init(void)
{

	struct qep_configure qep_config = RT_QEP_CONFIG_DEFAULT;
	qep_device1.config = qep_config;
	qep_device1.ops = &_qep_ops;
	
	qep_handle.Instance = MYQEP_BASEADDR;
	qep_handle.state = MYIP_STATE_RESET;

	qep_hw_device1.qep = qep_handle;

	rt_hw_qep_register(&qep_device1, "qep1",
                          NULL,
                          &qep_hw_device1);

	return 0;

}
INIT_BOARD_EXPORT(qep_hw_init);


int qep_config_init(void)
{
	rt_device_t device;

	device = rt_device_find("qep1");
	if(device == NULL) printf("device not found \r\n");
	rt_device_open(device,NULL);
	rt_device_init(device);
	rt_device_close(device);
	return 0;
}
INIT_DEVICE_EXPORT(qep_config_init);


#endif

