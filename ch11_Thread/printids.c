
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

void printids(const char *s) 
{
    pid_t pid;
    pthread_t tid;

    pid = getpid();
    tid = pthread_self();

    printf("%s pid %lu tid %lu (0x%lx)\n", s, (unsigned long)pid, (unsigned long)tid, (unsigned long)tid);
}

void *
thr_fn(void *arg)
{
    printids("new thread: ");
    return ((void *)0);
}

int main(void)
{
    int err;
    pthread_t chtid;
    err = pthread_create(&chtid, NULL, thr_fn, NULL);
    if (err != 0) {
        printf("can't create thread\n");
        exit(-1);
    }
    printids("main thread: ");
    sleep(1);
    exit(0);
}
