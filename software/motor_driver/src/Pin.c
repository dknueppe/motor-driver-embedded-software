#include <stdlib.h>
#include <wiringPi.h>
#include "Pin.h"

static void toggle(Pin self)
{
    self->status = !(self->status);
    digitalWrite(self->pin, self->status);
}

static PinClass cls = {
	.toggle = toggle,
};

Pin newPin(int num)
{
	Pin tmp = malloc(sizeof(*tmp));
	tmp->clazz = &cls;
	tmp->pin = num;
	tmp->status = false;
	pinMode(num, OUTPUT);
	digitalWrite(tmp->pin, 0);
	return tmp;
}

void deletePin(Pin self)
{
        digitalWrite(self->pin, LOW);
	free(self);
}
