#include "main.h"

int     check_args(int argc, char **argv)
{
    return (0);
}

void    init_state(t_state *state, int argc, char **argv)
{

}

void    parse_args(t_state *state)
{

}

void    find_solution(t_state *state)
{

}

void    print_solution(t_state *state)
{

}

int main(int argc, char **argv) {
    t_state     state;

    check_args(argc, argv);
    init_state(&state, argc, argv);
    parse_args(&state);
    find_solution(&state);
    print_solution(&state);
    return (0);
}