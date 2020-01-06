#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include "CObjects.h"
#include "Iterator.h"
#include "TimerObservable.h"
#include "Observer.h"

static void setDutyCycle(TimerObservable self, unsigned int dc)
{
    sem_wait(&(self->_lock));
    self->dutyCycle = dc;
    sem_post(&(self->_lock));
}

static void setFrequency(TimerObservable self, unsigned int freq)
{
    sem_wait(&(self->_lock));
    self->frequency = freq;
    sem_post(&(self->_lock));
}

#define USEC_PER_SEC 1000000u
static void *run(TimerObservable self)
{
    //TODO
}

static void start(TimerObservable self)
{
    if (self->_is_running)
        return;
    self->_keep_running = true;
    self->_is_running = true;
    pthread_create(&(self->_thread_id), NULL, (void*(*)(void*))run, self);
}

static void join(TimerObservable self)
{
    sem_wait(&(self->_lock));
    self->_keep_running = false;
    sem_post(&(self->_lock));
    pthread_join(self->_thread_id, NULL);
}

static TimerObservableClass cls = {
    .setDutyCycle = setDutyCycle,
    .setFrequency = setFrequency,
    .start = start,
    .run = run,
    .join = join,
};

TimerObservable newTimerObservable(bool pwm_enable)
{
    TimerObservable tmp = malloc(sizeof(*tmp));
    tmp->clazz = &cls;
    if (cls.observe == NULL) {
        Observable observable = newObservable();
        memcpy(&cls, observable->clazz, sizeof(*(observable->clazz)));
        deleteObservable(observable);
    }
    tmp->pwm = pwm_enable;
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

void deleteTimerObservable(TimerObservable self)
{
    deleteList(self->observers);
    sem_destroy(&(self->_lock));
    free(self->state);
    free(self);
}
