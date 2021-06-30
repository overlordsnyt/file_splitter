//
// Created by overlord on 2021/7/1.
//

#define BUFSIZ 4096

#ifndef PRACTICE1_COMPABILITY_H
#define PRACTICE1_COMPABILITY_H
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

#endif //PRACTICE1_COMPABILITY_H
