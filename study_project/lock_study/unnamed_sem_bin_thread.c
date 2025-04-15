/*
无名信号量
	信号量本质上是一个非负整数变量，可以被用来控制对共享资源的访问。它主要用于两种目的：互斥和同步。
	（1）互斥（Mutex）：确保多个进程或线程不会同时访问临界区（即访问共享资源的代码区域）。
	（2）同步（Synchronization）：协调多个进程或线程的执行顺序，确保它们按照一定的顺序执行。

	基于不同的目的，信号量可以分为两类：用于实现互斥的“二进制信号量”和用于同步的“计数信号量”。
	（1）二进制信号量（或称作互斥锁）：其值只能是0或1，主要用于实现互斥，即一次只允许一个线程进入临界区。
	通常用于控制共享资源的访问，避免竞态条件的产生。
	（2）计数信号量：其值可以是任意非负整数，表示可用资源的数量。计数信号量允许多个线程根据可用资源的数量进入临界区。
	通常用于控制不同进程或线程执行的顺序，如消费者必须在生产者发送数据后才可以消费。

（1）无名信号量
	无名信号量不是通过名称标识，而是直接通过sem_t结构的内存位置标识。无名信号量在使用前需要初始化，
	在不再需要时应该销毁。它们不需要像有名信号量那样进行创建和链接，因此设置起来更快，运行效率也更高。


	在这里，我们通过二进制信号量起到了互斥锁的作用，避免了线程间的竞态条件

*/

#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <pthread.h>

sem_t unnamed_sem;
int shard_num = 0;

void *plusOne(void *argv) {
    sem_wait(&unnamed_sem);
    int tmp = shard_num + 1;
    shard_num = tmp;
    sem_post(&unnamed_sem);
}

int main() {
    sem_init(&unnamed_sem, 0, 1);

    pthread_t tid[10000];
    for (int i = 0; i < 10000; i++) {
        pthread_create(tid + i, NULL, plusOne, NULL);
    }

    for (int i = 0; i < 10000; i++) {
        pthread_join(tid[i], NULL);
    }
    
    printf("shard_num is %d\n", shard_num);

    sem_destroy(&unnamed_sem);

    return 0;
}
