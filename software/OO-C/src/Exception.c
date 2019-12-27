#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "Exception.h"

static void print(Exception e)
{
    fprintf(stderr, "Error occured in File %s at Line %d in Function %s. \n%s\n",
            __FILE__, __LINE__, __func__, e->error_msg);
}

static ExceptionClass cls = {
    .print = print
};

Exception newException()
{
    Exception tmp;
    tmp = malloc(sizeof(*tmp));
    tmp->clazz = &cls;
    tmp->error_msg = "";
    return tmp;
}
