#ifndef DRV_MOTOR_MISC_H
#define DRV_MOTOR_MISC_H

#include <rtthread.h>
#include "motor_misc.h"

#define TZ1_FAULT (0x01)
#define TZ2_FAULT (0x02)
#define VOE_FAULT (0x04)
#define SC_FAULT (0x08)
#define EA_FAULT (0x10)
#define EB_FAULT (0x20)

#define MOTOR_MISC_LOCAL_BASEADDR 0x43c40000
#define CPU1_IRQF2P0_ID 61

struct pwm_ctrl_def
{
	int break_en : 1;  //0: disable;1:enable 
	int fan_en : 1;    //0: disable;1:enable 
	int RLY : 1;
	int rsv1 : 5;
	int rsv2 : 8;
	int rsv3 : 8;
	int rsv4 : 8;
};


struct intr_ctrl_def
{
	int rsv1 : 8;
	int rsv2 : 8;
	int rsv3 : 8;
	int rsv4 : 7;
	int clr_flag : 1;// 1: clr; 0: normal
};


typedef struct
{
	volatile struct pwm_ctrl_def pwm_ctrl_reg; //0
	volatile unsigned long break_duty_reg; //4//  max:10000
	volatile unsigned long fan_duty_reg; //8
	volatile unsigned long intr_state_reg; //12
	volatile struct intr_ctrl_def intr_ctrl_reg; //16
}MiscLocal_TypeDef;



/** 
  * @brief  mypwm Handle Structure definition  
  */ 
typedef struct
{
  MiscLocal_TypeDef                 *Local_Instance;     /*!< Register base address             */
  unsigned char irq_nr;
}Misc_HandleTypeDef;
extern Misc_HandleTypeDef Misc_handle;


#define RT_MISC_CONFIG_DEFAULT           \
{                                          \
    0,      \
    0,    \
    0,      \
    5000,   \
    5000,   \
}

#endif

