/**
* @file
* @brief Defines the Order struct, and is responsible for the arrays containing them. 
* 
*/
#ifndef REQUEST_H
#define REQUEST_H

#include <stdio.h>
#include <stdlib.h>
#include "hardware.h"
#include "elevator_state.h"

/**
 *@brief Struct used in array @c destinations and @c orders. 
 */
typedef struct {
    Floor pos;
    HardwareOrder dir;
} Order;

/**
* @brief Undefined Order type to initialize and reset @c destinations and @c orders.
*/
#define ORDER_UNDEF {undef, HARDWARE_ORDER_INSIDE}

typedef enum {
	descending = -1,
	ascending = 1
} SortMode;

/**
* @brief Requests in presceding elevator direction, top priority.
*/
Order destinations[HARDWARE_NUMBER_OF_FLOORS];

/**
* @brief Requests in none-presceding elevator direction, chronological order, sub-priorities.
*/
Order orders[HARDWARE_NUMBER_OF_ORDER_BUTTONS];

/**
* @brief Checks if @c op exist in @c destinations or @c orders, and preceed to place Order to @c destinations or @c orders based upon the member values and logic.
*/
void request_place_order(Order* op);

/**
* @brief Fills up the destinations list with elements from the order list
*/
void request_fill_destination();

/**
* @brief deletes the first element in destinations and move the remainding elements one place towards the front
*/
void request_delete_current_destination();

/**
* @brief deletes all requests.
*/
void request_delete_all();

/**
* @brief Puts the valid elements in the destinations-list in ascending order
*
* @param S sort mode. -1 for descending and 1 for ascending.
*/
void destinations_sort(SortMode S);

/**
* @brief Swaps the pointers of two Order elements
*/
void swap_order(Order *o1, Order *o2);

/**
* @brief Removes all elements in destinations and replaces them with invalid elements 
*/
void destinations_clear();

/**
* @brief Removes all elements in orders and replaces them with invalid elements 
*/
void orders_clear();

/**
* @brief .
*/
void orders_sort();

#endif
