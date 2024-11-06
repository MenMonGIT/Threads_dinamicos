/*
 * Este programa se soluciona el problema de concurrencia que se presenta al momento
 * que dos hilos intentan modificar una variable compartida al volver independiente cada variable
 *
 */
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

int max;
volatile int counter = 0; // Unique  A  variable
volatile int counter2=0;//Unique B variable
void *mythread(void *arg) {
  char *letter = arg;
  int i; // stack (private per thread)
  printf("%s: begin [addr of i: %p]\n", letter, &i);
  if(letter=="A"){
  	for(i=0;i<max;i++){
   		counter=counter+1;
  	}

  }else{
  	for(i=0;i<max;i++){
                counter2=counter2+1;
	} 
  } 
  printf("%s: done\n", letter);
  return NULL;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
	fprintf(stderr, "usage: main-first <loopcount>\n");
	exit(1);
  }
  max = atoi(argv[1]);

  pthread_t p1, p2;
  printf("main: begin [counter = %d] [%p]\n", counter, &counter);
  pthread_create(&p1, NULL, mythread, "A");
  pthread_create(&p2, NULL, mythread, "B");
  // join waits for the threads to finish
  pthread_join(p1, NULL);
  pthread_join(p2, NULL);
  printf("main: done\n [counter: %d]\n [should: %d]\n",
	  counter+counter2, max*2);
  return 0;
}
