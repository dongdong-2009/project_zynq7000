
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


struct sharemem_configure
{
	unsigned int readposition;
	unsigned int writeposition;
	unsigned int maxlength;
	
	unsigned int readbuff_readposition;
	unsigned int readbuff_writeposition;
	unsigned int readbuff_maxlength;
};





struct rt_sharemem_device
{
    struct rt_device          parent;

    const struct rt_sharemem_ops *ops;
	
    struct sharemem_configure   config;

};
typedef struct rt_sharemem_device rt_sharemem_t;

struct rt_sharemem_ops
{
    rt_err_t (*configure)(struct rt_sharemem_device *sharememdev, struct sharemem_configure *cfg);
	rt_err_t (*writemem)(struct rt_sharemem_device *sharememdev, char * data,int size);
	rt_err_t (*readmem)(struct rt_sharemem_device *sharememdev, char * buff,int size);
    //rt_err_t (*control)(struct rt_sharemem_device *sharememdev, int cmd, void *arg);
    //unsigned long (*getIntrState)(struct rt_sharemem_device *serial);
};

#endif

