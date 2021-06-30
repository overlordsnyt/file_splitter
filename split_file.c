//
// Created by overlord on 2021/6/28.
//

#include "compability.h"
#include "iocontrol.h"
#include <string.h>
#include <stdbool.h>
#include <errno.h>
#include <sys/stat.h>

#define THREAD_COUNT 4
#define FILENAME_BUFF 256

static file_io *file;
static size_t line_count;
static size_t lines_maxlen;

static unsigned long file_count_offset = 0;

int thrd_gen_split_file(void *args);

static void destructor(void);

static FILE *Fcreate_writer(char *filepath);

static mtx_t *mkdir_mutex;
static mtx_t *file_count_mutex;

int main(int argc, char *argv[]) {
    if (argc != 3) {
        fprintf(stderr, "usage: %s [whole_file.txt] [file_lines]",
                argv[0]);
        exit(ENOEXEC);
    }

    file = init_io(argv[1]);
    line_count = strtoul(argv[2], NULL, 10);
    lines_maxlen = line_count * LINE_SIZE_GUESS * sizeof(char);
    mkdir_mutex = malloc(sizeof(mtx_t));
    file_count_mutex = malloc(sizeof(mtx_t));
    if (mtx_init(mkdir_mutex, mtx_plain) == thrd_error)
        perror("Initial mkdir mutex error");
    if (mtx_init(file_count_mutex, mtx_plain) == thrd_error)
        perror("Initial file count mutex error");

    thrd_t thrd_pool[THREAD_COUNT];
    for (int i = 0; i < THREAD_COUNT; i++) {
        int ret = thrd_create(&thrd_pool[i], thrd_gen_split_file, NULL);
        if (ret != thrd_success) {
            perror("Create thread error");
            exit(ret);
        }
    }
    for (int i = 0; i < THREAD_COUNT; i++) {
        int ret = thrd_join(thrd_pool[i], NULL);
        if (ret == thrd_error) {
            fputs("Join thread error.", stderr);
            exit(ret);
        }
    }

    mtx_destroy(file_count_mutex);
    mtx_destroy(mkdir_mutex);
    delete_io(file);

    return EXIT_SUCCESS;
}

int thrd_gen_split_file(void *args) {
#ifdef _WINDOWS
    _Thrd_id_t current_tid = thrd_current();
#else
    thrd_t current_tid = thrd_current();
#endif
    while (true) {
        char *readstr = malloc(lines_maxlen);
        memset(readstr, 0, lines_maxlen);
        size_t readlen = readlines_s(readstr, line_count, file);
        if (readlen == 0) {
            thrd_exit(thrd_success);
        }

        char *split_file_name = malloc(FILENAME_BUFF);
        mtx_lock(file_count_mutex);
        int ret = sprintf(split_file_name,
                          "split/phone-thread%lu-fileNo.%lu.txt",
                          current_tid, ++file_count_offset);
        mtx_unlock(file_count_mutex);
        if (ret < 0) {
            perror("Output split file error");
            thrd_exit(thrd_error);
        }

        FILE *split_file = Fcreate_writer(split_file_name);
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

FILE *Fcreate_writer(char *filepath) {
    char *start = strdup(filepath);
    struct stat sti;

    mtx_lock(mkdir_mutex);
    for (char *sep = strchr(start, '/');
         sep != NULL;
         sep = strchr(sep + 1, '/')) {
        if (start == sep) {
            ++sep;
            continue;
        }
        *sep = '\0';

        if (stat(start, &sti) != 0) {
            int ret = mkdir(start, S_IFDIR | S_IRWXU | S_IRWXO);
            if (ret != 0)
                perror("Create directory error");
        }
        *sep = '/';
    }
    mtx_unlock(mkdir_mutex);

    FILE *writer = fopen(start, "w");
    free(start);
    return writer;
}