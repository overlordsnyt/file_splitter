#include "number.h"

int main() {
    char *phone = randomPhoneNumber(1);
    printf("Random range [0,%d]\nphone number: %s\nphone string length:%zu\n",
           RAND_BOUND,
           phone,
           strlen(phone));
    free(phone);
    return 0;
}
