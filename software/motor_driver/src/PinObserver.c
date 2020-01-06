#include <wiringPi.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>
#include "PinObserver.h"

static void update(PinObserver self)
{
    sem_wait(&(self->_lock));
    self->pin->clazz->toggle(self->pin);
    sem_post(&(self->_lock));
}

static PinObserverClass cls = {
    .update = (void(*)(Observer))update,
};

PinObserver newPinObserver(int pin, bool status)
{
    PinObserver tmp = malloc(sizeof(*tmp));
    tmp->clazz = &cls;
    tmp->pin = newPin(pin, OUTPUT);
    sem_init(&(tmp->_lock), 0, 1);
    if(!status)
        tmp->pin->clazz->toggle(tmp->pin);
    return tmp;
}

void deletePinObserver(PinObserver self) {
    sem_destroy(&(self->_lock));
    deletePin(self->pin);
    free(self);
}
