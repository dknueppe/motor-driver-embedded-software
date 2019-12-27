#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "CObjects.h"
#include "Iterator.h"
#include "PWMObservable.h"
#include "PWMObserver.h"

static void setDutyCycle(PWMObservable self, unsigned int dc)
{
    sem_wait(&(self->_lock));
    self->dutyCycle = dc;
    sem_post(&(self->_lock));
}

static void setFrequency(PWMObservable self, unsigned int freq)
{
    sem_wait(&(self->_lock));
    self->frequency = freq;
    sem_post(&(self->_lock));
}

#define USEC_PER_SEC 1000000u
static void *run(PWMObservable self)
{
    unsigned int on_time, off_time, period_us;
    bool keep_running = true;
    while (keep_running) {
        sem_wait(&(self->_lock));
        keep_running = self->_keep_running;
        period_us = USEC_PER_SEC / self->frequency;
        on_time = period_us * self->dutyCycle / 100;
        sem_post(&(self->_lock));
        off_time = period_us - on_time;
        foreach_iterable(observer, self->observers)
            ((PWMObserver)observer)->clazz->update(observer);
        usleep(on_time);
        foreach_iterable(observer, self->observers)
            ((PWMObserver)observer)->clazz->update(observer);
        usleep(off_time);
    }
    return NULL;
}

static void start(PWMObservable self)
{
    if (self->_is_running)
        return;
    self->_keep_running = true;
    self->_is_running = true;
    pthread_create(&(self->_thread_id), NULL, (void*(*)(void*))run, self);
}

static void join(PWMObservable self)
{
    sem_wait(&(self->_lock));
    self->_keep_running = false;
    sem_post(&(self->_lock));
    pthread_join(self->_thread_id, NULL);
}

PWMObservableClass cls = {
    .setDutyCycle = setDutyCycle,
    .setFrequency = setFrequency,
    .start = start,
    .run = run,
    .join = join,
};

PWMObservable newPWMObservable(void)
{
    PWMObservable tmp = malloc(sizeof(*tmp));
    tmp->clazz = &cls;
    if (cls.observe == NULL) {
        Observable observable = newObservable();
        memcpy(&cls, observable->clazz, sizeof(*(observable->clazz)));
        deleteObservable(observable);
    }
    tmp->_is_running = false;
    tmp->_keep_running = false;
    tmp->observers = newList();
    tmp->dutyCycle = 20;
    tmp->frequency = 10;
    tmp->state = malloc(sizeof(bool));
    *((bool *)(tmp->state)) = true;
    sem_init(&(tmp->_lock), 0, 1);
    return tmp;
}

void deletePWMObservable(PWMObservable self)
{
    deleteList(self->observers);
    sem_destroy(&(self->_lock));
    free(self->state);
    free(self);
}
