/**
 * 线程池保证最大运行线程的数量，确保不会同时创建多个线程去争抢资源
 * 运行时在gcc 后加上`pkg-config --cflags --libs glib-2.0`，链接库文件
 */

#include <glib.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

// 任务函数
void task_func(gpointer data, gpointer user_data) {
    int task_num = *(int*)data;
    free(data);
    printf("Executing task is %d...\n", task_num);
    sleep(1);
    printf("Task %d completed\n", task_num);
}

int main() {
    // 创建线程池
    GThreadPool *thread_pool = g_thread_pool_new(task_func, NULL, 5, TRUE, NULL);

    // 向线程池添加任务
    for (int i = 0; i < 10; i++) {
        int *tmp = malloc(sizeof(int));
        *tmp = i + 1;
        g_thread_pool_push(thread_pool, tmp, NULL);
    }

    // 等待所有任务完成
    g_thread_pool_free(thread_pool, FALSE, TRUE);
    printf("All tasks completed\n");

    return 0;
}
