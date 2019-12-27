#include <stdlib.h>
#include "List.h"

static void *get_item(Iterator iter)
{
    ListNode tmp = iter->state;
    if(tmp)
        return tmp->data; // Datarace
    deleteIterator(iter);
    return NULL;
}

static void next(Iterator iter)
{
    iter->state = ((ListNode)iter->state)->next;
}

static IteratorClass iter_cls = {
    .next = next,
    .get_item = get_item
};

Iterator newIterator()
{
    Iterator tmp = malloc(sizeof(*tmp));
    tmp->clazz = &iter_cls;
    return tmp;
}

void deleteIterator(Iterator iter) { free(iter); }

static ListNode newListNode(void *data)
{
    ListNode tmp = malloc(sizeof(*tmp));
    tmp->data = data;
    tmp->next = NULL;
    return tmp;
}

void deleteListNodes(ListNode node);
void deleteListNodes(ListNode node)
{
    for(ListNode tmp = node; tmp;) {
        tmp = node->next;
        free(node);
        node = tmp;
    }
}

static void append(List self, void* data)
{
    ListNode node = newListNode(data);
    if (self->head == NULL)
        self->head = node;
    if (self->tail != NULL)
        self->tail->next = node;
    self->tail = node;
}

static Iterator iter(void *self)
{
    List list = self;
    Iterator tmp = newIterator();
    tmp->state = list->head;
    return tmp;
}

static ListClass cls = {
    .append = append,
    .iter = iter,
};

List newList(void)
{
    List tmp = malloc(sizeof(*tmp));
    tmp->clazz = &cls;
    tmp->head = NULL;
    tmp->tail = NULL;
    return tmp;
}

void deleteList(List list)
{
    if (list->head)
        deleteListNodes(list->head);
    free(list);
}
