/*
	条件变量	
	条件变量允许线程挂起执行并释放已持有的互斥锁，等待某个条件变为真。条件变量总是需要与互斥锁一起使用，以避免出现竞态条件。
（2）用途
	允许线程等待特定条件的发生。当条件尚未满足时，线程通过条件变量等待，直到其他线程修改条件并通知条件变量。
	通知等待中的线程条件已改变，允许它们重新评估条件。
（3）操作
	初始化（pthread_cond_init）：创建并初始化条件变量。
	等待（pthread_cond_wait）：在给定的互斥锁上等待条件变量。调用时，线程将释放互斥锁并进入等待状态，直到被唤醒。
	定时等待（pthread_cond_timedwait）：等待条件变量或直到超过指定的时间。
	信号（pthread_cond_signal）：唤醒至少一个等待该条件变量的线程。
	广播（pthread_cond_broadcast）：唤醒所有等待该条件变量的线程。
	销毁（pthread_cond_destroy）：清理条件变量资源。

代码作用：可以看到producer线程生产数据，consumer线程消费数据，二者交替工作
*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

#define BUFFER_SIZE 5
int buffer[BUFFER_SIZE];
int count = 0;
// 初始化锁
static pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
// 初始化条件变量
static pthread_cond_t cond = PTHREAD_COND_INITIALIZER;
// 生产者线程
void *producer(void *arg)
{
    int item = 1;
    while (1)
    {
        // 获取互斥锁 拿不到等
        pthread_mutex_lock(&mutex);
        // 如果缓冲区满，等消费者读取
        while (count == BUFFER_SIZE)
        {
            // 暂停线程 等待唤醒
            pthread_cond_wait(&cond, &mutex);
        }
        // 能到这里说明缓冲区不满了 可以写一个
        buffer[count++] = item++;
        printf("白月光发送一个幸运数字%d\n", buffer[count - 1]);
        // 通知消费者可以消费数据了
        // 唤醒消费者 同时解锁
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
}
void *consumer(void *arg)
{
    while (1)
    {
        // 获取互斥锁 拿不到等
        pthread_mutex_lock(&mutex);
        // 如果缓冲区为空，则等待生产者生产数据
        while (count == 0)
        {
            // 暂停线程 等待唤醒
            pthread_cond_wait(&cond, &mutex);
        }
        printf("我收到了幸运数字 %d\n", buffer[--count]);
        // 通知生产者可以发送数据了
        // 唤醒生产者 同时解锁
        pthread_cond_signal(&cond);
        pthread_mutex_unlock(&mutex);
    }
}
int main()
{
    pthread_t producer_thread, consumer_thread;
    pthread_create(&producer_thread, NULL, producer, NULL);
    pthread_create(&consumer_thread, NULL, consumer, NULL);
    pthread_join(producer_thread, NULL);
    pthread_join(consumer_thread, NULL);
    return 0;
}
