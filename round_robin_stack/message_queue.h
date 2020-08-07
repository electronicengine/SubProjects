#ifndef __message_queue_H
#define __message_queue_H


#include <inttypes.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <memory.h>
#include <pthread.h>


#define TOTAL_QUEUE 10
#define container_of(ptr, type, member) \
    ((type *)((char *)(ptr)-(unsigned long)(&((type *)0)->member)))



struct MessageQueue;

struct MessageQueueOperations
{

    void (*stopMessageQueue)();
    int *(*popQueue)(struct MessageQueue *Queue);
    int (*pushQueue)(struct MessageQueue *Queue, int Message);


};



struct MessageQueue
{

    struct MessageQueueOperations ops;

    int messages[TOTAL_QUEUE];
    volatile uint8_t stack_ptr;
    volatile uint8_t base_ptr;

    volatile uint8_t stack_loop;
    volatile uint8_t base_loop;

};


void initMessageQueue(struct MessageQueue *Queue);
void deinitMessageQueue(struct MessageQueue *Queue);


#endif
