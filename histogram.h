#ifndef HISTOGRAM_H
#define HISTOGRAM_H

#include "diptool.h"

struct histogram {
	int n_intensity, min, max;
	unsigned int *data;
};

extern void init_histogram(struct histogram *histogram, int n_intensity);
extern void build_histogram(
		struct histogram *histogram, const struct image *image);
extern void print_histogram(const struct histogram *histogram);

#endif
