#include <stdio.h>
#include "message_queue.h"

int main()
{
    int ret;
    struct MessageQueue queue;

    initMessageQueue(&queue);

    for(int i=0; i<4; i++)
    {
        do{ret = queue.ops.pushQueue(&queue, i);}
        while(ret != 0);
    }


    usleep(150000);

    for(int i=4; i<8; i++)
    {
        do{ret = queue.ops.pushQueue(&queue, i);}
        while(ret != 0);
    }

    usleep(150000);

    for(int i=8; i<16; i++)
    {
        do{ret = queue.ops.pushQueue(&queue, i);}
        while(ret != 0);
    }

    for(int i=16; i<32; i++)
    {
        do{ret = queue.ops.pushQueue(&queue, i);}
        while(ret != 0);
    }


    usleep(150000);

    for(int i=32; i<40; i++)
    {
        do{ret = queue.ops.pushQueue(&queue, i);}
        while(ret != 0);
    }
    usleep(150000);

    for(int i=40; i<60; i++)
    {
        do{ret = queue.ops.pushQueue(&queue, i);}
        while(ret != 0);
    }


    while(1);
    return 0;
}
