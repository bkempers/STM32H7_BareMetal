/*
 * timer.h
 *
 *  Created on: Aug 25, 2025
 *      Author: benkempers
 */

#ifndef TIMER_H_
#define TIMER_H_

#include "includes.h"

void tim2_1hz_init();

void tim1_output_capture_init();
void tim4_input_capture_init();

void timx_driver(bool output_tim);



#endif /* TIMER_H_ */
