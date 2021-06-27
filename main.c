#include "number.h"

#define MAXBUFF 4096

void write_file();

int main() {
    write_file();
    return 0;
}

void write_file() {
    FILE *phone_file_ptr = fopen("gen_phone.txt", "w+");
    for (size_t buf_len = 0; buf_len < MAXBUFF; buf_len += 12) {
        char *gen_phone = random_phone_number(buf_len);
        fprintf(phone_file_ptr, "%s\n", gen_phone);
        free(gen_phone);
    }
    fclose(phone_file_ptr);
}
