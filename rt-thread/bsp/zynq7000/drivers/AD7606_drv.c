#include <rthw.h>
#include <rtthread.h>
#ifdef USER_USING_MOTORLOWLEVEL 
#ifdef USER_USING_AD7606
#include <rtdevice.h>
#include "AD7606_drv.h"
#include "mypwm.h"
#include "myqep.h"
#include "drv_pwm.h"
#include "qep.h"
#ifdef USER_USING_MOTORFLOATLIB
#include "MC_Globals.h"
#include "modules/hal/hal_obj.h"
#include "modules/MotorCtrlApp/MotorCtrlApp.h"
#include "MC_encoder_param.h"
#include "modules/hal/hal.h"

#endif
//! \Add By Dl.K
#include "drv_pwm.h"
#include "myqep.h"
#include "qep.h"
#include "drv_qep.h"
#include "motor_misc.h"
#include "drv_motor_misc.h"

#include "CTRL_doCurrentCtrl_v1_0/src/xctrl_docurrentctrl.h"
#include "CTRL_doCurrentCtrl_v1_0/src/xctrl_usr_docurrentctrl.h"
#include "client.h"


CurrentCtrl_dout_type t;
CurrentCtrl_din_type in;

XCtrl_docurrentctrl InstancePtr;

struct hw_adc_device adc_hw_device1;
ADC_HandleTypeDef adc_handle;
rt_adc_t adc_device1;


struct hw_adc_device
{
	ADC_HandleTypeDef adchandle;

};
#if 0
struct spi_msg
{
	unsigned char head;
	unsigned short timer;
	unsigned int speed;
	short v1;
	short v2;
	short v3;
	short v4;
	short v5;
	short v6;
	short v7;
	short v8;
};
#endif
int speed;
unsigned int t_array[126];
int turn_array[126];
extern HAL_Obj gHal;
extern CTRL_Obj gCtrl;

int pwm0[260];
int pwm1[260];
int pwm2[260];
int point[260];
int angleout[260];
int angle[260];
int va[260];
int vb[260];
int spd[260];
unsigned int j=0;
extern CTRL_Handle gCtrlHandle;

