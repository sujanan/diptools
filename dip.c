#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "dip.h"

#define N_COLORS 256

static void read_jpeg(struct image *image, const char *filename)
{
	int x, y, n;
	unsigned char *data = stbi_load(filename, &x, &y, &n, 0);

	image->width = x;
	image->height = y;
	image->nchannels = n;
	image->data = data;
}

void build_histogram(int *histogram, const struct image *image)
{
	const unsigned char *data = image->data;
	int npixels = image->width * image->height;
	int p, i;

	memset(histogram, 0, sizeof(int) * N_COLORS);
	for (i = 0; i < npixels; i++) {
		p = data[i];
		histogram[p]++;
	}
}

void print_histogram(int *histogram)
{
	int i;

	for (i = 0; i < N_COLORS; i++) {
		printf("%03d: %d\n", i, histogram[i]);
	}
}

int main(int argc, char **argv)
{
	if (argc != 2) {
		fprintf(stderr, "usage: %s <filename>\n", argv[0]);
		return 1;
	}
	struct image image;
	int histogram[N_COLORS];

	read_jpeg(&image, argv[1]);
	if (image.data == NULL) {
		fprintf(stderr, "error: reading jpeg file failed.");
		return 1;
	}
	build_histogram(histogram, &image);
	print_histogram(histogram);

	stbi_image_free(image.data);
	return 0;
}
