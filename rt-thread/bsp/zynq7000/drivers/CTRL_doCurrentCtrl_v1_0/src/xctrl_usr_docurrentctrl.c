#include "xstatus.h"
#include "xparameters.h"
#include "xctrl_docurrentctrl.h"
#include "xctrl_usr_docurrentctrl.h"
#include <rtthread.h>

XCtrl_docurrentctrl_Config XCtrl_docurrentctrl_ConfigTable[] = {{DEV0,DOCURRENTCTRL_DEV0}};

void Init_doCurrentCtrl(XCtrl_docurrentctrl *InstancePtr)
{
	XCtrl_docurrentctrl_Initialize(InstancePtr,DEV0);
}

void Run_doCurrentCtrl(XCtrl_docurrentctrl *InstancePtr,CurrentCtrl_din_type *in, CurrentCtrl_dout_type *t)
{
	XCtrl_docurrentctrl_Start(InstancePtr);
	while(XCtrl_docurrentctrl_IsReady(InstancePtr) == 1);


	XCtrl_docurrentctrl_Set_in_f_iqref(InstancePtr, in->iqref.d);
	XCtrl_docurrentctrl_Set_in_f_idref(InstancePtr, in->idref.d);
	XCtrl_docurrentctrl_Set_in_f_udc(InstancePtr, in->udc.d) ;
	XCtrl_docurrentctrl_Set_in_f_ttop(InstancePtr, in->ttop.d);
	XCtrl_docurrentctrl_Set_in_f_ia(InstancePtr, in->ia.d) ;
	XCtrl_docurrentctrl_Set_in_f_ib(InstancePtr, in->ib.d);
	XCtrl_docurrentctrl_Set_in_f_ic(InstancePtr, in->ic.d) ;
	XCtrl_docurrentctrl_Set_in_f_theta(InstancePtr, in->theta.d) ;
	XCtrl_docurrentctrl_Set_in_f_kp_id(InstancePtr, in->kp_id.d) ;
	XCtrl_docurrentctrl_Set_in_f_ki_id(InstancePtr, in->ki_id.d);
	XCtrl_docurrentctrl_Set_in_f_id_pidmax(InstancePtr, in->id_pidmax.d) ;
	XCtrl_docurrentctrl_Set_in_f_id_pidmin(InstancePtr, in->id_pidmin.d);
	XCtrl_docurrentctrl_Set_in_f_kp_iq(InstancePtr, in->kp_iq.d) ;
	XCtrl_docurrentctrl_Set_in_f_ki_iq(InstancePtr, in->ki_iq.d);
	XCtrl_docurrentctrl_Set_in_f_iq_pidmax(InstancePtr, in->iq_pidmax.d); 
	XCtrl_docurrentctrl_Set_in_f_iq_pidmin(InstancePtr, in->iq_pidmin.d) ;
	//rt_kprintf("ia:%x,ib:%x,ic:%x\r\n",XCtrl_docurrentctrl_Get_in_ia(InstancePtr),XCtrl_docurrentctrl_Get_in_ib(InstancePtr),XCtrl_docurrentctrl_Get_in_ic(InstancePtr));
#if 1
	XCtrl_docurrentctrl_Set_in_f_ud(InstancePtr, in->ud.d) ;
	XCtrl_docurrentctrl_Set_in_f_uq(InstancePtr, in->uq.d) ;
	XCtrl_docurrentctrl_Set_in_f_mod(InstancePtr, in->mod) ;
#endif

	while(XCtrl_docurrentctrl_IsDone(InstancePtr) == 0);
	
	while(XCtrl_docurrentctrl_Get_t_f_ta_vld(InstancePtr)== 0);
	t->ta.d = XCtrl_docurrentctrl_Get_t_f_ta(InstancePtr);
	
	while(XCtrl_docurrentctrl_Get_t_f_tb_vld(InstancePtr) == 0);
	t->tb.d = XCtrl_docurrentctrl_Get_t_f_tb(InstancePtr);
	
	while(XCtrl_docurrentctrl_Get_t_f_tc_vld(InstancePtr) == 0);
	t->tc.d = XCtrl_docurrentctrl_Get_t_f_tc(InstancePtr);

#if 1
	while(XCtrl_docurrentctrl_Get_t_f_ud_out_vld(InstancePtr) == 0);
	t->out_ud.d = XCtrl_docurrentctrl_Get_t_f_ud_out(InstancePtr);

	while(XCtrl_docurrentctrl_Get_t_f_uq_out_vld(InstancePtr) == 0);
	t->out_uq.d = XCtrl_docurrentctrl_Get_t_f_uq_out(InstancePtr);
#endif

}
