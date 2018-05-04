
#ifndef PWM_H
#define PWM_H

struct pwm_configure
{
    rt_uint32_t clk_hz;
    rt_uint32_t deadzone_ns;
    rt_uint32_t pwm0_duty;
    rt_uint32_t pwm1_duty;
    rt_uint32_t pwm2_duty;
};



struct rt_pwm_device
{
    struct rt_device          parent;

    const struct rt_pwm_ops *ops;
    struct pwm_configure   config;

};
typedef struct rt_pwm_device rt_pwm_t;


struct rt_pwm_ops
{
    rt_err_t (*configure)(struct rt_pwm_device *pwm, struct pwm_configure *cfg);
    rt_err_t (*control)(struct rt_pwm_device *pwm, int cmd, void *arg);
};

#endif
