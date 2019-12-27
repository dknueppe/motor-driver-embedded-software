#include <wiringPi.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "PWMObserver.h"

static void update(PWMObserver self)
{
    sem_wait(&(self->_lock));
    self->pin->clazz->toggle(self->pin);
    sem_post(&(self->_lock));
}

static PWMObserverClass cls = {
    .update = update,
};

PWMObserver newPWMObserver(int pin, bool status)
{
    PWMObserver tmp = malloc(sizeof(*tmp));
    tmp->clazz = &cls;
    tmp->pin = newPin(pin);
    sem_init(&(tmp->_lock), 0, 1);
    if(!status)
        tmp->pin->clazz->toggle(tmp->pin);
    return tmp;
}

void deletePWMObserver(PWMObserver self) {
    sem_destroy(&(self->_lock));
    deletePin(self->pin);
    free(self);
}
