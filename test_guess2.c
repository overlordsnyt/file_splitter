//
// Created by overlord on 2021/6/30.
//

#include <stdio.h>
#include <xthreads.h>

int main() {
    puts("23123\n");
#ifdef _WINDOWS
    puts("macro defined WINDOWS.\n");
#else
    puts("macro not defined WINDOWS.\n");
#endif

    thrd_create()
}