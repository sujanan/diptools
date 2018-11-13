#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "histogram.h"
#include "dip.h"

static void read_jpeg(struct image *image, const char *filename)
{
	int x, y, n;
	unsigned char *data = stbi_load(filename, &x, &y, &n, 0);

	image->width = x;
	image->height = y;
	image->n_channels = n;
	image->data = data;
}

int main(int argc, char **argv)
{
	if (argc != 2) {
		fprintf(stderr, "usage: %s <filename>\n", argv[0]);
		return 1;
	}
	struct image image;
	struct histogram histogram;

	read_jpeg(&image, argv[1]);
	if (image.data == NULL) {
		fprintf(stderr, "error: reading jpeg file failed.");
		return 1;
	}
	init_histogram(&histogram, 256);
	build_histogram(&histogram, &image);
	print_histogram(&histogram);


	free(image.data);
	return 0;
}
