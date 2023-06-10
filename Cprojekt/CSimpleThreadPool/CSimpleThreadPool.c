//
// Created by 陶挺 on 14.04.23.
//

#include <printf.h>
#include <string.h>
#include <libc.h>
#include "CSimpleThreadPool.h"

const int  NUMBER = 2;

ThreadPool *init_ThreadPool(int minThreadsNum, int maxThreadsNum, int queueCapacity){
    ThreadPool* pool =(ThreadPool*) malloc(sizeof(ThreadPool));
    do{
        if(pool == NULL){
            printf("malloc pool faile\n");
            // we could use break in this while, and set while(0) so it wont loop
            //return NULL;
            break;
        }

        //define the array to store threads
        pool->maxThreadsNum = maxThreadsNum;
        pool->minThreadsNum = minThreadsNum;
        pool->queueCapacity = queueCapacity;
        pool->workingThreadsNum = 0;
        pool->liveThreadsNum = minThreadsNum;
        pool->threadsToExit = 0;

        pool->threadIDs = (pthread_t*)malloc(sizeof (pthread_t) * maxThreadsNum);
        if(pool->threadIDs == NULL){
            printf("malloc threadIDs failed\n");
            break;
        }

        //memset init this buffer to 0
        memset(pool->threadIDs,0,sizeof(pthread_t)*maxThreadsNum);

        if(pthread_mutex_init(&pool->poolMutex, NULL) != 0||pthread_mutex_init(&pool->workingThreadsNumMutex, NULL) != 0
           ||pthread_cond_init(&pool->isEmpty, NULL) != 0 || pthread_cond_init(&pool->isFull,NULL) != 0){
            printf("init mutex falied");
            break;
        }

        //tasks queue
        /*通过使用malloc函数动态分配了一块内存空间来存储任务队列，也就是为taskQueue指针分配了一块连续的内存，
         * 使其指向一个Task类型的数组。这样，taskQueue就可以被视为一个数组，可以通过索引访问其中的元素。*/
        pool->taskQueue = (Task*)malloc(sizeof(Task) * queueCapacity);
        pool->queueSize = 0;
        pool->queueFront = 0;
        pool->queueRear = 0;

        pool->shutdown = 0;

        //init threads
        if(pthread_create(&pool->managerID,NULL,manager,pool) != 0){
            printf("manager thread creation falied");
            break;
        }
        for(int i = 0; i < minThreadsNum; i++){
            if(pthread_create(&pool->threadIDs[i], NULL, worker,pool)!=0){
                printf("working thred creation falied");
                break;
            }
        }

        return pool;
    }while(0);

    //if while breaks, we have to free the memories
    if(pool->threadIDs) free(pool->threadIDs);
    if(pool->taskQueue) free(pool->taskQueue);
    if(pool) free(pool);

    return NULL;
}

_Noreturn void* worker(void* arg){
    //cast arg to pool
    ThreadPool* pool = (ThreadPool*) arg;
    while(1){
        //every worker will reach pool to get task so pool is critical resource
        pthread_mutex_lock(&pool->poolMutex);
        //if queue is empty
        while(pool->queueSize == 0 && !pool->shutdown){
            //let the worker sleep
            //pthread_cond_wait的使用步骤如下：
            /*在等待条件之前，使用pthread_mutex_lock函数锁定互斥锁。
             * 调用pthread_cond_wait函数，它会释放互斥锁并将线程置于阻塞状态，直到接收到与条件变量相关的信号。
             * 一旦接收到信号，线程将被唤醒，并再次获取互斥锁。
             * 当线程重新获取到互斥锁时，它可以继续执行后续操作。*/
            pthread_cond_wait(&pool->isEmpty,&pool->poolMutex);

            //check if the thread should be killed
            if(pool->threadsToExit > 0){
                pool->threadsToExit--;
                if(pool->liveThreadsNum>pool->minThreadsNum){
                pool->liveThreadsNum--;
                }
                //watch out to unlock because cond_wait will get the lock
                pthread_mutex_unlock(&pool->poolMutex);
                threadExit(pool);
            }
        }

        //check if pool still open
        if(pool->shutdown){
            pthread_mutex_unlock(&pool->poolMutex);
            threadExit(pool);
        }

        //take a task
        Task task;
        task.function = pool->taskQueue[pool->queueFront].function;
        task.arg = pool->taskQueue[pool->queueFront].arg;

        //move qFront
        pool->queueFront = (pool->queueFront + 1) % pool->queueCapacity;
        pool->queueSize--;

        pthread_mutex_unlock(&pool->poolMutex);

        //busy thread couting
        pthread_mutex_lock(&pool->workingThreadsNumMutex);
        printf("thread %ld start working..\n");
        pool->workingThreadsNum++;
        pthread_mutex_unlock(&pool->workingThreadsNumMutex);

        task.function(task.arg);
        //通过在函数指针前加上解引用操作符*，可以调用函数。
        // (*task.function)(task.arg);
        free(task.arg);
        task.arg = NULL;

        //busy thread couting
        pthread_mutex_lock(&pool->workingThreadsNumMutex);
        printf("thread %ld end working..\n");
        pool->workingThreadsNum--;
        pthread_mutex_unlock(&pool->workingThreadsNumMutex);

    }
    return  NULL;
}


void* manager(void* arg){
    ThreadPool* pool = (ThreadPool*) arg;
    while(!pool->shutdown){
        //check every 3 sec
        sleep(3);

        // get the tasknum and threadnum in pool
        pthread_mutex_lock(&pool->poolMutex);
        int queueSize = pool->queueSize;
        int liveNum = pool->liveThreadsNum;
        int busyNum = pool->workingThreadsNum;

        //creat more thread
        //taskNum > living thread && living thread < max threadNum
        if(queueSize > liveNum && liveNum < pool->maxThreadsNum){
            int counter = 0;
            for(int i = 0; i < pool->maxThreadsNum && counter < NUMBER && pool->liveThreadsNum < pool->maxThreadsNum; ++i){
                if(pool->threadIDs[i] == 0){
                    pthread_create(&pool->threadIDs[i], NULL,worker,pool);
                    counter++;
                    pool->liveThreadsNum++;
                }
            }
        }

        //kill threads
        //busy threads *2 < living threads && living thread > min threadNum
        if(busyNum*2 < liveNum && liveNum > pool->minThreadsNum){
            pool->threadsToExit = NUMBER;

            // let free threads suicide (haha manager)
            for(int i = 0; i < NUMBER;++i){
                pthread_cond_signal(&pool->isEmpty);
            }
        }
        pthread_mutex_unlock(&pool->poolMutex);

        //get busing threadnum
        /*
        pthread_mutex_lock(&pool->workingThreadsNumMutex);
        int busyNum = pool->workingThreadsNum;
        pthread_mutex_unlock(&pool->workingThreadsNumMutex);*/
    }
    return NULL;
}

void threadExit(ThreadPool* pool){
    pthread_t tid = pthread_self();
    for(int i = 0; i < pool->maxThreadsNum;++i){
        if(pool->threadIDs[i] == tid){
            pool->threadIDs[i] = 0;
            printf("threadExit() called, %ld exiting...\n", tid);
            break;
        }
        pthread_exit(NULL);
    }
}