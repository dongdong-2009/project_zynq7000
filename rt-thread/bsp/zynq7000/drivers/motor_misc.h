
#ifndef MOTOR_MISC_H
#define MOTOR_MISC_H

#define CMD_MISC_INTENABLE 1
#define CMD_MISC_INTDISABLE 2
#define CMD_MISC_SET_BREAK_DUTY	3
#define CMD_MISC_SET_FAN_DUTY	4
#define CMD_MISC_BREAKEN 5
#define CMD_MISC_FANEN 6
#define CMD_MISC_READ_STATE 7
#define CMD_MISC_CLR_FLAG 8
#define CMD_MISC_SET_RLY 9
#define CMD_MISC_CLR_RLY 10


struct motor_misc_configure
{
	unsigned char pwmen;
	unsigned char fanen;
	unsigned char clrflag;
	unsigned int breakduty;
	unsigned int fanduty;
};





struct rt_motor_misc_device
{
    struct rt_device          parent;

    const struct rt_motor_misc_ops *ops;
    struct motor_misc_configure   config;

};
typedef struct rt_motor_misc_device rt_motor_misc_t;

struct rt_motor_misc_ops
{
    rt_err_t (*configure)(struct rt_motor_misc_device *motor_miscdev, struct motor_misc_configure *cfg);
    rt_err_t (*control)(struct rt_motor_misc_device *motor_miscdev, int cmd, void *arg);
    unsigned long (*getIntrState)(struct rt_motor_misc_device *serial);
};

#endif

