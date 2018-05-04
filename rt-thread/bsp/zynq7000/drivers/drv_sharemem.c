#include <rthw.h>
#include <rtthread.h>
#ifdef USER_MOTOR_MISC
#include <rtdevice.h>
#include "drv_sharemem.h"
#include "drv_pwm.h"
#include "xadc_drv.h"
#include "myqep.h"
#include "qep.h"
#include "drv_qep.h"
#include "sharemem.h"



struct hw_sharemem_device sharemem_hw_device1;
ShareMem_HandleTypeDef sharemem_handle;
rt_sharemem_t sharemem_device1;


struct hw_sharemem_device
{
	ShareMem_HandleTypeDef sharememhandle;

};


static rt_err_t sharemem_configure(struct rt_sharemem_device *sharememdev, struct sharemem_configure *cfg)
{
	struct hw_sharemem_device *pdev;

	
    RT_ASSERT(sharememdev != RT_NULL);
	pdev = sharememdev->parent.user_data;
	
	pdev->sharememhandle.Local_Instance->readposition = sharememdev->config.readposition;
	pdev->sharememhandle.Local_Instance->writeposition = sharememdev->config.writeposition;
	pdev->sharememhandle.Local_Instance->maxlength = sharememdev->config.maxlength;

	pdev->sharememhandle.Local_Instance->readbuff_readposition = sharememdev->config.readbuff_readposition;
	//pdev->sharememhandle.Local_Instance->readbuff_writeposition = sharememdev->config.readbuff_writeposition;
	pdev->sharememhandle.Local_Instance->readbuff_maxlength = sharememdev->config.readbuff_maxlength;
	rt_kprintf("sharemem init complete\r\n");
	
    return RT_EOK;
}

static unsigned long sharemem_readmem(struct rt_sharemem_device *sharememdev, char * buf,int size)
{

    struct hw_sharemem_device *pdev;
	int readposition;
	int writeposition;
	int maxlength;
	unsigned int baseaddr;
	unsigned int writebuff_size;
	
	unsigned char *tmp;
	unsigned long readsize = 0; 

    RT_ASSERT(sharememdev != RT_NULL);

    pdev = sharememdev->parent.user_data;

	readposition = pdev->sharememhandle.Local_Instance->readbuff_readposition;
	writeposition = pdev->sharememhandle.Local_Instance->readbuff_writeposition;
	maxlength = pdev->sharememhandle.Local_Instance->readbuff_maxlength;
	writebuff_size = pdev->sharememhandle.Local_Instance->maxlength;

	
	baseaddr = pdev->sharememhandle.Local_Instance;
	baseaddr = sizeof(sharememhead_TyepDef) + baseaddr;
	baseaddr = baseaddr + writebuff_size;
	tmp = baseaddr;
	if(readposition <= writeposition)
	{
		while(readposition < writeposition)
		{
			*(buf++) = *(tmp + readposition);
			//rt_kprintf("1:%x:%x\r\n",tmp + readposition,*(tmp + readposition));
			readposition++;
		}
		readsize = readposition - pdev->sharememhandle.Local_Instance->readbuff_readposition;
		pdev->sharememhandle.Local_Instance->readbuff_readposition = readposition;
	}
	else
	{
		while(readposition < maxlength)
		{
			*(buf++) = *(tmp + readposition);
			//rt_kprintf("2:%x:%x\r\n",tmp + readposition,*(tmp + readposition));
			readposition++;
		}
		readposition = 0;
		while(readposition < writeposition)
		{
			*(buf++) = *(tmp + readposition);
			//rt_kprintf("2:%x:%x\r\n",tmp + readposition,*(tmp + readposition));
			readposition++;
		}
		
		readsize = readposition + maxlength - pdev->sharememhandle.Local_Instance->readbuff_readposition;
		pdev->sharememhandle.Local_Instance->readbuff_readposition = readposition;
	}
	return readsize;



}


static unsigned long sharemem_writemem(struct rt_sharemem_device *sharememdev, char * data,int size)
{
    struct hw_sharemem_device *pdev;
	int readposition;
	int writeposition;
	int maxlength;
	char *p;
	unsigned int temp;
	int i,z;
	unsigned int head;

    RT_ASSERT(sharememdev != RT_NULL);

    pdev = sharememdev->parent.user_data;

	readposition = pdev->sharememhandle.Local_Instance->readposition;
	writeposition = pdev->sharememhandle.Local_Instance->writeposition;
	maxlength = pdev->sharememhandle.Local_Instance->maxlength;
	temp = pdev->sharememhandle.Local_Instance;
	temp += sizeof(sharememhead_TyepDef);
	temp += writeposition;
	p = temp;
	rt_kprintf("temp=%x\r\n",temp);
	

	rt_kprintf("base:%x,head:%x,point:%x,size:%x,writeposition:%x\r\n",pdev->sharememhandle.Local_Instance,sizeof(sharememhead_TyepDef),p,size,writeposition);
	z = 0;
	for(i = 0;i < size;i++)
	{
		head = pdev->sharememhandle.Local_Instance;
		head += sizeof(sharememhead_TyepDef);
		if((writeposition + i) >= maxlength )
		{
				temp = pdev->sharememhandle.Local_Instance;
				temp += sizeof(sharememhead_TyepDef);
				p = temp;
				*(p + z) = *(data + i); 
				rt_kprintf("1:%x:%d\r\n ",(p+z),*(p + i));
				z++;
		}
		else
		{
				*(p + i) = *(data + i); 
				int temp1,temp2;
				temp1 = p+i;
				temp2 = *(p+i);
				rt_kprintf("2:%x:%d\r\n ",temp1,temp2);
		}
	}
	if((writeposition + i) >= maxlength )
		{
			i = z;
			writeposition = 0;
		}
	pdev->sharememhandle.Local_Instance->writeposition = i + writeposition;

	return RT_EOK;
}


static const struct rt_sharemem_ops _sharemem_ops =
{
    sharemem_configure,
    sharemem_writemem,
    sharemem_readmem,
};


int sharemem_hw_init(void)
{

	
	struct sharemem_configure sharemem_config = RT_SHAREMEM_CONFIG_DEFAULT;
	sharemem_device1.config = sharemem_config;
	
	sharemem_device1.ops = &_sharemem_ops;
	
	sharemem_handle.Local_Instance = SHAREMEMHEAD_BASEADDR;
	//sharemem_handle.irq_nr = CPU1_IRQF2P0_ID;

	sharemem_hw_device1.sharememhandle= sharemem_handle;

	rt_hw_sharemem_register(&sharemem_device1, "sharemem1",
                          RT_DEVICE_FLAG_RDWR,
                          &sharemem_hw_device1);

	return 0;

}

INIT_BOARD_EXPORT(sharemem_hw_init);

#endif

