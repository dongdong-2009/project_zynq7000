#ifndef QEP_H
#define QEP_H

struct qep_configure
{
    rt_uint32_t mod;
	rt_uint32_t period;
	rt_uint32_t qepstate;
};

struct Qep_Value
{
	rt_uint32_t turn;
	int cnt;
};

typedef struct Qep_Value Qep_ValueTypeDef;




struct rt_qep_device
{
    struct rt_device          parent;

    const struct rt_qep_ops *ops;
    struct qep_configure   config;

};
typedef struct rt_qep_device rt_qep_t;

struct rt_qep_ops
{
    rt_err_t (*configure)(struct rt_qep_device *qep, struct qep_configure *cfg);
    rt_err_t (*control)(struct rt_qep_device *qep, int cmd, void *arg);
    Qep_ValueTypeDef (*getQepValue)(struct rt_qep_device *qep);
};

#endif

