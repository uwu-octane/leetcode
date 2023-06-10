//
// Created by 陶挺 on 14.04.23.
//this is a learning follow writing from  https://subingwen.cn/linux/threadpool/

#ifndef CSIMPLETHREADPOOL_CSIMPLETHREADPOOL_H
#define CSIMPLETHREADPOOL_CSIMPLETHREADPOOL_H

#include <pthread.h>
#include <stdlib.h>
typedef struct Task{
    void (*function)(void* arg);
    void* arg;
}Task;

struct ThreadPool{
  Task* taskQueue;
  int queueCapacity;
  //current task number
  int queueSize;
  int queueFront;
  int queueRear;

  pthread_t managerID;
  pthread_t *threadIDs; //work threads

  int minThreadsNum;
  int maxThreadsNum;
  int workingThreadsNum;
  int liveThreadsNum;
  int threadsToExit; //over loaded threads should be destoryed;

  pthread_mutex_t poolMutex; // for the whole pool
  pthread_mutex_t workingThreadsNumMutex;
  pthread_cond_t isFull; // is taskqueue full
  pthread_cond_t isEmpty; // is taskqueue empty

  int shutdown; // destruct threadspool
};
typedef struct ThreadPool ThreadPool;
//creat and init threadpool
ThreadPool *init_ThreadPool(int minThreadsNum, int maxThreadsNum, int queueCapacity);

//destruct threadspool
int threadPoolDestroy(ThreadPool* pool);

//add task into the pool
void threadPoolAdd(ThreadPool* pool, void(*func)(void*), void* arg);

// get wroking threads num from the pool
int getBusyThreadNum(ThreadPool* pool);

// get alive threads num from the pool
int getLivingThreadNum(ThreadPool* pool);

_Noreturn void* worker(void* arg);
void* manager(void* arg);
void threadExit(ThreadPool* pool);
#endif //CSIMPLETHREADPOOL_CSIMPLETHREADPOOL_H
