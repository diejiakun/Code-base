/**
 * 在上述例程中，我们定义了两个信号量：full和empty，full表示当前的缓冲区（在本例中为shared_num，
 * 实质上只能存储一个int类型的数据）是否已满，empty表示缓冲区是否已空。我们启动了一个消费者线程consumer和生产者线程producer，
 * 前者用于从缓冲区读取数据（消费），后者用于向缓冲区写入数据（生产）。
	① 生产者的逻辑：首先等待缓冲区为空，然后写入数据，最后通过sem_post告诉消费者，缓冲区已满，可以消费数据。
	② 消费者的逻辑：首先等待缓冲区满，然后消费数据，最后通过sem_post告诉生产者，缓冲区已空，可以生产数据。
	需要注意的是，初始时缓冲区是空的，因此，empty信号量的初值应为1，而full应为0，二者都是用于线程间通信的，
	sem_init()函数的第二个参数都应该是0。
	上述例程通过两个信号量控制生产者和消费者的执行顺序：
	① 消费者必须在生产者发送数据后方可消费。
	② 除首次发送外，生产者必须等待消费者读取数据后方可发送数据。

	信号量的取值仍在0和1之间变动，但这并不意味着本例中的也是二进制信号量。
	二进制信号量和计数信号量的划分更多地是从控制效果来说的：二进制信号量起到了互斥锁的作用，当多个进程或线程访问共享资源时，
	确保同一时刻只有一个进程或线程进入了临界区，起到了“互斥”的作用；而计数信号量起到了“控制顺序”的作用，明确了“谁先执行”、
	“谁后执行”。很显然，本例是通过信号量控制了线程执行的先后顺序，属于计数信号量。
	计数信号量和二进制信号量的划分不能只看信号量值的波动范围。
	本例只展示了一个生产者和一个消费者在缓冲区为1时的协同工作，如果我们增加生产者和消费者的数量，
	信号量的取值范围自然就不再是0和1了。


	0为阻塞1为运行，这个信号量就是0和1的切换使得阻塞和运行不断切换运行，让程序顺序运行

 */
#include <stdio.h>
#include <unistd.h>
#include <semaphore.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

sem_t *full;
sem_t *empty;

int shard_num;

int rand_num()
{
    srand(time(NULL));

    return rand();
}

void *producer(void *argv)
{
    for (int i = 0; i < 5; i++)
    {
        sem_wait(empty);
        printf("\n==========> 第 %d 轮数据传输 <=========\n\n", i + 1);
        sleep(1);
        shard_num = rand_num();
        printf("producer has sent data\n");
        sem_post(full);
    }
}

void *consumer(void *argv)
{
    for (int i = 0; i < 5; i++)
    {
        sem_wait(full);
        printf("consumer has read data\n");
        printf("the shard_num is %d\n", shard_num);
        sleep(1);
        sem_post(empty);
    }
}

int main()
{
    full = malloc(sizeof(sem_t));
    empty = malloc(sizeof(sem_t));

    sem_init(empty, 0, 1);
    sem_init(full, 0, 0);

    pthread_t producer_id, consumer_id;
    pthread_create(&producer_id, NULL, producer, NULL);
    pthread_create(&consumer_id, NULL, consumer, NULL);

    pthread_join(producer_id, NULL);
    pthread_join(consumer_id, NULL);

    sem_destroy(empty);
    sem_destroy(full);

    return 0;
}
