#include "system_operation.h"

void system_operation_start() {
    int error = hardware_init();

    if (error != 0) {
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }
    signal(SIGINT, sigint_handler);

    printf("\n=== Running elevator program ===\n");

    elevator_state_initialize();
}

void system_operation_program() {

    while(1) {

        print_operating_info();

        if(hardware_read_stop_signal()) {

            hardware_command_stop_light(1);
            hardware_command_movement(HARDWARE_MOVEMENT_STOP);

            if (hardware_input_read_floors() != undef)
                 hardware_command_door_open(1);

            while(hardware_read_stop_signal())
                ELEVATOR_STATE->time_wait = clock() + CLOCKS_PER_SEC * IDLE_TIME;
            hardware_command_stop_light(0);
            
            clear_all_order_lights();
            request_delete_all();
        }

        elevator_state_update_pos();
        elevator_state_update_floor_light();
        hardware_input_take_order();

        if(hardware_read_obstruction_signal() && clock() < ELEVATOR_STATE->time_wait) {
            ELEVATOR_STATE->time_wait = clock() + CLOCKS_PER_SEC * IDLE_TIME;
        }
        
        if(clock() > ELEVATOR_STATE->time_wait) {
            hardware_command_door_open(0);
            elevator_state_move_elevator();
        }
    }
}

void system_operation_stop() {
    printf("Stopped\n");
    clear_all_order_lights();
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
}

void sigint_handler(int sig) {
    (void)(sig);
    printf("Terminating elevator\n");
    hardware_command_movement(HARDWARE_MOVEMENT_STOP);
    exit(0);
}

void clear_all_order_lights() {
    HardwareOrder order_types[3] = {
        HARDWARE_ORDER_UP,
        HARDWARE_ORDER_INSIDE,
        HARDWARE_ORDER_DOWN
    };

    for(int f = 0; f < HARDWARE_NUMBER_OF_FLOORS; f++){
        for(int i = 0; i < 3; i++){
            HardwareOrder type = order_types[i];
            hardware_command_order_light(f, type, 0);
        }
    }
}

void print_operating_info() {
    int check_floor = hardware_input_read_floors();
    if (( check_floor != undef) && (check_floor != ELEVATOR_STATE->pos) ) {

        printf("\nFloor %d \nDirection: %d", check_floor+1,((ELEVATOR_STATE->dir)-1)*(-1));
        printf("\nDestinations: ");
        for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++) {
            printf("%d ", destinations[i].pos+1);
        }

        printf("\nOrders: ");
        for (int i = 0; i < HARDWARE_NUMBER_OF_ORDER_BUTTONS; i++) {
            printf("%d ", orders[i].pos+1);
        }
        printf("\n");
    }
}