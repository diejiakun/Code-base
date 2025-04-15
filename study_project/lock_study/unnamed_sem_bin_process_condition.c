/**
 * void *mmap(void *addr, size_t length, int prot, int flags,int fd, off_t offset);
 * 将文件映射到内存区域,进程可以直接对内存区域进行读写操作,就像操作普通内存一样,但实际上是对文件或设备进行读写,
 * 从而实现高效的 I/O 操作
 * 
 * void *addr: 指向期望映射的内存起始地址的指针,通常设为 NULL,让系统选择合适的地址
 * size_t length: 要映射的内存区域的长度,以字节为单位
 * int prot: 内存映射区域的保护标志,可以是以下标志的组合
 *          (1) PROT_READ: 允许读取映射区域
 *          (2) PROT_WRITE: 允许写入映射区域
 *          (3) PROT_EXEC: 允许执行映射区域
 *          (4) PROT_NONE: 页面不可访问
 * int flags：映射选项标志
 *          (1) MAP_SHARED: 映射区域是共享的,对映射区域的修改会影响文件和其他映射到同一区域的进程(一般使用共享)
 *          (2) MAP_PRIVATE: 映射区域是私有的,对映射区域的修改不会影响原始文件,对文件的修改会被暂时保存在一个私有副本中
 *          (3) MAP_ANONYMOUS: 创建一个匿名映射,不与任何文件关联
 *          (4) MAP_FIXED: 强制映射到指定的地址,如果不允许映射,将返回错误
 * int fd: 文件描述符,用于指定要映射的文件或设备,如果是匿名映射,则传入无效的文件描述符（例如-1）
 * off_t offset: 从文件开头的偏移量,映射开始的位置
 * return void*: (1) 成功时,返回映射区域的起始地址,可以像操作普通内存那样使用这个地址进行读写
 *               (2) 如果出错,返回 (void *) -1,并且设置 errno 变量来表示错误原因
 */

/**
* int munmap(void *addr, size_t length);
* 用于取消之前通过 mmap() 函数建立的内存映射关系
* 
* void *addr: 这是指向之前通过 mmap() 映射的内存区域的起始地址的指针,这个地址必须是有效的,并且必须是 mmap() 返回的有效映射地址
* size_t length: 这是要解除映射的内存区域的大小(以字节为单位),它必须与之前通过 mmap() 映射的大小一致
* return: int 成功 0
*             失败 -1
*/

/*
	作为二进制信号量用于进程间通信
	线程比进程的资源共享程度更高，可以用于进程间通信的方式，通常也可以用于线程间通信。

	此处为便于讲解，只给出了父子进程间通信的示例，但由于共享内存对象可以被任意进程访问，
	因此，无名信号量实际上可以用于任意进程间的通信，而不仅限于父子进程。在非父子进程通信时，
	共享资源的初始化和释放要格外注意，必须按照合理的顺序进行。
*/
#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <semaphore.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    char *shm_sem_name = "unnamed_sem_shm_sem";
    char *shm_value_name = "unnamed_sem_shm_value";

    // 创建内存共享对象
    int sem_fd = shm_open(shm_sem_name, O_CREAT | O_RDWR, 0666);
    int value_fd = shm_open(shm_value_name, O_CREAT | O_RDWR, 0666);

    // 调整内存共享对象的大小
    ftruncate(sem_fd, sizeof(sem_t));
    ftruncate(value_fd, sizeof(int));

    // 将内存共享对象映射到共享内存区域
    sem_t *sem = mmap(NULL, sizeof(sem_t), PROT_READ | PROT_WRITE, MAP_SHARED, sem_fd, 0);
    
    int *value = mmap(NULL, sizeof(int), PROT_READ | PROT_WRITE, MAP_SHARED, value_fd, 0);
    
    // 初始化信号量和共享变量的值
    sem_init(sem, 1, 1);
    *value = 0;

    int pid = fork();

    if (pid > 0)
    {
        sem_wait(sem);
        int tmp = *value + 1;
        sleep(1);
        *value = tmp;
        sem_post(sem);

        // 等待子进程执行完毕
        waitpid(pid, NULL, 0);
        printf("this is father, child finished\n");
        printf("the final value is %d\n", *value);
    }
    else if (pid == 0)
    {
        sem_wait(sem);
        int tmp = *value + 1;
        sleep(1);
        *value = tmp;
        sem_post(sem);
    }
    else
    {
        perror("fork");
    }

    // 父进程执行到这里，子进程已执行完毕，可以销毁信号量
    if (pid > 0)
    {
        if (sem_destroy(sem) == -1)
        {
            perror("sem_destory");
        }
    }

    // 无论父子进程都应该解除共享内存的映射，并关闭共享对象的文件描述符
    if (munmap(sem, sizeof(sem)) == -1)
    {
        perror("munmap sem");
    }

    if (munmap(value, sizeof(int)) == -1)
    {
        perror("munmap value");
    }

    if (close(sem_fd) == -1)
    {
        perror("close sem");
    }

    if (close(value_fd) == -1)
    {
        perror("close value");
    }

    // 如果调用时别的进程仍在使用共享对象，则等待所有进程释放资源后，才会销毁相关资源。
    // shm_unlink只能调用一次,这里在父进程中调用shm_unlink
    if (pid > 0)
    {
        if (shm_unlink(shm_sem_name) == -1)
        {
            perror("father shm_unlink shm_sem_name");
        }

        if (shm_unlink(shm_value_name) == -1)
        {
            perror("father shm_unlink shm_value_name");
        }
    }

    return 0;
}
