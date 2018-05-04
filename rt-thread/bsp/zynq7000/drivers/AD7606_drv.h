#ifndef AD7606_DRV_H
#define AD7606_DRV_H

#include <rtthread.h>
#include "adc.h"




#define ADC_LOCAL_BASEADDR (0x43c00000)

#define CPU1_IRQ_ID 31
#define CPU1_FIQ_ID 28


#define GIEINTR 0x80000000
#define EOSINTR 0x10
#define OVERSAMPLE_0 0
#define OVERSAMPLE_2 1
#define OVERSAMPLE_4 2
#define OVERSAMPLE_8 3
#define OVERSAMPLE_16 4
#define OVERSAMPLE_32 5
#define OVERSAMPLE_64 6


#define RT_ADC_CONFIG_DEFAULT           \
{                                          \
}

struct ctrl_def
{
	int ad_rst : 1;//1:rst
	int intr_time : 1;
	int ad_os : 3;
	int convst: 1;
	int rsv1: 2;
	int rsv2: 8;
	int rsv3: 8;
	int rsv4: 7;
	int intr_clr :1;
};

typedef struct
{
	volatile unsigned long data1_reg; //0
	volatile unsigned long data2_reg; //4//
	volatile unsigned long data3_reg; //8
	volatile unsigned long data4_reg; //12
	volatile unsigned long data5_reg; //16
	volatile unsigned long data6_reg; //20
	volatile unsigned long data7_reg; //24
	volatile unsigned long data8_reg; //28
	volatile struct ctrl_def ctrl_reg; //32  bit0: ad_rst, bit1: intr time, bit2-bit4: ad_os, bit5: start a convst, bit31:1, clear data ready  
	volatile unsigned long state_reg;  //36 bit0: 1, data is ready;
}ADCLocal_TypeDef;



/** 
  * @brief  mypwm Handle Structure definition  
  */ 
typedef struct
{
  ADCLocal_TypeDef                 *Local_Instance;     /*!< Register base address             */
  unsigned char irq_nr;
}ADC_HandleTypeDef;
extern ADC_HandleTypeDef adc_handle;

#endif

