#pragma once

#ifndef PINOBSERVABLE_H_
#define PINOBSERVABLE_H_

#include "CObjects.h"
#include "Observable.h"
#include "Pin.h"

#define PinObservable_ATTRIBUTES \
    Pin         pin; \
    bool       _is_running; \
    bool       _keep_running; \
    sem_t      _lock; \
    pthread_t  _thread_id;

#define PinObservable_METHODS \
    void    (*start)(PinObservable); \
    void   *(*run)  (PinObservable); \
    void    (*join) (PinObservable);

DEFINE_EXTENDED_TYPE(PinObservable, Observable, int)

#endif /* PINOBSERVABLE_H_ */