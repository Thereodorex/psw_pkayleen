#include <unistd.h>
#include <stdlib.h>

// команды
#define SA 0
#define SB 1
#define SS 2
#define PA 3
#define PB 4
#define RA 5
#define RB 6
#define RR 7
#define RRA 8
#define RRB 9
#define RRR 10


// стек фиксированного размера
typedef struct	s_stack
{
	int		*stack;
	int		length;
}				t_stack;

// динамический массив
typedef struct	s_solution
{
	int		length; // текущее количество элементов
	int		size; // текущая вместимость
	int		*operations; // сам массив
}				t_solution;

typedef struct	s_state
{
	int			numbers_count;
	t_stack		stack_a;
	t_stack		stack_b;
	t_solution	solution;
}				t_state;

// utils
size_t			str_len(char *str);
void			print_str(char *str);
int				error_func();
void			*ft_calloc(size_t size);
int				ft_atoi(char *str);

// main functions
int				check_args(int argc, char **argv);
int				init_state(t_state *state, int argc);
void			parse_args(t_state *state, char **argv);
int				check_duplicates(t_state *state);
void			find_solution(t_state *state);
void			print_solution(t_state *state);
void			free_state(t_state *state);

// debug
void			ft_putnbr(int n);
void 			print_stacks(t_state *state);