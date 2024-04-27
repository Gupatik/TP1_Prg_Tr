#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void *thread_func1(void *ptr){
    char *msg = (char*) ptr;
    printf("%s \n", msg);
}

void *thread_func2(void *ptr){
    char *msg = (char*) ptr;
    printf("%s \n", msg);
}



int main(int argc, char const *argv[])
{
    pthread_t th1, th2;

    char *msg1 = "Bonjour!";
    char *msg2 = "Salut!";

    pthread_create(&th1, NULL, thread_func1, (void*) msg1);
    pthread_create(&th2, NULL, thread_func2, (void*) msg2);

    pthread_join(th1, NULL);
    pthread_join(th2, NULL);

    return 0;
}

