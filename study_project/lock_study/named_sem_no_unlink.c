/**
 * 有名信号量在文件系统的表示
 * 
 * 有名信号量的名称形如/somename，是一个以斜线（/）打头，\0字符结尾的字符串，打头的斜线之后可以有若干字符但不能再出现斜线，
 * 长度上限为NAME_MAX-4（即251）。不同的进程可以通过相同的信号量名称访问同一个信号量。
	有名信号量通常用于进程间通信，这是因为线程间通信可以有更高效快捷的方式（全局变量等），不必“杀鸡用牛刀”。但要注意的是，
	正如上文提到的，可以用于进程间通信的方式通常也可以用于线程间通信。

	其实就是初始化不同与无名，但是更高效对于通信
 */
#include <stdio.h>
#include <semaphore.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    char *sem_name = "/named_sem";

    // 初始化有名信号量
    sem_t *sem = sem_open(sem_name, O_CREAT, 0666, 0);

    pid_t pid = fork();
    if (pid > 0) {
        sem_wait(sem);
        printf("this is father\n");
        
        // 等待子进程执行完毕
        waitpid(pid, NULL, 0);
        
        // 释放引用
        sem_close(sem);

        // 释放有名信号量
        // if(sem_unlink(sem_name) == -1) {
        //     perror("sem_unlink");
        // }
    } else if(pid == 0) {
        sleep(1);
        printf("this is son\n");
        sem_post(sem);

        // 释放引用
        sem_close(sem);
    } else
    {
        perror("fork");
    }

    return 0;
}
