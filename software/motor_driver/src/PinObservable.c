#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
#include "wiringPi.h"
#include "Observer.h"
#include "PinObservable.h"

#define USEC_PER_SEC 1000000u
#define PERIOD 1000
static void *run(PinObservable self)
{
    int status = 0;
    int tmp;
    bool keep_running = true;
    while (keep_running) {
        sem_wait(&(self->_lock));
        keep_running = self->_keep_running;
        sem_post(&(self->_lock));
        tmp = self->pin->clazz->readPin(self->pin);
        if (!status && tmp)
            foreach(observer, self->observers)
                ((Observer)observer)->clazz->update(observer);
        status = tmp;
        usleep(PERIOD);
    }
    return NULL;
}

static void start(PinObservable self)
{
    if (self->_is_running)
        return;
    self->_keep_running = true;
    self->_is_running = true;
    pthread_create(&(self->_thread_id), NULL,
        (void*(*)(void*))self->clazz->run, self);
}

static void join(PinObservable self)
{
    sem_wait(&(self->_lock));
    self->_keep_running = false;
    sem_post(&(self->_lock));
    pthread_join(self->_thread_id, NULL);
}

static PinObservableClass cls = {
    .run = run,
    .join = join,
    .start = start,
};

PinObservable newPinObservable(int pin)
{
    PinObservable tmp = malloc(sizeof(*tmp));
    tmp->clazz = &cls;
    tmp->pin = newPin(pin, INPUT);
    if (cls.observe == NULL) {
        Observable observable = newObservable();
        memcpy(&cls, observable->clazz, sizeof(*(observable->clazz)));
        deleteObservable(observable);
    }
    tmp->_is_running = false;
    tmp->_keep_running = false;
    tmp->observers = newList();
    tmp->state = NULL;
    sem_init(&(tmp->_lock), 0, 1);
    return tmp;
}

void deletePinObservable(PinObservable self)
{
    sem_destroy(&(self->_lock));
    deletePin(self->pin);
    free(self);
}
