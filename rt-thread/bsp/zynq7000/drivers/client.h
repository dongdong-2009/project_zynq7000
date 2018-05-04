#ifndef CLIENT_H
#define CLIENT_H


typedef float float_t;
typedef union data{
float_t f;
unsigned int d;
} motorgui_datatype;

typedef struct d_monitor {
	char start0;/*0xff*/
	char start1;/*0x00*/
    motorgui_datatype ia;
    motorgui_datatype ib;
    motorgui_datatype ic;
    motorgui_datatype spd;
    motorgui_datatype time;
    motorgui_datatype check;
	char end1;/*0x22*/
	char end0;/*0x11*/
} d_monitor_type;

typedef struct d_input {
    int cmd;
} d_input_type;

#endif