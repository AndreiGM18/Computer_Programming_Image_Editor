// Copyright 2021-2022 313CA Mitran Andrei-Gabriel
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "image.h"
#include "basic.h"

// Writes the image's data, either in an ascii file or a binary file
void write(image_t *image, int new_file_type, FILE *f)
{
	unsigned char x;

	// Gets the number of pixels
	int n_pixels = 1;
	if (image->image_type == 2)
		n_pixels = 3;

	// Writes an unsigned char, that was obtained using a cast,
	// from the original image's data, recently scanned value,
	// regardless of the file type
	if (!new_file_type) {
		for (int i = 0; i < image->height; ++i) {
			for (int j = 0; j < image->width; ++j)
				for (int k = 0; k < n_pixels; ++k) {
					// Ascii
					x = (unsigned char)round(image->colour[i][j][k]);
					fprintf(f, "%hhu ", x);
			}
			fprintf(f, "\n");
		}
	} else {
		for (int i = 0; i < image->height; ++i)
			for (int j = 0; j < image->width; ++j)
				for (int k = 0; k < n_pixels; ++k) {
					// Binary
					x = (unsigned char)round(image->colour[i][j][k]);
					fwrite(&x, sizeof(unsigned char), 1, f);
			}
	}
}

// Writes the magic word. that is identified by the image's type
// (black and white, grayscale or rgb) and the file's type (ascii
// or binary)
void write_type(image_t *image, int new_file_type, FILE *f)
{
	if (!new_file_type) {
		if (image->image_type == 0)
			fprintf(f, "P1");
		else if (image->image_type == 1)
			fprintf(f, "P2");
		else
			fprintf(f, "P3");
	} else {
		if (image->image_type == 0)
			fprintf(f, "P4");
		else if (image->image_type == 1)
			fprintf(f, "P5");
		else
			fprintf(f, "P6");
	}
}

// Does the SAVE command
void save_command(image_t *image, int load_fail, char *tok, int new_file_type)
{
	// Returns if LOAD failed
	if (load_fail == 1) {
		fprintf(stdout, "No image loaded\n");
	} else {
		// Gets the file's name (in which to write)
		tok = strtok(NULL, "\n ");

		// Returns if SAVE does not have a parameter after it
		if (!tok) {
			printf("Invalid command\n");
			return;
		}

		// Open file in ascii write mode
		FILE *fout = fopen(tok, "wt");

		// Returns if the file cannot be opened
		if (open_fail_message(fout, tok))
			return;

		// Writes magic word
		write_type(image, new_file_type, fout);

		// Writes width, height and the max value (only
		// for grayscale and rgb)
		if (image->image_type == 0) {
			fprintf(fout, "\n%d %d\n", image->width, image->height);
		} else {
			fprintf(fout, "\n%d %d\n", image->width, image->height);
			fprintf(fout, "%d\n", image->maxx);
		}

		// Continues writing in ascii write mode
		if (!new_file_type) {
			// Writes the image's data
			write(image, new_file_type, fout);

			fprintf(stdout, "Saved %s\n", tok);

			fclose(fout);
		// Writes in binary append mode
		} else {
			// Closes the file
			fclose(fout);

			// Reopens it
			FILE *fout = fopen(tok, "ab");

			// Returns if the file cannot be opened,
			if (open_fail_message(fout, tok))
				return;

			// Writes the image's data
			write(image, new_file_type, fout);

			fprintf(stdout, "Saved %s\n", tok);

			fclose(fout);
		}
	}
}