static void motor_ctl(struct hw_adc_device *pdev)
{
	static unsigned int cnt_p = 0,cnt_n = 0;
	rt_device_t device_qep,device_sharemem;
	Qep_ValueTypeDef qep_data;
	device_qep = rt_device_find("qep1");
	//static struct spi_msg spi_msg;
	static unsigned int i = 0;
	
	if(gCtrl.state != 1)
	{
		j++;
	}
	if(device_qep != NULL)
	{
		rt_device_read(device_qep,0,&qep_data,0);
		cnt_p = cnt_n;
		cnt_n = qep_data.cnt;


		for(i = 0; i < 125; i++)
		{
			t_array[i] = t_array[i + 1];
			//turn_array[i] = turn_array[i + 1];
		}
		t_array[i] = qep_data.cnt;
		//turn_array[i] = qep_data.turn;
	}
	#if 1
	static HAL_AdcData_t sHal_AdcData;
	static HAL_PwmData_t sHal_PwmData;
	static HAL_QepData_t sHal_QepData;

	rt_device_t device_adc;
	
	QIEMW_ADC_HandleTypeDef adcvalue;
	device_adc = rt_device_find("adc1");
	rt_device_read (device_adc,
                          0,
                          &adcvalue,
                          0);

	adcvalue.PhaseA.qI_value = pdev->adchandle.Local_Instance->data1_reg;//IV
	adcvalue.PhaseB.qI_value = pdev->adchandle.Local_Instance->data2_reg;//IW
	adcvalue.PhaseC.qI_value = pdev->adchandle.Local_Instance->data3_reg;//IU
	adcvalue.BUS.qV_value = pdev->adchandle.Local_Instance->data4_reg;//VDC
	adcvalue.Temp.TEMP_value = pdev->adchandle.Local_Instance->data5_reg;//TEMP
	adcvalue.PhaseA.qV_value = pdev->adchandle.Local_Instance->data6_reg;//VUV
	adcvalue.PhaseB.qV_value = pdev->adchandle.Local_Instance->data7_reg;//VVW

	
	sHal_AdcData.I.value[0] = adcvalue.PhaseA.qI_value/3276.8-3.3;//IV  control board voltage
	sHal_AdcData.I.value[1] = adcvalue.PhaseB.qI_value/3276.8-3.3;//IW
	sHal_AdcData.I.value[2] = adcvalue.PhaseC.qI_value/3276.8-3.3;//IU
	sHal_AdcData.V.value[0] = adcvalue.PhaseA.qV_value;//VUV
	sHal_AdcData.V.value[1] = adcvalue.PhaseB.qV_value;//VVW
	//sHal_AdcData.V.value[2] = -adcvalue.PhaseA.qV_value - adcvalue.PhaseB.qV_value;
	sHal_AdcData.VdcBus = adcvalue.BUS.qV_value * 2.37 / 10000;//VDC

	rt_device_read(device_qep,0,&qep_data,0);
	sHal_QepData.qep_cnt = qep_data.cnt;
	sHal_QepData.turn_cnt = qep_data.turn;
	sHal_AdcData.I.value[0] = sHal_AdcData.I.value[0] * 8.77;//IV real current
	sHal_AdcData.I.value[1] = sHal_AdcData.I.value[1] * 8.77;//IW
	sHal_AdcData.I.value[2] = sHal_AdcData.I.value[2] * 8.77;//IU
	sHal_AdcData.VdcBus = sHal_AdcData.VdcBus * 195.5;//real bus voltage
	
	
	sHal_AdcData.I.value[0] = sHal_AdcData.I.value[0] - gHal.adcBias.I.value[0];//È¥Æ«ÖÃ
	sHal_AdcData.I.value[1] = sHal_AdcData.I.value[1] - gHal.adcBias.I.value[1];
	sHal_AdcData.I.value[2] = sHal_AdcData.I.value[2] - gHal.adcBias.I.value[2];
	
	#if 0 
	spi_msg.head = 0x5a;
	spi_msg.speed = 1;//qep_data.cnt;
	spi_msg.timer++;
	spi_msg.v1 = 2;//adcvalue.PhaseA.qI_value;
	spi_msg.v2 = 3;//adcvalue.PhaseB.qI_value;
	spi_msg.v3 = 4;//adcvalue.PhaseC.qI_value;
	spi_msg.v4 = 5;//adcvalue.BUS.qV_value;
	spi_msg.v5 = 6;//adcvalue.Temp.TEMP_value;
	spi_msg.v6 = 7;//adcvalue.PhaseA.qV_value;
	spi_msg.v7 = 8;//adcvalue.PhaseB.qV_value;
	spi_msg.v8 = 0;
	device_sharemem = rt_device_find("sharemem1");
	rt_device_open(device_sharemem,NULL);
	rt_device_write(device_sharemem,0,&spi_msg,sizeof(struct spi_msg));
	#endif

		#if 1
		d_monitor_type monitor;
		device_sharemem = rt_device_find("sharemem1");
		rt_device_open(device_sharemem,NULL);
		
		monitor.ia.f = sHal_AdcData.I.value[0];
		monitor.ib.f = sHal_AdcData.I.value[1];
		monitor.ic.f = sHal_AdcData.I.value[2];
		monitor.spd.f = 0;
		monitor.time.d++;
		monitor.check.d = monitor.ia.d + monitor.ib.d + monitor.ic.d + monitor.spd.d + monitor.time.d;
		
		rt_device_write(device_sharemem,0,&monitor,sizeof(d_monitor_type));
		
		#endif
	
	Motor_Ctrl_Run(&sHal_AdcData, &sHal_PwmData, &sHal_QepData);

	rt_device_t device_pwm;
	duty_HandleTypeDef dutyhandle;
	
	device_pwm = rt_device_find("pwm1");
	dutyhandle.pwm0_duty = sHal_PwmData.Tabc.value[0]*(float)TRIANGLETOP;
	dutyhandle.pwm1_duty = sHal_PwmData.Tabc.value[1]*(float)TRIANGLETOP;
	dutyhandle.pwm2_duty = sHal_PwmData.Tabc.value[2]*(float)TRIANGLETOP;
	#if 1
	static int xi = 0;
	xi++;
	
	static int count = 0;
	if(j <= 26000)
	{

		if(xi > 100)
		{

			for(i = 0; i < 259; i++)
			{
				pwm0[i] = pwm0[i + 1];
				pwm1[i] = pwm1[i + 1];
				pwm2[i] = pwm2[i + 1];
				point[i] = point[i + 1];
				angleout[i] = angleout[i + 1];
				angle[i] = angle[i + 1];
				va[i] = va[i + 1];
				vb[i] = vb[i + 1];
				spd[i] = spd[i + 1];
			}
			//pwm0[i] = dutyhandle.pwm0_duty;
			pwm0[i] = gCtrl.Vdq_out.value[0] * 1000;
			pwm1[i] = t.ta.f;
			//pwm2[i] = dutyhandle.pwm2_duty;
			//pwm2[i] = sHal_QepData.qep_cnt;
			pwm2[i] = gCtrl.Vdq_out.value[1] * 1000;
			//point[i] = gCtrl.rampgen.Freq * (float)10000 * (float)1000;
			//point[i] = gCtrl.Speed_handle->ElecSpeed * (float)10000;
			point[i] = t.out_ud.f * 1000;
			//angleout[i] = gCtrl.rampgen.Out * (float)10000 * (float)10000 * (float)10;
			angleout[i] = t.out_uq.f * 1000;
			//angle[i] = gCtrl.rampgen.Angle * (float)10000 * (float)10000 * (float)10;
			angle[i] = sHal_AdcData.I.value[0]*1000;
			//va[i] = gCtrl.Vab_out.value[0] * (float)10000 * (float)10000 * (float)10;
			va[i] = sHal_AdcData.I.value[1]*1000;
			//vb[i] = gCtrl.Vab_out.value[1] * (float)10000 * (float)10000 * (float)10;
			vb[i] = sHal_AdcData.I.value[2]*1000;
			spd[i] = gCtrl.Speed.spd_test * 10000;
			//spd[i] =  gCtrl.temp_iq * 10000;
			xi = 0;
		}
	}
	//}
	#endif
	//rt_kprintf("%x,%x,%x\r\n",dutyhandle.pwm0_duty,dutyhandle.pwm1_duty,dutyhandle.pwm2_duty );
	#if 1
	CTRL_State_e ctrlState = gCtrlHandle->state;
	if (ctrlState == CTRL_State_SpeedCloseLoop || ctrlState == CTRL_State_OpenLoop || ctrlState == CTRL_State_InitDete)
	{

	dutyhandle.pwm0_duty = t.ta.f;
	dutyhandle.pwm1_duty = t.tb.f;
	dutyhandle.pwm2_duty = t.tc.f;
	count ++;

	}
	#endif
	rt_device_control(device_pwm,CMD_PWMSETDUTY,&dutyhandle);
	#endif
}

