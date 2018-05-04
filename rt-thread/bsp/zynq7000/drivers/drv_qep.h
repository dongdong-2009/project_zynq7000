#ifndef DRV_qep_H
#define DRV_qep_H

#include <rtthread.h>
#include "myqep.h"
#include "qep.h"



#define CMD_QEPEN 1
#define CMD_QEPDISABLE 2
#define CMD_QEPSETMOD 3
#define CMD_QEPSETPERIOD 4



#define QEP_DEFAULT_STATE 0


#define QEP_PERIOD (625 * 4 * 4)

extern Qep_HandleTypeDef qep;


#define RT_QEP_CONFIG_DEFAULT           \
{                                          \
    QEP_MOD3,      	\
    QEP_PERIOD,    	\
    QEP_DEFAULT_STATE,		\
}





#endif

