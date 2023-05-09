// Copyright 2021-2022 313CA Mitran Andrei-Gabriel
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "image.h"
#include "mem_err.h"
#include "basic.h"
#include "select.h"

#define TYPELEN 3

// Skips to endline
void skip(void)
{
	char disposable;
	do {
		fscanf(stdin, "%c", &disposable);
	} while (disposable != '\n');
}

// Skips comment if the scanned charcter is '#'
void skip_comments(FILE *fin)
{
	char c;
	fscanf(fin, "%c", &c);
	if (c == '#')
		skip();
	else
		fseek(fin, -1, SEEK_CUR);
}

// Allocates memory for the image data, then reads it,
// either from an ascii file or a binary file
void read(image_t *image, FILE *f)
{
	unsigned char x;

	image->colour = (double ***)malloc(image->height * sizeof(double **));
	mem_err3(image->colour);

	for (int i = 0; i < image->height; ++i) {
		image->colour[i] = (double **)malloc(image->width * sizeof(double *));
		mem_err2(image->colour, i);

		// Gets the number of pixels
		int n_pixels = 1;
		if (image->image_type == 2)
			n_pixels = 3;

		for (int j = 0; j < image->width; ++j) {
			image->colour[i][j] = (double *)malloc(n_pixels * sizeof(double));
			mem_err1(image->colour, i, j);

			// Reads an unsigned char, then, using a cast,
			// stores the recently scanned value, regardless
			// of the file type
			if (!(image->file_type)) {
				for (int k = 0; k < n_pixels; ++k) {
					// Ascii
					fscanf(f, "%hhu", &x);
					image->colour[i][j][k] = (double)x;
				}
			} else {
				for (int k = 0; k < n_pixels; ++k) {
					// Binary
					fread(&x, sizeof(unsigned char), 1, f);
					image->colour[i][j][k] = (double)x;
				}
			}
		}
	}
}

// Gets the image type and file type from the magic word
void get_types(image_t *image, char *type)
{
	char ascii[TYPELEN][TYPELEN] = {"P1", "P2", "P3"};
	char binary[TYPELEN][TYPELEN] = {"P4", "P5", "P6"};
	int i = 0;

	// Gets the file type, ascii or binary
	while (i < TYPELEN) {
		if (strcmp(type, ascii[i]) == 0) {
			image->file_type = 0;
			break;
		}
		if (strcmp(type, binary[i]) == 0) {
			image->file_type = 1;
			break;
		}
		++i;
	}

	// Gets the image type, black and white, grayscale or rgb
	if (strcmp(type, "P1") == 0 || strcmp(type, "P4") == 0)
		image->image_type = 0;

	if (strcmp(type, "P2") == 0 || strcmp(type, "P5") == 0)
		image->image_type = 1;

	if (strcmp(type, "P3") == 0 || strcmp(type, "P6") == 0)
		image->image_type = 2;
}

// Does the LOAD command
void load_command(image_t *image, int *load_fail, char *tok)
{
	// Gets the file's name (from which to read)
	tok = strtok(NULL, "\n ");
	// Returns if LOAD does not have a parameter after it
	if (!tok) {
		printf("Invalid command\n");
		return;
	}
	// Frees the allocated memory for the already stored image's data
	if (image->colour) {
		free_image(image);
		image->colour = NULL;
	}
	// LOAD is successful
	*load_fail = 0;
	char type[TYPELEN];
	long pos;
	// Open file in ascii read mode
	FILE *fin = fopen(tok, "rt");

	// Returns if the file cannot be opened,
	// which means LOAD failed
	if (load_fail_message(fin, tok, load_fail))
		return;
	skip_comments(fin);
	// Gets the magic word
	fscanf(fin, "%s", type);
	get_types(image, type);
	skip_comments(fin);

	// Reads width, height and the max value (only
	// for grayscale and rgb)
	if (image->image_type == 0) {
		fscanf(fin, "%d%d", &image->width, &image->height);
	} else {
		fscanf(fin, "%d%d", &image->width, &image->height);
		skip_comments(fin);
		fscanf(fin, "%d", &image->maxx);
	}

	skip_comments(fin);
	// Gets the cursor's position
	pos = ftell(fin);

	// Continues reading in ascii read mode
	if (!(image->file_type)) {
		fprintf(stdout, "Loaded %s\n", tok);
		// Reads the image's data
		read(image, fin);
		// Selects the full image
		select_all(image);
		fclose(fin);

	// Reads in binary read mode
	} else {
		// Closes the file
		fclose(fin);
		// Reopens it
		FILE *fin = fopen(tok, "rb");
		// Returns if the file cannot be opened,
		// which means LOAD failed
		if (load_fail_message(fin, tok, load_fail))
			return;
		fprintf(stdout, "Loaded %s\n", tok);
		// Put the cursor back where it was before
		// closing + 1
		fseek(fin, pos + 1, SEEK_SET);
		// Reads the image's data
		read(image, fin);
		// Selects the whole image
		select_all(image);
		fclose(fin);
	}
}
