#include <stdlib.h>
#include "PinObserver.h"

static void update(PinObserver self)
{
    struct timespec current_time;
    clock_gettime(CLOCK_MONOTONIC, &current_time);
    sem_wait(&(self->_lock));
    self->timediff = (current_time.tv_sec - self->tv.tv_sec)
                   + (current_time.tv_nsec - self->tv.tv_nsec)
                   / 1E9 ;
    self->tv = current_time;
    sem_post(&(self->_lock));
}

static float getRPM(PinObserver self)
{
    sem_wait(&(self->_lock));
    double tmp = self->timediff;
    sem_post(&(self->_lock));
    return 60 / tmp;
}

static PinObserverClass cls = {
    .update = (void(*)(Observer))update,
    .getRPM = getRPM,
};

PinObserver newPinObserver()
{
    PinObserver tmp = malloc(sizeof(*tmp));
    tmp->clazz = &cls;
    sem_init(&(tmp->_lock), 0, 1);
    return tmp;
}

void deletePinObserver(PinObserver self)
{
    sem_destroy(&(self->_lock));
    free(self);
}
