#include <wiringPi.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "PWMObservable.h"
#include "PWMObserver.h"

int main()
{
    wiringPiSetup();
    PWMObservable pwm = newPWMObservable();
<<<<<<< HEAD
    pwm->frequency = 1000;
    pwm->dutyCycle = 20;
    PWMObserver in1 = newPWMObserver(25, false);
    PWMObserver in2 = newPWMObserver(26, true);
    PWMObserver enable = newPWMObserver(28, false);
    pwm->clazz->observe((Observable)pwm, (void*)in1);
    pwm->clazz->observe((Observable)pwm, (void*)in2);
    pwm->clazz->observe((Observable)pwm, (void*)enable);
=======
    pwm->frequency = 440;
    pwm->dutyCycle = 100;
    PWMObserver in1 = newPWMObserver(3, false);
    PWMObserver in2 = newPWMObserver(5, false);
    PWMObserver enable = newPWMObserver(4, false);
    pwm->clazz->observe((Observable)pwm, (void*)in1);
>>>>>>> d03de3371ecd86c9d0585a59be44f47ef6ad97a7
    pwm->clazz->start(pwm);
    for(unsigned int i = 0;; i+=3){
        pwm->clazz->setDutyCycle(pwm, i%100);
        usleep(100000);
    }
    volatile int foo = getchar();
    pwm->clazz->join(pwm);
    deletePWMObservable(pwm);
    deletePWMObserver(in1);
    deletePWMObserver(in2);
    deletePWMObserver(enable);
    return 0;
}
