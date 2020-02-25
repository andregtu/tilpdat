/**
* @file
* @brief State machine.
*
*/
#ifndef ELEVATOR_STATE_H
#define ELEVATOR_STATE_H

#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include "hardware.h"

/**
* @brief Floor position used in struct @c Order.
*/
typedef enum { 
	undef = -1, first, second, third, fourth
} Floor;

/**
* @brief Represent the real-world elevator
*/
typedef struct {
    Floor pos;
    HardwareMovement dir;
    bool door;
	clock_t time_wait;
} Elevator;

/**
* @brief Elevator state.
*/
Elevator* ELEVATOR_STATE;

#include "hardware_input.h"
#include "system_operation.h"
#include "request.h"

#define IDLE_TIME 1
/**
* @brief initialize the elevator-struct with a valid position and direction
*/
void elevator_state_initialize();

/**
* @brief 
*/
void elevator_state_update_pos();

/**
* @brief Moves the elevator to a defined position
* @return floor.
*/
 int elevator_state_go_to_defined_pos();

/**
* @brief 
*/
void elevator_state_update_floor_light();

/**
 * @brief Sets the movement of the elevator based on the difference between the current position and destination
 * 
 * @param [in] dest The destination floor
 * @param [in] pos The current position of the elevator
 * @param [out] ELEVATOR_STATE direction is changed
 * 
 */
void elevator_state_transition(Floor dest, Floor pos);

/**
 * @brief Either fills up the destination-list, or send a new destination to motor_state_elevator_transistion
 */
void elevator_state_move_elevator();


#endif
