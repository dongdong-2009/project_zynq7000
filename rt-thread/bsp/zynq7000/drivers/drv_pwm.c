/*************************************************************************/

#include <rtthread.h>

//#undef USER_USING_MOTORLOWLEVEL
#ifdef USER_USING_MOTORLOWLEVEL 

#include "drv_pwm.h"

struct hw_pwm_device
{
	PWM_HandleTypeDef pwm;

};

static void PWMOutputsEnable(PWM_HandleTypeDef *pwm)
{
	while(PWMEnable(pwm) != MYIP_SUCCESS);
}

static void PWMOutputsDisable(PWM_HandleTypeDef *pwm)
{
	while(PWMDisable(pwm)!= MYIP_SUCCESS);

}

static void SetDutyCycles(PWM_HandleTypeDef *pwm, duty_HandleTypeDef *duty)
{
	while(PWMSetduty(pwm,duty)!= MYIP_SUCCESS);
}

static rt_err_t pwm_configure(struct rt_pwm_device *pwmdev, struct pwm_configure *cfg)
{
	uint32_t mr;
	struct hw_pwm_device *pdev = pwmdev->parent.user_data;
	
	pdev->pwm.state = MYIP_STATE_RESET;
	pdev->pwm.Init.clk = cfg->clk_hz;
	pdev->pwm.Init.dead_ns = cfg->deadzone_ns;
	pdev->pwm.Init.pwmduty.pwm0_duty = cfg->pwm0_duty;
	pdev->pwm.Init.pwmduty.pwm1_duty = cfg->pwm1_duty;
	pdev->pwm.Init.pwmduty.pwm2_duty = cfg->pwm2_duty;
	pdev->pwm.Init.pwmstate = PWM_DISABLE;
	
	PWM_Init(&pdev->pwm);
	rt_kprintf("******pwm init*********************\r\n");
	rt_kprintf("clk=%d,deadzone=%d,pwm0duty=%d,pwm1duty=%d,pwm2duty=%d\r\n",\
		cfg->clk_hz,cfg->deadzone_ns,cfg->pwm0_duty,cfg->pwm1_duty,cfg->pwm2_duty);
	
	rt_kprintf("******end*********************\r\n");
    return RT_EOK;
}
static rt_err_t pwm_control(struct rt_pwm_device *pwmdev, int cmd, void *arg)
{
    struct hw_pwm_device *pdev;
	duty_HandleTypeDef *duty;

    RT_ASSERT(pwmdev != RT_NULL);

    pdev = pwmdev->parent.user_data;

    switch (cmd)
    {
    case CMD_PWMEN:
		PWMOutputsEnable(&pdev->pwm);
        break;

    case CMD_PWMDISABLE:
		PWMOutputsDisable(&pdev->pwm);
        break;
		
	case CMD_PWMSETDUTY:
		duty = arg;
		SetDutyCycles(&pdev->pwm,duty);

		break;

	case CMD_PWMSETDEADZONE:
		while(PWMSetDeadzone(&pdev->pwm,arg) != MYIP_SUCCESS);


		break;
	case CMD_PWMSETCLK:
		while(PWMSetclk(&pdev->pwm,arg) != MYIP_SUCCESS);

		break;
	default: 
			break;
    }

    return RT_EOK;
}

static const struct rt_pwm_ops _pwm_ops =
{
    pwm_configure,
    pwm_control,
};

void PWM_MSP_Init(PWM_HandleTypeDef *pwm)
{
}


struct hw_pwm_device pwm_hw_device1;
PWM_HandleTypeDef pwm_handle;
rt_pwm_t pwm_device1;




int pwm_hw_init(void)
{

	struct pwm_configure pwm_config = RT_PWM_CONFIG_DEFAULT;
	pwm_device1.config = pwm_config;
	pwm_device1.ops = &_pwm_ops;
	
	pwm_handle.Instance = MYPWM_BASEADDR;

	pwm_hw_device1.pwm = pwm_handle;

	rt_hw_pwm_register(&pwm_device1, "pwm1",
                          NULL,
                          &pwm_hw_device1);
	return 0;

}
INIT_BOARD_EXPORT(pwm_hw_init);


int pwm_config_init(void)
{
	rt_device_t device;

	//rt_kprintf("pwm init\r\n");
	device = rt_device_find("pwm1");
	if(device == NULL) printf("device not found \r\n");
	rt_device_open(device,NULL);
	
	rt_device_init(device);
	
	rt_device_close(device);
	return 0;
}
INIT_DEVICE_EXPORT(pwm_config_init);


#endif
