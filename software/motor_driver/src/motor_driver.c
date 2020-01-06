#include <wiringPi.h>
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>
#include "TimerObservable.h"
#include "PinObserver.h"
#include "PinObservable.h"
#include "FreqCounter.h"

/* Pin assignments from motor driver board to wiringPi internals */
#define INPUT1      3   /* connect YELLOW Wire with physical pin 15 (eigth on the inner row) */
#define INPUT2      5   /* connect RED Wire with physical pin 18 (ninth on the outer row) */
#define ENABLE      4   /* connect ORANGE Wire with physical pin 16 (eigth on the outer row) */
#define PROX_OUT    7   /* connect VIOLET Wire with physical pin 7 (fourth on the inner row) */
#define COMP_IN     1   /* connect BLUE Wire with physical pin 12 (sixth on the outer row) */
#define COMP_OUT    2   /* connect GREEN Wire with physical pin 13 (seventh on the inner row) */

int main()
{
    wiringPiSetup();

/* driving the motor */
    TimerObservable pwm = newTimerObservable(PWM_ENABLE);
    pwm->frequency = 440;
    pwm->dutyCycle = 100;
    PinObserver in1 = newPinObserver(INPUT1, LOW);
    PinObserver in2 = newPinObserver(INPUT2, LOW);
    pwm->clazz->observe((Observable)pwm, (void*)in1);
    pwm->clazz->start(pwm);

/* setup proximity sensor */
    PinObservable proximity_sensor = newPinObservable(PROX_OUT);
    FreqCounter freq_counter = newFreqCounter();
    proximity_sensor->clazz->observe((Observable)proximity_sensor, (void*)freq_counter);
    proximity_sensor->clazz->start(proximity_sensor);

/* setup voltage reference for current watchdog */
    pinMode(COMP_IN, PWM_OUTPUT);
    pwmSetClock(2);
    pwmSetRange(10);
    pwmWrite(1, 2);

/* setup motor current watchdog */
    PinObservable comp_out = newPinObservable(COMP_OUT);
    PinObserver enable = newPinObserver(ENABLE, HIGH);
    comp_out->clazz->observe((Observable)comp_out, (void*)enable);
    comp_out->clazz->start(comp_out);

    char tmp;
    while((tmp = getchar()) != 's') {
        printf("PRM: %.2f", freq_counter->clazz->getRPM(freq_counter));
        enable->pin->clazz->setPin(enable->pin, HIGH);
        if (tmp == 'r'){
            sem_wait(&(comp_out->_lock));
            sleep(1);
            sem_post(&(comp_out->_lock));
        }
    }

/* freeing up resources */
    pwm->clazz->join(pwm);
    proximity_sensor->clazz->join(proximity_sensor);
    comp_out->clazz->join(comp_out);
    deleteTimerObservable(pwm);
    deletePinObserver(in1);
    deletePinObserver(in2);
    deletePinObserver(enable);
    deletePinObservable(proximity_sensor);
    deletePinObservable(comp_out);
    deleteFreqCounter(freq_counter);
    return 0;
}
