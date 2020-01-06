#pragma once

#ifndef PINOBSERVER_H_
#define PINOBSERVER_H_

#include <stdbool.h>
#include <semaphore.h>
#include "Observer.h"
#include "Pin.h"

#define PinObserver_ATTRIBUTES \
    Pin     pin; \
    sem_t  _lock;

#define PinObserver_METHODS \

DEFINE_EXTENDED_TYPE(PinObserver, Observer, int, bool)

#endif /* PINOBSERVER_H_ */