#include "main.h"

static void		execute_step(t_state *state, int a_index, int b_index)
{
	// Поиск кратчайшей комбинации вращений для пары. Логика частично дублирует подсчёт функции ниже.
	// Операции сразу выполняются на стеках и записываются в результат
	int		i;
	int		j;
	int		rotate;
	int		reverse_rotate;
	int		different_rotates;

	rotate = a_index > b_index ? a_index : b_index;
	reverse_rotate = (state->stack_a.length - a_index) > (state->stack_b.length - b_index) ? (state->stack_a.length - a_index) : (state->stack_b.length - b_index);
	different_rotates = a_index + (state->stack_b.length - b_index);
	if (b_index + (state->stack_a.length - a_index) < different_rotates)
		different_rotates = b_index + (state->stack_a.length - a_index);
	if (rotate <= reverse_rotate && rotate <= different_rotates)
	{
		i = 0;
		while (i < b_index || i < a_index)
		{
			if (i < a_index && i < b_index)
				add_op(state, RR);
			else if (i < a_index)
				add_op(state, RA);
			else if (i < b_index)
				add_op(state, RB);
			i++;
		}
	}
	else if (reverse_rotate <= rotate && reverse_rotate <= different_rotates)
	{
		i = state->stack_a.length - 1;
		j = state->stack_b.length - 1;
		while (i >= a_index || j >= b_index)
		{
			if (i >= a_index && j >= b_index)
				add_op(state, RRR);
			else if (i >= a_index)
				add_op(state, RRA);
			else if (i >= b_index)
				add_op(state, RRB);
			i--;
			j--;
		}
	}
	else
	{
		if (a_index <= (state->stack_a.length - a_index))
		{
			i = -1;
			while (++i < a_index)
				add_op(state, RA);
		}
		else
		{
			i = state->stack_a.length;
			while (--i >= a_index)
				add_op(state, RRA);
		}
		if (b_index <= (state->stack_b.length - b_index))
		{
			i = -1;
			while (++i < b_index)
				add_op(state, RB);
		}
		else
		{
			i = state->stack_b.length;
			while (--i >= b_index)
				add_op(state, RRB);
		}
	}
	add_op(state, PA);
}

static int		calc_shortest_rotations(int a_index, int b_index, int a_length, int b_length)
{
	// Подсчёт кратчайшой комбинации вращений для пары
	// Операции не выполняются. Только считаются. Используется для поиска выгодной пары.
	int		rotate;
	int		reverse_rotate;
	int		different_rotates;

	rotate = a_index > b_index ? a_index : b_index;
	reverse_rotate = (a_length - a_index) > (b_length - b_index) ? (a_length - a_index) : (b_length - b_index);
	different_rotates = a_index + (b_length - b_index);
	if (b_index + (a_length - a_index) < different_rotates)
		different_rotates = b_index + (a_length - a_index);
	if (rotate <= reverse_rotate && rotate <= different_rotates)
		return (rotate);
	else if (reverse_rotate <= rotate && reverse_rotate <= different_rotates)
		return (reverse_rotate);
	return (different_rotates);
}

int		is_pair_ok(t_state *state, int a_index, int b_index)
{
	// 1 - ok, 0 - not ok
	int		prev_a_number;
	int		next_a_number;
	int		current_a_number;
	int		b_number;

	// не знаю зачем next_number, возможно он не нужен
	prev_a_number = a_index == 0 ? state->stack_a.stack[state->stack_a.length - 1] : state->stack_a.stack[a_index - 1];
	next_a_number = a_index == state->stack_a.length - 1 ? state->stack_a.stack[0] : state->stack_a.stack[a_index + 1];
	current_a_number = state->stack_a.stack[a_index];
	b_number = state->stack_b.stack[b_index];
	// Надо проверить что это корректная логика для обычных случаев
	if (current_a_number < next_a_number && current_a_number > prev_a_number)
	{
		printf("%d\n", state->stack_a.stack[a_index]);
		printf("%d\n", state->stack_b.stack[b_index]);
		if (b_number < current_a_number && b_number > prev_a_number)
			return (1);
	}
	// Надо проверить что это корректная логика для крайних случаев
	else if (b_number < current_a_number || b_number > prev_a_number)
		return (1);
	return (0);
}

void			main_algo(t_state *state)
{
	// Вращает стеки и выполняет pa один раз
	int		shortest_combo;
	int		shortest_index_a;
	int		shortest_index_b;
	int		i;
	int		j;

	shortest_combo = state->stack_a.length + state->stack_b.length;
	i = -1;
	while (++i < state->stack_a.length)
	{
		j = -1;
		while (++j < state->stack_b.length)
		{
			if (is_pair_ok(state, i, j) &&
			calc_shortest_rotations(i, j, state->stack_a.length, state->stack_b.length) < shortest_combo)
			{
				// Надо отрефакторить чтобы не было двух одинаковых вызовов
				shortest_index_a = i;
				shortest_index_b = j;
				shortest_combo = calc_shortest_rotations(i, j, state->stack_a.length, state->stack_b.length);
			}
		}
	}
	execute_step(state, shortest_index_a, shortest_index_b);
}