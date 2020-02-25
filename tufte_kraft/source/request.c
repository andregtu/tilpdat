#include "request.h"

Order destinations[HARDWARE_NUMBER_OF_FLOORS]  = {[0 ... HARDWARE_NUMBER_OF_FLOORS-1] = ORDER_UNDEF};
Order orders[HARDWARE_NUMBER_OF_ORDER_BUTTONS] = {[0 ... HARDWARE_NUMBER_OF_ORDER_BUTTONS-1] = ORDER_UNDEF};

void request_place_order(Order* op) {
	if(destinations->pos == undef && orders->pos == undef) {
		destinations[0] = *op;
		return;
	}

	for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++)
		if(op->pos == destinations[i].pos) 
			return;

	for(int i = 0; i < HARDWARE_NUMBER_OF_ORDER_BUTTONS; i++)
		if(op->pos == orders[i].pos && op->dir == orders[i].dir) 
			return;

	int diff = op->pos - ELEVATOR_STATE->pos;

	if(diff == 0 && ELEVATOR_STATE->dir == HARDWARE_MOVEMENT_STOP) {
		//door_door_state_machine();
		return;
	}

	if(diff > 0 && ELEVATOR_STATE->dir == HARDWARE_MOVEMENT_UP && op->dir != (int)HARDWARE_MOVEMENT_DOWN) {
		for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++)
			if(destinations[i].pos == undef) {
				destinations[i] = *op;
				destinations_sort(ascending);
				return;
			}
	}

	if(diff < 0 && ELEVATOR_STATE->dir == HARDWARE_MOVEMENT_DOWN && op->dir != (int)HARDWARE_MOVEMENT_UP) {
		for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++)
			if(destinations[i].pos == undef) {
				destinations[i] = *op;
				destinations_sort(descending);
				return;
			}
	}

	for(int i = 0; i < HARDWARE_NUMBER_OF_ORDER_BUTTONS; i++)
		if(orders[i].pos == undef) {
			orders[i] = *op;
			return;
		}
}

void request_delete_current_destination() {
	for(int i = 0; i < HARDWARE_NUMBER_OF_ORDER_BUTTONS; i++)
		if(orders[i].pos == destinations->pos)
			orders[i] = (Order)ORDER_UNDEF;
	orders_sort();
	for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS - 1; i++)
		destinations[i] = destinations[i+1];
	destinations[HARDWARE_NUMBER_OF_FLOORS-1] = (Order)ORDER_UNDEF;
}

void request_fill_destination() {
	if(orders->pos != undef) {
		destinations[0] = orders[0];
		ELEVATOR_STATE->dir = destinations->dir;
	}

	Order orders_temp[HARDWARE_NUMBER_OF_ORDER_BUTTONS];

	for(int i = 0; i < HARDWARE_NUMBER_OF_ORDER_BUTTONS; i++) {
		orders_temp[i] = orders[i];
		orders[i] = (Order)ORDER_UNDEF;
	}
	
	for(int i = 0; i < HARDWARE_NUMBER_OF_ORDER_BUTTONS; i++)
		if (orders_temp[i].pos != undef)
			request_place_order(&orders_temp[i]);
}

void request_delete_all() {
	destinations_clear();
	orders_clear();
}

void destinations_sort(SortMode S) {
	for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++)
		for(int j = i+1; j < HARDWARE_NUMBER_OF_FLOORS; j++)
			if(destinations[j].pos != undef && destinations[i].pos*S > destinations[j].pos*S)
				swap_order(&destinations[i], &destinations[j]);
}

void swap_order(Order* o1, Order* o2) {
		Order temp = *o1;
		*o1 = *o2;
		*o2 = temp;
}

void orders_sort() {
	for(int i = 0; i < HARDWARE_NUMBER_OF_ORDER_BUTTONS; i++)
		if(orders[i].pos == undef) 
			for(int j = i+1; j < HARDWARE_NUMBER_OF_ORDER_BUTTONS; j++)
				if(orders[j].pos != undef) {
					orders[i] = orders[j];
					orders[j] = (Order)ORDER_UNDEF;
					break;
				}
}

void destinations_clear() {
	for(int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++)
	destinations[i] = (Order)ORDER_UNDEF;
}

void orders_clear() {
	for(int i = 0; i < HARDWARE_NUMBER_OF_ORDER_BUTTONS; i++)
	orders[i] = (Order)ORDER_UNDEF;
}
