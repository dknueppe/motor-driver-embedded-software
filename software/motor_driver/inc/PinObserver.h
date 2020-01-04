#pragma once

#ifndef PINOBSERVER_H_
#define PINOBSERVER_H_

#include <sys/time.h>
#include <semaphore.h>
#include "CObjects.h"
#include "Observer.h"

#define PinObserver_ATTRIBUTES \
    suseconds_t     timediff; \
    struct timeval  tv; \
    sem_t          _lock;

#define PinObserver_METHODS \
    float (*getRPM) (PinObserver);

DEFINE_EXTENDED_TYPE(PinObserver, Observer, void)

#endif /* PINOBSERVER_H_ */