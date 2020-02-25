/**
* @file
* @brief Hardware input.
* Iterates through floor sensors and order buttons using functions defined in hardware.h
*/
#ifndef HARDWARE_INPUT_H
#define HARDWARE_INPUT_H

#include <stdio.h>
#include "elevator_state.h"
#include "hardware.h"
#include "request.h"

/**
* @brief First element in enum @c HardwareOrder used for iterating through elements in function @c hardware_input_take_order.
*/
#define HardwareOrderStart 0
/**
* @brief Last element in enum @c HardwareOrder used for iterating through elements in function @c hardware_input_take_order.
*/
#define HardwareOrderLast 2

/**
* @brief Iterate through floors looking for a sensor-read
*
* @return int floor.
*/
int hardware_input_read_floors();

/**
* @brief Iterates through different order-inputs, and create and divert valid orders.
*/
void hardware_input_take_order();

#endif
