#pragma once

#ifndef OBSERVER_H_
#define OBSERVER_H_

#include <semaphore.h>
#include "CObjects.h"

#define Observer_ATTRIBUTES \
    sem_t _lock;

#define Observer_METHODS \
    void (*update)(Observer, void *);

DEFINE_BASE_TYPE(Observer, void)

#endif /* OBSERVER_H_ */
