#include "main.h"

// TODO:
// Создать список операций и соответсвие число-строка
// Добавление операции и расширение массива
// Операции со стеками
// Алгоритм
// Всяческие проверки ввода
// Расширить парсер (сейчас каждое число подаётся отдельным аргументом)
// Чекер

int		check_args(int argc, char **argv)
{
	// Проверить, что в аргументах только числа
	// Проверить, что числа в допустимом диапазоне
	// Кол-во чисел в массиве

	// Возвращает 0 - ок, 1 - не ок
	return (0);
}

int		init_state(t_state *state, int argc)
{
	// Единственная функция с маллоком, кроме добавления новых операций в решение и самого state
	// Может возникнуть ошибка маллока
	state->numbers_count = argc - 1;
	state->stack_a.stack = ft_calloc(sizeof(int) * state->numbers_count);
	state->stack_b.stack = ft_calloc(sizeof(int) * state->numbers_count);
	state->stack_a.length = state->numbers_count;
	state->solution.operations = ft_calloc(sizeof(int) * 100);	// динамический массив
	state->solution.size = 100;
	state->solution.length = 0;

	if (!state->stack_a.stack || !state->stack_b.stack || !state->solution.operations)
	{
		// Зафришить NULL не страшно
		free_state(state);
		return (1);
	}
	// Возвращает 0 - ок, 1 - ошибка маллока
	return (0);
}

void	parse_args(t_state *state, char **argv)
{
	int		i;

	i = 0;
	while(i < state->numbers_count)
	{
		state->stack_a.stack[i] = ft_atoi(argv[i + 1]);
		ft_putnbr(state->stack_a.stack[i]);
		print_str("\n");
		i++;
	}
}

int		check_duplicates(t_state *state)
{
	// Возвращает 0 - ок, 1 - есть дубликаты
	return (0);
}

void	swap_stack(int *arr)
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

void	rotate_stack(t_stack *stack)
{
	int num;
	int	i;

	num = stack->stack[0];
	i = -1;
	while (++i < stack->length)
		stack->stack[i] = stack->stack[i + 1];
	stack->stack[i - 1] = num;
}

void	rotate_stack_back(t_stack *stack)
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

int		operation_append(t_solution *solution, int operation)
{
	int		i;
	int		*old_operations;
	if (solution->length == solution->size)
	{
		old_operations = solution->operations;
		solution->size *= 2;
		solution->operations = malloc(solution->size * sizeof(int));
		if (!solution->operations)
			return (1);
		i = -1;
		while (++i < solution->length)
			solution->operations[i] = old_operations[i];
		free(old_operations);
	}
	solution->operations[solution->length] = operation;
	solution->length++;
	return (0);
}

int		add_op(t_state *state, int oper)
{
	if (operation_append(&state->solution, oper))
		return (1);
	do_op(state, oper);
	operation_print();
	return (0);
}


void	sort_a(t_state	*state)
{
	t_stack		*stack;

	stack = &state->stack_a;
	// 1 2 3 или 2 3 1 или 3 1 2 ок

	// 1 3 2
	if (stack->stack[2] > stack->stack[0] && stack->stack[2] < stack->stack[1])
		add_op(state, SA);
	// 2 1 3
	if (stack->stack[0] > stack->stack[1] && stack->stack[0] < stack->stack[2])
		add_op(state, SA);
	// 3 2 1
	if (stack->stack[1] < stack->stack[0] && stack->stack[1] > stack->stack[2])
		add_op(state, SA);
}

void	search_min_comb(t_state *state)
{
	int	i;
	int	j;
	int	idx_num_a;
	int	num_a;	// пара чисел из топа стэков a и b, для которой есть подходщая комбинация
	int	num_b;

	int	flag; // 1 - комбинация подходит, 0 - не подходит
	i = -1;

	num_a = state->stack_a.stack[0];
	num_b = state->stack_b.stack[0];
	min_comb = state->stack_b.length;
	while (++i < state->stack_a.length)
	{
		j = -1;
		while (++j < state->stack_b.length)
		{
			if (state->stack_a.stack[0] >= state->stack_a.stack[state->stack_a.length - 1])
			{
				if ((state->stack_b.stack[0] > state->stack_a.stack[state->stack_a.length - 1])
					&& (state->stack_b.stack[0] < state->stack_a.stack[0]))
					flag = 1;
				else flag = 0;
			}
			else
			{
				if ((state->stack_b.stack[0] > state->stack_a.stack[state->stack_a.length - 1])
					|| (state->stack_b.stack[0] < state->stack_a.stack[0]))
					flag = 1;
				else flag = 0;
			}
			if (flag)
			{
				if (j < min_comb)
				{
					if (j <= state->stack_b.length / 2)
					min_comb = j;
					idx_num_a = i;
				}
			}
			// else
			// 	add_op(state, RB);
		}
	}
}

void	find_solution(t_state *state)
{
	int	min_comb;	// мин число вращений

	print_stacks(state);
	while (state->stack_a.length > 3)
		add_op(state, PB);
	print_stacks(state);

// сортировка 3ех элементов из стэка a
	sort_a(state);
	print_stacks(state);

// поиск мин. числа вращений с сохранением пары чисел
	min_comb = search_min_comb(state);

	if (min_comb <= state->stack_b.length / 2)
		while (min_comb != 0)
		{
			add_op(state, RB);
			min_comb--;
		}
	else
	{
		while (min_comb != state->stack_b.length)
		{
			add_op(state, RRB);
			min_comb++;
		}
	}
}

void	print_solution(t_state *state)
{

}

void	free_state(t_state *state)
{
	// Здесь освобождается всё, включая список операций, но не state
	free(state->stack_a.stack);
	free(state->stack_b.stack);
	free(state->solution.operations);
}

int		main(int argc, char **argv) {
	// Для удобства используем антипатерн god object
	t_state	*state;

	state = ft_calloc(sizeof(t_state));
	if (check_args(argc, argv))
		return (error_func());
	if (init_state(state, argc))
		return (error_func());
	parse_args(state, argv);
	if (check_duplicates(state))
		return (error_func());
	
	find_solution(state);
	print_solution(state);
	free_state(state);
	free(state);
	return (0);
}