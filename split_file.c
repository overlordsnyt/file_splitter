//
// Created by overlord on 2021/6/28.
//

#include "iocontrol.h"
#include <string.h>


FILE *Fopen_read(char *src);


int main(int argc, char *argv[]) {
//    printf("args count: %d\narg2 is '%s'", argc, argv[1]);
    if (argc != 3) {
        fprintf(stderr, "usage: %s [whole_file.txt] [file_lines]",
                argv[0]);
        exit(EXIT_FAILURE);
    }

    file_io *file = init_io(argv[1]);
    size_t line_count = strtoul(argv[2], NULL, 10);

//    printf("argv[2] = %zu",line_count);

    char *readstr = readlines_s(file, line_count);
    printf("read lines:\n%s", readstr);
    free(readstr);

    delete_io(file);


    return EXIT_SUCCESS;
}