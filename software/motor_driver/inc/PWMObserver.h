#pragma once

#ifndef PWMOBSERVER_H_
#define PWMOBSERVER_H_

#include <stdbool.h>
#include <semaphore.h>
#include "Observer.h"
#include "Pin.h"

#define PWMObserver_ATTRIBUTES \
    Pin     pin; \
    sem_t  _lock;

#define PWMObserver_METHODS \

DEFINE_EXTENDED_TYPE(PWMObserver, Observer, int, bool)
//DEFINE_BASE_TYPE(PWMObserver, int, bool)

#endif /* PWMOBSERVER_H_ */