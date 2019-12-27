#pragma once

#ifndef EXCEPTION_H_
#define EXCEPTION_H_

#include "CObjects.h"

#define Exception_ATTRIBUTES \
    char *error_msg;

#define Exception_METHODS \
    void (*print)(Exception);

DEFINE_BASE_TYPE(Exception, void)

#ifndef MAX_THREADS
#define MAX_THREADS 20
#endif

#include "cexcept.h"
define_exception_type(Exception);
struct exception_context the_exception_context[MAX_THREADS];

#endif /* EXCEPTION_H_ */
