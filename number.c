//
// Created by overlord on 2021/6/18.
//
#include "number.h"

char *randomPhoneNumber(time_t support) {
    srand(time(NULL) + (support * 13L));
    unsigned long randv = (unsigned long) rand() % RAND_BOUND;
    while ((randv <<= 3) < RAND_LOW);
    randv %= RAND_BOUND;

    char *prefix;
    switch (randv % 3) {
        case 1:
            prefix = "135";
            break;
        case 2:
            prefix = "185";
            break;
        default:
            prefix = "150";
    }
    //TODO remember free this who quoted
    char *retstr = malloc(15 * sizeof(char));
    char *temp = malloc(10 * sizeof(char));
    sprintf(temp, "%lu", randv);
    sprintf(retstr, "%s%s", prefix, temp + 1);
    free(temp);
    return retstr;
}