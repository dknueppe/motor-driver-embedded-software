#pragma once

#ifndef FREQCOUNTER_H_
#define FREQCOUNTER_H_

#include <time.h>
#include <semaphore.h>
#include "CObjects.h"
#include "Observer.h"

#define FreqCounter_ATTRIBUTES \
    double          timediff; \
    struct timespec tv; \
    sem_t          _lock;

#define FreqCounter_METHODS \
    float (*getRPM) (FreqCounter);

DEFINE_EXTENDED_TYPE(FreqCounter, Observer, void)

#endif /* FREQCOUNTER_H_ */