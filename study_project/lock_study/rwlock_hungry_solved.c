/*写饥饿问题：① 读操作可以并发执行，相互之间不必争抢锁，多个读操作可以同时获得读锁；
② 只要有一个线程持有读写锁，写操作就会被阻塞。
读写锁的写饥饿问题（Writer Starvation）是指在使用读写锁时，
写线程可能无限期地等待获取写锁，因为读线程持续地获取读锁而不断地推迟写线程的执行。这种情况通常在读操作远多于写操作时出现。

解决方案：Linux提供了可以修改的属性pthread_rwlockattr_t，默认情况下，属性中指定的策略为“读优先”，
当写操作阻塞时，读线程依然可以获得读锁，从而在读操作并发较高时导致写饥饿问题。
我们可以尝试将策略更改为“写优先”，当写操作阻塞时，读线程无法获取锁，避免了写线程持有锁的时间持续延长，
使得写线程获取锁的等待时间显著降低，从而避免写饥饿问题。(就是使用提供的函数让写优先，默认读优先)
*/


#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

pthread_rwlock_t rwlock;
int shared_data = 0;

void *lock_reader(void *argv)
{
    pthread_rwlock_rdlock(&rwlock);
    printf("this is %s, value is %d\n", (char *)argv, shared_data);
    sleep(1);

    pthread_rwlock_unlock(&rwlock);
}

void *lock_writer(void *argv)
{
    pthread_rwlock_wrlock(&rwlock);
    int tmp = shared_data + 1;
    shared_data = tmp;
    printf("this is %s, shared_data++\n", (char *)argv);

    pthread_rwlock_unlock(&rwlock);
}

int main()
{
    pthread_rwlockattr_t attr;
    pthread_rwlockattr_init(&attr);

    // 设置写优先
    pthread_rwlockattr_setkind_np(&attr, PTHREAD_RWLOCK_PREFER_WRITER_NONRECURSIVE_NP);
    pthread_rwlock_init(&rwlock, &attr);
    pthread_rwlockattr_destroy(&attr);

    pthread_t writer1, writer2, reader1, reader2, reader3, reader4, reader5, reader6;
    pthread_create(&writer1, NULL, lock_writer, "writer1");
    pthread_create(&reader1, NULL, lock_reader, "reader1");
    pthread_create(&reader2, NULL, lock_reader, "reader2");
    pthread_create(&reader3, NULL, lock_reader, "reader3");
    pthread_create(&writer2, NULL, lock_writer, "writer2");
    pthread_create(&reader4, NULL, lock_reader, "reader4");
    pthread_create(&reader5, NULL, lock_reader, "reader5");
    pthread_create(&reader6, NULL, lock_reader, "reader6");

    pthread_join(writer1, NULL);
    pthread_join(writer2, NULL);
    pthread_join(reader1, NULL);
    pthread_join(reader2, NULL);
    pthread_join(reader3, NULL);
    pthread_join(reader4, NULL);
    pthread_join(reader5, NULL);
    pthread_join(reader6, NULL);

    pthread_rwlock_destroy(&rwlock);
}
