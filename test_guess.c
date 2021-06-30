//
// Created by overlord on 2021/6/30.
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>

static FILE *Fcreate_writer(char *filepath);

int main() {
    char *split_file_name = malloc(4026);
    int ret = sprintf(split_file_name,
                      "split/phone-thread%lu-fileNo.%lu.txt",
                      1775090, 5);
    puts(split_file_name);
    putc('\n', stdout);

//    FILE *writer=fopen(split_file_name,"w");
    FILE *writer = Fcreate_writer("fuckinganimal/babaisyou.txt");
    fwrite_unlocked("baocaonidema\n", sizeof(char), 13, writer);

    return 0;
}

FILE *Fcreate_writer(char *filepath) {
    char *start = strdup(filepath);
    struct stat sti;

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

    FILE *writer = fopen(start, "w");
    free(start);
    return writer;
}