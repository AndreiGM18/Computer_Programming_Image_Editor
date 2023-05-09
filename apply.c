// Copyright 2021-2022 313CA Mitran Andrei-Gabriel
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "mem_err.h"
#include "basic.h"

#define LEN 20

// Allocates memory for a copy to store image data
double ***alloc_copy(image_t image)
{
	double ***copy = (double ***)malloc(image.height * sizeof(double **));

	mem_err3(copy);

	for (int i = 0; i < image.height; ++i) {
		copy[i] = (double **)malloc(image.width * sizeof(double *));
		mem_err2(copy, i);

		int n_pixels = 1;
		if (image.image_type == 2)
			n_pixels = 3;

		for (int j = 0; j < image.width; ++j) {
			copy[i][j] = (double *)malloc(n_pixels * sizeof(double));
			mem_err1(copy, i, j);

			for (int k = 0; k < n_pixels; ++k)
				copy[i][j][k] = image.colour[i][j][k];
		}
	}

	return copy;
}

// Applies EDGE filter
void edge(image_t *image)
{
	double ***copy = alloc_copy(*image);
	int new_x1 = image->c[0][0];
	int new_x2 = image->c[0][1];
	int new_y1 = image->c[1][0];
	int new_y2 = image->c[1][1];

	// Checks coordinates and subtract 1 if the filter
	// needs to be applied to the whole image
	if (new_y2 == image->height)
		--new_y2;
	if (new_y1 == 0)
		++new_y1;
	if (new_x2 == image->width)
		--new_x2;
	if (new_x1 == 0)
		++new_x1;

	// Applies the filter
	for (int i = new_y1; i < new_y2; ++i)
		for (int j = new_x1; j < new_x2; ++j)
			for (int k = 0; k < 3; ++k) {
				copy[i][j][k] = 0;
				copy[i][j][k] -= image->colour[i - 1][j - 1][k];
				copy[i][j][k] -= image->colour[i - 1][j][k];
				copy[i][j][k] -= image->colour[i - 1][j + 1][k];
				copy[i][j][k] -= image->colour[i][j - 1][k];
				copy[i][j][k] += 8 * image->colour[i][j][k];
				copy[i][j][k] -= image->colour[i][j + 1][k];
				copy[i][j][k] -= image->colour[i + 1][j - 1][k];
				copy[i][j][k] -= image->colour[i + 1][j][k];
				copy[i][j][k] -= image->colour[i + 1][j + 1][k];
				copy[i][j][k] = clamp(copy[i][j][k]);
			}

	// Frees the original data and store the new one
	free_image(image);
	image->colour = copy;

	fprintf(stdout, "APPLY EDGE done\n");
}

// Applies SHARPEN filter
void sharpen(image_t *image)
{
	double ***copy = alloc_copy(*image);
	int new_x1 = image->c[0][0];
	int new_x2 = image->c[0][1];
	int new_y1 = image->c[1][0];
	int new_y2 = image->c[1][1];

	// Checks coordinates and subtract 1 if the filter
	// needs to be applied to the whole image
	if (new_y2 == image->height)
		--new_y2;
	if (new_y1 == 0)
		++new_y1;
	if (new_x2 == image->width)
		--new_x2;
	if (new_x1 == 0)
		++new_x1;

	// Applies the filter
	for (int i = new_y1; i < new_y2; ++i)
		for (int j = new_x1; j < new_x2; ++j)
			for (int k = 0; k < 3; ++k) {
				copy[i][j][k] = 0;
				copy[i][j][k] += 0 * image->colour[i - 1][j - 1][k];
				copy[i][j][k] -= image->colour[i - 1][j][k];
				copy[i][j][k] += 0 * image->colour[i - 1][j + 1][k];
				copy[i][j][k] -= image->colour[i][j - 1][k];
				copy[i][j][k] += 5 * image->colour[i][j][k];
				copy[i][j][k] -= image->colour[i][j + 1][k];
				copy[i][j][k] += 0 * image->colour[i + 1][j - 1][k];
				copy[i][j][k] -= image->colour[i + 1][j][k];
				copy[i][j][k] += 0 * image->colour[i + 1][j + 1][k];
				copy[i][j][k] = clamp(copy[i][j][k]);
			}

	free_image(image);
	image->colour = copy;
	fprintf(stdout, "APPLY SHARPEN done\n");
}

