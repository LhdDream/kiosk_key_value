//
// Created by kiosk on 19-8-15.
//

#ifndef MY_REDIES_STATE_H
#define MY_REDIES_STATE_H
//字典的操作状态
#define DICT_OK 0
#define DICT_ERR 1
/*
 * 事件执行状态
 */
// 成功
#define AE_OK 0
// 出错
#define AE_ERR -1

/*
 * 文件事件状态
 */
// 未设置
#define AE_NONE 0
// 可读
#define AE_READABLE 1
// 可写
#define AE_WRITABLE 2

/*
 * 时间处理器的执行 flags
 */
// 文件事件
#define AE_FILE_EVENTS 1
// 时间事件
#define AE_TIME_EVENTS 2
// 所有事件
#define AE_ALL_EVENTS (AE_FILE_EVENTS|AE_TIME_EVENTS)
// 不阻塞，也不进行等待
#define AE_DONT_WAIT 4

/*
 * 决定时间事件是否要持续执行的 flag
 */
#define AE_NOMORE -1

/* Macros */
#define AE_NOTUSED(V) ((void) V)

#define ANET_OK         0
#define ANET_ERR        -1
#define ANET_ERR_LEN    256

/* Flags used with certain functions. */
#define ANET_NONE       0
#define ANET_IP_ONLY    (1<<0)
#endif //MY_REDIES_STATE_H
