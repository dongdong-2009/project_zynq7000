#ifndef USR_DOCURRENTCTRL_H
#define USR_DOCURRENTCTRL_H
#define DOCURRENTCTRL_DEV0 (0x43c60000)
#define DEV0 (0)

#define XPAR_XCTRL_DOCURRENTCTRL_NUM_INSTANCES (1)


typedef union din_u{
	float f;
	unsigned int d;
} din;
typedef union dout_u{
	float f;
	unsigned int d;
} dout;

typedef union datatype_u{
	float f;
	unsigned int d;
} datatype;



typedef struct CurrentCtrl_din {
din iqref;
din idref;
din udc;
din ttop;
din ia;
din ib;
din ic;
din theta;
din kp_id;
din ki_id;
din id_pidmax;
din id_pidmin;
din kp_iq;
din ki_iq;
din iq_pidmax;
din iq_pidmin;
din ud;
din uq;
unsigned int mod;
} CurrentCtrl_din_type;

typedef struct CurrentCtrl_dout {
dout ta;
dout tb;
dout tc;

dout out_ud;
dout out_uq;
} CurrentCtrl_dout_type;

#endif
