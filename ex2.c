#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>

void *print_message(void *ptr) {
    char *message = (char *)ptr;
    printf("%s\n", message);
    pthread_exit(NULL); 
}

int main() {
    pthread_t thread;
    char *message = "Bonjour!";

    if(pthread_create(&thread, NULL, print_message, (void *)message) != 0){
        perror("Erreur lors de creation!");
    }

    if(pthread_join(thread, NULL) != 0){
        perror("Erreur lors de join!");
    }

    return 0;
}

