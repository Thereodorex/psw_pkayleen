#include "main.h"

static void	ft_putchar(char c)
{
	write(0, &c, 1);
}

void	ft_putnbr(int n)
{
	int		sign;

	sign = n < 0 ? -1 : 1;
	if (sign == -1)
		ft_putchar('-');
	if (n > 9 || n < -9)
		ft_putnbr(n / 10 * sign);
	ft_putchar(n % 10 * sign + '0');
}

void print_stack(t_stack *stack)
{
	int		i;

	i = -1;
	while (++i < stack->length)
	{
		print_str(" ");
		ft_putnbr(stack->stack[i]);
	}
	print_str("\n");
}

void print_stacks(t_state *state)
{
	print_str("A:");
	print_stack(&state->stack_a);
	print_str("B:");
	print_stack(&state->stack_b);
}