#include "main.h"

static void		swap_stack(int *arr)
{
	int	tmp;

	tmp = arr[0];
	arr[0] = arr[1];
	arr[1] = tmp;
}

void	push_stack(t_stack *stack1, t_stack *stack2)
{
	int num;
	int	i;

	num = stack2->stack[0];
	stack2->length--;
	i = -1;
	while (++i < stack2->length)
		stack2->stack[i] = stack2->stack[i + 1];
	i = stack1->length + 1;
	while (--i > 0)
		stack1->stack[i] = stack1->stack[i - 1];
	stack1->stack[0] = num;
	stack1->length++;
}

static void		rotate_stack(t_stack *stack)
{
	int num;
	int	i;

	num = stack->stack[0];
	i = -1;
	while (++i < stack->length)
		stack->stack[i] = stack->stack[i + 1];
	stack->stack[i - 1] = num;
}

static void		rotate_stack_back(t_stack *stack)
{
	int	num;
	int	i;

	num = stack->stack[stack->length - 1];
	i = stack->length + 1;
	while (--i)
		stack->stack[i] = stack->stack[i - 1];
	stack->stack[0] = num;
}


void	do_op(t_state *state, int oper)
{
	int		tmp;

	if (oper == SA)
		swap_stack(state->stack_a.stack);
	else if (oper == SB)
		swap_stack(state->stack_b.stack);	
	else if (oper == SS)
	{
		swap_stack(state->stack_a.stack);
		swap_stack(state->stack_b.stack);
	}
	else if (oper == PA)
	{
		push_stack(&state->stack_a, &state->stack_b);
	}
	else if (oper == PB)
	{
		push_stack(&state->stack_b, &state->stack_a);
	}
	else if (oper == RA)
	{
		rotate_stack(&state->stack_a);
	}
	else if (oper == RB)
	{
		rotate_stack(&state->stack_b);
	}
	else if (oper == RR)
	{
		rotate_stack(&state->stack_a);
		rotate_stack(&state->stack_b);
	}
	else if (oper == RRA)
	{
		rotate_stack_back(&state->stack_a);
	}
	else if (oper == RRB)
	{
		rotate_stack_back(&state->stack_b);
	}
	else if (oper == RRR)
	{
		rotate_stack_back(&state->stack_a);
		rotate_stack_back(&state->stack_b);
	}
}