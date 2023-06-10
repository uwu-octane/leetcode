#include <stdio.h>
#include <unistd.h>
#include "CSimpleThreadPool.h"
#include "pthread.h"

void taskFunc(void* arg){
    int num = *(int*) arg;
    printf("thread %ld is working, number = %d\n",pthread_self(),num);
    sleep(2);
}
int main() {
    ThreadPool * pool = init_ThreadPool(3,10,100);
    for(int i = 0; i <100; ++i){
        int* num = (int*)malloc(sizeof(int));
        *num = i + 100;
        threadPoolAdd(pool,taskFunc,num);
    }
    sleep(10);
    threadPoolDestroy(pool);
    return 0;
}