static void adc_intr(int irqno, void *param)
{
    struct hw_adc_device *pdev = (struct hw_adc_device *)param;
	unsigned long temp;

	pdev->adchandle.Local_Instance->ctrl_reg.intr_time = 1;
	pdev->adchandle.Local_Instance->ctrl_reg.intr_clr = 1; //CLR and forbid int

	motor_ctl(pdev);

	pdev->adchandle.Local_Instance->ctrl_reg.intr_clr = 0; //enable int
	pdev->adchandle.Local_Instance->ctrl_reg.intr_time = 0;
}


static void ad_delay_us(unsigned int us)
{
    volatile unsigned int len;
    for (; us > 0; us --)
        for (len = 0; len < 20; len++ );
}

void adc_setos(struct hw_adc_device *pdev,unsigned char os)
{
	pdev->adchandle.Local_Instance->ctrl_reg.ad_os = os;
}
void adc_rst(struct hw_adc_device *pdev)
{
	pdev->adchandle.Local_Instance->ctrl_reg.ad_rst = 1;
	ad_delay_us(100);
	pdev->adchandle.Local_Instance->ctrl_reg.ad_rst = 0;
}


static rt_err_t adc_configure(struct rt_adc_device *adcdev, struct adc_configure *cfg)
{
	struct hw_adc_device *pdev = adcdev->parent.user_data;
	adc_rst(pdev);
	adc_setos(pdev,OVERSAMPLE_2);
	
	pdev->adchandle.Local_Instance->ctrl_reg.convst = 0;
	
	pdev->adchandle.Local_Instance->ctrl_reg.intr_clr = 1;
	
	rt_kprintf("adc init complete\r\n");
	
    return RT_EOK;
}

