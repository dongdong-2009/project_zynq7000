

/***************************** Include Files *******************************/
#include "myqep.h"


int qep_read_cnt(Qep_HandleTypeDef *qep_handle)
{
	if(qep_handle == NULL)
	{
		return MYIP_ERROR;
	}
	return qep_handle->Instance->cnt_eg;
}

int qep_read_turn(Qep_HandleTypeDef *qep_handle)
{
	if(qep_handle == NULL)
	{
		return MYIP_ERROR;
	}

	return qep_handle->Instance->turn_cnt_reg;
}

int qep_set_period(Qep_HandleTypeDef *qep_handle,unsigned int period)
{
	if(qep_handle == NULL)
	{
		return MYIP_ERROR;
	}
	if(qep_handle->state == MYIP_STATE_READY)
	{
		qep_handle->state = MYIP_STATE_BUSY;
		
		qep_handle->Instance->turn_reg = period;
		qep_handle->state = MYIP_STATE_READY;
		return MYIP_SUCCESS;
	}
	return MYIP_BUSY;
}

int qep_enable(Qep_HandleTypeDef *qep_handle)
{
	unsigned int temp;

	if(qep_handle == NULL)
	{
		return MYIP_ERROR;
	}
	if(qep_handle->state == MYIP_STATE_READY)
	{
		qep_handle->state = MYIP_STATE_BUSY;
		temp = qep_handle->Instance->ctrl_reg;
		temp |= 0x80000000;
		qep_handle->Instance->ctrl_reg = temp;
		qep_handle->state = MYIP_STATE_READY;
		return MYIP_SUCCESS;
	}
	return MYIP_BUSY;
		
}

unsigned char qep_disable(Qep_HandleTypeDef *qep_handle)
{
	unsigned int temp;

	if(qep_handle == NULL)
	{
		return MYIP_ERROR;
	}
	if(qep_handle->state == MYIP_STATE_READY)
	{
		qep_handle->state = MYIP_STATE_BUSY;
		temp = qep_handle->Instance->ctrl_reg;
		temp &= 0x7fffffff;
		qep_handle->Instance->ctrl_reg = temp;
		qep_handle->state = MYIP_STATE_READY;
		return MYIP_SUCCESS;
	}
	return MYIP_BUSY;
}

int qep_set_mode(Qep_HandleTypeDef *qep_handle, unsigned int mod)
{
	unsigned int temp;

	if(qep_handle == NULL)
	{
		return MYIP_ERROR;
	}
	
	if(mod != QEP_MOD1 && mod != QEP_MOD2 && mod != QEP_MOD3)
	{
		return MYIP_ERROR;
	}

	
	if(qep_handle->state == MYIP_STATE_READY)
	{
		qep_handle->state = MYIP_STATE_BUSY;
		temp = qep_handle->Instance->ctrl_reg;
		temp &= 0xfffffffc;
		temp |= mod;
		qep_handle->Instance->ctrl_reg = temp;
		qep_handle->state = MYIP_STATE_READY;
		return MYIP_SUCCESS;
	}
	return MYIP_BUSY;
}

extern char QEP_Init(Qep_HandleTypeDef *qep_handle)
{
	if(qep_handle == NULL)
	{
		return MYIP_ERROR;
	}
	if(qep_handle->state == MYIP_STATE_RESET)
	{
		QEP_MSP_Init(qep_handle);
		qep_handle->state = MYIP_STATE_READY;
	}
	while(qep_disable(qep_handle) != MYIP_SUCCESS);
	while(qep_set_period( qep_handle,qep_handle->init.period) != MYIP_SUCCESS);
	while(qep_set_mode( qep_handle,qep_handle->init.mod) != MYIP_SUCCESS);
	if(qep_handle->init.qepstate == 1)
		while(qep_enable(qep_handle) != MYIP_SUCCESS);
	else
		while(qep_disable(qep_handle) != MYIP_SUCCESS);
		
	return MYIP_SUCCESS;
}


/************************** Function Definitions ***************************/
