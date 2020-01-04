#include <wiringPi.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "PWMObservable.h"
#include "PWMObserver.h"
#include "PinObservable.h"
#include "PinObserver.h"

int main()
{
    wiringPiSetup();
    PWMObservable pwm = newPWMObservable();
    pwm->frequency = 440;
    pwm->dutyCycle = 100;
    PWMObserver in1 = newPWMObserver(3, false);
    PWMObserver in2 = newPWMObserver(5, false);
    PWMObserver enable = newPWMObserver(4, false);
    pwm->clazz->observe((Observable)pwm, (void*)in1);
    pwm->clazz->start(pwm);
    PinObservable proximity_sensor = newPinObservable(7);
    PinObserver freq_counter = newPinObserver();
    proximity_sensor->clazz->observe((Observable)proximity_sensor, (void*)freq_counter);
    proximity_sensor->clazz->start(proximity_sensor);
    while(getchar() != 'f')
        printf("Motor dreht sich %f mal pro Minute\n", freq_counter->clazz->getRPM(freq_counter));
    //for(unsigned int i = 0;; i+=3){
    //    pwm->clazz->setDutyCycle(pwm, i%100);
    //    usleep(100000);
    //}
    pwm->clazz->join(pwm);
    proximity_sensor->clazz->join(proximity_sensor);
    deletePWMObservable(pwm);
    deletePWMObserver(in1);
    deletePWMObserver(in2);
    deletePWMObserver(enable);
    deletePinObservable(proximity_sensor);
    deletePinObserver(freq_counter);
    return 0;
}
