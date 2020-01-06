#pragma once

#ifndef TIMEROBSERVABLE_H_
#define TIMEROBSERVABLE_H_

#include <stdbool.h>
#include <semaphore.h>
#include <sys/types.h>
#include <pthread.h>
#include "Observable.h"

#define PWM_ENABLE  true
#define TIMER       false

#define TimerObservable_ATTRIBUTES \
    unsigned int    dutyCycle; \
    unsigned int    frequency; \
    bool           _is_running; \
    bool           _keep_running; \
    sem_t          _lock; \
    pthread_t      _thread_id; \
    bool            pwm;

#define TimerObservable_METHODS \
    void    (*setDutyCycle)     (TimerObservable, unsigned int); \
    void    (*setFrequency)     (TimerObservable, unsigned int); \
    void    (*start)            (TimerObservable); \
    void   *(*run)              (TimerObservable); \
    void    (*join)             (TimerObservable);
    
DEFINE_EXTENDED_TYPE(TimerObservable, Observable, bool)

#endif /* TIMEROBSERVABLE_H_*/
