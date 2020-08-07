#include "message_queue.h"



void stopMessageQueue()
{

}



void *queueThread(void *Arg)
{

    struct MessageQueue *queue = (struct MessageQueue *) Arg;

    printf("Queue Thread is started!\n");
    int *ptr;

    usleep(50000);


    while(1)
    {
        ptr = queue->ops.popQueue(queue);
        if(ptr != NULL)
        {
            printf("\033[1;33m"); //Set the text to
            printf("Queue Value: %d - stack ptr: %d base ptr: %d - stack_loop: %d - base_loop: %d \n",
                   *ptr, queue->stack_ptr, queue->base_ptr, queue->stack_loop, queue->base_loop);
            usleep(50000);
        }
    }
}



int *popQueue(struct MessageQueue *Queue)
{
    int *message;

    if((Queue->stack_ptr + Queue->stack_loop * TOTAL_QUEUE) == (Queue->base_ptr + Queue->base_loop * TOTAL_QUEUE))
    {
        return NULL;
    }
    else
    {

        printf("diffirence %d\n", (Queue->stack_ptr + Queue->stack_loop * TOTAL_QUEUE) - (Queue->base_ptr + Queue->base_loop * TOTAL_QUEUE));

        message = &Queue->messages[Queue->base_ptr++];


        if(Queue->base_ptr >= TOTAL_QUEUE)
        {
            Queue->base_loop++;
            Queue->base_ptr = 0;
        }

        return message;
    }

}



int pushQueue(struct MessageQueue *Queue, int Message)
{
    if(Queue->stack_ptr > TOTAL_QUEUE - 1)
    {
        Queue->stack_loop++;
        Queue->stack_ptr = 0;

        if(Queue->stack_loop == TOTAL_QUEUE)
        {
            printf("stack_loop is overflowed... \n");

            Queue->stack_loop = Queue->stack_loop - Queue->base_loop;
            Queue->base_loop = 0;
        }

    }

    if((Queue->base_loop < Queue->stack_loop) &&
            Queue->stack_ptr >= Queue->base_ptr)
    {
        printf("Queue is full. Wait sometime\n");
        usleep(50000);
        return -1;
    }





    printf("\033[1;31m"); //Set the text to
    printf("pushed value: %d, stack ptr: %d base ptr: %d - stack_loop: %d - base_loop: %d \n",
           Message, Queue->stack_ptr, Queue->base_ptr, Queue->stack_loop, Queue->base_loop);

    memcpy(&Queue->messages[Queue->stack_ptr++], &Message, sizeof(int));

    return 0;

}



void initMessageQueue(struct MessageQueue *Queue)
{

    Queue->ops.pushQueue = pushQueue;
    Queue->ops.popQueue = popQueue;

    pthread_t thread_id;

    Queue->stack_ptr = 0;
    Queue->base_ptr = 0;
    Queue->stack_loop = 0;
    Queue->base_loop = 0;


    pthread_create(&thread_id, NULL, queueThread, Queue);

}
