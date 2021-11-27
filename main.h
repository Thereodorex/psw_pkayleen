typedef struct  s_stack
{
    int     *stack;
    int     length;
}               t_stack;

typedef struct  s_state
{
    int         numbers_count;
    t_stack     stack_a;
    t_stack     stack_b;
    char        **solution;
}               t_state;