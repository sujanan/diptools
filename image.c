#include <stdio.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "image.h"

void build_image(struct image *image, const char *filename)
{
	int x, y, n;
	unsigned char *data = stbi_load(filename, &x, &y, &n, 0);

	image->width = x;
	image->height = y;
	image->n_channels = n;
	image->data = data;
}
