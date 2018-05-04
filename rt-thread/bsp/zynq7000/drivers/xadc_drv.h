#ifndef XADC_DRV_H
#define XADC_DRV_H

#include <rtthread.h>
#include "adc.h"


#define PWM_CLK_HZ 12500//5000 12500 25000
#define DEAD_ZONE_NS 800
#define PWM_ENABLE 1
#define PWM_DISABLE 0
#define PWM0_DUTY 500
#define PWM1_DUTY 500
#define PWM2_DUTY 500


#define ADC_LOCAL_BASEADDR (0x43c00000)
#define ADC_INTC_BASEADDR  (ADC_LOCAL_BASEADDR + 0x5c)
#define ADC_HARD_BASEADDR  (ADC_LOCAL_BASEADDR + 0x200)

#define CPU1_FIQ_ID 28
#define CPU1_IRQ_ID 31


#define GIEINTR 0x80000000
#define EOSINTR 0x10
#define RT_ADC_CONFIG_DEFAULT           \
{                                          \
}



typedef struct
{
	volatile unsigned long soft_rst_reg;//0
	volatile unsigned long status_reg;//4/
	volatile unsigned long alarm_out_status_reg;//8
	volatile unsigned long convst_reg;//12
	volatile unsigned long xadc_rst_reg;//16
}ADCLocal_TypeDef;

typedef struct
{
	volatile unsigned long gier;//0 global interrupt enable register
	volatile unsigned long ipisr;//  4   ip interrupt status register
	volatile unsigned long rsv;//8
	volatile unsigned long ipier;//12  ip interrupt enable register
}ADCINTC_TypeDef;


typedef struct
{
	volatile unsigned long temperature;//0
	volatile unsigned long vccint;//4/
	volatile unsigned long vccaux;//8
	volatile unsigned long vp_vn;//12
	
	volatile unsigned long vrefp;//0
	volatile unsigned long vrefn;//4//
	volatile unsigned long vbram;//8
	volatile unsigned long rsv1;//12

	volatile unsigned long supply_offset;//0
	volatile unsigned long adcoffset;//4/
	volatile unsigned long gainerror;//8
	volatile unsigned long rsv2;//12

	volatile unsigned long rsv4;//0
	volatile unsigned long coresupply;//4/
	volatile unsigned long coreauxsupply;//8
	volatile unsigned long memorysupply;//12

	volatile unsigned long vauxpn0;//0
	volatile unsigned long vauxpn1;//4/
	volatile unsigned long vauxpn2;//8
	volatile unsigned long vauxpn3;//12

	volatile unsigned long vauxpn4;//0
	volatile unsigned long vauxpn5;//4/
	volatile unsigned long vauxpn6;//8
	volatile unsigned long vauxpn7;//12

	volatile unsigned long vauxpn8;//0
	volatile unsigned long vauxpn9;//4/
	volatile unsigned long vauxpn10;//8
	volatile unsigned long vauxpn11;//12

	volatile unsigned long vauxpn12;//0
	volatile unsigned long vauxpn13;//4/
	volatile unsigned long vauxpn14;//8
	volatile unsigned long vauxpn15;//12

	volatile unsigned long maxtemp;//0
	volatile unsigned long maxvccint;//4/
	volatile unsigned long maxvccaux;//8
	volatile unsigned long maxvbram;//12

	volatile unsigned long mintemp;//0
	volatile unsigned long minvccint;//4/
	volatile unsigned long minvccaux;//8
	volatile unsigned long minvbram;//12

	volatile unsigned long maxvccpint;//0
	volatile unsigned long maxvccpaux;//4/
	volatile unsigned long maxvccddro;//8
	volatile unsigned long rsv5;//12

	volatile unsigned long minvccpint;//0
	volatile unsigned long minvccpaux;//4/
	volatile unsigned long minvccddro;//8
	volatile unsigned long rsv6;//12

}ADCHard_TypeDef;

/** 
  * @brief  mypwm Handle Structure definition  
  */ 
typedef struct
{
  ADCLocal_TypeDef                 *Local_Instance;     /*!< Register base address             */
  ADCINTC_TypeDef                  *INTC_Instance;
  ADCHard_TypeDef                  *Hard_Instance;
  unsigned char irq_nr;
}ADC_HandleTypeDef;
extern ADC_HandleTypeDef adc_handle;

#endif
