//
// Created by overlord on 2021/6/29.
//

#include "iocontrol.h"
#include <string.h>


static size_t readfill_un(file_io *file);

file_io *init_io(char *filename) {
    file_io *iop = malloc(sizeof(file_io));

    mtx_t *mutex = malloc(sizeof(mtx_t));
    if (mtx_init(mutex, mtx_plain) == thrd_error) {
        perror("Initial mutex error.");
        exit(EXIT_FAILURE);
    }
    iop->mutex = mutex;

    memset(iop->buff, 0, BUFSIZ + 1);
    iop->exist = 0;
    iop->t = 0;

    FILE *opf = fopen(filename, "r");
    if (opf == NULL) {
        perror("Open filename error.");
        exit(EXIT_FAILURE);
    }
    iop->fd_ptr = opf;

    return iop;
}

void delete_io(file_io *file) {
    fclose(file->fd_ptr);
    mtx_destroy(file->mutex);
    free(file);
}

size_t readlines_s(char *lines, size_t line_count, file_io *file) {
    mtx_lock(file->mutex);
    size_t register tt = (size_t) file->t;
    size_t exist = file->exist;
    size_t register read_index = 0;
    size_t read_line_count = 0;
    //TODO free read lines str
    while (read_line_count < line_count) {
        if (tt >= exist) {
            size_t sz = readfill_un(file);
            if (sz == 0 && feof(file->fd_ptr))
                break;
            exist = file->exist;
            tt = (size_t) file->t;
        }
        char nowchar = file->buff[tt];
        lines[read_index++] = nowchar;
        if (nowchar == '\n')
            ++read_line_count;
        ++tt;
    }
    file->t = (off_t) tt;
    mtx_unlock(file->mutex);
    return read_index;
}

size_t readfill_un(file_io *file) {
//    if (file->t < (long) file->exist) {
//        fprintf(stderr, "No need to fill new buff. remain: %ld\n", (long) file->exist - file->t);
//        exit(EXIT_FAILURE);
//    }
    size_t reading = fread_unlocked(file->buff, sizeof(char), BUFSIZ, file->fd_ptr);
    if (reading < BUFSIZ) {
        if (ferror(file->fd_ptr)) {
            perror("Read file stream error.");
            exit(EXIT_FAILURE);
        }
    }
    file->exist = reading;
    file->t = 0;
    return reading;
}
