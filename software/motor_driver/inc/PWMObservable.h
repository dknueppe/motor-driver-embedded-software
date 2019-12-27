#pragma once

#ifndef PWMOBSERVABLE_H_
#define PWMOBSERVABLE_H_

#include <stdbool.h>
#include <semaphore.h>
#include <sys/types.h>
#include <pthread.h>
#include "Observable.h"

#define PWMObservable_ATTRIBUTES \
    unsigned int    dutyCycle; \
    unsigned int    frequency; \
    bool           _is_running; \
    bool           _keep_running; \
    sem_t          _lock; \
    pthread_t      _thread_id;

#define PWMObservable_METHODS \
    void    (*setDutyCycle)     (PWMObservable, unsigned int); \
    void    (*setFrequency)     (PWMObservable, unsigned int); \
    void    (*start)            (PWMObservable); \
    void   *(*run)              (PWMObservable); \
    void    (*join)             (PWMObservable);
    
DEFINE_EXTENDED_TYPE(PWMObservable, Observable, void)

#endif /* PWMOBSERVABLE_H_*/
