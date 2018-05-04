
#include <rtthread.h>
#ifdef USER_USING_MOTORBOARD_ZYNQ

#include "finsh.h"
#include "board.h"
#include <rtdevice.h>
#include "MC_Globals.h"


#include "modules/hal/hal_obj.h"

#include "modules/MotorCtrlApp/MotorCtrlApp.h"
#include "drv_pwm.h"
//#include "xadc_drv.h"
#include "myqep.h"
#include "qep.h"
#include "drv_qep.h"
#include "motor_misc.h"
#include "drv_motor_misc.h"
#include "modules/hal/hal.h"
#include "modules/user/user.h"
#include "modules/ctrl/ctrl_obj.h"
#include "modules/hal/hal_obj.h"
#include "modules/data_select/data_select.h"
#include "modules/ctrl/ctrl.h"
#include "AD7606_drv.h"
#include "CTRL_doCurrentCtrl_v1_0/src/xctrl_docurrentctrl.h"
#include "CTRL_doCurrentCtrl_v1_0/src/xctrl_usr_docurrentctrl.h"
#include "client.h"

extern CurrentCtrl_din_type in;
long setpi(int argc,char**argv)
{
	if(strcmp(argv[1], "kp_id") == 0)
	{
		in.kp_id.f = atoi(argv[2])/1000;

		rt_kprintf("kp_id = %d\r\n",in.kp_id.f *1000);
	}
	else if(strcmp(argv[1], "ki_id") == 0)
	{
		in.ki_id.f = atoi(argv[2])/1000;

		rt_kprintf("ki_id = %d\r\n",in.ki_id.f *1000);
	}
	else if(strcmp(argv[1], "kp_iq") == 0)
	{
		in.kp_iq.f = atoi(argv[2])/1000;

		rt_kprintf("kp_iq = %d\r\n",in.kp_iq.f *1000);
	}
	else if(strcmp(argv[1], "ki_iq") == 0)
	{
		in.ki_iq.f = atoi(argv[2])/1000;

		rt_kprintf("ki_iq = %d\r\n",in.ki_iq.f *1000);
	}
	
	//rt_device_close(device);

}
FINSH_FUNCTION_EXPORT(setpi,examp : setpi kp_id data);
MSH_CMD_EXPORT(setpi, examp : setpi kp_id data);



extern CTRL_Handle gCtrlHandle;
long state(int argc,char**argv)
{
	if(strcmp(argv[1], "0") == 0)
	{
		CTRL_setState(gCtrlHandle,CTRL_State_Error);
		rt_kprintf("CTRL_State_Error\r\n");
	}
	else if(strcmp(argv[1], "1") == 0)
	{
		CTRL_setState(gCtrlHandle,CTRL_State_Idle);
		rt_kprintf("CTRL_State_Idle\r\n");
	}
	else if(strcmp(argv[1], "2") == 0)
	{
		CTRL_setState(gCtrlHandle,CTRL_State_OffLine);
		rt_kprintf("CTRL_State_OffLine\r\n");
	}	
	else if(strcmp(argv[1], "3") == 0)
	{
		CTRL_setState(gCtrlHandle,CTRL_State_InitDete);
		rt_kprintf("CTRL_State_InitDete\r\n");
	}	
	else if(strcmp(argv[1], "4") == 0)
	{
		CTRL_setState(gCtrlHandle,CTRL_State_StaticStatorInitDete);
		rt_kprintf("CTRL_State_StaticStatorInitDete\r\n");
	}
	else if(strcmp(argv[1], "5") == 0)
	{
		CTRL_setState(gCtrlHandle,CTRL_State_OpenLoop);
		rt_kprintf("CTRL_State_OpenLoop\r\n");
	}
	else if(strcmp(argv[1], "6") == 0)
	{
		CTRL_setState(gCtrlHandle,CTRL_State_OnLine);
		rt_kprintf("CTRL_State_OnLine\r\n");
	}
	else if(strcmp(argv[1], "7") == 0)
	{
		CTRL_setState(gCtrlHandle,CTRL_State_CurrentCloseLoop);
		rt_kprintf("CTRL_State_CurrentCloseLoop\r\n");
	}
	else if(strcmp(argv[1], "8") == 0)
	{
		CTRL_setState(gCtrlHandle,CTRL_State_SpeedCloseLoop);
		rt_kprintf("CTRL_State_SpeedCloseLoop\r\n");
	}
	//rt_device_close(device);

}
FINSH_FUNCTION_EXPORT(state,state);
MSH_CMD_EXPORT(state, state);
#include "drv_pwm.h"
//#include "xadc_drv.h"

