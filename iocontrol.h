//
// Created by overlord on 2021/6/29.
//

#ifndef PRACTICE1_IOCONTROL_H
#define PRACTICE1_IOCONTROL_H

#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

#define LINE_SIZE_GUESS 15

typedef struct _io_struct_ {
    mtx_t *mutex;
    FILE *fd_ptr;
    off_t t;
    size_t exist;
    char buff[BUFSIZ + 1];
} file_io;

file_io *init_io(char *filename);

size_t readlines_s(char *lines, size_t line_count, file_io *file);

void delete_io(file_io *file);


#endif //PRACTICE1_IOCONTROL_H
