//
// Created by overlord on 2021/6/18.
//
#include "number.h"

char *random_phone_number(time_t support) {
    srand(time(NULL) + (support * 13L));
    unsigned long register randv = (unsigned long) rand();

    randomize:
    while ((randv <<= 3) < RAND_LOW);
    randv %= RAND_MOD;
    if (randv < RAND_LOW)
        goto randomize;

    char *prefix;
    switch (randv % 3) {
        case 1:
            prefix = "136";
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
    sprintf(retstr, "%s%s", prefix, temp + (strlen(temp) - 8));
    free(temp);
    return retstr;
}