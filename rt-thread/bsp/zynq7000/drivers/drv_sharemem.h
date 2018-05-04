#ifndef DRV_SHAREMEM_H
#define DRV_SHAREMEM_H

#include <rtthread.h>
#include "sharemem.h"


#define SHAREMEMHEAD_BASEADDR 0xFFFF0000
#define SHAREMEM_READSTART (0)
#define SHAREMEM_WRITESTART (0)
#define SHAREMEM_MAXLENGTH (0x6000)

#define READBUFF_SHAREMEM_READSTART (0)
#define READBUFF_SHAREMEM_WRITESTART (0)
#define READBUFF_SHAREMEM_MAXLENGTH (0x6000)


//#define CPU1_IRQF2P0_ID 61

typedef struct sharememhead
{
	unsigned int readposition;
	unsigned int writeposition;
	unsigned int maxlength;//0x6000

	unsigned int readbuff_readposition;
	unsigned int readbuff_writeposition;
	unsigned int readbuff_maxlength;
}sharememhead_TyepDef;






typedef struct monitor_msg
{			  
	char head;//0x5a
	short int timer;	
	int speed_cnt;
	short int v1;
	short int v2;	
	short int v3;	
	short int v4;	
	short int v5;	
	short int v6;	
	short int v7;	
	short int v8;	
	char check;
}MonitorMsg_TypeDef;//24BYTE

/** 
  * @brief  mypwm Handle Structure definition  
  */ 
typedef struct
{
  sharememhead_TyepDef  *Local_Instance;     /*!< Register base address             */
  unsigned char irq_nr;
}ShareMem_HandleTypeDef;
extern ShareMem_HandleTypeDef sharemem_handle;

#define RT_SHAREMEM_CONFIG_DEFAULT           \
{                                          	\
    SHAREMEM_READSTART,      					\
    SHAREMEM_WRITESTART,    						\
    SHAREMEM_MAXLENGTH,						\
    READBUFF_SHAREMEM_READSTART,						\
    READBUFF_SHAREMEM_WRITESTART,						\
    READBUFF_SHAREMEM_MAXLENGTH,						\
}



#endif

