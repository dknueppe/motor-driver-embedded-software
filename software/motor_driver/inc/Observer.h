#pragma once

#ifndef OBSERVER_H_
#define OBSERVER_H_

#include <semaphore.h>
#include "CObjects.h"

#define Observer_ATTRIBUTES \

#define Observer_METHODS \
    void (*update)(Observer);

DEFINE_BASE_TYPE(Observer, void)

#endif /* OBSERVER_H_ */
