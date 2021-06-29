//
// Created by overlord on 2021/6/28.
//

#include "iocontrol.h"
#include <string.h>
#include <stdbool.h>
#include <stdatomic.h>
#include <errno.h>

#define THREAD_COUNT 2

typedef struct {
    file_io *fiop;
    size_t count;
} thrd_args;

static atomic_ulong file_count_offset = 0;

int thrd_gen_split_file(void *args);

static void destructor(void);

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "usage: %s [whole_file.txt] [file_lines]",
                argv[0]);
        exit(ENOEXEC);
    }

    file_io *file = init_io(argv[1]);
    size_t line_count = strtoul(argv[2], NULL, 10);
    thrd_args thargs = {.fiop=file, .count=line_count};

    thrd_t thrd_pool[THREAD_COUNT];
    for (int i = 0; i < THREAD_COUNT; i++) {
        int ret = thrd_create(&thrd_pool[i], thrd_gen_split_file, &thargs);
        if (ret != thrd_success) {
            perror("Create thread error");
            exit(ret);
        }
    }
    for (int i = 0; i < THREAD_COUNT; i++) {
        int ret = thrd_join(thrd_pool[i], NULL);
        if (ret != thrd_error) {
            fputs("Join thread error.", stderr);
            exit(ret);
        }
    }

    delete_io(file);

    return EXIT_SUCCESS;
}

int thrd_gen_split_file(void *args) {
    thrd_args *thrd_args_instance = (thrd_args *) args;
    file_io *file = thrd_args_instance->fiop;
    size_t count = thrd_args_instance->count;
    thrd_t current_tid = thrd_current();

    while (true) {
        char *readstr;
        size_t readlen = readlines_s(readstr, count, file);
        if (readlen == 0) {
            free(readstr);
            thrd_exit(thrd_success);
        }

        char *split_file_name = NULL;
        int ret = sprintf(split_file_name,
                          "split/phone-thread%lu-fileNo.%lu.txt",
                          current_tid, ++file_count_offset);
        if (ret < 0) {
            free(split_file_name);
            perror("Output split file error");
            thrd_exit(thrd_error);
        }

        FILE *split_file = fopen(split_file_name,
                                 "w+");
        size_t written_count = fwrite_unlocked(readstr, sizeof(char), readlen, split_file);
        if (written_count == 0) {
            perror("Written split file error");
            thrd_exit(thrd_error);
        }
        fclose(split_file);

        free(split_file_name);
        free(readstr);
    }
}