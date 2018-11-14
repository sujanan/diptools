#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include "histogram.h"

void init_histogram(struct histogram *histogram, int n_intensity)
{
	size_t s;

	s = sizeof(*(histogram->data)) * n_intensity;
	histogram->n_intensity = n_intensity;	
	histogram->min = 0;
	histogram->max = 0;
	histogram->data = malloc(s);
	if (histogram->data != NULL)
		memset(histogram->data, 0, s);
}

void build_histogram(struct histogram *histogram, const struct image *image)
{
	int n_pixel = image->width * image->height;
	unsigned int fmin = UINT_MAX, fmax = 0;
	unsigned int frequency;
	int imin, imax;
	int intensity;
	int i;

	for (i = 0; i < n_pixel; i++) {
		intensity = image->data[i];
		histogram->data[intensity]++;
		frequency = histogram->data[intensity];
		if (frequency > fmax) {
			fmax = frequency;
			imax = intensity;
		}
	}
	for (intensity = 0; intensity < histogram->n_intensity; intensity++) {
		frequency = histogram->data[intensity];
		if (frequency < fmin) {
			fmin = frequency;
			imin = intensity;
		}
	}
	histogram->min = imin;
	histogram->max = imax;
}

void print_histogram(const struct histogram *histogram)
{
	unsigned int fmax = histogram->data[histogram->max];
	double unit;
	unsigned int n_units;
	struct winsize w;
	int i, j;

    	ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);		
	unit = (double) fmax / (w.ws_col - 7); /* "[%3d]: "*/

	for (i = 0; i < histogram->n_intensity; i++) {
		n_units = (unsigned int) (histogram->data[i] / unit);
		printf("[%3d]: ", i);
		for (j = 0; j < n_units; j++)
			printf("*");
		printf("\n");
	}
}
