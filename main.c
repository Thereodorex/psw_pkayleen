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

int		init_state(t_state *state, int argc, char **argv)
{
	// Единственная функция с маллоком, кроме добавления новых операций в решение и самого state
	// Может возникнуть ошибка маллока
	char	*argv_copy;

	argv_copy = ft_strdup(argv[1]);
	state->numbers_count = countwords(argv_copy , ' ');
	// printf("%d\n", state->numbers_count);
	// printf("%s\n", argv_copy );
	state->numbers = ft_strsplit(argv_copy, ' ');
	// for (int i = 0; i < state->numbers_count; i++)
	// 	printf("%s\n", state->numbers[i]);
	state->stack_a.stack = ft_calloc(sizeof(int) * state->numbers_count);
	state->stack_b.stack = ft_calloc(sizeof(int) * state->numbers_count);
	state->solution.operations = ft_calloc(sizeof(int) * 10);	// динамический массив
	state->solution.size = 10;

	if (!state->stack_a.stack || !state->stack_b.stack || !state->solution.operations)
	{
		// Зафришить NULL не страшно
		free_state(state);
		return (1);
	}
	// Возвращает 0 - ок, 1 - ошибка маллока
	return (0);
}

void	parse_args(t_state *state)
{
	int		i;
	int		words_count;
	char	**splited;


	i = 0;
	while(i < state->numbers_count)
	{
		state->stack_a.stack[i] = ft_atoi(state->numbers[i]);
		state->stack_a.length++;
		// ft_putnbr(state->stack_a.stack[i]);
		// print_str("\n");
		i++;
	}
	del(state->numbers, state->numbers_count);
}

int		check_duplicates(t_state *state)
{
	// Возвращает 0 - ок, 1 - есть дубликаты
	return (0);
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
	return (0);
}

void	sort_three(t_state *state)
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

int		find_min_index(t_state *state)
{
	int		i;
	int		min;
	int		min_index;

	min = 0;
	min_index = 0;
	i = 0;
	if (state->stack_a.length)
		min = state->stack_a.stack[0];
	while (++i < state->stack_a.length)
	{
		if (state->stack_a.stack[i] < min)
		{
			min = state->stack_a.stack[i];
			min_index = i;
		}
	}
	return (min_index);
}

void	find_solution(t_state *state)
{
	int		min_index;
	// print_stacks(state);
	while (state->stack_a.length > 3)
		add_op(state, PB);
	sort_three(state);
	// print_stacks(state);
	while (state->stack_b.length)
	{
		main_algo(state);
		// print_stacks(state);
	}
	min_index = find_min_index(state);
	if (min_index < (state->stack_a.length - min_index))
		while (min_index--)
			add_op(state, RA);
	else
		while (min_index++ != state->stack_a.length)
			add_op(state, RRA);
	// print_str("\n");
	// print_stacks(state);
}

void	print_solution(t_state *state)
{
	int		i;

	i = -1;
	while (++i < state->solution.length)
	{
		if (state->solution.operations[i] == 0)
			print_str("sa\n");
		else if (state->solution.operations[i] == 1)
			print_str("sb\n");
		else if (state->solution.operations[i] == 2)
			print_str("ss\n");
		else if (state->solution.operations[i] == 3)
			print_str("pa\n");
		else if (state->solution.operations[i] == 4)
			print_str("pb\n");
		else if (state->solution.operations[i] == 5)
			print_str("ra\n");
		else if (state->solution.operations[i] == 6)
			print_str("rb\n");
		else if (state->solution.operations[i] == 7)
			print_str("rr\n");
		else if (state->solution.operations[i] == 8)
			print_str("rra\n");
		else if (state->solution.operations[i] == 9)
			print_str("rrb\n");
		else if (state->solution.operations[i] == 10)
			print_str("rrr\n");
	}
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
	if (init_state(state, argc, argv))
		return (error_func());
	parse_args(state);
	if (check_duplicates(state))
		return (error_func());
	find_solution(state);
	print_solution(state);
	free_state(state);
	free(state);
	return (0);
}