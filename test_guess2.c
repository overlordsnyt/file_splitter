//
// Created by overlord on 2021/6/30.
//

#include <stdio.h>
#include <stdlib.h>

#ifdef _WINDOWS

#include <thr/xthreads.h>

typedef _Thrd_t thrd_t;
#define thrd_create  _Thrd_create
#define thrd_exit    _Thrd_exit
#define thrd_join    _Thrd_join
#define thrd_success _Thrd_success
#define thrd_error   _Thrd_error
#define thrd_current() _Thrd_id()

typedef _Mtx_t mtx_t;
#define mtx_init(x, y) _Mtx_init(x ,y)
#define mtx_destroy(x) _Mtx_destroy(*x)
#define mtx_plain _Mtx_plain
#define mtx_lock(x) _Mtx_lock(*x)
#define mtx_unlock(x) _Mtx_unlock(*x)

#else
#include <threads.h>
#endif

#define THREADSNUM 4

int thrd_func(void *args);

mtx_t *mutex;

int main() {
    thrd_t threads[THREADSNUM];
    char *trash[THREADSNUM];
    mutex = malloc(sizeof(mtx_t));
    mtx_init(mutex, mtx_plain);
    for (int i = 0; i < THREADSNUM; ++i) {
        trash[i] = malloc(20);
        sprintf(trash[i], "It's %d thread.", i + 1);
        thrd_create(&threads[i], thrd_func, trash[i]);
    }

    for (int i = 0; i < THREADSNUM; ++i) {
        int ret = thrd_join(threads[i], NULL);
        free(trash[i]);
    }

    mtx_destroy(mutex);
    return 0;
}

int thrd_func(void *args) {
    char *str = (char *) args;
    mtx_lock(mutex);
    printf("Thread %u deliver message: %s\n", thrd_current(), str);
    mtx_unlock(mutex);
    return thrd_success;
}