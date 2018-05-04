
#ifndef ADC_H
#define ADC_H
#define CMD_INTENABLE 1
#define CMD_INTDISABLE 2
#define CMD_RST	3
#define CMD_CFG	4
#define CMD_CONVST 5



typedef struct 
{
	signed short qI1_value;
	unsigned short qI1_offset;
	signed short qI2_value;
	unsigned short qI2_offset;
	signed short qI_value;
	signed short qV_value;
	unsigned short qV_offset;
} QIEMW_Phase;

typedef struct 
{
	signed short TEMP_value;
	unsigned short TEMP_offset;
	signed short FANTEMP_value;
	unsigned short FANTEMP_offset;
} QIEMW_Temp;

typedef struct 
{
	signed short qI_value;
	unsigned short qI_offset;
	signed short qV_value;
	unsigned short qV_offset;
} QIEMW_Bus;


/** 
  * @brief  ADC handle Structure definition
  */ 
typedef struct
{
	QIEMW_Phase PhaseA;
	QIEMW_Phase PhaseB;
	QIEMW_Phase PhaseC;
	QIEMW_Bus BUS;
	QIEMW_Phase UR;
	QIEMW_Phase US;
	QIEMW_Phase UT;
	QIEMW_Temp Temp;
} QIEMW_ADC_HandleTypeDef;


struct adc_configure
{
};





struct rt_adc_device
{
    struct rt_device          parent;

    const struct rt_adc_ops *ops;
    struct adc_configure   config;

};
typedef struct rt_adc_device rt_adc_t;

struct rt_adc_ops
{
    rt_err_t (*configure)(struct rt_adc_device *adcdev, struct adc_configure *cfg);
    rt_err_t (*control)(struct rt_adc_device *adcdev, int cmd, void *arg);
    QIEMW_ADC_HandleTypeDef (*getAdcValue)(struct rt_adc_device *serial);
};

#endif

