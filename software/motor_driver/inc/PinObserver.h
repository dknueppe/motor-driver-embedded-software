#pragma once

#ifndef PINOBSERVER_H_
#define PINOBSERVER_H_

#include <time.h>
#include <semaphore.h>
#include "CObjects.h"
#include "Observer.h"

#define PinObserver_ATTRIBUTES \
    double          timediff; \
    struct timespec tv; \
    sem_t          _lock;

#define PinObserver_METHODS \
    float (*getRPM) (PinObserver);

DEFINE_EXTENDED_TYPE(PinObserver, Observer, void)

#endif /* PINOBSERVER_H_ */