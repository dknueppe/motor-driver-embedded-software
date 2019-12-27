#pragma once

#ifndef LIST_H_
#define LIST_H_

#include "Iterator.h"

typedef struct ListNode *ListNode;

#define List_ATTRIBUTES \
    unsigned int len; \
    ListNode head; \
    ListNode tail;

#define List_METHODS \
    void        (*append)   (List, void*);

DEFINE_EXTENDED_TYPE(List, Iterable, void)

struct ListNode {
    ListNode    next;
    void       *data;
};

#endif /* LIST_H_ */
