#include "main.h"

size_t  str_len(char *str)
{
    char    *ptr;

    ptr = str;
    while(*ptr)
        ptr++;
    return (ptr - str);
}

void    print_str(char *str)
{
    write(1, str, str_len(str));
}

int     error_func()
{
    print_str("Error\n");
    return (0);
}

void	*ft_calloc(size_t size)
{
	void	*ptr;
	char	*bzerator;

	ptr = malloc(size);
	if (ptr)
	{
		bzerator = (char *)ptr;
		while (bzerator < (char *)(ptr + size))
			*bzerator++ = 0;
	}
	return (ptr);
}

int			ft_atoi(char *str)
{
	int		sign;
	int		res;

	sign = *str == '-' ? -1 : 1;
	if (*str == '-' || *str == '+')
		str++;
	res = 0;
	while (*str >= '0' && *str <= '9')
		res = res * 10 + *str++ - '0';
	return (res);
}