// Applies BLUR filter
void blur(image_t *image)
{
	double ***copy = alloc_copy(*image);
	int new_x1 = image->c[0][0];
	int new_x2 = image->c[0][1];
	int new_y1 = image->c[1][0];
	int new_y2 = image->c[1][1];

	// Checks coordinates and subtract 1 if the filter
	// needs to be applied to the whole image
	if (new_y2 == image->height)
		--new_y2;
	if (new_y1 == 0)
		++new_y1;
	if (new_x2 == image->width)
		--new_x2;
	if (new_x1 == 0)
		++new_x1;

	// Applies the filter
	for (int i = new_y1; i < new_y2; ++i)
		for (int j = new_x1; j < new_x2; ++j)
			for (int k = 0; k < 3; ++k) {
				copy[i][j][k] = 0;
				copy[i][j][k] += image->colour[i - 1][j - 1][k];
				copy[i][j][k] += image->colour[i - 1][j][k];
				copy[i][j][k] += image->colour[i - 1][j + 1][k];
				copy[i][j][k] += image->colour[i][j - 1][k];
				copy[i][j][k] += image->colour[i][j][k];
				copy[i][j][k] += image->colour[i][j + 1][k];
				copy[i][j][k] += image->colour[i + 1][j - 1][k];
				copy[i][j][k] += image->colour[i + 1][j][k];
				copy[i][j][k] += image->colour[i + 1][j + 1][k];
				copy[i][j][k] = copy[i][j][k] / 9;
				copy[i][j][k] = clamp(copy[i][j][k]);
			}

	// Frees the original data and store the new one
	free_image(image);
	image->colour = copy;

	fprintf(stdout, "APPLY BLUR done\n");
}

// Applies GAUSSIAN_BLUR filter
void gaussian_blur(image_t *image)
{
	double ***copy = alloc_copy(*image);
	int new_x1 = image->c[0][0];
	int new_x2 = image->c[0][1];
	int new_y1 = image->c[1][0];
	int new_y2 = image->c[1][1];

	// Checks coordinates and subtract 1 if the filter
	// needs to be applied to the whole image
	if (new_y2 == image->height)
		--new_y2;
	if (new_y1 == 0)
		++new_y1;
	if (new_x2 == image->width)
		--new_x2;
	if (new_x1 == 0)
		++new_x1;

	// Applies the filter
	for (int i = new_y1; i < new_y2; ++i)
		for (int j = new_x1; j < new_x2; ++j)
			for (int k = 0; k < 3; ++k) {
				copy[i][j][k] = 0;
				copy[i][j][k] += image->colour[i - 1][j - 1][k];
				copy[i][j][k] += 2 * image->colour[i - 1][j][k];
				copy[i][j][k] += image->colour[i - 1][j + 1][k];
				copy[i][j][k] += 2 * image->colour[i][j - 1][k];
				copy[i][j][k] += 4 * image->colour[i][j][k];
				copy[i][j][k] += 2 * image->colour[i][j + 1][k];
				copy[i][j][k] += image->colour[i + 1][j - 1][k];
				copy[i][j][k] += 2 * image->colour[i + 1][j][k];
				copy[i][j][k] += image->colour[i + 1][j + 1][k];
				copy[i][j][k] = copy[i][j][k] / 16;
				copy[i][j][k] = clamp(copy[i][j][k]);
			}

	// Frees the original data and stores the new one
	free_image(image);
	image->colour = copy;

	fprintf(stdout, "APPLY GAUSSIAN_BLUR done\n");
}

// Does the APPLY command
void apply_command(image_t *image, int load_fail, char *tok)
{
	// Gets the filter
	tok = strtok(NULL, "\n ");

	// Returns if LOAD failed
	if (load_fail == 1) {
		fprintf(stdout, "No image loaded\n");
		return;
	}
	// Returns if APPLY does not have a parameter after it
	if (!tok) {
		printf("Invalid command\n");
		return;
	}
	// Returns if the image is black and white or grayscale
	if (image->image_type == 0 || image->image_type == 1) {
		fprintf(stdout, "Easy, Charlie Chaplin\n");
		return;
	}

	// Applies the various filters
	if (strcmp(tok, "EDGE") == 0)
		edge(image);
	else if (strcmp(tok, "SHARPEN") == 0)
		sharpen(image);
	else if (strcmp(tok, "BLUR") == 0)
		blur(image);
	else if (strcmp(tok, "GAUSSIAN_BLUR") == 0)
		gaussian_blur(image);
	else
		fprintf(stdout, "APPLY parameter invalid\n");
}
