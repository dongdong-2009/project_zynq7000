
#ifndef MYQEP_H
#define MYQEP_H


/****************** Include Files ********************/
#include "xil_types.h"
#include "xstatus.h"
#include "myip.h"

#define MYQEP_BASEADDR 0x43c30000
#define MYQEP_CNT_REG 0
#define MYQEP_TURN_REG 4
#define MYQEP_CTRL_REG 8
#define MYQEP_TURN_CNT_REG 12
#define QEP_MOD1 (0x00000001)
#define QEP_MOD2 (0x00000002)
#define QEP_MOD3 (0x00000003)

typedef struct
{
	volatile unsigned long cnt_eg;//0
	volatile unsigned long turn_reg;//4/
	volatile unsigned long ctrl_reg;//8
	volatile unsigned long turn_cnt_reg;//12
}Qep_TypeDef;

typedef struct
{
	unsigned int mod;  
	unsigned int period;
	unsigned int qepstate;
}QEP_Base_InitTypeDef;


typedef struct
{
  Qep_TypeDef                 *Instance;     /*!< Register base address             */
  QEP_Base_InitTypeDef  init;
  unsigned int state;
}Qep_HandleTypeDef;


/**************************** Type Definitions *****************************/
/**
 *
 * Write a value to a MYQEP register. A 32 bit write is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is written.
 *
 * @param   BaseAddress is the base address of the MYQEPdevice.
 * @param   RegOffset is the register offset from the base to write to.
 * @param   Data is the data written to the register.
 *
 * @return  None.
 *
 * @note
 * C-style signature:
 * 	void MYQEP_mWriteReg(u32 BaseAddress, unsigned RegOffset, u32 Data)
 *
 */
#define MYQEP_mWriteReg(BaseAddress, RegOffset, Data) \
  	Xil_Out32((BaseAddress) + (RegOffset), (u32)(Data))

/**
 *
 * Read a value from a MYQEP register. A 32 bit read is performed.
 * If the component is implemented in a smaller width, only the least
 * significant data is read from the register. The most significant data
 * will be read as 0.
 *
 * @param   BaseAddress is the base address of the MYQEP device.
 * @param   RegOffset is the register offset from the base to write to.
 *
 * @return  Data is the data from the register.
 *
 * @note
 * C-style signature:
 * 	u32 MYQEP_mReadReg(u32 BaseAddress, unsigned RegOffset)
 *
 */
#define MYQEP_mReadReg(BaseAddress, RegOffset) \
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
 * @param   baseaddr_p is the base address of the MYQEP instance to be worked on.
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
XStatus MYQEP_Reg_SelfTest(void * baseaddr_p);

#endif // MYQEP_H
