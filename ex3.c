#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

void *Tache1(void *arg){
    int i=0;
    while(i<5){
        printf("Execution de Tache1 \n");
        sleep(1);
        i++;
    }
    return NULL;
}

void *Tache2(void *arg){
    int j=0;
    while(j<3){
        printf("Execution de Tache2 \n");
        sleep(2);
        j++;
    }
    return NULL;
}

int main(int argc, char *argv[]){
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, Tache1, NULL);
    pthread_join(thread1, NULL);

    pthread_create(&thread2, NULL, Tache2, NULL);
    pthread_join(thread2, NULL);
    
    return 0;
}

int main(int argc, char *argv[]){
    pthread_t thread1, thread2;

    pthread_create(&thread1, NULL, Tache1, NULL);
    pthread_create(&thread2, NULL, Tache2, NULL);

    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

   return 0;
}