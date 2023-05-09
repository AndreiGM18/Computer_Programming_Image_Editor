// Copyright 2021-2022 313CA Mitran Andrei-Gabriel
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"

// THE clamp function
double clamp(double x)
{
	if (x < 0)
		return 0;
	else if (x > 255)
		return 255;
	else
		return x;
}

// Swaps two values
void swap_values(int *a, int *b)
{
	int tmp = *a;
	*a = *b;
	*b = tmp;
}

// Swaps two pointers
void swap_pointers(unsigned char **a, unsigned char **b)
{
	unsigned char *tmp = *a;
	*a = *b;
	*b = tmp;
}

// Checks if LOAD fails
int load_fail_message(FILE *fin, char *filename, int *load_fail)
{
	if (!fin) {
		fprintf(stdout, "Failed to load %s\n", filename);
		*load_fail = 1;
		return 1;
	}

	return 0;
}

// Checks if the file to be written in has been opened
int open_fail_message(FILE *fout, char *filename)
{
	if (!fout) {
		fprintf(stderr, "Cannot open %s\n", filename);
		return 1;
	}

	return 0;
}

// Frees memory allocated for the image's data
void free_image(image_t *image)
{
	for (int i = 0; i < image->height; ++i) {
		for (int j = 0; j < image->width; ++j)
			free(image->colour[i][j]);
		free(image->colour[i]);
	}
	free(image->colour);
}
