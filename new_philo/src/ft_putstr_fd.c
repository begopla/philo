#include "../include/philo.h"

static size_t	ft_strlen(const char *s)
{
	size_t	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

size_t	ft_putstr_fd(const char *str, int fd)
{
	if (!str)
		return (write(fd, "(null)", 6));
	else
		return (write(fd, str, ft_strlen(str)));
}
