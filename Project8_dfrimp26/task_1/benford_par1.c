/**
 * File: benford_par1.c -- implements a parallel version of the Benford's Law using a global
 *                         counter array using protected by single mutex
 * 
 * Author: Desmond Frimpong
 * Project: 08
 * Date: May 8, 2026
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <time.h>
#include <math.h>
#include <pthread.h>
#include "my_timing.h"

// Global variables
int global_counts[10] = {0,0,0,0,0,0,0,0,0,0};
int N = 0;
double *data;
pthread_mutex_t lock; // Mutex lock

// Load data from a binary file that has an int and then
// a sequence of doubles. The value of the int should indicate
// the number of doubles in the sequence.
// Load the data into global variables N and data.
int loadData(char *filename) {
  FILE *fp;

  if(filename != NULL && strlen(filename))
    fp = fopen(filename, "r");
  else
    return -1;

  if (!fp)
    return -1;

  fread( &N, sizeof(int), 1, fp );
  data = (double*)malloc( sizeof(double)*N );
  fread( data, sizeof(double), N, fp );
  fclose( fp );
  return 1; // success
}

// Return the leading Digit of n.
int leadingDigit( double n ) {
    if (fabs(n) == 1.0)
        return 1;
    else if (fabs(n) == 0.0)
        return 0;
    else if (fabs(n) < 1.0) {
        double tmp = fabs(n);
        while (tmp < 1.0) {
            tmp *= 10.0;
        }
        return (int)floor( tmp );
    }
    else {
        long long unsigned in = (long long unsigned) floor(fabs(n));
        while (in > 9) {
            in /= 10;
        }
        return in;
    }
} // end leadingDigit

// Thread function
void* analyze_section(void* arg) {
    int thread_id = *((int*)arg);
    int start_idx = thread_id * (N / 8);
    int end_idx = (thread_id == 7) ? N : start_idx + (N / 8);

    for (int i = start_idx; i < end_idx; i++) {
        int d = leadingDigit(data[i]);
        pthread_mutex_lock(&lock);
        global_counts[d]++;
        pthread_mutex_unlock(&lock);
    }

    pthread_exit(NULL);
}

/* Main routine. */
int main(int argc, char* argv[]) 
{
  double t1, t2;
  int i;

  // Load the data
  int succ;
  succ = loadData( "medium.bin" );
  if (!succ) { return -1; }

  pthread_t threads[8];
  int thread_ids[8];
  pthread_mutex_init(&lock, NULL);

  // Start the timer after we have loaded the data.
  t1 = get_time_sec();

  // Create threads
  for (i = 0; i < 8; i++) {
      thread_ids[i] = i;
      pthread_create(&threads[i], NULL, analyze_section, (void*)&thread_ids[i]);
  }

  // Join threads
  for (i = 0; i < 8; i++) {
      pthread_join(threads[i], NULL);
  }

  // End the timer  
  t2 = get_time_sec();
  
  for (i = 1; i < 10; i++) {
    printf( "There are %d %d's\n", global_counts[i], i );
  }
         
  printf("It took %f seconds for the whole thing to run\n",t2-t1); 

  // We are responsible for calling loadData, so we are responsible
  // for freeing the data array.
  free( data );
  pthread_mutex_destroy(&lock);
  return 0;
} // end main
