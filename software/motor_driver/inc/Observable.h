#pragma once

#ifndef OBSERVABLE_H_
#define OBSERVABLE_H_

#include "CObjects.h"
#include "List.h"
#include "Observer.h"

#define Observable_ATTRIBUTES \
    void* state; \
    List observers;

#define Observable_METHODS \
    void  (*observe)    (Observable, Observer); \
    void  (*setState)   (Observable, void*); \
    void *(*getState)   (Observable);

DEFINE_BASE_TYPE(Observable, void)

#endif /* OBSERVABLE_H_ */