long pwmtest(int argc,char**argv)
{
	unsigned long ctrl_reg,clkdiv_reg,pwm0_duty_reg,deadtime_reg;
	unsigned long clk,duty,deadtime;
	rt_device_t device;
	duty_HandleTypeDef dutyhandle;

	//Xil_Out32((0x43c40000) + (16), 0x80000000);
	rt_kprintf("pwm start\r\n");
	device = rt_device_find("pwm1");
	//rt_device_open(device,NULL);
	rt_device_control(device,CMD_PWMEN,NULL);
	ctrl_reg = Xil_In32((MYPWM_BASEADDR) + (CTRL_REG));
	clkdiv_reg = Xil_In32((MYPWM_BASEADDR) + (DIVIDER_REG));
	pwm0_duty_reg = Xil_In32((MYPWM_BASEADDR) + (PWM0_DUTY_REG));
	rt_kprintf("ctrl %d\r\nclkdiv %d \r\n pwm0duty %d\r\n",ctrl_reg,clkdiv_reg,pwm0_duty_reg);
	if(argv[1] != NULL)
	{
		if(strcmp(argv[1], "en") == 0)
		{
			rt_device_control(device,CMD_PWMEN,NULL);
		}
		else if(strcmp(argv[1], "dis") == 0)
		{
			rt_device_control(device,CMD_PWMDISABLE,NULL);
		}
		else
		{
			clk = atoi(argv[1]);
			rt_device_control(device,CMD_PWMSETCLK,&clk);
		}
	}
	if(argv[2] != NULL)
	{
		duty = atoi(argv[2]);
		dutyhandle.pwm0_duty = duty * TRIANGLETOP / 1000;
		dutyhandle.pwm1_duty = duty * TRIANGLETOP / 1000;
		dutyhandle.pwm2_duty = duty * TRIANGLETOP / 1000;
		rt_device_control(device,CMD_PWMSETDUTY,&dutyhandle);
	}

	if(argv[3] != NULL)
	{
		deadtime = atoi(argv[3]);
		
		rt_device_control(device,CMD_PWMSETDEADZONE,&deadtime);
	}
	ctrl_reg = Xil_In32((MYPWM_BASEADDR) + (CTRL_REG));
	clkdiv_reg = Xil_In32((MYPWM_BASEADDR) + (DIVIDER_REG));
	pwm0_duty_reg = Xil_In32((MYPWM_BASEADDR) + (PWM0_DUTY_REG));
	deadtime_reg = Xil_In32((MYPWM_BASEADDR) + (DEAD_ZONE_REG));
	rt_kprintf("ctrl %d\r\nclkdiv %d \r\n pwm0duty %d\r\n deadtime ns %d\r\n",ctrl_reg,clkdiv_reg,pwm0_duty_reg,deadtime_reg);
	
	//rt_device_close(device);
}
FINSH_FUNCTION_EXPORT(pwmtest, pwmtest clk duty deadtime);
MSH_CMD_EXPORT(pwmtest,pwmtest clk duty deadtime);

