#include <stdio.h>
#include <pthread.h>
#include <unistd.h>

typedef struct {
    int id;
    int period;
} PeriodicTask;


void *taskFunction(void *arg) {
    PeriodicTask *task = (PeriodicTask *)arg;
    pthread_setcancelstate(PTHREAD_CANCEL_ENABLE, NULL);

    while (1) {
        sleep(task->period);
        printf("Task %d executed\n", task->id);
        pthread_testcancel();
    }

    return NULL;
}


int main() {
    
    int task_p[] = {1, 2, 3};
    int nT=3;
    pthread_t Th[nT];
    PeriodicTask T[nT];

    for (int i = 0; i < nT; i++){
        T[i].id = i+1;
        T[i].period = task_p[i];
        pthread_create(&Th[i], NULL, taskFunction, &T[i]);
        // sleep(i+1);
        // pthread_cancel(threads[i]);
    }

    sleep(10);   

    for (int i = 0; i < nT; i++){
        pthread_cancel(Th[i]);
        pthread_join(Th[i], NULL);
    }
        

    return 0;
}

