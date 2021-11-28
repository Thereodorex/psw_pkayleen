#include "main.h"

char	*ft_strdup(const char *s1)
{
	size_t	len;
	char	*s2;

	len = str_len(s1);
	if (!(s2 = (char*)malloc(sizeof(char) * (len + 1))))
		return (NULL);
	s2[len] = '\0';
	while (len-- > 0)
		s2[len] = s1[len];
	return (s2);
}

static void		ft_bzero(void *s, size_t n)
{
	char	*str;

	str = (char*)s;
	while (n--)
		*str++ = 0;
}

static void		*ft_memalloc(size_t size)
{
	void	*mem;
	size_t	i;

	if (size == 0)
		return (NULL);
	if (!(mem = (void *)malloc(size)))
		return (NULL);
	i = 0;
	ft_bzero(mem, size);
	return (mem);
}

char	*ft_strnew(size_t size)
{
	return ((char*)ft_memalloc(sizeof(char) * (size + 1)));
}

int 	countwords(char *str, char c)
{
	int		i;
	int		counter;

	i = 0;
	counter = 0;
	if (str[0] != c && str[0] != '\0')
		counter = 1;
	while (str[++i])
		if (str[i] != c && str[i - 1] == c)
			counter++;
	return (counter);
}

static char	*findnext(char *ptr, char c)
{
	while (++ptr)
		if (*(ptr - 1) == c && *ptr != c)
			return (ptr);
	return (NULL);
}

static char	*worddup(char *s, char c)
{
	int		len;
	char	*str;

	len = 0;
	while (s[len] != c && s[len])
		len++;
	if (!(str = ft_strnew(sizeof(char) * len)))
		return (NULL);
	while (len--)
		str[len] = s[len];
	return (str);
}

void	del(char **as, int size)
{
	int		i;

	i = -1;
	while (++i < size)
	{
		if (as[i])
			free(as[i]);
	}
	free(as);
}

char		**ft_strsplit(char const *s, char c)
{
	char	**as;
	int		size;
	char	*ptr;
	int		i;

	if (!s)
		return (NULL);
	size = countwords((char *)s, c);
	if (!(as = (char**)malloc(sizeof(char *) * (size + 1))))
		return (NULL);
	i = 0;
	while (i <= size)
		as[i++] = NULL;
	ptr = s[0] == c ? findnext((char*)s, c) : (char*)s;
	i = -1;
	while (++i < size)
	{
		if (!(as[i] = worddup(ptr, c)))
		{
			del(as, size);
			return (NULL);
		}
		ptr = findnext(ptr, c);
	}
	return (as);
}