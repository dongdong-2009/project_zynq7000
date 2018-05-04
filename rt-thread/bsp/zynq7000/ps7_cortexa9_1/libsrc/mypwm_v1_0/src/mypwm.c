

/***************************** Include Files *******************************/
#include "mypwm.h"


extern unsigned char PWMEnable(PWM_HandleTypeDef *pwm)
{
	if(pwm == NULL)
	{
		return MYIP_ERROR;
	}
	if(pwm->state == MYIP_STATE_READY)
	{
		pwm->state = MYIP_STATE_BUSY;
		pwm->Instance->ctrl_reg |= 0x7; 
		pwm->state = MYIP_STATE_READY;
		return MYIP_SUCCESS;
	}
	return MYIP_BUSY;
	
}
extern char PWMSetduty(PWM_HandleTypeDef *pwm,duty_HandleTypeDef *duty)
{
	if(pwm == NULL)
	{
		return MYIP_ERROR;
	}
	
	if(duty == NULL)
	{
		return MYIP_ERROR;
		
	}
	if(pwm->state == MYIP_STATE_READY)
	{
	
		pwm->state = MYIP_STATE_BUSY;
		pwm->Instance->pwm0_duty_reg = PWMDUTY(duty->pwm0_duty);
		pwm->Instance->pwm1_duty_reg = PWMDUTY(duty->pwm1_duty);
		pwm->Instance->pwm2_duty_reg = PWMDUTY(duty->pwm2_duty);
		pwm->state = MYIP_STATE_READY;
		
		return MYIP_SUCCESS;
	}
	return MYIP_BUSY;
}

extern char PWMSetDeadzone(PWM_HandleTypeDef *pwm,unsigned long *deadzone)
{
	if(pwm == NULL)
	{
		return MYIP_ERROR;
	}
	
	if(pwm->state == MYIP_STATE_READY)
	{
	
		pwm->state = MYIP_STATE_BUSY;
		pwm->Instance->dead_zone_reg = DEADZONE(*deadzone/2);
		pwm->state = MYIP_STATE_READY;
		return MYIP_SUCCESS;
	}
	
	return MYIP_BUSY;
}

extern char PWMSetclk(PWM_HandleTypeDef *pwm,unsigned long *clk)
{
	if(pwm == NULL)
	{
		return MYIP_ERROR;
	}
	
	if(pwm->state == MYIP_STATE_READY)
	{
	
		pwm->state = MYIP_STATE_BUSY;
		pwm->Instance->divider_reg = CLKDIV(*clk);
		pwm->state = MYIP_STATE_READY;
		return MYIP_SUCCESS;
	}
	
	return MYIP_BUSY;
}

extern unsigned char PWMDisable(PWM_HandleTypeDef *pwm)
{
	if(pwm == NULL)
	{
		return MYIP_ERROR;
	}
	if(pwm->state == MYIP_STATE_READY)
	{
		pwm->state = MYIP_STATE_BUSY;
		pwm->Instance->ctrl_reg &= 0xffffffff8; 
		pwm->state = MYIP_STATE_READY;
		return MYIP_SUCCESS;
	}
	//rt_kprintf("PWMDisable busy\r\n");
	return MYIP_BUSY;
}

__attribute__((weak)) void PWM_MSP_Init(PWM_HandleTypeDef *pwm)
{
}

extern char PWM_Init(PWM_HandleTypeDef *pwm)
{
	if(pwm == NULL)
	{
		return MYIP_ERROR;
	}
	if(pwm->state == MYIP_STATE_RESET)
	{
		PWM_MSP_Init(pwm);
		pwm->state = MYIP_STATE_READY;
	}
	while(PWMDisable(pwm) != MYIP_SUCCESS);
	
	while(PWMSetclk( pwm,&pwm->Init.clk) != MYIP_SUCCESS);
	while(PWMSetDeadzone( pwm,&pwm->Init.dead_ns) != MYIP_SUCCESS);
	while(PWMSetduty( pwm,&pwm->Init.pwmduty) != MYIP_SUCCESS);
	
	if(pwm->Init.pwmstate == 1)
		while(PWMEnable(pwm) != MYIP_SUCCESS);
	else
		while(PWMDisable(pwm) != MYIP_SUCCESS);
		
	return MYIP_SUCCESS;
}


/************************** Function Definitions ***************************/
