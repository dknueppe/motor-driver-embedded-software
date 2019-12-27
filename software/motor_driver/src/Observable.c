#include <stdlib.h>
#include "Observable.h"

static void observe(Observable self, Observer observer)
{
    self->observers->clazz->append(self->observers, observer);
}

static void setState(Observable self, void *args)
{
    self->state = args;
}

static void *getState(Observable self)
{
    return self->state;
}

static ObservableClass cls = {
    .observe = observe,
    .setState = setState,
    .getState = getState,
};

Observable newObservable(void) 
{
    Observable tmp = malloc(sizeof(*tmp));
    tmp->clazz = &cls;
    tmp->observers = malloc(sizeof(*(tmp->observers)));
    tmp->observers->head = NULL;
    tmp->observers->tail = NULL;
    return tmp;
}

void deleteObservable(Observable self)
{
    if(self->observers->head != NULL)
        deleteList(self->observers);
    free(self->observers);
    free(self);
}