long adctest(int argc,char**argv)
{
	rt_device_t device;
	QIEMW_ADC_HandleTypeDef adcvalue;
	unsigned int adcvalue2;
	unsigned long temp;
	static unsigned char rst = 0;
	
	float tempa,tempb,tempc;
	
	device = rt_device_find("adc1");
	#if 0
	if(rst == 0)
	{
		device = rt_device_find("adc1");
		rt_device_open(device,RT_DEVICE_FLAG_RDONLY);
		temp = 0x0;
		rt_device_control(device,CMD_RST,&temp);
		rt_thread_delay(1000);
		temp = 0x1;
		rt_device_control(device,CMD_RST,&temp);
		rst++;
		
		rt_device_close(device);
	}
	#endif
	if(strcmp(argv[1], "en") == 0)
	{
		rt_kprintf("adc test\r\n");
		
		rt_device_control(device,CMD_INTDISABLE,0);
		//rt_device_open(device,RT_DEVICE_FLAG_RDONLY);
		rt_device_control(device,CMD_CONVST,0);
		rt_device_read (device,
	                          0,
	                          &adcvalue,
	                          0);
		
		//adcvalue2 = Xil_In32((0x43c40000) + (0x0));
		
		tempa = adcvalue.PhaseA.qI_value / 3276.8 - 3.3;//IV 输入控制板电压
		tempb = adcvalue.PhaseB.qI_value / 3276.8 - 3.3;//IW
		tempc = adcvalue.PhaseC.qI_value / 3276.8 - 3.3;//IU

		tempa = tempa * 8.77;//IV 输入控制板电压
		tempb = tempb * 8.77;//IW
		tempc = tempc * 8.77;//IU	

		rt_kprintf("phase a %x\r\n",adcvalue.PhaseA.qI_value);
		rt_kprintf("phase b %x\r\n",adcvalue.PhaseB.qI_value);
		rt_kprintf("phase C %x\r\n",adcvalue.PhaseC.qI_value);
		
		
		rt_kprintf("phase a %d\r\n",(int)(tempa * 1000));
		rt_kprintf("phase b %d\r\n",(int)(tempb * 1000));
		rt_kprintf("phase C %d\r\n",(int)(tempc * 1000));
		rt_kprintf("BUS V %d\r\n",adcvalue.BUS.qV_value);
		rt_kprintf("Temp %d\r\n",adcvalue.Temp.TEMP_value);
		rt_kprintf("phase AV %d\r\n",adcvalue.PhaseA.qV_value);
		rt_kprintf("phase BV %d\r\n",adcvalue.PhaseB.qV_value);

		//rt_device_close(device);
	}
	if(strcmp(argv[1], "close") == 0)
	{
		
		//rt_device_open(device,RT_DEVICE_FLAG_RDONLY);
		rt_kprintf("adc close\r\n");
		device = rt_device_find("adc1");
		//rt_device_close(device);
	}
}
FINSH_FUNCTION_EXPORT(adctest, adctest en or close);
MSH_CMD_EXPORT(adctest,adctest en or close);


#include "myqep.h"
#include "qep.h"
#include "drv_qep.h"
extern int speed;
extern unsigned int t_array[1000];

long qeptest(int argc,char**argv)
{
	unsigned long ctrl_reg;
	rt_device_t device;
	Qep_ValueTypeDef qep_data;

	rt_kprintf("qep start\r\n");
	device = rt_device_find("qep1");
	//rt_device_open(device,NULL);
	ctrl_reg = Xil_In32((MYQEP_BASEADDR) + (MYQEP_CTRL_REG));
	rt_kprintf("ctrl %x\r\n",ctrl_reg);
	rt_kprintf("period = %x",Xil_In32((MYQEP_BASEADDR) + (MYQEP_TURN_REG)));
	if(argv[1] != NULL)
	{
		if(strcmp(argv[1], "en") == 0)
		{
			rt_device_control(device,CMD_QEPEN,NULL);
			
			ctrl_reg = Xil_In32((MYQEP_BASEADDR) + (MYQEP_CTRL_REG));
			rt_kprintf("ctrl %x\r\n",ctrl_reg);
		}
		else if(strcmp(argv[1], "dis") == 0)
		{
			rt_device_control(device,CMD_QEPDISABLE,NULL);
			
			ctrl_reg = Xil_In32((MYQEP_BASEADDR) + (MYQEP_CTRL_REG));
			rt_kprintf("ctrl %x\r\n",ctrl_reg);
		}
		else if(strcmp(argv[1], "read") == 0)
		{
			rt_device_read(device,0,&qep_data,0);
			
			rt_kprintf("cnt= %x\r\nturn = %x\r\n",qep_data.cnt,qep_data.turn);
			if(t_array[125] > t_array[0])
			{
				speed = (t_array[125] - t_array[0]);
				rt_kprintf("forwardspeed = %d\r\n",speed);// Mechanics:10000, t:10ms, x/10000/10ms:mechanical speed
			}
			else
			{
				speed = (t_array[0] - t_array[125]);
				rt_kprintf("reversespeed = %d\r\n",speed);
			}
		}
		
	}
	//rt_device_close(device);
}
FINSH_FUNCTION_EXPORT(qeptest, qeptest en dis r);
MSH_CMD_EXPORT(qeptest, qeptest en dis r);



