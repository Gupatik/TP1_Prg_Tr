#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>


#define ARRAY_SIZE 10 // Taille du tableau
#define NUM_THREADS 4   // Nombre de threads






// Structure pour stocker les informations nécessaires pour le calcul partiel
typedef struct {
   int start_index;
   int end_index;
   int *array;
   int *partial_sum; // Résultat partiel stocké dans une variable partagée
   pthread_mutex_t *lock;  // Mutex pour synchroniser l'accès à la variable partagée
} PartialCalculationInfo;








// Fonction pour calculer la somme des éléments d'un sous-tableau
void *sum_partial(void *arg) {
   PartialCalculationInfo *info = (PartialCalculationInfo *)arg;
   int sum = 0;
   for (int i = info->start_index; i < info->end_index; i++) {
       sum += info->array[i];
       printf("La somme est : %d\n", sum);
   }


   // Create lock
   pthread_mutex_lock(info->lock);


   *(info->partial_sum) += sum;
  
   // Release lock
   pthread_mutex_unlock(info->lock);


   return NULL;
}






int main() {
   int array[ARRAY_SIZE];
   int total_sum = 0;
   pthread_t threads[NUM_THREADS];
   pthread_mutex_t lock;
   PartialCalculationInfo thread_info[NUM_THREADS];


   // Initialisation du tableau avec des valeurs
   for (int i = 0; i < ARRAY_SIZE; i++) {
       array[i] = i + 1;
   }


   // Initialisation du mutex
   pthread_mutex_init(&lock, NULL);



   // Division du tableau en parties et création d'un thread pour chaque partie
   for (int i = 0; i < NUM_THREADS; i++) {
       thread_info[i].start_index = i * (ARRAY_SIZE / NUM_THREADS);
       thread_info[i].end_index = (i == NUM_THREADS - 1) ? (ARRAY_SIZE) : ((i + 1) * (ARRAY_SIZE / NUM_THREADS));


       printf("start index est : %d\n", thread_info[i].start_index);
       printf("end index est : %d\n", thread_info[i].end_index);


       thread_info[i].array = array;
       thread_info[i].partial_sum = &total_sum;
       thread_info[i].lock = &lock;


       pthread_create(&threads[i], NULL, sum_partial, (void *)&thread_info[i]);
   }


   // Attente de la fin de l'exécution de tous les threads
   for (int i = 0; i < NUM_THREADS; i++) {
       pthread_join(threads[i], NULL);
   }

   printf("La somme totale est : %d\n", total_sum);

   pthread_mutex_destroy(&lock);


   return 0;
}
