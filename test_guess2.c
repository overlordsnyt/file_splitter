//
// Created by overlord on 2021/6/30.
//

#include <stdio.h>
#include <stdlib.h>

#ifdef _WINDOWS

#include <thr/xthreads.h>

#define THREAD_HEAD(TAILNAME) _Thrd_ ## TAILNAME
#define THREAD_CURRENT _Thrd_current()._Id
#else

#include <threads.h>

#define THREAD_HEAD(TAILNAME) thrd_ ## TAILNAME
#define THREAD_CURRENT thrd_current()
#endif

#define THREADSNUM 4

int thrd_func(void *args);

int main() {
    THREAD_HEAD(t) threads[THREADSNUM];
    char *trash[THREADSNUM];

    for (int i = 0; i < THREADSNUM; ++i) {
        trash[i] = malloc(20);
        sprintf(trash[i], "It's %d thread.", i + 1);
        THREAD_HEAD(create)(&threads[i], thrd_func, trash[i]);
    }

    for (int i = 0; i < THREADSNUM; ++i) {
        int ret = THREAD_HEAD(join)(threads[i], NULL);
        free(trash[i]);
    }

    return 0;
}

int thrd_func(void *args) {
    char *str = (char *) args;
    printf("Thread %u deliver message: %s\n", THREAD_CURRENT, str);
//    _Thrd_current()._Id
    return THREAD_HEAD(success);
}