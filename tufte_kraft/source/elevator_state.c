#include "elevator_state.h"

Elevator* ELEVATOR_STATE = &(Elevator){undef, HARDWARE_MOVEMENT_STOP, 0, 0};

int elevator_state_go_to_defined_pos() {
  while(hardware_input_read_floors() == undef) {
    hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
  }
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    return hardware_input_read_floors();
}

void elevator_state_initialize() {
  ELEVATOR_STATE->pos = elevator_state_go_to_defined_pos();
  ELEVATOR_STATE->dir = HARDWARE_MOVEMENT_STOP;
}

void elevator_state_update_pos() {
  if(hardware_input_read_floors() != undef)
    ELEVATOR_STATE->pos = hardware_input_read_floors();
}

void elevator_state_update_floor_light() {
  if(ELEVATOR_STATE->pos != undef)
    hardware_command_floor_indicator_on(ELEVATOR_STATE->pos);
}

void elevator_state_transition(Floor dest, Floor pos) {

  int diff = dest - pos;

  if(diff < 0) {
    hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    ELEVATOR_STATE->dir = HARDWARE_MOVEMENT_DOWN;
  }
  if(diff > 0) {
    hardware_command_movement(HARDWARE_MOVEMENT_UP);
    ELEVATOR_STATE->dir = HARDWARE_MOVEMENT_UP;
  }
  if(diff == 0) {
    if (hardware_input_read_floors() == undef)
    switch(ELEVATOR_STATE->dir) {
      case HARDWARE_MOVEMENT_UP:
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
        return;
      case HARDWARE_MOVEMENT_DOWN:
        hardware_command_movement(HARDWARE_MOVEMENT_UP);
        return;
      case HARDWARE_MOVEMENT_STOP:
      break;
    }
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    ELEVATOR_STATE->dir = HARDWARE_MOVEMENT_STOP;
    hardware_command_door_open(1);
  }
}


void elevator_state_move_elevator() {
    if (destinations->pos == undef)
        request_fill_destination();

    if ( destinations->pos != undef ) {
        elevator_state_transition(destinations->pos, ELEVATOR_STATE->pos);

        if (ELEVATOR_STATE->pos == destinations->pos) {
            for (int i = HardwareOrderStart; i <= HardwareOrderLast; i++)
                hardware_command_order_light(ELEVATOR_STATE->pos, i, 0);
            request_delete_current_destination();
            ELEVATOR_STATE->time_wait = clock() + CLOCKS_PER_SEC * IDLE_TIME;
        }
    }
}