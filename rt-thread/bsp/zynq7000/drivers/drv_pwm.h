#ifndef DRV_PWM_H
#define DRV_PWM_H

#include <rtthread.h>
#include "mypwm.h"
#include "pwm.h"


#define PWM_CLK_HZ (12500)
#define DEAD_ZONE_NS (3000)
#define PWM_ENABLE 1
#define PWM_DISABLE 0
#define TRIANGLETOP (PWM_CLK_IN/((PWM_CLK_HZ)*2))
#define PWM0_DUTY ((0.5)*TRIANGLETOP)
#define PWM1_DUTY ((0.5)*TRIANGLETOP)
#define PWM2_DUTY ((0.5)*TRIANGLETOP)

#define CMD_PWMEN 1
#define CMD_PWMDISABLE 2
#define CMD_PWMSETDUTY 3
#define CMD_PWMSETDEADZONE 4
#define CMD_PWMSETCLK 5



extern PWM_HandleTypeDef pwm;


#define RT_PWM_CONFIG_DEFAULT           \
{                                          \
    PWM_CLK_HZ,      \
    DEAD_ZONE_NS,    \
    PWM0_DUTY,       \
    PWM1_DUTY,       \
    PWM2_DUTY,   	 \
}





#endif