static void adc_convst(struct hw_adc_device *pdev)
{
	pdev->adchandle.Local_Instance->ctrl_reg.convst = 1;
	ad_delay_us(1);
	pdev->adchandle.Local_Instance->ctrl_reg.convst = 0;

}

static rt_err_t adc_control(struct rt_adc_device *adcdev, int cmd, void *arg)
{
    struct hw_adc_device *pdev;
	unsigned int *temp;
	unsigned long temp1;

    RT_ASSERT(adcdev != RT_NULL);

    pdev = adcdev->parent.user_data;

    switch (cmd)
    {
	case CMD_INTDISABLE:
		//rt_hw_interrupt_mask(pdev->adchandle.irq_nr);
		
		pdev->adchandle.Local_Instance->ctrl_reg.intr_clr = 1;

		break;
	case CMD_INTENABLE:
		
		pdev->adchandle.Local_Instance->ctrl_reg.intr_clr = 0;
		
		rt_hw_interrupt_clear(pdev->adchandle.irq_nr);
		rt_hw_interrupt_install(pdev->adchandle.irq_nr,adc_intr,pdev, "adc_intr");
		
		//arm_gic_set_cpu(0, pdev->adchandle.irq_nr, 1 << rt_cpu_get_smp_id());
		rt_hw_interrupt_umask(pdev->adchandle.irq_nr);

		break;
	case CMD_RST:
		pdev->adchandle.Local_Instance->ctrl_reg.ad_rst = 1;
		break;
	case CMD_CFG:
		temp = arg;
		adc_setos(pdev,*temp);
		break;
	case CMD_CONVST:
		adc_convst(pdev);
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


static QIEMW_ADC_HandleTypeDef adc_getValue(struct rt_adc_device *adcdev)
{
    struct hw_adc_device *pdev;
	QIEMW_ADC_HandleTypeDef adcvalue;


    RT_ASSERT(adcdev != RT_NULL);

    pdev = adcdev->parent.user_data;

	while(pdev->adchandle.Local_Instance->state_reg & 0x1 == 0);

	pdev->adchandle.Local_Instance->ctrl_reg.intr_clr = 1;

	adcvalue.PhaseA.qI_value = pdev->adchandle.Local_Instance->data1_reg;//IV
	adcvalue.PhaseB.qI_value = pdev->adchandle.Local_Instance->data2_reg;//IW
	adcvalue.PhaseC.qI_value = pdev->adchandle.Local_Instance->data3_reg;//IU
	adcvalue.BUS.qV_value = pdev->adchandle.Local_Instance->data4_reg;//VDC
	adcvalue.Temp.TEMP_value = pdev->adchandle.Local_Instance->data5_reg;//TEMP
	adcvalue.PhaseA.qV_value = pdev->adchandle.Local_Instance->data6_reg;//VUV
	adcvalue.PhaseB.qV_value = pdev->adchandle.Local_Instance->data7_reg;//VVW
	
	pdev->adchandle.Local_Instance->ctrl_reg.intr_clr = 0;

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
	adc_handle.irq_nr = CPU1_IRQ_ID;
	//adc_handle.irq_nr = CPU1_FIQ_ID;

	adc_hw_device1.adchandle= adc_handle;

	rt_hw_adc_register(&adc_device1, "adc1",
                          RT_DEVICE_FLAG_RDONLY,
                          &adc_hw_device1);

	return 0;

}

INIT_BOARD_EXPORT(adc_hw_init);

#endif
#endif

