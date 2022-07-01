#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <inttypes.h>

typedef int32_t (*SysJob)(void);

typedef struct data_
{
    float clock_time;
    SysJob job;
} JobData;

int32_t
job1(void)
{
    printf("It worked first!\n");
}

int32_t
job2(void)
{
    printf("It worked!\n");
}

void *
scheduler(JobData *job_data)
{
    if (NULL != job_data)
    {
        float time_in_seconds = job_data->clock_time / 1000;
        // printf("%1.3f\n", time_in_seconds);

        sleep(time_in_seconds);
        job_data->job();
    }
}

int main(void)
{
    pthread_t thread1;
    pthread_t thread2;

    JobData firstThread;
    firstThread.clock_time = 1000;
    firstThread.job = &job1;

    JobData secondThread;
    secondThread.clock_time = 2000;
    secondThread.job = &job2;

    pthread_create(&thread1, NULL, (void *(*)(void *))scheduler, &firstThread);
    pthread_create(&thread2, NULL, (void *(*)(void *))scheduler, &secondThread);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    return 0;
}