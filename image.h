// Copyright 2021-2022 313CA Mitran Andrei-Gabriel
#ifndef IMAGE_H
#define IMAGE_H

typedef struct {
	double ***colour;
	int height;
	int width;
	int maxx;
	int image_type;
	int file_type;
	int c[2][2];
} image_t;

#endif
