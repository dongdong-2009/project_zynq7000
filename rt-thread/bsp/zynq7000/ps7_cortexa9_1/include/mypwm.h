/*
**pin definition
*Y11 PWM_OUT[0]
*AA11 PWM_OUT[1]
*Y10 PWM_OUT[2]
*AA9 PWM_OUTN[0]
*AB11 PWM_OUTN[1]
*AB10 PWM_OUTN[2]
*/
#ifndef MYPWM_H
#define MYPWM_H


/****************** Include Files ********************/
#include "xil_types.h"
#include "xstatus.h"
#include "myip.h"
/*
**PWM?_DUTY_REG  [DEAD_ZONE_REG   999-DEAD_ZONE_REG]
*/
#define MYPWM_BASEADDR 0x43c10000
#define INTR_BASEADDR 
#define PWM_CLK_IN (100000000)
//#define PWM_PEAK 1000
#define CLKDIV(freq) (PWM_CLK_IN/((freq)*2))
#define DEADZONE(ns) ((unsigned long)(ns)/(1000000000/PWM_CLK_IN));
//#define PWMDUTY(duty) PWM_PEAK * (duty) / 10000;
#define PWMDUTY(duty) (duty);

					
#define PWM0_DUTY_REG 0
#define PWM1_DUTY_REG 4
#define PWM2_DUTY_REG 8
/*
**DEAD_ZONE_REG 
*/
#define DEAD_ZONE_REG 12
/*
**·ÖÆµ¼Ä´æÆ÷
*/
#define DIVIDER_REG 16
/*
**¿ØÖÆ¼Ä´æÆ÷
*/
#define CTRL_REG 20

#define GLOBAL_INTR_EN_REG 44
#define INTR_EN_REG 48
#define INTR_STS_REG 52
#define INTR_ACK_REG 56
#define INTR_PENDING_REG 60



typedef struct
{
	unsigned short int pwm0_duty;
	unsigned short int pwm1_duty;
	unsigned short int pwm2_duty;
}duty_HandleTypeDef;

typedef struct
{
	/*
	**PWM?_DUTY_REG  [DEAD_ZONE_REG   0xfffffff-DEAD_ZONE_REG]
	*/
	volatile unsigned long pwm0_duty_reg;//0
	volatile unsigned long pwm1_duty_reg;//4/
	volatile unsigned long pwm2_duty_reg;//8
	/*
	**DEAD_ZONE_REG 
	*/
	volatile unsigned long dead_zone_reg;//12
	/*
	**·ÖÆµ¼Ä´æÆ÷
	*/
	volatile unsigned long divider_reg;//16
	
	volatile unsigned long ctrl_reg;//20  ctrl_reg[2 : 0]: pwm enable register ,1 enable ,0 disable
	volatile unsigned long rsv1;     //24
	volatile unsigned long rsv2;     //28
	volatile unsigned long rsv3;     //32
	volatile unsigned long rsv4;     //36
	volatile unsigned long rsv5;     //40
	
	volatile unsigned long global_intr_en_reg; //44
	volatile unsigned long intr_en_reg;//48
	volatile unsigned long intr_sts_reg;//52
	volatile unsigned long intr_ack_reg;//56
	volatile unsigned long intr_pending_reg;//60
}PWM_TypeDef;

typedef struct
{
	duty_HandleTypeDef pwmduty;
	unsigned long dead_ns;  
	unsigned long clk;
	unsigned char pwmstate; //0: pwm enable; 1: pwm disable
}PWM_Base_InitTypeDef;
/** 
  * @brief  mypwm Handle Structure definition  
  */ 
typedef struct
{
  PWM_TypeDef                 *Instance;     /*!< Register base address             */
  PWM_Base_InitTypeDef        Init;          /*!< TIM Time Base required parameters */
  unsigned char state;
}PWM_HandleTypeDef;

/**************************** Type Definitions *****************************/
/**
 *
 * Write a value to a MYPWM register. A 32 bit write is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is written.
 *
 * @param   BaseAddress is the base address of the MYPWMdevice.
 * @param   RegOffset is the register offset from the base to write to.
 * @param   Data is the data written to the register.
 *
 * @return  None.
 *
 * @note
 * C-style signature:
 * 	void MYPWM_mWriteReg(u32 BaseAddress, unsigned RegOffset, u32 Data)
 *
 */
#define MYPWM_mWriteReg(BaseAddress, RegOffset, Data) \
  	Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))

/**
 *
 * Read a value from a MYPWM register. A 32 bit read is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is read from the register. The most significant data
 * will be read as 0.
 *
 * @param   BaseAddress is the base address of the MYPWM device.
 * @param   RegOffset is the register offset from the base to write to.
 *
 * @return  Data is the data from the register.
 *
 * @note
 * C-style signature:
 * 	u32 MYPWM_mReadReg(u32 BaseAddress, unsigned RegOffset)
 *
 */
#define MYPWM_mReadReg(BaseAddress, RegOffset) \
    Xil_In32((BaseAddress) + (RegOffset))

/************************** Function Prototypes ****************************/
/**
 *
 * Run a self-test on the driver/device. Note this may be a destructive test if
 * resets of the device are performed.
 *
 * If the hardware system is not built correctly, this function may never
 * return to the caller.
 *
 * @param   baseaddr_p is the base address of the MYPWM instance to be worked on.
 *
 * @return
 *
 *    - XST_SUCCESS   if all self-test code passed
 *    - XST_FAILURE   if any self-test code failed
 *
 * @note    Caching must be turned off for this function to work.
 * @note    Self test may fail if data memory and device are not on the same bus.
 *
 */
XStatus MYPWM_Reg_SelfTest(void * baseaddr_p);

#endif // MYPWM_H
