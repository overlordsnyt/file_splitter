//
// Created by overlord on 2021/6/29.
//

#ifndef PRACTICE1_IOCONTROL_H
#define PRACTICE1_IOCONTROL_H

#include <stdio.h>
#include <stdlib.h>
#include <threads.h>

typedef struct _io_struct_ {
    mtx_t *mutex;
    FILE *fd_ptr;
    off_t t;
    size_t exist;
    char buff[BUFSIZ + 1];
} file_io;

file_io *init_io(char *filename);

char *readlines_s(file_io *file, size_t line_count);

void delete_io(file_io *file);


#endif //PRACTICE1_IOCONTROL_H
