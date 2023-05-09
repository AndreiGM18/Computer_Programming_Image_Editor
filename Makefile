# Copyright 2021-2022 313CA Mitran Andrei-Gabriel
CC=gcc

CFLAGS=-Wall -Wextra -std=c99

TARGETS=image_editor

build: $(TARGETS)

image_editor: image_editor.c
		$(CC) $(CFLAGS) -g image_editor.c -o image_editor exit.c basic.c load.c mem_err.c save.c select.c crop.c rotate.c apply.c -lm

pack:
		zip -FSr 313CA_MitranAndreiGabriel_Tema3.zip README Makefile *.c *.h

clean:
		rm -f $(TARGETS)

.PHONY: pack clean