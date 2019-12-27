//#include <wiringPi.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "PWMObservable.h"
#include "PWMObserver.h"

int main()
{
    //wiringPiSetup();
    PWMObservable pwm = newPWMObservable();
    pwm->frequency = 1;
    pwm->dutyCycle = 20;
    PWMObserver in1 = newPWMObserver(25, false);
    //PWMObserver in2 = newPWMObserver(26, true);
    pwm->clazz->observe((Observable)pwm, (void*)in1);
    //pwm->clazz->observe((Observable)pwm, (void*)in2);
    pwm->clazz->start(pwm);
    sleep(5);
    pwm->clazz->join(pwm);
    deletePWMObservable(pwm);
    deletePWMObserver(in1);
    //deletePWMObserver(in2);
    return 0;
}