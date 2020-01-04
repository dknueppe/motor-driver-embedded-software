#include <stdlib.h>
#include <wiringPi.h>
#include "Pin.h"

static void toggle(Pin self)
{
    self->status = !(self->status);
    digitalWrite(self->pin, self->status);
}

static void setPin(Pin self, int val)
{
    if(self->direction == OUTPUT)
        digitalWrite(self->pin, val);
}

static int readPin(Pin self)
{
    return digitalRead(self->pin);
}

static PinClass cls = {
    .toggle = toggle,
    .setPin = setPin,
    .readPin = readPin,
};

Pin newPin(int num, int direction)
{
    Pin tmp = malloc(sizeof(*tmp));
    tmp->clazz = &cls;
    tmp->direction = direction;
    tmp->pin = num;
    tmp->status = false;
    pinMode(num, direction);
    if(direction == OUTPUT)
        digitalWrite(tmp->pin, LOW);
    return tmp;
}

void deletePin(Pin self)
{
    free(self);
}