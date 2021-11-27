#include "main.h";

int main(int argc, char **argv) {
    t_state     state;

    check_args(argc, argv);
    init_program(&state, argc, argv);
    parse_args(&state);
    find_solution(&state);
    print_solution(&state);
    return (0);
}