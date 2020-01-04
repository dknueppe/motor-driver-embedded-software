#include <wiringPi.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "PWMObservable.h"
#include "PWMObserver.h"
#include "PinObservable.h"
#include "PinObserver.h"

/* Pin assignments from motor driver board to wiringPi internals */
#define INPUT1      3
#define INPUT2      5
#define ENABLE      4
#define PROX_OUT    7
#define COMP_IN     0
#define COMP_OUT    2

int main()
{
    wiringPiSetup();

/* driving the motor */
    PWMObservable pwm = newPWMObservable();
    pwm->frequency = 440;
    pwm->dutyCycle = 100;
    PWMObserver in1 = newPWMObserver(INPUT1, false);
    PWMObserver in2 = newPWMObserver(INPUT2, false);
    pwm->clazz->observe((Observable)pwm, (void*)in1);
    pwm->clazz->start(pwm);

/* setup proximity sensor */
    PinObservable proximity_sensor = newPinObservable(PROX_OUT);
    PinObserver freq_counter = newPinObserver();
    proximity_sensor->clazz->observe((Observable)proximity_sensor, (void*)freq_counter);
    proximity_sensor->clazz->start(proximity_sensor);

/* setup motor current watchdog */
    PWMObservable ref_voltage = newPWMObservable();
    ref_voltage->frequency = 100;
    ref_voltage->dutyCycle = 5;
    PWMObserver comp_in = newPWMObserver(COMP_IN, false);
    ref_voltage->clazz->observe((Observable)ref_voltage, (void*)comp_in);
    ref_voltage->clazz->start(ref_voltage);
    PinObservable comp_out = newPinObservable(COMP_OUT);
    PWMObserver enable = newPWMObserver(ENABLE, false);
    comp_out->clazz->observe((Observable)comp_out, (void*)enable);
    comp_out->clazz->start(comp_out);

    while(getchar() != 'f') {
        printf("Motor dreht sich %f mal pro Minute", freq_counter->clazz->getRPM(freq_counter));
        enable->pin->clazz->setPin(enable->pin, HIGH);
    }

/* freeing up resources */
    pwm->clazz->join(pwm);
    proximity_sensor->clazz->join(proximity_sensor);
    ref_voltage->clazz->join(ref_voltage);
    comp_out->clazz->join(comp_out);
    deletePWMObservable(pwm);
    deletePWMObservable(ref_voltage);
    deletePWMObserver(in1);
    deletePWMObserver(in2);
    deletePWMObserver(enable);
    deletePinObservable(proximity_sensor);
    deletePinObservable(comp_out);
    deletePinObserver(freq_counter);
    return 0;
}
