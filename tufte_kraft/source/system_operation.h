/**
* @file
* @brief Start up and running progress for elevator.
*
*/
#ifndef SYSTEM_OPERATION_H
#define SYSTEM_OPERATION_H

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

#include "hardware.h"
#include "hardware_input.h"
#include "elevator_state.h"
#include "request.h"

/**
* @brief Sigint handler.
*/
void sigint_handler(int sig);


/**
* @brief Start up of the system.
*/
void system_operation_start();

/**
* @brief Running system.
*/
void system_operation_program();

/**
* @brief Stop system.
*/
void system_operation_stop();

/**
* @brief Clear lights.
*/
void clear_all_order_lights();

/**
* @brief PRINTFs.
*/
void print_operating_info();

#endif
