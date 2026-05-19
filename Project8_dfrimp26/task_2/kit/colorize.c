/**
 * File: colorize.c -- implements a parallel version of the Benford's Law using a global
 *                         counter array using protected by single mutex
 * 
 * Author: Desmond Frimpong
 * Project: 08
 * Date: May 8, 2026
*/

#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>
#include "ppmIO.h"

#define NUM_THREADS_DEFAULT 1

typedef struct
{
	int rows;
	int cols;
	int start_row;
	int end_row;
	Pixel *image;
} thread_data_t;

void *process_image_section(void *arg)
{
	thread_data_t *data = (thread_data_t *)arg;
	for (int i = data->start_row; i < data->end_row; i++)
	{
		for (int j = 0; j < data->cols; j++)
		{
			int index = i * data->cols + j;
			data->image[index].r = data->image[index].r > 128 ? (220 + data->image[index].r) / 2 : (30 + data->image[index].r) / 2;
			data->image[index].g = data->image[index].g > 128 ? (220 + data->image[index].g) / 2 : (30 + data->image[index].g) / 2;
			data->image[index].b = data->image[index].b > 128 ? (220 + data->image[index].b) / 2 : (30 + data->image[index].b) / 2;
		}
	}
	return NULL;
}

int main(int argc, char *argv[])
{
	Pixel *src;
	int rows, cols, colors;
	int num_threads = NUM_THREADS_DEFAULT;
	int num_iterations = 10; // Number of iterations for performance comparison
	double serial_time_avg = 0.0;
	double parallel_time_avg = 0.0;

	// Check usage
	if (argc < 2)
	{
		printf("Usage: %s <image filename> [num_threads]\n", argv[0]);
		exit(-1);
	}

	
	if (argc > 2)
	{
		num_threads = atoi(argv[2]);
		if (num_threads < 1)
		{
			printf("Invalid number of threads: %d\n", num_threads);
			exit(-1);
		}
	}

	// Read image and check for errors
	src = ppm_read(&rows, &cols, &colors, argv[1]);
	if (!src)
	{
		printf("Unable to read file %s\n", argv[1]);
		exit(-1);
	}

	// Serial processing
	struct timespec start_time, end_time;
	clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);
	for (int iter = 0; iter < num_iterations; iter++)
	{
		for (int i = 0; i < rows * cols; i++)
		{
			src[i].r = src[i].r > 128 ? (220 + src[i].r) / 2 : (30 + src[i].r) / 2;
			src[i].g = src[i].g > 128 ? (220 + src[i].g) / 2 : (30 + src[i].g) / 2;
			src[i].b = src[i].b > 128 ? (220 + src[i].b) / 2 : (30 + src[i].b) / 2;
		}
	}
	clock_gettime(CLOCK_MONOTONIC_RAW, &end_time);
	double serial_time_total = (end_time.tv_sec - start_time.tv_sec) * 1e3 + (end_time.tv_nsec - start_time.tv_nsec) / 1e6;
	serial_time_avg = serial_time_total / num_iterations;

	// Reset image
	src = ppm_read(&rows, &cols, &colors, argv[1]);

	// Parallel processing
	pthread_t threads[num_threads];
	thread_data_t thread_data[num_threads];
	int rows_per_thread = rows / num_threads;
	int leftover_rows = rows % num_threads;
	clock_gettime(CLOCK_MONOTONIC_RAW, &start_time);
	for (int iter = 0; iter < num_iterations; iter++)
	{
		for (int i = 0; i < num_threads; i++)
		{
			thread_data[i].rows = rows_per_thread;
			thread_data[i].cols = cols;
			thread_data[i].image = src;
			if (i < leftover_rows)
			{
				thread_data[i].start_row = i * rows_per_thread;
				thread_data[i].end_row = thread_data[i].start_row + rows_per_thread + 1;
			}
			else
			{
				thread_data[i].start_row = i * rows_per_thread + leftover_rows;
				thread_data[i].end_row = thread_data[i].start_row + rows_per_thread;
			}
			int rc = pthread_create(&threads[i], NULL, process_image_section, &thread_data[i]);
			if (rc)
			{
				printf("Error creating thread %d\n", i);
				exit(-1);
			}
		}
		// Wait for all threads to finish
		for (int i = 0; i < num_threads; i++)
		{
			pthread_join(threads[i], NULL);
		}
	}
	clock_gettime(CLOCK_MONOTONIC_RAW, &end_time);
	double parallel_time_total = (end_time.tv_sec - start_time.tv_sec) * 1e3 + (end_time.tv_nsec - start_time.tv_nsec) / 1e6;
	parallel_time_avg = parallel_time_total / num_iterations;

	// Write out the image
	ppm_write(src, rows, cols, colors, "bold.ppm");

	free(src);

	// Output processing times
	printf("Serial processing time (average over %d iterations): %.3f ms\n", num_iterations, serial_time_avg);
	printf("Parallel processing time with %d threads (average over %d iterations): %.3f ms\n", num_threads, num_iterations, parallel_time_avg);

	return 0;
}
