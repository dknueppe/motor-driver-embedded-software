#pragma once

#ifndef ITERATOR_H_
#define ITERATOR_H_

#include "CObjects.h"

#define Iterator_ATTRIBUTES \
    void    *state;

#define Iterator_METHODS \
    void     (*next)       (Iterator); \
    void    *(*get_item)   (Iterator);

DEFINE_BASE_TYPE(Iterator, void)

#define Iterable_ATTRIBUTES

#define Iterable_METHODS \
    Iterator (*iter) (void*);

DEFINE_BASE_TYPE(Iterable, void)

//#define foreach(element, iterator) \
//    for(void *element; \
//        (element = iterator->clazz->get_item(iterator)); \
//        iterator->clazz->next(iterator))

#define foreach(element, iterable) \
    for(void *element, *iter = iterable->clazz->iter(iterable); \
        (element = ((Iterator)iter)->clazz->get_item(iter)); \
        ((Iterator)iter)->clazz->next(iter))

#endif /* ITERATOR_H_ */