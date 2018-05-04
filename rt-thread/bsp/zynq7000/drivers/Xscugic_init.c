#if 0
#include <rtthread.h>

#include "xscugic.h"
#include "userconf.h"

XScuGic ScuGic1_InstancePtr;

int Xscugic_init(void)
{
	int result;
	XScuGic_Config *XScuGic_Config;
	XScuGic_Config = XScuGic_LookupConfig(XPAR_PS7_SCUGIC_0_DEVICE_ID);

	ScuGic1_InstancePtr.IsReady = 0;

	result = XScuGic_CfgInitialize(&ScuGic1_InstancePtr,XScuGic_Config,XScuGic_Config->CpuBaseAddress);
	return result;
}
INIT_BOARD_EXPORT(Xscugic_init);
#endif 
