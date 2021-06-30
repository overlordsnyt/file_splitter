#include "number.h"

int write_file(void *args);

void Thrd_join(thrd_t t);

int main() {
    FILE *phone_file_ptr = fopen("gen_phone.txt", "w");

    thrd_t t1;
    thrd_create(&t1, &write_file, (void *) phone_file_ptr);
    thrd_t t2;
    thrd_create(&t2, &write_file, (void *) phone_file_ptr);

    Thrd_join(t1);
    Thrd_join(t2);

    fclose(phone_file_ptr);

    return EXIT_SUCCESS;
}

int write_file(void *args) {
    FILE *phone_file_ptr = (FILE *) args;

    for (size_t register buf_len = 0; buf_len < BUFSIZ; buf_len += 12) {
        char *gen_phone = random_phone_number(thrd_current() - buf_len);
        fprintf(phone_file_ptr, "%s\n", gen_phone);
        free(gen_phone);
    }
    return thrd_success;
}

void Thrd_join(thrd_t t) {
    int exit_code;
    thrd_join(t, &exit_code);
    if (exit_code != thrd_success) {
#ifdef _WINDOWS
        fprintf(stderr, "[%s:%d] Threading %u join thread error. [%s]", __FILE__, __LINE__, t._Id, strerror(exit_code));
#else
        fprintf(stderr, "[%s:%d] Threading %lu join thread error. [%s]", __FILE__, __LINE__, t, strerror(exit_code));
#endif
        exit(thrd_error);
    }
}



