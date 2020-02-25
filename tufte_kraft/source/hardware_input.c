#include "hardware_input.h"

int hardware_input_read_floors() {
    for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++)
        if (hardware_read_floor_sensor(i))
            return i;
    return -1;
}

void hardware_input_take_order() {
    for (int i = 0; i < HARDWARE_NUMBER_OF_FLOORS; i++)
        for(int j = HardwareOrderStart; j <= HardwareOrderLast; j++)
            if (hardware_read_order(i, j)) {
                hardware_command_order_light(i, j, 1);
                request_place_order(&(Order){i, j});
            }
}