#include "motor_misc.h"
#include "drv_motor_misc.h"

long mmtest(int argc,char**argv)
{
	rt_device_t device;
	device = rt_device_find("motor_misc1");
	unsigned long intrstate;
	unsigned int temp;
	
	if(strcmp(argv[1], "en") == 0)
	{
		//rt_device_open(device,NULL);
		//rt_device_read(device,0,&intrstate,0);
		//rt_kprintf("intr state: %x\r\n",intrstate);
		temp = 100;
		rt_device_control(device,CMD_MISC_SET_BREAK_DUTY,&temp);
		temp = 5000;
		rt_device_control(device,CMD_MISC_SET_FAN_DUTY,&temp);
		temp = 1;
		rt_device_control(device,CMD_MISC_BREAKEN,&temp);
		temp = 1;
		rt_device_control(device,CMD_MISC_FANEN,&temp);
		temp = 1;
		//rt_device_control(device,CMD_MISC_CLR_FLAG,&temp);
		
		rt_device_control(device,CMD_MISC_INTENABLE,NULL);
		
		//rt_device_close(device);
		
	}
	else if(strcmp(argv[1], "dis") == 0)
	{
		
		//rt_device_open(device,NULL);
		temp = 0;
		rt_device_control(device,CMD_MISC_INTDISABLE,NULL);
		rt_device_control(device,CMD_MISC_SET_BREAK_DUTY,&temp);
		rt_device_control(device,CMD_MISC_BREAKEN,&temp);
		rt_device_control(device,CMD_MISC_FANEN,&temp);
		rt_device_control(device,CMD_MISC_SET_FAN_DUTY,&temp);
		rt_device_control(device,CMD_MISC_CLR_FLAG,NULL);
		
		//rt_device_close(device);
		rt_kprintf("close\r\n");
	}

}
FINSH_FUNCTION_EXPORT(mmtest, mmtest en dis);
MSH_CMD_EXPORT(mmtest, mmtest en dis);

long rlytest(int argc,char**argv)
{
	rt_device_t device;
	device = rt_device_find("motor_misc1");
	unsigned long intrstate;
	unsigned int temp;
	//rt_device_open(device,NULL);
	if(strcmp(argv[1], "set") == 0)
	{
		rt_device_control(device,CMD_MISC_SET_RLY,NULL);
		
	}
	else if(strcmp(argv[1], "clr") == 0)
	{
		rt_device_control(device,CMD_MISC_CLR_RLY,NULL);
	}
	//rt_device_close(device);
	return 0;
}
FINSH_FUNCTION_EXPORT(rlytest, rlytest set clr);
MSH_CMD_EXPORT(rlytest, rlytest set clr);

long sharememtest(int argc,char**argv)
{
	rt_device_t device;
	device = rt_device_find("sharemem1");
	rt_device_open(device,NULL);
	int *p,i;
	if(argc > 0)
	{
		p = rt_malloc(argc-1);
		if(p != NULL)
		{
			for(i = 0; i < argc-1; i++)
			{
				*(p+i) = atoi(argv[i+1]);
				rt_kprintf("%x \r\n",*(p+i));
			}
			rt_device_write(device,0,p,4*(argc-1));
			rt_free(p);
		}
	}
	return 0;
}
FINSH_FUNCTION_EXPORT(sharememtest, sharememtest num);
MSH_CMD_EXPORT(sharememtest, sharememtest num);


#define SLEEPTIME(ms) (((ms)/1000)*RT_TICK_PER_SECOND)
extern HAL_Obj gHal;

