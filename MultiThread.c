/*
 * Este programa ilustra el problema de concurrencia que se presenta al momento
 * que dos hilos intentan modificar una variable compartida.
 *
 * Ejemplo tomado del libro 'Operating Systems Three Easy Pieces'.
 *
 * Adaptado por: John Sanabria - john.sanabria@correounivalle.edu.co
 * Fecha: 2023-05-17
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int max;

void *mythread(void *arg) {
  char *numero = arg;   
  int i; // stack (private per thread)
  printf("%s: begin [addr of i: %p]\n", numero, &i);
  for(i=0;i<max;i++){
    counter[atoi(numero)]=counter[atoi(numero)]+1;
  }
  printf("%s: done\n", numero); 
  return NULL;
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
	fprintf(stderr, "usage: main-first <loopcount><Threadscount>\n");
	exit(1);
  }
  int i;
  int z;
  max = atoi(argv[1]);
  
  pthread_t hilos[atoi(argv[2])];
  //printf("main: begin [counter = %d] [%p]\n", counter[0], &counter[0]);
  for (i=0;i<atoi(argv[2]);i++){
    pthread_create(&hilos[i], NULL, mythread,"1");   //creacion de los  multiples hilos y asigna la funcion de ejecucion de cada hilo 
  }
  
  for (z=0;z<atoi(argv[2]);z++){ //This wait for threads to finish
    pthread_join(hilos[z], NULL);
  }  
   
  printf("main: done\n [counter: %d]\n [should: %d]\n",
	  counter, max*atoi(argv[2]));
  printf(counter[1]);
  return 0;
}
