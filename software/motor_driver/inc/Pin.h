#pragma once

#ifndef PIN_H_
#define PIN_H_

#include "CObjects.h"
#include <stdbool.h>

#define Pin_ATTRIBUTES \
		int pin; \
		bool status;

#define Pin_METHODS \
    void (*toggle) (Pin);

DEFINE_BASE_TYPE(Pin, int)

#endif /* PIN_H_ */