#define USER_MOTORTASK_PRIORITY (10)
static void Motor_Hardware_Init(void)
{
	rt_device_t device_pwm,device_qep,device_misc,device_adc;
	unsigned int temp;
	QIEMW_ADC_HandleTypeDef adcvalue;
	float tempa,tempb,tempc;

	device_misc = rt_device_find("motor_misc1");
	rt_device_open(device_misc,NULL);
	temp = 100;
	rt_device_control(device_misc,CMD_MISC_SET_BREAK_DUTY,&temp);
	temp = 5000;
	rt_device_control(device_misc,CMD_MISC_SET_FAN_DUTY,&temp);
	temp = 1;
	rt_device_control(device_misc,CMD_MISC_BREAKEN,&temp);
	temp = 1;
	rt_device_control(device_misc,CMD_MISC_FANEN,&temp);
	temp = 1;
	rt_device_control(device_misc,CMD_MISC_INTENABLE,NULL);
	
	device_pwm = rt_device_find("pwm1");
	rt_device_open(device_pwm,NULL);
	rt_device_control(device_pwm,CMD_PWMEN,NULL);
	
	device_qep = rt_device_find("qep1");
	rt_device_open(device_qep,NULL);
	rt_device_control(device_qep,CMD_QEPEN,NULL);


	rt_device_control(device_misc,CMD_MISC_SET_RLY,NULL);

	
	device_adc = rt_device_find("adc1");
	rt_device_open(device_adc,NULL);
	
	rt_device_control(device_adc,CMD_INTDISABLE,0);
	int i = 10;
	while(i--)
	{
		rt_device_control(device_adc,CMD_CONVST,0);
		rt_device_read (device_adc,
							  0,
							  &adcvalue,
							  0);


		tempa = adcvalue.PhaseA.qI_value / 3276.8 - 3.3;//IV 输入控制板电压
		tempb = adcvalue.PhaseB.qI_value / 3276.8 - 3.3;//IW
		tempc = adcvalue.PhaseC.qI_value / 3276.8 - 3.3;//IU

		tempa = tempa * 8.77;//IV 输入控制板电压
		tempb = tempb * 8.77;//IW
		tempc = tempc * 8.77;//IU	

		gHal.adcBias.I.value[0] += tempa;//IV 输入控制板电压
		gHal.adcBias.I.value[1] += tempb;//IW
		gHal.adcBias.I.value[2] += tempc;//IU
		
		rt_kprintf("phase a %x\r\n",adcvalue.PhaseA.qI_value);
		rt_kprintf("phase b %x\r\n",adcvalue.PhaseB.qI_value);
		rt_kprintf("phase C %x\r\n",adcvalue.PhaseC.qI_value);
		rt_kprintf("phase a %d\r\n",tempa * 1000);
		rt_kprintf("phase b %d\r\n",tempb * 1000);
		rt_kprintf("phase C %d\r\n",tempc * 1000);
		#if 0
		gHal.adcBias.I.value[0] = adcvalue.PhaseA.qI_value/3276.8-3.3;//IV 输入控制板电压
		gHal.adcBias.I.value[1] = adcvalue.PhaseB.qI_value/3276.8-3.3;//IW
		gHal.adcBias.I.value[2] = adcvalue.PhaseC.qI_value/3276.8-3.3;//IU
		
		gHal.adcBias.I.value[0] = gHal.adcBias.I.value[0] * 8.77;//IV 输入控制板电压
		gHal.adcBias.I.value[1] = gHal.adcBias.I.value[1] * 8.77;//IW
		gHal.adcBias.I.value[2] = gHal.adcBias.I.value[2] * 8.77;//IU
		#endif
	}

	gHal.adcBias.I.value[0] = gHal.adcBias.I.value[0] / 10;
	gHal.adcBias.I.value[1] = gHal.adcBias.I.value[1] / 10;
	gHal.adcBias.I.value[2] = gHal.adcBias.I.value[2] / 10;

	i = gHal.adcBias.I.value[0] * 1000;
	rt_kprintf("phase a bias %d\r\n",i);
	rt_kprintf("phase b bias %d\r\n",gHal.adcBias.I.value[1] * 1000);
	rt_kprintf("phase C bias %d\r\n",gHal.adcBias.I.value[2] * 1000);

	
	rt_device_control(device_adc,CMD_INTENABLE,0);

}
/*
/**4kw: 采样电阻2mohm，采样电阻两端电压到控制板输入电压是1 :57，
/********	     I=8.77V      I:电流(A);     V:输入控制板的电压(V)
*/
extern int turn_array[126];
extern CTRL_Obj gCtrl;
extern int pwm0[260];
extern int pwm1[260];
extern int pwm2[260];
extern int point[260];
extern int angle[260];
extern int angleout[260];
extern int va[260];
extern int vb[260];
extern unsigned int j;
extern int spd[260];
#if 0
struct spi_msg
{
	unsigned short head;
	unsigned short timer;
	unsigned short split1;
	unsigned int speed;
	unsigned short split2;
	short v1;
	unsigned short split3;
	short v2;
	unsigned short split4;
	short v3;
	unsigned short split5;
	short v4;
	unsigned short split6;
	short v5;
	unsigned short split7;
	short v6;
	unsigned short split8;
	short v7;
	unsigned short split9;
	short v8;
	unsigned short split10;
	short check;
	
};
#endif
struct spi_msg
{
	unsigned char head;
	unsigned char timerl;
	
