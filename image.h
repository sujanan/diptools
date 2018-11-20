#ifndef IMAGE_H
#define IMAGE_H

struct image {
	int width, height, n_channels;
	unsigned char *data;
};

extern void build_image(struct image *image, const char *filename);

#endif
