#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int max;
int num_thread;
int *counter;  // Contador global

// Función que será ejecutada por cada hilo
void *mythread(void *arg) {
  int numero = *(int *)arg;  // Convertimos el argumento a int, que es el índice del hilo
  
  printf("Thread %d: begin\n", numero);
  
  // Cada hilo incrementa su propio contador 'counter[numero]' durante 'max' iteraciones
  for (int i = 0; i < max; i++) {
    counter[numero] = counter[numero] + 1;
  }
  
  printf("Thread %d: done\n", numero); 
  return NULL;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "usage: main-first <loopcount> <Threadscount>\n");
    exit(1);
  }
  
  max = atoi(argv[1]);
  num_thread = atoi(argv[2]);
  
  // Asignamos memoria para 'counter' para tener un contador por hilo
  counter = (int *)malloc(num_thread * sizeof(int));
  if (counter == NULL) {
    fprintf(stderr, "Error, No se asigno correctamente espacio de memoria\n");
    exit(1);
  }

  // Inicializamos el arreglo 'counter' en cero
  for (int i = 0; i < num_thread; i++) {
    counter[i] = 0;
  }
  
  pthread_t hilos[num_thread];  // Creamos los hilos
  int indices[num_thread];  // Array para almacenar los índices de los hilos
  
  // Creamos los hilos y les asignamos el índice correspondiente
  for (int i = 0; i < num_thread; i++) {
    indices[i] = i;  // Asignamos el índice al hilo
    pthread_create(&hilos[i], NULL, mythread, (void *)&indices[i]);  // Pasamos la dirección del índice
  }

  // Esperamos a que todos los hilos terminen
  for (int z = 0; z < num_thread; z++) {  
    pthread_join(hilos[z], NULL);
  }

  // Mostramos el resultado final
  int total = 0;
  for (int i = 0; i < num_thread; i++) {
    total += counter[i];
  }

  printf("main: done\n [total counter: %d]\n [should be: %d]\n", total, max * num_thread);

  // Liberamos la memoria asignada para 'counter'
  free(counter);

  return 0;
}