	unsigned char split11;
	unsigned char timerh;
	
	unsigned char split1;
	unsigned char speedll;
	
	unsigned char split12;
	unsigned char speedlh;
	
	unsigned char split22;
	unsigned char speedhl;
	
	unsigned char split13;
	unsigned char speedhh;
	
	unsigned char split2;
	char v1l;
	
	unsigned char split14;
	char v1h;
	
	unsigned char split3;
	char v2l;
	
	unsigned char split15;
	char v2h;
	
	unsigned char split4;
	char v3l;
	
	unsigned char split16;
	char v3h;
	
	unsigned char split5;
	char v4l;
	
	unsigned char split17;
	char v4h;
	
	unsigned char split6;
	char v5l;
	
	unsigned char split18;
	char v5h;
	
	unsigned char split7;
	char v6l;
	
	unsigned char split19;
	char v6h;
	
	unsigned char split8;
	char v7l;
	
	unsigned char split20;
	char v7h;
	
	unsigned char split9;
	char v8l;
	
	unsigned char split21;
	char v8h;
	
	unsigned char split10;
	char check;
	
};


void USER_MotorTask_entry(void *parameter)
{
	
	Motor_Ctrl_Init();
	Motor_Hardware_Init();
	
	rt_device_t device,device_sharemem;

	
	CurrentCtrl_dout_type t;
	CurrentCtrl_din_type in;
	
	XCtrl_docurrentctrl InstancePtr;

	
	static struct spi_msg spi_msg = {.timerl = 0,.timerh = 0,.check = 0,\
		.split1 = 0x5b,.split2 = 0x5b,.split3 = 0x5b,\
		.split4 = 0x5b,.split5 = 0x5b,.split6 = 0x5b,\
		.split7 = 0x5b,.split8 = 0x5b,.split9 = 0x5b,\
		.split10 = 0x5b,.split11 = 0x5b,.split12 = 0x5b,\
		.split13 = 0x5b,.split14 = 0x5b,.split15 = 0x5b,\
		.split16 = 0x5b,.split17 = 0x5b,.split18 = 0x5b,\
		.split19 = 0x5b,.split20 = 0x5b,.split21 = 0x5b,\
		.split22 = 0x5b,.v2l = 0,.v2h = 0,\
		};
	
	//device = rt_device_find("pwm1");
	
	device_sharemem = rt_device_find("sharemem1");
	rt_device_open(device_sharemem,NULL);
 	//pwm_config_init();
	//stm32_hw_ADC_init();
	//stm32_hw_QEP_init();
	while(1)
	{


		
		#if 0
		spi_msg.check = 0;
		short *ptr_spi_msg = &spi_msg;
		int i = 0;
		spi_msg.head = 0x5a;
		spi_msg.speedll = 1;//qep_data.cnt;
		spi_msg.timerl++;
		if(spi_msg.timerl == 0xff)
		{
			spi_msg.timerh++;
			spi_msg.timerl = 0;
		}
		spi_msg.v1l++;
		if(spi_msg.v1l == 0xff)
		{
			spi_msg.v1h++;
			spi_msg.v1l = 0;
		}
		spi_msg.v2l++;
		if(spi_msg.v2l == 0xff)
		{1
			spi_msg.v2h++;
			spi_msg.v2l = 0;
		}
		spi_msg.v3l++;
		if(spi_msg.v3l == 0xff)
		{
			spi_msg.v3h++;
			spi_msg.v3l = 0;
		}
		spi_msg.v4l++;
		if(spi_msg.v4l == 0xff)
		{
			spi_msg.v4h++;
			spi_msg.v4l = 0;
		}
		spi_msg.v5l++;
		if(spi_msg.v5l == 0xff)
		{
			spi_msg.v5h++;
			spi_msg.v5l = 0;
		}
		spi_msg.v6l++;
		if(spi_msg.v6l == 0xff)
		{
			spi_msg.v6h++;
			spi_msg.v6l = 0;
		}
		spi_msg.v7l++;
		if(spi_msg.v7l == 0xff)
		{
			spi_msg.v7h++;
			spi_msg.v7l = 0;
		}
		spi_msg.v8l = 0;
		for(i = 1;i < (sizeof(struct spi_msg) - 2);i++,i++)
			spi_msg.check ^= ptr_spi_msg[i];
		rt_device_write(device_sharemem,0,&spi_msg,sizeof(struct spi_msg));
#endif
		if(j > 26000)
		{

		//rt_device_open(device,NULL);
		//rt_device_control(device,CMD_PWMDISABLE,NULL);
			int i=0;
			
			rt_kprintf("state: %d\r\n", gCtrl.state);
			for(i = 0; i < 260;i++)
			{
				rt_kprintf("0: %5d;1: %5d;2: %5d;p: %8d;ao: %9d;a: %9d;va: %9d;vb: %10d;spd: %5d\r\n",pwm0[i],pwm1[i],pwm2[i],point[i],angleout[i],angle[i],va[i],vb[i],spd[i]);
			}
			//rt_device_control(device,CMD_PWMEN,NULL);
			
			j = 0;
		}
		#if 0
		if(Motor_Ctrl_State(a,&gFlag))
		{
			PWMOutputsEnable(TIM8);
		}
		else
		{
			PWMOutputsDisable(TIM8);
		}
		if(myscanf((char *)a) == RT_EOK)
		{
			gFlag = 1;
		}
		#endif
#if 1
		d_monitor_type monitor;
		monitor.start0 = 0xff;
		monitor.start1 = 0x00;
		monitor.end0 = 0x11;
		monitor.end1 = 0x22;
		
		monitor.ia.f = sin(monitor.time.d);
		monitor.ib.f = cos(monitor.time.d);
		monitor.ic.f = sin(monitor.time.d);
		monitor.spd.f = 0;
		monitor.time.d++;
		monitor.check.d = monitor.ia.d + monitor.ib.d + monitor.ic.d + monitor.spd.d + monitor.time.d;
		
		rt_device_write(device_sharemem,0,&monitor,sizeof(d_monitor_type));
		
#endif

		
		/*
		**fpga test 
		*/
		#if 0
		CurrentCtrl_din_type in;
		XCtrl_docurrentctrl InstancePtr;
		CurrentCtrl_dout_type t;
		//char buffer[10000],buffer2[6]={0x1,0x2,0x3,0x4,0x5,0x6};
		int revbytes;
		while(revbytes = rt_device_read(device_sharemem,0,&in,0)==0);
		Init_doCurrentCtrl(&InstancePtr);
		#if 0
			int k;
		for(k=0;k<revbytes;k++)
			printf("%x ",buffer[k]);
		printf("\n");
	#endif

		Run_doCurrentCtrl(&InstancePtr,&in,&t);
		rt_device_write(device_sharemem,0,&t,sizeof(CurrentCtrl_dout_type));
		
		#endif
		
		rt_thread_sleep(1);
	}
}






int USER_MotorTask_init()
{
    rt_thread_t tid;
	
	tid = rt_thread_create("Motor",
                           USER_MotorTask_entry, RT_NULL,
                           1024, USER_MOTORTASK_PRIORITY, 20);
    if (tid != RT_NULL) rt_thread_startup(tid);

    return 0;
}
INIT_APP_EXPORT(USER_MotorTask_init);
#endif

