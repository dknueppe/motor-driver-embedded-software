#include <stdlib.h>
#include "PinObserver.h"

static void update(PinObserver self)
{
    struct timeval tv;
    gettimeofday(&tv, NULL);
    sem_wait(&(self->_lock));
    self->timediff = tv.tv_usec - (self->tv.tv_usec);
    sem_post(&(self->_lock));
}

#define USEC_PER_SEC 1000000
static float getRPM(PinObserver self)
{
    sem_wait(&(self->_lock));
    suseconds_t tmp = self->timediff;
    sem_post(&(self->_lock));
    return  60 * USEC_PER_SEC / tmp;
}

static PinObserverClass cls = {
    .update = update,
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
